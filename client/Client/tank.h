#pragma once

#include <SFML\Graphics.hpp>

enum TurnObject {
	Up = 100,
	Down = 101,
	Left = 102,
	Right = 103,
	Space = 104
};

class Bullet {
	public:
		sf::Vector2<float> point;
		//TurnObject turn;

		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;

		Bullet::Bullet (float x, float y):
			point(x, y)
			//turn(turn)
		{ 
			image.loadFromFile("../Data/Images/bullet.png");
			texture.loadFromImage(image); 
			sprite.setTexture(texture);
			//spriteSize  = sprite.getLocalBounds();
			//size_x = spriteSize.width;
			//size_y = spriteSize.height;
			//sprite.setOrigin(spriteSize.width/2.0, spriteSize.height - spriteSize.width/2.0);
			//sprite.setScale(0.2, 0.2);
			sprite.setPosition(point.x, point.y);
		}

		void DrawBullet(sf::RenderWindow &window) {
			window.draw(sprite);
		}
};

class Tank{
	public:
		int HP;
		sf::Vector2<float> point;
		//std::vector<Bullet> bullets;
		TurnObject turn;
		
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		sf::FloatRect spriteSize;

		Tank::Tank (int health = 0, float x = 0, float y = 0, TurnObject turn = TurnObject::Up): 
			HP(health), 
			point(x, y),
			turn(turn)
		{
			image.loadFromFile("../Data/Images/tank.png");
			texture.loadFromImage(image); 
			sprite.setTexture(texture);
			spriteSize  = sprite.getLocalBounds();
			//size_x = spriteSize.width;
			//size_y = spriteSize.height;
			sprite.setOrigin(spriteSize.width/2.0, spriteSize.height/2.0);
			//sprite.setScale(0.2, 0.2);
			sprite.setPosition(point.x, point.y);
		}

		void DrawTank(sf::RenderWindow &window) {
			if(turn == Left)
				if (sprite.getRotation() != 270)
					sprite.setRotation(270);
           
			if (turn == Right) 
				if (sprite.getRotation() != 90) 
					sprite.setRotation(90);
          
			if (turn == Up) 
				if (sprite.getRotation() != 0) 
					sprite.setRotation(0);  

			if (turn == Down)
				if (sprite.getRotation() != 180)
					sprite.setRotation(180);
                
			window.draw(sprite);
		}
};