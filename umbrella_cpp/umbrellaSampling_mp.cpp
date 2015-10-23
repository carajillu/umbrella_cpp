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
#include <sstream>

#ifdef _OPENMP
   #include <omp.h>
#else
   #define omp_get_num_threads() 1
   #define omp_get_thread_num() 0
#endif

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

double window(double x0, int nSteps, double perturbSize, double k, string windowName){
    ofstream win;
    win.open(windowName.c_str());
    float U0=potential(x0,x0,k);
    int accepted=0;
    while (accepted<nSteps)
    {
        float x=RandomPerturbation(x0,perturbSize);
        float U=potential(x,x0,k);
        if (U<U0)
        {
         accepted++;
         win << x0 <<' '<< x << '\n';
        }
        else
        {
         int metro_output=metropolis(U,U0);
         if (metro_output==1)
         {
          accepted++;
          win << x0 <<' '<< x0 << '\n';
         }
        }
    }
    win.close();
}

string winame(int winum){
    stringstream sstm;
    sstm << "window" << winum;
    string windowName = sstm.str();
    //cout <<windowNumber<<'\n';
    return windowName;
}

int main() {
    double x0=0.;
    int nSteps=1000;
    double perturbSize=0.05;
    double k=10.;
    int nWin=50;
    double spacing=0.1;
    
    #pragma omp parallel
    { //into parallel environment
    
       int nthreads=omp_get_num_threads();
       cout<<"Detected "<<nthreads<<" openMP threads";      
 
       #pragma omp for  // run for loop in parallel
       for (int winum=0;winum<nWin+1;winum++)
       {
        int thread_id=omp_get_thread_num();
        string windowName=winame(winum);
        cout << "running window "<<windowName<<" in thread "<<thread_id<<"\n";
        x0=x0+spacing;
        window(x0,nSteps,perturbSize,k,windowName);
       } 
    } // out of parallel environment
    
    return 0;
}
/*I have to find out how to convert an int to an str and modify the window
 function so it outputs the values in a file for each window*/
