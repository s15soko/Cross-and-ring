#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#include "boardFields.hpp"
#include "gameStatus.hpp"
#include "player.hpp"
#include "gameController.hpp"


int main()
{
	srand(time(NULL));

	// create player objects
	// player 1
	player player1;
	player1.setPlayerID(1);
	player1.setPlayerSign(CROSS);
	// player 2
	player player2;
	player1.setPlayerID(2);
	player2.setPlayerSign(RING);


	// new object for game
	gameController gameController;
	// reset the board (set empty)
	gameController.resetBoard();
	// rand player first move
	gameController.randPlayer(&player1, &player2);
	// set play status to start the game
	gameController.gameStatus(PLAY);


	// game loop
	do
	{
		system("cls");
		// draw board
		gameController.drawBoard();

		// choose the field
		cout << "Actually sign: " << gameController.returnPlayerSign();
		char sign;

		cout << " Choose the field [0-9]: ";
		cin >> sign;
	
		// if sign is valid 
		if (sign >= 49 && sign <= 57)
		{
			// set board field
			// -48 to receive valid int 
			gameController.setBoardField((int)sign-48);

			// if someone win or there is no empty fields
			if (gameController.checkBoard())
			{
				system("cls");
				// draw board -- update
				gameController.drawBoard();

				if (gameController.returnGameStatus() == WIN)
					cout << " === PLAYER " << gameController.returnPlayerSign() << " won the game! === " << endl;
				if (gameController.returnGameStatus() == DRAW)
					cout << " === NO ONE WIN ===" << endl;

				// choice
				cout << endl << "== What you want to do? ==" << endl;
				cout << "1. Play again." << endl;
				cout << "2. Exit" << endl;
				short choice;
				cin >> choice;

				switch (choice)
				{
				case 1: // start a new game
					gameController.gameStatus(PLAY);
					gameController.resetBoard();
					gameController.randPlayer(&player1, &player2);
					break;
				case 2: // exit
					gameController.gameStatus(END);
					break;
				default: // exit
					gameController.gameStatus(END);
				}
			}
			else
			{
				// change player
				gameController.changePlayer(&player1, &player2);
			}
		}

		// while game status != end
	} while (gameController.returnGameStatus() != END);

	return 0;
}
