/*
 * computerplayer.cpp
 *
 */
 
#include "computerplayer.h"

using namespace std;


/*
 * This function will only be used internally by the computerplayer class, and will take into a list of factors
 * to figure out which move will be taken by the computer.
 *
 *  FACTORS CHECKED:
 *      How many pieces does the opponent have?
 *      How many pieces does the computer have?
 *      How many kings does the opponent/computer have?
 *      How many possible jumps can be made in the future?
 *      How close is the average piece to a corner?
 *      How close is the average piece to becoming a king?
 *
 *  After checking these it has an algorithm to choose a spot to go to.
 */
void findMove() {


}

computerplayer::computerplayer(array<piece*, 12> *pieces1,
							   array<piece*, 12> *pieces2) : player(pieces1, pieces2) {
	Ppieces = pieces1;
	Opieces = pieces2;
}

void computerplayer::handlePlayer(string &source, string &destination) {
	bool pieceValid = false;            // Holds the value to know if the piece given is valid
	bool locationValid = false;         // Holds the value to know if the location given is valid
	string pieceToMove;         		// Holds string for what piece the player wants to be moved
	string backupMove;
	string locationToMove;      		// Holds string for location the player wants to move to
	piece * usedPiece;
	piece * backupPiece;
	bool jump;

	string tempStr;


	sleep_for(seconds(1));

	for (array<piece*, 12>::iterator it = &Ppieces->front(); (it) != Ppieces->end(); it++) {

		for (std::list<moveObj*>::iterator it2 = (*it)->validMoves.begin(); it2 != (*it)->validMoves.end(); it2++) {

			if ((*it2)->isJump == true) {

				jump = true;
				usedPiece = (*it);
				locationToMove = (*it2)->space;
				break;
			} else {
				backupPiece = (*it);
				backupMove = (*it2)->space;
			}
		}
	}

	if (jump == true) {
		tempStr = usedPiece->position;
		source = tempStr;
		destination = locationToMove;
		return;
	}

	destination = backupMove;
	source = backupPiece->position;
}
