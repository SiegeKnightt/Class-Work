/*
 * Name: Reeves Farrell
 * Date Submitted: Due: Feb 13th by midnight
 * Lab Section: 005
 * Assignment Name: Lab 3: Finding Groups Using Recursion
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below

Grouping::Grouping(string fileName) {

    char input;
    int flag;

    ifstream file(fileName);

    // Creates a 10x10 grid of
    // 1s and 0s to compare
    // to the input file
    for (int i = 0; i < 10; i++) {

        for (int j = 0; j < 10; j++) {

            // Gets input from file
            file >> input;

            if (input != '.') {
                
                // sets flag to one if it is an X
                flag = 1;
            }
            else {

                // Sets to zero if it is a period
                flag = 0;
            }

            grid[i][j] = flag;
        }
    }

    for(int i = 0; i < 10; i++){
        
        for (int j = 0; j < 10; j++) {

            if (grid[i][j] != 0) {

                groups.push_back(vector<GridSquare>());
                findGroup(i, j);
            }
        }
    }
}

void Grouping::findGroup(int r, int c) {

    if (grid[r][c] == 1) {

        if (r < 0 || r > 9 || c < 0 || c > 9) {

            return;
        }

        grid[r][c] = 0;
           
        cout << "(" << r << "," << c << ") ";
            
        findGroup(r + 1, c);
        findGroup(r - 1, c);
        findGroup(r, c + 1);
        findGroup(r, c - 1);

        groups[groups.size() - 1].push_back(GridSquare(r,c));
        
    }
}

//Simple main function to test Grouping
//Be sure to comment out main() before submitting
/*int main()
{
    Grouping input1("input1.txt");
    input1.printGroups();
    
    return 0;
}*/

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}