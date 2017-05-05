void paranoid_riff2()//Second riff to Paranoid by Black Sabbath with a twist, cheap memory song
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
	  play(2,-5);
	  while(duration_count>0){}
	  up_oct();
	}  
	for(i=0;i<8;i++)
	{
	  play(6,-5);
	  while(duration_count>0){}
	  down_oct();
	}  
}
void hash_pipe()//Riff to Hash Pipe by Weezer, dirt poor memory song
{
	unsigned char i;
	down_oct();
	for(i=0;i<4;i++)
	{
	  play(5,-4);
	  while(duration_count>0){}
	  play(5,-4);
	  while(duration_count>0){}
	  play(6,-4);
	  while(duration_count>0){}
	  play(0,-4);
	  while(duration_count>0){}
	}
}

void paranoid_riff()//Plays the opening riff of Paranoid by Black Sabbath
// R = rest
{
  unsigned char Paranoid_Notes[] = {2,'R',2,'R',2,5,6,1,2,5,6,1,5};
  signed char Paranoid_Duration[] = {-2,-10,-2,-10,-2,-5,-5,-5,-5,-5,-5,-5,-5};
  unsigned char i;
	down_oct();
    for(i=0;i<7;i++)
	{
     play(Paranoid_Notes[i],Paranoid_Duration[i]);
	 while(duration_count>0){}
    }
	up_oct();
	for(i=7;i<9;i++)
	{
	 playd(Paranoid_Notes[i],Paranoid_Duration[i]);
	 while(duration_count>0){}
	}
	down_oct();
	for(i=9;i<11;i++)
	{
	 playd(Paranoid_Notes[i],Paranoid_Duration[i]);
	 while(duration_count>0){}
	}
	up_oct();
	 playd(Paranoid_Notes[11],Paranoid_Duration[11]);
	  while(duration_count>0){}
	down_oct();
	 playd(Paranoid_Notes[12],Paranoid_Duration[12]);
	 while(duration_count>0){}
	up_oct();
}