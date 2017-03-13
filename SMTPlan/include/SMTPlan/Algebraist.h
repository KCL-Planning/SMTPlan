/**
 * This file describes the Algebraist class.
 * This class uses a Computer Algebra System to perform the necessary
 * integration and differentiation of continuous change in the PDDL
 * domain, before the problem is encoded.
 */
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#include <piranha/piranha.hpp>
#include <piranha/math.hpp>

#include "ptree.h"
#include "instantiation.h"
#include "VisitController.h"
#include "FastEnvironment.h"
#include "TIM.h"

#include "SMTPlan/PlannerOptions.h"
#include "SMTPlan/ProblemInfo.h"

#ifndef KCL_algebraist
#define KCL_algebraist

// polynomials over R||Q
using pexpr = piranha::polynomial<piranha::rational,piranha::monomial<int>>;

namespace SMTPlan
{

	struct SingleFlow
	{
		std::set<int> operators;
		std::set<int> dependencies;
		std::vector<pexpr> derivatives;
		pexpr polynomial;
	};

	/*
	 * Describes the continuous change of a singe PDDL function
	 */
	class FunctionFlow
	{
		public:

		int f_id;
		pexpr function_var;
		std::string function_string;
		std::vector<SingleFlow> flows;
		bool integrated;

		~FunctionFlow() {}

		void addExpression(int opID, std::set<int> deps, pexpr &expr);
		void createChildren(std::map<int,FunctionFlow*> &allFlows);
		bool dependenciesResolved(std::map<int,FunctionFlow*> &allFlows);
		void integrate();
	};

	class Algebraist : public VAL::VisitController
	{
	public:

		std::map<int,FunctionFlow*> function_flow;
		std::map<std::string, int> function_id_map;
		std::map<int, std::string> predicate_head_map;

	private:

		enum AlgState
		{
			ALG_NONE,
			ALG_COLLECT_STATICS,
			ALG_PROCESS_FUNCTIONS
		};

		AlgState alg_state;

		/* problem info */
		PlannerOptions * opt;
		ProblemInfo * problem_info;
		VAL::FastEnvironment * fe;
		VAL::analysis * val_analysis;

		/* piranha environment */
		std::string alg_function_symbol;
		std::vector<pexpr> alg_expression_stack;
		std::set<int> alg_dependency_stack;

		std::map<int, pexpr> function_var;
		pexpr hasht{"hasht"};

		/* utility method */
		void checkFunction(Inst::PNE * const lit) {

			map<int,pexpr>::iterator fit = function_var.find(lit->getID());
			if(fit != function_var.end()) return;


			std::stringstream ss;
			ss << (*lit);
			pexpr fv = pexpr{ss.str()};			
			function_var[lit->getID()] = fv;
			function_id_map[ss.str()] = lit->getID();
			predicate_head_map[lit->getID()] = lit->getHead()->getName();

			map<int,FunctionFlow*>::iterator it = function_flow.find(lit->getID());
			if(it == function_flow.end()) {
				FunctionFlow* ff = new FunctionFlow();

				ff->function_var = function_var[lit->getID()];
				ff->function_string = ss.str();
				ff->f_id = lit->getID();
				ff->integrated = false;

				function_flow[lit->getID()] = ff;
			}
		};

	public:

		Algebraist(VAL::analysis* analysis, PlannerOptions &options, ProblemInfo &pi)
		{
			problem_info = &pi;
			val_analysis = analysis;
		}

		~Algebraist()
		{
			map<int,FunctionFlow*>::iterator it = function_flow.begin();
			for (; it != function_flow.end(); ++it) delete it->second;
		}

		/* encoding methods */
		bool processDomain();

		/* visitor methods */
		virtual void visit_durative_action(VAL::durative_action * da);

		virtual void visit_assignment(VAL::assignment * e);
		virtual void visit_forall_effect(VAL::forall_effect * e);
		virtual void visit_cond_effect(VAL::cond_effect * e);
		virtual void visit_timed_effect(VAL::timed_effect * e);
		virtual void visit_timed_initial_literal(VAL::timed_initial_literal * til);
		virtual void visit_effect_lists(VAL::effect_lists * e);

		virtual void visit_plus_expression(VAL::plus_expression * s);
		virtual void visit_minus_expression(VAL::minus_expression * s);
		virtual void visit_mul_expression(VAL::mul_expression * s);
		virtual void visit_div_expression(VAL::div_expression * s);
		virtual void visit_uminus_expression(VAL::uminus_expression * s);
		virtual void visit_int_expression(VAL::int_expression * s);
		virtual void visit_float_expression(VAL::float_expression * s);
		virtual void visit_special_val_expr(VAL::special_val_expr * s);
		virtual void visit_func_term(VAL::func_term * s);

		virtual void visit_preference(VAL::preference *);
		virtual void visit_event(VAL::event * e);
		virtual void visit_process(VAL::process * p);
		virtual void visit_derivation_rule(VAL::derivation_rule * o);
	};

} // close namespace

#endif

