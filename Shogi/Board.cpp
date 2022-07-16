#include <iostream>
#include <fstream>

#include "Board.h"
#include "Pawn.h"
#include "King.h"
#include "Bishop.h"
#include "Lance.h"
#include "Rook.h"
#include "GoldenGeneral.h"
#include "SilverGeneral.h"
#include "Knight.h"

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
			Color team = (sym >= 'a' && sym <= 'z' ? BLACK : WHITE);
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

void Board::highLightMoves(Pos srcPiece)
{
	if ((*this)[srcPiece] == nullptr) return;
	sf::Texture greenHighlight;
	sf::Texture redHighlight;
	redHighlight.loadFromFile("assets\\red-h.png");
	greenHighlight.loadFromFile("assets\\green-h.png");
	sf::Sprite greenHighlightSprite(greenHighlight);
	sf::Sprite redHighlightSprite(redHighlight);

	std::vector<std::vector<bool>> validMoves = (*this)[srcPiece]->getValidMoves();
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
						redHighlightSprite.setPosition((j * 96) + 56, (i * 96) + 56);
						winP->draw(redHighlightSprite);
						continue;
					}
				}
				greenHighlightSprite.setPosition((j * 96) + 56, (i * 96) + 56);
				winP->draw(greenHighlightSprite);
			}
		}
	}

}

void Board::printBoard()
{
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("assets\\w-background.jpg");
	sf::Sprite background(backgroundTexture);
	this->getWinPtr()->draw(background);

	sf::Texture boardTexture;
	boardTexture.loadFromFile("assets\\board.png");
	sf::Sprite board(boardTexture);
	board.setPosition(0, 0);
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

Pos Board::findKing(Color team)
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
	return piecesArr[p.r][p.c];
}