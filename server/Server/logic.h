#pragma once

#include <iostream>

#include "tank.h"

void MoveTank(Tank &tank, int route, float move);

void MoveBullet(Bullet &bullet, float move);

void MoveBullets(std::vector<Bullet> &bullets, float move);

