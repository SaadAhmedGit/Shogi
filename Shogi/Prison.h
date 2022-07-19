#pragma once

#include <SFML/Graphics.hpp>
#include "Utility.h"

//Forward declarations
class Piece;
class Player;

class Prison
{
private:
	int count[7];
	Piece* cells[7];
	sf::RenderWindow* winPtr;

	//Graphics stuff
public:
	sf::Vector2i corner;
	Prison(sf::Vector2i _corner, sf::RenderWindow* _winPtr);
	void addPrisoner(Piece* prisoner);
	Piece* freePrisoner(const int cellNo);
	Piece* peekPrisoner(const int cellNo);
	void draw();
	static sf::Texture texture;

};