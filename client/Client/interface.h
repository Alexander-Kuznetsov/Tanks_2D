#pragma once

#include <SFML\Graphics.hpp>
#include "fonts.h"

class Interfaces{
	public:
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		Fonts fonts;

		Interfaces() {
			image.loadFromFile("../Data/Images/interface.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}

		void DrawInterface(sf::RenderWindow &window, unsigned width_map, int HP) {
			for (int i = 0; i < width_map; i++){
				if (i == 0)
					sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
				else if (i == width_map - 1)
					sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
				else
					sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
				sprite.setPosition(i * 32, 0);
				window.draw(sprite);
			}
			fonts.text.setString("HP: " + std::to_string(HP));
			fonts.text.setPosition(10, 5);
			window.draw(fonts.text);
		}
};
