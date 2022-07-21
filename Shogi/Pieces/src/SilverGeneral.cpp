#include "../headers/SilverGeneral.h"
#include "../headers/GoldenGeneral.h"
#include "../../Board.h"

sf::Texture SilverGeneral::texture;
sf::Texture SilverGeneral::texture_p;

SilverGeneral::SilverGeneral(Pos _pos, Team _team, Board* _B)
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
	if (abs(tgtPos.y - pos.y) > 1
		|| abs(tgtPos.x - pos.x) > 1)
		return false;

	if (team == WHITE)
		return tgtPos.y == this->pos.y - 1 || isDiagonal(tgtPos);

	else
		return tgtPos.y == this->pos.y + 1 || isDiagonal(tgtPos);

}

void SilverGeneral::draw() const
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

void SilverGeneral::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	sf::Sprite sprite(texture);
	sprite.setPosition(corner.x + 13, corner.y + (98 * cellNo) + 5);
	sprite.setScale(0.6, 0.6);
	this->B->getWinPtr()->draw(sprite);
}
