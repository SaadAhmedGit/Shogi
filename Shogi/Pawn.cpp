#include <iostream>

#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Pawn::isValidMove(Pos tgtPos) const
{
	if (tgtPos.c == this->pos.c)
	{

		switch (this->team)
		{
			case WHITE:
				return tgtPos.r == this->pos.r - 1;
				break;
			case BLACK:
				return tgtPos.r == this->pos.r + 1;
				break;
		}
	}
	return false;
}

void Pawn::draw() const
{
	//get the pawn texture using SFML called asset/pawn.png and diaply it on window
	sf::Texture pawnTexture;
	pawnTexture.loadFromFile("assets\\pawn.png");
	sf::Sprite pawnSprite;
	pawnSprite.setTexture(pawnTexture);
	pawnSprite.setPosition((pos.c * 96) + 50, (pos.r * 96) + 50);
	pawnSprite.setScale({ 0.4,0.4 });
	this->B->getWinPtr()->draw(pawnSprite);
}
