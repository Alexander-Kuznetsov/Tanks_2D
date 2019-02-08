#pragma once

#include <iostream>

#include "tank.h"
#include "map.h"
#include "network.h"

void MoveTank(Tank &tank, int route, float move, Map MyMap);
//void MoveTank(Tank &tank, int route, float move);

void MoveBullet(Bullet &bullet, float move);

void MoveBullets(std::vector<Bullet> &bullets, float move);

int CheckCollision(Tank tank, Map MymMap, float move, float move_y);