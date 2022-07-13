#include <iostream>

#include "Bishop.h"
#include "Board.h"

sf::Texture Bishop::texture;

Bishop::Bishop(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Bishop::isValidMove(Pos tgtPos) const
{
	return this->Piece::isDiagonal(tgtPos) && this->Piece::isDiagClear(tgtPos);
}

void Bishop::draw() const
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setScale({ 0.4,0.4 });
	sprite.setScale({ 0.4,0.4 });
	sprite.setPosition((pos.c * 96.1) + 58, (pos.r * 95.4) + 52);
	if (team == BLACK)
	{
		sprite.setRotation(180);
		sprite.setPosition((pos.c * 96.1) + 130, (pos.r * 95.4) + 142);
	}
	this->B->getWinPtr()->draw(sprite);
}
