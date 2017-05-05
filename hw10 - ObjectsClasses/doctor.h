//Name:Samuel Itschner
//Date:4/15/2012
//Description:Header for the doctor class
//File:doctor.h
#ifndef DOCTOR_H
#define DOCTOR_H
#include <iostream>
using namespace std;

const short GIN_AMT = 0;//Original amount the constructor will use to set 
//the amount of gin
const float MONEY = 0;//Original amount the constructor will use to set the
//money amount
const short PUKE = 25;//Amount of gin needed to activate the puke function

//doctor(const string name) is a default constructor to set the values of the class
//Pre:None
//Post:m_name, m_gin_amt, and m_money are all assigned values

//puke() will reset the amount of gin in the doctor
//Pre:None
//Post:m_gin_amt is set to 0 if m_gin_amt is above PUKE

//getGin() retrieves the amount of gin in the doctor's body
//Pre:None
//Post:The amount of gin in the doctor is returned

//setGin(int gin_amt) sets the doctor's gin amount
//Pre:None
//Post:The doctor's gin amount is set to the number passed in

//collectMoney(int money) collects the money collected by the machines
//Pre:None
//Post:The doctor's money amount is updated by the number of times the machine
// was used and the cost_per_use

//ostream& operator<<(ostream &out, const doctor &doc) overloads the
//insertion operator to output the state of the doctor class
//Pre:None
//Post:The state of the doctor is displayed on-screen

class doctor
{
  public:
	doctor(const string name);
    void puke();
	short getGin() {return m_gin_amt;}
	void setGin(int gin_amt);
	void collectMoney(float money);
	friend ostream& operator<<(ostream &out, const doctor &doc);
  private:
    string m_name;
	short m_gin_amt;
	float m_money;
	int m_num_puke;
};

#endif