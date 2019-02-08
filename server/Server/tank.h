#pragma once

#include <SFML/Graphics.hpp>

class Bullet;

enum RouteObject {
	Up = 100,
	Down = 101,
	Left = 102,
	Right = 103,
	Space = 104
};

class Tank{
	public:
		int HP;
		sf::Vector2<float> point;
		std::vector<Bullet> bullets;
		RouteObject turn;
		int team;

		Tank (int health = 0, float x = 0, float y = 0, RouteObject turn = RouteObject::Up, int team = 0): 
			HP(health), 
			point(x, y),
			turn(turn),
			team(team)
		{}
};

class Bullet {
	public:
		sf::Vector2<float> point;
		RouteObject turn;
		int team;

		Bullet (float x, float y, RouteObject turn, int team):
			point(x, y),
			turn(turn),
			team(team)
		{ }
};