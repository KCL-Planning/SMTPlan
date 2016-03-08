#include "SMTPlan/Grounder.h"

/* implementation of SMTPlan::Grounder */
namespace SMTPlan {

	// ground out problem and store
	bool Grounder::ground(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options) {

		if(grounded) return true;

		groundProps(domain, problem, options);
		groundFluents(domain, problem, options);
		groundActions(domain, problem, options);

		grounded = true;
		return true;
	}

	// copy one (partial) PDDLAtomicFormula into another (proposition, fluent, or action signiature)
	void Grounder::copyFormula(PDDLAtomicFormula &oldProp, PDDLAtomicFormula &newProp) {
		newProp.name = oldProp.name;
		for(int i=0; i<oldProp.param_types.size(); i++) {
			newProp.param_types.push_back(oldProp.param_types[i]);
			newProp.param_names.push_back(oldProp.param_names[i]);
		}
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

			PDDLAtomicFormula action;
			action.name = op->name->symbol::getName();
			std::deque<PDDLAtomicFormula> groundingActions;
			groundingActions.push_back(action);

			for (VAL::var_symbol_list::const_iterator vi = op->parameters->begin(); vi != op->parameters->end(); vi++) {
				const VAL::var_symbol* var = *vi;

				// for each partially grounded prop
				int propCount = groundingActions.size();
				for(int i=0; i<propCount; i++) {
					action = groundingActions.front();
					groundingActions.pop_front();

					//for each object
					VAL::const_symbol_list* objects = problem->objects;
					for (VAL::const_symbol_list::const_iterator ci = objects->begin(); ci != objects->end(); ci++) {
						const VAL::const_symbol* object = *ci;

						// bind object to parameter, save (partially) grounded action
						if(object->type->getName() == var->type->getName()) {
							PDDLAtomicFormula newAction;
							copyFormula(action, newAction);
							newAction.param_types.push_back(object->type->getName());
							newAction.param_names.push_back(object->getName());
							groundingActions.push_back(newAction);
						}
					}
				}
			}

			// save grounded actions
			while(groundingActions.size()>0) {
				PDDLAtomicFormula action = groundingActions.front();
				
				std::stringstream ss;
				if(options.explanatory_var_names) {
					ss << action.name;
					for(int i=0; i< action.param_names.size(); i++)
						ss << "_" << action.param_names[i];
				} else {
					ss << "p" << actions.size();
				}
				action.var_name = ss.str();
				actions.push_back(action);
				if(action_map.find(action.name)==action_map.end())
					action_map[action.name];
				action_map[action.name].push_back(action);
				groundingActions.pop_front();
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
						if(object->type->getName() == var->type->getName()) {
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
				PDDLAtomicFormula fluent = groundingFluents.front();
				
				std::stringstream ss;
				if(options.explanatory_var_names) {
					ss << fluent.name;
					for(int i=0; i< fluent.param_names.size(); i++)
						ss << "_" << fluent.param_names[i];
				} else {
					ss << "p" << fluents.size();
				}
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
						if(object->type->getName() == var->type->getName()) {
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
				PDDLAtomicFormula prop = groundingProps.front();
				
				std::stringstream ss;
				if(options.explanatory_var_names) {
					ss << prop.name;
					for(int i=0; i< prop.param_names.size(); i++)
						ss << "_" << prop.param_names[i];
				} else {
					ss << "p" << props.size();
				}
				prop.var_name = ss.str();
				props.push_back(prop);
				groundingProps.pop_front();
			}
		}
	}
} // close namespace
