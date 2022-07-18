#pragma once
#include <SFML/Graphics.hpp>

#define BOARD_X 476
#define BOARD_Y 0

const enum Color { BLACK = 0, WHITE = 15 };
struct Pos
{
	int r, c;
	Pos() :r(0), c(0) {}
	Pos(int _r, int _c) :r(_r), c(_c) {}
};