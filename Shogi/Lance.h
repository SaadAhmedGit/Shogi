#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>

class Lance : public Piece
{
public:
	static	sf::Texture texture;
	static sf::Texture texture_p;
	Lance(Pos _pos, Color _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void draw() const;
};

