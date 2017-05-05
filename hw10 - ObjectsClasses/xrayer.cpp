//Name: Samuel Itschner
//Date: 4/5/2012
//Description: File holding the functions of the x_rayer class
//File:xrayer.cpp
#include "xrayer.h"

ostream& operator<<(ostream &out, const x_rayer &machine)
{
  out << "The cost per use of this X-Ray machine is "
    << machine.m_cost_per_use << " and it has been used " <<
	machine.m_num_uses << " times." << endl;
	return out;
}

void x_rayer::apply (patient & person)
{
  m_num_uses++;
  int prob;
  prob = (rand() % (100+1-1) + 1);
  if(prob <= CHANCE_TO_REDUCE_XRAY)
  {
    person.setCond(person.getCond() / REDUCTION_XRAY);
  }		
}

void x_rayer::charge_patient(patient & person)
{
  person.pay_out(m_cost_per_use);
}

x_rayer::x_rayer () : m_num_uses(0), m_cost_per_use(COST_PER_USE_XRAY) {}