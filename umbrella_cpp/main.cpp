/* 
 * File:   main.cpp
 * Author: joan
 * Created on 29 September 2015, 15:30
 */
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

float kT=10.; //Yes, by now I'll' leave it here

float potential(float x){
    float U=pow((x-2.),4)-6.*pow((x-2.),2)+2.*(x-2.);
    return U;
}
float perturbation(float x0){
    float x=x0+rand();/*deciding how to set the perturbation*/
    return x;
}

float metropolis(float metro_input[2]){
    float U=metro_input[0];
    float U0=metro_input[1];
    float metro=exp((U-U0)/kT);
    float R=rand(); 
    if (metro<R)
    {
     return 1;//Accepted
    }
    else
    {
     return 0; //Rejected
    }
}

float MonteCarlo (float initial_values[5]){
    
    float x0=initial_values[0];
    float U0=initial_values[1];
    int acceptedSteps=initial_values[2];
    int totalSteps=initial_values[3];
    int maxSteps=initial_values[4];
 
    if (totalSteps<maxSteps)
    {
        int totalSteps=totalSteps+1;
        float x=perturbation(x0);
        float U=potential(x);
        if (U<U0)
        {
         int acceptedSteps=acceptedSteps+1;
         float results[4]={x, U, acceptedSteps, totalSteps};
         cout<< results;
        }
        else
        {
         float metro_input[2]={U,U0};
         int metro_output=metropolis(metro_input);
         if (metro_output==1)
         {
          int acceptedSteps=acceptedSteps+1;
          float results[4]={x, U, acceptedSteps, totalSteps};
          cout<< results;
          initial_values[5]={x,U,acceptedSteps,totalSteps,maxSteps};
          results[4]=MonteCarlo(initial_values);
         }
         else
         {
          float results[4]=MonteCarlo(initial_values);
         }
        }
    }
    else
    {
        cout<< "Reached the maximum number of steps. Stopping";
        return 0;
    }
}


int main() {
    
    srand (19121988); // initialize random seed
  
    float x0=3.0;
    float U0=potential(x0);
    int acceptedSteps=0;
    int totalSteps=0;
    int maxSteps=100;
  
    float initial_values[5]={x0,U0,acceptedSteps,totalSteps,maxSteps};
    return 0;
}

