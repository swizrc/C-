//Name: Samuel Itschner
//Date: 4/18/2012
//Description: Contains the functions for the organ_donor class
//File:organ_donor.cpp
#include "organ_donor.h"

void organ_donor::charge_patient(patient & person)
{
  person.pay_out(m_cost_per_use);
}

void organ_donor::apply(patient & person)
{
  int prob, prob2;
  m_num_uses++;
  person.setMent(person.getMent() + INCREASE_MENT_ORGA);
  prob = (rand() % (100+1-1) + 1);
  if(prob <= CHANCE_TO_REDUCE_ORGA)
  {
    person.modify_health(person.getCond()-(person.getCond() * 2));
  }
  prob2 = (rand() % (UPPER_LIMIT_ORGA-LOWER_LIMIT_ORGA) + LOWER_LIMIT_ORGA);
  person.modify_health(prob2);
  person.setWeight(person.getWeight() + WEIGHT_MODIFY_ORGA);
}

ostream& operator<<(ostream &out, const organ_donor &machine)
{
  out << "The cost per use of this organ donor machine is "
    << machine.m_cost_per_use << " and it has been used " <<
	machine.m_num_uses << " times." << endl;
	return out;
}

organ_donor::organ_donor () : m_num_uses(0), m_cost_per_use(COST_PER_USE_ORGA) {}