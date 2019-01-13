#ifndef player_hpp
#define player_hpp
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
#endif