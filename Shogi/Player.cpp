#include "Player.h"

Player::Player(const std::string& _name, Color _team, const Prison& _prison)
	:name(_name), team(_team), prison(_prison)
{
}

Color Player::getTeam() const
{
	return this->team;
}
void Player::drawPrison()
{
	prison.draw();
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
