#include <iostream>

#include "Shogi.h"
#include "Board.h"
#include "Player.h"
#include "Piece.h"

Pos Shogi::pickOnBoard() const
{
	return mouseL();
}

bool Shogi::isValidSelect(Pos tgt) const
{
	if (tgt.r < 0 || tgt.r > 8
		||
		tgt.c < 0 || tgt.c > 8)
		return false;
	auto tgtPtr = (*B)[tgt.r][tgt.c];
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
	: B(new Board{}), turn(bool(WHITE))
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
	do
	{
		B->printBoard();
		std::cout << PlayersArr[turn].getName() << "'s Turn (" << PlayersArr[turn].getTeamName() << ")" << std::endl;
		Pos tgtPos{};
		Pos srcPos{};
		do
		{
			std::cout << "Select a piece (r,c): ";
			srcPos = pickOnBoard();

		} while (!isValidSelect(srcPos));
		do
		{
			std::cout << "Select the destination (r,c): ";
			tgtPos = pickOnBoard();

		} while (!isValidDest(tgtPos));
		(*B)[srcPos.r][srcPos.c]->move(tgtPos);
		(*B)[tgtPos.r][tgtPos.c] = (*B)[srcPos.r][srcPos.c];
		(*B)[srcPos.r][srcPos.c] = nullptr;
		turn = !turn;
	} while (true);
}
