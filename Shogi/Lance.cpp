#include "Lance.h"
#include "Board.h"

Lance::Lance(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

sf::Texture Lance::texture;

bool Lance::isValidMove(Pos tgtPos) const
{
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
