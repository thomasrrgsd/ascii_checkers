/*
 * piece.h
 *
 */

#include "piece.h"


using namespace std;

/*
 * Constructor
 *
 */
piece::piece(bool c, string p){  // Constructor. Must be passed values to create pieces.
    color = c;
    king = false;
    position = p;  // Position given in coordinate form. Where is the piece on the board??
}

/*
 * Destructor. Delete all move objects associated with piece.
 * The pointers themselves will be deleted automatically.
 *
 */
piece::~piece(){
	for(auto objPtr : validMoves){
		delete objPtr;
	}
}

/*
 * The copy constructor grabs each moveObj from the others
 * valid move list and makes a copy of it. This copy is put
 * on the heap and pushed to this valid move list.
 *
 */
piece::piece(const piece &other){
	
	for(auto objPtr : other.validMoves){
		moveObj aMove = *objPtr;
		moveObj* newMove = new moveObj(aMove.space,  aMove.isJump, aMove.pieceJumped);
		newMove->kingMe = aMove.kingMe;
		validMoves.push_front(newMove);
	}
}

/*
 * Same as the copy constructor, except that we must
 * check if its the same object and then empty out the old list.
 *
 */
piece& piece::operator=(const piece &other){
	
	if(&other == this) {
		return *this;
	}
	
	for(auto objPtr : validMoves){
		delete objPtr;
	}
	
	for(auto objPtr : other.validMoves){
		moveObj aMove = *objPtr;
		moveObj* newMove = new moveObj(aMove.space,  aMove.isJump, aMove.pieceJumped);
		newMove->kingMe = aMove.kingMe;
		validMoves.push_front(newMove);
	}

	return *this;
}

/*
 * Given a piece object it will print its characteristics.
 * This is used to populate the spaces on the board GUI.
 *
 */
void piece::printPiece() const{

    if(color && !king){
        cout << "RO";
    }
    else if(color && king){
        cout << "RK";
    }
    else if(!color && !king){
        cout << "BO";
    }
    else{
        cout << "BK";
    }
}

