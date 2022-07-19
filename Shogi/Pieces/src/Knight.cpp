#include "../headers/Knight.h"
#include "../headers/GoldenGeneral.h"
#include "../../Board.h"

sf::Texture Knight::texture;
sf::Texture Knight::texture_p;
Knight::Knight(Pos _pos, Team _team, Board* _B)
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
		return (pos.y - 2 == tgtPos.y) && ((pos.x + 1) == tgtPos.x || (pos.x - 1) == tgtPos.x);
	return (pos.y + 2 == tgtPos.y) && ((pos.x + 1) == tgtPos.x || (pos.x - 1) == tgtPos.x);
}

void Knight::draw() const
{
	sf::Sprite sprite;
	auto& image = isPromoted ? texture_p : texture;
	sprite.setTexture(image);
	sf::Vector2f imgCenter = static_cast<sf::Vector2f>(image.getSize());
	sprite.setOrigin({ imgCenter.x / 2, imgCenter.y / 2 });
	if (team == BLACK)	sprite.setRotation(180);
	sprite.setPosition((pos.x * 96) + (BOARD_X + 98), (pos.y * 96) + (BOARD_Y + 98));
	sprite.setScale({ 0.4,0.4 });
	this->B->getWinPtr()->draw(sprite);
}

void Knight::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	sf::Sprite sprite(texture);
	sprite.setPosition(corner.x + 8, corner.y + (98 * cellNo) + 16);
	sprite.setScale(0.4, 0.4);
	this->B->getWinPtr()->draw(sprite);
}
