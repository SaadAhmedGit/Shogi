#pragma once
#include "Utility.h"

class Board;
class Piece
{
protected:
	Pos pos;
	Color team;
	Board* B;
	bool isPromoted;

	//Helper methods
	bool isDiagonal(Pos tgt) const;
	bool isDiagClear(Pos tgt) const;
	bool isVertical(Pos tgt) const;
	bool isVertClear(Pos tgt) const;
	bool isHorizontal(Pos tgt) const;
	bool isHorizClear(Pos tgt) const;
public:
	Piece(const Pos _pos, const Color _team, Board* const  _B, bool _isPromoted = false);
	virtual ~Piece();
	virtual bool isValidMove(Pos tgtPos) const = 0;
	void move(Pos newPos);
	void promote();
	virtual bool isPromotable() const;
	std::vector<std::vector<bool>> getValidMoves() const;
	virtual void draw() const = 0;
	Pos getPos() const;
	Color getTeam() const;
};