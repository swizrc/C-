//Name: Samuel Itschner
//Date: 4/5/2012
//Description: Header file for the x_rayer class
//File:xrayer.h
#ifndef XRAYER_H
#define XRAYER_H
#include "patient.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int CHANCE_TO_REDUCE_XRAY = 10; //Constant showing, out of 100,
// the chance that the x-ray machine will halve the patient's condition
const int COST_PER_USE_XRAY = 550; //The cost to use the x-ray machine every time
const int REDUCTION_XRAY = 2; //The factor by which to reduce the patient's 
//condition by

//charge_patient(patient & person) subtracts a cost from the patient's total
// money
//Pre:None
//Post:The cost per use is subtracted from the patient's money amount

//apply(patient & person) represents the patient "using" the x-ray machine
//There is a set chance that using the machine will reduce the patient's
//condition
//Pre:The patient has money to pay the machine and is alive
//Post:m_num_uses is increased by one and patient's condition might be reduced

//ostream& operator<<(ostream &out, const x_rayer &machine) overloads the
//insertion operator to output the state of the x_rayer class
//Pre:None
//Post:The state of the x-ray machine is displayed on-screen

//x_rayer() is the default constructor that sets the private values of the 
//class 
//Pre:None
//Post:m_num_uses and m_cost_per_use will have values assigned to them

//getUses() retrieves the machine's uses
//Pre:None
//Post:The machine's number of uses is returned

class x_rayer
{
  public:
	void charge_patient(patient & person);
	void apply(patient & person); 
	friend ostream& operator<<(ostream &out, const x_rayer &machine);
	x_rayer();
    short getUses() {return m_num_uses;}	
  private:
    short m_num_uses;
	float m_cost_per_use;
};
#endif