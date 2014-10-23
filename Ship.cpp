// Ship.cpp - Ship class function implementation
// Written by Michael Onjack

#include "Ship.h"


Ship::Ship()
{
    
}



void Ship::LoadShips(Ship ship[SHIP_TYPES])
{
    //Sets the default data for the ships
    //we plan to include in the game
    //IMPORTANT!! > MUST MATCH SHIP_TYPES -Default=5 (0-4)
    ship[0].Name = "Cruiser"; ship[0].Length = 2;
    ship[1].Name = "Frigate"; ship[1].Length = 3;
    ship[2].Name = "Submarine"; ship[2].Length = 3;
    ship[3].Name = "Escort"; ship[3].Length = 4;
    ship[4].Name = "Battleship"; ship[4].Length = 5;
}





void Ship::FillShipData( const DIRECTION& direction, Point coordinate )
{
    // Fill the ship's private data field 'Direction' with the direction parameter
	Direction = direction;
    
    // If the ship will be laid horizontally, give it the initial point plus the y-coordinates to its right
    if( Direction == HORIZONTAL )
    {
        for( int i = 0; i < Length; i++ )
        {
            spaceOccupied[i].X = coordinate.X;
			spaceOccupied[i].Y = coordinate.Y;
            coordinate.Y++;
        }
    }
    
    // If the ship will be laid vertically, give it the initial point plus the spaces below it
    else
    {
		// Continue until
        for( int i = 0; i < Length; i++ )
        {
			spaceOccupied[i].X = coordinate.X;
			spaceOccupied[i].Y = coordinate.Y;
            coordinate.X++;
        }
    }
    
    
	// Se the ship's 'Hits' private data field to zero
	Hits = 0;
}





// Uses throwaway to call, one user's guess and the other user's ships
// Determines if the opposing player has landed a hit on a ship
bool Ship::isHit( const Point& guess, Ship ship[SHIP_TYPES] ) const
{
	// Initialize hit to false
    bool hit = false;
    
    // For loop to go through each ship
    for( int i = 0; i < SHIP_TYPES && hit==false; i++ )
    {
        // For loop to go through each point the ship occupies
        for( int j = 0; j < ship[i].Length && hit==false; j++ )
        {
            // If the player's guess matches a point the ship is located on, it has been hit
            if( ship[i].spaceOccupied[j] == guess )
            {
				// Set flag hit to true to show that the guess has hit a ship
                hit = true;
                
                // Inform player they landed a hit and which one suffered the damage
                cout << ship[i].Name << " has been hit!\n";
				// Increment the number of times this ship has been hit
				ship[i].Hits++;
				// Print the ship's status to console after each time it has been hit
				ship[i].PrintDamage();
            }
        }
    }
    
    // If the player has missed all ships, inform them
    if( hit == false )
        cout << "Missed.\n";
    
    
    return hit;
}





bool Ship::isSunk( const Board& opponentBoard ) const
{
    // Number of times the ship has been hit
    int hits = 0;
    
	// For loop to go through each space the ship occupies
    for( int i = 0; i < Length; i++ )
    {
		// If the opponent has guessed a space that the ship occupies, it has been hit
        if( opponentBoard.playerBoard[spaceOccupied[i].X][spaceOccupied[i].Y] == true )
        {
			// Increase the number of times the ship has been hit
            hits++;
        }
    }
    
	// If the ship was hit at each space is occupies, the ship has been sunk
    if( hits == Length )
    {
		// Return true to show the ship has been sunk
		return true;
    }
    
    else
        return false;
}






bool Ship::CheckPlacement(Point placePoint, const DIRECTION& direction, const Ship ship[], const Ship& currentShip, int shipNumber)
{
    bool invalidPos = false;
    
    if( direction == HORIZONTAL )
    {
		// Check if the desired placement is containe on the board
		if( placePoint.Y+currentShip.GetLength() >= BOARD_WIDTH || placePoint.X < 0 || placePoint.Y < 0 || placePoint.X >= BOARD_LENGTH  )
        {
            return true;
        }
    }
    
    else
    {
		// Check if the desired placement is containe on the board
		if( placePoint.X+currentShip.GetLength() >= BOARD_LENGTH || placePoint.X < 0 || placePoint.Y < 0 || placePoint.Y >= BOARD_WIDTH )
        {
            return true;
        }
    }
    
    
    int originalX = placePoint.X;
    int originalY = placePoint.Y;
    // For loop to examine each ship
    for( int i = 0; i < shipNumber; i++)
    {
        // For loop to examine the spaces each loop occupies
        for( int j = 0; j < ship[shipNumber].Length; j++ )
        {
            for( int k = 0; k < currentShip.Length; k++ )
            {
                if( direction == HORIZONTAL )
                {
                    // If an already placed ship already occupies the given space, return true
                    if( ship[i].spaceOccupied[j] == placePoint )
                        return true;
                    placePoint.Y++;
                }
                
                else
                {
                    // If an already placed ship already occupies the given space, return true
                    if( ship[i].spaceOccupied[j] == placePoint )
                        return true;
                    placePoint.X++;
                }
            }
            placePoint.Y = originalY;
            placePoint.X = originalX;
        }
    }
    
    
    return invalidPos;
}

// Prints the ships status displaying how many times it has been hit
void Ship::PrintDamage() const
{
	cout << endl;
	cout << Name<< " DAMAGE: " << Hits << "/" << Length;
	cout << endl;
}
