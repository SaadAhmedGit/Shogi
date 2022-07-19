#include "Player.h"

Player::Player(const std::string& _name, Team _team, const Prison& _prison)
	:name(_name), team(_team), prison(_prison)
{
}

Team Player::getTeam() const
{
	return this->team;
}
void Player::drawPrison()
{
	prison.draw();
}
Piece* Player::freePrisoner(int cellNo)
{
	return prison.freePrisoner(cellNo);
}
Piece* Player::peekPrisoner(int cellNo)
{
	return prison.peekPrisoner(cellNo);
}
int Player::mapToCell(Pos raw)
{
	return (raw.y - prison.corner.y) / 98;
}
sf::Vector2i Player::getPrisonCorner()
{
	return prison.corner;
}
void Player::capture(Piece* prisoner)
{
	prison.addPrisoner(prisoner);
}
std::string Player::getTeamName() const
{
	return (this->team == 0 ? "Black" : "White");
}

const std::string& Player::getName() const
{
	return this->name;
}
