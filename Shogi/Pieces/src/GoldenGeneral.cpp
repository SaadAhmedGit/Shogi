#include "../headers/GoldenGeneral.h"
#include "../../Board.h"

sf::Texture GoldenGeneral::texture;
GoldenGeneral::GoldenGeneral(Pos _pos, Color _team, Board* _B)
	:Piece(_pos, _team, _B)
{
}

bool GoldenGeneral::isPromotable() const
{
	return false;
}

bool GoldenGeneral::isValidMove(Pos tgtPos) const
{
	if (abs(tgtPos.r - pos.r) > 1
		|| abs(tgtPos.c - pos.c) > 1)
		return false;

	if (team == WHITE && pos.r < tgtPos.r)
		return tgtPos.c == pos.c;

	else if (team == BLACK && pos.r > tgtPos.r)
		return tgtPos.c == pos.c;

	return isVertical(tgtPos) || isHorizontal(tgtPos) || isDiagonal(tgtPos);
}

void GoldenGeneral::draw() const
{
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sf::Vector2f imgDim = static_cast<sf::Vector2f>(texture.getSize());
	sprite.setOrigin({ imgDim.x / 2, imgDim.y / 2 });
	if (team == BLACK)	sprite.setRotation(180);
	sprite.setPosition((pos.c * 96) + (BOARD_X + 98), (pos.r * 96) + (BOARD_Y + 98));
	sprite.setScale({ 0.4,0.4 });
	this->B->getWinPtr()->draw(sprite);
}
void GoldenGeneral::drawInPrison(sf::Vector2i corner, const int cellNo) const
{
	sf::Sprite sprite(texture);
	sprite.setPosition(corner.x + 98, corner.y + (98 * cellNo));
	sprite.setScale(0.4, 0.4);
	this->B->getWinPtr()->draw(sprite);
}
