/*
 * menu.cpp
 *
 */

#include "menu.h"

using namespace std;

void printBanner(void){
    cout << "\n\n\t _____________________________________________________________\n";
    cout << "\t|     _____ _    _ ______ _____ _  ________ _____   _____    |\n";
    cout << "\t|    / ____| |  | |  ____/ ____| |/ /  ____|  __ \\ / ____|   |\n";
    cout << "\t|   | |    | |__| | |__ | |    | ' /| |__  | |__) | (___     |\n";
    cout << "\t|   | |    |  __  |  __|| |    |  < |  __| |  _  / \\___ \\    |\n";
    cout << "\t|   | |____| |  | | |___| |____| . \\| |____| | \\ \\ ____) |   |\n";
    cout << "\t|    \\_____|_|  |_|______\\_____|_|\\_\\______|_|  \\_\\_____/    |\n";
    cout << "\t|____________________________________________________________|\n\n";
}

void printRules(void){

    char throwAway[25];
    throwAway[0] = 'p';
    cout << "\033[2J" << "\033[H\n\n";
	
	cout << "\033[s";
    cout << " Games Rules:" << endl;
    cout << " Taken from: https://www.officialgamerules.org/checkers \n\n" << endl;

    cout << " Game Pieces and Board:" << endl;
    cout << "\t- Checkers is a board game played between two people on an 8x8" << endl;
    cout << "\t  checked board like the one shown below." << endl;
    cout << "\t- Each player has 12 pieces that are like flat round disks that" << endl;
    cout << "\t  fit inside each of the boxes on the board. The pieces are" << endl;
    cout << "\t  placed on every other dark square and then staggered by rows," << endl;
    cout << "\t  like shown on the board." << endl;
    cout << "\t- Each Checkers player has different colored pieces. Sometimes" << endl;
    cout << "\t  the pieces are black and red or red and white." << endl;

    cout << "\n\n Taking a Turn:" << endl;
    cout << "\t- Each player takes their turn by moving a piece. Pieces are" << endl;
    cout << "\t  always moved diagonally and can be moved in the following ways:" << endl;
    cout << "\t\t+ Diagonally in the forward direction (towards the opponent)" << endl;
    cout << "\t\t  to the next dark square if a pawn piece (RO/BO)." << endl;
    cout << "\t\t+ Diagonally in the forward or backwards direction" << endl;
    cout << "\t\t  to the next dark square if a king piece (RK/BK)." << endl;
    cout << "\t\t+ If there is one of the opponent's pieces next to a piece and" << endl;
    cout << "\t\t  an empty space on the other side, you jump your opponent and" << endl;
    cout << "\t\t  remove their piece. If you have a jump, you must take it." << endl;

    cout << "\n\n King Pieces:" << endl;
    cout << "\t- The last row is called the king row. If you get a piece across the" << endl;
    cout << "\t  board to the opponent's king row, that piece becomes a king. Another" << endl;
    cout << "\t  piece is placed onto that piece so it is now two pieces high. King" << endl;
    cout << "\t  pieces can move in both directions, forward and backward." << endl;
    cout << "\t- Once a piece is kinged, the player must wait until the next turn to" << endl;
    cout << "\t  jump out of the king row." << endl;

    cout << "\n\n Winning the Game:" << endl;
    cout << "\t- You win the game when the opponent has no more pieces or can't move" << endl;
    cout << "\t  (even if he/she still has pieces). If neither player can move then it" << endl;
    cout << "\t  is a draw or a tie." << endl;

    cout << "\n\n Checkers Strategy and Tips:" << endl;
    cout << "\t- Pieces on the sides are valuable because they can't be jumped." << endl;
    cout << "\t- Don't bunch all your pieces in the middle or you may not be able to move," << endl;
    cout << "\t  and then you will lose." << endl;
    cout << "\t- Try to keep your pieces on the back row or king row for as long as" << endl;
    cout << "\t  possible, to keep the other player from gaining a king." << endl;
    cout << "\t- Plan ahead and try to look at every possible move before you take" << endl;
    cout << "\t  your turn." << endl;
    cout << "\t- Practice: if you play a lot against a lot of different players, you" << endl;
    cout << "\t  will get better." << endl;

    cout << "\n\n\n Hit enter to return to main menu...";
    cin.getline(throwAway, 25);
	cout << "\033[u";
}

void printInstructions(void){

    char throwAway[25];
    throwAway[0] = 'p';
    cout << "\033[2J" << "\033[H\n\n";
	cout << "\033[s";
    cout << " Game Instructions:\n\n" << endl;
    cout << " \tThe game is played by inputting coordinates to move pieces around the board." << endl;
    cout << " \tThe 8x8 checkers board is labeled on the x and y axis to label each space." << endl;
    cout << " \tSpace A0 refers to the top left corner of the board, and H7 refers to the bottom right." << endl;
    cout << " \tWhen a jump is available, the game will force the player to make a jump type move." << endl;
    cout << " \tIf an invalid move is entered, the player will be allowed to fix their error." << endl;
    cout << endl;
    cout << " \tIn single player mode, the player will be pitted against the CPU." << endl;
    cout << " \tThe CPU will make moves immediately after the player, so the board is updated two moves at a time." << endl;
    cout << endl;
    cout << " \tIn two player mode, two players must pass the keyboard back and forth to play against each other." << endl;
    cout << endl;
    cout << " \tIn watch CPU mode, two computers will be put against each other for spectating." << endl;

    cout << endl;
    cout << " \tTo quit the game at any time, type quit." << endl;

    cout << "\n\n Hit enter to return to main menu...";
    cin.getline(throwAway, 25);
	cout << "\033[u";
}

void printMenu(char &userChoice){

	cout << "\033[s";
    cout << "\033[2J" << "\033[H";
    printBanner();
    cout << "\t\tMenu:\n\n";
    cout << "\t\t0: Watch CPU" << endl;
    cout << "\t\t1: 1 Player" << endl;
    cout << "\t\t2: 2 Player" << endl;
    cout << "\t\t3: Games Rules" << endl;
    cout << "\t\t4: Terminal Instructions" << endl;
    cout << "\t\t5: Quit Game" << endl;
    cout << endl;
    cout << "\t\tChoose option: ";
    cin >> userChoice;
    cin.ignore(1000, '\n');
	cout << "\033[u";
}