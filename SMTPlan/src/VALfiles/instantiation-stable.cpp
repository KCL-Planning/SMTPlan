/************************************************************************
 * Copyright 2008, Strathclyde Planning Group,
 * Department of Computer and Information Sciences,
 * University of Strathclyde, Glasgow, UK
 * http://planning.cis.strath.ac.uk/
 *
 * Maria Fox, Richard Howey and Derek Long - VAL
 * Stephen Cresswell - PDDL Parser
 *
 * This file is part of VAL, the PDDL validator.
 *
 * VAL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * VAL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VAL.  If not, see <http://www.gnu.org/licenses/>.
 *
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <fstream>
#include "ptree.h"
#include <FlexLexer.h>
#include "TIM.h"
#include "instantiation.h"
#include "SimpleEval.h"
#include "DebugWriteController.h"
#include "typecheck.h"
#include "Exceptions.h"
#include "main.h"


using std::ifstream;
using std::cerr;

using namespace VAL;

namespace Inst {

set<instantiatedDrvUtils::index,instantiatedDrvUtils::indexLT> instantiatedDrvUtils::definitive;
bool instantiatedDrvUtils::initDefinitive = false;

instantiatedDrvUtils::index * instantiatedDrvUtils::purify(const index * i) {
	if (!initDefinitive) {
		for(derivations_list::const_iterator os = current_analysis->the_domain->drvs->begin();
					os != current_analysis->the_domain->drvs->end();++os)
		{
			index newIndex((*os)->get_head()->head,(*os));
			definitive.insert(newIndex);
		};
		initDefinitive = true;
	};
	set<index,indexLT>::iterator defItr = definitive.find(*i);
	return const_cast<index*>(&(*(defItr)));
};


bool varFree(const VAL::parameter_symbol_list * pl)
{
	for(VAL::parameter_symbol_list::const_iterator i = pl->begin();i != pl->end();++i)
	{
		if(!dynamic_cast<const VAL::const_symbol *>(*i)) return false;
	};
	return true;
}


ostream & operator<<(ostream & o,const instantiatedOp & io)
{
	io.write(o);
	return o;
};

ostream & operator<<(ostream & o,const instantiatedDrv & io)
{
	io.write(o);
	return o;
};

ostream & operator<<(ostream & o,const PNE & io)
{
	io.write(o);
	return o;
};

ostream & operator<<(ostream & o,const Literal & io)
{
	io.write(o);
	return o;
};

void instantiatedOp::writeAll(ostream & o) 
{
	instOps.write(o);
};

void instantiatedDrv::writeAll(ostream & o) 
{
	instDrvs.write(o);
};


void LitStoreEvaluator::evaluateSimpleGoal(FastEnvironment * f,simple_goal * s)
{
	Literal l(s->getProp(),f);
	Literal * l1 = instantiatedOp::findLiteral(&l);
	if(l1) 
	{
		value = true;
		unknown = false;
	}
	else
	{
		value = false;
		unknown = false;
	}
};

OpStore instantiatedOp::instOps;
DrvStore instantiatedDrv::instDrvs;

map<VAL::pddl_type *,vector<VAL::const_symbol*> > instantiatedValues;

map<VAL::pddl_type *,vector<VAL::const_symbol*> > & instantiatedOp::values = instantiatedValues;
map<VAL::pddl_type *,vector<VAL::const_symbol*> > & instantiatedDrv::values = instantiatedValues;

void instantiatedOp::filterOps()
{
	int offset = 0;
	for(OpStore::iterator i = opsBegin(); !(i == opsEnd());++i)
	{
		SimpleEvaluator se((*i)->getEnv(),LSE(literals));
		(*i)->forOp()->visit(&se);
		if(se.reallyFalse())
		{
//			cout << "Kill " << *(*i) << "\n";
			opErase(*i);
			++offset;
		}
		else
		{
			(*i)->setID((*i)->getID() - offset);
		};
	}
	instOps.clearUp();
};

void instantiatedDrv::filterDrvs()
{
	int offset = 0;
	for(DrvStore::iterator i = drvsBegin(); !(i == drvsEnd());++i)
	{
		SimpleEvaluator se((*i)->getEnv(),LSE(literals));
		(*i)->forDrv()->visit(&se);
		if(se.reallyFalse())
		{
//			cout << "Kill " << *(*i) << "\n";
			drvErase(*i);
			++offset;
		}
		else
		{
			(*i)->setID((*i)->getID() - offset);
		};
	}
	instDrvs.clearUp();
};
	
	
void instantiatedOp::instantiate(const VAL::operator_ * op,const VAL::problem * prb,VAL::TypeChecker & tc)
{
	FastEnvironment e(static_cast<const id_var_symbol_table*>(op->symtab)->numSyms());
	vector<vector<VAL::const_symbol*>::const_iterator> vals(op->parameters->size());
	vector<vector<VAL::const_symbol*>::const_iterator> starts(op->parameters->size());
	vector<vector<VAL::const_symbol*>::const_iterator> ends(op->parameters->size());
	vector<VAL::var_symbol *> vars(op->parameters->size());

	int i = 0;
	int c = 1;
	for(var_symbol_list::const_iterator p = op->parameters->begin();
			p != op->parameters->end();++p,++i)
	{
		if(values.find((*p)->type) == values.end()) 
		{
			try {
				values[(*p)->type] = tc.range(*p);
			}
			catch (TypeException e) {			

				cerr << "A problem has been encountered with your domain/problem file.\n";
				cerr << "-------------------------------------------------------------\n";
				cerr << "Unfortunately, a type error has been encountered in your domain and problem file,\n";
				cerr << "and the planner has to terminate.  Specifically, for parameter " << (i+1) << "\n";
				cerr << "of the action '" << op->name->getName() << "':\n\n\t";

				Verbose = true;
				try {
					values[(*p)->type] = tc.range(*p);
				}
				catch (TypeException f) {
				}
				exit(1);
			}
		};
		vals[i] = starts[i] = values[(*p)->type].begin();
		ends[i] = values[(*p)->type].end();
		if(ends[i]==starts[i]) return;
		e[(*p)] = *(vals[i]);
		vars[i] = *p;
		c *= values[(*p)->type].size();
	};
	//cout << c << " candidates to consider\n";
	SimpleEvaluator se(0,ISC());
	if(!i)
	{
		se.prepareForVisit(&e);
		op->visit(&se);
		if(!se.reallyFalse())
		{
			FastEnvironment * ecpy = e.copy();
			instantiatedOp * o = new instantiatedOp(op,ecpy);
			if(instOps.insert(o))
			{
				delete o;
			};
				
		};
		return;
	};
	--i;
	while(vals[i] != ends[i])
	{
		if(!TIM::selfMutex(op,makeIterator(&e,op->parameters->begin()),
						makeIterator(&e,op->parameters->end())))
		{
			
			se.prepareForVisit(&e);
			const_cast<VAL::operator_*>(op)->visit(&se);
			if(!se.reallyFalse())
			{
				FastEnvironment * ecpy = e.copy();
				instantiatedOp * o = new instantiatedOp(op,ecpy);
				if(instOps.insert(o))
				{
					delete o;
				};
			}
			else if (false)
			{
				cout << "Killed\n" << op->name->getName() << "(";
				for(var_symbol_list::const_iterator a = op->parameters->begin();
						a != op->parameters->end();++a)
				{
					cout << e[*a]->getName() << " ";
				};
				cout << ")\n";
			};

		};

		int x = 0;
		++vals[0];
		if(vals[0] != ends[0]) e[vars[0]] = *(vals[0]);
		while(x < i && vals[x] == ends[x])
		{
			vals[x] = starts[x];
			e[vars[x]] = *(vals[x]);
			++x;
			++vals[x];
			if(vals[x] != ends[x]) e[vars[x]] = *(vals[x]);
		};
	};
};

void instantiatedDrv::instantiate(const VAL::derivation_rule * op,const VAL::problem * prb,VAL::TypeChecker & tc)
{
	FastEnvironment e(static_cast<const id_var_symbol_table*>(op->get_vars())->numSyms());
	vector<vector<VAL::const_symbol*>::const_iterator> vals(op->get_head()->args->size());
	vector<vector<VAL::const_symbol*>::const_iterator> starts(op->get_head()->args->size());
	vector<vector<VAL::const_symbol*>::const_iterator> ends(op->get_head()->args->size());
	vector<VAL::parameter_symbol *> vars(op->get_head()->args->size());

	int i = 0;
	int c = 1;
	for(parameter_symbol_list::const_iterator p = op->get_head()->args->begin();
			p != op->get_head()->args->end();++p,++i)
	{
		if(values.find((*p)->type) == values.end()) 
		{
			
			try {
				values[(*p)->type] = tc.range(*p);
			}
			catch (TypeException e) {			

				cerr << "A problem has been encountered with your domain/problem file.\n";
				cerr << "-------------------------------------------------------------\n";
				cerr << "Unfortunately, a type error has been encountered in your domain and problem file,\n";
				cerr << "and the planner has to terminate.  Specifically, for parameter " << (i+1) << "\n";
				cerr << "of a derivation rule for '" << op->get_head()->head->getName() << "':\n\n\t";

				Verbose = true;
				try {
					values[(*p)->type] = tc.range(*p);
				}
				catch (TypeException f) {
				}
				exit(1);
			}
		};
		vals[i] = starts[i] = values[(*p)->type].begin();
		ends[i] = values[(*p)->type].end();
		if(ends[i]==starts[i]) return;
		e[(*p)] = *(vals[i]);
		vars[i] = *p;
		c *= values[(*p)->type].size();
	};
	//cout << c << " candidates to consider\n";
	if(!i)
	{
		SimpleEvaluator se(&e,ISC());
		op->visit(&se);
		if(!se.reallyFalse())
		{
			FastEnvironment * ecpy = e.copy();
			instantiatedDrv * o = new instantiatedDrv(op,ecpy);
			if(instDrvs.insert(o))
			{
				delete o;
			};
				
		};
		return;
	};
	--i;
	while(vals[i] != ends[i])
	{
//		if(!TIM::selfMutex(op,makeIterator(&e,op->parameters->begin()),
//						makeIterator(&e,op->parameters->end())))
		{
			
			SimpleEvaluator se(&e,ISC());
			const_cast<VAL::derivation_rule*>(op)->visit(&se);
			if(!se.reallyFalse())
			{
				FastEnvironment * ecpy = e.copy();
				instantiatedDrv * o = new instantiatedDrv(op,ecpy);

				if(instDrvs.insert(o))
				{
					delete o;
				}
			};
		};
/*
		else
		{
			cout << "Killed\n" << op->name->getName() << "(";
			for(var_symbol_list::const_iterator a = op->parameters->begin();
					a != op->parameters->end();++a)
			{
				cout << e[*a]->getName() << " ";
			};
			cout << ")\n";
		};
*/
		int x = 0;
		++vals[0];
		if(vals[0] != ends[0]) e[vars[0]] = *(vals[0]);
		while(x < i && vals[x] == ends[x])
		{
			vals[x] = starts[x];
			e[vars[x]] = *(vals[x]);
			++x;
			++vals[x];
			if(vals[x] != ends[x]) e[vars[x]] = *(vals[x]);
		};
	};
};


