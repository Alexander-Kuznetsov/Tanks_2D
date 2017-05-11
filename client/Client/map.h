#pragma once

#include <SFML\Graphics.hpp>

class Map {
	public:
		unsigned WIDTH;
		unsigned HEIGHT;

		std::vector<std::string> map;

		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;

		Map() {
			image.loadFromFile("../Data/Images/map.png");
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}

		void DrawMap(sf::RenderWindow &window) {
			for (unsigned i = 0; i < HEIGHT; i++){
				for (unsigned j = 0; j < WIDTH; j++){
					if (map[i][j] == '0') 
						sprite.setTextureRect(sf::IntRect(0, 0, 32, 32));
					if (map[i][j] == '1') 
						sprite.setTextureRect(sf::IntRect(32, 0, 32, 32));
					if (map[i][j] == '@') 
						sprite.setTextureRect(sf::IntRect(64, 0, 32, 32));
					sprite.setPosition(j * 32, (i + 1) * 32);
					window.draw(sprite);
				}
			}
		}
};
