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
	sf::Event event;
	std::vector<Player> PlayersArr;
	Board* B;

	//Static
	static sf::Texture menu;
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
	bool didYouRighClick();
	bool checkMate();
	bool prompt();
	bool liesInPrison(Pos raw);
	Pos mouseL();
	void drawBackground();
	void jishogi();
	std::string inputNames(int colPixel, const std::string& p1Name = "");
	std::vector<std::vector<bool>> computeDropZones(Piece* prisoner);
	void highlightForDrop(std::vector<std::vector<bool>>& dropZones);

public:
	Shogi();
	void loadAssets();
	~Shogi();
	void play();
};