LiteralStore instantiatedLiterals;
PNEStore instantiatedPNEs;


LiteralStore & instantiatedOp::literals = instantiatedLiterals;
PNEStore & instantiatedOp::pnes = instantiatedPNEs;

LiteralStore & instantiatedDrv::literals = instantiatedLiterals;
PNEStore & instantiatedDrv::pnes = instantiatedPNEs;


class Collector : public VisitController {
private:
	VAL::TypeChecker * tc;
	bool adding;
	const VAL::operator_ * op;
	const VAL::derivation_rule * drv;
	FastEnvironment * fe;
	LiteralStore & literals;
	PNEStore & pnes;

	bool inpres;
	bool checkpos;
	
public:
	Collector(const VAL::operator_ * o,FastEnvironment * f,LiteralStore & l,PNEStore & p,VAL::TypeChecker * t = 0) :
		tc(t), adding(true), op(o), drv(0), fe(f), literals(l), pnes(p), inpres(true), checkpos(true)
	{};

	Collector(const VAL::derivation_rule * o,FastEnvironment * f,LiteralStore & l,PNEStore & p,VAL::TypeChecker * t = 0) :
		tc(t), adding(true), op(0), drv(o), fe(f), literals(l), pnes(p), inpres(true), checkpos(true)
	{};
	
