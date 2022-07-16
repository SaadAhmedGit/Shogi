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
	Board(sf::RenderWindow* windowPtr);
	~Board();
	sf::RenderWindow* getWinPtr();
	void movePiece(const Pos src, const Pos dest);
	void highLightMoves(Pos srcPiece);
	void printBoard();
	Pos findKing(Color team);
	Piece*& operator[](const Pos p);
};