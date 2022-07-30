#include "Prison.h"

#include "Pieces/headers/Pawn.h"
#include "Pieces/headers/Rook.h"
#include "Pieces/headers/Knight.h"
#include "Pieces/headers/Lance.h"
#include "Pieces/headers/Bishop.h"
#include "Pieces/headers/GoldenGeneral.h"
#include "Pieces/headers/SilverGeneral.h"

sf::Texture Prison::texture;

Prison::Prison(sf::Vector2i _corner, sf::RenderWindow* _winPtr)
	:count(), cells(), corner(_corner), winPtr(_winPtr)
{
}

void Prison::addPrisoner(Piece* prisoner)
{
	int cellNo = 0;
	if (dynamic_cast<Pawn*> (prisoner))
		cellNo = 0;
	else if (dynamic_cast<Lance*> (prisoner))
		cellNo = 1;
	else if (dynamic_cast<Knight*> (prisoner))
		cellNo = 2;
	else if (dynamic_cast<GoldenGeneral*> (prisoner))
		cellNo = 3;
	else if (dynamic_cast<SilverGeneral*> (prisoner))
		cellNo = 4;
	else if (dynamic_cast<Bishop*> (prisoner))
		cellNo = 5;
	else if (dynamic_cast<Rook*> (prisoner))
		cellNo = 6;
	else
		return;

	if (cells[cellNo] == nullptr)
		cells[cellNo] = prisoner;
	count[cellNo]++;

}

Piece* Prison::freePrisoner(const int cellNo)
{
	//Can reduce the boiler-plate code here but just want to have it working for now
	if (count[cellNo] > 0)
		count[cellNo]--;
	else
		return nullptr;

	if (dynamic_cast<Pawn*> (cells[cellNo]))
	{
		auto cpy = new Pawn{ *(dynamic_cast<Pawn*> (cells[cellNo])) };
		if (count[cellNo] == 0)
			cells[cellNo] = nullptr;
		return cpy;
	}
	else if (dynamic_cast<Lance*> (cells[cellNo]))
	{
		auto cpy = new Lance{ *(dynamic_cast<Lance*> (cells[cellNo])) };
		if (count[cellNo] == 0)
			cells[cellNo] = nullptr;
		return cpy;
	}
	else if (dynamic_cast<Knight*> (cells[cellNo]))
	{
		auto cpy = new Knight{ *(dynamic_cast<Knight*> (cells[cellNo])) };
		if (count[cellNo] == 0)
			cells[cellNo] = nullptr;
		return cpy;
	}
	else if (dynamic_cast<GoldenGeneral*> (cells[cellNo]))
	{
		auto cpy = new GoldenGeneral{ *(dynamic_cast<GoldenGeneral*> (cells[cellNo])) };
		if (count[cellNo] == 0)
			cells[cellNo] = nullptr;
		return cpy;
	}
	else if (dynamic_cast<SilverGeneral*> (cells[cellNo]))
	{
		auto cpy = new SilverGeneral{ *(dynamic_cast<SilverGeneral*> (cells[cellNo])) };
		if (count[cellNo] == 0)
			cells[cellNo] = nullptr;
		return cpy;
	}
	else if (dynamic_cast<Bishop*> (cells[cellNo]))
	{
		auto cpy = new Bishop{ *(dynamic_cast<Bishop*> (cells[cellNo])) };
		if (count[cellNo] == 0)
			cells[cellNo] = nullptr;
		return cpy;
	}
	else if (dynamic_cast<Rook*> (cells[cellNo]))
	{
		auto cpy = new Rook{ *(dynamic_cast<Rook*> (cells[cellNo])) };
		if (count[cellNo] == 0)
			cells[cellNo] = nullptr;
		return cpy;
	}
	else
		return nullptr;
}

Piece* Prison::peekPrisoner(const int cellNo)
{
	return cells[cellNo];
}

void Prison::load(std::ifstream& prisonFile, Board* B)
{
	int curr_count = 0;
	for (int i = 0; i < 7; i++)
	{
		prisonFile >> curr_count;
		if (i == 0)
		{
			if (curr_count > 0)
			{
				cells[i] = new Pawn{ {}, WHITE,  B };
				count[i] = curr_count;
			}
		}
		else if (i == 1)
		{
			if (curr_count > 0)
			{
				cells[i] = new Lance{ {}, WHITE,  B };
				count[i] = curr_count;
			}
		}
		else if (i == 2)
		{
			if (curr_count > 0)
			{
				cells[i] = new Knight{ {}, WHITE,  B };
				count[i] = curr_count;
			}
		}
		else if (i == 3)
		{
			if (curr_count > 0)
			{
				cells[i] = new GoldenGeneral{ {}, WHITE,  B };
				count[i] = curr_count;
			}
		}
		else if (i == 4)
		{
			if (curr_count > 0)
			{
				cells[i] = new SilverGeneral{ {}, WHITE, B };
				count[i] = curr_count;
			}
		}
		else if (i == 5)
		{
			if (curr_count > 0)
			{
				cells[i] = new Bishop{ {}, WHITE,  B };
				count[i] = curr_count;
			}
		}
		else if (i == 6)
		{
			if (curr_count > 0)
			{
				cells[i] = new Rook{ {}, WHITE,  B };
				count[i] = curr_count;
			}
		}
	}
}

int Prison::getCountOf(const int cellNo)
{
	return count[cellNo];
}

void Prison::draw()
{
	sf::Sprite prisonSprite(texture);
	prisonSprite.setPosition(static_cast<sf::Vector2f>(corner));
	sf::Font timeNewRoman;
	timeNewRoman.loadFromFile("assets/fonts/digital-7.ttf");
	sf::Text countText;
	countText.setCharacterSize(32);
	countText.setFillColor(sf::Color::Red);
	countText.setFont(timeNewRoman);
	winPtr->draw(prisonSprite);
	for (int i = 0; i < 7; i++)
	{
		countText.setString(std::to_string(count[i]));
		countText.setPosition(corner.x + 120, corner.y + (98 * i) + 25);
		winPtr->draw(countText);

		if (cells[i] != nullptr)
			cells[i]->drawInPrison(corner, i);
	}
}