	virtual void visit_simple_goal(simple_goal * p) 
	{
		VAL::extended_pred_symbol * s = EPS(p->getProp()->head);
		
		if(VAL::current_analysis->pred_tab.symbol_probe("=") == s->getParent())
		{
			return;
		};
		if(!inpres || (p->getPolarity() && !checkpos) || (!p->getPolarity() && checkpos) )
		{
			Literal * l = new Literal(p->getProp(),fe);
			if(literals.insert(l))
			{
				delete l;
			} else {
//				cout << "Created " << *l << "\n";
			};
		};
	};
	virtual void visit_qfied_goal(qfied_goal * p) 
	{
		vector<vector<VAL::const_symbol*>::const_iterator> vals(p->getVars()->size());
		vector<vector<VAL::const_symbol*>::const_iterator> starts(p->getVars()->size());
		vector<vector<VAL::const_symbol*>::const_iterator> ends(p->getVars()->size());
		vector<VAL::var_symbol *> vars(p->getVars()->size());
		fe->extend(vars.size());
		int i = 0;
		int c = 1;
		for(var_symbol_list::const_iterator pi = p->getVars()->begin();
				pi != p->getVars()->end();++pi,++i)
		{
			if(instantiatedOp::values.find((*pi)->type) == instantiatedOp::values.end()) 
			{
				instantiatedOp::values[(*pi)->type] = tc->range(*pi);
			};
			vals[i] = starts[i] = instantiatedOp::values[(*pi)->type].begin();
			ends[i] = instantiatedOp::values[(*pi)->type].end();
			if(ends[i]==starts[i]) return;
			(*fe)[(*pi)] = *(vals[i]);
			vars[i] = *pi;
			c *= instantiatedOp::values[(*pi)->type].size();
		};
	
		--i;
		while(vals[i] != ends[i])
		{
// This is inefficient because it creates a copy of the environment even if the copy is never used.
// In practice, this should not be a problem because a quantified effect presumably uses the variables
// it quantifies.
			FastEnvironment * ecpy = fe;
			fe = fe->copy();
			p->getGoal()->visit(this);
			fe = ecpy;

			int x = 0;
			++vals[0];
			if(vals[0] != ends[0]) (*fe)[vars[0]] = *(vals[0]);
			while(x < i && vals[x] == ends[x])
			{
				vals[x] = starts[x];
				(*fe)[vars[x]] = *(vals[x]);
				++x;
				++vals[x];
				if(vals[x] != ends[x]) (*fe)[vars[x]] = *(vals[x]);
			};
		};

	};

