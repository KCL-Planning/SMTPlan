/**
 * This file implements the main method of SMTPlan.
 */

#include "SMTPlanConfig.h"
#include "SMTPlan/PlannerOptions.h"

#include "SMTPlan/Parser.h"
#include "SMTPlan/Grounder.h"
#include "SMTPlan/Encoder.h"

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <string>


int number_of_arguments = 7;
SMTPlan::Argument argument[] = {
	{"-h",	false,	"\tPrint this and exit."},
	{"-l",	true,	"number\tBegin iterative deepening at an encoding with l happenings (default 1)."},
	{"-u",	true,	"number\tRun iterative deepening until the u is reached. Set -1 for unlimited (default -1)."},
	{"-s",	true,	"number\tIteratively deepen with a step size of s (default 1)."},
	{"-o",	true,	"path\tSave encodings to file in smt2 format."},
	{"-n",	false,	"\tDo not solve. Generate encoding and exit."},
	{"-e",	false,	"\tUse human readable variable names in the SMT encoding."}
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
	options.explanatory_var_names = true;
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
				options.encoding_path = argv[i];
			} else if(argument[j].name == "-n") {
				options.solve = false;
			} else if(argument[j].name == "-e") {
				options.explanatory_var_names = true;
			}
			
		}
		if(!argumentFound) {
			std::cerr << "Unrecognised argument: " << argv[i] << std::endl;
			return false;
		}
	}

	return true;
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

	// parse domain and problem
	SMTPlan::Parser parser;
	if(!parser.parseDomain(options.domain_path) || !parser.parseProblem(options.problem_path)) {
		std::cerr << "Domain and Problem parsing failed." << std::endl;
		return 1;
	}

//	TIM::performTIMAnalysis(&argv[1]);

	SMTPlan::Grounder grounder;
	grounder.ground(parser.getDomain(), parser.getProblem(), options);

	// set output
	SMTPlan::Encoder encoder;
	std::ofstream pFile;
	if(options.encoding_path == "") {
		encoder.setOutput(std::cout);
	} else {
		pFile.open((options.encoding_path).c_str());
		if (!pFile.is_open() || pFile.fail() || pFile.bad()) {
			std::cerr << "Unable to open file for output: " << options.encoding_path << std::endl;
			return 1;
		}
		encoder.setOutput(pFile);
	}

	// generate encoding
	encoder.encode(parser.getDomain(), parser.getProblem(), grounder, options.lower_bound);

	// close file if open
	if (!pFile.is_open()) pFile.close();

	return 0;
}
