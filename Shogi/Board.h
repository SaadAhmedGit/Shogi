#pragma once
#include <vector>
#include "Utility.h"

class Piece;
class Player;

class Board
{
private:
	std::vector<std::vector<Piece*>> piecesArr;
public:
	Board();
	~Board();
	void movePiece(const Pos src, const Pos dest);
	void printBoard();
	Piece*& operator[](const Pos p);
};