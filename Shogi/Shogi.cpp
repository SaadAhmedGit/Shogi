#include <iostream>
#include <SFML/Graphics.hpp>

#include "Shogi.h"
#include "Board.h"
#include "Player.h"
#include "Piece.h"

Pos Shogi::pickOnBoard(sf::RenderWindow& window, sf::Event& event) const
{
	Pos raw = mouseL(window, event);
	raw.r -= 50;
	raw.c -= 49;
	raw.r /= 96;
	raw.c /= 96;
	return raw;
}

bool Shogi::isValidSelect(Pos tgt) const
{
	if (tgt.r < 0 || tgt.r > 8
		||
		tgt.c < 0 || tgt.c > 8)
		return false;
	auto tgtPtr = (*B)[tgt];
	return tgtPtr != nullptr && (tgtPtr->getTeam() == PlayersArr[turn].getTeam());
}

bool Shogi::isValidDest(Pos tgt) const
{
	if (tgt.r < 0 || tgt.r > 8
		||
		tgt.c < 0 || tgt.c > 8)
		return false;
	return !isValidSelect(tgt);
}

Shogi::Shogi()
	: window(sf::VideoMode(1920, 1080), "Shogi"), B(new Board{ &(this->window) }), turn(bool(WHITE))
{
	PlayersArr.emplace_back("Saad", WHITE);
	PlayersArr.emplace_back("Zoraz", BLACK);
}

Shogi::~Shogi()
{
	delete B;
}

void Shogi::play()
{
	window.setFramerateLimit(60);

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("assets\\background.png");
	sf::Sprite background(backgroundTexture);

	sf::Texture boardTexture;
	boardTexture.loadFromFile("assets\\board.png");
	sf::Sprite board(boardTexture);

	window.draw(background);
	window.draw(board);
	window.display();
	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//std::cout << "(" << p.r << ", " << p.c << ")\n";
			//window.clear();
			//window.display();
			do
			{
				B->printBoard();
				std::cout << PlayersArr[turn].getName() << "'s Turn (" << PlayersArr[turn].getTeamName() << ")" << std::endl;
				Pos tgtPos{};
				Pos srcPos{};
				do
				{
					std::cout << "Select a piece (r,c): ";
					srcPos = pickOnBoard(window, event);

				} while (!isValidSelect(srcPos));
				do
				{
					std::cout << "Select the destination (r,c): ";
					tgtPos = pickOnBoard(window, event);

				} while (!isValidDest(tgtPos) || !(*B)[srcPos]->isValidMove(tgtPos));
				B->movePiece(srcPos, tgtPos);
				turn = !turn;
			} while (true);
		}
	}
}
