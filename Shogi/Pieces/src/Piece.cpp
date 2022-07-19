#include "../headers/Piece.h"
#include "../../Board.h"

bool Piece::isDiagonal(Pos tgt) const
{
	return  abs(tgt.y - this->pos.y) != 0 && abs(tgt.y - this->pos.y) == abs(tgt.x - this->pos.x);
}

bool Piece::isDiagClear(Pos tgt) const
{
	Pos dir = pos;
	dir.y = (tgt.y > pos.y ? 1 : -1);
	dir.x = (tgt.x > pos.x ? 1 : -1);

	Pos i = { pos.y + dir.y, pos.x + dir.x };
	while (abs(i.y - tgt.y) > 0)
	{
		if ((*B)[i] != nullptr)
			return false;

		i.y += dir.y;
		i.x += dir.x;
	}
	return true;
}

bool Piece::isVertical(Pos tgt) const
{
	return pos.x == tgt.x;
}

bool Piece::isVertClear(Pos tgt) const
{
	Pos dir = { 0,0 };
	dir.y = (tgt.y > pos.y ? 1 : -1);

	Pos i = { pos.y + dir.y, pos.x };

	while (abs(i.y - tgt.y) > 0)
	{
		if ((*B)[i] != nullptr)
			return false;

		i.y += dir.y;
	}
	return true;
}

bool Piece::isHorizontal(Pos tgt) const
{
	return pos.y == tgt.y;
}

bool Piece::isHorizClear(Pos tgt) const
{
	Pos dir = { 0,0 };
	dir.x = (tgt.x > pos.x ? 1 : -1);

	Pos i = { pos.y, pos.x + dir.x };

	while (abs(i.x - tgt.x) > 0)
	{
		if ((*B)[i] != nullptr)
			return false;

		i.x += dir.x;
	}
	return true;
}

Piece::Piece(const Pos _pos, const Team _team, Board* const  _B, bool _isPromoted)
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
			return pos.y < 3;
		else
			return pos.y > 5;
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

Team Piece::getTeam() const
{
	return this->team;
}

void Piece::setTeam(Team _team)
{
	team = _team;
}
