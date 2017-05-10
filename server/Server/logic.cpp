#include "logic.h"

void MoveTank(Tank &tank, int route, float move) {
	if (tank.turn != route) {
		tank.turn = (RouteObject) route;
		return;
	}

	switch (route) {
		case RouteObject::Up:
			std::cout << "Up" << std::endl;
			tank.point.y -= move;
			break;
		case RouteObject::Down:
			std::cout << "Down" << std::endl;
			tank.point.y += move;
			break;
		case RouteObject::Left:
			std::cout << "Left" << std::endl;
			tank.point.x -= move;
			break;
		case RouteObject::Right:
			std::cout << "Right" << std::endl;
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