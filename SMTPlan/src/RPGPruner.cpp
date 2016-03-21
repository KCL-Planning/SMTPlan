#include "SMTPlan/RPGPruner.h"

/* implementation of SMTPlan::RPGPruner */
namespace SMTPlan {
	
	/**
	 * builds the Relaxed Plan Graph for the grounded problem until a fix point
	 */
	bool RPGPruner::build(Grounder &grounder, PlannerOptions &options) {

		goal_layer = -1;
		bool finished = false;

		while(!finished) {
			finished = !buildLayer(grounder, options);
		}

		// printRPG(grounder, options);
		if(options.prune) {
			prune(grounder);
		}
	}

	/**
	 * prune away the unreachable state from the grounder
	 */
	void RPGPruner::prune(Grounder &grounder) {
		
		if(action_layers.size()==0 || fact_layers.size()==0)
			return;

		grounder.op_action_map.clear();
		grounder.string_prop_map.clear();
		grounder.pred_prop_map.clear();

		std::vector<PDDLProposition> newProps;
		std::vector<PDDLDurativeAction> newActions;
		
		// loop through actions
		std::vector<PDDLDurativeAction>::iterator ait = grounder.actions.begin();
		for(; ait!=grounder.actions.end(); ait++) {
			PDDLDurativeAction action = (*ait);
			if(action_layers.back().test(action.index)) {
				action_index_map[action.index] = newActions.size();
				action.index = newActions.size();
				newActions.push_back(action);
				grounder.op_action_map[action.definition.name].push_back(action);
			}
		}

		// loop through facts
		std::vector<PDDLProposition>::iterator pit = grounder.props.begin();
		for(; pit!=grounder.props.end(); pit++) {
			PDDLProposition prop = (*pit);
			if(fact_layers.back().test(prop.index)) {
				prop_index_map[prop.index] = newProps.size();
				prop.index = newProps.size();
				newProps.push_back(prop);
				grounder.string_prop_map[prop.var_name] = (newProps.size()-1);
				grounder.pred_prop_map[prop.definition.name].push_back(prop);
			}
		}

		// fix bitset references in actions
		ait = newActions.begin();
		for(; ait!=newActions.end(); ait++) {
			PDDLDurativeAction action = (*ait);
			
			std::bitset<MAX_BITSET> sae, sde, eae, ede, sc, dc, ec;
			for(int i=0;i<grounder.props.size();i++) {

				if(fact_layers.size()>0 && !fact_layers.back().test(i)) continue;

				if(action.sta_simple_add_effects.test(i)) sae.set(prop_index_map[i]);
				if(action.sta_simple_del_effects.test(i)) sde.set(prop_index_map[i]);
				if(action.end_simple_add_effects.test(i)) eae.set(prop_index_map[i]);
				if(action.end_simple_del_effects.test(i)) ede.set(prop_index_map[i]);

				if(action.sta_simple_conditions.test(i)) sc.set(prop_index_map[i]);
				if(action.dur_simple_conditions.test(i)) dc.set(prop_index_map[i]);
				if(action.end_simple_conditions.test(i)) ec.set(prop_index_map[i]);
			}

			ait->sta_simple_add_effects = sae;
			ait->sta_simple_del_effects = sde;
			ait->end_simple_add_effects = eae;
			ait->end_simple_del_effects = ede;

			ait->sta_simple_conditions = sc;
			ait->dur_simple_conditions = dc;
			ait->end_simple_conditions = ec;
		}

		// fix bitset references in props
		pit = newProps.begin();
		for(; pit!=newProps.end(); pit++) {
			PDDLProposition prop = (*pit);
			std::bitset<MAX_BITSET> saa, sda, eaa, eda, sca, dca, eca;
			for(int i=0;i<grounder.actions.size();i++) {

				if(action_layers.size()>0 && !action_layers.back().test(i)) continue;

				if(prop.sta_add_actions.test(i)) saa.set(action_index_map[i]);
				if(prop.sta_del_actions.test(i)) sda.set(action_index_map[i]);
				if(prop.end_add_actions.test(i)) eaa.set(action_index_map[i]);
				if(prop.end_del_actions.test(i)) eda.set(action_index_map[i]);

				if(prop.sta_condition_actions.test(i)) sca.set(action_index_map[i]);
				if(prop.dur_condition_actions.test(i)) dca.set(action_index_map[i]);
				if(prop.end_condition_actions.test(i)) eca.set(action_index_map[i]);
			}

			pit->sta_add_actions = saa;
			pit->sta_del_actions = sda;
			pit->end_add_actions = eaa;
			pit->end_del_actions = eda;

			pit->sta_condition_actions = sca;
			pit->dur_condition_actions = dca;
			pit->end_condition_actions = eca;
		}
		
		// fix bitset refs in initial state and goal
		std::bitset<MAX_BITSET> is, gs;
		for(int i=0; i<grounder.props.size(); i++) {
			if(grounder.initial_state.test(i)) is.set(prop_index_map[i]);
			if(grounder.simple_goal_state.test(i)) gs.set(prop_index_map[i]);
		}
		grounder.initial_state = is;
		grounder.simple_goal_state = gs;
	
		std::cout << "pruned:" <<std::endl;
		std::cout << (grounder.actions.size() - newActions.size()) << " actions" <<std::endl;
		std::cout << (grounder.props.size() - newProps.size()) << " props" <<std::endl;

		grounder.props = newProps;
		grounder.actions = newActions;
	}

