#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utility.h"
#include "Pawn.h"

class Board;
class Player;

class Shogi
{
private:
	bool turn;
	sf::RenderWindow window;
	std::vector<Player> PlayersArr;
	Board* B;

	//Helpers
	Pos pickOnBoard(sf::RenderWindow& window, sf::Event& event) const;
	bool isValidSelect(Pos tgt) const;
	bool isValidDest(Pos tgt) const;

public:
	Shogi();
	void loadAssets();
	~Shogi();
	void play();
};

