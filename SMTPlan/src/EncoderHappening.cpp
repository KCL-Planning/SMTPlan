#include "SMTPlan/EncoderHappening.h"

/* implementation of SMTPlan::EncoderHappening */
namespace SMTPlan {


	/**
	 * attempt to solve the encoding
	 */
	z3::check_result EncoderHappening::solve() {
		z3::check_result result = z3_solver->check(goal_expression.size(), &(*goal_expression.begin()));
		return result;
	}

	/**
	 * prints the current model if there is one
	 */
	void EncoderHappening::printModel() {
		z3::model m = z3_solver->get_model();
		z3::expr t = z3_context->bool_val(true);
		z3::set_param("pp.decimal", true);
		//print plan
		for(int h=0; h<upper_bound; h++) {

			std::vector<int>::iterator ait = action_ids.begin();
			for(; ait != action_ids.end(); ait++) {
				z3::expr v = m.eval(sta_action_vars[*ait][h]);

				if(eq(v,t))	{
					// time
					std::cout << m.eval(time_vars[h]) << ":\t";
					// action
					std::stringstream ss;
					ss << sta_action_vars[*ait][h];
					std::string a = ss.str();
					std::cout << a.substr(a.find("("), a.find(")")-a.find("(")+1);
					// duration
					std::cout << " [" << m.eval(dur_action_vars[*ait][h]) << "]" << std::endl;
				}
			}

			if(opt->debug) {

				//events
				std::map<int, std::vector<std::vector<z3::expr>>>::iterator eit = event_vars.begin();
				for(; eit != event_vars.end(); eit++) {
					for(int b=0; b<opt->cascade_bound-1; b++) {
						z3::expr v = m.eval(eit->second[h][b]);
						if(eq(v,t)) {
							std::cout << m.eval(time_vars[h]) << ":\t" << eit->second[h][b] << " [0.0]" << std::endl;
						}
					}
				}

				// run
				ait = action_ids.begin();
				for(; ait != action_ids.end(); ait++) {
					//if(run_action_vars.find(*ait)==run_action_vars.end()) continue;
					z3::expr v = m.eval(run_action_vars[*ait][h]);
					if(eq(v,t))	std::cout << m.eval(time_vars[h]) << ":\t" << run_action_vars[*ait][h] << "\t(running)" << std::endl;
				}

				// end
				ait = action_ids.begin();
				for(; ait != action_ids.end(); ait++) {
					if(end_action_vars.find(*ait)==end_action_vars.end()) continue;
					z3::expr v = m.eval(end_action_vars[*ait][h]);
					if(eq(v,t))	std::cout << m.eval(time_vars[h]) << ":\t" << end_action_vars[*ait][h] << "\t(end)" << std::endl;
				}

				std::vector<std::vector<std::vector<z3::expr> > >::iterator lit = event_cascade_literal_vars.begin();
				for(; lit != event_cascade_literal_vars.end(); lit++) {
					for(int b=0; b<opt->cascade_bound; b++) {
						z3::expr v = m.eval((*lit)[h][b]);
						if(eq(v,t)) std::cout << m.eval(time_vars[h]) << ":\t" << (*lit)[h][b] << std::endl;
					}
				}

				std::vector<std::vector<std::vector<z3::expr> > >::iterator fit = event_cascade_function_vars.begin();
				for(; fit != event_cascade_function_vars.end(); fit++) {
					for(int b=0; b<opt->cascade_bound; b++) {
						std::cout << m.eval(time_vars[h]) << ":\t" << (*fit)[h][b] << " == " << m.eval((*fit)[h][b]) << std::endl;
					}
				}
			}
		}
		if(opt->debug) std::cout << "Goal at " << "[" << m.eval(time_vars[upper_bound-1]) << "]" << std::endl;
	}

	/**
	 * Main encode method
	 */
	bool EncoderHappening::encode(int H) {

		upper_bound = H;

		// declare all variables
		encodeHeader(H);

		// timing constraints
		encodeTimings(H);

		// known states
		encodeInitialState();
		encodeGoalState(H);

		// action constraints
		enc_make_op_vars = true;
		Inst::OpStore::iterator opsItr = Inst::instantiatedOp::opsBegin();
		Inst::OpStore::iterator opsEnd = Inst::instantiatedOp::opsEnd();
		for (; opsItr != opsEnd; ++opsItr) {
			Inst::instantiatedOp * const currOp = *opsItr;
		    enc_opID = currOp->getID();
			std::stringstream ss;
			ss << (*currOp);
			enc_op_string = ss.str();
			fe = currOp->getEnv();
			currOp->forOp()->visit(this);
		}

		enc_make_op_vars = false;
		opsItr = Inst::instantiatedOp::opsBegin();
		opsEnd = Inst::instantiatedOp::opsEnd();
		for (; opsItr != opsEnd; ++opsItr) {
			Inst::instantiatedOp * const currOp = *opsItr;
		    enc_opID = currOp->getID();
			std::stringstream ss;
			ss << (*currOp);
			enc_op_string = ss.str();
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
			encodeFunctionFlows(H);
		}
		next_layer = upper_bound;

	}

	/*--------*/
	/* header */
	/*--------*/

