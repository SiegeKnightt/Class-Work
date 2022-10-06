/*
My Name: Joseph Reeves Farrell
My Class: CPSC 1021
Date: 9/21/2022
Desc: Menu based program that 
calculates the areas of different shapes
using OOP concepts such as classes
Time: 
*/

#include <iostream>
#include <iomanip>
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"
#include "Trapezoid.h"

using namespace std;

int main () {

    int menuInput;

    // Variable to exit main loop
    int x = 0;

    while (x == 0) {

    // Builds the menu for the program
    // iomanip allows for adjusting the placement
    // of the menu options using setw()
    cout << "Program to calculate areas of objects" << endl;
    cout << setw(19) << "1 -- circle" << endl;
    cout << setw(19) << "2 -- square" << endl;
    cout << setw(22) << "3 -- rectangle" << endl;
    cout << setw(22) << "4 -- trapezoid" << endl;
    cout << setw(17) << "5 -- quit" << endl;

    // Gathers user input for menu option
    cin >> menuInput;
    
    // Menu option for circle area
    if (menuInput == 1) {
        
        // Declares an object called Circle
        Circle circ;

        double circRadius;

        cout << "Enter radius: " << endl;

        cin >> circRadius;

        // Gets valid input for radius
        while (!circ.setRadius(circRadius)) {

            cout << "Enter a valid radius: " << endl;

            cin >> circRadius;
        }
        
        // Outputs details of calculation
        cout << "Radius: " << fixed << setprecision(1) << circ.getRadius() << endl;

        cout << "Area: " << fixed << setprecision(1) << circ.calcArea() << endl;
        
        // Exits the menu loop
        ++x;
    }
    // Menu option for square area
    else if (menuInput == 2) {

        // Declares an object called Square
        Square sq;

        double sqSide;

        cout << "Enter side: " << endl;

        cin >> sqSide;

        // Gets valid input for side
        while (!sq.setSide(sqSide)) {

            cout << "Enter a valid side: " << endl;

            cin >> sqSide;
        }
        
        // Outputs details of calculation
        cout << "Side: " << fixed << setprecision(1) << sq.getSide() << endl;

        cout << "Area: " << fixed << setprecision(1) << sq.calcArea() << endl;

        // Exits the menu loop
        ++x;
    }
    // Menu option for rectangle area
    else if (menuInput == 3) {

        // Declares an object called Rectangle
        Rectangle rect;
        
        double rectLength;
        double rectWidth;

        cout << "Enter length: " << endl;

        cin >> rectLength;

        cout << "Enter width: " << endl;

        cin >> rectWidth;


        // Gets valid input for length
        while (!rect.setLength(rectLength)) {

            cout << "Enter a valid length: " << endl;

            cin >> rectLength;
        }

        // Gets valid input for width
        while (!rect.setWidth(rectWidth)) {

            cout << "Enter a valid width: " << endl;

            cin >> rectWidth;
        }

        // Outputs details of calculation
        cout << "Length: " << fixed << setprecision(1) << rect.getLength() << endl;

        cout << "Width: " << fixed << setprecision(1) << rect.getWidth() << endl;

        cout << "Area: " << fixed << setprecision(1) << rect.calcArea() << endl;

        // Exits the menu loop
        ++x;
    }
    // Menu option for trapezoid area
    else if (menuInput == 4) {

        // Declares an object called Trapezoid
        Trapezoid trap;
        
        double trapBase1;
        double trapBase2;
        double trapHeight;

        cout << "Enter base 1: " << endl;

        cin >> trapBase1;

        cout << "Enter base 2: " << endl;

        cin >> trapBase2;

        cout << "Enter height: " << endl;

        cin >> trapHeight;

        // Gets valid input for base 1
        while (!trap.setBase1(trapBase1)) {

            cout << "Enter a valid base 1: " << endl;

            cin >> trapBase1;
        }

        // Gets valid input for base 2
        while (!trap.setBase2(trapBase2)) {

            cout << "Enter a valid base 2: " << endl;

            cin >> trapBase2;
        }

        // Gets valid input for height
        while (!trap.setHeight(trapHeight)) {

            cout << "Enter a valid height: " << endl;

            cin >> trapHeight;
        }

        // Outputs details of calculation
        cout << "Base1: " << fixed << setprecision(1) << trap.getBase1() << endl;

        cout << "Base2: " << fixed << setprecision(1) << trap.getBase2() << endl;

        cout << "Height: " << fixed << setprecision(1) << trap.getHeight() << endl;

        cout << "Area: " << fixed << setprecision(1) << trap.calcArea() << endl;

        // Exits the menu loop
        ++x;
    }
    // Menu option for quit button
    else if (menuInput == 5) {

        // Ends the program normally
        return 0;
    }
    // Condition if valid menuInput is not obtained
    else {

        cout << "Please input a valid menu option: " << endl;
    }

    }

    return 0;
} 