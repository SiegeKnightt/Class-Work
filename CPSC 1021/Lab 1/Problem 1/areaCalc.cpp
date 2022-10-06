/*
My Name: Joseph Reeves Farrell
My Class: CPSC 1021
Date: 9/4/2022
Desc: A menu-driven program to calculate and display the areas of three different shapes
Time: ~ 1 hour
*/

#include <iostream>
#include <iomanip>
using namespace std;

int main () {

    // Defines a constant for the number PI
    const double PI = 3.14159;
    
    int menuInput;
    double squareLength;
    double circleRadius;
    double triangleBase;
    double triangleHeight; 
    double squareArea;
    double circleArea;
    double triangleArea;

    // Builds the menu for the program
    // iomanip allows for adjusting the placement
    // of the menu options using setw()
    cout << "Program to calculate areas of objects" << endl;
    cout << setw(19) << "1 -- square" << endl;
    cout << setw(19) << "2 -- circle" << endl;
    cout << setw(27) << "3 -- right triangle" << endl;
    cout << setw(17) << "4 -- quit" << endl;

    // Gathers user input for menu option
    cin >> menuInput;
    
    // Menu option for square area
    if (menuInput == 1) {
        
        cout << "Length of the square: " << endl;

        cin >> squareLength;

        // Calculates the are of the square
        squareArea = squareLength * squareLength;

        // setprecision affects the whole number so
        // fixed applies setprecision to just the decimal portion
        cout << "Area = " << fixed << setprecision(2) << squareArea << endl;
    }
    // Menu option for circle areaa
    else if (menuInput == 2) {

        cout << "Radius of the circle: " << endl;

        cin >> circleRadius;

        // Calculates the area of the circle
        circleArea = PI * (circleRadius * circleRadius);

        // setprecision affects the whole number so
        // fixed applies setprecision to just the decimal portion
        cout << "Area = " << fixed << setprecision(2) << circleArea << endl;
    }
    // Menu option for right triangle area
    else if (menuInput == 3) {

        cout << "Base of the trangle: " << endl;

        cin >> triangleBase;

        cout << "Height of the triangle: " << endl;

        cin >> triangleHeight;

        // Calculates the area of the triangle
        triangleArea = 0.5 * triangleBase * triangleHeight;

        // setprecision affects the whole number so
        // fixed applies setprecision to just the decimal portion
        cout << "Area = " << fixed << setprecision(2) << triangleArea << endl; 
    }
    // Menu option for quit button
    else if (menuInput == 4) {

        // Exits the program normally
        return 0;
    }
    // Error for an invalid choice
    else {

        cout << "You entered an invalid choice. Good bye!" << endl;

        // Return 1 because this is not the correct/expected result
        return 1;
    }

    return 0;
} 