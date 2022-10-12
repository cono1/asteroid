#pragma once
#include <raylib.h>

const int maxAsteroids = 2;

struct Asteroid
{
	Texture2D texture;
	Vector2 pos;
	Vector2 newPos;
	Vector2 dir;
	float scale;
	float rotation;
	bool isAlive;
};

void initAsteroids();
void drawAsteroids();
void checkAsteroidToShipCollisions(Vector2& pos, Rectangle& collisionBoxShip, Vector2& dir);
void checkAsteroidToBulletCollision();
void divideAsteroids();