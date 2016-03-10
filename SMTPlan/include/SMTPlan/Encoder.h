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
				ss1 << "_" << mit->first << "([_\\) ]|\\z)";
				ss2 << "_" << mit->second << "\\1";
				boost::regex re(ss1.str(), boost::regex::icase);
				subject = boost::regex_replace(subject, re, ss2.str());
			}
		}

		void findReplace(std::string &subject, std::string &find, std::string &replace) {
			std::stringstream ss1, ss2;
			ss1 << "([_\\( ])" << find << "([_\\) ]|\\z)";
			ss2 << "\\1" << replace << "\\2";
			boost::regex re(ss1.str(), boost::regex::icase);
			subject = boost::regex_replace(subject, re, ss2.str());
		}

		void addHappeningTags(std::string &subject, int b, int h) {
			std::stringstream ss1, ss2;
			ss1 << "([ ](?!duration)[a-z][^) ]*)([\\) ]|\\z)";
			ss2 << "\\1_" << b << "_" << h << "\\2";
			boost::regex re(ss1.str(), boost::regex::icase);
			subject = boost::regex_replace(subject, re, ss2.str());
		}

		std::string parseExpression(const VAL::expression* exp, int h, int b);
		std::string parseCondition(const VAL::goal* goal, int h, int b);
		std::string parseTimedCondition(const VAL::goal* goal, VAL::time_spec part, int h, int b);

		void encodeHeader(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);

		void encodeTimings(int h);
		void encodeInitialState(VAL::domain* domain, VAL::problem* problem, Grounder &grounder);
		void encodeGoalState(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);

		void encodeHappeningVariableSupport(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);
		void encodeIntervalVariableSupport(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);

		void encodeActionConditions(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);
		void encodeActionEffects(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);
		void encodeActionMutexes(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);
		void encodeActionDurations(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int h);

	public:

		/* setup methods */
		void setOutput(std::ostream &o);

		/* encoding methods */
		bool encode(VAL::domain* domain, VAL::problem* problem, Grounder &grounder, int H);
	};

} // close namespace

#endif

