/**
 * This file implements the main method of SMTPlan.
 */
#include "SMTPlanConfig.h"
#include "SMTPlan/PlannerOptions.h"
#include "SMTPlan/ProblemInfo.h"
#include "SMTPlan/Encoder.h"
#include "SMTPlan/EncoderHappening.h"
#include "SMTPlan/EncoderFluent.h"
#include "SMTPlan/Algebraist.h"

#include <ctime>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>
#include <fstream>

#include <FlexLexer.h>

#include "ptree.h"
#include "instantiation.h"
#include "SimpleEval.h"
#include "DebugWriteController.h"
#include "typecheck.h"
#include "TIM.h"

int number_of_arguments = 9;
SMTPlan::Argument argument[] = {
	{"-h",	false,	"\tPrint this and exit."},
	{"-l",	true,	"number\tBegin iterative deepening at an encoding with l happenings (default 1)."},
	{"-u",	true,	"number\tRun iterative deepening until the u is reached. Set -1 for unlimited (default -1)."},
	{"-c",	true,	"number\tLimit the length of the concurrent cascading event and action chain (default 2, minimum 2)."},
	{"-e",	true,	"number\tChoose which encoding to use:\n\t\t\t0\tHappening-based encoding described in the paper (default)"},
	{"-s",	true,	"number\tIteratively deepen with a step size of s (default 1)."},
	{"-n",	false,	"\tDo not solve. Output encoding in smt2 format and exit."},
	{"-v",	false,	"\tVerbose times."},
	{"-d",	false,	"\tDebug output."}
};

void printUsage(char* arg) {
	fprintf(stdout,"Usage: %s domain problem [options]\n",arg);
	fprintf(stdout,"Options:\n");
	for(int i=0; i<number_of_arguments; i++) {
		fprintf(stdout,"\t%s\t%s\n", argument[i].name.c_str(), argument[i].help.c_str());
	}
	fprintf(stdout,"Example: %s domain.pddl problem.pddl -l 4 -u 10 -s 2\n", arg);
}

/*---------------------------*/
/* parsing program arguments */
/*---------------------------*/

bool parseArguments(int argc, char *argv[], SMTPlan::PlannerOptions &options) {
	
	// file paths
	options.domain_path = argv[1];
	options.problem_path = argv[2];

	// defaults
	options.verbose = false;
	options.debug = false;
	options.solve = true;
	options.lower_bound = 1;
	options.upper_bound = -1;
	options.cascade_bound = 2;
	options.step_size = 1;
	options.encoder = 0;

	// read arguments
	for(int i=3;i<argc; i++) {

		bool argumentFound = false;
		for(int j=0; j<number_of_arguments; j++) {

			// find argument type
			if(argument[j].name != argv[i]) continue;
			argumentFound = true;

			// check if value is present
			if(argument[j].has_value) {
				i++;
				if(i==argc) {
					fprintf(stdout,"\nExpected value for option %s\n\n", argv[i-1]);
					return false;
				}
			}
			
			// set options
			if(argument[j].name == "-h") {
				return false;
			} else if(argument[j].name == "-l") {
				options.lower_bound = atoi(argv[i]);
			} else if(argument[j].name == "-u") {
				options.upper_bound = atoi(argv[i]);
			} else if(argument[j].name == "-c") {
				options.cascade_bound = atoi(argv[i]);
				if(options.cascade_bound < 2) options.cascade_bound = 2;
			} else if(argument[j].name == "-s") {
				options.step_size = atoi(argv[i]);
			} else if(argument[j].name == "-n") {
				options.solve = false;
			} else if(argument[j].name == "-v") {
				options.verbose = true;
			} else if(argument[j].name == "-d") {
				options.debug = true;
			} else if(argument[j].name == "-e") {
				options.encoder = atoi(argv[i]);
			}
		}
		if(!argumentFound) {
			std::cerr << "Unrecognised argument: " << argv[i] << std::endl;
			return false;
		}
	}

	return true;
}

/*-------*/
/* timer */
/*-------*/

std::clock_t last;

double getElapsed() {

    double duration = ( std::clock() - last ) / (double) CLOCKS_PER_SEC;
    last = std::clock();
	return duration;
}

double getTotalElapsed() {

    double duration = ( std::clock() ) / (double) CLOCKS_PER_SEC;
	return duration;
}

/*-------------*/
/* main method */
/*-------------*/

