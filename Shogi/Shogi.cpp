#include <iostream>
#include <conio.h>
#include <SFML/Graphics.hpp>

#include "Shogi.h"
#include "Board.h"
#include "Player.h"

#include "Pieces/headers/Piece.h"
#include "Pieces/headers/Bishop.h"
#include "Pieces/headers/Lance.h"
#include "Pieces/headers/Rook.h"
#include "Pieces/headers/GoldenGeneral.h"
#include "Pieces/headers/SilverGeneral.h"
#include "Pieces/headers/King.h"
#include "Pieces/headers/Knight.h"

Pos Shogi::mapToBoard(Pos raw)
{
	Pos transformed = raw;
	transformed.x -= (BOARD_X + 48);
	transformed.y -= (BOARD_Y + 48);
	transformed.x /= 96;
	transformed.y /= 96;
	return transformed;
}

bool Shogi::isValidSelect(Pos tgt) const
{
	if (tgt.y < 0 || tgt.y > 8
		||
		tgt.x < 0 || tgt.x > 8)
		return false;
	auto tgtPtr = (*B)[tgt];
	return tgtPtr != nullptr && (tgtPtr->getTeam() == PlayersArr[turn].getTeam());
}

bool Shogi::isValidDest(Pos tgt) const
{
	if (tgt.y < 0 || tgt.y > 8
		||
		tgt.x < 0 || tgt.x > 8)
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
		if (clickPos.x >= 690 && clickPos.x <= 790 && clickPos.y >= 480 && clickPos.y <= 524)
			return true;
		else if (clickPos.x >= 966 && clickPos.x <= 1067 && clickPos.y >= 480 && clickPos.y <= 524)
			return false;
	}
	return false;
}

bool Shogi::liesInPrison(Pos raw)
{
	auto start = PlayersArr[turn].getPrisonCorner();
	return (raw.x >= start.x && raw.x <= start.x + 98) && (raw.y >= start.y && raw.y <= start.y + (7 * 98));
}

Pos Shogi::mouseL()
{
	sf::Event event;
	Pos raw{ -1,-1 };
	while (window.pollEvent(event) || (raw.x == -1 && raw.y == -1))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					sf::Vector2i posV = sf::Mouse::getPosition(window);
					raw.y = posV.y;
					raw.x = posV.x;
					return raw;
				}
				break;
			default:
				break;
		}
	}
}

void Shogi::drawBackground()
{
	sf::Sprite background;
	background.setTexture(bgTexture);
	background.setPosition({ 0, 0 });
	window.draw(background);
}

std::vector<std::vector<bool>> Shogi::computeDropZones(Piece* prisoner)
{
	std::vector<std::vector<bool>> dropZones(9, std::vector<bool>(9, 0));
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if ((*B)[{i, j}] != nullptr) continue;
			prisoner->move({ i,j });
			auto legalMap = prisoner->getValidMoves();
			bool didBreak = false;
			for (const auto& r : legalMap)
			{
				for (const auto& c : r)
				{
					if (c == 1)
					{
						dropZones[i][j] = 1;
						didBreak = true;
						break;
					}
				}
				if (didBreak) break;
			}

		}
	}
	bool isPawn = dynamic_cast<Pawn*>(prisoner);
	if (isPawn)
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if ((*B)[{i, j}] != nullptr) continue;
				prisoner->move({ i,j });
				(*B)[{i, j}] = prisoner;
				if (checkMate())
					dropZones[i][j] = 0;
				(*B)[{i, j}] = nullptr;

			}
		}
	return dropZones;
}

void Shogi::highlightForDrop(std::vector<std::vector<bool>>& dropZones)
{
	sf::Sprite greenSprite(Board::green_h);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (dropZones[i][j])
			{
				greenSprite.setPosition((j * 96) + (BOARD_X + 56), (i * 96) + (BOARD_Y + 56));
				window.draw(greenSprite);
			}
		}
	}
}

Shogi::Shogi()
	: window(sf::VideoMode(1920, 1080), "Shogi", sf::Style::Titlebar), B(new Board{ &(this->window) }), turn(WHITE)
{
	window.setPosition({ -10,0 });
	Player p1("Saad", WHITE,
			  {
				  {(BOARD_X + 968) + 100, 240},
				  &window
			  });
	Player p2("Zoraz", BLACK,
			  {
				  {BOARD_X - (100 + 98), 240},
				  &window
			  });
	PlayersArr.push_back(p1);
	PlayersArr.push_back(p2);
}

