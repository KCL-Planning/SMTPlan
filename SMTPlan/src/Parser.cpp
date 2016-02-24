#include "SMTPlan/Parser.h"

/* implementation of SMTPlan::Parser */
namespace SMTPlan {

	void Parser::clear() {

		// clear old problem
		problem_parsed = false;
	}

	/*----------------*/
	/* parsing domain */
	/*----------------*/

	/**
	 * read domain: used for writing the PDDL problem file and then for constructing the dispatch
	 * messages.
	 */
	bool Parser::parseDomain(const std::string domainPath) {
		
		// only parse domain once
		if(domain_parsed)
			return true;

		domain_parsed = true;
		std::string domainFileName = (domainPath);

		// save filename for VAL
		std::vector<char> writable(domainFileName.begin(), domainFileName.end());
		writable.push_back('\0');
		current_filename = &writable[0];

		// parse domain
		VAL::current_analysis = &VAL::an_analysis;
		std::ifstream domainFile;
		domainFile.open(domainFileName.c_str());
		yydebug = 0;

		VAL::yfl = new yyFlexLexer;

		if (!domainFile.is_open() || domainFile.fail() || domainFile.bad()) {

			line_no = 0;
			VAL::log_error(VAL::E_FATAL,"Failed to open file");
			fprintf(stdout,"Could not find/open domain file: %s\n", domainFileName.c_str());
			return false;

		} else {
					
			line_no = 1;
			VAL::yfl->switch_streams(&domainFile,&std::cout);
			yyparse();

			// domain name
			VAL::domain* domain = VAL::current_analysis->the_domain;
			domainName = domain->name;

		}
		domainFile.close();
		delete VAL::yfl;
		
		return true;
	}

	/*-----------------*/
	/* parsing problem */
	/*-----------------*/

	/**
	 * requests all the information required to build a problem instance.
	 */
	bool Parser::parseProblem(const std::string problemPath) {


		// clear old problem
		clear();

		problem_parsed = true;
		std::string problemFileName = (problemPath);

		// save filename for VAL
		std::vector<char> writable(problemFileName.begin(), problemFileName.end());
		writable.push_back('\0');
		current_filename = &writable[0];

		// parse domain
		VAL::current_analysis = &VAL::an_analysis;
		std::ifstream problemFile;
		problemFile.open(problemFileName.c_str());
		yydebug = 0;

		VAL::yfl = new yyFlexLexer;

		if (!problemFile.is_open() || problemFile.fail() || problemFile.bad()) {

			line_no = 0;
			VAL::log_error(VAL::E_FATAL,"Failed to open file");
			fprintf(stdout,"Could not find/open problem file: %s\n", problemFileName.c_str());
			return false;

		} else {
					
			line_no = 1;
			VAL::yfl->switch_streams(&problemFile,&std::cout);
			yyparse();

			// domain name
			VAL::problem* problem = VAL::current_analysis->the_problem;
			problemName = problem->name;

		}
		problemFile.close();
		delete VAL::yfl;

		return true;
	}
} // close namespace
