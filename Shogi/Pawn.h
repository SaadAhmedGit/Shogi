#pragma once

#include "Piece.h"

class Pawn : public Piece
{
private:

public:
	Pawn(Pos _pos, Color _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void move(Pos newPos);
	virtual void draw() const;
};

