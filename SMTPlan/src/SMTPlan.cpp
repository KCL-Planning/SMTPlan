/**
 * This file implements the main method of SMTPlan.
 */

#include "SMTPlanConfig.h"
#include "SMTPlan/PlannerOptions.h"
#include "SMTPlan/Encoder.h"

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

int number_of_arguments = 6;
SMTPlan::Argument argument[] = {
	{"-h",	false,	"\tPrint this and exit."},
	{"-l",	true,	"number\tBegin iterative deepening at an encoding with l happenings (default 1)."},
	{"-u",	true,	"number\tRun iterative deepening until the u is reached. Set -1 for unlimited (default -1)."},
	{"-s",	true,	"number\tIteratively deepen with a step size of s (default 1)."},
	{"-o",	false,	"\tOutput encoding in smt2 format."},
	{"-n",	false,	"\tDo not solve. Generate encoding and exit."},
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
	options.encoding_path = "";

	// defaults
	options.solve = true;
	options.lower_bound = 1;
	options.upper_bound = -1;
	options.step_size = 1;

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
			} else if(argument[j].name == "-s") {
				options.step_size = atoi(argv[i]);
			} else if(argument[j].name == "-o") {
				options.encoding_path = "true";
			} else if(argument[j].name == "-n") {
				options.solve = false;
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

	// parse domain and problem
	TIM::performTIMAnalysis(&argv[1]);
	Inst::SimpleEvaluator::setInitialState();
	VAL::operator_list::const_iterator os = VAL::current_analysis->the_domain->ops->begin();
    for(; os != VAL::current_analysis->the_domain->ops->end(); ++os) {
    	Inst::instantiatedOp::instantiate(*os, VAL::current_analysis->the_problem, *VAL::theTC);
    };
    Inst::instantiatedOp::createAllLiterals(VAL::current_analysis->the_problem, VAL::theTC);
    Inst::instantiatedOp::filterOps(VAL::theTC);

	fprintf(stdout,"Grounded:\t%f seconds\n", getElapsed());

	// begin search loop
	for(int i=options.lower_bound; (options.upper_bound<0 || i<=options.upper_bound); i+=options.step_size) {

		// generate encoding
		SMTPlan::Encoder encoder;
		encoder.encode(VAL::current_analysis, options, i);
		fprintf(stdout,"Encoded %i:\t%f seconds\n", i, getElapsed());

		// output to file
		std::ofstream pFile;
		if(options.encoding_path != "") {
			std::cout << encoder.z3_solver->to_smt2() << std::endl;
			return 0;
		}

		// solve
		if(options.encoding_path == "") {
			z3::check_result result = encoder.solve();
			if(result == z3::sat) {
				encoder.printModel();
				fprintf(stdout,"Solved %i:\t%f seconds\n", i, getElapsed());
				fprintf(stdout,"Total time:\t%f seconds\n", getTotalElapsed());
				return 0;
			}
			delete encoder.z3_solver;
		} else {
			// close file if open
			if (!pFile.is_open()) pFile.close();

			if(system("z3 test.smt2 | paste -sd ' \n' | egrep 'true|duration' | egrep 'sta|duration'") == 0) {
				fprintf(stdout,"Solved %i:\t%f seconds\n", i, getElapsed());
				fprintf(stdout,"Total time:\t%f seconds\n", getTotalElapsed());
				return 0;
			}
		}

		fprintf(stdout,"Solved %i:\t%f seconds\n", i, getElapsed());

	}

	fprintf(stdout, "No plan found in %i happenings\n", options.upper_bound);
	fprintf(stdout, "Total time:\t%f seconds\n", getTotalElapsed());

	return 0;
}
