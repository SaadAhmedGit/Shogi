#include "Utility.h"

#include <Windows.h>
#include <SFML/Graphics.hpp>
Pos mouseL(sf::RenderWindow& window, sf::Event& event)
{
	/*HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	Pos mPos;
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			mPos.r = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			mPos.c = InputRecord.Event.MouseEvent.dwMousePosition.X;
			return mPos;
		}
	} while (true);*/
	while (true)
	{
		window.pollEvent(event);
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::MouseButtonPressed)
		{
			sf::Vector2i posV = sf::Mouse::getPosition(window);
			return Pos { posV.y, posV.x };
		}
	}
}