void Shogi::loadAssets()
{
	//Pawn
	Pawn::texture.loadFromFile("assets/Pawn.png");
	Pawn::texture_p.loadFromFile("assets/Pawn-p.png");
	//Bishop
	Bishop::texture.loadFromFile("assets/Bishop.png");
	Bishop::texture_p.loadFromFile("assets/Bishop-p.png");
	//Lance
	Lance::texture.loadFromFile("assets/Lance.png");
	Lance::texture_p.loadFromFile("assets/Lance-p.png");
	//Rook
	Rook::texture.loadFromFile("assets/Rook.png");
	Rook::texture_p.loadFromFile("assets/Rook-p.png");
	//GoldenGeneral
	GoldenGeneral::texture.loadFromFile("assets/GoldenGeneral.png");
	//SilverGeneral
	SilverGeneral::texture.loadFromFile("assets/SilverGeneral.png");
	SilverGeneral::texture_p.loadFromFile("assets/SilverGeneral-p.png");
	//King
	King::textureW.loadFromFile("assets/KingWhite.png");
	King::textureB.loadFromFile("assets/KingBlack.png");
	//Knight
	Knight::texture.loadFromFile("assets/Knight.png");
	Knight::texture_p.loadFromFile("assets/Knight-p.png");
	//Misc
	Shogi::font.loadFromFile("assets/fonts/times.ttf");
	Shogi::promoTexture.loadFromFile("assets/promo-prompt.png");
	Prison::texture.loadFromFile("assets/prison.png");
	Board::green_h.loadFromFile("assets/green-h.png");
	Board::red_h.loadFromFile("assets/red-h.png");
	Board::boardTexture.loadFromFile("assets/board.png");
	Shogi::bgTexture.loadFromFile("assets/w-background.jpg");
}

Shogi::~Shogi()
{
	delete B;
}

sf::Font Shogi::font;
sf::Texture Shogi::promoTexture;
sf::Texture Shogi::bgTexture;
void Shogi::play()
{
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	//PlayersArr[0].capture(new Bishop({ 8, 8 }, WHITE, B));
	//sf::Sprite board(boardTexture);

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
				drawBackground();
				B->printBoard();
				//printText();
				for (auto& i : PlayersArr) i.drawPrison();
				window.display();
				Pos tgtPos;
				Pos srcPos;
				Pos raw;
				if (checkMate())
				{
					//TODO: Display output on window
					std::cout << "CHECKMATE\n";
					while (window.pollEvent(event))
					{

					}
				}
				int cellNo = -1;
				do
				{
					raw = mouseL();
					if (liesInPrison(raw))
					{
						cellNo = PlayersArr[turn].mapToCell(raw);
						auto prisoner = PlayersArr[turn].peekPrisoner(cellNo);
						if (prisoner != nullptr) break;
					}
					srcPos = mapToBoard(raw);

				} while (!isValidSelect(srcPos));
				drawBackground();
				for (auto& i : PlayersArr) i.drawPrison();
				B->printBoard();
				if (cellNo > -1)
				{
					auto dropZones = computeDropZones(PlayersArr[turn].peekPrisoner(cellNo));
					highlightForDrop(dropZones);
				}
				else
					B->highLightMoves(srcPos);
				//printText();
				window.display();
				do
				{
					raw = mouseL();
					tgtPos = mapToBoard(raw);
					if (cellNo > -1)
					{
						if (isValidDest(tgtPos))
						{
							//Drop according to legality criteria
							Piece* droppedPiece = PlayersArr[turn].freePrisoner(cellNo);
							droppedPiece->move(tgtPos);
							(*B)[{tgtPos}] = droppedPiece;
							droppedPiece->setTeam(PlayersArr[turn].getTeam());
							break;
						}
						else
							continue;
					}

				} while (!isValidDest(tgtPos) || !(*B)[srcPos]->isValidMove(tgtPos));
				if (cellNo < 0)
				{
					if ((*B)[{tgtPos}] != nullptr)
						PlayersArr[turn].capture((*B)[{tgtPos}]);
					B->movePiece(srcPos, tgtPos);
					if ((*B)[tgtPos]->isPromotable() && prompt())
						(*B)[tgtPos]->promote();
				}
				//turn = !turn;
			} while (true);
		}
	}
}