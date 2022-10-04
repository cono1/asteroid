#pragma once
#include <raylib.h>

struct Bullet
{
	Vector2 pos;
	Vector2 newPos;
	Vector2 dir;
	Vector2 size;
};

void initBullet();
void shoot(Vector2 &pos);