/* 
 * File:   main.cpp
 * Author: joan
 * Created on 29 September 2015, 15:30
 */
#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

float kT=2.; //Yes, by now I'll' leave it here

float RandomFloat (float lower, float upper){
    float random1=rand();
    float randmax=RAND_MAX;
    float random=(upper-lower)*(random1/randmax)+lower;
    return random;
}

float potential(float x){
    float U=pow((x-2.),4)-6.*pow((x-2.),2)+2.*(x-2.);
    return U;
}
float RandomPerturbation(float x0, float perturbSize){
    float x=x0+perturbSize*RandomFloat(-1,1);
    return x;
}

float PositivePerturbation(float x0, float perturbSize){
    float x=x0+perturbSize;
    return x;
}

float metropolis(float metro_input[2]){
    float U=metro_input[0];
    float U0=metro_input[1];
    float metro=exp(-((U-U0)/kT));
    float R=RandomFloat(0,1);
    
    if (metro<R)
    {
     return 1;//Accepted
    }
    else
    {
     return 0; //Rejected
    }
}

float MonteCarlo (float initial_values[6]){
    
    float x0=initial_values[0];
    float U0=initial_values[1];
    int acceptedSteps=initial_values[2];
    int totalSteps=initial_values[3];
    int maxSteps=initial_values[4];
    float perturbSize=initial_values[5];
    cout << x0;
    cout << ' ';
    cout << U0;
    cout << ' ';        
    cout << acceptedSteps;
    cout << ' ';
    cout << totalSteps;
    cout << '\n';
 
    if (totalSteps<maxSteps)
    {
        totalSteps=totalSteps+1;
        float x=RandomPerturbation(x0,perturbSize);
        float U=potential(x);
        if (U<=U0)
        {
            acceptedSteps=acceptedSteps+1;
            //float results[4]={x, U, acceptedSteps, totalSteps};
            float initial_values[6]={x,U,acceptedSteps,totalSteps,maxSteps,perturbSize};
            MonteCarlo(initial_values);
        }
        else
        {
            float metro_input[2]={U,U0};
            int metro_output=metropolis(metro_input);
            if (metro_output==1)
            {
                acceptedSteps=acceptedSteps+1;
                //float results[4]={x, U, acceptedSteps, totalSteps};
                float initial_values[6]={x,U,acceptedSteps,totalSteps,maxSteps,perturbSize};
                MonteCarlo(initial_values);
            }
            else
            { 
                float initial_values[6]={x0,U0,acceptedSteps,totalSteps,maxSteps,perturbSize};
                MonteCarlo(initial_values);
            }
        }
    }
    else
    {
        cout<< "Reached the maximum number of steps. Stopping.\n";
        return 0;
    }
}


int main() {
    
    srand (19121988); // initialize random seed
    float perturbSize=0.05;
  
    float x0=4.;
    float U0=potential(x0);
    int acceptedSteps=0;
    int totalSteps=0;
    int maxSteps=100000;
  
    float initial_values[6]={x0,U0,acceptedSteps,totalSteps,maxSteps,perturbSize};
    MonteCarlo(initial_values);
    return 0;
}