	void EncoderHappening::encodeHeader(int H) {

		// timings
		for(int h=next_layer; h<H; h++) {
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

			if(next_layer == 0) {
				simpleStartAddEffects[currLit->getID()];
				simpleStartDelEffects[currLit->getID()];
				simpleEventAddEffects[currLit->getID()];
				simpleEventDelEffects[currLit->getID()];
				simpleEndAddEffects[currLit->getID()];
				simpleEndDelEffects[currLit->getID()];
				simpleTILAddEffects[currLit->getID()];
				simpleTILDelEffects[currLit->getID()];

				event_cascade_literal_vars[currLit->getID()];
			}

			for(int h=next_layer; h<H; h++) {
				std::vector<z3::expr> literalVars;
				for(int b=0; b<opt->cascade_bound; b++) {
					std::stringstream ss;
					ss << (*currLit) << h << "_" << b;
					literalVars.push_back(z3_context->bool_const(ss.str().c_str()));
				}
				event_cascade_literal_vars[currLit->getID()].push_back(literalVars);
			}
		}

		// functions
		Inst::PNEStore::iterator pneItr = Inst::instantiatedOp::pnesBegin();
		const Inst::PNEStore::iterator pneEnd = Inst::instantiatedOp::pnesEnd();
		for(; pneItr != pneEnd; ++pneItr) {
			Inst::PNE * const currPNE = *pneItr;

			if(next_layer == 0) {
				event_cascade_literal_vars[currPNE->getID()];
			}

			for(int h=next_layer; h<H; h++) {
				std::vector<z3::expr> functionVars;
				for(int b=0; b<opt->cascade_bound; b++) {
					std::stringstream ss;
					ss << (*currPNE) << h << "_" << b;
					functionVars.push_back(z3_context->real_const(ss.str().c_str()));
				}
				event_cascade_function_vars[currPNE->getID()].push_back(functionVars);
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
	void EncoderHappening::encodeTimings(int H) {

		for(int h=next_layer; h<H; h++) {
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
	void EncoderHappening::encodeInitialState() {

		enc_state = ENC_INIT;
		VAL::effect_lists* eff_list = val_analysis->the_problem->initial_state;

		// TILS
		enc_tilID = 0;
		for (VAL::pc_list<VAL::timed_effect*>::const_iterator ci = eff_list->timed_effects.begin(); ci != eff_list->timed_effects.end(); ci++) {
			const VAL::timed_effect* effect = *ci;
			effect->visit(this);
			enc_tilID++;
		}

		if(next_layer == 0)	{

			// simple add effects
			for (VAL::pc_list<VAL::simple_effect*>::const_iterator ci = eff_list->add_effects.begin(); ci != eff_list->add_effects.end(); ci++) {
				const VAL::simple_effect* effect = *ci;
				Inst::Literal * l = new Inst::Literal(effect->prop, fe);
				Inst::Literal * const lit = Inst::instantiatedOp::findLiteral(l);

				if(!problem_info->staticPredicateMap[lit->getHead()->getName()]) {
					z3_solver->add(event_cascade_literal_vars[lit->getID()][0][0]);
				}
				if (initialState.size() <= lit->getID()) std::cout << initialState.size() << " AND " << lit->getID() << std::endl;
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
					z3_solver->add(!event_cascade_literal_vars[currLit->getID()][0][0]);
				}
			}

			initialState.clear();

			// assign effects
			for (VAL::pc_list<VAL::assignment*>::const_iterator ci = eff_list->assign_effects.begin(); ci != eff_list->assign_effects.end(); ci++) {
				const VAL::assignment* effect = *ci;
				Inst::PNE * l = new Inst::PNE(effect->getFTerm(), fe);	
				Inst::PNE * const lit = Inst::instantiatedOp::findPNE(l);

				enc_pneID = lit->getID();
				enc_function_symbol = l->getHead()->getName();

				enc_expression_h = 0;
				enc_expression_b = 0;
				effect->getExpr()->visit(this);
				z3::expr expr = enc_expression_stack.back();
				enc_expression_stack.pop_back();

				if(problem_info->staticFunctionMap[lit->getHead()->getName()]) {
					problem_info->staticFunctionValues.insert(std::make_pair(enc_pneID,expr));
				} else {
					z3_solver->add(event_cascade_function_vars[enc_pneID][0][0] == expr);
				}
				delete l;
			}
		}

		enc_state = ENC_NONE;
	}

	/**
	 * Constraints P2 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes the goal state
	 */
	void EncoderHappening::encodeGoalState(int H) {

		enc_state = ENC_GOAL;
		enc_expression_b = opt->cascade_bound-1;
		enc_expression_h = upper_bound-1;
		goal_expression.clear();

		VAL::goal* goal = val_analysis->the_problem->the_goal;
		goal->visit(this);
		enc_state = ENC_NONE;
	}

	/*------*/
	/* TILS */
	/*------*/

	void EncoderHappening::visit_timed_initial_literal(VAL::timed_initial_literal * til) {

		til_vars[enc_tilID];

		for(int h=next_layer; h<upper_bound; h++) {

			// MAKE VARS
			std::stringstream ss;
			ss << "til_" << enc_tilID << "_" << h;
			til_vars[enc_tilID].push_back(z3_context->bool_const(ss.str().c_str()));
			ss.str("");

			ss << til->time_stamp;
			z3::expr time_value = z3_context->real_val(ss.str().c_str());

			// true iff at time
			z3_solver->add(
					((time_vars[h] <= time_value) && (time_vars[h] >= time_value))
					 == til_vars[enc_tilID][h]
					);

			// TIL cannot be skipped
			if(h>0) {
				z3_solver->add( (time_vars[h] - time_value) * (time_vars[h-1] - time_value) >= 0);
			}

			// effects
			enc_state = ENC_TIL_EFFECT;
			enc_expression_b = 0;
			enc_expression_h = h;
			til->effs->visit(this);
			enc_state = ENC_NONE;
		}
	};

	/*---------*/
	/* actions */
	/*---------*/

	/**
	 * Constraints H9-H10, H14-15, P7-P8 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes durative action constraints
	 */
	void EncoderHappening::visit_durative_action(VAL::durative_action * da) {

		if(enc_make_op_vars)
		{
			sta_action_vars[enc_opID];
			run_action_vars[enc_opID];
			end_action_vars[enc_opID];
			dur_action_vars[enc_opID];

			// remember which operators are actions and not processes
			if(next_layer==0) {
				action_ids.push_back(enc_opID);
			}

			for(int h=next_layer; h<upper_bound; h++) {

				// MAKE VARS
				std::stringstream ss;
				ss << enc_op_string << h << "_sta";
				sta_action_vars[enc_opID].push_back(z3_context->bool_const(ss.str().c_str()));
				ss.str("");
				ss << enc_op_string << h << "_end";
				end_action_vars[enc_opID].push_back(z3_context->bool_const(ss.str().c_str()));
				ss.str("");
				ss << enc_op_string << h << "_run";
				run_action_vars[enc_opID].push_back(z3_context->bool_const(ss.str().c_str()));
				ss.str("");
				ss << enc_op_string << h << "_dur";
				dur_action_vars[enc_opID].push_back(z3_context->real_const(ss.str().c_str()));
		
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

		}
		else
		{
			enc_expression_b = opt->cascade_bound - 2;
			for(enc_expression_h=next_layer; enc_expression_h<upper_bound; enc_expression_h++) {

				// duration
				enc_state = ENC_ACTION_DURATION;
				da->dur_constraint->visit(this);

				// effects (sets up add/delete effect lists)
				enc_state = ENC_ACTION_EFFECT;
				da->effects->visit(this);

				// conditions (sets up mutex lists)
				enc_state = ENC_ACTION_CONDITION;
			   	if (da->precondition) da->precondition->visit(this);

				enc_state = ENC_NONE;
			}

			goal_expression.push_back(!run_action_vars[enc_opID][upper_bound-1]);
		}
	}

	void EncoderHappening::visit_action(VAL::action * o) {

		if(enc_make_op_vars)
		{
			sta_action_vars[enc_opID];
			dur_action_vars[enc_opID];

			// remember which operators are actions and not processes
			if(next_layer==0) {
				action_ids.push_back(enc_opID);
			}

			for(int h=next_layer; h<upper_bound; h++) {
			
				// MAKE VARS
				std::stringstream ss;
				ss << enc_op_string << h << "_sta";
				sta_action_vars[enc_opID].push_back(z3_context->bool_const(ss.str().c_str()));
				ss.str("");
				ss << enc_op_string << h << "_dur";
				dur_action_vars[enc_opID].push_back(z3_context->real_const(ss.str().c_str()));

				// (duration == 0)
				z3_solver->add(dur_action_vars[enc_opID][h] == 0);
			}
		}
		else
		{

			enc_expression_b = opt->cascade_bound - 2;
			for(enc_expression_h=next_layer; enc_expression_h<upper_bound; enc_expression_h++) {

				enc_eff_time = VAL::E_AT_START;

				// effects (sets up add/delete effect lists)
				enc_state = ENC_SIMPLE_ACTION_EFFECT;
				o->effects->visit(this);

				// conditions (sets up mutex lists)
				enc_state = ENC_SIMPLE_ACTION_CONDITION;
			   	if (o->precondition) o->precondition->visit(this);

				enc_state = ENC_NONE;
			}
		}
	}

	/*--------*/
	/* events */
	/*--------*/

	void EncoderHappening::visit_event(VAL::event * e){

		if(enc_make_op_vars)
		{
			event_vars[enc_opID];

			for(int h=next_layer; h<upper_bound; h++) {
				// MAKE VARS
				std::vector<z3::expr> eventVars;
				for(enc_expression_b=0; enc_expression_b<opt->cascade_bound-1; enc_expression_b++) {
					std::stringstream ss;
					ss << enc_op_string << h << "_" << enc_expression_b;
					eventVars.push_back(z3_context->bool_const(ss.str().c_str()));
				}
				event_vars[enc_opID].push_back(eventVars);
			}
		}
		else
		{
			for(enc_expression_h=next_layer; enc_expression_h<upper_bound; enc_expression_h++) {

				enc_eff_time = VAL::E_AT_START;

				// conditions (sets up mutex lists)
				for(enc_expression_b=0; enc_expression_b<opt->cascade_bound-1; enc_expression_b++) {

					// effects (sets up add/delete effect lists)
					enc_state = ENC_EVENT_EFFECT;
					e->effects->visit(this);

					enc_state = ENC_EVENT_CONDITION;
					enc_event_condition_stack = new z3::expr_vector(*z3_context);
					enc_musts_expression_stack.clear();
					enc_musts_discrete_stack.clear();

					// make event trigger and save parts of MUST condition
				   	if (e->precondition) e->precondition->visit(this);
					z3_solver->add(event_vars[enc_opID][enc_expression_h][enc_expression_b] == mk_and(*enc_event_condition_stack));

					if(enc_expression_b == 0 && enc_expression_h > 0) {

						// make rest of must condition
						std::vector<z3::expr> current;
						current.insert(current.begin(), enc_musts_expression_stack.begin(), enc_musts_expression_stack.end());
						enc_expression_h--;
						enc_expression_b = opt->cascade_bound - 1;
						enc_musts_expression_stack.clear();
						enc_musts_discrete_stack.clear();
					   	if (e->precondition) e->precondition->visit(this);
						enc_expression_h++;
						enc_expression_b = 0;

						// create boundary equations
						z3::expr_vector mustConstraints(*z3_context);
						while(enc_musts_expression_stack.size() > 0) {
							mustConstraints.push_back(current.back() * enc_musts_expression_stack.back() >= 0);
							enc_musts_expression_stack.pop_back();
							current.pop_back();
						}

						/*/ add negative discrete conditions
						while(enc_musts_discrete_stack.size() > 0) {
							mustConstraints.push_back(enc_musts_discrete_stack.back());
							enc_musts_discrete_stack.pop_back();
						}*/

						// declare must condition
						z3_solver->add(mk_and(mustConstraints));
					}
					delete enc_event_condition_stack;				
				}

				enc_state = ENC_NONE;
			}
		}
	}

	/*-----------*/
	/* processes */
	/*-----------*/

    void EncoderHappening::visit_process(VAL::process * p){

		if(enc_make_op_vars)
		{
			sta_action_vars[enc_opID];
			run_action_vars[enc_opID];
			end_action_vars[enc_opID];
			dur_action_vars[enc_opID];

			for(int h=next_layer; h<upper_bound; h++) {
			
				// MAKE VARS
				std::stringstream ss;
				ss << enc_op_string << h << "_sta";
				sta_action_vars[enc_opID].push_back(z3_context->bool_const(ss.str().c_str()));
				ss.str("");
				ss << enc_op_string << h << "_end";
				end_action_vars[enc_opID].push_back(z3_context->bool_const(ss.str().c_str()));
				ss.str("");
				ss << enc_op_string << h << "_run";
				run_action_vars[enc_opID].push_back(z3_context->bool_const(ss.str().c_str()));
				ss.str("");
				ss << enc_op_string << h << "_dur";
				dur_action_vars[enc_opID].push_back(z3_context->real_const(ss.str().c_str()));
		
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
					z3_solver->add(implies(sta_action_vars[enc_opID][h], run_action_vars[enc_opID][h]));
					z3_solver->add(implies(sta_action_vars[enc_opID][h], !run_action_vars[enc_opID][h-1]));
					z3_solver->add(implies(run_action_vars[enc_opID][h], run_action_vars[enc_opID][h-1] || sta_action_vars[enc_opID][h]));
					z3_solver->add(implies(!run_action_vars[enc_opID][h], !run_action_vars[enc_opID][h-1] || end_action_vars[enc_opID][h]));
				} else {
					z3_solver->add(!end_action_vars[enc_opID][h]);
					z3_solver->add(implies(run_action_vars[enc_opID][h], sta_action_vars[enc_opID][h]));
					z3_solver->add(implies(sta_action_vars[enc_opID][h], run_action_vars[enc_opID][h]));
					z3_solver->add(implies(!run_action_vars[enc_opID][h], !sta_action_vars[enc_opID][h]));
				}
			}
		}
		else
		{
			enc_expression_b = opt->cascade_bound - 1;
			for(enc_expression_h=next_layer; enc_expression_h<upper_bound; enc_expression_h++) {

				// effects (sets up add/delete effect lists)
				enc_state = ENC_ACTION_EFFECT;
				p->effects->visit(this);

				// conditions (sets up mutex lists)
				enc_state = ENC_PROCESS_CONDITION;
				enc_event_condition_stack = new z3::expr_vector(*z3_context);
				enc_musts_expression_stack.clear();
				enc_musts_discrete_stack.clear();

				// make process trigger
			   	if (p->precondition) p->precondition->visit(this);

				z3_solver->add( run_action_vars[enc_opID][enc_expression_h] == mk_and(*enc_event_condition_stack) );

				if(enc_expression_h > 0) {

					// fetch half of the must conditions
					enc_musts_expression_stack.clear();
					enc_musts_discrete_stack.clear();
					enc_expression_b = 0;
				   	if (p->precondition) p->precondition->visit(this);
					enc_expression_b = opt->cascade_bound - 1;

					// make rest of must condition
					std::vector<z3::expr> current;
					current.insert(current.begin(), enc_musts_expression_stack.begin(), enc_musts_expression_stack.end());
					enc_expression_h--;
					enc_musts_expression_stack.clear();
					enc_musts_discrete_stack.clear();
				   	if (p->precondition) p->precondition->visit(this);
					enc_expression_h++;

					// create boundary equations
					z3::expr_vector mustConstraints(*z3_context);
					while(enc_musts_expression_stack.size() > 0) {
						mustConstraints.push_back(current.back() * enc_musts_expression_stack.back() >= 0);
						enc_musts_expression_stack.pop_back();
						current.pop_back();
					}
					while(mustConstraints.size() > 0) {
						z3_solver->add(implies(run_action_vars[enc_opID][enc_expression_h-1], mustConstraints.back()));
						mustConstraints.pop_back();
					}
				}
				delete enc_event_condition_stack;				
				enc_state = ENC_NONE;
			}
		}
	}

	/*----------*/
	/* literals */
	/*----------*/

	/**
	 * Constraints H1--H4, P5-P6 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes variable support in the form of explanatory frame axioms.
	 */
	void EncoderHappening::encodeLiteralVariableSupport(int H) {

		for(int h=next_layer;h<H;h++) {

			for(int b=1;b<opt->cascade_bound;b++) {

				// remain TRUE
				z3::expr_vector addargs(*z3_context);
				addargs.push_back(event_cascade_literal_vars[enc_litID][h][b-1]);

				// event enablers
				if(simpleEventAddEffects[enc_litID].size()>0) {
					std::vector<int>::const_iterator iterator = simpleEventAddEffects[enc_litID].begin();
					for (; iterator != simpleEventAddEffects[enc_litID].end(); ++iterator) {
						addargs.push_back(event_vars[(*iterator)][h][b-1]);
					}
				}

				// action enablers
				if(b == opt->cascade_bound - 1) {
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
				}
				z3_solver->add(implies(event_cascade_literal_vars[enc_litID][h][b], mk_or(addargs)));


				// remain FALSE
				z3::expr_vector delargs(*z3_context);
				delargs.push_back(!event_cascade_literal_vars[enc_litID][h][b-1]);

				// event disablers
				if(simpleEventDelEffects[enc_litID].size()>0) {
					std::vector<int>::const_iterator iterator = simpleEventDelEffects[enc_litID].begin();
					for (; iterator != simpleEventDelEffects[enc_litID].end(); ++iterator) {
						delargs.push_back(event_vars[(*iterator)][h][b-1]);
					}
				}

				// action disablers
				if(b == opt->cascade_bound - 1) {
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
				}
				z3_solver->add(implies(!event_cascade_literal_vars[enc_litID][h][b], mk_or(delargs)));
			}

			// between happenings
			if(h<=0) continue;

			z3::expr_vector addargs(*z3_context);
			addargs.push_back(event_cascade_literal_vars[enc_litID][h-1][opt->cascade_bound-1]);

			// TIL enablers
			if(simpleTILAddEffects[enc_litID].size()>0) {
				std::vector<int>::const_iterator iterator = simpleTILAddEffects[enc_litID].begin();
				for (; iterator != simpleTILAddEffects[enc_litID].end(); ++iterator) {
					addargs.push_back(til_vars[(*iterator)][h]);
				}
			}

			// become/remain TRUE
			z3_solver->add(implies( event_cascade_literal_vars[enc_litID][h][0], mk_or(addargs) ));

			z3::expr_vector delargs(*z3_context);
			delargs.push_back(!event_cascade_literal_vars[enc_litID][h-1][opt->cascade_bound-1]);

			// TIL disablers
			if(simpleTILDelEffects[enc_litID].size()>0) {
				std::vector<int>::const_iterator iterator = simpleTILDelEffects[enc_litID].begin();
				for (; iterator != simpleTILDelEffects[enc_litID].end(); ++iterator) {
					delargs.push_back(til_vars[(*iterator)][h]);
				}
			}

			// become/remain FALSE
			z3_solver->add(implies( !event_cascade_literal_vars[enc_litID][h][0], mk_or(delargs) ));
		}
	}

	/**
	 * Constraints H5--H6, P5-P6 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes variable support in the form of explanatory frame axioms.
	 */
	void EncoderHappening::encodeFunctionVariableSupport(int H) {

		for(int h=next_layer;h<H;h++) {

			for(int b=1;b<opt->cascade_bound;b++) {

				// remain or assign
				z3::expr_vector chargs(*z3_context);

				// event assigners
				if(simpleEventAssignEffects[enc_pneID].size()>0) {
					std::vector<std::pair<int, z3::expr> >::const_iterator iterator = simpleEventAssignEffects[enc_pneID].begin();
					for (; iterator != simpleEventAssignEffects[enc_pneID].end(); ++iterator) {
						chargs.push_back(event_vars[iterator->first][h][b-1]);
					}
				}

				// action assigners
				if(b == opt->cascade_bound - 1) {
					if(simpleStartAssignEffects[enc_pneID].size()>0 || simpleEndAssignEffects[enc_pneID].size()>0) {
						std::vector<std::pair<int, z3::expr> >::const_iterator iterator = simpleStartAssignEffects[enc_pneID].begin();
						for (; iterator != simpleStartAssignEffects[enc_pneID].end(); ++iterator) {
							chargs.push_back(sta_action_vars[iterator->first][h]);
						}
						iterator = simpleEndAssignEffects[enc_pneID].begin();
						for (; iterator != simpleEndAssignEffects[enc_pneID].end(); ++iterator) {
							chargs.push_back(end_action_vars[iterator->first][h]);
						}
					}
				}
				chargs.push_back(event_cascade_function_vars[enc_pneID][h][b-1] == event_cascade_function_vars[enc_pneID][h][b]);
				z3_solver->add(mk_or(chargs));
			}
		}
	}

	/**
	 */
	void EncoderHappening::encodeFunctionFlows(int H) {

		FunctionFlow * flow = algebraist->function_flow[enc_pneID];

		for(int h=next_layer;h<H;h++) {

			// between happenings
			if(h<=0) continue;

			// !continuous => (function_{i+1} == function_i) unless TILS
			if(!flow || flow->flows.empty()) {

				// remain or assign
				z3::expr_vector chargs(*z3_context);
				chargs.push_back(event_cascade_function_vars[enc_pneID][h][0] == event_cascade_function_vars[enc_pneID][h-1][opt->cascade_bound-1]);

				// TIL assigners
				if(simpleTILAssignEffects[enc_pneID].size()>0) {
					std::vector<std::pair<int, z3::expr> >::const_iterator iterator = simpleTILAssignEffects[enc_pneID].begin();
					for (; iterator != simpleTILAssignEffects[enc_pneID].end(); ++iterator) {
						chargs.push_back(til_vars[iterator->first][h]);
					}
				}

				z3_solver->add(mk_or(chargs));
				continue;
			}

			// TIL assigners
			z3::expr_vector til_chargs(*z3_context);
			til_chargs.push_back(z3_context->bool_val(true));
			if(simpleTILAssignEffects[enc_pneID].size()>0) {
				std::vector<std::pair<int, z3::expr> >::const_iterator iterator = simpleTILAssignEffects[enc_pneID].begin();
				for (; iterator != simpleTILAssignEffects[enc_pneID].end(); ++iterator) {
					til_chargs.push_back(!til_vars[iterator->first][h]);
				}
			}

			bool nchargsSet = false;
			z3::expr_vector nchargs(*z3_context);
			std::vector<SingleFlow>::iterator fit = flow->flows.begin();
			for(; fit != flow->flows.end(); fit++) {

				// conjunction of operators
				z3::expr_vector chargs(*z3_context);
				std::set<int>::const_iterator iit = fit->operators.begin();
				for (; iit != fit->operators.end(); ++iit) {
					if(*iit < 0) {
						chargs.push_back(!run_action_vars[-1*(*iit)-1][h-1]);
						if(!nchargsSet) nchargs.push_back(!run_action_vars[-1*(*iit)-1][h-1]);
					} else {
						chargs.push_back(run_action_vars[(*iit)-1][h-1]);
						if(!nchargsSet) nchargs.push_back(!run_action_vars[(*iit)-1][h-1]);
					}
				}

				// !conjunction_operators => (function_{i+1} == function_i)
				if(!nchargsSet) {
					z3_solver->add(implies( mk_and(nchargs) && mk_and(til_chargs), (event_cascade_function_vars[enc_pneID][h][0] == event_cascade_function_vars[enc_pneID][h-1][opt->cascade_bound-1])));
					nchargsSet = true;
				}

				//conjunction_operators => (function_{i+1} == function_i + flow_i)
				z3_solver->add(implies( mk_and(chargs) && mk_and(til_chargs), event_cascade_function_vars[enc_pneID][h][0] == mk_expr(fit->polynomial, h-1, opt->cascade_bound-1)));
			}

		}
	}

	/*-------*/
	/* goals */
	/*-------*/

	void EncoderHappening::visit_conj_goal(VAL::conj_goal *c){
		c->getGoals()->visit(this);
	}

	void EncoderHappening::visit_timed_goal(VAL::timed_goal *c){
		enc_cond_time = c->getTime();
        c->getGoal()->visit(this);
	}

	void EncoderHappening::visit_neg_goal(VAL::neg_goal *c) {
		enc_cond_neg = !enc_cond_neg;
        c->getGoal()->visit(this);
		enc_cond_neg = !enc_cond_neg;
	}

	void EncoderHappening::visit_simple_goal(VAL::simple_goal *c){

		Inst::Literal * l = new Inst::Literal(c->getProp(), fe);
		Inst::Literal * const lit = Inst::instantiatedOp::findLiteral(l);

		if(!lit) {
			if(enc_state == ENC_GOAL) goal_expression.push_back(z3_context->bool_val(false));
			return;
		}

		switch(enc_state) {

		case ENC_GOAL:
			if(enc_cond_neg) {
				goal_expression.push_back(!event_cascade_literal_vars[lit->getID()][(upper_bound-1)][opt->cascade_bound-1]);
			} else {
				goal_expression.push_back(event_cascade_literal_vars[lit->getID()][(upper_bound-1)][opt->cascade_bound-1]);
			}
			break;

		case ENC_EVENT_CONDITION:
		case ENC_PROCESS_CONDITION:

			if(problem_info->staticPredicateMap[lit->getHead()->getName()]) {
				enc_event_condition_stack->push_back(z3_context->bool_val(true));
				break;
			}

			if(enc_cond_neg) {
				enc_event_condition_stack->push_back(!event_cascade_literal_vars[lit->getID()][enc_expression_h][enc_expression_b]);
				enc_musts_discrete_stack.push_back(event_cascade_literal_vars[lit->getID()][enc_expression_h][enc_expression_b]);
			} else {
				enc_event_condition_stack->push_back(event_cascade_literal_vars[lit->getID()][enc_expression_h][enc_expression_b]);
				enc_musts_discrete_stack.push_back(!event_cascade_literal_vars[lit->getID()][enc_expression_h][enc_expression_b]);
			}
			break;

		case ENC_SIMPLE_ACTION_CONDITION:
			if(enc_cond_neg) {
				z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], !event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-2]));
				// mutual exclusion
				std::vector<int>::const_iterator iterator = simpleStartAddEffects[lit->getID()].begin();
				for (; iterator != simpleStartAddEffects[lit->getID()].end(); ++iterator) {
					if((*iterator) == enc_opID) continue;
					z3_solver->add(!sta_action_vars[enc_opID][enc_expression_h] || !sta_action_vars[(*iterator)][enc_expression_h]);
				}
			} else {
				z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-2]));
				// mutual exclusion
				std::vector<int>::const_iterator iterator = simpleStartDelEffects[lit->getID()].begin();
				for (; iterator != simpleStartDelEffects[lit->getID()].end(); ++iterator) {
					if((*iterator) == enc_opID) continue;
					z3_solver->add(!sta_action_vars[enc_opID][enc_expression_h] || !sta_action_vars[(*iterator)][enc_expression_h]);
				}
			}
			break;

		case ENC_ACTION_CONDITION:
			if(problem_info->staticPredicateMap[lit->getHead()->getName()]) {
				break;
			}
			switch(enc_cond_time) {
			case VAL::E_AT_START:

				if(enc_cond_neg) {

					z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], !event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-2]));
					// mutual exclusion
					std::vector<int>::const_iterator iterator = simpleStartAddEffects[lit->getID()].begin();
					for (; iterator != simpleStartAddEffects[lit->getID()].end(); ++iterator) {
						if((*iterator) == enc_opID) continue;
						z3_solver->add(!sta_action_vars[enc_opID][enc_expression_h] || !sta_action_vars[(*iterator)][enc_expression_h]);
					}
				} else {

					z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-2]));
					// mutual exclusion
					std::vector<int>::const_iterator iterator = simpleStartDelEffects[lit->getID()].begin();
					for (; iterator != simpleStartDelEffects[lit->getID()].end(); ++iterator) {
						if((*iterator) == enc_opID) continue;
						z3_solver->add(!sta_action_vars[enc_opID][enc_expression_h] || !sta_action_vars[(*iterator)][enc_expression_h]);
					}
				}
				break;
			case VAL::E_AT_END:
				if(enc_cond_neg) {
					z3_solver->add(implies(end_action_vars[enc_opID][enc_expression_h], !event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-2]));
				} else {
					z3_solver->add(implies(end_action_vars[enc_opID][enc_expression_h], event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-2]));
				}
				break;
			case VAL::E_OVER_ALL:
				if(enc_cond_neg) {
					z3_solver->add(implies(run_action_vars[enc_opID][enc_expression_h], !event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-2]));
				} else {
					z3_solver->add(implies(run_action_vars[enc_opID][enc_expression_h], event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-2]));
				}
				break;
			}
			break;
		default:
			std::cerr << "Visit simple goal without correct state! (" << enc_state << ")" << std::endl;
			break;
		}

		delete l;
	}

	void EncoderHappening::visit_comparison(VAL::comparison * c) {

		enc_expression_stack.clear();

		// generate SMT expression
		c->getLHS()->visit(this);
		c->getRHS()->visit(this);

		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();

		// generate SMT comparison
		z3::expr com = (rhs == lhs);
		switch(c->getOp()) {
		case VAL::E_GREATER: com = (lhs > rhs); break;
		case VAL::E_GREATEQ: com = (lhs >= rhs); break;
		case VAL::E_LESS: com = (lhs < rhs); break;
		case VAL::E_LESSEQ: com = (lhs <= rhs); break;
		case VAL::E_EQUALS: com = (lhs <= rhs) && (lhs >= rhs); break;
		}
		// encode planning constraint		
		switch(enc_state) {

		case ENC_GOAL:
			{
				std::stringstream ss;
				ss << com;
				z3::expr g = z3_context->bool_const(ss.str().c_str());
				z3_solver->add(implies(g,com));
				goal_expression.push_back(g);
			}
			break;

		case ENC_EVENT_CONDITION:
		case ENC_PROCESS_CONDITION:
			// save the event trigger
			enc_event_condition_stack->push_back(com);
			// save part of the MUST condition
			enc_musts_expression_stack.push_back((lhs-rhs));
			break;

		case ENC_ACTION_CONDITION:
		case ENC_SIMPLE_ACTION_CONDITION:
			switch(enc_cond_time) {
			case VAL::E_AT_START:
				z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], com));
				break;
			case VAL::E_AT_END:
				z3_solver->add(implies(end_action_vars[enc_opID][enc_expression_h], com));
				break;
			case VAL::E_OVER_ALL:
				z3_solver->add(implies(run_action_vars[enc_opID][enc_expression_h], com));
				z3_solver->add(implies(end_action_vars[enc_opID][enc_expression_h], com)); 
				break;
			}
			break;

		case ENC_ACTION_DURATION:
			z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], com));
			break;

		default:
			std::cerr << "Visit comparison without correct state! (" << enc_state << ")" << std::endl;
			break;
		}
	}

	void EncoderHappening::visit_qfied_goal(VAL::qfied_goal *){}
	void EncoderHappening::visit_disj_goal(VAL::disj_goal *){}
	void EncoderHappening::visit_imply_goal(VAL::imply_goal *){}

	/*---------*/
	/* effects */
	/*---------*/

	void EncoderHappening::visit_effect_lists(VAL::effect_lists * e) {

		enc_eff_neg = false;
		e->add_effects.pc_list<VAL::simple_effect*>::visit(this);

		enc_eff_neg = true;
		e->del_effects.pc_list<VAL::simple_effect*>::visit(this);
		enc_eff_neg = false;

		e->forall_effects.pc_list<VAL::forall_effect*>::visit(this);
		e->cond_effects.pc_list<VAL::cond_effect*>::visit(this);
		e->cond_assign_effects.pc_list<VAL::cond_effect*>::visit(this);
		e->assign_effects.pc_list<VAL::assignment*>::visit(this);
		e->timed_effects.pc_list<VAL::timed_effect*>::visit(this);
	}

	void EncoderHappening::visit_timed_effect(VAL::timed_effect * e) {
		enc_eff_time = e->ts;
		e->effs->visit(this);
	};

	void EncoderHappening::visit_simple_effect(VAL::simple_effect * e) {
		Inst::Literal * l = new Inst::Literal(e->prop, fe);
		Inst::Literal * const lit = Inst::instantiatedOp::findLiteral(l);

		if (!lit) return;

		switch(enc_state) {

		case ENC_EVENT_EFFECT:
			if(enc_eff_neg) {
				z3_solver->add(implies(
						event_vars[enc_opID][enc_expression_h][enc_expression_b],
						!event_cascade_literal_vars[lit->getID()][enc_expression_h][enc_expression_b+1]));
				// save del effect for literal support later
				if(enc_expression_h==0 && enc_expression_b==0) simpleEventDelEffects[lit->getID()].push_back(enc_opID);
			} else {
				z3_solver->add(implies(
						event_vars[enc_opID][enc_expression_h][enc_expression_b],
						event_cascade_literal_vars[lit->getID()][enc_expression_h][enc_expression_b+1]));
				// save add effect for literal support later
				if(enc_expression_h==0 && enc_expression_b==0) simpleEventAddEffects[lit->getID()].push_back(enc_opID);
			}
			break;

		case ENC_SIMPLE_ACTION_EFFECT:
			if(enc_eff_neg) {
				z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], !event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-1]));
				// save del effect for literal support later
				if(enc_expression_h==0) simpleStartDelEffects[lit->getID()].push_back(enc_opID);
			} else {
				z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-1]));
				// save add effect for literal support later
				if(enc_expression_h==0) simpleStartAddEffects[lit->getID()].push_back(enc_opID);
			}
			break;

		case ENC_TIL_EFFECT:

			problem_info->staticPredicateMap[lit->getHead()->getName()] = false;
			if(enc_eff_neg) {
				z3_solver->add(implies(til_vars[enc_tilID][enc_expression_h], !event_cascade_literal_vars[lit->getID()][enc_expression_h][0]));
				// save del effect for literal support later
				if(enc_expression_h==0) simpleTILDelEffects[lit->getID()].push_back(enc_tilID);
			} else {
				z3_solver->add(implies(til_vars[enc_tilID][enc_expression_h], event_cascade_literal_vars[lit->getID()][enc_expression_h][0]));
				// save add effect for literal support later
				if(enc_expression_h==0) simpleTILAddEffects[lit->getID()].push_back(enc_tilID);
			}
			break;

		case ENC_ACTION_EFFECT:
			switch(enc_eff_time) {
			case VAL::E_AT_START:
				if(enc_eff_neg) {
					z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], !event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-1]));
					// save del effect for literal support later
					if(enc_expression_h==0) simpleStartDelEffects[lit->getID()].push_back(enc_opID);
				} else {
					z3_solver->add(implies(sta_action_vars[enc_opID][enc_expression_h], event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-1]));
					// save add effect for literal support later
					if(enc_expression_h==0) simpleStartAddEffects[lit->getID()].push_back(enc_opID);
				}
				break;
			case VAL::E_AT_END:
				if(enc_eff_neg) {
					z3_solver->add(implies(end_action_vars[enc_opID][enc_expression_h], !event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-1]));
					// save del effect for literal support later
					if(enc_expression_h==0) simpleEndDelEffects[lit->getID()].push_back(enc_opID);
				} else {
					z3_solver->add(implies(end_action_vars[enc_opID][enc_expression_h], event_cascade_literal_vars[lit->getID()][enc_expression_h][opt->cascade_bound-1]));
					// save add effect for literal support later
					if(enc_expression_h==0) simpleEndAddEffects[lit->getID()].push_back(enc_opID);
				}
				break;
			}
			break;

		default:
			std::cerr << "Visit effects without correct state! (" << enc_state << ")" << std::endl;
			break;
		}

		delete l;
	}

	void EncoderHappening::visit_assignment(VAL::assignment * e) {

		Inst::PNE * l = new Inst::PNE(e->getFTerm(), fe);	
		Inst::PNE * const lit = Inst::instantiatedOp::findPNE(l);

		if (!lit) return;

		// value
		enc_continuous = false;
		e->getExpr()->visit(this);
		if(enc_continuous) {
			enc_expression_stack.clear();
			return;
		}

		z3::expr expr = enc_expression_stack.back();
		enc_expression_stack.pop_back();

		// function
		enc_pneID = lit->getID();
		enc_function_symbol = l->getHead()->getName();
		z3::expr * opExpr;
		switch(enc_state) {

		case ENC_EVENT_EFFECT:

			opExpr = &event_vars[enc_opID][enc_expression_h][enc_expression_b];
			if(enc_expression_h==0 && enc_expression_b == 0) {
				simpleEventAssignEffects[lit->getID()];
				simpleEventAssignEffects[lit->getID()].push_back(std::pair<int,z3::expr>(enc_opID, expr));
			}
			break;

		case ENC_SIMPLE_ACTION_EFFECT:
		case ENC_ACTION_EFFECT:

			switch(enc_eff_time) {
			case VAL::E_AT_START:
				opExpr = &sta_action_vars[enc_opID][enc_expression_h];
				if(enc_expression_h==0) {
					simpleStartAssignEffects[lit->getID()];
					simpleStartAssignEffects[lit->getID()].push_back(std::pair<int,z3::expr>(enc_opID, expr));
				}
				break;
			case VAL::E_AT_END:
				opExpr = &end_action_vars[enc_opID][enc_expression_h];
				if(enc_expression_h==0) {
					simpleEndAssignEffects[lit->getID()];
					simpleEndAssignEffects[lit->getID()].push_back(std::pair<int,z3::expr>(enc_opID, expr));
				}
				break;

			default:
				std::cerr << "Visit assignment without time spec!" << std::endl;
				break;
			}
			break;

			case ENC_TIL_EFFECT:
				opExpr = &til_vars[enc_tilID][enc_expression_h];
				if(enc_expression_h==0) {
					simpleTILAssignEffects[lit->getID()];
					simpleTILAssignEffects[lit->getID()].push_back(std::pair<int,z3::expr>(enc_tilID, expr));
				}
				problem_info->staticFunctionMap[lit->getHead()->getName()] = false;
				break;

			break;
		}

		// operator
		VAL::assign_op op = e->getOp();
		switch(op) {
		case VAL::E_ASSIGN:
			if(enc_state == ENC_TIL_EFFECT)
				z3_solver->add(implies(*opExpr, (event_cascade_function_vars[enc_pneID][enc_expression_h][0] == expr)));
			else
				z3_solver->add(implies(*opExpr, (event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-1] == expr)));
			break;
		case VAL::E_INCREASE:
			z3_solver->add(implies(*opExpr, (
				event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-1] == (expr + event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-2])
			)));
			break;
		case VAL::E_DECREASE:
			z3_solver->add(implies(*opExpr, (
				event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-1] == (event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-2] - expr)
			)));
			break;
		case VAL::E_SCALE_UP:
			z3_solver->add(implies(*opExpr, (
				event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-1] == (expr * event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-2])
			)));
			break;
		case VAL::E_SCALE_DOWN:
			z3_solver->add(implies(*opExpr, (
				event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-1] == (event_cascade_function_vars[enc_pneID][enc_expression_h][opt->cascade_bound-2] / expr)
			)));
			break;
		case VAL::E_ASSIGN_CTS:
			std::cerr << "not implemented assign CTS" << std::endl;
			break;
		}
		delete l;
	}

	void EncoderHappening::visit_forall_effect(VAL::forall_effect * e) {std::cout << "not implemented forall" << std::endl;};
	void EncoderHappening::visit_cond_effect(VAL::cond_effect * e) {std::cout << "not implemented cond" << std::endl;};

	/*-------------*/
	/* expressions */
	/*-------------*/

	void EncoderHappening::parseExpression(VAL::expression * e) {
		e->visit(this);
	}

	void EncoderHappening::visit_plus_expression(VAL::plus_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		enc_expression_stack.push_back(lhs + rhs);
	}

	void EncoderHappening::visit_minus_expression(VAL::minus_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		enc_expression_stack.push_back(lhs - rhs);
	}

	void EncoderHappening::visit_mul_expression(VAL::mul_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		enc_expression_stack.push_back(lhs * rhs);
	}

	void EncoderHappening::visit_div_expression(VAL::div_expression * s) {

		s->getLHS()->visit(this);
		s->getRHS()->visit(this);

		z3::expr rhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		z3::expr lhs = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		enc_expression_stack.push_back(lhs / rhs);
	}

	void EncoderHappening::visit_uminus_expression(VAL::uminus_expression * s) {

		s->getExpr()->visit(this);

		z3::expr exp = enc_expression_stack.back();
		enc_expression_stack.pop_back();
		enc_expression_stack.push_back(-exp);
	}

	void EncoderHappening::visit_int_expression(VAL::int_expression * s) {

		std::stringstream ss;
		ss << s->double_value();
		z3::expr dv = z3_context->real_val(ss.str().c_str());
		enc_expression_stack.push_back(dv);
	}

	void EncoderHappening::visit_float_expression(VAL::float_expression * s) {

		std::stringstream ss;
		ss << s->double_value();
		z3::expr dv = z3_context->real_val(ss.str().c_str());
		enc_expression_stack.push_back(dv);
	}

	void EncoderHappening::visit_func_term(VAL::func_term * s) {
		Inst::PNE * l = new Inst::PNE(s, fe);
		Inst::PNE * const lit = Inst::instantiatedOp::findPNE(l);

		if (!lit) {
			z3::expr dv = z3_context->real_val(0);
			enc_expression_stack.push_back(dv);
			delete l;
			return;
		}

		switch(enc_state) {

		case ENC_GOAL:
			if(problem_info->staticFunctionMap[l->getHead()->getName()]) {
				enc_expression_stack.push_back(problem_info->staticFunctionValues.find(lit->getID())->second);
			} else {
				enc_expression_stack.push_back(event_cascade_function_vars[lit->getID()][enc_expression_h][opt->cascade_bound-1]);
			}
			break;
		case ENC_ACTION_DURATION:
		case ENC_ACTION_CONDITION:
		case ENC_ACTION_EFFECT:
		case ENC_SIMPLE_ACTION_CONDITION:
		case ENC_SIMPLE_ACTION_EFFECT:
		case ENC_EVENT_EFFECT:
		case ENC_TIL_EFFECT:
		case ENC_EVENT_CONDITION:
		case ENC_PROCESS_CONDITION:
			if(problem_info->staticFunctionMap[lit->getHead()->getName()]) {
				enc_expression_stack.push_back(problem_info->staticFunctionValues.find(lit->getID())->second);
			} else {
				enc_expression_stack.push_back(event_cascade_function_vars[lit->getID()][enc_expression_h][enc_expression_b]);
			}
			break;

		default:
			std::cerr << "Visit func_term expression without correct state! (" << enc_state << ")" << std::endl;
			break;
		}
		delete l;
	}

	void EncoderHappening::visit_special_val_expr(VAL::special_val_expr * s) {

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
			enc_continuous = true;
			switch(enc_state) {
			case ENC_ACTION_EFFECT:
				enc_expression_stack.push_back(dur_action_vars[enc_opID][enc_expression_h]);
				break;
			}
			break;
		case VAL::E_TOTAL_TIME:
			std::cerr << "Total time used in expression, but not implemented!" << std::endl;
			break;
		}
	}

	/*-------*/
	/* extra */
	/*-------*/

	void EncoderHappening::visit_preference(VAL::preference *){}
	void EncoderHappening::visit_derivation_rule(VAL::derivation_rule * o){}

} // close namespace
