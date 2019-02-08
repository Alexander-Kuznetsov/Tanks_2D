#include "logic.h"

int CheckCollision(Tank tank, Map MymMap, float move_x, float move_y) {
	Network &network = Network::Instance();
	sf::IntRect position_tank((int)(tank.point.x + move_x + 16), (int)(tank.point.y + move_y + 16), 32, 32);
	for (unsigned i = 0; i < MymMap.HEIGHT; i++) {
		for (unsigned j = 0; j < MymMap.WIDTH; j++) {
			if (MymMap.map[i][j] == '@' || MymMap.map[j][i] == '1') {
				sf::IntRect stone(32 + 32 * i, 64 + 32 * j, 32, 32);
				if (position_tank.intersects(stone) == true)
					return -1;
			}
		}
	}
	for (unsigned i = 0; i < network.tanks.size(); i++) {
		if (network.tanks[i].point.x  == tank.point.x && network.tanks[i].point.y  == tank.point.y)
			continue;
		sf::IntRect enemy((int) (network.tanks[i].point.x + 16), (int)(network.tanks[i].point.y + 16), 32, 32);
		if (position_tank.intersects(enemy) == true) 
			return -1;
	}
	return 0;
}

void MoveTank(Tank &tank, int route, float move, Map MyMap) {
	if (tank.turn != route) {
		tank.turn = (RouteObject) route;
		return;
	}

	switch (route) {
		case RouteObject::Up:
			//std::cout << "Up" << std::endl;
			if (CheckCollision(tank, MyMap, 0, -move) == -1)
				return;
	
			tank.point.y -= move;
			break;
		case RouteObject::Down:
			//std::cout << "Down" << std::endl;
			if (CheckCollision(tank, MyMap, 0, move) == -1)
				return;
			tank.point.y += move;
			break;
		case RouteObject::Left:
			//std::cout << "Left" << std::endl;
			if (CheckCollision(tank, MyMap, -move, 0) == -1)
				return;
			tank.point.x -= move;
			break;
		case RouteObject::Right:
			//std::cout << "Right" << std::endl;
			if (CheckCollision(tank, MyMap, move, 0) == -1)
				return;
			tank.point.x += move;
			break; 
		default:		 
			break;
	}
}

void MoveBullet(Bullet &bullet, float move) {
	switch (bullet.turn) {
		case RouteObject::Up:
			bullet.point.y -= move;
			break;
		case RouteObject::Down:
			bullet.point.y += move;
			break;
		case RouteObject::Left:
			bullet.point.x -= move;
			break;
		case RouteObject::Right:
			bullet.point.x += move;
			break;
		default:		 
			break;
	}
}

void MoveBullets(std::vector<Bullet> &bullets, float move) {
	for (unsigned i = 0; i < bullets.size(); i++) {
		MoveBullet(bullets[i], move);
	}
}

