// Board.cpp - Board class function implementation
// Written by Michael Onjack

#include "Board.h"


Board::Board()
{
    
}


// Prints the output board to console showing user their hits, misses, unguessed spaces
void Board::PrintBoard() const
{
    // Print column numbers
    cout << " \t   ";
	for( int number = 1; number < BOARD_LENGTH + 1; number++)
        cout << " " << number;
    cout << endl;
    
    // Print board itself
    // i = row number, j = column number
	for( int i = 0; i < BOARD_LENGTH; i++)
    {
        
        cout << endl;
        // Print row number
        cout << "\t" << i+1;
		if( i != BOARD_LENGTH-1 )
			cout << "  ";
		else
			cout << " ";
        
		// Print columns
		for( int j = 0; j < BOARD_WIDTH; j++)
        {
			// Print the game board borders to console
			cout << "|";
            
            // If the curent space on board has not yet been guessed
			if( outputBoard[i][j] == NOT_GUESSED )
				// Print the character for water
                cout << WATER;
			// If the curent space on board has been guessed and is a hit
			if( outputBoard[i][j] == GUESS_HIT )
				// Print the character for a hit
                cout << HIT;
			// If the curent space on board has been guessed and was not a hit
			if( outputBoard[i][j] == GUESS_MISS )
				// Print the characer for a miss
                cout << MISS;
            
        }
		// Print the game board borders to console
        cout << "|";
        cout << endl;
    }
    
	// Output the board key to console so user can interpret their board
	cout << "\n'~' = NOT GUESSED \t'O' = MISS \t'X' = HIT\n";
    cout << endl;
}


// Marks the outputBoard with a certain character depending on
// whether the user guess was a hit or miss
// Marks the playerBoard true to signify that the user has guess this point on the board
void Board::MarkBoard(bool hit, const Point& guessCoordinate)
{
    // First mark the board to show the player has guessed this coordinate
    playerBoard[guessCoordinate.X][guessCoordinate.Y] = true;
    
	// If the coodinate the player guessed was a hit..
    if( hit == true )
    {
        // Mark the outputBoard with the corresponding character
        outputBoard[guessCoordinate.X][guessCoordinate.Y] = 1;
    }
    
	// If the coordinate he player guessed was a miss
    else
    {
        // Mark the outputBoard with the corresponding character
        outputBoard[guessCoordinate.X][guessCoordinate.Y] = 2;
    }
}


// Determines whether the player's guess is valid or not, returns true if the guess is INVALID
// A guess is NOT valid if
//		1.) The point that has been guessed is not contained on the board ( i.e. (123,43) )
//		2.) The player has already guessed the same point
bool Board::CheckGuess( const Point& guessCordinate) const
{
    // Flag to be returned; true is guess is INVALID, false if guess is VALID
	bool invalidGuess = false;
    
    // If the given point has already been guessed..
    if( playerBoard[guessCordinate.X][guessCordinate.Y] )
    {
		// Return true because the player cannot guess the same point twice
        invalidGuess = true;
    }
    
	// If the given point is greater than the size of the board
	else if( guessCordinate.X >= BOARD_LENGTH || guessCordinate.Y >=BOARD_WIDTH )
	{
		// Return true because the point that is guessed must be contained on the board
		invalidGuess = true;
	}
    
	// If the given point is less than the minimum size of the board
	else if( guessCordinate.X < 0 || guessCordinate.Y < 0 )
	{
		// Return true because the point that is guessed must be contained on the board
		invalidGuess = true;
	}
    
	// If the preceding criteria has been met, the guess is valid
    else
    {
		// Return false to show that the guess is valid
        invalidGuess = false;
    }
    
    return invalidGuess;
}



// Resets both the outputBoard (to 0) and the playerBoard (to false)
void Board::ResetBoard()
{
	// Go through each row of outputBoard
	for( int i = 0; i < BOARD_WIDTH; i++)
	{
		// Go through each column of output board
		for(int j=0; j < BOARD_LENGTH; j++)
		{
			// Reset board space to zero (WATER)
			outputBoard[i][j] = NOT_GUESSED;
		}
	}
    
	// Go through each row of outputBoard
	for( int i = 0; i < BOARD_LENGTH; i++)
	{
		// Go through each column of output board
		for(int j=0; j < BOARD_LENGTH; j++)
		{
			// Reset board space to false (not yet guessed)
			playerBoard[i][j] = false;
		}
	}
    
    
}
