//
//  main.cpp
//  BATTLESHIP
//
//  Created by Michael Onjack on 10/2/13.
//

#include <iostream>
#include "Board.h"
#include "Ship.h"
#include "Fleet.h"

#define MAX_GUESSES 30
#define EVEN 2

using namespace std;


int main()
{
    // true if the user wants to continue playing
    bool continuePlaying = true;
    bool invalidPlacement = false;
    
    // char that holds 'y' or 'n' that the user answers with when asked if they'd like to play again
    char userDecision;
    
    // Number of guesses the player has remaining
    int guesses;
    
    // Container holding the different types of ships for player and computer
    Ship playerShips[SHIP_TYPES];
    Ship computerShips[SHIP_TYPES];
    
    // Player and computer's game boards
    Board playerBoard;
    Board compBoard;
    
    // Point on the board the player guesses
    Point fireSpot;
    
    // Point on the board the player wishes to place their ship
    Point shipPlacement;
    // Direction the player chooses to lay their ship (vertical/horizontal)
    DIRECTION directionChoice;
    // Holds user input which determines what direction to use
    int choice;
    
    // throwaway ship used to access ship member functions and load each players' ships
    Ship throwAway;
    // Begin by initalizing the ships with the proper values (names, sizes, etc.)
    throwAway.LoadShips(playerShips);
    throwAway.LoadShips(computerShips);
    
    
    
    // Greet user to game
    cout << "\t\t\t     Welcome to BATTLESHIP" << endl << endl;
    cout << "You will be playing against the computer." << endl;
    cout << "Each player begins the game with 5 ships, you must sink your opponent's ships!" << endl;
    cout << "Guess your opponent's ships' location by inputing a row number and column number\n";
	cout << "You have "<< MAX_GUESSES <<" guesses for the game." << endl;
    cout << "\nBEGIN WAR" << endl << endl;
    
    // While user wishes to continue playing
    while( continuePlaying )
    {
        // Reset guesses to the max number of guesses for each new game
        guesses = MAX_GUESSES;
        
		// Reset user and computer's boards for each new game
		playerBoard.ResetBoard();
		compBoard.ResetBoard();
        
        // Prompt user to place their ships
        cout << "Time to place your ships. \nFor each ship, you will choose one point which is where the front of the ships will lie. \n";
		cout << "You will then choose a direction for your ship to lie (vertical or horizontal)\n\n";
		cout << "Here is a sample board. Row #'s on left and column #'s on top..\n\n";
		playerBoard.PrintBoard();
        
        for( int i = 0; i < SHIP_TYPES; i++ )
        {
            cout << "Enter row and column number for front coordinate of " << playerShips[i].GetName() << " (size: " << playerShips[i].GetLength() << ") (ex: x y) : ";
            cin >> shipPlacement.X >> shipPlacement.Y;
			// Subtract one from user input to account for indexing
            shipPlacement.X--; shipPlacement.Y--;
			// Ask user for direction in which the ship lies
            cout << "Lay it vertically or hortizontally? ( 0 for vert, 1 for horiz ) : ";
            cin >> choice;
			
			// Prompt user for appropriate response if one was not given
			while( choice != 0 && choice != 1 )
			{
				cout << "You did not enter 0 or 1. Please enter 0 for vert, 1 for horiz: ";
				cin >> choice;
			}
            
            if( choice == 0 )
                directionChoice = VERTICAL;
            else
                directionChoice = HORIZONTAL;
            
            // Check if the given point and direction are valid
            invalidPlacement = throwAway.CheckPlacement(shipPlacement, directionChoice, playerShips, playerShips[i], i);
            
            // While the placement is not valid, prompt user for new coordinates and direction
            while( invalidPlacement )
            {
                cout << "\nINVALID PLACEMENT!\nYou either already have a ship at this location or\n";
				cout << "your ship will not be entirely placed on the board at this location.\n";
                cout << "\nEnter new row and column number for ship placement separated by a space: ";
                cin >> shipPlacement.X >> shipPlacement.Y;
                shipPlacement.X--; shipPlacement.Y--;
                
                cout << "Lay it vertically or hortizontally? ( 0 for vert, 1 for horiz ) : ";
                cin >> choice;
                if( choice == 0 )
                    directionChoice = VERTICAL;
                else
                    directionChoice = HORIZONTAL;
                
                // Check if the given point and direction are valid
                invalidPlacement = throwAway.CheckPlacement(shipPlacement, directionChoice, playerShips, playerShips[i], i);
                
            }
            
			// Give the current ship its user assigned data (spaces occupied, direction)
            playerShips[i].FillShipData(directionChoice, shipPlacement);
            cout << endl;
            
        }
        
        // Place computer ships
        cout << "Placing computer ships..\n";
        for( int i = 0; i < SHIP_TYPES; i++ )
        {
            // Give ship random coordinates and direction until it has valid values for each
            do {
                
                // Pick random point
                shipPlacement.X = rand() % BOARD_LENGTH;
                shipPlacement.Y = rand() % BOARD_WIDTH;
                
                // Pick random direction
                choice = rand() % EVEN;
                if( choice == 0 )
                    directionChoice = VERTICAL;
                else
                    directionChoice = HORIZONTAL;
                
                // Check if the random point and direction are valid
                invalidPlacement = throwAway.CheckPlacement(shipPlacement, directionChoice, computerShips, computerShips[i], i);
                
            } while (invalidPlacement); // While the placement is not valid, repeat
            
            // cout << shipPlacement << choice << computerShips[i].GetLength() << endl;
		    // Give the current ship its randomly assigned data (spaces occupied, direction)
            computerShips[i].FillShipData(directionChoice, shipPlacement);
        }
        
        // Declaration and initialization of each player's fleet of ships using their respective 'Ships' arrays
        Fleet playerFleet( playerShips );
        Fleet computerFleet( computerShips );
        cout << endl;
        // Print coordinates of users' ships
        cout << "Your ships' locations..\n";
        cout << "(ROW#, COLUMN#)\n";
        playerFleet.ShowUserFleet();
        
        // While the user still has guess left and both player has playable ships, continue the game
        while( guesses > 0 && !computerFleet.FleetIsSunk(playerBoard) )
        {
            
            // Success is determined by whether they hit an opponent ship or not
            bool userSuccess = true;
            // user's turn continues if they successfully land a hit
            while(userSuccess && !playerFleet.FleetIsSunk(compBoard) && !computerFleet.FleetIsSunk(playerBoard) )
            {
                userSuccess = false;
                
                // Show user their guesses remaining and their board
                cout << "\nYou have " << guesses << " guesses remaining.\n";
                cout << "Here is your board showing your previous guesses..\n\n";
                playerBoard.PrintBoard();
                
                // Ask user for next guess location
                cout << "Enter row and column of your guess separated by a space: ";
                cin >> fireSpot.X >> fireSpot.Y;
                // Subtract one from the given points for correct indexing
                fireSpot.X--; fireSpot.Y--;
                
                // Check to be sure the player had entered a valid guess
                while( playerBoard.CheckGuess(fireSpot) )
                {
					// While an invalid guess coordinate is inputted by the user
					// Inform them it is invalid and prompt them to enter a new coordinate
                    cout << "\nINVALID GUESS!\n";
					cout << "This point is either not contained on the board or you have previously guessed it!\n";
                    cout << "Please enter a new point to guess..\n";
					cout << "Enter row then column separated by a space: ";
                    cin >> fireSpot.X >> fireSpot.Y;
					// Decrement the inputted coordinates by one to account for indexing
                    fireSpot.X--; fireSpot.Y--;
                }
                
				// Determine if the user's guess landed a hit
				// If so, their turn continues so userSuccess is set to true
                userSuccess = throwAway.isHit(fireSpot, computerShips );
				// Mark the user's board with the correct character depending on if a hit was landed
                playerBoard.MarkBoard(userSuccess, fireSpot);
                
				// Show user which of the computers' ships they have sunk
				cout << "Ships you have sunk:\n";
				for( int i = 0; i < SHIP_TYPES; i++ )
				{
					// If one of the computer's ships has been sunk..
                    if( computerShips[i].isSunk(playerBoard) )
					{
						// Print the name of the ship and its size to the console
						cout << "   - " << computerShips[i].GetName() << " (of length ";
						cout << computerShips[i].GetLength() << ") has been sunk.\n";
					}
				}
                
            }
            
			// Initialize flag to true to enter the loop
            bool computerSuccess = true;
            // computer's turn continues if they successfully land a hit and both
            while( computerSuccess && !computerFleet.FleetIsSunk(playerBoard) && !playerFleet.FleetIsSunk(compBoard) )
            {
                computerSuccess = false;
                
                // Generate random number from 0-9 for x and y coordinates
				fireSpot.X = rand() % BOARD_LENGTH;
				fireSpot.Y = rand() % BOARD_WIDTH;
                
                // Be sure the computer has not already guessed this point
                while( compBoard.CheckGuess(fireSpot) )
                {
                    // If it has, pick new coordinates
                    fireSpot.X = rand() % BOARD_LENGTH;
                    fireSpot.Y = rand() % BOARD_WIDTH;
                }
                
				// Print the computer's guess coordinate to console
                cout << "\nThe computer launched their torpedo at position " << fireSpot << endl;
                
                computerSuccess = throwAway.isHit(fireSpot, playerShips);
                compBoard.MarkBoard(computerSuccess, fireSpot);
                
				// Prints the ships sunk by the computer
				cout << "Ships sunk by computer:\n";
                for( int i = 0; i < SHIP_TYPES; i++ )
				{
					// If the user's ship is sunk..
                    if( playerShips[i].isSunk(compBoard) )
					{
						// Output the name and size of the ship to the console
						cout << "   - " << playerShips[i].GetName() << " (of length ";
						cout << playerShips[i].GetLength() << ") has been sunk.\n";
					}
				}
                
            }
            
            // After each turn, decrease the user's amount of guesses by one
            guesses--;
        }
        
        // If the gameplay loop has been exited from, this must mean either
		// 1.) The user's fleet has been sunk by the computer
		// 2.) The computer's fleet has been sunk by the user
		// 3.) The user ran out of guesses
		// Therefore the appropriate message must be chosen once the game ends
        
		cout << "\nGAME OVER.\n";
        
		// Check is user's fleet has been sunk
		if( playerFleet.FleetIsSunk(compBoard) )
			// If so, inform the user they have lost
			cout << "\nComputer has sunk your battleships. You fail.\n";
		
		// Check if computer's ships have been sunk
		else if( computerFleet.FleetIsSunk(playerBoard) )
			// If so, inform the they have won the game
			cout << "\nYou sunk all the computers battleships! You win!\n";
        
		// If neither fleet has sunk but the game has ended, the user must have ran out of guesses
		else
			// Inform the user the reason the game ended was because they ran out of guesses
			cout << "\nYou ran out of guesses! Tie game.\n";
        
        // Ask user if they would like to play again
        cout << "\nPlay again? Enter 'y' for yes, 'n' for no: ";
        cin >> userDecision;
        
		// Prompt user for an eligible response if they have yet to give one
        while ( userDecision != 'y' && userDecision != 'n' )
        {
			// User must enter 'y' or 'n' in order to continue or exit the game
            cout << "You did not enter 'y' or 'n'. Please do so: ";
            cin >> userDecision;
        }
        
		// If the user wishes to play again..
		if( userDecision == 'y' )
			// Set the continuePlaying flag to true to reenter the gameplay loop
            continuePlaying = true;
        
		// If the user wishes to not play again..
		else if ( userDecision == 'n' )
			// Set the continuePlaying flag to  false to exit the gameplay loop
            continuePlaying = false;
        
        cout << endl;
    }
    
	// Thank user for playing and terminate the game
    cout << "Thank you for playing BATTLESHIP" << endl;
    cout << "Goodbye." << endl;
    
    
    system("pause");
    
}
