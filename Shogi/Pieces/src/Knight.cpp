#include "../headers/Knight.h"
#include "../headers/GoldenGeneral.h"
#include "../../Board.h"

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
	sf::Vector2f imgCenter = static_cast<sf::Vector2f>(image.getSize());
	sprite.setOrigin({ imgCenter.x / 2, imgCenter.y / 2 });
	if (team == BLACK)	sprite.setRotation(180);
	sprite.setPosition((pos.c * 96) + (BOARD_X + 98), (pos.r * 96) + (BOARD_Y + 98));
	sprite.setScale({ 0.4,0.4 });
	this->B->getWinPtr()->draw(sprite);
}

void Knight::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	sf::Sprite sprite(texture);
	sprite.setPosition(corner.x + 98, corner.y + (98 * cellNo));
	sprite.setScale(0.4, 0.4);
	this->B->getWinPtr()->draw(sprite);
}
