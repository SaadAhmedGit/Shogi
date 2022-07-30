#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utility.h"

class Piece;
class Player;

class Board
{
private:
	std::vector<std::vector<Piece*>> piecesArr;
	sf::RenderWindow* winP;
public:
	static sf::Texture green_h;
	static sf::Texture red_h;
	static sf::Texture boardTexture;
	Board(sf::RenderWindow* windowPtr, const std::string& boardFile);
	~Board();
	sf::RenderWindow* getWinPtr();
	void movePiece(const Pos src, const Pos dest);
	void highLightMoves(Pos srcPiece);
	void printBoard();
	Pos findKing(Team team);
	Piece*& operator[](const Pos p);
};