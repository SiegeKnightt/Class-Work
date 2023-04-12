/*
 * Name: Reeves Farrell
 * Date Submitted: Due Mar 13 by 11:59pm
 * Lab Section: 005
 * Assignment Name: Lab 6: Finding the Closest Pair of Points
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cmath>
#include <set>
#include <limits>

using namespace std;

struct point
{
    double x;
    double y;
};

/*Implement the following function
  Reads in a file specified by the parameter
  Format of file: #of points on first line
                  remaining (#of points) lines: x-value and y-value of point
                  one point per line
                  x-value and y-value are double-precision values and
                  bounded by the unit square 0.0 <= x,y < 1.0
  Should use "spatial hashing" where the #of cells scales with the #of points
  and find the distance between the closest pair of points which will be
  returned as a double type value
*/
double closestPair(string filename);

/*int main()
{
    double min;
    string filename;
    cout << "File with list of points within unit square: ";
    cin >> filename;
    min = closestPair(filename);
    cout << setprecision(16);
    cout << "Distance between closest pair of points: " << min << endl;
    return 0;
}*/

double closestPair(string filename) {

  // Opens the file
  ifstream file(filename);

  int numberPoints;
  int b;
  int hashX;
  int hashY;
  double minimumDistance;
  double xDistance;
  double yDistance;
  double dis;

  file >> numberPoints;

  // Sets the number of cells proportional to the number of points.
  // This makes sure that b is larger for bigger sets of points
  // and is smaller for smaller sets of points (scales with number of points)
  b = ceil(sqrt(numberPoints));

  // Creates cells for every single set of points
  vector<vector<vector<point>>> cells(b, vector<vector<point>>(b));
  vector<point> curr(numberPoints);

  // Puts every point into a cell
  for (int z = 0; z < numberPoints; z++) {

    file >> curr[z].x;
    file >> curr[z].y;

    hashX = floor(curr[z].x * b);
    hashY = floor(curr[z].y * b);

    cells[hashX][hashY].push_back(curr[z]);
  }

  minimumDistance = numeric_limits<double>::max();

  // Main loops for comparing points
  // Brute force method
  for (int i = 0; i < b; i++) {

    for (int j = 0; j < b; j++) {

      for (int k = 0; k < cells[i][j].size(); k++) {
        
        // Loop for left and right adjacents
        for (int l = max(0, i - 1); l <= min(b - 1, i + 1); l++) {
          
          // Loop for top and bottom adjacents
          for (int m = max(0, j - 1); m <= min(b - 1, j + 1); m++) {

            for (int n = 0; n < cells[l][m].size(); n++) {
              
              // Makes sure the points are different
              if (cells[i][j][k].y == cells[l][m][n].y && cells[i][j][k].x == cells[l][m][n].x) {

                continue;
              }

              // Finds the distance between points
              xDistance = pow(cells[i][j][k].x - cells[l][m][n].x, 2);
              yDistance = pow(cells[i][j][k].y - cells[l][m][n].y, 2);
              dis = sqrt(yDistance + xDistance);

              if (dis < minimumDistance) {

                minimumDistance = dis;
              }
            }
          }
        }
      }
    }
  }

  return minimumDistance;
}