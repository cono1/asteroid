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
	int lives;
	float rotation;
	bool isAlive;
	bool collide;
};

void loadTexture();
void unloadTexture();
void initShip();
void restartShipPos();
void drawShip();
void rotateShip();
void moveShip();
