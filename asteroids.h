#pragma once
#include <raylib.h>

const int maxAsteroids = 5;

struct Asteroid
{
	Texture2D texture;
	Vector2 pos;
	Vector2 newPos;
	Vector2 dir;
	float scale;
	int amount;
	float rotation;
};

void initAsteroids();
void drawAsteroids();
void moveAsteroids();
void checkCollisions();