#pragma once
#include "raylib.h"

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
void unloadTextures();
void drawAsteroids();
void checkAsteroidToShipCollisions();
void checkAsteroidToBulletCollision();
void divideAsteroids();