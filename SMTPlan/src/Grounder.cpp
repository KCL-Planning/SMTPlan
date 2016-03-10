#include "SMTPlan/Grounder.h"

/* implementation of SMTPlan::Grounder */
namespace SMTPlan {

	// is A a type of B?
	bool Grounder::isTypeOf(const VAL::pddl_type* a, const VAL::pddl_type* b) {
		if(a->getName() == b->getName())
			return true;
		if(a->type == NULL || a->getName() == "object")
			return false;
		return isTypeOf(a->type, b);
	}

	// ground out problem and store
	bool Grounder::ground(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options) {

		if(grounded) return true;

		groundProps(domain, problem, options);
		groundFluents(domain, problem, options);
		groundActions(domain, problem, options);

		grounded = true;
		return true;
	}

	// copy one (partial) PDDLAtomicFormula into another (proposition, fluent, or action signature)
	void Grounder::copyFormula(PDDLAtomicFormula &oldProp, PDDLAtomicFormula &newProp) {
		newProp.name = oldProp.name;
		for(int i=0; i<oldProp.param_types.size(); i++) {
			newProp.param_types.push_back(oldProp.param_types[i]);
			newProp.param_names.push_back(oldProp.param_names[i]);
		}
	}

	// copy one (partial) PDDLDurativeAction into another
	void Grounder::copyDurativeAction(PDDLDurativeAction &oldact, PDDLDurativeAction &newact) {
		copyFormula(oldact.definition, newact.definition);
		newact.param_object = oldact.param_object;
	}

	/*---------*/
	/* ACTIONS */
	/*---------*/

	/**
	 * generate PDDLAtomicFormulas representing ground actions from operators and objects
	 */
	void Grounder::groundActions(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options) {

		VAL::operator_list* operators = domain->ops;
		for (VAL::operator_list::const_iterator ci = operators->begin(); ci != operators->end(); ci++) {			
			const VAL::operator_* op = *ci;

			PDDLDurativeAction action;
			action.definition.name = op->name->symbol::getName();
			op_action_map[action.definition.name];
			std::deque<PDDLDurativeAction> groundingActions;
			groundingActions.push_back(action);

			for (VAL::var_symbol_list::const_iterator vi = op->parameters->begin(); vi != op->parameters->end(); vi++) {
				const VAL::var_symbol* var = *vi;

				// for each partially grounded action
				int propCount = groundingActions.size();
				for(int i=0; i<propCount; i++) {
					action = groundingActions.front();
					groundingActions.pop_front();

					//for each object
					VAL::const_symbol_list* objects = problem->objects;
					for (VAL::const_symbol_list::const_iterator ci = objects->begin(); ci != objects->end(); ci++) {
						const VAL::const_symbol* object = *ci;

						// bind object to parameter, save (partially) grounded action
						if(isTypeOf(object->type, var->type)) {
							PDDLDurativeAction newAction;
							copyDurativeAction(action, newAction);
							newAction.definition.param_types.push_back(object->type->getName());
							newAction.definition.param_names.push_back(object->getName());
							newAction.param_object[var->getName()] = object->getName();
							groundingActions.push_back(newAction);
						}
					}
				}
			}

			// save grounded actions
			while(groundingActions.size()>0) {

				if(actions.size()==MAX_BITSET) {
					std::cerr << "Too many grounded actions. Increase MAX_BITSET." << std::endl;
					std::exit(0);
				}

				PDDLDurativeAction action = groundingActions.front();
				
				std::stringstream ss;
				ss << action.definition.name;
				for(int i=0; i< action.definition.param_names.size(); i++)
					ss << "_" << action.definition.param_names[i];
				action.var_name = ss.str();
				action.index = (actions.size());

				// set action discrete effects and conditions
				action.sta_simple_conditions.reset();
				action.dur_simple_conditions.reset();
				action.end_simple_conditions.reset();
				groundActionConditions(domain, problem, op, action);

				action.sta_simple_add_effects.reset();
				action.sta_simple_del_effects.reset();
				action.end_simple_add_effects.reset();
				action.end_simple_del_effects.reset();
				groundActionEffects(domain, problem, op, action);

				groundActionDuration(domain, problem, op, action);

				actions.push_back(action);
				op_action_map[action.definition.name].push_back(action);
				groundingActions.pop_front();
			}
		}
	}

