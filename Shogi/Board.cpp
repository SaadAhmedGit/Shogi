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

Board::Board(sf::RenderWindow* windowPtr, const std::string& boardFile)
	:winP(windowPtr), piecesArr(9, std::vector<Piece*>(9, 0))
{
	std::ifstream setupFile(boardFile + "-s.txt");
	if (!setupFile.is_open()) throw "Setup file couldn't be loaded";
	std::ifstream promotionFile(boardFile + "-p.txt");
	if (!promotionFile.is_open()) throw "Promotion file couldn't be loaded";

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			char sym = 0;
			int wasPromoted = 0;
			setupFile >> sym;
			promotionFile >> wasPromoted;
			Team team = (sym >= 'a' && sym <= 'z' ? BLACK : WHITE);
			switch (tolower(sym))
			{
				case 'p':
					piecesArr[i][j] = new Pawn({ i, j }, team, this);
					if (wasPromoted)
						piecesArr[i][j]->promote();
					break;
				case 'b':
					piecesArr[i][j] = new Bishop({ i, j }, team, this);
					if (wasPromoted)
						piecesArr[i][j]->promote();
					break;
				case 'l':
					piecesArr[i][j] = new Lance({ i, j }, team, this);
					if (wasPromoted)
						piecesArr[i][j]->promote();
					break;
				case 'r':
					piecesArr[i][j] = new Rook({ i, j }, team, this);
					if (wasPromoted)
						piecesArr[i][j]->promote();
					break;
				case 'g':
					piecesArr[i][j] = new GoldenGeneral({ i, j }, team, this);
					if (wasPromoted)
						piecesArr[i][j]->promote();
					break;
				case 's':
					piecesArr[i][j] = new SilverGeneral({ i, j }, team, this);
					if (wasPromoted)
						piecesArr[i][j]->promote();
					break;
				case 'k':
					piecesArr[i][j] = new King({ i, j }, team, this);
					break;
				case 'h':
					piecesArr[i][j] = new Knight({ i, j }, team, this);
					if (wasPromoted)
						piecesArr[i][j]->promote();
					break;
				default:
					piecesArr[i][j] = nullptr;
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
