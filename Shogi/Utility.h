#pragma once
#include <SFML/Graphics.hpp>

#define BOARD_X 476
#define BOARD_Y 0

const enum Team { BLACK = 1, WHITE = 0 };
struct Pos
{
	int y, x;
	Pos() :y(0), x(0) {}
	Pos(int _y, int _x) :y(_y), x(_x) {}
};