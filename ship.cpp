#include <cmath>
#include <iostream>
#include <raylib.h>
#include "raymath.h"
#include "asteroids.h"
#include "ship.h"
#include "game.h"
using namespace std;

Vector2 mousePos;
Texture2D texture;
SpaceShip ship;
float angle;
Rectangle collisionBoxShip;
Rectangle textureBox;
Rectangle shipBox;


void loadTexture()
{
    texture = LoadTexture("Assets/conoShip.png");
}

void initShip()
{
    ship.pos.x = screenWidth / 2;
    ship.pos.y = screenHeight / 2;
    ship.newPos.x = ship.pos.x;
    ship.newPos.y = ship.pos.y;
    ship.pivot.x = ship.pos.x/2;  //ship.width / 2;
    ship.pivot.y = ship.pos.y/2;  //ship.height / 2;
    ship.acceleration.x = 0;
    ship.acceleration.y = 0;
    angle = 0;
    ship.lives = 3;
    ship.rotation = 0;
    ship.isAlive = true;

    collisionBoxShip.width = 80;
    collisionBoxShip.height = 80;

    shipBox.x = 250;
    shipBox.y = 190;
    shipBox.width = 900;
    shipBox.height = 900;

    textureBox.width = 100;
    textureBox.height = 100;
}

void restartShipPos()
{
    ship.pos.x = screenWidth / 2;
    ship.pos.y = screenHeight / 2;
    ship.newPos.x = ship.pos.x;
    ship.newPos.y = ship.pos.y;
    ship.dir.x = 0;
    ship.dir.y = 0;
    ship.acceleration.x = 0;
    ship.acceleration.y = 0;
}

void drawShip()
{
    ship.pos = ship.newPos;
    textureBox.x = ship.pos.x;
    textureBox.y = ship.pos.y;
    collisionBoxShip.x = textureBox.x- collisionBoxShip.width/2;
    collisionBoxShip.y = textureBox.y - collisionBoxShip.height/2;

    ship.pivot.x = collisionBoxShip.width / 2;
    ship.pivot.y = collisionBoxShip.height / 2;
    DrawRectangleLines(collisionBoxShip.x, collisionBoxShip.y, collisionBoxShip.width, collisionBoxShip.height, YELLOW);

    DrawTexturePro(texture, shipBox, textureBox, ship.pivot, ship.rotation, WHITE);
}

void rotateShip()
{
    mousePos.x = GetMouseX();
    mousePos.y= GetMouseY();
    ship.dir.x = ship.pos.x - mousePos.x;
    ship.dir.y = ship.pos.y - mousePos.y;
    angle = (atan2f((float)ship.dir.y, (float)ship.dir.x)) * 180 / PI;

    if (ship.dir.x < screenWidth / 2 && ship.dir.y < screenHeight / 2 || mousePos.x < screenWidth / 2 && mousePos.y > screenHeight / 2) //cuadrante dos y tres
    {
        angle += 180;
    }
    if (ship.dir.x > screenWidth / 2 && ship.dir.y < screenHeight / 2)
    {
        angle += 360;
    }
    ship.rotation = angle;
}

void moveShip()
{
    if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
    {
        ship.dir = Vector2Normalize(ship.dir);
        ship.acceleration.x -= ship.dir.x;
        ship.acceleration.y -= ship.dir.y;
    }
    ship.newPos.x = ship.pos.x + ship.acceleration.x * GetFrameTime();
    ship.newPos.y = ship.pos.y + ship.acceleration.y * GetFrameTime();
    if (ship.newPos.x > screenWidth)
    {
        ship.newPos.x = 0;
    }
    if (ship.newPos.x < 0)
    {
        ship.newPos.x = screenWidth;
    }

    if (ship.newPos.y > screenHeight)
    {
        ship.newPos.y = 0;
    }
    if (ship.newPos.y < 0)
    {
        ship.newPos.y = screenHeight;
    }
} 
