//amath 483/583
//homework 1 code
//problems 1 and 3 

#include <iostream>
#include <cmath>
#include <iomanip>

//using namespace std;

int main() {
    
    //problem 1 - machine epsilon
    std::cout << "Problem 1" << std::endl;
    // float, 32-bit
    float x = 1.;
    float fmeps = (1./2.);
    float y = 0.;
    int j = 0;
    while (x!=y)
    {
        j++;
        y = 1. + powf(fmeps,j);
    }
    std::cout << "float 32-bit precision: (1/2)^" << j-1 << std::endl;
    std::cout << "float 32-bit machine epsilon: " << std::setprecision(16) << powf(fmeps,j-1) << std::endl;
    
    // double, 64-bit
    double xd = 1.;
    double dmeps = (1./2.);
    double yd = 0.;
    int i = 0;
    while (xd!=yd)
    {
        i++;
        yd = 1. + pow(dmeps,i);
    }
    std::cout << "\ndouble 64-bit precision: (1/2)^" << i-1 << std::endl;
    std::cout << "double 64-bit machine epsilon: " << std::setprecision(16) << pow(dmeps,i-1) << std::endl;
    
    //note that 
    std::cout << "\twith 52: " << 1. - (1.+pow(.5,52)) << std::endl; //correct
    std::cout << "\twith 53: " << 1. - (1.+pow(.5,53)) << std::endl; //yields zero

    //problem 3 - integer overflow and underflow
    std::cout << "\nProblem 3" << std::endl;
    int k = 200*300*400; //I don't multiply the 500 yet to suppress compiler overflow warning 
    std::cout << "200*300*400*500: " << k*500 << std::endl;

    return 0;
}
