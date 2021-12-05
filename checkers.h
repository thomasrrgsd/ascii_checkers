/*
 * checkers.h
 *
 */

#ifndef CHECKERS_H_
#define CHECKERS_H_

#include <iostream>
#include <string>
#include <list>
#include "boardgame.h"
#include "checkerboard.h"
#include "player.h"
#include "humanplayer.h"
#include "computerplayer.h"

#define CPU_VS_CPU      (0)
#define CPU_VS_HUMAN    (1)
#define HUMAN_VS_HUMAN  (2)

#define NO_MOVES		(true)
#define YES_MOVES		(false)

using namespace std;


/*
 * Checkers class, inherited from a boardgame class. Checkers IS-A boardgame.
 * A checkers game has a checkerboard, two players, 12 pieces per player, and
 * not physically, but also a history of moves. The checkers class also keeps
 * track of the number of pieces.
 *
 * Because the checkers class puts objects on the heap, it needs to implement
 * a destructor and therefore the Ro3.
 * 
 */
class Checkers : public AbstractBoardGame {
public:
	int gameType;
	
    CheckerBoard* board{};			// Board object

    player *player1;				// Player 1 object
    player *player2;				// Player 2 object	
	
    array<piece*, 12> pieces1{}; 	// Player 1 pieces
    array<piece*, 12> pieces2{};	// Player 2 pieces	
	
    int numPieces1;				// Player 1 pieces left
    int numPieces2;				// Player 2 pieces left
	
	bool noMoves1;					// No moves to make
	bool noMoves2;

    list<string> prevMoves;			// Last 10 moves in linked list

    Checkers(int numPlayers);						// Constructor
	~Checkers();									// Destructor
	Checkers(const Checkers &other);				// Copy Copy
    Checkers& operator=(const Checkers &other);		// Assignment Operator

    int	 PlayGame() override;						// Play the Game!
    int  HandleCurrentMove(string from, string to); // Processes move, returns error code.
    int  CheckGameOver(); 							// Has anybody won?
    void WinnerTieDisplay(int whoWon); 				// Displays who won.
	void PrintPlayer(int playerNum);				// Which player turn is it?
    void UpdatePlayerStats() const; 				// Show number of pieces left.
	bool IsThereNoMove();							// Determines if moves available.
	void UpdatePreviousMoves(string strFrom, string strTo, int whichPlayer = 0);
};

#endif	// CHECKERS_H_