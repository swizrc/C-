//Name: Samuel Itschner
//Date: 4/18/2012
//Description: Holds the functions for the pharmacy class
//File:pharmacy.cpp
#include "pharmacy.h"

int pharmacy::randPills()
{
  int prob;
  prob = (rand() % (UPPER_LIMIT_PILLS+1-LOWER_LIMIT_PILLS)
  + LOWER_LIMIT_PILLS);
  return prob;
}

pharmacy::pharmacy() : m_num_uses(0), m_cost_per_use(COST_PER_USE_PHARM), 
m_num_pills(randPills()) {}

void pharmacy::charge_patient(patient & person)
{
  person.pay_out(m_cost_per_use);
}

ostream& operator<<(ostream &out, const pharmacy &machine)
{
  out << "The cost per use of this pharmacy machine is "
    << machine.m_cost_per_use << " and it has been used " <<
	machine.m_num_uses << " times." << endl
	<< " It currently holds " << machine.m_num_pills << " pills." << endl;
	return out;
}

void pharmacy::apply(patient & person)
{
  int prob;
  prob = (rand() % (100+1-1) + 1);
  m_num_uses++;
  if(m_num_pills > 0)
  {  
    m_num_pills--;
  }
  if(m_num_pills <= 0)
  {
    person.setMent(person.getMent() + DISTRESS);
	person.setWeight(person.getWeight() + WEIGHT_DISTRESS);
  }
  if(prob <= 25 && m_num_pills > 0)
  {
    person.setMent(person.getMent() + NORM_MENT);
	person.modify_health(NORM_COND);
  }
  if(prob > 25 && prob <= 50 && m_num_pills > 0)
  {
    person.setMent(BRAIN_DEAD);
	person.modify_health(BRAIN_DEAD_COND);
  }
  if(prob > 50 && prob <= 75 && m_num_pills > 0)
  {
    person.setCond(MIDDLE);
  }
  if(prob > 75 && m_num_pills > 0)
  {
    person.setMent(HAPPY);
	person.setWeight(person.getWeight() + FAT);
  }  
}