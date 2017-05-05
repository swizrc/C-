//Name: Samuel Itschner
//Date: 4/5/2012
//Description: Header file for the hospital_room class
//File:hospitalroom.h
#ifndef HOSPITALROOM_H
#define HOSPITALROOM_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "doctor.h"
using namespace std;

const int GIN_AMOUNT = 10; //Default amount of gin in a hospital room
const int MAX_DRINK = 3; //Maximum amount of ounces of gin the doctor can drink
const int MIN_DRINK = 1; //Minimum amount of ounces of gin the doctor can drink

//admit(patient & person) lets the patient in and uses the xrayer's functions
//Pre:None
//Post:charge_patient and apply functions of the xrayer class are executed

//hospital_room() is a default constructor setting the variables in private
//Pre:None
//Post:m_gin_amount is set to GIN_AMOUNT

//ostream& operator<< (ostream &out, const hospital_room &cRoom) is an 
//overloading of the insertion operator, meant to output the state of the 
//hospital_room
//Pre:None
//Post:The state of the hospital_room is displayed on-screen

//getUses() retrieves the machine's uses
//Pre:None
//Post:The machine's number of uses is returned

template <class T_machine>
class hospital_room
{
  public:
    void admit(patient & person, doctor & guy);
	hospital_room();
	template<typename U>
	friend ostream& operator<< (ostream &out, const hospital_room<U> &cRoom);
	int getUses() {return m_the_machine.getUses();}
  private:
    T_machine m_the_machine;
	short m_gin_amount;
};
#include "hospitalroom.hpp"
#endif