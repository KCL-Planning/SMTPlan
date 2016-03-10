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
		encodeGoalState(domain, problem, grounder, (H-1));

		for(int h=0; h<H; h++) {
			encodeTimings(h);
			encodeHappeningVariableSupport(domain, problem, grounder, h);
			encodeIntervalVariableSupport(domain, problem, grounder, h);
			encodeActionConditions(domain, problem, grounder, h);
			encodeActionEffects(domain, problem, grounder, h);
			encodeActionDurations(domain, problem, grounder, h);
			encodeActionMutexes(domain, problem, grounder, h);
		}


		(*out) << "(check-sat)" << std::endl;
		(*out) << "(get-model)" << std::endl;
		(*out) << "(exit)" << std::endl;

		return true;
	}

	/**
	 * writes header vars, for happening h
	 */
	void Encoder::encodeHeader(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		(*out) << "(declare-fun t_" << h << " () Real)" << std::endl;
		(*out) << "(declare-fun duration_" << h << " () Real)" << std::endl;

		// propositions
		for (int i=0; i<grounder.props.size(); i++) {
			(*out) << "(declare-fun " << grounder.props[i].var_name << "_0_" << h << " () Bool)" << std::endl;
			(*out) << "(declare-fun " << grounder.props[i].var_name << "_1_" << h << " () Bool)" << std::endl;
		}

		// fluents
		for (int i=0; i<grounder.fluents.size(); i++) {
			(*out) << "(declare-fun " << grounder.fluents[i].var_name << "_0_" << h << " () Real)" << std::endl;
			(*out) << "(declare-fun " << grounder.fluents[i].var_name << "_1_" << h << " () Real)" << std::endl;
		}

		// actions
		for (int i=0; i<grounder.actions.size(); i++) {
			(*out) << "(declare-fun " << "sta_" << grounder.actions[i].var_name << "_" << h << " () Bool)" << std::endl;
			(*out) << "(declare-fun " << "end_" << grounder.actions[i].var_name << "_" << h << " () Bool)" << std::endl;
			(*out) << "(declare-fun " << "run_" << grounder.actions[i].var_name << "_" << h << " () Bool)" << std::endl;
			(*out) << "(declare-fun " << "dur_" << grounder.actions[i].var_name << "_" << h << " () Real)" << std::endl;
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

		// discrete part
		for(int i=0; i<grounder.props.size(); i++) {			
			std::stringstream ss;
			if(!grounder.initial_state[i])
				ss << "(not ";
			ss << grounder.props[i].var_name << "_0_0";
			if(!grounder.initial_state[i])
				ss << ")";			
			(*out) << "(assert " << ss.str() << ")" << std::endl;
		}

		VAL::effect_lists* eff_list = problem->initial_state;

		// assign effects
		for (VAL::pc_list<VAL::assignment*>::const_iterator ci = eff_list->assign_effects.begin(); ci != eff_list->assign_effects.end(); ci++) {
			const VAL::assignment* effect = *ci;

			std::stringstream ss;
			ss << effect->getFTerm()->getFunction()->getName();
			for (VAL::parameter_symbol_list::const_iterator vi = effect->getFTerm()->getArgs()->begin(); vi != effect->getFTerm()->getArgs()->end(); vi++) {			
				const VAL::parameter_symbol* var = *vi;
				ss << "_" << var->getName();
			}
			ss << "_0_0";

			(*out) << "(assert (= " << ss.str() << " " << parseExpression(effect->getExpr(),0,0) << "))" << std::endl;
		}
	}

	/**
	 * Constraints P2 (A Compilation of the Full PDDL+ Language into SMT)
	 * encodes the goal state
	 */
	void Encoder::encodeGoalState(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		VAL::goal* goal = problem->the_goal;
		(*out) << "(assert " << parseCondition(goal,h,1) << ")" << std::endl;
	}

	/*-------------------*/
	/* variable supports */
	/*-------------------*/

	/**
	 * Constraints H1--H6 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes variable support for propositions and real values variables, in the form of explanatory frame axioms.
	 */
	void Encoder::encodeHappeningVariableSupport(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		// explanatory frame axioms in happening;
		for (int i=0; i<grounder.props.size(); i++) {

			// remain TRUE
			(*out) << "(assert (=> " << grounder.props[i].var_name << "_1_" << h << " ";
			if((grounder.props[i].sta_add_actions|grounder.props[i].end_add_actions).any()) {
				(*out) << "(or";
				for(int a=0;a<MAX_BITSET;a++) {
					if(grounder.props[i].sta_add_actions[a])
						(*out) << " sta_" << grounder.actions[a].var_name << "_" << h;
					if(grounder.props[i].end_add_actions[a])
						(*out) << " end_" << grounder.actions[a].var_name << "_" << h;
				}
				(*out) << " " << grounder.props[i].var_name << "_0_" << h << ")";
			} else {
				(*out) << grounder.props[i].var_name << "_0_" << h;
			}
			(*out) << "))" << std::endl;

			// remain FALSE
			(*out) << "(assert (=> (not " << grounder.props[i].var_name << "_1_" << h << ") ";
			if((grounder.props[i].sta_del_actions|grounder.props[i].end_del_actions).any()) {
				(*out) << "(or";
				for(int a=0;a<MAX_BITSET;a++) {
					if(grounder.props[i].sta_del_actions[a])
						(*out) << " sta_" << grounder.actions[a].var_name << "_" << h;
					if(grounder.props[i].end_del_actions[a])
						(*out) << " end_" << grounder.actions[a].var_name << "_" << h;
				}
				(*out) << " (not " << grounder.props[i].var_name << "_0_" << h << "))";
			} else {
				(*out) << " (not " << grounder.props[i].var_name << "_0_" << h << ")";
			}
			(*out) << "))" << std::endl;
		}

		// fixed numeric variables in happening
		for (int i=0; i<grounder.fluents.size(); i++) {
			(*out) << "(assert (= "
					<< grounder.fluents[i].var_name << "_1_" << h << " "
					<< grounder.fluents[i].var_name << "_0_" << h
					<< " ))" << std::endl;
		}
	}

	/**
	 * Constraints P5--P6 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes variable support for propositions and real values variables, in the form of explanatory frame axioms.
	 */
	void Encoder::encodeIntervalVariableSupport(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		if(h<=0) return;

		// explanatory frame axioms between happenings
		for (int i=0; i<grounder.props.size(); i++) {
			(*out) << "(assert (=> "
					<< grounder.props[i].var_name << "_0_" << h << " "
					<< grounder.props[i].var_name << "_1_" << (h-1)
					<< " ))" << std::endl;
		}
		for (int i=0; i<grounder.props.size(); i++) {
			(*out) << "(assert (=> "
					<< "(not " << grounder.props[i].var_name << "_0_" << h << ") "
					<< "(not " << grounder.props[i].var_name << "_1_" << (h-1) << ")"
					<< " ))" << std::endl;
		}

		// fixed numeric variables between happenings
		for (int i=0; i<grounder.fluents.size(); i++) {
			(*out) << "(assert (= "
					<< grounder.fluents[i].var_name << "_0_" << h << " "
					<< grounder.fluents[i].var_name << "_1_" << (h-1)
					<< " ))" << std::endl;
		}
	}

	/*---------*/
	/* actions */
	/*---------*/

	/**
	 * Constraints H13--15 & P7 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes action support.
	 */
	void Encoder::encodeActionDurations(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		// operators
		VAL::operator_list* operators = domain->ops;
		for (VAL::operator_list::const_iterator ci = operators->begin(); ci != operators->end(); ci++) {
			const VAL::operator_* op = (*ci);
			const std::string name = op->name->symbol::getName();

			// if no actions, skip operator
			if(grounder.op_action_map[name].size() == 0)
				continue;

			// for each action of this operator
			std::vector<PDDLDurativeAction>::iterator ait = grounder.op_action_map[name].begin();
			for(; ait!=grounder.op_action_map[name].end(); ait++) {
				PDDLDurativeAction action = (*ait);

				// running action/process iff (remaining duration > 0)
				(*out) << "(assert (=> " << "run_" << action.var_name << "_" << h << " "
						<< "(> dur_" << action.var_name << "_" << h << " 0)))" << std::endl;
				(*out) << "(assert (=> " << "(not run_" << action.var_name << "_" << h << ") "
						<< "(= dur_" << action.var_name << "_" << h << " 0)))" << std::endl;

				// remaining duration (i) = remaining duration (i-1) - duration (i)
				if(h>0) {
					(*out) << "(assert (=> " << "run_" << action.var_name << "_" << (h-1) << " "
						<< "(= " << "dur_" << action.var_name << "_" << h << " "
						<< "(- dur_" << action.var_name << "_" << (h-1) << " duration_" << (h-1) << "))))" << std::endl;
				}

				// ground duration
				std::stringstream ss;
				ss << "dur_" << action.var_name << "_" << h;
				std::string duration = action.unground_duration;
				findReplace(duration, action.param_object);
				addHappeningTags(duration, 0, h);
				std::string find("duration");
				std::string replace(ss.str());
				findReplace(duration, find, replace);

				// remaining duration = action duration
				(*out) << "(assert (=> " << "sta_" << action.var_name << "_" << h << " " << duration << "))" << std::endl;
				(*out) << "(assert (=> " << "end_" << action.var_name << "_" << h << " "
					<< "(= " << "dur_" << action.var_name << "_" << h << " 0)))" << std::endl;

				// start->run->end
				if(h>0) {
					(*out) << "(assert (=> " << "end_" << action.var_name << "_" << h << " " << "run_" << action.var_name << "_" << (h-1) << "))" << std::endl;
					(*out) << "(assert (=> " << "sta_" << action.var_name << "_" << h << " (not " << "run_" << action.var_name << "_" << (h-1) << ")))" << std::endl;

					(*out) << "(assert (=> " << "run_" << action.var_name << "_" << h << " (or"
							<< " " << "sta_" << action.var_name << "_" << h
							<< " " << "run_" << action.var_name << "_" << (h-1)
							<< ")))" << std::endl;

					(*out) << "(assert (=> " << "(not run_" << action.var_name << "_" << h << ") (or"
							<< " " << "end_" << action.var_name << "_" << h
							<< " " << "(not run_" << action.var_name << "_" << (h-1)
							<< "))))" << std::endl;
				} else {
					(*out) << "(assert (not end_" << action.var_name << "_" << h << "))" << std::endl;
					(*out) << "(assert (=> " << "run_" << action.var_name << "_" << h
							<< " " << "sta_" << action.var_name << "_" << h
							<< "))" << std::endl;
					(*out) << "(assert (=> " << "(not run_" << action.var_name << "_" << h << ")"
							<< " " << "(not sta_" << action.var_name << "_" << h << ")"
							<< "))" << std::endl;
				}
			}
		}
	}

	/**
	 * Constraints H9 (A Compilation of the Full PDDL+ Language into SMT)
	 * Encodes action support.
	 */
	void Encoder::encodeActionConditions(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		// operators
		VAL::operator_list* operators = domain->ops;
		for (VAL::operator_list::const_iterator ci = operators->begin(); ci != operators->end(); ci++) {
			const VAL::operator_* op = (*ci);
			const VAL::goal* condition = op->precondition;
			const std::string name = op->name->symbol::getName();

			// if no actions, skip operator
			if(grounder.op_action_map[name].size() == 0)
				continue;

			// ungrounded conditions
			std::string c_start = parseTimedCondition(condition, VAL::E_AT_START, h, 0);
			std::string c_end = parseTimedCondition(condition, VAL::E_AT_END, h, 0);
			std::string c_overall = parseTimedCondition(condition, VAL::E_OVER_ALL, h, 0);

			// for each action of this operator
			std::vector<PDDLDurativeAction>::iterator ait = grounder.op_action_map[name].begin();
			for(; ait!=grounder.op_action_map[name].end(); ait++) {
				PDDLDurativeAction action = (*ait);

				if(c_start.length()>0) {
					std::string gc_start = c_start;
					findReplace(gc_start, action.param_object);
					(*out) << "(assert (=> " << "sta_" << action.var_name << "_" << h << " " << gc_start << "))" << std::endl;
				}

				if(c_end.length()>0) {
					std::string gc_end = c_end;
					findReplace(gc_end, action.param_object);
					(*out) << "(assert (=> " << "end_" << action.var_name << "_" << h << " " << gc_end << "))" << std::endl;
				}

				if(c_overall.length()>0) {
					std::string gc_overall = c_overall;
					findReplace(gc_overall, action.param_object);
					(*out) << "(assert (=> " << "sta_" << action.var_name << "_" << h << " " << gc_overall << "))" << std::endl;
					(*out) << "(assert (=> " << "end_" << action.var_name << "_" << h << " " << gc_overall << "))" << std::endl;
				}
			}
		}
	}

	/**
	 * Constraints H10 (A Compilation of the Full PDDL+ Language into SMT)
	 * Enforces action effects.
	 */
	void Encoder::encodeActionEffects(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		// operators
		VAL::operator_list* operators = domain->ops;
		for (VAL::operator_list::const_iterator ci = operators->begin(); ci != operators->end(); ci++) {
			const VAL::operator_* op = (*ci);
			const VAL::effect_lists* eff_list = op->effects;
			const std::string name = op->name->symbol::getName();

			// if no actions, skip operator
			if(grounder.op_action_map[name].size() == 0)
				continue;

			// timed effects
			for (VAL::pc_list<VAL::timed_effect*>::const_iterator ci = eff_list->timed_effects.begin(); ci != eff_list->timed_effects.end(); ci++) {
				const VAL::timed_effect* effect = *ci;


				std::vector<PDDLDurativeAction>::iterator ait = grounder.op_action_map[name].begin();
				for(; ait!=grounder.op_action_map[name].end(); ait++) {
					PDDLDurativeAction action = (*ait);

					std::stringstream ss;					

					// simple add effects
					VAL::pc_list<VAL::simple_effect*>::const_iterator sei = effect->effs->add_effects.begin();
					if (sei != effect->effs->add_effects.end()) {
						const VAL::simple_effect* simpleEffect = *sei;
						ss << simpleEffect->prop->head->getName();
						for (VAL::parameter_symbol_list::const_iterator vi = simpleEffect->prop->args->begin(); vi != simpleEffect->prop->args->end(); vi++) {			
							const VAL::parameter_symbol* var = *vi;
							ss << "_" << var->getName();
						}
						ss << "_1_" << h;
					}

					// negative effects
					VAL::pc_list<VAL::simple_effect*>::const_iterator nei = effect->effs->del_effects.begin();
					if (nei != effect->effs->del_effects.end()) {
						const VAL::simple_effect* simpleEffect = *nei;
						ss << "(not " << simpleEffect->prop->head->getName();
						for (VAL::parameter_symbol_list::const_iterator vi = simpleEffect->prop->args->begin(); vi != simpleEffect->prop->args->end(); vi++) {			
							const VAL::parameter_symbol* var = *vi;
							ss << "_" << var->getName();
						}
						ss << "_1_" << h << ")";
					}

					// assign effects
					VAL::pc_list<VAL::assignment*>::const_iterator aei = effect->effs->assign_effects.begin();
					if (aei != effect->effs->assign_effects.end()) {
						const VAL::assignment* assignEffect = *aei;

						std::stringstream ss;
						ss << assignEffect->getFTerm()->getFunction()->getName();
						for (VAL::parameter_symbol_list::const_iterator vi = assignEffect->getFTerm()->getArgs()->begin(); vi != assignEffect->getFTerm()->getArgs()->end(); vi++) {		
							const VAL::parameter_symbol* var = *vi;
							ss << "_" << var->getName();
						}
						ss << "_1_" << h;
					}
					
					ss << "))" << std::endl;

					std::string effectString = ss.str();
					findReplace(effectString, action.param_object);

					switch(effect->ts) {
					case VAL::E_AT_START: (*out) << "(assert (=> " << "sta_" << action.var_name << "_" << h << " "; break;
					case VAL::E_AT_END: (*out) << "(assert (=> " << "end_" << action.var_name << "_" << h << " "; break;
					default: std::cerr << "UNRECOGNISED EFFECT TIME SPEC" << std::endl; break;
					}
					(*out) << effectString;
				}
			}
		}
	}

	/**
	 * Constraints H16 (A Compilation of the Full PDDL+ Language into SMT)
	 * Enforces action mutual exclusion relations.
	 */
	void Encoder::encodeActionMutexes(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h) {

		std::vector<PDDLDurativeAction>::iterator ait1 = grounder.actions.begin();
		std::vector<PDDLDurativeAction>::iterator ait2 = grounder.actions.begin();
		for(; ait1!=grounder.actions.end(); ait1++) {
			for(; ait2!=ait1; ait2++) {
				(*out) << "(assert (=> " << "sta_" << (*ait1).var_name << "_" << h << " " << "(not sta_" << (*ait2).var_name << "_" << h << ")))" << std::endl;
				(*out) << "(assert (=> " << "sta_" << (*ait1).var_name << "_" << h << " " << "(not end_" << (*ait2).var_name << "_" << h << ")))" << std::endl;
				(*out) << "(assert (=> " << "end_" << (*ait1).var_name << "_" << h << " " << "(not sta_" << (*ait2).var_name << "_" << h << ")))" << std::endl;
				(*out) << "(assert (=> " << "end_" << (*ait1).var_name << "_" << h << " " << "(not end_" << (*ait2).var_name << "_" << h << ")))" << std::endl;
			}
		}
	}

	/*---------------------*/
	/* PDDL to SMT strings */
	/*---------------------*/

	/**
	 * parse an expression recursively.
	 */
	std::string Encoder::parseExpression(const VAL::expression* exp, int h, int b) {

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
			ss << "(- 0 " << parseExpression(ume->getExpr(),h,b) << ")";
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
			ss << "_" << b << "_" << h;
			return ss.str();
		}

		// binary expressions
		const VAL::binary_expression* be = dynamic_cast<const VAL::binary_expression*>(exp);
		if (be) {
			std::string lhs = parseExpression(be->getLHS(),h,b);
			std::string rhs = parseExpression(be->getRHS(),h,b);

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
	std::string Encoder::parseCondition(const VAL::goal* goal, int h, int b) {

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
			ss << "_" << b << "_" << h;
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
			ss << parseExpression(co->getLHS(),h,b) << " " << parseExpression(co->getRHS(),h,b) << ")";
			return ss.str();
		}

		// negative condition
		const VAL::neg_goal* ng = dynamic_cast<const VAL::neg_goal*>(goal);
		if (ng) {
			ss << "(not " << parseCondition(ng->getGoal(),h,b) << ")";
			return ss.str();
		}

		// conjunctive condition
		const VAL::conj_goal* cg = dynamic_cast<const VAL::conj_goal*>(goal);
		if (cg) {
			ss << "(and";
		        const VAL::goal_list* goals = cg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				ss << " " << parseCondition((*ci),h,b);
			}
			ss << ")";
			return ss.str();
		}

		// disjunctive condition
		const VAL::disj_goal* dg = dynamic_cast<const VAL::disj_goal*>(goal);
		if (dg) {
			ss << "(or";
		        const VAL::goal_list* goals = dg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				ss << " " << parseCondition((*ci),h,b);
			}
			ss << ")";
			return ss.str();
		}

		return "PARSING_ERROR";
	}

	/**
	 * parse a condition recursively, only retrieving a timed part
	 */
	std::string Encoder::parseTimedCondition(const VAL::goal* goal, VAL::time_spec part, int h, int b) {

		std::stringstream ss;

		// conjunctive condition
		const VAL::conj_goal* cg = dynamic_cast<const VAL::conj_goal*>(goal);
		if (cg) {
			ss << "(and";
		        const VAL::goal_list* goals = cg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				std::string c = parseTimedCondition((*ci),part,h,b);
				if(c.length()>0) ss << " " << c;
			}
			ss << ")";
			if (ss.str().length()>5) return ss.str();
			return "";
		}

		// disjunctive condition
		const VAL::disj_goal* dg = dynamic_cast<const VAL::disj_goal*>(goal);
		if (dg) {
			ss << "(or";
		        const VAL::goal_list* goals = dg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				std::string c = parseTimedCondition((*ci),part,h,b);
				if(c.length()>0) ss << " " << c;
			}
			ss << ")";
			if (ss.str().length()>4) return ss.str();
			return "";
		}


		// timed condition
		const VAL::timed_goal* tg = dynamic_cast<const VAL::timed_goal*>(goal);
		if (tg) {
			if(tg->getTime() == part) {
				return parseCondition(tg->getGoal(),h,b);
			} else {
				return "";
			}
		}

		return "PARSING_ERROR";
	}
} // close namespace
