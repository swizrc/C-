//Name: Samuel Itschner
//Date: 4/5/2012
//Description: Contains the functions for the hospital_room function
//File:hospitalroom.hpp

template <class T_machine>
void hospital_room<T_machine>::admit(patient & person, doctor & guy)
{
  if(person.getAlive() == true && person.getMoney() > 0)
  {
	int drink_amt, num_apps;
	drink_amt = (rand() % (MAX_DRINK+1-MIN_DRINK) + MIN_DRINK);
	if(m_gin_amount < 0)
	{
      m_gin_amount = 0;
    }
	if(drink_amt <= m_gin_amount && m_gin_amount > 0)
	{ 
      m_gin_amount = m_gin_amount - drink_amt;
	  guy.setGin(guy.getGin() + drink_amt);
	  num_apps = guy.getGin() - 5;
	  if(m_gin_amount < 0)
	  {
        m_gin_amount = 0;
      }
	  for(int i = 1;i <= num_apps;i++)
	  {
		if(person.getAlive() == true && person.getMoney() > 0)
		{  
		  m_the_machine.charge_patient(person);
		  m_the_machine.apply(person);
		}  
	  }
    }
    if(drink_amt > m_gin_amount && m_gin_amount > 0)
    {
      m_gin_amount = 0;
	  guy.setGin(guy.getGin() + m_gin_amount);
	  num_apps = guy.getGin() - 5;
	  if(m_gin_amount < 0)
	  {
        m_gin_amount = 0;
      }
	  for(int i = 1;i <= num_apps;i++)
	  {
	    if(person.getAlive() == true && person.getMoney() > 0)
		{ 
		  m_the_machine.charge_patient(person);
		  m_the_machine.apply(person);
		}
	  }
    }
	if(m_gin_amount <= 0)
	{
	  if(m_gin_amount < 0)
	  {
        m_gin_amount = 0;
      }
	  num_apps = (guy.getGin() - 5) * 2;
	  for(int i = 1;i <= num_apps;i++)
	  {
	    if(person.getAlive() == true && person.getMoney() > 0)
		{  
		  m_the_machine.charge_patient(person);
		  m_the_machine.apply(person);
		}  
	  }
	}
  }	
}

template <class T_machine>
hospital_room<T_machine>::hospital_room () : m_gin_amount(GIN_AMOUNT) {}

template <class U>
ostream& operator<< (ostream &out, const hospital_room<U> &cRoom)
{
  out << "In this hospital room, there are " << cRoom.m_gin_amount << 
  " ounces of gin and " << cRoom.m_the_machine << endl;
  return out;
}