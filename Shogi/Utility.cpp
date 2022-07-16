#include "Utility.h"

#include <iostream>
#include <SFML/Graphics.hpp>
//Pos mouseL(sf::RenderWindow& window, sf::Event& event)
//{
//	while (sf::Event::MouseButtonReleased && window.pollEvent(event))
//	{
//		if (event.type == sf::Event::Closed)
//			window.close();
//		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
//		{
//			sf::Vector2i posV = sf::Mouse::getPosition(window);
//			return Pos{ posV.y, posV.x };
//		}
//	}
//}