	virtual void visit_conj_goal(conj_goal * p) 
	{p->getGoals()->visit(this);};
	virtual void visit_disj_goal(disj_goal * p) 
	{p->getGoals()->visit(this);};
	virtual void visit_timed_goal(timed_goal * p) 
	{p->getGoal()->visit(this);};
	virtual void visit_imply_goal(imply_goal * p) 
	{
		p->getAntecedent()->visit(this);
		p->getConsequent()->visit(this);
	};
	virtual void visit_neg_goal(neg_goal * p) 
	{
		bool oldcheck = checkpos;
		checkpos = !checkpos;
		p->getGoal()->visit(this);
		checkpos = oldcheck;
	};
    virtual void visit_preference(preference * p)
    {
    	p->getGoal()->visit(this);
    };	
    virtual void visit_simple_effect(simple_effect * p) 
	{
		Literal * l = new Literal(p->prop,fe);
		if(literals.insert(l))
		{
			delete l;
		};
	};
	virtual void visit_constraint_goal(constraint_goal *cg)
    {
            if(cg->getRequirement())
            {
                    cg->getRequirement()->visit(this);
            };
            if(cg->getTrigger())
            {
                    cg->getTrigger()->visit(this);
            };
    };

	virtual void visit_forall_effect(forall_effect * p) 
	{
//		p->getEffects()->visit(this);
		vector<vector<VAL::const_symbol*>::const_iterator> vals(p->getVarsList()->size());
		vector<vector<VAL::const_symbol*>::const_iterator> starts(p->getVarsList()->size());
		vector<vector<VAL::const_symbol*>::const_iterator> ends(p->getVarsList()->size());
		vector<VAL::var_symbol *> vars(p->getVarsList()->size());
		fe->extend(vars.size());
		int i = 0;
		int c = 1;
		for(var_symbol_list::const_iterator pi = p->getVarsList()->begin();
				pi != p->getVarsList()->end();++pi,++i)
		{
			if(instantiatedOp::values.find((*pi)->type) == instantiatedOp::values.end()) 
			{
				instantiatedOp::values[(*pi)->type] = tc->range(*pi);
			};
			vals[i] = starts[i] = instantiatedOp::values[(*pi)->type].begin();
			ends[i] = instantiatedOp::values[(*pi)->type].end();
			if(ends[i]==starts[i]) return;
			(*fe)[(*pi)] = *(vals[i]);
			vars[i] = *pi;
			c *= instantiatedOp::values[(*pi)->type].size();
		};
	
		--i;
		while(vals[i] != ends[i])
		{
// This is inefficient because it creates a copy of the environment even if the copy is never used.
// In practice, this should not be a problem because a quantified effect presumably uses the variables
// it quantifies.
			FastEnvironment * ecpy = fe;
			fe = fe->copy();
			p->getEffects()->visit(this);
			fe = ecpy;

			int x = 0;
			++vals[0];
			if(vals[0] != ends[0]) (*fe)[vars[0]] = *(vals[0]);
			while(x < i && vals[x] == ends[x])
			{
				vals[x] = starts[x];
				(*fe)[vars[x]] = *(vals[x]);
				++x;
				++vals[x];
				if(vals[x] != ends[x]) (*fe)[vars[x]] = *(vals[x]);
			};
		};
		
// Ends here!
	};
	virtual void visit_cond_effect(cond_effect * p) 
	{
		p->getCondition()->visit(this);
		p->getEffects()->visit(this);
	};
	virtual void visit_timed_effect(timed_effect * p) 
	{
		p->effs->visit(this);
	};
	virtual void visit_timed_initial_literal(timed_initial_literal * p)
	{
		p->effs->visit(this);
	};
	virtual void visit_effect_lists(effect_lists * p) 
	{
		p->add_effects.pc_list<simple_effect*>::visit(this);
		p->forall_effects.pc_list<forall_effect*>::visit(this);
		p->cond_effects.pc_list<cond_effect*>::visit(this);
		p->timed_effects.pc_list<timed_effect*>::visit(this);
		bool whatwas = adding;
		adding = !adding;
		p->del_effects.pc_list<simple_effect*>::visit(this);
		adding = whatwas;
		p->assign_effects.pc_list<assignment*>::visit(this);
	};
	virtual void visit_operator_(VAL::operator_ * p) 
	{
		inpres = true;
		checkpos = true;
		if(p->precondition) p->precondition->visit(this);
		inpres = false;
		
		adding = true;
		p->effects->visit(this);
	};

