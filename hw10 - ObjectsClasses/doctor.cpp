//Name:Samuel Itschner
//Date:4/15/2012
//Description:Contains the functions for the doctor class
//File:doctor.cpp
#include "doctor.h"
doctor::doctor (const string name)
{
  m_name = name;
  m_gin_amt = GIN_AMT;
  m_money = MONEY;
  m_num_puke = 0;
}

void doctor::puke()
{
  if(m_gin_amt >= PUKE)
  {
    m_gin_amt = 0;
	m_num_puke++;
  }
}

void doctor::setGin(int gin_amt)
{
  m_gin_amt = gin_amt;
  puke();
}

void doctor::collectMoney(float money)
{
  m_money = m_money + money;
}

ostream& operator<<(ostream &out, const doctor &doc)
{
  out << endl << "The name of this doctor is "<< doc.m_name << endl
  << "This doctor has " << doc.m_gin_amt << " ounces of gin in their system."
  << endl << "This doctor has $" << doc.m_money << "." << endl <<
  "The doctor has puked " << doc.m_num_puke << " times." << endl;
  return out;
}