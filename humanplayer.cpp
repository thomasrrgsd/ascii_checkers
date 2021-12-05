/*
 * humanplayer.cpp
 *
 */

#include "humanplayer.h"

using namespace std;

    humanplayer::humanplayer(array<piece*, 12> *pieces1,
                             array<piece*, 12> *pieces2) : player(pieces1, pieces2) {
        Ppieces = pieces1;
        Opieces = pieces2;
}

/*
 * Description: Takes user input and handles the inputs
 * Enforces the jumping rule that is in place
 * Allows the user to quit the game at any time
 */
void humanplayer::handlePlayer(string &source, string &destination) {
    bool pieceValid = false;            // Holds the value to know if the piece given is valid
    bool locationValid = false;         // Holds the value to know if the location given is valid
    string pieceToMove;         // Holds string for what piece the player wants to be moved
    string locationToMove;      // Holds string for location the player wants to move to
    piece * usedPiece;


    list<string> jumpMoveList;
    list <string> jumpingPieceList;
    bool jumpAvailable = false;

    /*
     * This loop will iterate through all the pieces that the player still controls and check to see
     * one of them is the piece requested by the player. If it is, it saves a value of that piece so it can
     * check positions for it later.
     */

    cout << "\033[s";
	// Clear out old input.
	cout << "\r\033[30B\033[K\r\n\033[K\r\n\033[K\r\n\033[K\r\n\033[4A";
    cout << "\r\033[K\t\tMove From: ";
    cin >> pieceToMove;
	cout << "\033[u";

    // User inputs to pieceToMove and the program evaluates the contents.

    if(pieceToMove != "quit") {
		
		// User did not type quit, so look for a movelist that contains a jump and add to a jump list.
		// Set jumpAvailable if a jump if found.
        for (auto it = Ppieces->begin(); (it) != Ppieces->end(); it++) {
            for (auto checkMove: (*it)->validMoves) {
                if (checkMove->isJump) {
                    jumpingPieceList.push_back((*it)->position);
                    jumpMoveList.push_back(checkMove->space);
                    jumpAvailable = true;
                }
            }
        }

        while (pieceValid != true) {

			// Now we scan the list to see if piece to move string entered by the user is in our
			// piece list (Ppieces).
            for (auto it = Ppieces->begin(); (it) != Ppieces->end(); it++) {
                if ((*it)->position == pieceToMove) {
					// We have found a piece that matches our location.
					// If a jump is available that must be what our user picked, if not the loop is broken and the user
					// will have to enter another piece.
                    if (jumpAvailable) {  // make sure the piece they just passed to move is in the jumpingPieceList
                        if (find(jumpingPieceList.begin(), jumpingPieceList.end(), (*it)->position) != jumpingPieceList.end()) {
                            // A jump is available and the user picked a jump.
							pieceValid = true;
                            usedPiece = (*it);
                        }
                    } else {	// We are not looking for a jump, but we did find that piece in our list.
								// Now we must check that it has a valid move.
						if(!(*it)->validMoves.empty()){
							pieceValid = true;
							usedPiece = (*it);
						}
                    }
					break; // We found the piece, no longer need to search.
                }
            }
			
            if (pieceValid) { break; } // If a valid piece is not found, we will print error message and get another piece.

            if (jumpAvailable) {
				cout << "\033[s";
				cout << "\r\033[31B\033[K";               
				cout << "\t\tJump available; Must move that piece.";
				cout << "\r\033[1A\033[K";
				cout << "\t\tMove From: ";
                cin >> pieceToMove;
				cout << "\033[u"; 
            } else {
				cout << "\033[s";
				cout << "\r\033[31B\033[K"; 
                cout << "\t\tInvalid Piece, Please pick another.";
				cout << "\r\033[1A\033[K";
				cout << "\t\tMove From: ";
                cin >> pieceToMove;
				cout << "\033[u"; 
            }
        }

		cout << "\033[s";
		cout << "\r\033[31B\033[K";  
        cout << "\r\n\033[K\t\t  Move To: ";
        cin >> locationToMove;
		cout << "\033[u";

        /*
         * This loop uses the previous value of the player in order to see if the position given to move to is valid,
         * and asks until it is.
         */

        if(locationToMove != "quit") {
            while (!locationValid) {
                for (std::list<moveObj *>::iterator it = usedPiece->validMoves.begin();
                     it != usedPiece->validMoves.end(); it++) {
                    if ((*it)->space == (locationToMove)) {

                        if (jumpAvailable) {  // make sure the space they just passed is in the valid jump move list
                            if (std::find(jumpMoveList.begin(), jumpMoveList.end(), (*it)->space) !=
                                jumpMoveList.end()) {
                                locationValid = true;
                                break;
                            }
                        } else {
                            locationValid = true;
                            break;
                        }
                    }
                }
                if (locationValid) {
                    break;
                }

                if (jumpAvailable) {
					cout << "\033[s";
					cout << "\r\033[33B\033[K"; 
                    cout << "\t\tJump available; Must move to jump piece.";
					cout << "\r\033[1A\033[K";
					cout << "\t\t  Move To: ";
                    cin >> locationToMove;
					cout << "\033[u";
                } else {
					cout << "\033[s";
					cout << "\r\033[33B\033[K"; 
                    cout << "\t\tInvalid Location, Please pick another.";
					cout << "\r\033[1A\033[K";
					cout << "\t\t  Move To: ";
                    cin >> locationToMove;
					cout << "\033[u";
                }
            }

            source = pieceToMove;
            destination = locationToMove;

        }

        // quit state sets source/destination to exit the game when the handle function returns

        else{
            source = "quit";
            destination = "quit";
        }

    }

    else{

        source = "quit";
        destination = "quit";

    }
	
	// Erase error message.
	cout << "\033[s";
	cout << "\r\033[33B\033[K";  
	cout << "\033[u";
}