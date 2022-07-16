#include "SilverGeneral.h"
#include "GoldenGeneral.h"
#include "Board.h"

sf::Texture SilverGeneral::texture;
sf::Texture SilverGeneral::texture_p;

SilverGeneral::SilverGeneral(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool SilverGeneral::isValidMove(Pos tgtPos) const
{
	if (isPromoted)
	{
		GoldenGeneral tmp(pos, team, B);
		return tmp.isValidMove(tgtPos);
	}
	if (abs(tgtPos.r - pos.r) > 1
		|| abs(tgtPos.c - pos.c) > 1)
		return false;

	if (team == WHITE)
		return tgtPos.r == this->pos.r - 1 || isDiagonal(tgtPos);

	else
		return tgtPos.r == this->pos.r + 1 || isDiagonal(tgtPos);

}

void SilverGeneral::draw() const
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
