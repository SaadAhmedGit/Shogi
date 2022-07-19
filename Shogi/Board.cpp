#include <iostream>
#include <fstream>

#include "Board.h"
//Pieces
#include "Pieces/headers/Pawn.h"
#include "Pieces/headers/King.h"
#include "Pieces/headers/Bishop.h"
#include "Pieces/headers/Lance.h"
#include "Pieces/headers/Rook.h"
#include "Pieces/headers/GoldenGeneral.h"
#include "Pieces/headers/SilverGeneral.h"
#include "Pieces/headers/Knight.h"

Board::Board(sf::RenderWindow* windowPtr)
	:winP(windowPtr)
{
	std::ifstream setupFile("dfltSetup.txt");
	if (!setupFile.is_open())
		throw std::exception("The dfltSetup.dat file is either corrupted or not present. Please re-install the game");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			piecesArr.push_back({});
			char sym = 0;
			setupFile >> sym;
			Team team = (sym >= 'a' && sym <= 'z' ? BLACK : WHITE);
			switch (tolower(sym))
			{
				case 'p':
					piecesArr[i].push_back(new Pawn({ i, j }, team, this));
					break;
				case 'b':
					piecesArr[i].push_back(new Bishop({ i, j }, team, this));
					break;
				case 'l':
					piecesArr[i].push_back(new Lance({ i, j }, team, this));
					break;
				case 'r':
					piecesArr[i].push_back(new Rook({ i, j }, team, this));
					break;
				case 'g':
					piecesArr[i].push_back(new GoldenGeneral({ i, j }, team, this));
					break;
				case 's':
					piecesArr[i].push_back(new SilverGeneral({ i, j }, team, this));
					break;
				case 'k':
					piecesArr[i].push_back(new King({ i, j }, team, this));
					break;
				case 'h':
					piecesArr[i].push_back(new Knight({ i, j }, team, this));
					break;
				default:
					piecesArr[i].push_back(nullptr);
			}
		}
	}
}

Board::~Board()
{
}

sf::RenderWindow* Board::getWinPtr()
{
	return this->winP;
}

void Board::movePiece(const Pos src, const Pos dest)
{
	(*this)[src]->move(dest);
	(*this)[dest] = (*this)[src];
	(*this)[src] = nullptr;
}

sf::Texture Board::green_h;
sf::Texture Board::red_h;
sf::Texture Board::boardTexture;

void Board::highLightMoves(Pos srcPiece)
{
	if ((*this)[srcPiece] == nullptr) return;
	sf::Sprite greenSprite(green_h);
	sf::Sprite redSprite(red_h);

	auto validMoves = (*this)[srcPiece]->getValidMoves();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (validMoves[i][j])
			{
				if ((*this)[{i, j}] != nullptr)
				{
					if ((*this)[{i, j}]->getTeam() != (*this)[srcPiece]->getTeam())
					{
						redSprite.setPosition((j * 96) + (BOARD_X + 56), (i * 96) + (BOARD_Y + 56));
						winP->draw(redSprite);
						continue;
					}
				}
				greenSprite.setPosition((j * 96) + (BOARD_X + 56), (i * 96) + (BOARD_Y + 56));
				winP->draw(greenSprite);
			}
		}
	}

}

void Board::printBoard()
{
	sf::Sprite board(boardTexture);
	board.setPosition(BOARD_X, BOARD_Y);
	this->getWinPtr()->draw(board);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (piecesArr[i][j] != nullptr)
				piecesArr[i][j]->draw();
		}
	}
}

Pos Board::findKing(Team team)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (dynamic_cast<King*> ((*this)[{i, j}]) && ((*this)[{i, j}]->getTeam() == team))
			{
				return (*this)[{i, j}]->getPos();
			}
		}
	}
	return Pos(-1, -1);
}

Piece*& Board::operator[](const Pos p)
{
	return piecesArr[p.y][p.x];
}