/**
 * This file describes the Encoder class. This class
 * is used to create encodings of a PDDL domain and 
 * problem pair.
 */
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>

#include "z3++.h"

#include "ptree.h"
#include "instantiation.h"
#include "VisitController.h"
#include "FastEnvironment.h"
#include "TIM.h"

#include "SMTPlan/Encoder.h"
#include "SMTPlan/PlannerOptions.h"
#include "SMTPlan/ProblemInfo.h"
#include "SMTPlan/Algebraist.h"

#ifndef KCL_encoder_fluent
#define KCL_encoder_fluent

namespace SMTPlan
{
	class EncoderFluent : public Encoder
	{
	private:

		/* encoding info */
		int upper_bound;
		int next_layer;
		int literal_bound;
		int next_literal_layer;
		std::vector<z3::expr> goal_expression;

		/* problem info */
		PlannerOptions * opt;
		ProblemInfo * problem_info;
		VAL::FastEnvironment * fe;
		VAL::analysis * val_analysis;
		Algebraist * algebraist;

		/* encoding state */
		int enc_litID;
		int enc_pneID;
		int enc_opID;
		int enc_tilID;
		std::string enc_op_string;

		bool enc_continuous;
		bool enc_cond_neg;
		bool enc_eff_neg;
		bool enc_make_op_vars;

		VAL::time_spec enc_cond_time;
		VAL::time_spec enc_eff_time;
		VAL::comparison_op enc_comparison_op;

		/* more encoding state */
		EncState enc_state;
		int enc_expression_h;
		int enc_expression_b;
		int enc_expression_l;
		std::vector<z3::expr> enc_expression_stack;

		std::vector<z3::expr> enc_musts_expression_stack;
		std::vector<z3::expr> enc_musts_discrete_stack;

		z3::expr_vector* enc_event_condition_stack;

		std::string enc_function_symbol;

		/* encoding information */
		std::vector<std::vector<int> > simpleEventAddEffects;
		std::vector<std::vector<int> > simpleEventDelEffects;
		std::vector<std::vector<int> > simpleStartAddEffects;
		std::vector<std::vector<int> > simpleStartDelEffects;
		std::vector<std::vector<int> > simpleEndAddEffects;
		std::vector<std::vector<int> > simpleEndDelEffects;
		std::vector<std::vector<int> > simpleTILAddEffects;
		std::vector<std::vector<int> > simpleTILDelEffects;
		std::map<int, std::vector<std::pair<int, z3::expr> > > simpleEventAssignEffects;
		std::map<int, std::vector<std::pair<int, z3::expr> > > simpleStartAssignEffects;
		std::map<int, std::vector<std::pair<int, z3::expr> > > simpleEndAssignEffects;
		std::map<int, std::vector<std::pair<int, z3::expr> > > simpleTILAssignEffects;
		std::vector<bool> initialState;
		std::vector<int> action_ids;


		/* SMT variables */
		std::vector<z3::expr> time_vars;
		std::vector<z3::expr> duration_vars;

		std::vector<std::vector<std::vector<z3::expr> > > event_cascade_literal_vars;
		std::vector<std::vector<z3::expr> > literal_time_vars;

		std::vector<std::vector<std::vector<z3::expr> > > event_cascade_function_vars;
		std::map<int, std::vector<std::vector<z3::expr>>> event_vars;
		std::map<int, std::vector<z3::expr> > sta_action_vars;
		std::map<int, std::vector<z3::expr> > end_action_vars;
		std::map<int, std::vector<z3::expr> > dur_action_vars;
		std::map<int, std::vector<z3::expr> > run_action_vars;
		std::map<int, std::vector<z3::expr> > til_vars;

		/* encoding methods */
		void encodeHeader(int H, int L);
		void encodeTimings(int H);
		void encodeLiteralVariableSupport(int H, int L);
		void encodeFunctionVariableSupport(int H);
		void encodeFunctionFlows(int H);
		void encodeGoalState(int H, int L);
		void encodeInitialState();

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

