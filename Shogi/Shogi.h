#pragma once
#include <vector>
#include "Utility.h"

class Board;
class Player;

class Shogi
{
private:
	Board* B;
	bool turn;
	std::vector<Player> PlayersArr;

	//Helpers
	Pos pickOnBoard() const;
	bool isValidSelect(Pos tgt) const;
	bool isValidDest(Pos tgt) const;

public:
	Shogi();
	~Shogi();
	void play();
};

