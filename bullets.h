#pragma once
#include <raylib.h>
#include <raymath.h>

struct Bullet
{
	Vector2 pos;
	Vector2 dir;
	Vector2 size;
	float speed;
	bool isAlive;
};

void initBullet();
void shoot();