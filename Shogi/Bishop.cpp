#include <iostream>

#include "Bishop.h"
#include "King.h"
#include "Board.h"

sf::Texture Bishop::texture;
sf::Texture Bishop::texture_p;

Bishop::Bishop(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool Bishop::isValidMove(Pos tgtPos) const
{
	if (isPromoted)
	{
		King tmp(pos, team, B);
		return tmp.isValidMove(tgtPos)
			|| this->Piece::isDiagonal(tgtPos) && this->Piece::isDiagClear(tgtPos);
	}
	return this->Piece::isDiagonal(tgtPos) && this->Piece::isDiagClear(tgtPos);
}

void Bishop::draw() const
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
