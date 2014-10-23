// Board.h - Board class declaration
// Written by Michael Onjack

#pragma once

#include "Point.h"
using namespace std;


#define HIT 'X'
#define MISS 'O'
#define WATER '~'
#define NOT_GUESSED 0
#define GUESS_HIT 1
#define GUESS_MISS 2

class Board
{
public:
    // Constructor
    Board();
    
    // Function which prints an image of the board showing hits ( X ) and misses ( O )
    void PrintBoard() const;
    
    // Resets the board for both players before new games begin
    void ResetBoard();
    
    // Marks both boards after each guess
    void MarkBoard(bool hit, const Point& guessCoordinate);
    
    // Returns TRUE if the user has guessed the given coordinate
    bool CheckGuess( const Point& guessCoordinate ) const;
    
    // Board used for determining whether the user has guessed a certain position yet or not
    bool playerBoard[BOARD_WIDTH][BOARD_LENGTH];
    
    
private:
    
    // Board used soley for output
    // KEY: 0 = not yet guessed, 1 = hit, 2 = miss
	int outputBoard[BOARD_LENGTH][BOARD_WIDTH];
    
};
