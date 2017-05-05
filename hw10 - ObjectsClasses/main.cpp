//Name:Samuel Itschner
//Date:4/15/2012
//Description:Implementation of Dr. Nick's services
//File:main.cpp

#include "patient.h"
#include "hospitalroom.h"
#include "doctor.h"
#include "xrayer.h"
#include "lobotomizer.h"
#include "organ_donor.h"
#include "placaeboizer.h"
#include "pharmacy.h"
#include "liposuctionizer.h"

const string NAME = "Nick"; //Name of the doctor
const int NUM_PATS = 10; //Number of patients to declare

int main()
{
  srand(time(NULL));
  patient pats [NUM_PATS];
  doctor man(NAME);
  hospital_room <lobotomizer> lobotomizer;
  hospital_room <organ_donor> organ_donor;
  hospital_room <placaeboizer> placaeboizer;
  hospital_room <pharmacy> pharmacy;
  hospital_room <liposuctionizer> liposuctionizer;
  hospital_room <x_rayer> x_rayer;
  cout << " \t  Dr.Nick's Hospital:" << endl
  << "\t \t Initial:" << endl << man << endl;
  cout << lobotomizer << organ_donor << placaeboizer << pharmacy
       << liposuctionizer << x_rayer;
  for(int o = 0;o < NUM_PATS; o++)
  {
    cout << "Patient " << o+1 << ":" << pats[o] << endl;
  }
  for (int i = 0; i < NUM_PATS; i++)
  {
    lobotomizer.admit(pats[i],man);
    organ_donor.admit(pats[i],man);
    placaeboizer.admit(pats[i],man);
    pharmacy.admit(pats[i],man);
    liposuctionizer.admit(pats[i],man);
    x_rayer.admit(pats[i],man);
  }
  man.collectMoney(lobotomizer.getUses() * COST_PER_USE_LOBO);
  man.collectMoney(organ_donor.getUses() * COST_PER_USE_ORGA);
  man.collectMoney(placaeboizer.getUses() * COST_PER_USE_PLAC);
  man.collectMoney(pharmacy.getUses() * COST_PER_USE_PHARM);
  man.collectMoney(liposuctionizer.getUses() * COST_PER_USE_LIPO);
  man.collectMoney(x_rayer.getUses() * COST_PER_USE_XRAY);

  cout << " \t \t After: " << endl << man << endl;
  cout << lobotomizer << organ_donor << placaeboizer << pharmacy
       << liposuctionizer << x_rayer;
  for(int o = 0;o < NUM_PATS; o++)
  {
    cout << "Patient " << o+1 << ":" << pats[o] << endl;
  }
}
