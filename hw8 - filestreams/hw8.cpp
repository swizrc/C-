//Name: Samuel Itschner
//Date: 3/19/2012
//Description: Contains functions used in the random poem generator
//File: hw8.cpp

#include "hw8.h"
void greeting()
{
  cout << "\t \t Welcome to the Random Poem Generator." << endl;
  return;
}  

void goodbye()
{
  cout << "Later" << endl;
  return;
}

int num_lines()
{
  int lines;
  do
  {
    cout << "How many lines do you want in your poem?" << endl;
    cin >> lines;
  }
  while(lines < 1);
  return lines;
}

void get_file(ifstream & filename, const string file)
{  
  string dat_file;
  filename.clear();
  filename.open(file.c_str());
  while (!filename)
  {
    filename.clear();
    cout << "Enter file to connect to: " << endl;
    cin >> dat_file;
    filename.open(dat_file.c_str());
  }
  return;
}
  
int random(const int UPPER_LIMIT)
{
  int rand_num;
  rand_num = rand() % (UPPER_LIMIT - 1) + 2;
  return rand_num;
}


void makePoem()
{
  ifstream fin;
  get_file(fin, "patterns.dat");
  char pattern[ARRAY_SIZE];
  get_dat(fin, pattern);
  fin.close();
  int i = 0;
  while(pattern[i] != '-') //Replaces the integers in the array with their
  //respective words: 1=nouns, 2=adjectives, 3=verbs, 4=pronouns, 5=adverbs
  //6=interjections
  {
    switch (pattern[i])
    {
      case '1':
      {
        get_file(fin, "nouns.dat");
        char noun[ARRAY_SIZE];
        get_dat(fin, noun);
        int p = 0;
        while(noun[p] != '-')
        {
          cout << noun[p];
          p++;
        }
        fin.close();     
        break;
      }
      case '2':
      {
        get_file(fin, "adjectives.dat"); 
        char adjective[ARRAY_SIZE];
        get_dat(fin, adjective);
        int p = 0;
        while(adjective[p] != '-')
        {
          cout << adjective[p];
          p++;
        }      
        fin.close();
        break;
      }
      case '3':
      {
        get_file(fin, "verbs.dat");
        char verb[ARRAY_SIZE];
        get_dat(fin, verb);
        int p = 0;
        while(verb[p] != '-')
        {
          cout << verb[p];
          p++;
        }        
        fin.close();
        break;
      }
      case '4':
      {
        get_file(fin, "pronouns.dat");
        char pronoun[ARRAY_SIZE];
        get_dat(fin, pronoun);
        int p = 0;
        while(pronoun[p] != '-')
        {
          cout << pronoun[p];
          p++;
        }
        fin.close();
        break;
      }
      case '5':
      {
        get_file(fin, "adverbs.dat");
        char adverb[ARRAY_SIZE];
        get_dat(fin, adverb);
        int p = 0;
        while(adverb[p] != '-')
        {
          cout << adverb[p];
          p++;
        }  
        fin.close();
        break;
      }
      case '6':  
      {
        get_file(fin, "interjections.dat");
        char interjection[ARRAY_SIZE];
        get_dat(fin, interjection);
        int p = 0;
        while(interjection[p] != '-')
        {
          cout << interjection[p];
          p++;
        }  
        fin.close();
        break;
      }  
      default://simply displays the character if not an integer
      {
        cout << pattern[i];
      }  
    }
  i++;
  }
}

void get_dat(ifstream & filename, char array[])
{
  int num_data, Rand;
  filename >> num_data;
  Rand = random(num_data);
  for(int i=1;i <= Rand; i++)
  {
    filename.getline(array, (ARRAY_SIZE - 1), '\n');
  }
  return;
}  
