/*
My Name: Joseph Reeves Farrell
My Class: CPSC 1021
Date: 9/6/2022
Desc: Retirment calulator to calculate the user's retirement savings
Time: ~ 30 mins
*/

#include <iostream>
#include <iomanip>
#include "compoundCalc.h"
using namespace std;

int main () {

    double principalValue;
    double interestRate;
    double years;

    cout << "Enter principal value: " << endl;

    cin >> principalValue;

    cout << "Enter interest rate as a decimal: " << endl;

    cin >> interestRate;

    cout << "Enter number of years: " << endl;

    cin >> years;

    // Calls compoundCalc function
    cout << "Your retirement savings will be $" << fixed << setprecision(2) << compoundCalc(principalValue, interestRate, years) << endl;

    return 0;
}