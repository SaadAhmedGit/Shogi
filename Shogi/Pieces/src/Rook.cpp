#include "../headers/Rook.h"
#include "../headers/King.h"
#include "../../Board.h"

sf::Texture Rook::texture;
sf::Texture Rook::texture_p;
Rook::Rook(Pos _pos, Team _team, Board* _B)
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
	sf::Vector2f imgCenter = static_cast<sf::Vector2f>(image.getSize());
	sprite.setOrigin({ imgCenter.x / 2, imgCenter.y / 2 });
	if (team == BLACK)	sprite.setRotation(180);
	sprite.setPosition((pos.x * 96) + (BOARD_X + 98), (pos.y * 96) + (BOARD_Y + 98));
	sprite.setScale({ 0.6,0.6 });
	this->B->getWinPtr()->draw(sprite);
}

void Rook::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	sf::Sprite sprite(texture);
	sprite.setPosition(corner.x + 13, corner.y + (98 * cellNo) + 5);
	sprite.setScale(0.6, 0.6);
	this->B->getWinPtr()->draw(sprite);
}

int Rook::getScore() const
{
	return 5;
}
