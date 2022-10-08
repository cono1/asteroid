#include <iostream>
#include "bullets.h"
#include "ship.h"

Bullet bullet; 
extern SpaceShip ship;

void initBullet()
{
    bullet.pos.x = ship.pos.x;
    bullet.pos.y = ship.pos.y;
    //bullet.newPos.x = 0;
    //bullet.newPos.y = 0;
    bullet.dir.x = ship.dir.x;
    bullet.dir.y = ship.dir.y;
    bullet.size.x = 10;
    bullet.size.y = 10;
}

void shoot(Vector2& pos)
{
    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) && !bullet.isAlive)
    {
        pos.x = bullet.pos.x;
        pos.y = bullet.pos.y;
        bullet.isAlive = true;
        bullet.dir.x = GetMouseX() - ship.pos.x;
        bullet.dir.y = GetMouseY() - ship.pos.y;
        bullet.dir = Vector2Normalize(bullet.dir);
        bullet.speed = 500;
    }

    if (!bullet.isAlive)
    {
        return;
    }

    bullet.pos.x += bullet.dir.x * bullet.speed * GetFrameTime(); 
    bullet.pos.y += bullet.dir.y * bullet.speed * GetFrameTime();

    
    DrawRectangleV(pos, bullet.size, WHITE);

    if (pos.x < 0 || pos.x > GetScreenWidth() || pos.y < 0 || pos.x > GetScreenWidth())
    {
        pos.x = ship.pos.x;
        pos.y = ship.pos.y;
        bullet.isAlive = false;
    }
}