		z3::expr mk_expr(pexpr poly, int h, int b) {

			auto it = poly._container().begin();
			auto end = poly._container().end();
			auto args = poly.get_symbol_set();

			z3::expr flow = z3_context->real_val(0);
			for (; it != end;) {

				// rational coefficient of term
				std::stringstream ss;
				ss << it->m_cf;
				z3::expr coeff = z3_context->real_val(ss.str().c_str());

				// symbols
				for (int i = 0; i < it->m_key.size(); i++) {
					if (it->m_key[i] != pexpr(0)) {
						// default symbol: #t
						z3::expr sym = duration_vars[h];
						if(args[i].get_name() != "hasht") {
							if(algebraist->function_id_map.find(args[i].get_name()) == algebraist->function_id_map.end()) {
								// symbol: real value
								sym = z3_context->real_val(args[i].get_name().c_str());
							} else {
								// symbol: function name
								int fID = algebraist->function_id_map[args[i].get_name()];
								if(problem_info->staticFunctionMap[algebraist->predicate_head_map[fID]]) {
									sym = problem_info->staticFunctionValues.find(fID)->second;
								} else {
									sym = event_cascade_function_vars[fID][h][b];
								}
							}
						}
						z3::expr arg = sym;
						if (it->m_key[i] != pexpr(1))
							arg = z3::pw(arg, it->m_key[i]);
						coeff = (coeff * arg);
					}
				}
				++it;
				flow = (flow + coeff);
			}
			return flow;
		}

	public:

		EncoderFluent(Algebraist * alg, VAL::analysis* analysis, PlannerOptions &options, ProblemInfo &pi)
		{
			next_layer = 0;

			opt = &options;
			problem_info = &pi;
			val_analysis = analysis;
			algebraist = alg;

			enc_continuous = enc_cond_neg = enc_eff_neg = false;

			const int pneCount = Inst::instantiatedOp::howManyPNEs();
			const int litCount = Inst::instantiatedOp::howManyLiterals();

			simpleStartAddEffects = std::vector<std::vector<int> >(litCount);
			simpleStartDelEffects = std::vector<std::vector<int> >(litCount);
			simpleEventAddEffects = std::vector<std::vector<int> >(litCount);
			simpleEventDelEffects = std::vector<std::vector<int> >(litCount);
			simpleEndAddEffects = std::vector<std::vector<int> >(litCount);
			simpleEndDelEffects = std::vector<std::vector<int> >(litCount);
			simpleTILAddEffects = std::vector<std::vector<int> >(litCount);
			simpleTILDelEffects = std::vector<std::vector<int> >(litCount);

			initialState = std::vector<bool>(litCount);

			// for each [func|lit] : for each happening : for each cascade level
			event_cascade_function_vars = std::vector<std::vector<std::vector<z3::expr> > >(pneCount);
			event_cascade_literal_vars = std::vector<std::vector<std::vector<z3::expr> > >(litCount);
			literal_time_vars = std::vector<std::vector<z3::expr> >(litCount);

			z3::config cfg;
			cfg.set("auto_config", true);
			z3_context = new z3::context(cfg);
			z3_tactic = new z3::tactic(*z3_context, "qfnra-nlsat");
			z3_solver = new z3::solver(*z3_context, z3_tactic->mk_solver());
		}

		/* encoding methods */
		bool encode(int H);

		/*
		 * add goal expression to the model for printing.
		 * Usually the goal expression is only passed to the solver for checking.
		 */
		void addGoal() {
			std::vector<z3::expr>::iterator git = goal_expression.begin();
			for(; git != goal_expression.end(); git++) 
				z3_solver->add(*git);
		};

		/* visitor methods */
		virtual void visit_action(VAL::action * o);
		virtual void visit_durative_action(VAL::durative_action * da);

		virtual void visit_simple_goal(VAL::simple_goal *);
		virtual void visit_qfied_goal(VAL::qfied_goal *);
		virtual void visit_conj_goal(VAL::conj_goal *);
		virtual void visit_disj_goal(VAL::disj_goal *);
		virtual void visit_timed_goal(VAL::timed_goal *);
		virtual void visit_imply_goal(VAL::imply_goal *);
		virtual void visit_neg_goal(VAL::neg_goal *);

		virtual void visit_assignment(VAL::assignment * e);
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
		z3::check_result solve();
		void printModel();
	};

} // close namespace

#endif

