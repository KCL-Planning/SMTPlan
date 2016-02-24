/**
 * This file describes the parser.
 */

#include "ptree.h"
#include "FlexLexer.h"

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
	};
} // close namespace

#endif

