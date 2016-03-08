/**
 * This file describes the parser.
 */

#include "ptree.h"
#include "FlexLexer.h"
#include "TIM.h"

#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>

#ifndef KCL_parser
#define KCL_parser

extern int yyparse();
extern int yydebug;

namespace VAL {
	extern analysis an_analysis;
	extern yyFlexLexer* yfl;
};

namespace SMTPlan
{

	class Parser
	{
	private:

		VAL::domain* domain;
		VAL::problem* problem;
		VAL::analysis* analysis;

	public:

		Parser() : domain_parsed(false), problem_parsed(false) {}

		/* domain information */
		bool domain_parsed;
		std::string domainName;

		/* problem information */
		bool problem_parsed;
		std::string problemName;

		/* parsing */		
		bool parseDomain(const std::string domainPath);
		bool parseProblem(const std::string problemPath);
		void clear();

		/* getters */
		VAL::domain* getDomain();
		VAL::problem* getProblem();
		VAL::analysis* getAnalysis();
	};
} // close namespace

#endif

