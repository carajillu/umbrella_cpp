/* 
 * File:   umbrellaSampling.cpp
 * Author: joan
 *
 * Created on 02 October 2015, 09:46
 */

#include <cstdlib>
#include <math.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

double kT=2;

double RandomFloat (double lower, double upper){
    double random1=rand();
    double randmax=RAND_MAX;
    double random=(upper-lower)*(random1/randmax)+lower;
    return random;
}

double metropolis(double U, double U0){
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

double potential(double x, double x0, double k){
    double U=pow((x-2.),4)-6.*pow((x-2.),2)+2.*(x-2.)+0.5*k*(pow((x-x0),2));
    return U;
}

double RandomPerturbation(double x0, double perturbSize){
    double x=x0+perturbSize*RandomFloat(-1,1);
    return x;
}

double window(double x0, int nSteps, double perturbSize, double k/*, string WindowName*/){
    //ofstream win (WindowName);
    float U0=potential(x0,x0,k);
    for (int i=0;i<nSteps;i++)
    {
        i++;
        float x=RandomPerturbation(x0,perturbSize);
        float U=potential(x,x0,k);
        if (U<U0)
        {
         cout << x0 <<' '<< x << '\n';
        }
        else
        {
         int metro_output=metropolis(U,U0);
         if (metro_output==1)
         {
          cout << x0 <<' '<< x0 << '\n';
         }
        }
    }
}

/*
string winame(int winum){
    string useless="window";
    string WindowName=useless+std::(winum);
    return WindowName;
}
*/
int main() {
    double x0=4.;
    int nSteps=10;
    double perturbSize=0.05;
    double k=10.;
    int nWin=50;
    double spacing=0.1;
    
    for (int winum=0;winum<nWin+1;winum++)
    {
   /*  string WindowName=winame(winum);*/
     x0=x0+spacing;
     window(x0,nSteps,perturbSize,k/*,windowName*/);
    }
    
    return 0;
}
/*I have to find out how to convert an int to an str and modify the window
 function so it outputs the values in a file for each window*/
