#ifndef gameController_hpp
#define gameController_hpp

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


#endif
