#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(Pos _pos, Color _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void draw() const;
};

