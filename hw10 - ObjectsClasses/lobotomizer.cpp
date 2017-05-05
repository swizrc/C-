//Name:Samuel Itschner
//Date:4/18/2012
//Description:Holds the functions for the lobotomizer class
//File:lobotomizer.cpp
#include "lobotomizer.h"

void lobotomizer::charge_patient(patient & person)
{
  person.pay_out(m_cost_per_use);
}

void lobotomizer::apply (patient & person)
{
  m_num_uses++;
  int prob, prob2;
  person.setMent(person.getMent() + INCREASE_MENT_LOBO);
  person.modify_health(INCREASE_COND_LOBO);
  prob = (rand() % (100+1-1) + 1);
  prob2 = (rand() % (100+1-1) + 1);
  if(prob <= CHANCE_TO_REDUCE_LOBO)
  {
    person.setMent(0);
  }
  if(prob2 <= CHANCE_TO_REDUCE2_LOBO)
  {
    person.setName(person.getName() + person.randName());
  }	
}

ostream& operator<<(ostream &out, const lobotomizer &machine)
{
  out << "The cost per use of this lobotomizer machine is "
    << machine.m_cost_per_use << " and it has been used " <<
	machine.m_num_uses << " times." << endl;
	return out;
}

lobotomizer::lobotomizer () : m_num_uses(0), m_cost_per_use(COST_PER_USE_LOBO)
{}