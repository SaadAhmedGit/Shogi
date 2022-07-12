#pragma once
#include <SFML/Graphics.hpp>
const enum Color { BLACK = 0, WHITE = 15 };

struct Pos {
	int r, c;
	Pos():r(0),c(0){}
	Pos(int _r, int _c) :r(_r), c(_c) {}
};

//Mouse
Pos mouseL(sf::RenderWindow& window, sf::Event& event);