/*
 * Name: Reeves Farrell
 * Date Submitted: Due April 17th by 11:59pm
 * Lab Section: 005
 * Assignment Name: Lab 9: Using Recursion to Solve the N-Queens Problem
 */

#include <iostream>
#include <vector>

using namespace std;

bool safe(int board[][50], int row, int col, int n);
int helper(int board[][50], int col, int n);

//Uses recursion to count how many solutions there are for
//placing n queens on an nxn chess board
int nQueens(int n) {
    
    //Implement int nQueens(int n)
    //Feel free to implement any recursive helper functions
    int numSolutions;
    int board[n][50] = {0};

    numSolutions = helper(board, 0, n);

    return numSolutions;
}

bool safe(int board[][50], int row, int col, int n) {

    // Check left of row
    for (int i = 0; i < col; i++) {

        if (board[row][i]) {

            return false;
        }
    }

    // Check up and right of row
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {

        if (board[i][j]) {

            return false;
        }
    }

    // Check down and left of row
    for (int i = row, j = col; j >= 0 && i < n; i++, j--) {

        if (board[i][j]) {

            return false;
        }
    }

    return true;
}

int helper(int board[][50], int col, int n) {

    // Count variable for solutions
    int count = 0;
    
    // Check for queens being placed
    if (col == n) {

        return 1;
    }

    for (int row = 0; row < n; row++) {
        
        // If position is safe, place the queen
        if (safe(board, row, col, n)) {

            board[row][col] = 1;

            // Recurion to place other queens
            count = count + helper(board, col + 1, n);

            // Removes queen from the position
            board[row][col] = 0;
        }
    }

    return count;
}

/*int main() {
    
    cout << "1: " << nQueens(1) << endl;
    cout << "2: " << nQueens(2) << endl;
    cout << "3: " << nQueens(3) << endl;
    cout << "4: " << nQueens(4) << endl;
    cout << "5: " << nQueens(5) << endl;
    cout << "6: " << nQueens(6) << endl;
    cout << "7: " << nQueens(7) << endl;
    cout << "8: " << nQueens(8) << endl;
    cout << "9: " << nQueens(9) << endl;
    cout << "10: " << nQueens(10) << endl;
    cout << "11: " << nQueens(11) << endl;
    cout << "12: " << nQueens(12) << endl;
    
    return 0;
}*/