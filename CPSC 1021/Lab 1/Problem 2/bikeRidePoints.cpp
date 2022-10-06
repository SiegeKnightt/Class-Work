/*
My Name: Joseph Reeves Farrell
My Class: CPSC 1021
Date: 9/5/2022
Desc: Asks user to input a specific number of bike rides 
to campus and then awards points based on the input
Time: ~ 30 min
*/

#include <iostream>
using namespace std;

int main () {

    int userInput;
    // Counter variable for while loop
    int x = 1;

    cout << "Input the number of bike rides to campus you take." << endl;

    // While loop is used to keep program running if an invalid number is entered
    while (x == 1) {

        // userInput = number of bike rides to campus
        cin >> userInput;

        if (userInput == 0) {

            cout << "You earned 0 points this semester" << endl;

            // Increments x to exit the while loop
            ++x;
        }
        else if (userInput == 1) {
            
            cout << "You earned 3 points this semester" << endl;

            ++x;
        }
        else if (userInput == 2) {
            
            cout << "You earned 10 points this semester" << endl;

            ++x;
        }
        else if (userInput == 3) {
            
            cout << "You earned 15 points this semester" << endl;

            ++x;
        }
        else if (userInput == 4) {
            
            cout << "You earned 30 points this semester" << endl;

            ++x;
        }
        else if (userInput >= 5) {
            
            cout << "You earned 50 points this semester" << endl;

            ++x;
        }
        else {

            // Does not increment x so the loop starts over
            cout << "Your input is invalid. Please enter a new number: " << endl;
        }

    }

    return 0;
}