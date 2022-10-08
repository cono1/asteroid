#include <ctime>
#include <iostream>
#include "game.h"
#include "asteroids.h"
#include "ship.h"

Asteroid bigAsteroid;
Asteroid mediumAsteroid;
Asteroid smallAsteroid;
extern SpaceShip ship;
Rectangle collisionBoxAsteroid;
extern Rectangle collisionBoxShip;

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

	collisionBoxAsteroid.x = bigAsteroid.pos.x;
	collisionBoxAsteroid.y = bigAsteroid.pos.y;
	collisionBoxAsteroid.width = 120;
	collisionBoxAsteroid.height = 100;

}

void drawAsteroids()
{

	bigAsteroid.pos.x = bigAsteroid.newPos.x;
	bigAsteroid.pos.y = bigAsteroid.newPos.y;
	DrawTextureEx(bigAsteroid.texture, bigAsteroid.pos, bigAsteroid.rotation, bigAsteroid.scale, RAYWHITE);
}

void moveAsteroids()
{
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
	bigAsteroid.rotation += 0.05 * GetFrameTime();
	bigAsteroid.newPos.x = bigAsteroid.pos.x + bigAsteroid.dir.x * GetFrameTime();//moveAsteroids
	bigAsteroid.newPos.y = bigAsteroid.pos.y + bigAsteroid.dir.y * GetFrameTime();//moveAsteroids
	/*bigAsteroid.newPos.x = bigAsteroid.pos.x + bigAsteroid.dir.x * GetFrameTime();
	bigAsteroid.newPos.y = bigAsteroid.pos.y + bigAsteroid.dir.y * GetFrameTime();*/
}

void checkCollisions()
{
	collisionBoxAsteroid.x = bigAsteroid.pos.x /*+ 50*/;
	collisionBoxAsteroid.y = bigAsteroid.pos.y /*+ 50*/;
	DrawRectangleLines(collisionBoxAsteroid.x, collisionBoxAsteroid.y, collisionBoxAsteroid.width, collisionBoxAsteroid.height, YELLOW);


	ship.closestPointToAsteroid.x = collisionBoxShip.x;
	if (ship.closestPointToAsteroid.x < collisionBoxAsteroid.x + collisionBoxAsteroid.width)
	{
		ship.closestPointToAsteroid.x = collisionBoxAsteroid.x + collisionBoxAsteroid.width;
	}
	if (ship.closestPointToAsteroid.x > collisionBoxAsteroid.x)
	{
		ship.closestPointToAsteroid.x = collisionBoxAsteroid.x;
	}

	ship.closestPointToAsteroid.y = collisionBoxShip.y;
	if (ship.closestPointToAsteroid.y < collisionBoxAsteroid.y)
	{
		ship.closestPointToAsteroid.y = collisionBoxAsteroid.y;
	}
	if (ship.closestPointToAsteroid.y > collisionBoxAsteroid.y + collisionBoxAsteroid.height)
	{
		ship.closestPointToAsteroid.y = collisionBoxAsteroid.y + collisionBoxAsteroid.height;
	}

	float distance = sqrt(pow(collisionBoxShip.x - ship.closestPointToAsteroid.x, 2) + pow(collisionBoxShip.y - ship.closestPointToAsteroid.y, 2));
	if (distance < collisionBoxShip.height || distance < collisionBoxShip.width)
	{
		ship.isAlive = false;
	}
}