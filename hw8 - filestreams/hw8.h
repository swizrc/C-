//Name: Samuel Itschner
//Date: 3/19/2012
//Description: Header file for the random poem generator program
//File: hw8.h

#ifndef HW8_H
#define HW8_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
using namespace std;

//Size of the arrays
const int ARRAY_SIZE = 50;

//Greets the user
//Pre:None
//Post:Greeting is displayed
void greeting();

//Farewells the user
//Pre:None
//Post:Goodbye meassage is displayed
void goodbye();

//Retreives a file for the stream
//Pre: File must exist
//Post: Stream is connected to file
void get_file(ifstream & filename, const string file);

//Grabs a random line from a file
//Pre:Stream is connected to a file
//Post:A random line from the file fills an array
void get_dat(ifstream & filename, char array[]);

//Holds all the processes to create a random poem
//Pre:None
//Post:A random line of poetry is shown to the user
void makePoem();

//Collects the amount of lines the user wants
//Pre:None
//Post:Returns a number greater than zero, entered by the user
int num_lines();

//Returns a random number
//Pre:Number of data lines in the file
//Post:Returns a random number between 2 and the number of data lines
int random(const int UPPER_LIMIT);

#endif
