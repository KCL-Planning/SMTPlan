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

#include "SMTPlan/PlannerOptions.h"
#include "SMTPlan/ProblemInfo.h"
#include "SMTPlan/Algebraist.h"

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
		ENC_ACTION_EFFECT,
		ENC_SIMPLE_ACTION_CONDITION,
		ENC_SIMPLE_ACTION_EFFECT,
		ENC_TIL_EFFECT,
		ENC_EVENT_CONDITION,
		ENC_EVENT_EFFECT,
		ENC_PROCESS_CONDITION
	};

	class Encoder : public VAL::VisitController
	{
	private:
	public:

		/* encoding methods */
		virtual bool encode(int H) =0;

		/*
		 * add goal expression to the model for printing.
		 * Usually the goal expression is only passed to the solver for checking.
		 */
		virtual void addGoal() =0;

		/* solving */
		z3::context * z3_context;
		z3::tactic * z3_tactic;
		z3::solver * z3_solver;
		virtual z3::check_result solve() =0;
		virtual void printModel() =0;
	};

} // close namespace

#endif

