#include "GoldenGeneral.h"
#include "Board.h"

sf::Texture GoldenGeneral::texture;
GoldenGeneral::GoldenGeneral(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool GoldenGeneral::isPromotable() const
{
	return false;
}

bool GoldenGeneral::isValidMove(Pos tgtPos) const
{
	if (abs(tgtPos.r - pos.r) > 1
		|| abs(tgtPos.c - pos.c) > 1)
		return false;

	if (team == WHITE && pos.r < tgtPos.r)
		return tgtPos.c == pos.c;

	else if (team == BLACK && pos.r > tgtPos.r)
		return tgtPos.c == pos.c;

	return isVertical(tgtPos) || isHorizontal(tgtPos) || isDiagonal(tgtPos);
}

void GoldenGeneral::draw() const
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
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
