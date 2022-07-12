#include <iostream>
#include <fstream>

#include "Board.h"
#include "Pawn.h"
#include "Bishop.h"

Board::Board()
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
				case 'r':
					piecesArr[i].push_back(new Pawn({ i, j }, team, this));
					break;
				case 'g':
					piecesArr[i].push_back(new Pawn({ i, j }, team, this));
					break;
				case 's':
					piecesArr[i].push_back(new Pawn({ i, j }, team, this));
					break;
				case 'k':
					piecesArr[i].push_back(new Pawn({ i, j }, team, this));
					break;
				case 'h':
					piecesArr[i].push_back(new Pawn({ i, j }, team, this));
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

void Board::movePiece(const Pos src, const Pos dest)
{
	(*this)[src]->move(dest);
	(*this)[dest] = (*this)[src];
	(*this)[src] = nullptr;
}

void Board::printBoard()
{
	system("cls");
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (piecesArr[i][j] == nullptr)
				std::cout << "-";
			else
				piecesArr[i][j]->draw();
		}
		std::cout << std::endl;
	}
}

Piece*& Board::operator[](const Pos p)
{
	return piecesArr[p.r][p.c];
}
