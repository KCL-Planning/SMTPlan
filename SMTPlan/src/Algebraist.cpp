#include "SMTPlan/Algebraist.h"

/* implementation of SMTPlan::Algebraist */
namespace SMTPlan {

	/*--------------*/
	/* FUNCTIONFLOW */
	/*--------------*/

	void FunctionFlow::addExpression(int opID, std::set<int> deps, pexpr &expr) {

		// expression in combination with others
		std::set<int> newOpKey;
		std::vector<SingleFlow> newFlows;
		std::vector<SingleFlow>::iterator fit = flows.begin();
		for(; fit!=flows.end(); fit++) {

			SingleFlow newFlow;
			newFlow.operators = fit->operators;
			newFlow.dependencies = fit->dependencies;
			newFlow.polynomial = fit->polynomial + expr;

			newFlow.operators.insert(opID);
			newFlow.dependencies.insert(deps.begin(), deps.end());
			newFlows.push_back(newFlow);

			std::set<int>::iterator kit = fit->operators.begin();
			for(; kit!=fit->operators.end(); kit++) {
				if(*kit < 0) newOpKey.insert(*kit);
				else newOpKey.insert(-(*kit));
			}

			fit->operators.insert(-opID);
		}

		flows.insert(flows.end(), newFlows.begin(), newFlows.end());

		// new expression
		SingleFlow newFlow;
		newFlow.operators = newOpKey;
		newFlow.operators.insert(opID);
		newFlow.dependencies = deps;
		newFlow.polynomial = expr;
		flows.push_back(newFlow);
	}

	void FunctionFlow::createChildren(std::map<int,FunctionFlow*> &allFlows) {

		std::vector<SingleFlow> resolvedFlows;
		while(flows.size() > 0) {

			SingleFlow currentFlow = flows.back();
			flows.pop_back();

			// this flow has no more dependencies
			if(currentFlow.dependencies.size() == 0) {
				resolvedFlows.push_back(currentFlow);
				continue;
			}

			int depID = *(currentFlow.dependencies.begin());
			FunctionFlow* dep = allFlows[depID];
			currentFlow.dependencies.erase(currentFlow.dependencies.begin());

			// dependency is constant
			if(dep->flows.size() == 0) {
				flows.push_back(currentFlow);
				continue;
			}

			// for each single flow of the dependency
			bool dep_op_distinct = true;
			std::vector<SingleFlow>::iterator fit = dep->flows.begin();
			for(; fit!=dep->flows.end(); fit++) {

				std::vector<int> v(10);
				std::vector<int>::iterator it = std::set_difference(
						fit->operators.begin(),fit->operators.end(),
						currentFlow.operators.begin(), currentFlow.operators.end(), v.begin());
				v.resize(it - v.begin());

				if(v.size() == 0) {

					// the dependent flow's conditions are subsumed by this one's
					currentFlow.polynomial = currentFlow.polynomial.subs(dep->function_string, fit->polynomial);
					flows.push_back(currentFlow);
					dep_op_distinct = false;
					
				} else {

					// check if they are incompatible and skip
					std::vector<int>::iterator vit = v.begin();
					for(; vit!=v.end(); vit++) {
						if(currentFlow.operators.find(-(*vit)) != currentFlow.operators.end())
							continue;
					}

					// add the difference to the operators and substitute
					SingleFlow newFlow;
					newFlow.operators = currentFlow.operators;
					newFlow.dependencies = currentFlow.dependencies;
					newFlow.polynomial = currentFlow.polynomial;

					newFlow.operators.insert(v.begin(), v.end());
					newFlow.polynomial = currentFlow.polynomial.subs(dep->function_string, fit->polynomial);

					flows.push_back(newFlow);

					// if difference == dep->flows.size() every time, then we can also add a dep==constant entry
					if(v.size() != fit->operators.size()) dep_op_distinct = false;

				}
			}
		
			// if all dependency flows were operator distinct, the dependency could be constant
			if(dep_op_distinct) flows.push_back(currentFlow);
		}

		flows = resolvedFlows;
	}

	void FunctionFlow::integrate() {

		std::vector<SingleFlow>::iterator fit = flows.begin();
		for(; fit!=flows.end(); fit++) {

			// do derivatives first
			fit->derivatives.push_back(fit->polynomial);
			pexpr expr = fit->polynomial;
			while(expr != 0) {
				expr = piranha::math::partial(expr,"hasht");
				if(expr!=0) fit->derivatives.push_back(expr);
			}

			// now do integration
			fit->polynomial = piranha::math::integrate(fit->polynomial,"hasht");
			fit->polynomial = fit->polynomial + function_var;
		}
		integrated = true;
	}

