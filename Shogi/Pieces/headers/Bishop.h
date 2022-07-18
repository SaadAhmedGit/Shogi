#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	static	sf::Texture texture;
	static sf::Texture texture_p;
	Bishop(Pos _pos, Color _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void draw() const;
	virtual void drawInPrison(sf::Vector2i corner, const int cellNo) const;
};

