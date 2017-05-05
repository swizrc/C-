//Name: Samuel Itschner
//Date: 2/6/2012
//Description: Collects some statistics from an array

#include <iostream>
using namespace std;

float min(float arr[]);
float max(float arr[]);
float mean(float arr[]);

struct arrayStats
{
  float arr[5];
  float arrMin;
  float arrMax;
  float arrMean;
};  

int main()
{
  float Max, Mean, Min;
  arrayStats mystats;
  cout << "Please input the values you want in this array." << endl;
  for(int i = 0;i < 5; i++)
  {
    cin >> mystats.arr[i];
  }    
  
  Max = max(mystats.arr);
  Min = min(mystats.arr);
  Mean = mean(mystats.arr);
  cout << "Mean = " << Mean << " Max = " << Max << " Min = " << Min << endl;
}

float max(float arr[])
{
  float max;
  max = arr[0];
  for(int y=0; y < 5; y++)
  {
    if(arr[y] > max)
      max = arr[y];
  }    
  return max;
}

float min(float arr[])
{
  float min;
  min = arr[0];
  for(int j=0; j < 5; j++)
  {
    if(arr[j] < min)
      min = arr[j];
  }    
  return min;
}

float mean(float arr[])
{
  float sum, mean;
  for(int o=0; o < 5; o++)
  {
    sum = sum + arr[o];
  }
  mean = sum / 5;
  return mean;
}   

