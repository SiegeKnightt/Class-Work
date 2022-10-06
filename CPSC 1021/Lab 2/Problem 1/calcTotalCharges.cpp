#include <iostream>
#include <iomanip>
#include "calcTotalCharges.h"
#include "validateUserInput.h"

using namespace std;

// Function for inpatient
double calcTotalCharges(int numDays, double roomRate, double chargeService, double chargeMeds) {

    double total;

    // Equation to calculate total for inpatient
    total = (numDays * roomRate) + chargeService + chargeMeds;

    return total;
}

// Function for outpatient
double calcTotalCharges(double chargeService, double chargeMeds) {

    double total;

    // Equation to calculate total for outpatient
    total = chargeService + chargeMeds;

    return total;
}