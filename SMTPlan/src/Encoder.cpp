#include "SMTPlan/Encoder.h"

/* implementation of SMTPlan::Encoder */
namespace SMTPlan {

		/* encoding state */
		int upper_bound;

		int enc_litID;
		int enc_pneID;
		int enc_opID;

		bool enc_cond_neg;
		bool enc_eff_neg;
		VAL::time_spec enc_cond_time;
		VAL::time_spec enc_eff_time;
		VAL::comparison_op enc_comparison_op;

	/**
	 * sets the output stream for writing to file/stdout
	 */
	void Encoder::setOutput(std::ostream &o) {
		out = &o;
	}

	/**
	 * attempt to solve the encoding
	 */
	z3::check_result Encoder::solve() {
		z3::check_result result = z3_solver->check();
		return result;
	}

	/**
	 * prints the current model if there is one
	 */
	void Encoder::printModel() {
		z3::model m = z3_solver->get_model();
		z3::expr t = z3_context->bool_val(true);
		z3::set_param("pp.decimal", true);
		//print plan
		for(int h=0; h<upper_bound; h++) {
			for(int a=0; a<Inst::instantiatedOp::howMany(); a++) {
				z3::expr v = m.eval(sta_action_vars[a][h]);
				if(eq(v,t)) std::cout << m.eval(time_vars[h]) << ":\t" << sta_action_vars[a][h] << " [" << m.eval(dur_action_vars[a][h]) << "]" << std::endl;
			}
		}
	}

	/**
	 * Main encode method
	 */
	bool Encoder::encode(VAL::analysis* analysis, PlannerOptions &options, ProblemInfo &pi, int H) {

		opt = &options;
		upper_bound = H;
		problem_info = &pi;
		const int pneCount = Inst::instantiatedOp::howManyPNEs();
		const int litCount = Inst::instantiatedOp::howManyLiterals();
		const int actCount = Inst::instantiatedOp::howMany();

		simpleStartAddEffects = std::vector<std::vector<int> >(litCount);
		simpleStartDelEffects = std::vector<std::vector<int> >(litCount);
		simpleEndAddEffects = std::vector<std::vector<int> >(litCount);
		simpleEndDelEffects = std::vector<std::vector<int> >(litCount);

		initialState = std::vector<bool>(litCount);

		pre_function_vars = std::vector<std::vector<z3::expr> >(pneCount);
		pos_function_vars = std::vector<std::vector<z3::expr> >(pneCount);
		pre_literal_vars = std::vector<std::vector<z3::expr> >(litCount);
		pos_literal_vars = std::vector<std::vector<z3::expr> >(litCount);
		sta_action_vars = std::vector<std::vector<z3::expr> >(actCount);
		end_action_vars = std::vector<std::vector<z3::expr> >(actCount);
		run_action_vars = std::vector<std::vector<z3::expr> >(actCount);
		dur_action_vars = std::vector<std::vector<z3::expr> >(actCount);

		z3::config cfg;
    	cfg.set("auto_config", true);
		z3_context = new z3::context(cfg);
		z3_solver = new z3::solver(*z3_context);

		// declare all variables
		encodeHeader(H);

		// timing constraints
		encodeTimings(H);

		// known states
		encodeInitialState(analysis);
		encodeGoalState(analysis, H);

		// action constraints
		Inst::OpStore::iterator opsItr = Inst::instantiatedOp::opsBegin();
		const Inst::OpStore::iterator opsEnd = Inst::instantiatedOp::opsEnd();
		for (; opsItr != opsEnd; ++opsItr) {
			Inst::instantiatedOp * const currOp = *opsItr;
		    enc_opID = currOp->getID();
			fe = currOp->getEnv();
			currOp->forOp()->visit(this);	
		}

		// literal constraints
		Inst::LiteralStore::iterator litItr = Inst::instantiatedOp::literalsBegin();
		const Inst::LiteralStore::iterator litEnd = Inst::instantiatedOp::literalsEnd();
		for (; litItr != litEnd; ++litItr) {
			Inst::Literal * const currLit = *litItr;
			if(problem_info->staticPredicateMap[currLit->getHead()->getName()]) continue;
		    enc_litID = currLit->getID();
			encodeLiteralVariableSupport(H);
		}

		// function constraints
		Inst::PNEStore::iterator pneItr = Inst::instantiatedOp::pnesBegin();
		const Inst::PNEStore::iterator pneEnd = Inst::instantiatedOp::pnesEnd();
		for(; pneItr != pneEnd; ++pneItr) {
			Inst::PNE * const currPNE = *pneItr;
			if(problem_info->staticFunctionMap[currPNE->getHead()->getName()]) continue;
		    enc_pneID = currPNE->getID();
			encodeFunctionVariableSupport(H);
		}
	}

