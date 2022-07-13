#include <iostream>
#include <SFML/Graphics.hpp>

#include "Shogi.h"
#include "Board.h"
#include "Player.h"
#include "Piece.h"
#include "Bishop.h"
#include "Lance.h"
#include "Rook.h"
#include "GoldenGeneral.h"

Pos Shogi::pickOnBoard(sf::RenderWindow& window, sf::Event& event) const
{
	Pos raw = mouseL(window, event);
	raw.r -= 52;
	raw.c -= 51;
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

void Shogi::loadAssets()
{
	Pawn::texture.loadFromFile("assets\\Pawn.png");
	Bishop::texture.loadFromFile("assets\\Bishop.png");
	Lance::texture.loadFromFile("assets\\Lance.png");
	Rook::texture.loadFromFile("assets\\Rook.png");
	GoldenGeneral::texture.loadFromFile("assets\\GoldenGeneral.png");
}

Shogi::~Shogi()
{
	delete B;
}

void Shogi::play()
{
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("assets\\w-background.jpg");
	sf::Sprite background(backgroundTexture);

	sf::Texture boardTexture;
	boardTexture.loadFromFile("assets\\board.png");
	sf::Sprite board(boardTexture);

	window.draw(background);
	window.draw(board);
	window.display();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				exit(0);
			}
			do
			{
				B->printBoard();
				window.display();
				Pos tgtPos;
				Pos srcPos;
				do
				{
					srcPos = pickOnBoard(window, event);

				} while (!isValidSelect(srcPos));
				B->printBoard();
				B->highLightMoves(srcPos);
				window.display();
				do
				{
					tgtPos = pickOnBoard(window, event);

				} while (!isValidDest(tgtPos) || !(*B)[srcPos]->isValidMove(tgtPos));
				B->movePiece(srcPos, tgtPos);
				turn = !turn;
			} while (true);
		}
	}
}
