#pragma once
#include "../../Utility.h"

class Board;
class Piece
{
protected:
	Pos pos;
	Team team;
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
	Piece(const Pos _pos, const Team _team, Board* const  _B, bool _isPromoted = false);
	virtual ~Piece();
	virtual bool isValidMove(Pos tgtPos) const = 0;
	void move(Pos newPos);
	void promote();
	void demote();
	virtual bool isPromotable();
	std::vector<std::vector<bool>> getValidMoves() const;
	virtual void draw() const = 0;
	virtual void drawInPrison(sf::Vector2i corner, const int cellNo) const = 0;
	Pos getPos() const;
	Team getTeam() const;
	void setTeam(Team _team);
	bool promoStatus() const;
	virtual int getScore() const;
};