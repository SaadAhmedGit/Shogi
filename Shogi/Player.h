#pragma once
#include <string>

#include "Utility.h"

class Player
{
private:
	const std::string name;
	const Color team;
public:
	Player(const std::string& _name, Color _team);
	Color getTeam() const;
	std::string getTeamName() const;
	const std::string& getName() const;
};