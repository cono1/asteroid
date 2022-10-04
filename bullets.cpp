#include <iostream>
#include "bullets.h"
#include "ship.h"

Bullet bullet; //(? cuando funke hacer array (?
extern SpaceShip ship;

void initBullet()
{
    bullet.pos.x = ship.pos.x;
    bullet.pos.y = ship.pos.y;
    bullet.newPos.x = 0;
    bullet.newPos.y = 0;
    bullet.dir.x = ship.dir.x;
    bullet.dir.y = ship.dir.y;
    bullet.size.x = 10;
    bullet.size.y = 10;
}

void shoot(Vector2& pos)
{
    bullet.newPos.x = pos.x + GetMouseX() * GetFrameTime(); //bullet.pos (??
    bullet.newPos.y = pos.y + GetMouseY() * GetFrameTime();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        //std::cout << "x " << pos.x ;
        //std::cout << " y " <<pos.y << std::endl;

        pos.x = bullet.newPos.x;
        pos.y = bullet.newPos.y;
        if (pos.x >= GetScreenWidth() / 2)
        {
            std::cout << "\n\nAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n\n";
        }
        DrawRectangleV(pos, bullet.size, WHITE);
    }

    if (pos.x < 0 || pos.x > GetScreenWidth() || pos.y < 0 || pos.x > GetScreenWidth())
    {
        pos.x = ship.pos.x;
        pos.y = ship.pos.y;
    }
}