	virtual void visit_derivation_rule(VAL::derivation_rule * p) 
	{
		inpres = true;
		checkpos = true;
		if (p->get_body()) p->get_body()->visit(this);
		inpres = false;
		
		adding = true;
		Literal * l = new Literal(p->get_head(),fe);
		if(literals.insert(l))
		{
			delete l;
		} else {
//			cout << "Created " << *l << "\n";
		}
	};

	virtual void visit_action(VAL::action * p)
	{
		visit_operator_(p); //static_cast<VAL::operator_*>(p));
	};
	virtual void visit_durative_action(VAL::durative_action * p) 
	{
		visit_operator_(p); //static_cast<VAL::operator_*>(p));
	};
	virtual void visit_process(VAL::process * p)
	{
		visit_operator_(p);
	};
	virtual void visit_event(VAL::event * p)
	{
		visit_operator_(p);
	};
	virtual void visit_problem(VAL::problem * p) 
	{
		p->initial_state->visit(this);
		inpres = false;
		p->the_goal->visit(this);
		if (p->constraints) p->constraints->visit(this);
	};

	virtual void visit_assignment(assignment * a) 
	{
		const func_term * ft = a->getFTerm();
		PNE * pne = new PNE(ft,fe);
		if(pnes.insert(pne))
		{
			delete pne;
		};
	};
};

void instantiatedOp::createAllLiterals(VAL::problem * p,VAL::TypeChecker * tc) 
{
	Collector c((VAL::operator_*)0,0,literals,pnes,tc);
	p->visit(&c);
	for(OpStore::iterator i = instOps.begin(); i != instOps.end(); ++i)
	{
		(*i)->collectLiterals(tc);
	};

	instantiatedDrv::createAllLiterals(p,tc);
};



void instantiatedOp::collectLiterals(VAL::TypeChecker * tc)
{
	Collector c(op,env,literals,pnes,tc);
	op->visit(&c);
};

