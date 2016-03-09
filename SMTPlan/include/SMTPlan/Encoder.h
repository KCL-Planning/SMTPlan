/**
 * This file describes the parser.
 */
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <boost/regex.hpp>

#include "ptree.h"

#include "SMTPlan/Grounder.h"

#ifndef KCL_encoder
#define KCL_encoder

namespace SMTPlan
{

	class Encoder
	{
	private:

		std::ostream *out;

		void findReplace(std::string &subject, std::map<std::string, std::string> &replaceMap) {
			std::map<std::string, std::string>::iterator mit = replaceMap.begin();
			for(; mit!=replaceMap.end(); mit++) {
				std::stringstream ss1, ss2;
				ss1 << "_" << mit->first << "([_\\) ])";
				ss2 << "_" << mit->second << "\\1";
				boost::regex re(ss1.str(), boost::regex::icase);
				subject = boost::regex_replace(subject, re, ss2.str());
			}
		}

		std::string parseExpression(const VAL::expression* exp, int h);
		std::string parseCondition(const VAL::goal* goal, int h);
		std::string parseTimedCondition(const VAL::goal* goal, VAL::time_spec part, int h);

		void encodeHeader(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);

		void encodeTimings(int h);
		void encodeInitialState(VAL::domain* domain, VAL::problem* problem, Grounder &grounder);
		void encodeGoalState(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);

		void encodeVariableSupport(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);

		void encodeActionConditions(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);
		void encodeActionEffects(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);
		void encodeActionMutexes(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);

	public:

		/* setup methods */
		void setOutput(std::ostream &o);

		/* encoding methods */
		bool encode(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int H);
	};

} // close namespace

#endif

