#include <iostream>

#include "../headers/Bishop.h"
#include "../headers/King.h"
#include "../../Board.h"

sf::Texture Bishop::texture;
sf::Texture Bishop::texture_p;

Bishop::Bishop(Pos _pos, Team _team, Board* _B)
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
	sf::Vector2f imgDim = static_cast<sf::Vector2f>(image.getSize());
	sprite.setOrigin({ imgDim.x / 2, imgDim.y / 2 });
	if (team == BLACK)	sprite.setRotation(180);
	sprite.setPosition((pos.x * 96) + (BOARD_X + 98), (pos.y * 96) + (BOARD_Y + 98));
	sprite.setScale({ 0.6,0.6 });
	this->B->getWinPtr()->draw(sprite);
}
void Bishop::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	sf::Sprite sprite(texture);
	sprite.setPosition(corner.x + 13, corner.y + (98 * cellNo) + 5);
	sprite.setScale(0.6, 0.6);
	this->B->getWinPtr()->draw(sprite);
}

int Bishop::getScore() const
{
	return 5;
}
