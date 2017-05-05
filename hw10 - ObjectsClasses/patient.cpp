//Name: Samuel Itschner
//Date: 4/5/2012
//Description: Contains the functions for class 'patient'
//File:patient.cpp
#include "patient.h"

string patient::randName()
{
  ifstream filename;
  string dat_file, name;
  int num_data, Rand;
  filename.clear();
  filename.open(NAME_PAT.c_str());
  while (!filename)
  {
    filename.clear();
    cout << "Enter file to connect to: " << endl;
    cin >> dat_file;
    filename.open(dat_file.c_str());
  }
  filename >> num_data;
  Rand = (rand() % (num_data) + 2);
  for(int i=1;i <= Rand; i++)
  {
    getline(filename, name, '\n');
  }
  return name;
}  

void patient::modify_health(int mod_num)
{
  m_condition = m_condition + mod_num;
  kill();
}

void patient::pay_out(float price)
{
  m_money = m_money - price;
  kill();
  if(m_money < 0)
    m_money = 0;
}

int patient::RandCond()
{
  int cond;
  cond = (rand() % (MAX_COND+1-0) + 0);
  kill();
  return cond;
}

int patient::RandMent()
{
  int mental;
  mental = (rand() % (MAX_MENTAL+1-0) + 0);
  kill();
  return mental;
}

int patient::RandWeight()
{
  int weight;
  weight = (rand() % (MAX_WEIGHT+1-MIN_WEIGHT) + MIN_WEIGHT);
  kill();
  return weight;
}

float patient::setMoney()
{
  float Secret, Out;
  Secret = (rand() % (MAX_MONEY+1-0) + 0);
  Out = Secret / 10;
  kill();
  return Out;  
}

ostream& operator<< (ostream &out, const patient &person)
{
  out << endl << person.m_name << " is " << person.m_weight << " lbs. PH: " <<
  person.m_condition << " MH: " << person.m_mental_condition << " has $" <<
  person.m_money << ". State is ";
  if(person.m_is_alive == false)
  {
    out << "Deceased." << endl;
  }
  if(person.m_is_alive == true)  
  { 
    out << "Alive!" << endl;
  }	
  return out;
}

patient::patient () : m_is_alive(true),m_money(setMoney()),  
m_condition(RandCond()), m_name(randName()), m_mental_condition(RandMent()), 
m_weight(RandWeight()) {}

void patient::setMent (int mental_condition)
{
  m_mental_condition = mental_condition;
  kill();
  if(m_mental_condition > 100)
  {  
	m_mental_condition = 100;
  }
}

void patient::setName (string name)
{
  m_name = name;
  kill();
}

void patient::setWeight (int weight)
{
  m_weight = weight;
  kill();
}

void patient::setCond (int cond)
{
  m_condition = cond;
  if(m_condition > 100)
  {  
	m_condition = 100;
  }
  kill();
}

void patient::kill()
{
  if(m_condition <= 0)
  {  
	m_is_alive = false;
    m_condition = 0;
  }
  if(m_condition > 0)
  {
    m_is_alive = true;
	if(m_condition > 100)
	  m_condition = 100;
  }	
}