//Name: Samuel Itschner
//Date: 4/5/2012
//Description: Header file for the patient class
//File:patient.h
#ifndef PATIENT_H 
#define PATIENT_H
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
using namespace std;

const string NAME_PAT = "names.dat"; // Name of file of names
const int MAX_MONEY = 40000; //Maximum amount of money the patient can have.
//IMPORTANT: Multiply number desired by 10 to apply to the program
const int MAX_COND = 100; //The maximum amount the patient's condition can
//be set to
const int MAX_MENTAL = 100;//Maximum amount the patient's mental health can be
const int MAX_WEIGHT = 120;//Maximum amount the patient's weight can be
const int MIN_WEIGHT = 220;//Minimum amount the patient's weight can be

//randName() returns a string to use for the name of the patient, chosen at
//random from an external .dat file
//Pre:None
//Post:Returns a random name string for the patient's private name variable

//modify_health(int mod_num) changes the conditon of the patient
//Pre:None
//Post:condition is altered by mod_num and the kill() function is called

//pay_out(float price) price is subtracted from m_money, 
//making the new m_money
//Pre:None
//Post: A new m_money is set from the difference of m_money and price

//patient() is a constructor that sets the private variables of the class
//Pre:None
//Post:m_is_alive, m_money, m_condition and m_name are all assigned values

//RandCond() makes condition set to a random value
//Pre:None
//Post:Sets the patient's condition between am upper and lower limit

//RandMent() makes mental_health a random number
//Pre:None
//Post:mental health is a random value

//RandWeight() randomly assigns the patient a weight value
//Pre:None
//Post:weight is a random value between an upper and lower limit

//setMoney() makes money set to a random value
//Pre:None
//Post:Money variable is randomly set between 0 and an upper limit

//ostream& operator<< (ostream &out, const patient &person) is an overloading  
//of the insertion operator, meant to output the state of the patient
//Pre:None
//Post:The state of the patient is displayed on-screen

//getCond() retrieves the patient's physical condition
//Pre:None
//Post:Patient's physical condition is returned

//getMent() retrieves the patient's mental health
//Pre:None
//Post:Patient's mental health is returned

//getWeight() retrieves the patient's weight
//Pre:None
//Post:Patient's weight is returned

//getAlive() retrieves the patient's state of aliveness
//Pre:None
//Post:Whether the patient is alive or not is returned

//getMoney() retrieves the patient's money
//Pre:None
//Post:Patient's money amount is returned

//getName() retrieves the patient's name
//Pre:None
//Post:Patient's name is returned

//setMent(const int mental_condition) sets the patient's mental health
//Pre:None
//Post:Mental condition is set to the number passed in

//setName(const string name) sets the patient's name
//Pre:None
//Post:Patient's name is set to the string passed in

//setWeight(const int weight) sets the patient's weight
//Pre:None
//Post:Patient's weight is set to the number passed in

//setCond(const int cond) sets the patient's condition
//Pre:None
//Post:Patient's physical condition is set to the number passed in

//kill() updates is_alive if condition is 0 or below
//Pre:None
//Post:Changes the is_alive variable to false if patient's condition is 
//zero or lower and makes sure is_alive is true if patient's condition is
//above zero

class patient
{
  public:
	string randName();
	void modify_health(int mod_num);
	void pay_out(float price);
	patient();
    int RandCond();
	int RandMent();
	int RandWeight();
	float setMoney();
	friend ostream& operator<< (ostream &out, const patient &person);
	int getCond() {kill();return m_condition;}
	int getMent() {kill();return m_mental_condition;}
	int getWeight() {kill();return m_weight;}
	bool getAlive () {kill();return m_is_alive;}
	float getMoney () {kill();return m_money;}
	string getName() {kill();return m_name;}
	void setMent (int mental_condition);
	void setName (string name);
	void setWeight (int weight);
	void setCond (int cond);
  private:
    void kill();
	bool m_is_alive;
	float m_money;
	int m_condition;
	string m_name;
	int m_mental_condition;
	int m_weight;
};
#endif