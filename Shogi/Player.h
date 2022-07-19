#pragma once
#include <string>

#include "Utility.h"
#include "Prison.h"

class Player
{
private:
	const std::string name;
	const Team team;
	Prison prison;
public:
	Player(const std::string& _name, Team _team, const Prison& _prison);
	Team getTeam() const;
	void drawPrison();
	Piece* freePrisoner(int cellNo);
	Piece* peekPrisoner(int cellNo);
	int mapToCell(Pos raw);
	sf::Vector2i getPrisonCorner();
	void capture(Piece* prisoner);
	std::string getTeamName() const;
	const std::string& getName() const;
};