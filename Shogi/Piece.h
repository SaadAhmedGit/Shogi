#pragma once
#include "Utility.h"

class Board;
class Piece
{
protected:
	Pos pos;
	Color team;
	Board* const  B;
public:
	Piece(const Pos _pos, const Color _team, Board* const  _B);
	virtual ~Piece();
	virtual bool isValidMove(Pos tgtPos) const = 0;
	virtual void move(Pos newPos) = 0;
	virtual void draw() const = 0;
	Pos getPos() const;
	char getID() const;
	Color getTeam() const;
	bool isCaptured() const;
	void capture();
};