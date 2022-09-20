#include <raylib.h>
#include "ship.h"

Rectangle rec;
Vector2 pivot;
float rotation;

void initShip()
{
    rec.x = 500;
    rec.y = 300;
    rec.width = 50;
    rec.height = 300;
    pivot.x = rec.width / 2;
    pivot.y = rec.height / 2;
    rotation = 0;
}

void drawShip()
{
    rotation += 0.01;
    //DrawTextureEx(Texture2D texture, shipPos, float rotation, float scale, Color tint);
    DrawRectanglePro(rec, pivot, rotation, RAYWHITE);
}