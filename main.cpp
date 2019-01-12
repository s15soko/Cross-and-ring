#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

// enum for fields in board
enum field
{
	EMPTY = 0,
	CROSS = 1,
	RING = 2
};

// player class
class player
{
	field playerSign;
	short playerID;

public:
	// set player sign
	void setPlayerSign(field sign)
	{
		this->playerSign = sign;
	}
	// set player id
	void setPlayerID(int id)
	{
		this->playerID = id;
	}

	// return player id
	int returnID()
	{
		return this->playerID;
	}
	// return player sign
	field returnSign()
	{
		return this->playerSign;
	}
};

// enum for game status
enum game_status
{
	END = 0,
	PLAY = 1,
	MENU = 2,
	DRAW = 3,
	WIN = 4
};

// game controller class
class gameController
{
	player actuallPlayer;
	field board[3][3]; // game board
	short emptyBoardFields;
	game_status STATUS;

public:
	// set game status
	void gameStatus(game_status status)
	{
		this->STATUS = status;
	}

	// reset board
	void resetBoard()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				this->board[i][j] = EMPTY;
			}
		}
		emptyBoardFields = 9;
	}

	// draw board
	void drawBoard()
	{
		int counter = 1;
		for (int i = 0; i < 3; i++)
		{
			cout << "-------" << endl;
			for (int j = 0; j < 3; j++)
			{
				if (this->board[i][j] == EMPTY)	cout << "|" << counter;
				if (this->board[i][j] == CROSS)	cout << "|O";
				if (this->board[i][j] == RING)	cout << "|X";

				counter++;
			}
			cout << "|";
			cout << endl;
		}
	}

	// set board field
	void setBoardField(int fieldNumber)
	{
		if (fieldNumber < 1 || fieldNumber > 9) {/*do nothing*/ }

		// 1 - 3
		if ((fieldNumber >= 1 && fieldNumber <= 3))
		{
			if (this->board[0][fieldNumber - 1] == EMPTY)
			{
				this->board[0][fieldNumber - 1] = this->actuallPlayer.returnSign();
				this->emptyBoardFields--;
			}

		}
		// 4 - 6
		if ((fieldNumber >= 4 && fieldNumber <= 6))
		{
			if (this->board[1][fieldNumber - 4] == EMPTY)
			{
				this->board[1][fieldNumber - 4] = this->actuallPlayer.returnSign();
				this->emptyBoardFields--;
			}

		}
		// 7 - 9
		if ((fieldNumber >= 7 && fieldNumber <= 9))
		{
			if (this->board[2][fieldNumber - 7] == EMPTY)
			{
				this->board[2][fieldNumber - 7] = this->actuallPlayer.returnSign();
				this->emptyBoardFields--;
			}
		}
	}

	// check board
	int checkBoard()
	{
		field sign = actuallPlayer.returnSign();
		int counter = 0;

		// check board horizontally
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (this->board[i][j] == sign) counter++;
			}

			// return true = someone win
			if (counter == 3)
			{
				STATUS = WIN;
				return true;
			}
			else counter = 0;
		}

		// check board vertically
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (this->board[j][i] == sign) counter++;
			}

			// return true = someone win
			if (counter == 3)
			{
				STATUS = WIN;
				return true;
			}
			else counter = 0;
		}


		// check board across from right top to left bottom
		int fieldNumber = 2;
		for (int i = 0; i < 3; i++)
		{
			if (this->board[i][fieldNumber] == sign) counter++;
			fieldNumber--;
		}
		// return true = someone win
		if (counter == 3)
		{
			STATUS = WIN;
			return true;
		}
		else counter = 0;

		// check board across from left bottom to top right
		fieldNumber = 0;
		for (int i = 0; i < 3; i++)
		{
			if (this->board[i][fieldNumber] == sign) counter++;
			fieldNumber++;
		}
		// return true = someone win
		if (counter == 3)
		{
			STATUS = WIN;
			return true;
		}
		else counter = 0;


		if (this->emptyBoardFields == 0)
		{
			STATUS = DRAW;
			return true;
		}

		// else return false
		return false;
	}

	// rand player
	void randPlayer(player *player1, player *player2)
	{
		this->actuallPlayer = rand() % 2 ? *player1 : *player2;
	}

	// change player
	void changePlayer(player *player1, player *player2)
	{
		if (this->actuallPlayer.returnID() == player1->returnID())
			this->actuallPlayer = *player2;
		else this->actuallPlayer = *player1;
	}

	// return game status
	game_status returnGameStatus()
	{
		return this->STATUS;
	}

	// return player sign
	field returnPlayerSign()
	{
		return this->actuallPlayer.returnSign();
	}
};



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
	gameController.gameStatus(MENU);


	// game loop
	do
	{
		system("cls");
		// draw board
		gameController.drawBoard();

		// choose the field
		cout << "Actually sign: " << gameController.returnPlayerSign();
		cout << " Choose the field [0-9]: ";
		int sign;
		cin >> sign;

		// set board field
		gameController.setBoardField(sign);


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
			case 1:
				gameController.gameStatus(PLAY);
				gameController.resetBoard();
				gameController.randPlayer(&player1, &player2);
				break;
			case 2: 
				gameController.gameStatus(END);
				break;
			default:
				gameController.gameStatus(END);
			}
		}
		else
		{
			// change player
			gameController.changePlayer(&player1, &player2);
		}

		// while game status != end
	} while (gameController.returnGameStatus() != END);

	return 0;
}