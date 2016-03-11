/**
 * This file describes the RPG pruner.
 */
#include <sstream>
#include <string>
#include <cstdio>
#include <iostream>
#include <vector>
#include <deque>
#include <bitset>

#include "SMTPlan/PlannerOptions.h"
#include "SMTPlan/Grounder.h"

#include "ptree.h"

#ifndef KCL_rpgpruner
#define KCL_rpgpruner

namespace SMTPlan
{
	class RPGPruner
	{
	private:

		bool buildLayer(Grounder &grounder, PlannerOptions &options);
		void printRPG(Grounder &grounder, PlannerOptions &options);
		void prune(Grounder &grounder);

		std::map<std::vector<std::bitset<MAX_BITSET> >::size_type, std::vector<std::bitset<MAX_BITSET> >::size_type> prop_index_map;
		std::map<std::vector<std::bitset<MAX_BITSET> >::size_type, std::vector<std::bitset<MAX_BITSET> >::size_type> action_index_map;

	public:

		/* constructor */
		RPGPruner() : built(false) {}

		/* bitsets */
		std::vector<std::bitset<MAX_BITSET> > fact_layers;
		std::vector<std::bitset<MAX_BITSET> > action_layers;

		/* grounding method */
		bool built;
		bool build(Grounder &grounder, PlannerOptions &options);
	};

} // close namespace

#endif

