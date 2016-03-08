#include "SMTPlan/Encoder.h"

/* implementation of SMTPlan::Encoder */
namespace SMTPlan {

	void Encoder::setOutput(std::ostream &o) {
		out = &o;
	}

	/*------------------*/
	/* encoding problem */
	/*------------------*/

	/**
	 * writes an encoding of grounded problem to output stream
	 */
	bool Encoder::encode(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int H) {

		(*out) << ";; SMTPlan PDDL+ encoding" << std::endl;
		(*out) << ";; domain: " << domain->name << "; problem: " << problem->name << std::endl;
		(*out) << "(set-logic QF_NRA)" << std::endl;

		for(int h=0; h<H; h++) {
			encodeHeader(domain, problem, grounder, h);
		}

		encodeInitialState(domain, problem, grounder);
		encodeGoalState(domain, problem, grounder, H);

		for(int h=0; h<H; h++) {
			encodeTimings(h);
			encodeVariableSupport(domain, problem, grounder, h);
			encodeActionConditions(domain, problem, grounder, h);
			encodeActionEffects(domain, problem, grounder, h);
			encodeActionMutexes(domain, problem, grounder, h);
		}

		return true;
	}

	/**
	 * writes header vars, for happening h
	 */
	void Encoder::encodeHeader(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		(*out) << "(declare-fun time_" << h << " Real)" << std::endl;
		(*out) << "(declare-fun duration_" << h << " Real)" << std::endl;

		// propositions
		for (int i=0; i<grounder.props.size(); i++) {
			(*out) << "(declare-fun " << grounder.props[i].var_name << "_0_" << h << " Bool)" << std::endl;
			(*out) << "(declare-fun " << grounder.props[i].var_name << "_1_" << h << " Bool)" << std::endl;
		}

		// fluents
		for (int i=0; i<grounder.fluents.size(); i++) {
			(*out) << "(declare-fun " << grounder.fluents[i].var_name << "_0_" << h << " Real)" << std::endl;
			(*out) << "(declare-fun " << grounder.fluents[i].var_name << "_1_" << h << " Real)" << std::endl;
		}

		// actions
		for (int i=0; i<grounder.actions.size(); i++) {
			(*out) << "(declare-fun " << "sta_" << grounder.actions[i].var_name << "_" << h << " Bool)" << std::endl;
			(*out) << "(declare-fun " << "end_" << grounder.actions[i].var_name << "_" << h << " Bool)" << std::endl;
			(*out) << "(declare-fun " << "run_" << grounder.actions[i].var_name << "_" << h << " Bool)" << std::endl;
			(*out) << "(declare-fun " << "dur_" << grounder.actions[i].var_name << "_" << h << " Real)" << std::endl;
		}
	}

	/*--------------*/
	/* known states */
	/*--------------*/

	/**
	 * Constraints P3--P4 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes the happening time constraints
	 */	
	void Encoder::encodeTimings(int h) {

		if(h==0) {
			(*out) << "(assert (= t_0 0))" << std::endl;
		} else {
			(*out) << "(assert (= t_" << h << " (+ t_" << (h-1) << " duration_" << (h-1) << ")))" << std::endl;
			(*out) << "(assert (> t_" << h << " t_" << (h-1) << "))" << std::endl;
		}
		(*out) << "(assert (>= duration_" << h << " 0.1))" << std::endl;
	}

	/**
	 * Constraints P1 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes the initial state
	 */
	void Encoder::encodeInitialState(VAL::domain* domain, VAL::problem* problem, Grounder &grounder) {

		VAL::effect_lists* eff_list = problem->initial_state;

		// simple add effects
		for (VAL::pc_list<VAL::simple_effect*>::const_iterator ci = eff_list->add_effects.begin(); ci != eff_list->add_effects.end(); ci++) {
			const VAL::simple_effect* effect = *ci;

			std::stringstream ss;
			ss << effect->prop->head->getName();
			for (VAL::parameter_symbol_list::const_iterator vi = effect->prop->args->begin(); vi != effect->prop->args->end(); vi++) {			
				const VAL::parameter_symbol* var = *vi;
				ss << "_" << var->getName();
			}
			ss << "_0";

			(*out) << "(assert " << ss.str() << ")" << std::endl;
		}

		// assign effects
		for (VAL::pc_list<VAL::assignment*>::const_iterator ci = eff_list->assign_effects.begin(); ci != eff_list->assign_effects.end(); ci++) {
			const VAL::assignment* effect = *ci;

			std::stringstream ss;
			ss << effect->getFTerm()->getFunction()->getName();
			for (VAL::parameter_symbol_list::const_iterator vi = effect->getFTerm()->getArgs()->begin(); vi != effect->getFTerm()->getArgs()->end(); vi++) {			
				const VAL::parameter_symbol* var = *vi;
				ss << "_" << var->getName();
			}
			ss << "_0";

			(*out) << "(assert (= " << ss.str() << " " << parseExpression(effect->getExpr(),0) << "))" << std::endl;
		}
	}

