#include "Rook.h"
#include "King.h"
#include "Board.h"

sf::Texture Rook::texture;
sf::Texture Rook::texture_p;
Rook::Rook(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Rook::isValidMove(Pos tgtPos) const
{
	if (isPromoted)
	{
		King tmp(pos, team, B);
		return tmp.isValidMove(tgtPos) || (isVertical(tgtPos) && isVertClear(tgtPos)) || (isHorizontal(tgtPos) && isHorizClear(tgtPos));
	}
	return (isVertical(tgtPos) && isVertClear(tgtPos)) || (isHorizontal(tgtPos) && isHorizClear(tgtPos));
}

void Rook::draw() const
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
