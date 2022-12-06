#pragma once
#include "raylib.h"
#include "raymath.h"

#include "asteroids.h"

struct Bullet
{
	Vector2 pos;
	Vector2 dir;
	Vector2 size;
	Vector2 closestPointToAsteroid[maxAsteroids];
	float speed;
	bool isAlive;
};

void initBullet();
void shoot();