	bool FunctionFlow::dependenciesResolved(std::map<int,FunctionFlow*> &allFlows) {

		std::vector<SingleFlow>::iterator fit = flows.begin();
		for(; fit!=flows.end(); fit++) {

			std::set<int>::iterator dit = fit->dependencies.begin();
			for(; dit!=fit->dependencies.end(); dit++) {
				if(!allFlows[*dit]->integrated) return false;
			}
		}		
		return true;
	}

	/*------------*/
	/* ALGEBRAIST */
	/*------------*/

	/* state */
	int alg_opID;
	int alg_funID;
	bool alg_is_continuous;
	VAL::time_spec alg_cond_time;
	VAL::time_spec alg_eff_time;
	VAL::comparison_op alg_comparison_op;

	/**
	 * Main processing method
	 */
	bool Algebraist::processDomain() {

		alg_state = ALG_COLLECT_STATICS;
		// std::cout << "STATICS" << std::endl;

		// examine initial state to get constant values of static functions
		VAL::effect_lists* eff_list = val_analysis->the_problem->initial_state;
		for (VAL::pc_list<VAL::assignment*>::const_iterator ci = eff_list->assign_effects.begin(); ci != eff_list->assign_effects.end(); ci++) {
			const VAL::assignment* effect = *ci;
			Inst::PNE * l = new Inst::PNE(effect->getFTerm(), fe);	
			Inst::PNE * const lit = Inst::instantiatedOp::findPNE(l);

			int pneID = lit->getID();
			std::string function_symbol = l->getHead()->getName();

			effect->getExpr()->visit(this);
			pexpr expr = alg_expression_stack.back();
			alg_expression_stack.pop_back();

			if(problem_info->staticFunctionMap[lit->getHead()->getName()]) {
				problem_info->staticFunctionValuesPiranha.insert(std::make_pair(pneID,expr));
			}
			delete l;
		}

		alg_state = ALG_PROCESS_FUNCTIONS;
		// std::cout << "FUNCTIONS" << std::endl;

		// for each operator, process effects
		Inst::OpStore::iterator opsItr = Inst::instantiatedOp::opsBegin();
		const Inst::OpStore::iterator opsEnd = Inst::instantiatedOp::opsEnd();
		for (; opsItr != opsEnd; ++opsItr) {
			Inst::instantiatedOp * const currOp = *opsItr;
		    alg_opID = currOp->getID() + 1;
			fe = currOp->getEnv();
			currOp->forOp()->visit(this);
		}

		bool allComplete = false;
		while(!allComplete) {

			allComplete = true;
			map<int,FunctionFlow*>::iterator fit = function_flow.begin();

			for (; fit != function_flow.end(); ++fit) {

				// check completed
				if(fit->second->integrated) {
					continue;
				}

				// std::cout << fit->first << std::endl;

				// check dependencies
				if(!fit->second->dependenciesResolved(function_flow)) {
					allComplete = false;
					continue;
				}
				fit->second->createChildren(function_flow);
				fit->second->integrate();
			}
		}
	}

	/*-------------------------*/
	/* operators and processes */
	/*-------------------------*/

	/**
	 * Visit an operator in order to process its continuous effects
	 */
	void Algebraist::visit_durative_action(VAL::durative_action * da) {
		da->effects->visit(this);
	}

	/**
	 * Visit a PDDL process in order to process its continuous effects
	 */
    void Algebraist::visit_process(VAL::process * p){
		p->effects->visit(this);
	}

	/*---------*/
	/* effects */
	/*---------*/

	void Algebraist::visit_effect_lists(VAL::effect_lists * e) {
		e->forall_effects.pc_list<VAL::forall_effect*>::visit(this);
		e->cond_effects.pc_list<VAL::cond_effect*>::visit(this);
		e->cond_assign_effects.pc_list<VAL::cond_effect*>::visit(this);
		e->assign_effects.pc_list<VAL::assignment*>::visit(this);
		e->timed_effects.pc_list<VAL::timed_effect*>::visit(this);
	}

	void Algebraist::visit_timed_effect(VAL::timed_effect * e) {
		alg_eff_time = e->ts;
		e->effs->visit(this);
	};

