#include <raylib.h>
#include <cmath>
#include "ship.h"
#include <iostream>
using namespace std;

Rectangle ship;
Vector2 pivot;
Vector2 dir;
Vector2 mousePos;
float rotation;
float angle;

void initShip()
{
    ship.x = 500;
    ship.y = 300;
    ship.width = 50;
    ship.height = 50;
    pivot.x = ship.width / 2;
    pivot.y = ship.height / 2;
    angle = 0;
    rotation = 0;
}

void drawShip()
{
    //rotation += 1;
    //DrawTextureEx(Texture2D texture, shipPos, float rotation, float scale, Color tint);
}

void moveShip()
{
    mousePos.x = GetMouseX();
    mousePos.y= GetMouseY();
    dir.x = mousePos.x + pivot.x;
    dir.y = mousePos.y + pivot.y;
    angle = atan2f((float)dir.y, (float)dir.x);
    angle *= PI / 180;//paso angulo a radianes
    if (mousePos.x < 0 && mousePos.y > 0 || mousePos.x < 0 && mousePos.y < 0) //cuadrante dos y tres
    {
        angle += 180;
    }
    if (mousePos.x > 0 && mousePos.y < 0) //cuadrante cuatro
    {
        angle += 360;
    }
    rotation = angle; 
    DrawRectanglePro(ship, pivot, rotation, RAYWHITE);

    //cout << " Angle: " << angle;
    //IF RIGHTCLICK IS PRESSED ship.x += dir.x ship.Y += dir.Y;
}