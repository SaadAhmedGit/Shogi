#pragma once

#include "Piece.h"
#include <SFML/Graphics.hpp>

class Pawn : public Piece
{
private:
public:
	static	sf::Texture texture;
	static sf::Texture texture_p;
	Pawn(Pos _pos, Team _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void draw() const;
	virtual void drawInPrison(sf::Vector2i corner, const int cellNo) const;
};