	/**
	 * Constraints P2 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes the goal state
	 */
	void Encoder::encodeGoalState(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		VAL::goal* goal = problem->the_goal;
		(*out) << "(assert " << parseCondition(goal,h) << ")" << std::endl;
	}

	/*-------------------*/
	/* variable supports */
	/*-------------------*/

	/**
	 * Constraints H1--H6 & P5--P6 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes variable support for propositions and real values variables, in the form of explanatory frame axioms.
	 */
	void Encoder::encodeVariableSupport(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		if(h<1) return;

		// explanatory frame axioms
		for (int i=0; i<grounder.props.size(); i++) {
			(*out) << "(assert (=> "
					<< grounder.props[i].var_name << "_" << h
					<< grounder.props[i].var_name << "_" << (h-1)
					<< " ))" << std::endl;
		}

		// fixed numeric variables
		for (int i=0; i<grounder.fluents.size(); i++) {
			(*out) << "(assert (= "
					<< grounder.fluents[i].var_name << "_" << h
					<< grounder.fluents[i].var_name << "_" << (h-1)
					<< " ))" << std::endl;
		}
		
	}

	/*---------*/
	/* actions */
	/*---------*/

	/**
	 * Constraints H9 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes action support.
	 */
	void Encoder::encodeActionConditions(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		// actions
		VAL::operator_list* operators = domain->ops;
		for (VAL::operator_list::const_iterator ci = operators->begin(); ci != operators->end(); ci++) {

			

			std::string condition = parseTimedCondition()
			(*out) << "(assert (=> " << "sta_" << grounder.actions[i].var_name << "_" << h;
			
			(*out) << "(assert (=> " << "end_" << grounder.actions[i].var_name << "_" << h;
			(*out) << "(assert (=> " << "end_" << grounder.actions[i].var_name << "_" << h;

			(*out) << ")" << std::endl;
		}		

	}

