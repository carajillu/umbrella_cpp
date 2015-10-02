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
#include <vector>

using namespace std;

double kT=10.; //Yes, by now I'll' leave it here

double RandomFloat (double lower, double upper){
    double random1=rand();
    double randmax=RAND_MAX;
    double random=(upper-lower)*(random1/randmax)+lower;
    return random;
}

double potential(double x){
    double U=pow((x-2.),4)-6.*pow((x-2.),2)+2.*(x-2.);
    return U;
}

double force_numeric(double x, double x0,double U,double U0){
    double f=-((U-U0)/(x-x0));
    return f;
    // something is wrong here, because it doesn't approximate U-U0
}

double RandomPerturbation(double x0, double perturbSize){
    double x=x0+perturbSize*RandomFloat(-1,1);
    return x;
}

double PositivePerturbation(double x0, double perturbSize){
    double x=x0+perturbSize*RandomFloat(0,1);
    return x;
}

double NegativePerturbation(double x0, double perturbSize){
    double x=x0-perturbSize*RandomFloat(0,1);
    return x;
}

double metropolis(double metro_input[2]){
    
    double U=metro_input[0];
    double U0=metro_input[1];
    double metro=exp(-((U-U0)/kT));
    double R=RandomFloat(0,1);
    
   // cout << "metropolis ";
  //  cout << metro;
   // cout << '\n';
    
    if (metro>R)
    {
     return 1;//Accepted
    }
    else
    {
     return 0; //Rejected
    }
}

double MonteCarlo_maxSteps (double initial_values[6]){
    double x0=initial_values[0];
    double U0=initial_values[1];
    int acceptedSteps=initial_values[2];
    int totalSteps=initial_values[3];
    int maxSteps=initial_values[4];
    double perturbSize=initial_values[5];
    
    double work_n=U0;
    double f=0;
    
    for (int i=1; i<maxSteps; i++)
    {
        totalSteps++;
        double x=RandomPerturbation(x0,perturbSize);
        double U=potential(x);
        if (U<U0)
        {
         acceptedSteps++;
         f=force_numeric(x,x0,U,U0);
         work_n=work_n+f;
         cout <<x<<' '<<U<<' '<<f<<' '<<work_n<<'\n';
         x0=x;
         U0=U;
        }
        else
        {
          double metro_input[2]={U,U0};
            int metro_output=metropolis(metro_input);
            if (metro_output==1)
            {
                acceptedSteps=acceptedSteps+1;
                f=force_numeric(x,x0,U,U0);
                work_n=work_n+f;
                cout <<x<<' '<<U<<' '<<f<<' '<<work_n<<'\n';
                x0=x;
                U0=U;
            }    
        }
        //cout <<x0<<' '<<U0<<' '<<acceptedSteps<< ' '<<totalSteps<<'\n';
    }
}
/*
double MonteCarlo_rec (double initial_values[6]){
    
    double x0=initial_values[0];
    double U0=initial_values[1];
    int acceptedSteps=initial_values[2];
    int totalSteps=initial_values[3];
    int maxSteps=initial_values[4];
    double perturbSize=initial_values[5];
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
        double x=RandomPerturbation(x0,perturbSize);
        double U=potential(x);
        if (U<=U0)
        {
            acceptedSteps=acceptedSteps+1;
            //double results[4]={x, U, acceptedSteps, totalSteps};
            double initial_values[6]={x,U,acceptedSteps,totalSteps,maxSteps,perturbSize};
            MonteCarlo(initial_values);
        }
        else
        {
            double metro_input[2]={U,U0};
            int metro_output=metropolis(metro_input);
            if (metro_output==1)
            {
                acceptedSteps=acceptedSteps+1;
                //double results[4]={x, U, acceptedSteps, totalSteps};
                double initial_values[6]={x,U,acceptedSteps,totalSteps,maxSteps,perturbSize};
                MonteCarlo(initial_values);
            }
            else
            { 
                double initial_values[6]={x0,U0,acceptedSteps,totalSteps,maxSteps,perturbSize};
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
*/

int main() {
    
    srand (19121988); // initialize random seed
    double perturbSize=0.005; //actually we can use even larger steps
  
    double x0=3.64;
    double U0=potential(x0);
    int acceptedSteps=0;
    int totalSteps=0;
    int maxSteps=1000;  
  
    double initial_values[6]={x0,U0,acceptedSteps,totalSteps,maxSteps,perturbSize};
    MonteCarlo_maxSteps(initial_values);
    
    
    return 0;
}

