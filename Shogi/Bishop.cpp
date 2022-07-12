#include "Bishop.h"
#include <iostream>

Bishop::Bishop(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Bishop::isValidMove(Pos tgtPos) const
{
	return this->Piece::isDiagonal(tgtPos) && this->Piece::isDiagClear(tgtPos);
}

void Bishop::draw() const
{
	//Convert to graphics using SFML
	std::cout << (this->team == BLACK ? 'b' : 'B');
}