	/*--------*/
	/* header */
	/*--------*/

	void Encoder::encodeHeader(int H) {

		// timings
		for(int h=0; h<H; h++) {
			std::stringstream ss1;
			ss1 << "t" << h;
			time_vars.push_back(z3_context->real_const(ss1.str().c_str()));
			std::stringstream ss2;
			ss2 << "d" << h;
			duration_vars.push_back(z3_context->real_const(ss2.str().c_str()));
		}

		// literals
		Inst::LiteralStore::iterator litItr = Inst::instantiatedOp::literalsBegin();
		const Inst::LiteralStore::iterator litEnd = Inst::instantiatedOp::literalsEnd();
		for (; litItr != litEnd; ++litItr) {
			Inst::Literal * const currLit = *litItr;

			simpleStartAddEffects[currLit->getID()];
			simpleStartDelEffects[currLit->getID()];
			simpleEndAddEffects[currLit->getID()];
			simpleEndDelEffects[currLit->getID()];

			pre_literal_vars[currLit->getID()];
			pos_literal_vars[currLit->getID()];

			for(int h=0; h<H; h++) {
				std::stringstream ss1;
				ss1 << (*currLit) << h << "_pre";
				pre_literal_vars[currLit->getID()].push_back(z3_context->bool_const(ss1.str().c_str()));
				std::stringstream ss2;
				ss2 << (*currLit) << h << "_pos";
				pos_literal_vars[currLit->getID()].push_back(z3_context->bool_const(ss2.str().c_str()));
			}
		}

		// functions
		Inst::PNEStore::iterator pneItr = Inst::instantiatedOp::pnesBegin();
		const Inst::PNEStore::iterator pneEnd = Inst::instantiatedOp::pnesEnd();
		for(; pneItr != pneEnd; ++pneItr) {
			Inst::PNE * const currPNE = *pneItr;

			pre_function_vars[currPNE->getID()];
			pos_function_vars[currPNE->getID()];

			for(int h=0; h<H; h++) {
				std::stringstream ss1;
				ss1 << (*currPNE) << h << "_pre";
				pre_function_vars[currPNE->getID()].push_back(z3_context->real_const(ss1.str().c_str()));
				std::stringstream ss2;
				ss2 << (*currPNE) << h << "_pos";
				pos_function_vars[currPNE->getID()].push_back(z3_context->real_const(ss2.str().c_str()));
			}
		}

		// actions
		Inst::OpStore::iterator opsItr = Inst::instantiatedOp::opsBegin();
		const Inst::OpStore::iterator opsEnd = Inst::instantiatedOp::opsEnd();
		for (; opsItr != opsEnd; ++opsItr) {
			Inst::instantiatedOp * const currOp = *opsItr;
		    const int operatorID = currOp->getID();

			sta_action_vars[operatorID];
			end_action_vars[operatorID];
			run_action_vars[operatorID];
			dur_action_vars[operatorID];

			for(int h=0; h<H; h++) {
				std::stringstream ss1;
				ss1 << (*currOp) << h << "_sta";
				sta_action_vars[operatorID].push_back(z3_context->bool_const(ss1.str().c_str()));
				std::stringstream ss2;
				ss2 << (*currOp) << h << "_end";
				end_action_vars[operatorID].push_back(z3_context->bool_const(ss2.str().c_str()));
				std::stringstream ss3;
				ss3 << (*currOp) << h << "_run";
				run_action_vars[operatorID].push_back(z3_context->bool_const(ss3.str().c_str()));
				std::stringstream ss4;
				ss4 << (*currOp) << h << "_dur";
				dur_action_vars[operatorID].push_back(z3_context->real_const(ss4.str().c_str()));
			}
		}
	}

