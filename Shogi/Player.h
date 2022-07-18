#pragma once
#include <string>

#include "Utility.h"
#include "Prison.h"

class Player
{
private:
	const std::string name;
	const Color team;
	Prison prison;
public:
	Player(const std::string& _name, Color _team, const Prison& _prison);
	Color getTeam() const;
	void drawPrison();
	void capture(Piece* prisoner);
	std::string getTeamName() const;
	const std::string& getName() const;
};