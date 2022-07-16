#pragma once
#include "Piece.h"
class Knight :public Piece
{
public:
	static sf::Texture texture;
	static sf::Texture texture_p;
	Knight(Pos _pos, Color _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void draw() const;
};

