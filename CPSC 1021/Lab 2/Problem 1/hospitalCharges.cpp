/*
My Name: Joseph Reeves Farrell
My Class: CPSC 1021
Date: 9/12/2022
Desc: Application to gather patient info and 
determine the total cost of their hospital stay
Time: 1 hour
*/

#include <iostream>
#include <iomanip>
#include "calcTotalCharges.h"
#include "validateUserInput.h"

using namespace std;

int main () {

    double input = false;
    char userInput;
    int numDays;
    double roomRate;
    double chargeService;
    double chargeMeds;

    // Counter variable
    int x = 0;

    cout << "This program will calculate a patient's hospital charges." << endl;
    cout << "Enter I for in-patient or O for out-patient:" << endl;

    while (x == 0) {

        cin >> userInput;
        
        // User option for inpatient
        if (userInput == 'I') {

                // Input for days in hospital
                cout << "Number of days in the hospital:" << endl;

                cin >> numDays;
                input = numDays;
                
                while (validateUserInput(input) == false) {
                    
                    cout << "Number of days in the hospital:" << endl;
                    cin >> numDays;
                }

                // Input for room rate
                cout << "Daily room rate ($):" << endl;

                cin >> roomRate;
                input = roomRate;

                while (validateUserInput(input) == false) {
                    
                    cout << "Daily room rate ($):" << endl;
                    cin >> roomRate;
                }

                cout << "Lab fees and other service charges ($):" << endl;

                cin >> chargeService;
                input = chargeService;

                while (validateUserInput(input) == false) {

                    cout << "Lab fees and other service charges ($):" << endl;
                    cin >> chargeService;  
                }

                cout << "Medication charges ($):" << endl;

                cin >> chargeMeds;
                input = chargeMeds;

                while (validateUserInput(input) == false) {

                    cout << "Medication charges ($):" << endl;
                    cin >> chargeMeds;
                }

            cout << "Your total hospital bills is $" << fixed << setprecision(2) << calcTotalCharges(numDays, roomRate, chargeService, chargeMeds) << endl;

            // Increments x to exit the loop
            ++x;
        }
        // User option for outpatient
        else if (userInput == 'O') {

                cout << "Lab fees and other service charges ($):" << endl;

                cin >> chargeService;
                input = chargeService;

                while (validateUserInput(input) == false) {

                    cout << "Lab fees and other service charges ($):" << endl;
                    cin >> chargeService;  
                }

                cout << "Medication charges ($):" << endl;

                cin >> chargeMeds;
                input = chargeMeds;

                while (validateUserInput(input) == false) {

                    cout << "Medication charges ($):" << endl;
                    cin >> chargeMeds;
                }

           cout << "Your total hospital bills is $" << fixed << setprecision(2) << calcTotalCharges(chargeService, chargeMeds) << endl;
           ++x;
        }
        else {

            cout << "Please enter either I or O:" << endl;
        }     

    }

    return 0;
}