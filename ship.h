#pragma once
#include "asteroids.h"

struct SpaceShip
{
	Vector2 pos;
	Vector2 newPos;
	Vector2 closestPointToAsteroid[maxAsteroids];
	Vector2 pivot;
	Vector2 dir;
	Vector2 acceleration;
	float rotation;
	bool isAlive;
};

void loadTexture();
void initShip();
void drawShip();
void rotateShip();
void moveShip();
