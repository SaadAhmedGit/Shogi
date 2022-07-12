#include <iostream>

#include "Pawn.h"

Pawn::Pawn(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Pawn::isValidMove(Pos tgtPos) const
{
	if (tgtPos.c == this->pos.c)
	{

		switch (this->team)
		{
			case WHITE:
				return tgtPos.r == this->pos.r - 1;
				break;
			case BLACK:
				return tgtPos.r == this->pos.r + 1;
				break;
		}
	}
	return false;
}

void Pawn::draw() const
{
	//Convert to graphics using SFML
	std::cout << (this->team == BLACK ? 'p' : 'P');
}
