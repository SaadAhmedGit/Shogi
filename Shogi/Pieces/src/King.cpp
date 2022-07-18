#include "../headers/King.h"
#include "../../Board.h"

sf::Texture King::textureW;
sf::Texture King::textureB;
King::King(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool King::isValidMove(Pos tgtPos) const
{
	return abs(tgtPos.r - pos.r) <= 1 && abs(tgtPos.c - pos.c) <= 1;
}

bool King::isPromotable() const
{
	return false;
}

void King::draw() const
{
	sf::Sprite sprite;
	sf::Vector2f imgDim;
	if (team == BLACK)
	{
		sprite.setTexture(textureB);
		imgDim = static_cast<sf::Vector2f>(textureB.getSize());
		sprite.setRotation(180);
	}
	else
	{
		sprite.setTexture(textureW);
		imgDim = static_cast<sf::Vector2f>(textureW.getSize());
	}

	sprite.setOrigin({ imgDim.x / 2, imgDim.y / 2 });
	sprite.setPosition((pos.c * 96) + (BOARD_X + 98), (pos.r * 96) + (BOARD_Y + 98));
	sprite.setScale({ 0.4,0.4 });
	this->B->getWinPtr()->draw(sprite);
}

void King::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	return;
}
