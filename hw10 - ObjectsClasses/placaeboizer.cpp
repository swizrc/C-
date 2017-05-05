//Name: Samuel Itschner
//Date: 4/18/2012
//Description: Contains the functions for the placaeboizer class
//File:placaeboizer.cpp
#include "placaeboizer.h"

void placaeboizer::charge_patient(patient & person)
{
  person.pay_out(m_cost_per_use);
}

void placaeboizer::apply(patient & person)
{
  m_num_uses++;
  person.setWeight(person.getWeight() + WEIGHT_MODIFY_PLAC);
  person.setMent(person.getMent() + (100-person.getMent())/2);
}

ostream& operator<<(ostream &out, const placaeboizer &machine)
{
  out << "The cost per use of this placaeboizer machine is "
    << machine.m_cost_per_use << " and it has been used " <<
	machine.m_num_uses << " times." << endl;
	return out;
}

placaeboizer::placaeboizer () : m_num_uses(0), m_cost_per_use(COST_PER_USE_PLAC) {}