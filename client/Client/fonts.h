#pragma once

#include <SFML\Graphics.hpp>

class Fonts {
	public:
		sf::Font font;
		sf::Text text;

		Fonts() {
			font.loadFromFile("../Data/Fonts/CyrilicOld.ttf");
			text = sf::Text("", font, 16);
			text.setFillColor(sf::Color::Red);
			text.setStyle(sf::Text::Bold);
		}	
};