// Cynthia Hong
// HW1
// Problem1
#include <iostream>
#include <cmath>

int main()
{
    // finds a practica; measure of machine's SP(32 bit)
    int i = 0.0;
    float resultSP = 0.0f;
    while ((1.0f - (1.0f + std::powf(2.0, -i))) != 0.0f)
    {
        resultSP = std::powf(2.0, -i);
        i++;
    }
    std::cout << "The measure of SP (32 bit) is " << resultSP << "." << std::endl;
    // The measure of SP (32 bit) is 1.19209e-07.

    // finds a practica; measure of machine's DP(64 bit)
    int j = 0;
    double resultDP = 0.0;
    while ((1 - (1 + std::pow(2, -j))) != 0)
    {
        resultDP = std::pow(2, -j);
        j++;
    }
    std::cout << "The measure of DP (64 bit) is " << resultDP << "." << std::endl;
    // The measure of DP (64 bit) is 2.22045e-16.
}

// Answer: The practical measure of machine's SP precision is 1.19209e-07 and that
//         of DP's is 2.22045e-16 by taking the difference of 2 numbers and comparing
//         the result to zero in each data type.