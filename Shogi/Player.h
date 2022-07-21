#pragma once
#include <string>

#include "Utility.h"
#include "Prison.h"
#include "Board.h"

class Player
{
private:
	const std::string name;
	const Team team;
	Prison prison;
	Board* B;

public:
	Player(const std::string& _name, Team _team, const Prison& _prison, Board* _B);
	Team getTeam() const;
	void drawPrison();
	int computeScore();
	Piece* freePrisoner(int cellNo);
	Piece* peekPrisoner(int cellNo);
	int mapToCell(Pos raw);
	sf::Vector2i getPrisonCorner();
	void capture(Piece* prisoner);
	std::string getTeamName() const;
	const std::string& getName() const;
};