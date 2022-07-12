#include "Player.h"

Player::Player(const std::string& _name, Color _team)
	:name(_name), team(_team)
{
}

Color Player::getTeam() const
{
	return this->team;
}
std::string Player::getTeamName() const
{
	return (this->team == 0 ? "Black" : "White");
}
const std::string& Player::getName() const
{
	return this->name;
}
