#include <ctime>
#include <iostream>
#include "game.h"
#include "asteroids.h"
#include "ship.h"
#include "bullets.h"

Asteroid bigAsteroid[maxAsteroids];
Asteroid mediumAsteroid[maxAsteroids*2];
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
		bigAsteroid[i].isAlive = true;

		do
		{
			bigAsteroid[i].pos.x = GetRandomValue(0, screenWidth); 
			bigAsteroid[i].pos.y = GetRandomValue(0, screenHeight);
		} while (bigAsteroid[i].pos.x == collisionBoxShip.x || bigAsteroid[i].pos.x == collisionBoxShip.x + collisionBoxShip.width || bigAsteroid[i].pos.y == collisionBoxShip.y || bigAsteroid[i].pos.y == collisionBoxShip.y + collisionBoxShip.height);
		do
		{
			bigAsteroid[i].dir.x = GetRandomValue(-100, 100);
			bigAsteroid[i].dir.y = GetRandomValue(-100, 100);
		} while (bigAsteroid[i].dir.x < 50 && bigAsteroid[i].dir.x > -50 && bigAsteroid[i].dir.x < 50 && bigAsteroid[i].dir.x > -50);

		collisionBoxAsteroid[i].x = bigAsteroid[i].pos.x;
		collisionBoxAsteroid[i].y = bigAsteroid[i].pos.y;
		collisionBoxAsteroid[i].width = 120;
		collisionBoxAsteroid[i].height = 100;
	}

	for (int i = 0; i < maxAsteroids*2; i++)
	{
		mediumAsteroid[i].texture = LoadTexture("Assets/onion.png");
		mediumAsteroid[i].scale = 0.085;
		mediumAsteroid[i].rotation = 0;
		mediumAsteroid[i].dir.x = GetRandomValue(-100, 100);
		mediumAsteroid[i].dir.y = GetRandomValue(-100, 100);

		std::cout << "mediumasteroid dir x: " << mediumAsteroid[i].dir.x << std::endl;
		std::cout << "mediumasteroid dir y: " << mediumAsteroid[i].dir.y << std::endl;
	}

	
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
		if (!bigAsteroid[i].isAlive)
		{
			bigAsteroid[i].scale = 0;
			collisionBoxAsteroid[i].width = 0;
			collisionBoxAsteroid[i].height = 0;
		}
		DrawTextureEx(bigAsteroid[i].texture, bigAsteroid[i].pos, bigAsteroid[i].rotation, bigAsteroid[i].scale, RAYWHITE);
	}
}

void checkAsteroidToShipCollisions(Vector2& pos, Rectangle& collisionBoxShip, Vector2& dir)
{	
	ship.collide = false;
	for (int i = 0; i < maxAsteroids; i++)
	{
		if (bigAsteroid[i].isAlive)
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
				std::cout << "lives" << ship.lives << std::endl;
				ship.lives -= 1;

				if (ship.lives < 1)
				{
					ship.isAlive = false;
				}
				ship.collide = true;

			}
			
		}
	}
}

void checkAsteroidToBulletCollision()
{
	for (int i = 0; i < maxAsteroids; i++)
	{
		//DrawRectangleLines(bullet.pos.x, bullet.pos.y, bullet.size.x, bullet.size.y, YELLOW);
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
			if (collisionBoxAsteroid[i].x == bigAsteroid[i].pos.x + 50)
			{
				std::cout << "Colision astroide grande\n";
				bigAsteroid[i].isAlive = false;
			}
			//if (collisionBoxAsteroid[i].x == mediumAsteroid.pos.x + 50)
			//{
			//	std::cout << "Colision astroide mediano\n";
			//}
		}
	}
}

void divideAsteroids()
{
	for (int i = 0; i < maxAsteroids*2; i++)
	{
		for (int j = 0; j < maxAsteroids; j++)
		{

			if (!bigAsteroid[j].isAlive)
			{

				//mediumAsteroid[i].pos.x = bigAsteroid[j].pos.x + mediumAsteroid[i].dir.x;
				mediumAsteroid[i].pos.y = bigAsteroid[j].pos.y + mediumAsteroid[i].dir.y;
			    mediumAsteroid[j].pos.x = bigAsteroid[j].pos.x + mediumAsteroid[j].dir.x + 150;
				//mediumAsteroid[j].pos.y += bigAsteroid[j].pos.y  + mediumAsteroid[j].dir.y +50;


				DrawTextureEx(mediumAsteroid[i].texture, mediumAsteroid[i].pos, mediumAsteroid[i].rotation, mediumAsteroid[i].scale, RAYWHITE);
			}
		}
	}	
}
