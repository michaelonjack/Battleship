//
//  Point.h
//  BATTLESHIP
//

#pragma once

#include <iostream>
using namespace std;

#define BOARD_LENGTH 10
#define BOARD_WIDTH 10

// Structure definition for Point struct
// Corresponds to a row number and column number
struct Point
{
	// A location on the grid defined
	// by X(horizontal) Y(vertical) coordinates
	int X;
	int Y;
    
	// Equivalence operator defined for Point types
    bool operator == (const Point& compareTo) const
    {
        return ( (X == compareTo.X) && (Y == compareTo.Y) );
    }
    
};
    
    
    // Output operator defined for Point types
    // Outputs point in traditional format (row#, column#)
    inline ostream& operator <<(ostream& out, Point myPoint)
    {
        // Increment X and Y coordinate to account for indexing
        myPoint.X++; myPoint.Y++;
        
        // Prints the coordinate to the console is traditional form (X,Y)
        out << "(" << myPoint.X << "," << myPoint.Y << ")";
        return out;
    }
