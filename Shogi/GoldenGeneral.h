#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
class GoldenGeneral : public Piece
{
public:
	static	sf::Texture texture;
	GoldenGeneral(Pos _pos, Color _team, Board* _B);
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void draw() const;
};

