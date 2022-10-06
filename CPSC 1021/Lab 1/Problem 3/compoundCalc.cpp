#include <iostream>
#include <iomanip>
// Used to exponentiate in the formula
#include <cmath>
#include "compoundCalc.h"
using namespace std;

double compoundCalc (double principalValue, double interestRate, double years) {
    
    double retirementSavings;

    // Calculates retirement savings by
    // multiplying the principal value
    // by (1 + the interest rate) ^ years
    retirementSavings = principalValue * pow((1 + interestRate), years);

    return retirementSavings;
}