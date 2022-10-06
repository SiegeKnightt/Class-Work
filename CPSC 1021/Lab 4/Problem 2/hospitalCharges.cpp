/*
My Name: Joseph Reeves Farrell
My Class: CPSC 1021
Date: 9/26/2022
Desc: Application to gather patient info and 
determine the total cost of their hospital stay
using OOP classes
Time: 1 hour
*/

#include <iostream>
#include <iomanip>
#include "Patient.h"

using namespace std;

int main () {

    char userInput;
    int numDays;
    double roomRate;
    double chargeService;
    double chargeMeds;

    // Counter variable
    int x = 0;

    // Patient class initalized
    Patient pat;

    cout << "This program will calculate a patient's hospital charges." << endl;
    cout << "Enter I for in-patient or O for out-patient:" << endl;

    while (x == 0) {

        cin >> userInput;

        pat.setPatientType(userInput);
        
        // User option for inpatient
        if (userInput == 'I') {

            // Input for days in hospital
            cout << "Number of days in the hospital:" << endl;

            cin >> numDays;

            pat.setDays(numDays);

            // Input for room rate
            cout << "Daily room rate ($):" << endl;

            cin >> roomRate;
                
            pat.setRate(roomRate);

            cout << "Lab fees and other service charges ($):" << endl;

            cin >> chargeService;
                
            pat.setServices(chargeService);

            cout << "Medication charges ($):" << endl;

            cin >> chargeMeds;
                
            pat.setMedication(chargeMeds);

            cout << "Your total hospital bills is $" << fixed << setprecision(2) << pat.calcTotalCharges(numDays, roomRate, chargeService, chargeMeds) << endl;

            // Increments x to exit the loop
            ++x;
        }
        // User option for outpatient
        else if (userInput == 'O') {

            cout << "Lab fees and other service charges ($):" << endl;

            cin >> chargeService;
                
            pat.setServices(chargeService);

            cout << "Medication charges ($):" << endl;

            cin >> chargeMeds;
                
            pat.setMedication(chargeMeds);

           cout << "Your total hospital bills is $" << fixed << setprecision(2) << pat.calcTotalCharges(chargeService, chargeMeds) << endl;
           ++x;
        }
        else {

            cout << "Please enter either I or O:" << endl;
        }     

    }

    return 0;
}