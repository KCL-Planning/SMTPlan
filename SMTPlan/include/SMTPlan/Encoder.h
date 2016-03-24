/**
 * This file describes the parser.
 */
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>

#include"z3++.h"

#include "ptree.h"
#include "instantiation.h"
#include "VisitController.h"
#include "FastEnvironment.h"
#include "TIM.h"

#include "SMTPlan/PlannerOptions.h"
#include "SMTPlan/ProblemInfo.h"

#ifndef KCL_encoder
#define KCL_encoder

namespace SMTPlan
{

	enum EncState
	{
		ENC_NONE,
		ENC_INIT,
		ENC_GOAL,
		ENC_LITERAL,
		ENC_ACTION_CONDITION,
		ENC_ACTION_DURATION,
		ENC_ACTION_EFFECT
	};

	class Encoder : public VAL::VisitController
	{
	private:

		std::ostream * out;
		PlannerOptions * opt;
		VAL::FastEnvironment * fe;
		ProblemInfo * problem_info;

		/* encoding state */
		EncState enc_state;
		int enc_expression_h;
		std::vector<z3::expr> enc_expression_stack;
		std::string enc_function_symbol;

		/* encoding information */
		std::vector<std::vector<int> > simpleStartAddEffects;
		std::vector<std::vector<int> > simpleStartDelEffects;
		std::vector<std::vector<int> > simpleEndAddEffects;
		std::vector<std::vector<int> > simpleEndDelEffects;
		std::vector<bool> initialState;

		/* SMT variables */
		std::vector<z3::expr> time_vars;
		std::vector<z3::expr> duration_vars;
		std::vector<std::vector<z3::expr> > pre_function_vars;
		std::vector<std::vector<z3::expr> > pos_function_vars;
		std::vector<std::vector<z3::expr> > pre_literal_vars;
		std::vector<std::vector<z3::expr> > pos_literal_vars;
		std::vector<std::vector<z3::expr> > sta_action_vars;
		std::vector<std::vector<z3::expr> > end_action_vars;
		std::vector<std::vector<z3::expr> > dur_action_vars;
		std::vector<std::vector<z3::expr> > run_action_vars;

		/* encoding methods */
		void encodeHeader(int H);
		void encodeTimings(int H);
		void encodeLiteralVariableSupport(int H);
		void encodeFunctionVariableSupport(int H);
		void encodeGoalState(VAL::analysis* analysis, int H);
		void encodeInitialState(VAL::analysis* analysis);

		void parseExpression(VAL::expression * e);

		/* internal encoding methods */
		z3::expr mk_or(z3::expr_vector args) {
			std::vector<Z3_ast> array;
			for (unsigned i = 0; i < args.size(); i++) array.push_back(args[i]);
			return z3::to_expr(args.ctx(), Z3_mk_or(args.ctx(), array.size(), &(array[0])));
		}

		z3::expr mk_and(z3::expr_vector args) {
			std::vector<Z3_ast> array;
			for (unsigned i = 0; i < args.size(); i++) array.push_back(args[i]);
			return z3::to_expr(args.ctx(), Z3_mk_and(args.ctx(), array.size(), &(array[0])));
		}

	public:

		/* setup methods */
		void setOutput(std::ostream &o);

		/* encoding methods */
		bool encode(VAL::analysis* analysis, PlannerOptions &options, ProblemInfo &pi, int H);

		virtual void visit_action(VAL::action * o);
		virtual void visit_durative_action(VAL::durative_action * da);

		virtual void visit_simple_goal(VAL::simple_goal *);
		virtual void visit_qfied_goal(VAL::qfied_goal *);
		virtual void visit_conj_goal(VAL::conj_goal *);
		virtual void visit_disj_goal(VAL::disj_goal *);
		virtual void visit_timed_goal(VAL::timed_goal *);
		virtual void visit_imply_goal(VAL::imply_goal *);
		virtual void visit_neg_goal(VAL::neg_goal *);

		virtual void visit_simple_effect(VAL::simple_effect * e);
		virtual void visit_forall_effect(VAL::forall_effect * e);
		virtual void visit_cond_effect(VAL::cond_effect * e);
		virtual void visit_timed_effect(VAL::timed_effect * e);
		virtual void visit_timed_initial_literal(VAL::timed_initial_literal * til);
		virtual void visit_effect_lists(VAL::effect_lists * e);

		virtual void visit_comparison(VAL::comparison *);
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

		/* solving */
		z3::context * z3_context;
		z3::solver * z3_solver;
		z3::check_result solve();
		void printModel();
	};

} // close namespace

#endif

