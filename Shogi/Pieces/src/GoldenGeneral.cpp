#include "../headers/GoldenGeneral.h"
#include "../../Board.h"

sf::Texture GoldenGeneral::texture;
GoldenGeneral::GoldenGeneral(Pos _pos, Team _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool GoldenGeneral::isPromotable()
{
	return false;
}

bool GoldenGeneral::isValidMove(Pos tgtPos) const
{
	if (abs(tgtPos.y - pos.y) > 1
		|| abs(tgtPos.x - pos.x) > 1)
		return false;

	if (team == WHITE && pos.y < tgtPos.y)
		return tgtPos.x == pos.x;

	else if (team == BLACK && pos.y > tgtPos.y)
		return tgtPos.x == pos.x;

	return isVertical(tgtPos) || isHorizontal(tgtPos) || isDiagonal(tgtPos);
}

void GoldenGeneral::draw() const
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sf::Vector2f imgDim = static_cast<sf::Vector2f>(texture.getSize());
	sprite.setOrigin({ imgDim.x / 2, imgDim.y / 2 });
	if (team == BLACK)	sprite.setRotation(180);
	sprite.setPosition((pos.x * 96) + (BOARD_X + 98), (pos.y * 96) + (BOARD_Y + 98));
	sprite.setScale({ 0.6,0.6 });
	this->B->getWinPtr()->draw(sprite);
}
void GoldenGeneral::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	sf::Sprite sprite(texture);
	sprite.setPosition(corner.x + 13, corner.y + (98 * cellNo) + 5);
	sprite.setScale(0.6, 0.6);
	this->B->getWinPtr()->draw(sprite);
}
