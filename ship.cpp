#include <raylib.h>
#include <cmath>
#include "ship.h"

Rectangle ship;
Vector2 pivot;
Vector2 dir;
Vector2 mousePos;
float rotation;

void initShip()
{
    ship.x = 500;
    ship.y = 300;
    ship.width = 50;
    ship.height = 50;
    pivot.x = ship.width / 2;
    pivot.y = ship.height / 2;
    rotation = 0;
}

void drawShip()
{
    //rotation += 0.01;
    //DrawTextureEx(Texture2D texture, shipPos, float rotation, float scale, Color tint);
    DrawRectanglePro(ship, pivot, rotation, RAYWHITE);
}

void moveShip()
{
    mousePos.x = GetMouseX();
    mousePos.y= GetMouseY();
    dir.x = mousePos.x - pivot.x;
    dir.y = mousePos.y - pivot.y;
    //angulo = arcotangente( vectorDireccion .y / vectorDireccion.x)


    //IF RIGHTCLICK IS PRESSED ship.x += dir.x ship.Y += dir.Y;

}