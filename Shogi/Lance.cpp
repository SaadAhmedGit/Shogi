#include "Lance.h"
#include "GoldenGeneral.h"
#include "Board.h"

Lance::Lance(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

sf::Texture Lance::texture;
sf::Texture Lance::texture_p;

bool Lance::isValidMove(Pos tgtPos) const
{
	if (isPromoted)
	{
		GoldenGeneral tmp(pos, team, B);
		return tmp.isValidMove(tgtPos);
	}
	if (team == WHITE)
	{
		return (tgtPos.r < pos.r) && isVertical(tgtPos) && isVertClear(tgtPos);
	}
	else
	{
		return (tgtPos.r > pos.r) && isVertical(tgtPos) && isVertClear(tgtPos);
	}
}

void Lance::draw() const
{
	sf::Sprite sprite;
	auto& image = isPromoted ? texture_p : texture;
	sprite.setTexture(image);
	if (team == BLACK)
	{
		sprite.setRotation(180);
		sprite.setPosition((pos.c * 96) + 132, (pos.r * 96) + 142);
	}
	else
		sprite.setPosition((pos.c * 96) + 58, (pos.r * 96) + 52);
	sprite.setScale({ 0.4,0.4 });
	this->B->getWinPtr()->draw(sprite);
}
