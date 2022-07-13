#include "Rook.h"
#include "Board.h"

sf::Texture Rook::texture;
Rook::Rook(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Rook::isValidMove(Pos tgtPos) const
{
	return (isVertical(tgtPos) && isVertClear(tgtPos)) || (isHorizontal(tgtPos) && isHorizClear(tgtPos));
}

void Rook::draw() const
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
