//Name: Samuel Itschner
//Date: 4/18/2012
//Description: Header file for the liposuctionizer class
//File:liposuctionizer.h
#ifndef LIPOSUCTIONIZER_H
#define LIPOSUCTIONIZER_H
#include "patient.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

const int COST_PER_USE_LIPO = 750; //How much the patient will be charged every time
// they use this machine
const float REDUCE_LIPO = .9; //What factor to set the weight after the patient uses
// this machine
const int MENT_INCREASE_LIPO = 20; //Magnitude of modification of the patient's
// mental condition
const int KILL_NUMBER = 61; //How many times the machine will run until it
// kills its user

//charge_patient(patient & person) subtracts a cost from the patient's total
// money
//Pre:None
//Post:The cost per use is subtracted from the patient's money amount

//apply(patient & person) represents the patient "using" the liposuctionizer
// machine
//Pre:The patient has money to pay the machine and is alive
//Post:Patient's weight is reduced by a factor, mental state is increased,
// kills the user if machine has been used a certain number of times

//ostream& operator<<(ostream &out, const liposuctionizer &machine) overloads
// the insertion operator
//Pre:None
//Post:Displays the state of the machine

//liposuctionizer() default constructor to set the values in private
//Pre:None
//Post:m_num_uses and m_cost_per_use are given values

//getUses() retrieves the machine's uses
//Pre:None
//Post:The machine's number of uses is returned

class liposuctionizer
{
  public:
	void charge_patient(patient & person);
	void apply(patient & person); 
	friend ostream& operator<<(ostream &out, const liposuctionizer &machine);
	liposuctionizer();	
	short getUses() {return m_num_uses;}
  private:
    short m_num_uses;
	float m_cost_per_use;
};
#endif