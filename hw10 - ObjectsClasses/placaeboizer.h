//Name: Samuel Itschner
//Date: 4/18/2012
//Description: Header file for the placaeboizer class
//File:placaeboizer.h
#ifndef PLACAEBOIZER_H
#define PLACAEBOIZER_H
#include "patient.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

const int WEIGHT_MODIFY_PLAC = 50; //How much to add to the patient's weight 
// every time the machine is used
const int COST_PER_USE_PLAC = 500; //How much the patient will be charged 
// every time they use this machine 

//charge_patient(patient & person) subtracts a cost from the patient's total
// money
//Pre:None
//Post:The cost per use is subtracted from the patient's money amount

//apply(patient & person) represents the patient "using" the placaeboizer
// machine
//Pre:The patient has money to pay the machine and is alive
//Post:Patient's mental health value will increase by an amount equal to half 
// the difference between their current mental health and the maximum mental 
// health. Also adds an amount to the patient's weight

//ostream& operator<<(ostream &out, const placaeboizer &machine) overloads the
// insertion operator to output the state of the machine
//Pre:None
//Post:The state of the machine is displayed

//placaeboizer() gives the private variables values
//Pre:None
//Post:m_num_uses and m_cost_per_use will have values assigned to them

//getUses() retrieves the machine's uses
//Pre:None
//Post:The machine's number of uses is returned

class placaeboizer
{
  public:
    void charge_patient(patient & person);
	void apply(patient & person); 
	friend ostream& operator<<(ostream &out, const placaeboizer &machine);
	placaeboizer();
    short getUses() {return m_num_uses;}	
  private:
    short m_num_uses;
	float m_cost_per_use;
};
#endif