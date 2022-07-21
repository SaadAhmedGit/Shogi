#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	static	sf::Texture textureW;
	static	sf::Texture textureB;
	King(Pos _pos, Team _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual bool isPromotable() override;
	virtual void draw() const;
	virtual void drawInPrison(sf::Vector2i corner, const int cellNo) const;
	virtual int getScore() const override;
};

