#include "King.h"
#include "Board.h"

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
	if (team == BLACK)
	{
		sprite.setTexture(textureB);
		sprite.setRotation(180);
		sprite.setPosition((pos.c * 96) + 132, (pos.r * 96) + 142);
	}
	else
	{
		sprite.setTexture(textureW);
		sprite.setPosition((pos.c * 96) + 58, (pos.r * 96) + 52);
	}
	sprite.setScale({ 0.4,0.4 });
	this->B->getWinPtr()->draw(sprite);
}
