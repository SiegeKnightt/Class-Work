#include <iostream>
#include "Patient.h"

using namespace std;

// Validates user input for double
bool Patient::validateInput(double input) {

    if (input < 0) {

        return false;
    }
    else {

        return true;
    }
}

// Validates user input for int
bool Patient::validateInput(int input) {

    if (input < 0) {

        return false;
    }
    else {

        return true;
    }
}

// Sets patient type to correct info
bool Patient::setPatientType(char pt) {

    patientType = pt;

    return validateInput(pt);
}

// Returns patient type
char Patient::getPatientType() {

    return patientType;
}

// Sets days in patient class and validates info
bool Patient::setDays(int d) {

    days = d;

    return validateInput(d);
}

// Returns days
int Patient::getDays() {

    return days;
}

// Sets rate in patient class and validates info
bool Patient::setRate(double r) {

    rate = r;

    return validateInput(r);
}

// Returns rate
double Patient::getRate() {

    return rate;
}

// Sets services in patient class and validates info
bool Patient::setServices(double s) {

    services = s;

    return validateInput(s);
}

// Returns services
double Patient::getServices() {

    return services;
}

// Sets medication in patient class and validates info
bool Patient::setMedication(double m) {

    medication = m;

    return validateInput(m);
}

// Returns medication
double Patient::getMedication() {

    return medication;
}

// Function for inpatient
double Patient::calcTotalCharges(int d, double r, double s, double m) {

    double total;

    // Equation to calculate total for inpatient
    total = (d * r) + s + m;

    return total;
}

// Function for outpatient
double Patient::calcTotalCharges(double s, double m) {

    double total;

    // Equation to calculate total for outpatient
    total = s + m;

    return total;
}

// Default calcTotalCharges
double Patient::calcTotalCharges() {

    return 0;
}