#include <iostream>

#include "Board.h"
#include "Pawn.h"

Board::Board()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			piecesArr.push_back({});
			if (i == 1)
				piecesArr[i].emplace_back(new Pawn({ i, j }, BLACK, this));
			else if (i == 7)
				piecesArr[i].emplace_back(new Pawn({ i, j }, WHITE, this));
			else
				piecesArr[i].emplace_back(nullptr);
		}
	}
}

Board::~Board()
{
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

std::vector<Piece*>& Board::operator[](int i)
{
	return piecesArr[i];
}
