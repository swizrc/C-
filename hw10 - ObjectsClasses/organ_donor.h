//Name: Samuel Itschner
//Date: 4/18/2012
//Description: Header file for the organ_donor class
//File:organ_donor.h
#ifndef ORGAN_DONOR_H
#define ORGAN_DONOR_H
#include "patient.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int COST_PER_USE_ORGA = 100; //How much the patient will be charged every time
// they use this machine
const int INCREASE_MENT_ORGA = 10; //Amount that the patient's mental condition
// will increase every time the machine is used
const int CHANCE_TO_REDUCE_ORGA = 2; //Chance out of one hundred that the patient
// will be killed when using the machine
const int UPPER_LIMIT_ORGA = 1; //Upper limit of a random number generator
const int LOWER_LIMIT_ORGA = -20; //Lower limit of a random number generator
const int WEIGHT_MODIFY_ORGA = -10; //Modifier of the patient's weight

//charge_patient(patient & person) subtracts a cost from the patient's total
// money
//Pre:None
//Post:The cost per use is subtracted from the patient's money amount

//apply(patient & person) represents the patient "using" the organ donor
// machine
//Pre:The patient has money to pay the machine and is alive
//Post:Increases the patient's mental health, decreases physical health 
// Has a chance of killing the patient, decreases the patient's weight

//ostream& operator<<(ostream &out, const organ_donor &machine) overloads the
// insertion operator to output the state of the machine
//Pre:None
//Post:The state of the organ donor machine is displayed

//organ_donor() default constructor that sets the private values
//Pre:None
//Post:m_num_uses and m_cost_per_use is given values

//getUses() retrieves the machine's uses
//Pre:None
//Post:The machine's number of uses is returned

class organ_donor
{
  public:
	void charge_patient(patient & person);
	void apply(patient & person); 
	friend ostream& operator<<(ostream &out, const organ_donor &machine);
	organ_donor();	
	short getUses() {return m_num_uses;}
  private:
    short m_num_uses;
	float m_cost_per_use;
};
#endif