#include <iostream>
#include "bullets.h"
#include "ship.h"

Bullet bullet; 
extern SpaceShip ship;

void initBullet()
{
    bullet.pos.x = ship.pos.x;
    bullet.pos.y = ship.pos.y;
    bullet.dir.x = ship.dir.x;
    bullet.dir.y = ship.dir.y;
    bullet.size.x = 10;
    bullet.size.y = 10;
}

void shoot()
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !bullet.isAlive)
    {
        bullet.isAlive = true;
        bullet.dir.x = GetMouseX() - ship.pos.x;
        bullet.dir.y = GetMouseY() - ship.pos.y;
        bullet.dir = Vector2Normalize(bullet.dir);
        bullet.speed = 700;
    }

    if (!bullet.isAlive)
    {
        return;
    }

    bullet.pos.x += bullet.dir.x * bullet.speed * GetFrameTime(); 
    bullet.pos.y += bullet.dir.y * bullet.speed * GetFrameTime(); 
    DrawRectangleV(bullet.pos, bullet.size, WHITE);

    if (bullet.pos.x < 0 || bullet.pos.x > GetScreenWidth() || bullet.pos.y < 0 || bullet.pos.x > GetScreenWidth())
    {
        bullet.pos.x = ship.pos.x;
        bullet.pos.y = ship.pos.y;
        bullet.isAlive = false;
    }
}