/*
My Name: Joseph Reeves Farrell
My Class: CPSC 1021
Date: 9/25/2022
Desc: COVID-19 ioslation self assesment tool
for students at a university
Time: 3+ hours
*/

#include <iostream>
#include <string>
#include "Date.h"
#include "calcDays.h"

using namespace std;

int main() {

    int dateDay;
    int dateMonth;
    int dateYear;
    int expoDay;
    int expoMonth;
    int expoYear;
    int vaxDay;
    int vaxMonth;
    int vaxYear;
    char illnessStatus;
    char exposureStatus;
    char vaccineStatus;

    cout << "Did you test positive or negative?" << endl;
    cout << "Enter 'p' for positive or 'n' for negative:" << endl;

    cin >> illnessStatus;

    // Case 1
    // Tested positive
    if (illnessStatus == 'p') {
        
        cout << "What month did you test positive?" << endl;
        cout << "Enter answer in numerical format (ie. January = 1):" << endl;

        cin >> dateMonth;

        cout << "What day of the month did you test positive?" << endl;

        cin >> dateDay;

        cout << "Did you test positive in 2021 or 2022?" << endl;

        cin >> dateYear;

        // Creates instance for date positive
        Date datePositive(dateDay, dateMonth, dateYear);

        cout << "Test result: positive" << endl;
        // Calls show date to use full string
        cout << "Date tested positive: " << datePositive.showDate() << endl;
        cout << "Length of isolation: 5 days" << endl;
    }
    // Cases 2 - 4
    // Tested negative
    else if (illnessStatus == 'n') {
        
        cout << "Have you been exposed to someone who tested positive?" << endl;
        cout << "Enter 'y' for yes or 'n' for no:" << endl;

        cin >> exposureStatus;

        // Cases 3 and 4
        // Exposed to positive case
        if (exposureStatus == 'y') {
        
            cout << "What month were you exposed?" << endl;
            cout << "Enter answer in numerical format (ie. January = 1):" << endl;

            cin >> expoMonth;

            cout << "What day of the month were you exposed?" << endl;

            cin >> expoDay;

            cout << "Were you exposed in 2021 or 2022?" << endl;

            cin >> expoYear;

            Date dateExposed(expoDay, expoMonth, expoYear);

            cout << "Have you recieved your second vaccination?" << endl;
            cout << "Enter 'y' for yes or 'n' for no:" << endl;

            cin >> vaccineStatus;

            // Cases 3 or 4
            // Exposed and has second vaccine
            if (vaccineStatus == 'y') {

                cout << "What month were you vaccinated?" << endl;
                cout << "Enter answer in numerical format (ie. January = 1):" << endl;

                cin >> vaxMonth;

                cout << "What day of the month were you vaccinated?" << endl;

                cin >> vaxDay;

                cout << "Were you vaccinated in 2021 or 2022?" << endl;

                cin >> vaxYear;

                Date dateSecondDose(vaxDay, vaxMonth, vaxYear);

                // Calls calcDays to determine vaccination status at the time of exposure
                if (calcDays(dateExposed, dateSecondDose) < 14) {

                    cout << "Test result: negative" << endl;
                    cout << "Exposed to positive case: Yes" << endl;
                    cout << "Date exposed to positive case: " << dateExposed.showDate() << endl;
                    cout << "Second vaccination dose recieved: Yes" << endl;
                    cout << "Date second vaccination dose recieved: " << dateSecondDose.showDate() << endl;
                    cout << "Vaccination status at time of exposure: not fully vaccinated" << endl;
                    cout << "Length of isolation: 10 days" << endl;
                }
                else {

                    cout << "Test result: negative" << endl;
                    cout << "Exposed to positive case: Yes" << endl;
                    cout << "Date exposed to positive case: " << dateExposed.showDate() << endl;
                    cout << "Second vaccination dose recieved: Yes" << endl;
                    cout << "Date second vaccination dose recieved: " << dateSecondDose.showDate() << endl;
                    cout << "Vaccination status at time of exposure: fully vaccinated" << endl;
                    cout << "Length of isolation: 5 days" << endl;
                }
            }
            // Only case 4
            // Exposed but no second vaccine
            else {

                cout << "Test result: negative" << endl;
                cout << "Exposed to positive case: Yes" << endl;
                cout << "Date exposed to positive case: " << dateExposed.showDate() << endl;
                cout << "Second vaccination dose recieved: No" << endl;
                cout << "Vaccination status at time of exposure: not fully vaccinated" << endl;
                cout << "Length of isolation: 10 days" << endl;
            }

        }
        // Case 2
        // Not exposed to a positive case
        else {

            cout << "Test result: negative" << endl;
            cout << "Exposed to positive case: No" << endl;
            cout << "Length of isolation: 0 days" << endl;
        }
    }

    return 0;
}