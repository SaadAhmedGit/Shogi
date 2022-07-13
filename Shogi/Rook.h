#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	static	sf::Texture texture;
	Rook(Pos _pos, Color _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void draw() const;
};

