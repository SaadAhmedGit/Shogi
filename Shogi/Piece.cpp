#include "Piece.h"
#include "Board.h"

bool Piece::isDiagonal(Pos tgt) const
{
	return abs(tgt.r - this->pos.r) == abs(tgt.c - this->pos.c);
}

bool Piece::isDiagClear(Pos tgt) const
{
	Pos dir = { 0,0 };
	dir.r = (tgt.r > pos.r ? 1 : -1);
	dir.c = (tgt.c > pos.c ? 1 : -1);

	Pos i = { pos.r + dir.r, pos.c + dir.c };

	while (abs(i.r - tgt.r) > 0)
	{
		if ((*B)[i] != nullptr)
			return false;

		i.r += dir.r;
		i.c += dir.c;
	}
	return true;
}

bool Piece::isVertical(Pos tgt) const
{
	return pos.c == tgt.c;
}

bool Piece::isVertClear(Pos tgt) const
{
	Pos dir = { 0,0 };
	dir.r = (tgt.r > pos.r ? 1 : -1);

	Pos i = { pos.r + dir.r, pos.c };

	while (abs(i.r - tgt.r) > 0)
	{
		if ((*B)[i] != nullptr)
			return false;

		i.r += dir.r;
	}
	return true;
}

bool Piece::isHorizontal(Pos tgt) const
{
	return pos.r == tgt.r;
}

bool Piece::isHorizClear(Pos tgt) const
{
	Pos dir = { 0,0 };
	dir.c = (tgt.c > pos.c ? 1 : -1);

	Pos i = { pos.r, pos.c + dir.c};

	while (abs(i.c - tgt.c) > 0)
	{
		if ((*B)[i] != nullptr)
			return false;

		i.c += dir.c;
	}
	return true;
}

Piece::Piece(const Pos _pos, const Color _team, Board* const  _B)
	:pos(_pos), team(_team), B(_B)
{
}

Piece::~Piece()
{
}

void Piece::move(Pos newPos)
{
	this->pos = newPos;
}

Pos Piece::getPos() const
{
	return this->pos;
}

Color Piece::getTeam() const
{
	return this->team;
}