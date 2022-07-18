#include "../headers/Piece.h"
#include "../../Board.h"

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

	Pos i = { pos.r, pos.c + dir.c };

	while (abs(i.c - tgt.c) > 0)
	{
		if ((*B)[i] != nullptr)
			return false;

		i.c += dir.c;
	}
	return true;
}

Piece::Piece(const Pos _pos, const Color _team, Board* const  _B, bool _isPromoted)
	:pos(_pos), team(_team), B(_B), isPromoted(_isPromoted)
{
}

Piece::~Piece()
{
}

void Piece::move(Pos newPos)
{
	this->pos = newPos;
}

void Piece::promote()
{
	isPromoted = true;
}

bool Piece::isPromotable() const
{
	if (!isPromoted)
	{
		if (team == WHITE)
			return pos.r < 3;
		else
			return pos.r > 5;
	}
	return false;
}

std::vector<std::vector<bool>> Piece::getValidMoves() const
{
	std::vector<std::vector<bool>> validMoves;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			validMoves.push_back(std::vector<bool>(9));
			if ((*B)[{i, j}] == nullptr && this->isValidMove({ i, j }))
			{
				validMoves[i][j] = true;
			}
			else if ((*B)[{i, j}] != nullptr && this->getTeam() != (*B)[{i, j}]->getTeam()
					 && this->isValidMove({ i, j }))
			{
				validMoves[i][j] = true;
			}
			else
				validMoves[i][j] = false;
		}
	}
	return validMoves;
}

Pos Piece::getPos() const
{
	return this->pos;
}

Color Piece::getTeam() const
{
	return this->team;
}