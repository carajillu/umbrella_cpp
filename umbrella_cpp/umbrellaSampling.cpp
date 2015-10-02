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

double RandomFloat (double lower, double upper){
    double random1=rand();
    double randmax=RAND_MAX;
    double random=(upper-lower)*(random1/randmax)+lower;
    return random;
}

double potential(double x, double x0, double k){
    double U=pow((x-2.),4)-6.*pow((x-2.),2)+2.*(x-2.)+0.5*k*(pow((x-x0),2));
    return U;
}

double RandomPerturbation(double x0, double perturbSize){
    double x=x0+perturbSize*RandomFloat(-1,1);
    return x;
}

double window(float x0, int nSteps, float perturbSize,float k, string WindowName){
    ifstream
    float U0=potential(x0,x0,k);
    for (int i=0;i,nSteps;i++)
    {
        i++;
        float x=RandomPerturbation(x0,perturbSize);
        float U=potential(x,x0,k);
        if (U<U0)
        {
            
        }
    }
}
/*
 * 
 */
int main() {
    
    return 0;
}

