#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Utility.h"
#include "Pieces/headers/Pawn.h"

class Board;
class Player;

class Shogi
{
private:
	bool turn;
	sf::RenderWindow window;
	std::vector<Player> PlayersArr;
	Board* B;

	//Static
	static sf::Texture bgTexture;
	static sf::Texture promoTexture;
	static sf::Font font;

	//Helpers
	Pos mapToBoard(Pos raw);
	bool isValidSelect(Pos tgt) const;
	bool isValidDest(Pos tgt) const;
	void printText();
	bool Check();
	bool selfCheck();
	bool checkMate();
	bool prompt();
	bool liesInPrison(Pos raw);
	Pos mouseL();
	void drawBackground();
	std::vector<std::vector<bool>> computeDropZones(Piece* prisoner);
	void highlightForDrop(std::vector<std::vector<bool>>& dropZones);

public:
	Shogi();
	void loadAssets();
	~Shogi();
	void play();
};