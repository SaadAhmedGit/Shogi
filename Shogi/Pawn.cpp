#include <iostream>

#include "Pawn.h"
#include "Board.h"


sf::Texture Pawn::texture;
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
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale({ 0.4,0.4 });
	sprite.setScale({ 0.4,0.4 });
	sprite.setPosition((pos.c * 96) + 58, (pos.r * 96) + 52);
	if (team == BLACK)
	{
		sprite.setRotation(180);
		sprite.setPosition((pos.c * 96) + 132, (pos.r * 96) + 142);
	}
	this->B->getWinPtr()->draw(sprite);
}
