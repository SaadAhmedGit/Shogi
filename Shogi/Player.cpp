#include "Player.h"
#include "Board.h"
#include "Pieces/headers/Piece.h"

Player::Player(const std::string& _name, Team _team, const Prison& _prison, Board* _B)
	:name(_name), team(_team), prison(_prison), B(_B)
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
int Player::computeScore()
{
	int score = 0;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((*B)[{i, j}] != nullptr
				&& (*B)[{i, j}]->getTeam() == team)
			{
				score += (*B)[{i, j}]->getScore();
			}
		}
	}
	for (int i = 0; i < 7; i++)
	{
		if (prison.peekPrisoner(i) != nullptr)
			score += prison.peekPrisoner(i)->getScore() * prison.getCountOf(i);
	}
	return score;
}
void Player::loadPrison(std::ifstream& prisonFile, Board* B)
{
	prison.load(prisonFile, B);
}
Piece* Player::freePrisoner(int cellNo)
{
	return prison.freePrisoner(cellNo);
}
void Player::setBoardptr(Board* _B)
{
	B = _B;
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
	prisoner->setTeam(team);
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