	/*--------------*/
	/* known states */
	/*--------------*/

	/**
	 * Constraints P3--P4 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes the happening time constraints
	 */	
	void Encoder::encodeTimings(int H) {

		for(int h=0; h<H; h++) {
			if(h==0) {
				z3_solver->add(time_vars[h] == 0);
			} else {
				z3_solver->add(time_vars[h] == (time_vars[h-1] + duration_vars[h-1]));
				z3_solver->add(time_vars[h] > (time_vars[h-1]));
			}
			z3_solver->add(duration_vars[h] >= z3_context->real_val("1/10"));
		}
	}

	/**
	 * Constraints P1 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes the initial state
	 */
	void Encoder::encodeInitialState(VAL::analysis* analysis) {

		enc_state = ENC_INIT;
		VAL::effect_lists* eff_list = analysis->the_problem->initial_state;

		// simple add effects
		for (VAL::pc_list<VAL::simple_effect*>::const_iterator ci = eff_list->add_effects.begin(); ci != eff_list->add_effects.end(); ci++) {
			const VAL::simple_effect* effect = *ci;
			Inst::Literal * l = new Inst::Literal(effect->prop, fe);
			Inst::Literal * const lit = Inst::instantiatedOp::findLiteral(l);

			if(!problem_info->staticPredicateMap[lit->getHead()->getName()]) {
				z3_solver->add(pre_literal_vars[lit->getID()][0]);
			}

			initialState[lit->getID()] = true;
			delete l;
		}

		Inst::LiteralStore::iterator litItr = Inst::instantiatedOp::literalsBegin();
		const Inst::LiteralStore::iterator litEnd = Inst::instantiatedOp::literalsEnd();
		for (; litItr != litEnd; ++litItr) {
			Inst::Literal * const currLit = *litItr;
			if(problem_info->staticPredicateMap[currLit->getHead()->getName()])
				continue;
			if(!initialState[currLit->getID()]) {
				z3_solver->add(!pre_literal_vars[currLit->getID()][0]);
			}
		}

		// assign effects
		for (VAL::pc_list<VAL::assignment*>::const_iterator ci = eff_list->assign_effects.begin(); ci != eff_list->assign_effects.end(); ci++) {
			const VAL::assignment* effect = *ci;
			Inst::PNE * l = new Inst::PNE(effect->getFTerm(), fe);	
			Inst::PNE * const lit = Inst::instantiatedOp::findPNE(l);
			enc_pneID = lit->getID();
			enc_function_symbol = l->getHead()->getName();
			effect->getExpr()->visit(this);
			delete l;
		}

		enc_state = ENC_NONE;
	}

	/**
	 * Constraints P2 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes the goal state
	 */
	void Encoder::encodeGoalState(VAL::analysis* analysis, int H) {

		enc_state = ENC_GOAL;
		VAL::goal* goal = analysis->the_problem->the_goal;
		goal->visit(this);
		enc_state = ENC_NONE;
	}

	/*---------*/
	/* actions */
	/*---------*/

