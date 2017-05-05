//Name: Samuel Itschner
//Date: 4/18/2012
//Description: Header file for the pharmacy class
//File:pharmacy.h
#ifndef PHARMACY_H
#define PHARMACY_H
#include "patient.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

const int COST_PER_USE_PHARM = 150; //How much the patient will be charged every
// time they use this machine
const int UPPER_LIMIT_PILLS = 100; //Upper limit for the random number generator
// for pills
const int LOWER_LIMIT_PILLS = 50; //Lower limit for the random number generator
// for pills
const int DISTRESS = -23; //If the pharmacy runs out of pills, this is how
// much the patient's mental health will be altered
const int WEIGHT_DISTRESS = 44; //If the pharmacy runs out of pills, this is
// how much the patient's weight will be altered
const int NORM_COND = 10; //If prob is less than 25, alters physical
// condition
const int NORM_MENT = -10; //If prob is less than 25, alters mental condition
const int BRAIN_DEAD = 0; //If prob is more than 25, less than 50, sets
// mental condition
const int BRAIN_DEAD_COND = 20; //If prob is more than 25, less than 50, 
// alters physical condition
const int MIDDLE = 50; //If prob is more than 50, less than 75, sets
// physical condition
const int FAT = 100; //If prob is more than 75, less than 100, sets weight
const int HAPPY = 100; //If prob is more than 75, less than 100, sets
// mental condition

//randPills() gives the pharmacy machine a random amount of pills
//Pre:None
//Post:m_num_pills is set to a random amount

//pharmacy() default constructor setting the private variables
//Pre:None
//Post:m_num_uses, m_cost_per_use, and m_num_pills are set to values

//charge_patient(patient & person) subtracts a cost from the patient's total
// money
//Pre:None
//Post:The cost per use is subtracted from the patient's money amount

//ostream& operator<<(ostream &out, const pharmacy &machine)
//Pre:None
//Post:State of the pharmacy is displayed

//apply(patient & person) represents the patient "using" the pharmacy
// machine
//Pre:The patient has money to pay the machine and is alive
//Post:Every use subtracts a pill from the machine, the pill is used and
// executes 1 out of 4 sets of effects 

//getUses() retrieves the machine's uses
//Pre:None
//Post:The machine's number of uses is returned

class pharmacy
{
  public:
    int randPills();
	pharmacy();
	void charge_patient(patient & person);
	friend ostream& operator<<(ostream &out, const pharmacy &machine);
	void apply(patient & person);
	short getUses() {return m_num_uses;}
  private:
    short m_num_uses;
	float m_cost_per_use;
	short m_num_pills;
};
#endif