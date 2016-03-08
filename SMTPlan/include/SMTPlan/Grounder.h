/**
 * This file describes the grounder.
 */
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>

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

	class Grounder
	{
	private:

		void groundProps(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options);
		void groundFluents(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options);
		void groundActions(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options);
		void copyFormula(PDDLAtomicFormula &oldProp, PDDLAtomicFormula &newProp);

	public:

		/* constructor */
		Grounder() : grounded(false) {}

		/* grounded problem */
		std::vector<PDDLAtomicFormula> props;
		std::vector<PDDLAtomicFormula> fluents;
		std::vector<PDDLAtomicFormula> actions;

		/* maps */
		std::map<std::string,std::vector<PDDLAtomicFormula> > action_map;

		/* grounding method */
		bool grounded;
		bool ground(VAL::domain* domain, VAL::problem* problem, PlannerOptions &options);
	};

} // close namespace

#endif

