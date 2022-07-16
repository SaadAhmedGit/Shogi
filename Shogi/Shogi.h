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
	static sf::Font font;
	static sf::Texture promoTexture;
	Board* B;

	//Helpers
	Pos pickOnBoard(sf::RenderWindow& window, sf::Event& event);
	bool isValidSelect(Pos tgt) const;
	bool isValidDest(Pos tgt) const;
	void printText();
	bool Check();
	bool selfCheck();
	bool checkMate();
	bool prompt();
	Pos mouseL();

public:
	Shogi();
	void loadAssets();
	~Shogi();
	void play();
};

