#include <cmath>
#include <iostream>
#include <raylib.h>
#include "raymath.h"
#include "ship.h"
#include "game.h"
using namespace std;

Rectangle ship;
Vector2 pivot;
Vector2 dir;
Vector2 acceleration;
Vector2 mousePos;
float rotation;
float angle;

void initShip()
{
    ship.x = screenWidth / 2;
    ship.y = screenHeight / 2;
    ship.width = 50;
    ship.height = 50;
    pivot.x = ship.width / 2;
    pivot.y = ship.height / 2;
    acceleration.x = 0;
    acceleration.y = 0;
    angle = 0;
    rotation = 0;
}

void drawShip()
{
    //rotation += 1;
    //DrawTextureEx(Texture2D texture, shipPos, float rotation, float scale, Color tint);
    dir = Vector2Normalize(dir);
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        acceleration.x += dir.x;
        acceleration.y += dir.y;
    }
    dir.x += dir.x + acceleration.x * GetFrameTime();
    dir.y += dir.y + acceleration.y * GetFrameTime();
    DrawRectanglePro(ship, pivot, rotation, RAYWHITE);
}

void rotateShip()
{
    mousePos.x = GetMouseX();
    mousePos.y= GetMouseY();
    dir.x = mousePos.x - pivot.x;
    dir.y = mousePos.y - pivot.y;
    angle = (atan2f((float)dir.y, (float)dir.x)) * 180 / PI;

    if (dir.x < screenWidth / 2 && dir.y < screenHeight / 2/*|| mousePos.x < 0 && mousePos.y < 0*/) //cuadrante dos y tres
    {
        angle += 180;
        cout << "Segundo cuadrante\n";
    }
    rotation = angle; 
}

void moveShip()
{
    //IF RIGHTCLICK IS PRESSED ship.x += dir.x ship.Y += dir.Y;

}