	/**
	 * Constraints H9-H10, H14-15, P7-P8 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes durative action constraints
	 */
	void Encoder::visit_durative_action(VAL::durative_action * da) {

		for(int h=0; h<upper_bound; h++) {
		
			// running action/process iff (remaining duration > 0)
			z3_solver->add(run_action_vars[enc_opID][h] == (dur_action_vars[enc_opID][h] > 0));
			z3_solver->add(!run_action_vars[enc_opID][h] == (dur_action_vars[enc_opID][h] == 0));

			// remaining duration (i) = remaining duration (i-1) - duration (i)
			if(h>0) {
				z3_solver->add(implies(run_action_vars[enc_opID][h-1],
						dur_action_vars[enc_opID][h] == (dur_action_vars[enc_opID][h-1] - duration_vars[h-1])));
			}

			// remaining duration = action duration
			z3_solver->add(implies(sta_action_vars[enc_opID][h], run_action_vars[enc_opID][h]));
			z3_solver->add(implies(end_action_vars[enc_opID][h], dur_action_vars[enc_opID][h] == 0));

			// start->run->end
			if(h>0) {
				z3_solver->add(implies(end_action_vars[enc_opID][h], run_action_vars[enc_opID][h-1]));
				z3_solver->add(implies(sta_action_vars[enc_opID][h], !run_action_vars[enc_opID][h-1]));
				z3_solver->add(implies(run_action_vars[enc_opID][h], run_action_vars[enc_opID][h-1] || sta_action_vars[enc_opID][h]));
				z3_solver->add(implies(!run_action_vars[enc_opID][h], !run_action_vars[enc_opID][h-1] || end_action_vars[enc_opID][h]));
			} else {
				z3_solver->add(!end_action_vars[enc_opID][h]);
				z3_solver->add(implies(run_action_vars[enc_opID][h], sta_action_vars[enc_opID][h]));
				z3_solver->add(implies(!run_action_vars[enc_opID][h], !sta_action_vars[enc_opID][h]));
			}
		}

		// duration
		enc_state = ENC_ACTION_DURATION;
		for(enc_expression_h=0; enc_expression_h<upper_bound; enc_expression_h++)
			da->dur_constraint->visit(this);

		// effects (sets up add/delete effect lists)
		enc_state = ENC_ACTION_EFFECT;
		da->effects->visit(this);

		// conditions (sets up mutex lists)
		enc_state = ENC_ACTION_CONDITION;
        if (da->precondition) da->precondition->visit(this);
		enc_state = ENC_NONE;
	}

	void Encoder::visit_action(VAL::action * o) {
		// currently only temporal actions
	}

	/*----------*/
	/* literals */
	/*----------*/

	/**
	 * Constraints H1--H4, P5-P6 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes variable support in the form of explanatory frame axioms.
	 */
	void Encoder::encodeLiteralVariableSupport(int H) {

		for(int h=0;h<H;h++) {

			// remain TRUE
			z3::expr_vector addargs(*z3_context);
			addargs.push_back(pre_literal_vars[enc_litID][h]);
			if(simpleStartAddEffects[enc_litID].size()>0 || simpleEndAddEffects[enc_litID].size()>0) {
				std::vector<int>::const_iterator iterator = simpleStartAddEffects[enc_litID].begin();
				for (; iterator != simpleStartAddEffects[enc_litID].end(); ++iterator) {
					addargs.push_back(sta_action_vars[(*iterator)][h]);
				}
				iterator = simpleEndAddEffects[enc_litID].begin();
				for (; iterator != simpleEndAddEffects[enc_litID].end(); ++iterator) {
					addargs.push_back(end_action_vars[(*iterator)][h]);
				}
			}
			z3_solver->add(implies(pos_literal_vars[enc_litID][h], mk_or(addargs)));


			// remain FALSE
			z3::expr_vector delargs(*z3_context);
			delargs.push_back(!pre_literal_vars[enc_litID][h]);
			if(simpleStartDelEffects[enc_litID].size()>0 || simpleEndDelEffects[enc_litID].size()>0) {
				std::vector<int>::const_iterator iterator = simpleStartDelEffects[enc_litID].begin();
				for (; iterator != simpleStartDelEffects[enc_litID].end(); ++iterator) {
					delargs.push_back(sta_action_vars[(*iterator)][h]);
				}
				iterator = simpleEndDelEffects[enc_litID].begin();
				for (; iterator != simpleEndDelEffects[enc_litID].end(); ++iterator) {
					delargs.push_back(end_action_vars[(*iterator)][h]);
				}
			}
			z3_solver->add(implies(!pos_literal_vars[enc_litID][h], mk_or(delargs)));

			// between happenings
			if(h<=0) continue;

			// remain TRUE and remain FALSE
			z3_solver->add(implies(pre_literal_vars[enc_litID][h], pos_literal_vars[enc_litID][h-1]));
			z3_solver->add(implies(!pre_literal_vars[enc_litID][h], !pos_literal_vars[enc_litID][h-1]));
		}
	}

