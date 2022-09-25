#include <ctime>
#include "game.h"
#include "asteroids.h"

Asteroid bigAsteroid;
Asteroid mediumAsteroid;
Asteroid smallAsteroid;

void initAsteroids()
{
	bigAsteroid.texture = LoadTexture("Assets/while(true).png");
	bigAsteroid.pos.x = 450;
	bigAsteroid.pos.y = 500;
	bigAsteroid.dir.x = 0;
	bigAsteroid.dir.y = 0;
	bigAsteroid.scale = 0.15;
	bigAsteroid.rotation = 0;

	mediumAsteroid.texture = LoadTexture("Assets/onion.png");
	smallAsteroid.texture = LoadTexture("Assets/cap.png");
}

void generateAsteroids()
{
	SetRandomSeed(time(NULL));
	bigAsteroid.amount = GetRandomValue(0, maxAsteroids);
	/*bigAsteroid.pos.x = GetRandomValue(0, screenHeight);
	bigAsteroid.pos.y = GetRandomValue(0, screenWidth);*/


	for (int i = 0; i < bigAsteroid.amount; i++)
	{
		bigAsteroid.asteroids[i] = bigAsteroid.pos;
	}
}

void drawAsteroids()
{
	bigAsteroid.rotation += 0.02;
	//for con todos los asteroides
	DrawTextureEx(bigAsteroid.texture, bigAsteroid.pos, bigAsteroid.rotation, bigAsteroid.scale, RAYWHITE);
}