	void Grounder::groundActionDuration(VAL::domain* domain, VAL::problem* problem, const VAL::operator_* op, PDDLDurativeAction &action) {

		// operator
		const VAL::goal* condition = op->precondition;
		const std::string name = op->name->symbol::getName();

		const VAL::durative_action* dop = dynamic_cast<const VAL::durative_action*>(op);
		if (dop) {
			// fetch ungrounded duration constraint
			const VAL::goal* duration = dop->dur_constraint;
			action.unground_duration = parseTimedCondition(duration, VAL::E_AT_START);
		}
	}

	void Grounder::groundActionConditions(VAL::domain* domain, VAL::problem* problem, const VAL::operator_* op, PDDLDurativeAction &action) {

		// operator
		const VAL::goal* condition = op->precondition;
		const std::string name = op->name->symbol::getName();

		// fetch ungrounded conditions
		std::string c_start = parseTimedCondition(condition, VAL::E_AT_START);
		std::string c_end = parseTimedCondition(condition, VAL::E_AT_END);
		std::string c_overall = parseTimedCondition(condition, VAL::E_OVER_ALL);

		if(c_start.length()>0) {
			std::string gc_start = c_start;
			// bind params
			findReplace(gc_start, action.param_object);
			std::map<std::string,std::vector<PDDLAtomicFormula>::size_type>::iterator pit = string_prop_map.find(gc_start);
			if(pit!=string_prop_map.end()) {
				action.sta_simple_conditions.set(pit->second);
				props[pit->second].sta_condition_actions.set(action.index);
			}
		}

		else if(c_end.length()>0) {
			std::string gc_end = c_end;
			findReplace(gc_end, action.param_object);
			std::map<std::string,std::vector<PDDLAtomicFormula>::size_type>::iterator pit = string_prop_map.find(gc_end);
			if(pit!=string_prop_map.end()) {
				action.end_simple_conditions.set(pit->second);
				props[pit->second].end_condition_actions.set(action.index);
			}
		}

		else if(c_overall.length()>0) {
			std::string gc_overall = c_overall;
			findReplace(gc_overall, action.param_object);
			std::map<std::string,std::vector<PDDLAtomicFormula>::size_type>::iterator pit = string_prop_map.find(gc_overall);
			if(pit!=string_prop_map.end()) {
				action.dur_simple_conditions.set(pit->second);
				props[pit->second].dur_condition_actions.set(action.index);
			}
		}
	}