	/**
	 * print the nice RPG
	 */
	void RPGPruner::printRPG(Grounder &grounder, PlannerOptions &options) {

		// loop through facts
		std::cout << "INITIAL STATE:" << std::endl;
		for(int i=0;i<grounder.props.size();i++) {
			if(grounder.initial_state.test(i)) {
				std::cout << " " << grounder.props[i].var_name << std::endl;
			}
		}

		for(int i=0; i<action_layers.size(); i++) {

			std::cout << std::endl;

			// loop through actions
			std::cout << "ACTIONS:" << std::endl;
			std::vector<PDDLDurativeAction>::iterator ait = grounder.actions.begin();
			for(; ait!=grounder.actions.end(); ait++) {
				PDDLDurativeAction action = (*ait);
				if(action_layers[i].test(action.index))
					std::cout << " " << action.var_name << std::endl;
			}

			// loop through facts
			std::cout << "FACTS:" << std::endl;
			std::vector<PDDLProposition>::iterator pit = grounder.props.begin();
			for(; pit!=grounder.props.end(); pit++) {
				PDDLProposition prop = (*pit);
				if(fact_layers[i].test(prop.index))
					std::cout << " " << prop.var_name << std::endl;
			}
		}

	}

	/**
	 * add a layer to the tree
	 * return if there is a change
	 */
	bool RPGPruner::buildLayer(Grounder &grounder, PlannerOptions &options) {

		bool change = false;

		std::bitset<MAX_BITSET> actionLayer;
		std::bitset<MAX_BITSET> factLayer;

		std::bitset<MAX_BITSET>* prevActionLayer;
		std::bitset<MAX_BITSET>* prevFactLayer;

		if(action_layers.size()>0) {
			prevActionLayer = &action_layers.back();
			prevFactLayer = &fact_layers.back();
		} else {
			prevFactLayer = &grounder.initial_state;
		}

		// add existing facts
		factLayer = (*prevFactLayer);

		// loop through actions
		std::vector<PDDLDurativeAction>::iterator ait = grounder.actions.begin();
		for(; ait!=grounder.actions.end(); ait++) {
			PDDLDurativeAction action = (*ait);

			if(action_layers.size()>0 && prevActionLayer->test(action.index)) {

				// add existing actions
				actionLayer.set(action.index);

			} else {

				// test action conditions			
				bool precAchieved = 
					((action.sta_simple_conditions & *prevFactLayer) ^ (action.sta_simple_conditions)).none()
					&& ((action.dur_simple_conditions & *prevFactLayer) ^ (action.dur_simple_conditions)).none();
				if(precAchieved) {

					// add new action to layer
					actionLayer.set(action.index);
					change = true;

					// add action's effects to new fact layer
					factLayer = factLayer | action.sta_simple_add_effects | action.end_simple_add_effects;
				}
			}
		}

		// save new layers
		action_layers.push_back(actionLayer);
		fact_layers.push_back(factLayer);

		// check for goal
		if(goal_layer<0 && ((grounder.simple_goal_state & factLayer) ^ (grounder.simple_goal_state)).none()) {
			goal_layer = fact_layers.size();
		}

		return change;
	}

} // close namespace

