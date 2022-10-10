#include <ctime>
#include <iostream>
#include "game.h"
#include "asteroids.h"
#include "ship.h"
#include "bullets.h"

Asteroid bigAsteroid[maxAsteroids];
Asteroid mediumAsteroid;
Asteroid smallAsteroid;
Rectangle collisionBoxAsteroid[maxAsteroids];
extern SpaceShip ship;
extern Rectangle collisionBoxShip;
extern Bullet bullet;

void initAsteroids()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		bigAsteroid[i].texture = LoadTexture("Assets/while(true).png");
		bigAsteroid[i].scale = 0.15;
		bigAsteroid[i].rotation = 0;

		do
		{
			bigAsteroid[i].pos.x = GetRandomValue(0, screenWidth); 
			bigAsteroid[i].pos.y = GetRandomValue(0, screenHeight);
		} while (bigAsteroid[i].pos.x == collisionBoxShip.x || bigAsteroid[i].pos.y == collisionBoxShip.y);
		do
		{
			bigAsteroid[i].dir.x = GetRandomValue(-100, 100);
			bigAsteroid[i].dir.y = GetRandomValue(-100, 100);
		} while (bigAsteroid[i].dir.x < 50 && bigAsteroid[i].dir.x > -50 && bigAsteroid[i].dir.x < 50 && bigAsteroid[i].dir.x > -50);

		//bigAsteroid[i].newPos.x = bigAsteroid[i].pos.x;
		//bigAsteroid[i].newPos.y = bigAsteroid[i].pos.y;

		collisionBoxAsteroid[i].x = bigAsteroid[i].pos.x;
		collisionBoxAsteroid[i].y = bigAsteroid[i].pos.y;
		collisionBoxAsteroid[i].width = 120;
		collisionBoxAsteroid[i].height = 100;
	}

	mediumAsteroid.texture = LoadTexture("Assets/onion.png");
	smallAsteroid.texture = LoadTexture("Assets/cap.png");
}

void drawAsteroids()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		bigAsteroid[i].newPos.x = bigAsteroid[i].pos.x + bigAsteroid[i].dir.x * GetFrameTime();
		bigAsteroid[i].newPos.y = bigAsteroid[i].pos.y + bigAsteroid[i].dir.y * GetFrameTime();
		if (bigAsteroid[i].newPos.x > screenWidth)
		{
			bigAsteroid[i].newPos.x = 0;
		}
		if (bigAsteroid[i].newPos.x < 0)
		{
			bigAsteroid[i].newPos.x = screenWidth;
		}

		if (bigAsteroid[i].newPos.y > screenHeight)
		{
			bigAsteroid[i].newPos.y = 0;
		}
		if (bigAsteroid[i].newPos.y < 0)
		{
			bigAsteroid[i].newPos.y = screenHeight;
		}
		bigAsteroid[i].rotation += 0.05 * GetFrameTime();
		bigAsteroid[i].pos.x = bigAsteroid[i].newPos.x;
		bigAsteroid[i].pos.y = bigAsteroid[i].newPos.y;
		DrawTextureEx(bigAsteroid[i].texture, bigAsteroid[i].pos, bigAsteroid[i].rotation, bigAsteroid[i].scale, RAYWHITE);
	}
}

void checkAsteroidToShipCollisions()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		collisionBoxAsteroid[i].x = bigAsteroid[i].pos.x + 50;
		collisionBoxAsteroid[i].y = bigAsteroid[i].pos.y + 50;
		DrawRectangleLines(collisionBoxAsteroid[i].x, collisionBoxAsteroid[i].y, collisionBoxAsteroid[i].width, collisionBoxAsteroid[i].height, YELLOW);

		ship.closestPointToAsteroid[i].x = collisionBoxShip.x;
		if (ship.closestPointToAsteroid[i].x < collisionBoxAsteroid[i].x + collisionBoxAsteroid[i].width)
		{
			ship.closestPointToAsteroid[i].x = collisionBoxAsteroid[i].x + collisionBoxAsteroid[i].width;
		}
		if (ship.closestPointToAsteroid[i].x > collisionBoxAsteroid[i].x)
		{
			ship.closestPointToAsteroid[i].x = collisionBoxAsteroid[i].x;
		}

		ship.closestPointToAsteroid[i].y = collisionBoxShip.y;
		if (ship.closestPointToAsteroid[i].y < collisionBoxAsteroid[i].y)
		{
			ship.closestPointToAsteroid[i].y = collisionBoxAsteroid[i].y;
		}
		if (ship.closestPointToAsteroid[i].y > collisionBoxAsteroid[i].y + collisionBoxAsteroid[i].height)
		{
			ship.closestPointToAsteroid[i].y = collisionBoxAsteroid[i].y + collisionBoxAsteroid[i].height;
		}

		float distance = sqrt(pow(collisionBoxShip.x - ship.closestPointToAsteroid[i].x, 2) + pow(collisionBoxShip.y - ship.closestPointToAsteroid[i].y, 2));
		if (distance < collisionBoxShip.height || distance < collisionBoxShip.width)
		{
			ship.isAlive = false;
		}
	}
}

void checkAsteroidToBulletCollision()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		DrawRectangleLines(bullet.pos.x, bullet.pos.y, bullet.size.x, bullet.size.y, YELLOW);
		bullet.closestPointToAsteroid[i].x = bullet.pos.x;

		if (bullet.closestPointToAsteroid[i].x < collisionBoxAsteroid[i].x + collisionBoxAsteroid[i].width)
		{
			bullet.closestPointToAsteroid[i].x = collisionBoxAsteroid[i].x + collisionBoxAsteroid[i].width;
		}
		if (bullet.closestPointToAsteroid[i].x > collisionBoxAsteroid[i].x)
		{
			bullet.closestPointToAsteroid[i].x = collisionBoxAsteroid[i].x;
		}

		bullet.closestPointToAsteroid[i].y = bullet.pos.y;
		if (bullet.closestPointToAsteroid[i].y < collisionBoxAsteroid[i].y)
		{
			bullet.closestPointToAsteroid[i].y = collisionBoxAsteroid[i].y;
		}
		if (bullet.closestPointToAsteroid[i].y > collisionBoxAsteroid[i].y + collisionBoxAsteroid[i].height)
		{
			bullet.closestPointToAsteroid[i].y = collisionBoxAsteroid[i].y + collisionBoxAsteroid[i].height;
		}

		float distance = sqrt(pow(bullet.pos.x - bullet.closestPointToAsteroid[i].x, 2) + pow(bullet.pos.y - bullet.closestPointToAsteroid[i].y, 2));
		if (distance < bullet.size.y || distance < bullet.size.x)
		{
			std::cout << "pium pium\n";
		}
	}
}