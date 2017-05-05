//Name:Samuel Itschner
//Date:4/18/2012
//Description:Header file for the lobotomizer class
//File:lobotomizer.h
#ifndef LOBOTOMIZER_H
#define LOBOTOMIZER_H
#include "patient.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int COST_PER_USE_LOBO = 200; //How much the patient will be charged every
// time they use this machine
const int CHANCE_TO_REDUCE_LOBO = 3; //Chance out of one hundred that
const int CHANCE_TO_REDUCE2_LOBO = 10; //Chance out of one hundred that
const int INCREASE_COND_LOBO = 3; //Amount that the patient's physical 
// condition will increase every time the machine is used
const int INCREASE_MENT_LOBO = 10; //Amount that the patient's mental condition
// will increase every time the machine is used

//charge_patient(patient & person) subtracts a cost from the patient's total
// money
//Pre:None
//Post:The cost per use is subtracted from the patient's money amount

//apply(patient & person) represents the patient "using" the lobotomizer
// machine
//Pre:The patient has money to pay the machine and is alive
//Post:Patient's mental and physical health increases, but has a chance to 
// set mental health to zero. Also a chance that the patient will choose a name
// to concatenate onto their own

//ostream& operator<<(ostream &out, const lobotomizer &machine) overloads the
// insertion operator to output the state of the machine
//Pre:None
//Post:Outputs the state of the machine

//lobotomizer() gives the private variables values
//Pre:None
//Post:m_num_uses and m_cost_per_use are given values

//getUses() retrieves the machine's uses
//Pre:None
//Post:The machine's number of uses is returned

class lobotomizer
{
  public:
	void charge_patient(patient & person);
	void apply(patient & person); 
	friend ostream& operator<<(ostream &out, const lobotomizer &machine);
	lobotomizer();	
	short getUses() {return m_num_uses;}
  private:
    short m_num_uses;
	float m_cost_per_use;   
};
#endif