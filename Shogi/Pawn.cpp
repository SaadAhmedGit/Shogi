#include <iostream>

#include "Pawn.h"

Pawn::Pawn(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Pawn::isValidMove(Pos tgtPos) const
{
	//TODO: Go to the board and do sum stuff then decide what to return
	return true;
}

void Pawn::move(Pos newPos)
{
	this->pos = newPos;
}

void Pawn::draw() const
{
	std::cout << (this->team == BLACK ? 'P' : 'p');
}
