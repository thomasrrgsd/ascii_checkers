/*
 * main.cpp
 *
 */

#include <iostream>
#include "menu.h"
#include "checkers.h"

using namespace std;

int main() {

    bool quitFlag = false;
    char userChoice = '5';

    cout << "\033[2J" << "\033[H";	// Clear the screen

    printMenu(userChoice);  // Get initial user input.

    while(!quitFlag){
        switch(userChoice){
            case '0':{
                Checkers cpuGame(CPU_VS_CPU);
                cpuGame.PlayGame();
                printMenu(userChoice);
                break;
            }
            case '1': {  // Code in each case is self-contained. Need curley braces.
                Checkers cpuHumanGame(CPU_VS_HUMAN);
                cpuHumanGame.PlayGame(); // Here is where the game will run for a 1 player game.
                printMenu(userChoice);    // userChoice passed by reference.
                break;
            }
            case '2': {
                Checkers humanGame(HUMAN_VS_HUMAN);
                humanGame.PlayGame(); // Here is where the game will run for a 2 player game.
                printMenu(userChoice);    // userChoice passed by reference.
                break;
            }
            case '3':
                printRules();
                printMenu(userChoice);	// userChoice passed by reference.
                break;
            case '4':
                printInstructions();
                printMenu(userChoice);	// userChoice passed by reference.
                break;
            case '5':
                cout << "\033[25B" << "\t\tThank you for playing, goodbye." << endl << endl;
                quitFlag = true;
                break;
            default:
				cout << "\033[s";
                cout << "\033[22B" << "\t\tInvalid choice, try again.";
                cout << "\r\033[2A" << "\033[K" << "\t\tChoose option:   \b\b";
                cin >> userChoice;
                cin.ignore(1000, '\n');	// Empties out cin buffer if user puts in more than number.
                cout << "\033[u";
				break;
        }
    }

    return 0;
}

/*
- Position the Cursor:
  \033[<L>;<C>H
     Or
  \033[<L>;<C>f
  puts the cursor at line L and column C.
- Move the cursor up N lines:
  \033[<N>A
- Move the cursor down N lines:
  \033[<N>B
- Move the cursor forward N columns:
  \033[<N>C
- Move the cursor backward N columns:
  \033[<N>D
- Clear the screen, move to (0,0):
  \033[2J
- Erase to end of line:
  \033[K
- Save cursor position:
  \033[s
- Restore cursor position:
  \033[u
*/