	/**
	 * Constraints H5--H6, P5-P6 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes variable support in the form of explanatory frame axioms.
	 */
	void Encoder::encodeFunctionVariableSupport(int H) {

		for(int h=0;h<H;h++) {

			// remain
			z3_solver->add(pre_function_vars[enc_pneID][h] == pos_function_vars[enc_pneID][h]);

			// between happenings
			if(h<=0) continue;

			// remain
			z3_solver->add(pos_function_vars[enc_pneID][h] == pre_function_vars[enc_pneID][h-1]);
		}
	}

	/*-------*/
	/* goals */
	/*-------*/

	void Encoder::visit_conj_goal(VAL::conj_goal *c){
		c->getGoals()->visit(this);
	}

	void Encoder::visit_timed_goal(VAL::timed_goal *c){
		enc_cond_time = c->getTime();
        c->getGoal()->visit(this);
	}

	void Encoder::visit_neg_goal(VAL::neg_goal *c) {
		enc_cond_neg = !enc_cond_neg;
        c->getGoal()->visit(this);
		enc_cond_neg = !enc_cond_neg;
	}

	void Encoder::visit_simple_goal(VAL::simple_goal *c){
		Inst::Literal * l = new Inst::Literal(c->getProp(), fe);
		Inst::Literal * const lit = Inst::instantiatedOp::findLiteral(l);

		switch(enc_state) {

		case ENC_GOAL:
			if(enc_cond_neg) {
				z3_solver->add(!pos_literal_vars[lit->getID()][(upper_bound-1)]);
			} else {
				z3_solver->add(pos_literal_vars[lit->getID()][(upper_bound-1)]);
			}
			break;

		case ENC_ACTION_CONDITION:

			if(problem_info->staticPredicateMap[lit->getHead()->getName()]) {
				break;
			}

			for(int h=0;h<upper_bound;h++) {
				switch(enc_cond_time) {
				case VAL::E_AT_START:
					if(enc_cond_neg) {
						z3_solver->add(implies(sta_action_vars[enc_opID][h], !pre_literal_vars[lit->getID()][h]));
						// set up mutual exclusion
						std::vector<int>::const_iterator iterator = simpleStartAddEffects[lit->getID()].begin();
						for (; iterator != simpleStartAddEffects[lit->getID()].end(); ++iterator) {
							if((*iterator) == enc_opID) continue;
							z3_solver->add(!sta_action_vars[enc_opID][h] || !sta_action_vars[(*iterator)][h]);
						}
					} else {
						z3_solver->add(implies(sta_action_vars[enc_opID][h], pre_literal_vars[lit->getID()][h]));
						// set up mutual exclusion
						std::vector<int>::const_iterator iterator = simpleStartDelEffects[lit->getID()].begin();
						for (; iterator != simpleStartDelEffects[lit->getID()].end(); ++iterator) {
							if((*iterator) == enc_opID) continue;
							z3_solver->add(!sta_action_vars[enc_opID][h] || !sta_action_vars[(*iterator)][h]);
						}
					}
					break;
				case VAL::E_AT_END:
					if(enc_cond_neg) {
						z3_solver->add(implies(end_action_vars[enc_opID][h], !pre_literal_vars[lit->getID()][h]));
					} else {
						z3_solver->add(implies(end_action_vars[enc_opID][h], pre_literal_vars[lit->getID()][h]));
					}
					break;
				case VAL::E_OVER_ALL:
					if(enc_cond_neg) {
						z3_solver->add(implies(run_action_vars[enc_opID][h], !pre_literal_vars[lit->getID()][h]));
					} else {
						z3_solver->add(implies(run_action_vars[enc_opID][h], pre_literal_vars[lit->getID()][h]));
					}
					break;
				}
			}
			break;

		default:
			std::cerr << "Visit simple goal without correct state! (" << enc_state << ")" << std::endl;
			break;
		}

		delete l;
	}

