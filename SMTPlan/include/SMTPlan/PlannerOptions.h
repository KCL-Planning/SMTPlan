/**
 * The structs in this file are used to the setup of an SMTPlan instance.
 */
#ifndef KCL_options
#define KCL_options

#define MAX_BITSET 100000

#include <string>

namespace SMTPlan
{

	struct Argument
	{
		std::string name;
		bool has_value;
		std::string help;
	};

	struct PlannerOptions
	{
		bool verbose;
		bool debug;

		// files
		std::string domain_path;
		std::string problem_path;

		// solving options
		bool solve;

		// encoding options
		int encoder;

		// iterative deepening
		int lower_bound;
		int upper_bound;
		int cascade_bound;
		int step_size;
	};

// close namespace
}
#endif