	void Grounder::groundActionEffects(VAL::domain* domain, VAL::problem* problem, const VAL::operator_* op, PDDLDurativeAction &action) {

		// operator
		const VAL::effect_lists* eff_list = op->effects;
		const std::string name = op->name->symbol::getName();

		// timed effects
		for (VAL::pc_list<VAL::timed_effect*>::const_iterator ci = eff_list->timed_effects.begin(); ci != eff_list->timed_effects.end(); ci++) {
			const VAL::timed_effect* effect = *ci;

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
				std::string effectString = ss.str();
				findReplace(effectString, action.param_object);
				std::map<std::string,std::vector<PDDLAtomicFormula>::size_type>::iterator pit = string_prop_map.find(effectString);
				if(pit!=string_prop_map.end()) {
					switch(effect->ts) {
					case VAL::E_AT_START:
						action.sta_simple_add_effects.set(pit->second);
						props[pit->second].sta_add_actions.set(action.index);
						break;
					case VAL::E_AT_END:
						action.end_simple_add_effects.set(pit->second);
						props[pit->second].end_add_actions.set(action.index);
						break;
					}
				}
			}

			// negative effects
			VAL::pc_list<VAL::simple_effect*>::const_iterator nei = effect->effs->del_effects.begin();
			if (nei != effect->effs->del_effects.end()) {
				const VAL::simple_effect* simpleEffect = *nei;
				ss << simpleEffect->prop->head->getName();
				for (VAL::parameter_symbol_list::const_iterator vi = simpleEffect->prop->args->begin(); vi != simpleEffect->prop->args->end(); vi++) {			
					const VAL::parameter_symbol* var = *vi;
					ss << "_" << var->getName();
				}
				std::string effectString = ss.str();
				findReplace(effectString, action.param_object);
				std::map<std::string,std::vector<PDDLAtomicFormula>::size_type>::iterator pit = string_prop_map.find(effectString);
				if(pit!=string_prop_map.end()) {
					switch(effect->ts) {
					case VAL::E_AT_START:
						action.sta_simple_del_effects.set(pit->second);
						props[pit->second].sta_del_actions.set(action.index);
						break;
					case VAL::E_AT_END:
						action.end_simple_del_effects.set(pit->second);
						props[pit->second].end_del_actions.set(action.index);
						break;
					}
				}
			}
		}
	}

	/*---------*/
	/* FLUENTS */
	/*---------*/

	/**
	 * generate real PDDLAtomicFormulas from functions and objects
	 */
	void Grounder::groundFluents(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options) {

		// for each function
		VAL::func_decl_list* functions = domain->functions;
		for (VAL::func_decl_list::const_iterator ci = functions->begin(); ci != functions->end(); ci++) {
			const VAL::func_decl* function = *ci;

			PDDLAtomicFormula fluent;
			fluent.name = function->getFunction()->symbol::getName();
			std::deque<PDDLAtomicFormula> groundingFluents;
			groundingFluents.push_back(fluent);

			for (VAL::var_symbol_list::const_iterator vi = function->getArgs()->begin(); vi != function->getArgs()->end(); vi++) {			
				const VAL::var_symbol* var = *vi;

				// for each partially grounded prop
				int propCount = groundingFluents.size();
				for(int i=0; i<propCount; i++) {
					fluent = groundingFluents.front();
					groundingFluents.pop_front();

					//for each object
					VAL::const_symbol_list* objects = problem->objects;
					for (VAL::const_symbol_list::const_iterator ci = objects->begin(); ci != objects->end(); ci++) {
						const VAL::const_symbol* object = *ci;

						// bind object to parameter, save (partially) grounded fluent
						if(isTypeOf(object->type, var->type)) {
							PDDLAtomicFormula newFluent;
							copyFormula(fluent, newFluent);
							newFluent.param_types.push_back(object->type->getName());
							newFluent.param_names.push_back(object->getName());
							groundingFluents.push_back(newFluent);
						}
					}
				}
			}

			// save grounded fluents
			while(groundingFluents.size()>0) {

				if(fluents.size()==MAX_BITSET) {
					std::cerr << "Too many grounded fluents. Increase MAX_BITSET." << std::endl;
					std::exit(0);
				}

				PDDLAtomicFormula fluent = groundingFluents.front();
				
				std::stringstream ss;
				ss << fluent.name;
				for(int i=0; i< fluent.param_names.size(); i++)
					ss << "_" << fluent.param_names[i];
				fluent.var_name = ss.str();
				fluents.push_back(fluent);
				groundingFluents.pop_front();
			}
		}
	}

	/*--------------*/
	/* PROPOSITIONS */
	/*--------------*/

	/**
	 * generate boolean PDDLAtomicFormulas from predicates and objects
	 */
	void Grounder::groundProps(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options) {

		// for each predicate
		VAL::pred_decl_list* predicates = domain->predicates;
		for (VAL::pred_decl_list::const_iterator ci = predicates->begin(); ci != predicates->end(); ci++) {
			const VAL::pred_decl* predicate = *ci;

			PDDLAtomicFormula prop;
			prop.name = predicate->getPred()->symbol::getName();
			pred_prop_map[prop.name];
			std::deque<PDDLAtomicFormula> groundingProps;
			groundingProps.push_back(prop);

			for (VAL::var_symbol_list::const_iterator vi = predicate->getArgs()->begin(); vi != predicate->getArgs()->end(); vi++) {			
				const VAL::var_symbol* var = *vi;

				// for each partially grounded prop
				int propCount = groundingProps.size();
				for(int i=0; i<propCount; i++) {
					prop = groundingProps.front();
					groundingProps.pop_front();

					//for each object
					VAL::const_symbol_list* objects = problem->objects;
					for (VAL::const_symbol_list::const_iterator ci = objects->begin(); ci != objects->end(); ci++) {
						const VAL::const_symbol* object = *ci;

						// bind object to parameter, save (partially) grounded prop
						if(isTypeOf(object->type, var->type)) {
							PDDLAtomicFormula newProp;
							copyFormula(prop, newProp);
							newProp.param_types.push_back(object->type->getName());
							newProp.param_names.push_back(object->getName());
							groundingProps.push_back(newProp);
						}
					}
				}
			}

			// save grounded props
			while(groundingProps.size()>0) {

				if(props.size()==MAX_BITSET) {
					std::cerr << "Too many grounded propositions. Increase MAX_BITSET." << std::endl;
					std::exit(0);
				}

				PDDLAtomicFormula prop = groundingProps.front();
				PDDLProposition newProp;
				copyFormula(prop, newProp.definition);

				std::stringstream ss;
				ss << prop.name;
				for(int i=0; i< prop.param_names.size(); i++)
					ss << "_" << prop.param_names[i];
				newProp.var_name = ss.str();
				props.push_back(newProp);
				newProp.index = (props.size()-1);
				string_prop_map[newProp.var_name] = (props.size()-1);
				pred_prop_map[prop.name].push_back(newProp);
				groundingProps.pop_front();
			}
		}
	}

	/*-------------------------------*/
	/* Discrete state representation */
	/*-------------------------------*/

	/** 
	 * save the discrete part of the initial state as a bitset
	 */
	void Grounder::parseInitialState(VAL::problem* problem) {

		initial_state.reset();
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
			initial_state.set(string_prop_map[ss.str()]);
		}
	}

	/*---------------------*/
	/* PDDL to SMT strings */
	/*---------------------*/

	/**
	 * parse a condition recursively. Condition types:
	 * simple_goal; qfied_goal;
	 * conj_goal; disj_goal; imply_goal;
	 * neg_goal; timed_goal; comparison;
	 */
	std::string Grounder::parseCondition(const VAL::goal* goal) {

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
			ss << parseExpression(co->getLHS()) << " " << parseExpression(co->getRHS()) << ")";
			return ss.str();
		}

		// negative condition
		const VAL::neg_goal* ng = dynamic_cast<const VAL::neg_goal*>(goal);
		if (ng) {
			ss << "(not " << parseCondition(ng->getGoal()) << ")";
			return ss.str();
		}

		// conjunctive condition
		const VAL::conj_goal* cg = dynamic_cast<const VAL::conj_goal*>(goal);
		if (cg) {
			ss << "(and";
		        const VAL::goal_list* goals = cg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				ss << " " << parseCondition((*ci));
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
				ss << " " << parseCondition((*ci));
			}
			ss << ")";
			return ss.str();
		}

		return "PARSING_ERROR";
	}

	/**
	 * parse a condition recursively, only retrieving a timed part
	 */
	std::string Grounder::parseTimedCondition(const VAL::goal* goal, VAL::time_spec part) {

		std::stringstream ss;

		// conjunctive condition
		const VAL::conj_goal* cg = dynamic_cast<const VAL::conj_goal*>(goal);
		if (cg) {
			ss << "(and";
		        const VAL::goal_list* goals = cg->getGoals();
		        for (VAL::goal_list::const_iterator ci = goals->begin(); ci != goals->end(); ci++) {
				std::string c = parseTimedCondition((*ci),part);
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
				std::string c = parseTimedCondition((*ci),part);
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
				return parseCondition(tg->getGoal());
			} else {
				return "";
			}
		}

		return "PARSING_ERROR";
	}

	/**
	 * parse an expression recursively.
	 */
	std::string Grounder::parseExpression(const VAL::expression* exp) {

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
			ss << "(- 0 " << parseExpression(ume->getExpr()) << ")";
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
			return ss.str();
		}

		// binary expressions
		const VAL::binary_expression* be = dynamic_cast<const VAL::binary_expression*>(exp);
		if (be) {
			std::string lhs = parseExpression(be->getLHS());
			std::string rhs = parseExpression(be->getRHS());

			// plus
			const VAL::plus_expression* pe = dynamic_cast<const VAL::plus_expression*>(exp);
			if (pe) ss << "(+ ";

			// minus
			const VAL::minus_expression* mie = dynamic_cast<const VAL::minus_expression*>(exp);
			if (mie) ss << "(- ";

			// multiply
			const VAL::mul_expression* mue = dynamic_cast<const VAL::mul_expression*>(exp);
			if (mue) ss << "(* ";

			// divide
			const VAL::div_expression* de = dynamic_cast<const VAL::div_expression*>(exp);
			if (de) ss << "(/ ";

			ss << lhs << " " << rhs << ")";
			return ss.str();
		}

		// "?duration"
		const VAL::special_val_expr* spe = dynamic_cast<const VAL::special_val_expr*>(exp);
		if (spe) {
			VAL::special_val val = spe->getKind();
			switch(val) {
			case VAL::E_HASHT: ss << "#t"; break;
			case VAL::E_DURATION_VAR: ss << "duration"; break;
			case VAL::E_TOTAL_TIME: ss << "total_time"; break;
			}
			return ss.str();
		}

		return "PARSING_ERROR";
	}

} // close namespace