	void Algebraist::visit_assignment(VAL::assignment * e) {

		Inst::PNE * l = new Inst::PNE(e->getFTerm(), fe);	
		Inst::PNE * const lit = Inst::instantiatedOp::findPNE(l);

		if (!lit) return;

		alg_funID = lit->getID();

		// create flow structure
		checkFunction(lit);

		// process expression
		alg_is_continuous = false;
		alg_dependency_stack.clear();
		e->getExpr()->visit(this);
		pexpr expr = alg_expression_stack.back();
		alg_expression_stack.pop_back();

		if(!alg_is_continuous) return;

		// expression as derivative
		expr = expr * piranha::math::pow(hasht,-1);


		// operator
		VAL::assign_op op = e->getOp();
		switch(op) {
		case VAL::E_DECREASE:
			expr = -1*expr;
		case VAL::E_INCREASE:
			function_flow[alg_funID]->addExpression(alg_opID, alg_dependency_stack, expr);
			alg_dependency_stack.clear();
			break;
		}

		delete l;
	}

	void Algebraist::visit_forall_effect(VAL::forall_effect * e) {std::cout << "not implemented forall" << std::endl;};
	void Algebraist::visit_cond_effect(VAL::cond_effect * e) {std::cout << "not implemented cond" << std::endl;};

	/*-------------*/
	/* expressions */
	/*-------------*/

	void Algebraist::visit_plus_expression(VAL::plus_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		pexpr lhs = alg_expression_stack.back();
		alg_expression_stack.pop_back();
		pexpr rhs = alg_expression_stack.back();
		alg_expression_stack.pop_back();

		alg_expression_stack.push_back(lhs + rhs);
	}

	void Algebraist::visit_minus_expression(VAL::minus_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		pexpr rhs = alg_expression_stack.back();
		alg_expression_stack.pop_back();
		pexpr lhs = alg_expression_stack.back();
		alg_expression_stack.pop_back();

		alg_expression_stack.push_back(lhs - rhs);
	}

	void Algebraist::visit_mul_expression(VAL::mul_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		pexpr lhs = alg_expression_stack.back();
		alg_expression_stack.pop_back();
		pexpr rhs = alg_expression_stack.back();
		alg_expression_stack.pop_back();

		alg_expression_stack.push_back(lhs * rhs);
	}

	void Algebraist::visit_div_expression(VAL::div_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		pexpr rhs = alg_expression_stack.back();
		alg_expression_stack.pop_back();
		pexpr lhs = alg_expression_stack.back();
		alg_expression_stack.pop_back();

		alg_expression_stack.push_back(lhs * piranha::math::pow(rhs,-1));		
	}

	void Algebraist::visit_uminus_expression(VAL::uminus_expression * s) {

		s->getExpr()->visit(this);

		pexpr exp = alg_expression_stack.back();
		alg_expression_stack.pop_back();

		alg_expression_stack.push_back(-1 * exp);
	}

	void Algebraist::visit_int_expression(VAL::int_expression * s) {
		alg_expression_stack.push_back(pexpr{s->double_value()});
	}

	void Algebraist::visit_float_expression(VAL::float_expression * s) {
		alg_expression_stack.push_back(pexpr{s->double_value()});
	}

	void Algebraist::visit_func_term(VAL::func_term * s) {

		Inst::PNE * l = new Inst::PNE(s, fe);
		Inst::PNE * const lit = Inst::instantiatedOp::findPNE(l);
		
		if (!lit) {
			std::cerr << "literal not found in expression: " << (*l) << std::endl;
			return;
		}

		checkFunction(lit);

		if(problem_info->staticFunctionMap[l->getHead()->getName()]) {
			alg_expression_stack.push_back(problem_info->staticFunctionValuesPiranha.find(lit->getID())->second);
		} else {
			alg_expression_stack.push_back(function_var[lit->getID()]);
			alg_dependency_stack.insert(lit->getID());
		}

		delete l;
	}

	void Algebraist::visit_special_val_expr(VAL::special_val_expr * s) {

		switch(s->getKind()) {

		case VAL::E_DURATION_VAR:
			alg_expression_stack.push_back(pexpr{"duration"});
			break;
		case VAL::E_HASHT:
			alg_is_continuous = true;
			alg_expression_stack.push_back(hasht);
			break;
		case VAL::E_TOTAL_TIME:
			alg_expression_stack.push_back(pexpr{"totaltime"});
			break;
		}
	}

	/*-------*/
	/* extra */
	/*-------*/

	void Algebraist::visit_timed_initial_literal(VAL::timed_initial_literal * til) {};
	void Algebraist::visit_preference(VAL::preference *){}
	void Algebraist::visit_event(VAL::event * e){}
	void Algebraist::visit_derivation_rule(VAL::derivation_rule * o){}

}; // close namespace
