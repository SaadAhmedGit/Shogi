#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>

#include "Shogi.h"
#include "Board.h"
#include "Player.h"
#include "Piece.h"
#include "Bishop.h"
#include "Lance.h"
#include "Rook.h"
#include "GoldenGeneral.h"
#include "SilverGeneral.h"
#include "King.h"
#include "Knight.h"

Pos Shogi::pickOnBoard(sf::RenderWindow& window, sf::Event& event)
{
	Pos raw = mouseL();
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

void Shogi::printText()
{
	sf::Text text;
	text.setFont(font);
	text.setString(PlayersArr[0].getName());
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(56);
	text.setPosition({ 1000, 150 });
	window.draw(text);
	text.setString(PlayersArr[1].getName());
	text.setPosition({ 1000, 225 });
	window.draw(text);
}

bool Shogi::Check()
{
	Pos kPos = B->findKing(PlayersArr[!turn].getTeam());

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((*B)[{i, j}] != nullptr &&
				(*B)[{i, j}]->getTeam() == PlayersArr[turn].getTeam()
				&& (*B)[{i, j}]->isValidMove(kPos))
			{
				return true;
			}
		}
	}
	return false;
}

bool Shogi::selfCheck()
{
	turn = !turn;
	bool doesEnemyCheck = Check();
	turn = !turn;
	return doesEnemyCheck;
}

bool Shogi::checkMate()
{
	bool amIStuck = true;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((*B)[{i, j}] != nullptr &&
				(*B)[{i, j}]->getTeam() == PlayersArr[turn].getTeam())
			{
				auto legalMap = (*B)[{i, j}]->getValidMoves();
				for (int k = 0; k < 9; k++)
				{
					for (int l = 0; l < 9; l++)
					{
						if (legalMap[k][l])
						{
							auto tmp = (*B)[{k, l}];
							B->movePiece({ i,j }, { k, l });
							amIStuck = selfCheck();
							B->movePiece({ k,l }, { i,j });
							(*B)[{k, l}] = tmp;
							if (!amIStuck)
								return false;

						}
					}
				}

			}
		}
	}
	return amIStuck;
}

bool Shogi::prompt()
{
	sf::Sprite prompt;
	prompt.setTexture(promoTexture);
	prompt.setPosition({ 600, 340 });
	window.draw(prompt);
	window.display();

	while (true)
	{

		Pos clickPos = mouseL();
		if (clickPos.c >= 690 && clickPos.c <= 790 && clickPos.r >= 480 && clickPos.r <= 524)
			return true;
		else if (clickPos.c >= 966 && clickPos.c <= 1067 && clickPos.r >= 480 && clickPos.r <= 524)
			return false;
	}
	return false;
}

Pos Shogi::mouseL()
{
	sf::Event event;
	while (sf::Event::MouseButtonReleased && window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
		{
			sf::Vector2i posV = sf::Mouse::getPosition(window);
			return Pos{ posV.y, posV.x };
		}
	}
}

Shogi::Shogi()
	: window(sf::VideoMode(1920, 1080), "Shogi"), B(new Board{ &(this->window) }), turn(WHITE)
{
	PlayersArr.emplace_back("Zoraz", BLACK);
	PlayersArr.emplace_back("Saad", WHITE);
}

void Shogi::loadAssets()
{
	//Pawn
	Pawn::texture.loadFromFile("assets\\Pawn.png");
	Pawn::texture_p.loadFromFile("assets\\Pawn-p.png");
	//Bishop
	Bishop::texture.loadFromFile("assets\\Bishop.png");
	Bishop::texture_p.loadFromFile("assets\\Bishop-p.png");
	//Lance
	Lance::texture.loadFromFile("assets\\Lance.png");
	Lance::texture_p.loadFromFile("assets\\Lance-p.png");
	//Rook
	Rook::texture.loadFromFile("assets\\Rook.png");
	Rook::texture_p.loadFromFile("assets\\Rook-p.png");
	//GoldenGeneral
	GoldenGeneral::texture.loadFromFile("assets\\GoldenGeneral.png");
	//SilverGeneral
	SilverGeneral::texture.loadFromFile("assets\\SilverGeneral.png");
	SilverGeneral::texture_p.loadFromFile("assets\\SilverGeneral-p.png");
	//King
	King::textureW.loadFromFile("assets\\KingWhite.png");
	King::textureB.loadFromFile("assets\\KingBlack.png");
	//Knight
	Knight::texture.loadFromFile("assets\\Knight.png");
	Knight::texture_p.loadFromFile("assets\\Knight-p.png");
	//Misc
	Shogi::font.loadFromFile("assets\\fonts\\times.ttf");
	Shogi::promoTexture.loadFromFile("assets\\promo-prompt.png");
}

Shogi::~Shogi()
{
	delete B;
}

sf::Font Shogi::font;
sf::Texture Shogi::promoTexture;
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
				printText();
				window.display();
				Pos tgtPos;
				Pos srcPos;
				if (checkMate())
				{
					//TODO: Display output on window
					std::cout << "CHECKMATE\n";
					while (window.pollEvent(event))
					{

					}
				}
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
				if ((*B)[tgtPos]->isPromotable() && prompt())
					(*B)[tgtPos]->promote();
				//turn = !turn;
			} while (true);
		}
	}
}