/**
 * This file describes the problem.
 */
#include <string>
#include <vector>
#include <map>

#include"z3++.h"

#ifndef KCL_problem_info
#define KCL_problem_info

namespace SMTPlan
{
	
	struct ProblemInfo
	{
		std::map<std::string,bool> staticPredicateMap;
		std::map<std::string,bool> staticFunctionMap;
		std::map<int,double> staticFunctionValues;
	};

} // close namespace

#endif