	/**
	 * Constraints H10 (A Compilation of the Full PDDL+ Language into SMT)
	 * Enforces action effects.
	 */
	void Encoder::encodeActionEffects(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {
	}

	/**
	 * Constraints H16 (A Compilation of the Full PDDL+ Language into SMT)
	 * Enforces action mutual exclusion relations.
	 */
	void Encoder::encodeActionMutexes(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {
	}

	/*---------------------*/
	/* PDDL to SMT strings */
	/*---------------------*/

	/**
	 * parse an expression recursively.
	 */
	std::string Encoder::parseExpression(const VAL::expression* exp, int h) {

		std::stringstream ss;

		// number
		const VAL::num_expression* nex = dynamic_cast<const VAL::num_expression*>(exp);
		if (nex) {
			ss << nex->double_value();
			return ss.str();
		}

		// unit minus
		const VAL::uminus_expression* ume = dynamic_cast<const VAL::uminus_expression*>(exp);
		if (ume) {
			ss << "(- 0 " << parseExpression(ume->getExpr(),h) << ")";
			return ss.str();
		}

		// function
		const VAL::func_term* ft = dynamic_cast<const VAL::func_term*>(exp);
		if (ft) {
			ss << ft->getFunction()->getName();
			for (VAL::parameter_symbol_list::const_iterator vi = ft->getArgs()->begin(); vi != ft->getArgs()->end(); vi++) {			
				const VAL::parameter_symbol* var = *vi;
				ss << "_" << var->getName();
			}
			ss << "_" << h;
			return ss.str();
		}

		// binary expressions
		const VAL::binary_expression* be = dynamic_cast<const VAL::binary_expression*>(exp);
		if (be) {
			std::string lhs = parseExpression(be->getLHS(),h);
			std::string rhs = parseExpression(be->getRHS(),h);

			// plus
			const VAL::plus_expression* pe = dynamic_cast<const VAL::plus_expression*>(exp);
			if (pe) ss << "(+ ";

			// minus
			const VAL::minus_expression* mie = dynamic_cast<const VAL::minus_expression*>(exp);
			if (mie) ss << "- ";

			// multiply
			const VAL::mul_expression* mue = dynamic_cast<const VAL::mul_expression*>(exp);
			if (mue) ss << "* ";

			// divide
			const VAL::div_expression* de = dynamic_cast<const VAL::div_expression*>(exp);
			if (de) ss << "/ ";

			ss << lhs << " " << rhs << ")";
			return ss.str();
		}

		// "?duration"
		const VAL::special_val_expr* spe = dynamic_cast<const VAL::special_val_expr*>(exp);
		if (spe) {
			// duration, #t, or total time
		}

		return "PARSING_ERROR";
	}

	/**
	 * parse a condition recursively.
	 */
	std::string Encoder::parseCondition(const VAL::goal* goal, int h) {

		std::stringstream ss;
		
		// simple proposition (base case 1)
		const VAL::simple_goal* sg = dynamic_cast<const VAL::simple_goal*>(goal);
		if (sg) {
			const VAL::proposition* prop = sg->getProp();
			ss << prop->head->getName();
			for (VAL::parameter_symbol_list::const_iterator vi = prop->args->begin(); vi != prop->args->end(); vi++) {			
				const VAL::parameter_symbol* var = *vi;
				ss << "_" << var->getName();
			}
			ss << "_" << h;
			return ss.str();
		}

		// function inequality (base case 2)
		const VAL::comparison* co = dynamic_cast<const VAL::comparison*>(goal);
		if (co) {
			ss << "(";
			switch(co->getOp()) {
				case VAL::E_EQUALS: ss << "= "; break;
				case VAL::E_GREATER: ss << "> "; break;
				case VAL::E_GREATEQ: ss << ">= "; break;
				case VAL::E_LESS: ss << "< "; break;
				case VAL::E_LESSEQ: ss << ">= "; break;
			};
			ss << parseExpression(co->getLHS(),h) << " " << parseExpression(co->getRHS(),h) << ")";
			return ss.str();
		}

		// negative condition
		const VAL::neg_goal* ng = dynamic_cast<const VAL::neg_goal*>(goal);
		if (ng) {
			ss << "(not " << parseCondition(ng->getGoal(),h) << ")";
			return ss.str();
		}

		// conjunctive condition
		const VAL::conj_goal* cg = dynamic_cast<const VAL::conj_goal*>(goal);
		if (cg) {
			ss << "(and ";
		        const VAL::goal_list* goals = cg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				ss << " " << parseCondition((*ci),h);
			}
			ss << ")";
			return ss.str();
		}

		// disjunctive condition
		const VAL::disj_goal* dg = dynamic_cast<const VAL::disj_goal*>(goal);
		if (dg) {
			ss << "(or ";
		        const VAL::goal_list* goals = dg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				ss << " " << parseCondition((*ci),h);
			}
			ss << ")";
			return ss.str();
		}

		/*
		// timed condition
		const VAL::timed_goal* tg = dynamic_cast<const VAL::timed_goal*>(goal);
		if (tg) {
			switch(tg->getTime()) {
				case VAL::E_AT_START: time_spec = START; break;
				case VAL::E_AT_END: time_spec = END; break;
				case VAL::E_OVER_ALL: time_spec = ALL; break;
			};
			PDDLGDTimed pgdt(time_spec);
			PDDLGoalDescription inner = parseCondition(tg->getGoal());
			pgdt.goal_conditions.push_back(inner);
			return pgdt;
		}
		*/
		return "PARSING_ERROR";
	}

	/**
	 * parse a condition recursively, only retrieving a timed part
	 */
	std::string Encoder::parseTimedCondition(const VAL::goal* goal, VAL::time_spec part, int h) {

		std::stringstream ss;

		// conjunctive condition
		const VAL::conj_goal* cg = dynamic_cast<const VAL::conj_goal*>(goal);
		if (cg) {
			ss << "(and ";
		        const VAL::goal_list* goals = cg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				ss << " " << parseTimedCondition((*ci),part,h);
			}
			ss << ")";
			return ss.str();
		}

		// disjunctive condition
		const VAL::disj_goal* dg = dynamic_cast<const VAL::disj_goal*>(goal);
		if (dg) {
			ss << "(or ";
		        const VAL::goal_list* goals = dg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				ss << " " << parseTimedCondition((*ci),part,h);
			}
			ss << ")";
			return ss.str();
		}


		// timed condition
		const VAL::timed_goal* tg = dynamic_cast<const VAL::timed_goal*>(goal);
		if (tg) {
			if(tg->getTime() == part) {
				return parseCondition(tg->getGoal(),h);
			} else {
				return "";
			}
		}

		return "PARSING_ERROR";
	}

} // close namespace
