#pragma once
#include <vector>


class Piece;
class Player;

class Board
{
private:
	std::vector<std::vector<Piece*>> piecesArr;
public:
	Board();
	~Board();
	void printBoard();
	std::vector<Piece*>& operator[](int i);
};