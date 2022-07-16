#include "Knight.h"
#include "GoldenGeneral.h"
#include "Board.h"

sf::Texture Knight::texture;
sf::Texture Knight::texture_p;
Knight::Knight(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Knight::isValidMove(Pos tgtPos) const
{
	if (isPromoted)
	{
		GoldenGeneral tmp(pos, team, B);
		return tmp.isValidMove(tgtPos);
	}
	if (team == WHITE)
		return (pos.r - 2 == tgtPos.r) && ((pos.c + 1) == tgtPos.c || (pos.c - 1) == tgtPos.c);
	return (pos.r + 2 == tgtPos.r) && ((pos.c + 1) == tgtPos.c || (pos.c - 1) == tgtPos.c);
}

void Knight::draw() const
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
