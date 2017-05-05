//Name: Samuel Itschner
//Date: 4/18/2012
//Description: Contains the functions for the liposuctionizer class
//File:liposuctionizer.h
#include "liposuctionizer.h"

void liposuctionizer::charge_patient(patient & person)
{
  person.pay_out(m_cost_per_use);
}

void liposuctionizer::apply(patient & person)
{
  m_num_uses++;
  person.setMent(person.getMent() + MENT_INCREASE_LIPO);
  if(m_num_uses == KILL_NUMBER)
  {
    m_num_uses = 0;
	person.modify_health(person.getCond() - (person.getCond() * 2));
  }
  person.setWeight(person.getWeight() * REDUCE_LIPO);
}

ostream& operator<<(ostream &out, const liposuctionizer &machine)
{
  out << "The cost per use of this liposuctionizer machine is "
    << machine.m_cost_per_use << " and it has been used " <<
	machine.m_num_uses << " times." << endl;
	return out;
}

liposuctionizer::liposuctionizer () : m_num_uses(0), 
m_cost_per_use(COST_PER_USE_LIPO) {}