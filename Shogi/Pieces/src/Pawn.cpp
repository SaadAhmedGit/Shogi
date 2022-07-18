#include <iostream>

#include "../../Board.h"
#include "../headers/Pawn.h"
#include "../headers/GoldenGeneral.h"


sf::Texture Pawn::texture;
sf::Texture Pawn::texture_p;
Pawn::Pawn(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Pawn::isValidMove(Pos tgtPos) const
{
	if (isPromoted)
	{
		GoldenGeneral tmp(pos, team, B);
		return tmp.isValidMove(tgtPos);
	}
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
	auto& image = isPromoted ? texture_p : texture;
	sprite.setTexture(image);
	sf::Vector2f imgCenter = static_cast<sf::Vector2f>(image.getSize());
	sprite.setOrigin({ imgCenter.x / 2, imgCenter.y / 2 });
	if (team == BLACK)	sprite.setRotation(180);
	sprite.setPosition((pos.c * 96) + (BOARD_X + 98), (pos.r * 96) + (BOARD_Y + 98));
	sprite.setScale({ 0.4,0.4 });
	this->B->getWinPtr()->draw(sprite);
}

void Pawn::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	sf::Sprite sprite(texture);
	sprite.setPosition(corner.x + 98, corner.y + (98 * cellNo));
	sprite.setScale(0.4, 0.4);
	this->B->getWinPtr()->draw(sprite);
}
