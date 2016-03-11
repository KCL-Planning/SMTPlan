/**
 * This file describes the grounder.
 */
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>
#include <bitset>
#include <boost/regex.hpp>

#include "SMTPlan/PlannerOptions.h"

#include "ptree.h"

#ifndef KCL_grounder
#define KCL_grounder

namespace SMTPlan
{
	struct PDDLAtomicFormula
	{
		// SMT
		std::string var_name;

		// PDDL
		std::string name;
		std::vector<string> param_types;
		std::vector<string> param_names;
	};

	struct PDDLProposition
	{
		std::vector<PDDLProposition>::size_type index;

		// SMT
		std::string var_name;

		// PDDL
		PDDLAtomicFormula definition;
		std::map<std::string,std::string> param_object;

		// representation of discrete part
		std::bitset<MAX_BITSET> sta_add_actions;
		std::bitset<MAX_BITSET> sta_del_actions;
		std::bitset<MAX_BITSET> end_add_actions;
		std::bitset<MAX_BITSET> end_del_actions;

		std::bitset<MAX_BITSET> sta_condition_actions;
		std::bitset<MAX_BITSET> end_condition_actions;
		std::bitset<MAX_BITSET> dur_condition_actions;

	};

	struct PDDLDurativeAction
	{
		std::vector<PDDLDurativeAction>::size_type index;

		// SMT
		std::string var_name;
		std::string unground_duration;

		// PDDL
		PDDLAtomicFormula definition;
		std::map<std::string,std::string> param_object;

		// representation of discrete part
		std::bitset<MAX_BITSET> sta_simple_add_effects;
		std::bitset<MAX_BITSET> sta_simple_del_effects;
		std::bitset<MAX_BITSET> end_simple_add_effects;
		std::bitset<MAX_BITSET> end_simple_del_effects;

		std::bitset<MAX_BITSET> sta_simple_conditions;
		std::bitset<MAX_BITSET> dur_simple_conditions;
		std::bitset<MAX_BITSET> end_simple_conditions;
	};

	class Grounder
	{
	private:

		void findReplace(std::string &subject, std::map<std::string, std::string> &replaceMap) {
			std::map<std::string, std::string>::iterator mit = replaceMap.begin();
			for(; mit!=replaceMap.end(); mit++) {
				std::stringstream ss1, ss2;
				ss1 << "_" << mit->first << "([_\\) ]|\\z)";
				ss2 << "_" << mit->second << "\\1";
				boost::regex re(ss1.str(), boost::regex::icase);
				subject = boost::regex_replace(subject, re, ss2.str());
			}
		}

		bool isTypeOf(const VAL::pddl_type* a, const VAL::pddl_type* b);

		std::string parseExpression(const VAL::expression* exp);
		std::string parseCondition(const VAL::goal* goal);
		std::string parseTimedCondition(const VAL::goal* goal, VAL::time_spec part);

		void groundProps(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options);
		void groundFluents(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options);
		void groundActions(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options);

		void groundActionConditions(VAL::domain* domain, VAL::problem* problem, const VAL::operator_* op, PDDLDurativeAction &action);
		void groundActionEffects(VAL::domain* domain, VAL::problem* problem, const VAL::operator_* op, PDDLDurativeAction &action);
		void groundActionDuration(VAL::domain* domain, VAL::problem* problem, const VAL::operator_* op, PDDLDurativeAction &action);

		void groundTimedActionCondition(PDDLDurativeAction &action, const VAL::goal* goal, VAL::time_spec part);
		void groundActionCondition(PDDLDurativeAction &action, const VAL::goal* goal);

		void copyFormula(PDDLAtomicFormula &oldProp, PDDLAtomicFormula &newProp);
		void copyDurativeAction(PDDLDurativeAction &oldact, PDDLDurativeAction &newact);

	public:

		/* constructor */
		Grounder() : grounded(false) {}

		/* grounded problem */
		std::vector<PDDLProposition> props;
		std::vector<PDDLAtomicFormula> fluents;
		std::vector<PDDLDurativeAction> actions;

		/* bitsets */
		std::bitset<MAX_BITSET> initial_state;

		/* maps */
		std::map<std::string,std::vector<PDDLProposition> > pred_prop_map;
		std::map<std::string,std::vector<PDDLDurativeAction> > op_action_map;
		std::map<std::string,std::vector<PDDLProposition>::size_type> string_prop_map;

		/* grounding method */
		bool grounded;
		bool ground(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options);
		void parseInitialState(VAL::problem* problem);
	};

} // close namespace

#endif