int main (int argc, char *argv[]) {

	// check arguments
	if (argc < 3) {
		printUsage(argv[0]);
		return 1;
	}

	// parse arguments
	SMTPlan::PlannerOptions options;
	if(!parseArguments(argc,argv, options)) {
		printUsage(argv[0]);
		return 1;
	}

    getElapsed();


	SMTPlan::ProblemInfo pi;

	// parse domain and problem
	TIM::performTIMAnalysis(&argv[1]);
	Inst::SimpleEvaluator::setInitialState();
	VAL::operator_list::const_iterator os = VAL::current_analysis->the_domain->ops->begin();
    for(; os != VAL::current_analysis->the_domain->ops->end(); ++os) {
    	Inst::instantiatedOp::instantiate(*os, VAL::current_analysis->the_problem, *VAL::theTC);
    };
    Inst::instantiatedOp::createAllLiterals(VAL::current_analysis->the_problem, VAL::theTC);
    Inst::instantiatedOp::filterOps(VAL::theTC);

	// save static predicates
	if(VAL::current_analysis->the_domain->predicates) {
		VAL::pred_decl_list* predicates = VAL::current_analysis->the_domain->predicates;
		for (VAL::pred_decl_list::const_iterator ci = predicates->begin(); ci != predicates->end(); ci++) {
			VAL::holding_pred_symbol * hps = HPS((*ci)->getPred());
			bool isStatic = true;
			for(VAL::holding_pred_symbol::PIt i = hps->pBegin();i != hps->pEnd();++i) {
				TIM::TIMpredSymbol * tps = const_cast<TIM::TIMpredSymbol *>(static_cast<const TIM::TIMpredSymbol*>(*i));
				if(!tps->isDefinitelyStatic() || !tps->isStatic()) {
					isStatic = false;
					break;
				}
			}
			pi.staticPredicateMap[hps->getName()] = isStatic;
		}
	}

	// save static functions
	if(VAL::current_analysis->the_domain->functions) {
		VAL::func_decl_list* functions = VAL::current_analysis->the_domain->functions;
		for (VAL::func_decl_list::const_iterator ci = functions->begin(); ci != functions->end(); ci++) {
			VAL::extended_func_symbol * efs = static_cast<VAL::extended_func_symbol*>(const_cast<VAL::func_symbol*>((*ci)->getFunction()));
			pi.staticFunctionMap[efs->getName()] = efs->isStatic();
		}
	}

	if(options.verbose) fprintf(stdout,"Grounded:\t%f seconds\n", getElapsed());

	// calculate boundary expressions for continuous change
	SMTPlan::Algebraist algebraist(VAL::current_analysis, options, pi);
	algebraist.processDomain();

	if(options.verbose) fprintf(stdout,"Algebra:\t%f seconds\n", getElapsed());

	// begin search loop
	SMTPlan::Encoder* encoder;
	if(options.encoder == 0) {
		encoder = new SMTPlan::EncoderHappening(&algebraist, VAL::current_analysis, options, pi);
	} else if(options.encoder == 1) {
		encoder = new SMTPlan::EncoderFluent(&algebraist, VAL::current_analysis, options, pi);
	} else {
		fprintf(stdout,"Uknown encoding selected.\n");
		return 0;
	}

	for(int i=options.lower_bound; (options.upper_bound<0 || i<=options.upper_bound); i+=options.step_size) {

		// generate encoding
		encoder->encode(i);
		if(options.verbose) fprintf(stdout,"Encoded %i:\t%f seconds\n", i, getElapsed());

		// output to file
		std::ofstream pFile;
		if(!options.solve) {
			// add the goal to the model
			encoder->addGoal();
			// print model
			std::cout << encoder->z3_solver->to_smt2() << std::endl;
			return 0;
		}

		// solve
		z3::check_result result = encoder->solve();

		if(result == z3::sat) {
			encoder->printModel();
			if(options.verbose) {
				fprintf(stdout,"Solved %i:\t%f seconds\n", i, getElapsed());
				fprintf(stdout,"Total time:\t%f seconds\n", getTotalElapsed());
			}
			delete encoder;
			return 0;
		}

		if(options.verbose) fprintf(stdout,"Solved %i:\t%f seconds\n", i, getElapsed());

	}

	fprintf(stdout, "No plan found in %i happenings\n", options.upper_bound);
	if(options.verbose) fprintf(stdout, "Total time:\t%f seconds\n", getTotalElapsed());

	//delete *encoder;

	return 0;
}
