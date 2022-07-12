#include "Piece.h"

Piece::Piece(const Pos _pos, const Color _team, Board* const  _B)
	:pos(_pos), team(_team), B(_B)
{
}

Piece::~Piece()
{
}

Pos Piece::getPos() const
{
	return this->pos;
}

Color Piece::getTeam() const
{
	return this->team;
}