	void Encoder::visit_comparison(VAL::comparison * c) {

		// generate SMT expression
		c->getLHS()->visit(this);
		c->getRHS()->visit(this);

		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();

		// generate SMT comparison
		z3::expr com = (lhs == rhs);
		switch(c->getOp()) {
		case VAL::E_GREATER: com = (lhs > rhs); break;
		case VAL::E_GREATEQ: com = (lhs >= rhs); break;
		case VAL::E_LESS: com = (lhs < rhs); break;
		case VAL::E_LESSEQ: com = (lhs <= rhs); break;
		case VAL::E_EQUALS: com = (lhs == rhs); break;
		}

		// encode planning constraint		
		switch(enc_state) {

		case ENC_GOAL:
			break;

		case ENC_ACTION_CONDITION:
			break;

		case ENC_ACTION_DURATION:
			z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], com));
			break;

		default:
			std::cerr << "Visit comparison without correct state! (" << enc_state << ")" << std::endl;
			break;
		}
	}

	void Encoder::visit_qfied_goal(VAL::qfied_goal *){}
	void Encoder::visit_disj_goal(VAL::disj_goal *){}
	void Encoder::visit_imply_goal(VAL::imply_goal *){}

	/*---------*/
	/* effects */
	/*---------*/

	void Encoder::visit_effect_lists(VAL::effect_lists * e) {
		e->add_effects.pc_list<VAL::simple_effect*>::visit(this);

		enc_eff_neg = true;
		e->del_effects.pc_list<VAL::simple_effect*>::visit(this);
		enc_eff_neg = false;

		e->forall_effects.pc_list<VAL::forall_effect*>::visit(this);
		e->cond_effects.pc_list<VAL::cond_effect*>::visit(this);
		e->timed_effects.pc_list<VAL::timed_effect*>::visit(this);
		e->assign_effects.pc_list<VAL::assignment*>::visit(this);
	}

	void Encoder::visit_timed_effect(VAL::timed_effect * e) {
		enc_eff_time = e->ts;
		e->effs->visit(this);
	};

	void Encoder::visit_forall_effect(VAL::forall_effect * e) {std::cout << "not implemented forall" << std::endl;};
	void Encoder::visit_cond_effect(VAL::cond_effect * e) {std::cout << "not implemented cond" << std::endl;};

	void Encoder::visit_simple_effect(VAL::simple_effect * e) {
		Inst::Literal * l = new Inst::Literal(e->prop, fe);
		Inst::Literal * const lit = Inst::instantiatedOp::findLiteral(l);

		if (!lit) return;

		switch(enc_state) {

		case ENC_ACTION_EFFECT:
			for(int h=0;h<upper_bound;h++) {
				switch(enc_eff_time) {
				case VAL::E_AT_START:
					if(enc_eff_neg) {
						z3_solver->add(implies(sta_action_vars[enc_opID][h], !pos_literal_vars[lit->getID()][h]));
						simpleStartDelEffects[lit->getID()].push_back(enc_opID);
					} else {
						z3_solver->add(implies(sta_action_vars[enc_opID][h], pos_literal_vars[lit->getID()][h]));
						simpleStartAddEffects[lit->getID()].push_back(enc_opID);
					}
					break;
				case VAL::E_AT_END:
					if(enc_eff_neg) {
						z3_solver->add(implies(end_action_vars[enc_opID][h], !pos_literal_vars[lit->getID()][h]));
						simpleEndDelEffects[lit->getID()].push_back(enc_opID);
					} else {
						z3_solver->add(implies(end_action_vars[enc_opID][h], pos_literal_vars[lit->getID()][h]));
						simpleEndAddEffects[lit->getID()].push_back(enc_opID);
					}
					break;
				}
			}
			break;

		default:
			std::cerr << "Visit effects without correct state! (" << enc_state << ")" << std::endl;
			break;
		}

		delete l;
	}

	/*-------------*/
	/* expressions */
	/*-------------*/

	void Encoder::parseExpression(VAL::expression * e) {
		e->visit(this);
	}

	void Encoder::visit_plus_expression(VAL::plus_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();

		enc_expression_stack.push_back(lhs + rhs);
	}

	void Encoder::visit_minus_expression(VAL::minus_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();

		enc_expression_stack.push_back(lhs - rhs);
	}

	void Encoder::visit_mul_expression(VAL::mul_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();

		enc_expression_stack.push_back(lhs * rhs);
	}

	void Encoder::visit_div_expression(VAL::div_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();

		enc_expression_stack.push_back(lhs / rhs);
	}

	void Encoder::visit_uminus_expression(VAL::uminus_expression * s) {

		s->getExpr()->visit(this);

		z3::expr exp = enc_expression_stack.back();
		enc_expression_stack.pop_back();

		enc_expression_stack.push_back(-exp);
	}

	void Encoder::visit_int_expression(VAL::int_expression * s) {

		std::stringstream ss;
		ss << s->double_value();
		z3::expr dv = z3_context->real_val(ss.str().c_str());
		enc_expression_stack.push_back(dv);
	}

	void Encoder::visit_float_expression(VAL::float_expression * s) {

		std::stringstream ss;
		ss << s->double_value();
		z3::expr dv = z3_context->real_val(ss.str().c_str());

		switch(enc_state) {
		
		case ENC_INIT:
			// initial state assignments
			if(problem_info->staticFunctionMap[enc_function_symbol]) {
				problem_info->staticFunctionValues[enc_pneID] = s->double_value();
			} else {
				z3_solver->add(pre_function_vars[enc_pneID][0] == dv);
			}
			break;

		case ENC_ACTION_DURATION:
		case ENC_ACTION_CONDITION:
			enc_expression_stack.push_back(dv);
			break;

		default:
			std::cerr << "Visit float expression without correct state! (" << enc_state << ")" << std::endl;
			break;
		}
	}

	void Encoder::visit_func_term(VAL::func_term * s) {
		Inst::PNE * l = new Inst::PNE(s, fe);
		Inst::PNE * const lit = Inst::instantiatedOp::findPNE(l);
		
		switch(enc_state) {

		case ENC_ACTION_DURATION:
		case ENC_ACTION_CONDITION:
			if(problem_info->staticFunctionMap[l->getHead()->getName()]) {
				std::stringstream ss;
				ss << problem_info->staticFunctionValues[lit->getID()];
				z3::expr dv = z3_context->real_val(ss.str().c_str());
				enc_expression_stack.push_back(dv);
			} else {
				enc_expression_stack.push_back(pre_function_vars[lit->getID()][enc_expression_h]);
			}
			break;

		case ENC_ACTION_EFFECT:
			enc_expression_stack.push_back(pos_function_vars[lit->getID()][enc_expression_h]);
			break;

		default:
			std::cerr << "Visit func_term expression without correct state! (" << enc_state << ")" << std::endl;
			break;
		}

		delete l;
	}

	void Encoder::visit_special_val_expr(VAL::special_val_expr * s) {

		switch(s->getKind()) {

		case VAL::E_DURATION_VAR:
			switch(enc_state) {

			case ENC_ACTION_DURATION:
			case ENC_ACTION_CONDITION:
				enc_expression_stack.push_back(dur_action_vars[enc_opID][enc_expression_h]);
				break;

			case ENC_ACTION_EFFECT:
				enc_expression_stack.push_back(dur_action_vars[enc_opID][enc_expression_h]);
				break;

			default:
				std::cerr << "Visit special_val expression without correct state! (" << enc_state << ")" << std::endl;
				break;
			}
			break;

		case VAL::E_HASHT:
		case VAL::E_TOTAL_TIME:
			break;
		}
	}

	/*-------*/
	/* extra */
	/*-------*/

	void Encoder::visit_timed_initial_literal(VAL::timed_initial_literal * til) {};
	void Encoder::visit_preference(VAL::preference *){}
	void Encoder::visit_event(VAL::event * e){}
    void Encoder::visit_process(VAL::process * p){}
	void Encoder::visit_derivation_rule(VAL::derivation_rule * o){}

} // close namespace
