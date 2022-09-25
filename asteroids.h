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
	Vector2 asteroids[maxAsteroids];
	int amount;
	float rotation;
};

void initAsteroids();
void generateAsteroids();
void drawAsteroids();
void moveAsteoids();