#include <ctime>
#include <iostream>
#include "game.h"
#include "asteroids.h"
#include "ship.h"

Asteroid bigAsteroid;
Asteroid mediumAsteroid;
Asteroid smallAsteroid;
extern SpaceShip ship;

void initAsteroids()
{
	SetRandomSeed(time(NULL));
	bigAsteroid.amount = GetRandomValue(0, maxAsteroids);
	bigAsteroid.texture = LoadTexture("Assets/while(true).png");
	bigAsteroid.scale = 0.15;
	bigAsteroid.rotation = 0;

	do
	{
		bigAsteroid.pos.x = screenWidth; //GetRandomValue(0, screenWidth);
		bigAsteroid.pos.y = screenHeight;//GetRandomValue(0, screenHeight);
	} while (bigAsteroid.pos.x == ship.pos.x || bigAsteroid.pos.y == ship.pos.y);
	do
	{
		bigAsteroid.dir.x = GetRandomValue(-100, 100);
		bigAsteroid.dir.y = GetRandomValue(-100, 100);
	} while (bigAsteroid.dir.x < 50 && bigAsteroid.dir.x > -50 && bigAsteroid.dir.x < 50 && bigAsteroid.dir.x > -50);
	
	bigAsteroid.newPos.x = bigAsteroid.pos.x;
	bigAsteroid.newPos.y = bigAsteroid.pos.y;


	mediumAsteroid.texture = LoadTexture("Assets/onion.png");
	smallAsteroid.texture = LoadTexture("Assets/cap.png");

}

void generateAsteroids()
{
	//std::cout << " pos x " << bigAsteroid.pos.x;


}

void drawAsteroids()
{
	bigAsteroid.newPos.x = bigAsteroid.pos.x + bigAsteroid.dir.x * GetFrameTime();//moveAsteroids
	bigAsteroid.newPos.y = bigAsteroid.pos.y + bigAsteroid.dir.y * GetFrameTime();//moveAsteroids
	if (bigAsteroid.newPos.x > screenWidth)
	{
		bigAsteroid.newPos.x = 0;
	}
	if (bigAsteroid.newPos.x < 0)
	{
		bigAsteroid.newPos.x = screenWidth;
	}

	if (bigAsteroid.newPos.y > screenHeight)
	{
		bigAsteroid.newPos.y = 0;
	}
	if (bigAsteroid.newPos.y < 0)
	{
		bigAsteroid.newPos.y = screenHeight;
	}
	bigAsteroid.rotation += 0.05;
	bigAsteroid.pos.x = bigAsteroid.newPos.x;
	bigAsteroid.pos.y = bigAsteroid.newPos.y;
	DrawTextureEx(bigAsteroid.texture, bigAsteroid.pos, bigAsteroid.rotation, bigAsteroid.scale, RAYWHITE);
}

void moveAsteoids()
{
	/*bigAsteroid.newPos.x = bigAsteroid.pos.x + bigAsteroid.dir.x * GetFrameTime();
	bigAsteroid.newPos.y = bigAsteroid.pos.y + bigAsteroid.dir.y * GetFrameTime();*/
}