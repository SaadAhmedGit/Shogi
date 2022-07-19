#pragma once
#include "Piece.h"
#include <SFML/Graphics.hpp>
class GoldenGeneral : public Piece
{
public:
	static	sf::Texture texture;
	GoldenGeneral(Pos _pos, Team _team, Board* _B);
	virtual bool isPromotable() const override;
	virtual bool isValidMove(Pos tgtPos) const;
	virtual void draw() const;
	virtual void drawInPrison(sf::Vector2i corner, const int cellNo) const;
};

