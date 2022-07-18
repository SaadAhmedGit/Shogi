#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	static	sf::Texture textureW;
	static	sf::Texture textureB;
	King(Pos _pos, Color _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual bool isPromotable() const override;
	virtual void draw() const;
	virtual void drawInPrison(sf::Vector2i corner, const int cellNo) const;
};