void instantiatedDrv::createAllLiterals(VAL::problem *,VAL::TypeChecker * tc) 
{
	for(DrvStore::iterator i = instDrvs.begin(); i != instDrvs.end(); ++i)
	{
		(*i)->collectLiterals(tc);
	};

};

void instantiatedDrv::collectLiterals(VAL::TypeChecker * tc)
{
//	cout << "Collecting literals for "; write(cout); cout << "\n";
	Collector c(op,env,literals,pnes,tc);
	op->visit(&c);
};


void instantiatedOp::writeAllLiterals(ostream & o) 
{
	literals.write(o);
};

void instantiatedOp::writeAllPNEs(ostream & o)
{
	pnes.write(o);
};

VAL::const_symbol * const getConst(string name) 
{
	return current_analysis->const_tab.symbol_get(name);
};

VAL::const_symbol * const getConst(char * name) 
{
	return current_analysis->const_tab.symbol_get(name);
};

// Added by AMC to test whether a goal may be satisfied by the effects
// of an InstantiatedOp

bool instantiatedOp::isGoalMetByOp(const Literal * lit)
{
  effect_lists * effs = op->effects;

  return isGoalMetByEffect(effs, lit);
};

bool instantiatedOp::isGoalMetByEffect(const VAL::effect_lists * effs, const Literal * lit)
{
  using VAL::pc_list;

  for(pc_list<VAL::simple_effect*>::const_iterator i = effs->add_effects.begin(); i != effs->add_effects.end(); ++i)
    {
	if (isGoalMetByEffect(*i, lit)) return true;
    };
  for(pc_list<VAL::forall_effect*>::const_iterator i = effs->forall_effects.begin(); i != effs->forall_effects.end();++i)
    {
      if (isGoalMetByEffect(*i, lit)) return true;
    };
  for(pc_list<VAL::cond_effect*>::const_iterator i = effs->cond_effects.begin(); i != effs->cond_effects.end();++i)
    {
      if (isGoalMetByEffect(*i, lit)) return true;
    };
  for(pc_list<VAL::cond_effect*>::const_iterator i = effs->cond_effects.begin(); i != effs->cond_effects.end();++i)
    {
      if (isGoalMetByEffect(*i, lit)) return true;
    };
  for (pc_list<VAL::timed_effect*>::const_iterator i = effs->timed_effects.begin(); i != effs->timed_effects.end(); ++i)
    {
      if (isGoalMetByEffect(*i, lit)) return true;
    };
  return false;
};

bool instantiatedOp::isGoalMetByEffect(VAL::simple_effect * seff, const Literal * lit)
{
  Literal l (seff->prop,env);
  Literal * lt = instantiatedOp::getLiteral(&l);
  //  std::cout <<"Simple effect: " << (*lt) << "\n";
  return (lit==lt);
};

bool instantiatedOp::isGoalMetByEffect(VAL::forall_effect * fleff, const Literal * lit)
{
  if (isGoalMetByEffect(fleff->getEffects(), lit)) return true;
  else return false;
};

bool instantiatedOp::isGoalMetByEffect(VAL::cond_effect * ceff, const Literal * lit)
{
  if (isGoalMetByEffect(ceff->getEffects(), lit)) return true;
  else return false;
};

bool instantiatedOp::isGoalMetByEffect(VAL::timed_effect * teff, const Literal * lit)
{
  if (isGoalMetByEffect(teff->effs, lit)) return true;
  else return false;
};


instantiatedOp::PropEffectsIterator instantiatedOp::addEffectsBegin()
{
	return PropEffectsIterator(this,true);
};

instantiatedOp::PropEffectsIterator instantiatedOp::addEffectsEnd()
{
	PropEffectsIterator pi(this,true);
	pi.toEnd();
	return pi;
};

instantiatedOp::PropEffectsIterator instantiatedOp::delEffectsBegin()
{
	return PropEffectsIterator(this,false);
};

instantiatedOp::PropEffectsIterator instantiatedOp::delEffectsEnd()
{
	PropEffectsIterator pi(this,false);
	pi.toEnd();
	return pi;
};

instantiatedOp::PNEEffectsIterator instantiatedOp::PNEEffectsBegin()
{
	return PNEEffectsIterator(this);
};

instantiatedOp::PNEEffectsIterator instantiatedOp::PNEEffectsEnd()
{
	PNEEffectsIterator pi(this);
	pi.toEnd();
	return pi;
};



};
