#include <iostream>
#include <ctime>
#include <raylib.h>
#include "game.h"
#include "ship.h"
#include "asteroids.h"
#include "bullets.h"

//menu vars
bool shouldShowMenu = true;
bool exitWindow = false;
int menuMouseHover = 0;
int menuOptionSelected = 0;
const int menuSize = 3;
Rectangle menuRect[menuSize];
Rectangle backRect;

extern Asteroid bigAsteroid;
extern SpaceShip ship;

void gameLoop()
{
    SetRandomSeed(time(NULL));
    initShip();
    initAsteroids();
    initBullet();
    createMenuButtons();

    while (!WindowShouldClose() && !exitWindow)
    {
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < menuSize; i++)
        {
            if (CheckCollisionPointRec(mousePos, menuRect[i]))//si la pos del mouse esta dentro del rec
            {
                menuMouseHover = i;
                break;
            }
            else
                menuMouseHover = -1;
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (shouldShowMenu)
        {
            SetExitKey(KEY_ESCAPE);
            DrawText("ANARCHY ON SPACE", 85, 100, 80, RAYWHITE);
            for (int i = 0; i < menuSize; i++)
            {
                DrawRectangle(menuRect[i].x, menuRect[i].y, menuRect[i].width, menuRect[i].height, GOLD);
                if (i == 0)
                {
                    DrawText("PLAY", menuRect[i].x + 55, menuRect[i].y + 10, 50, BLACK);
                    if (menuMouseHover == 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        menuOptionSelected = 0;
                        shouldShowMenu = false;
                    }
                }
                if (i == 1)
                {
                    DrawText("CREDITS", menuRect[i].x + 10, menuRect[i].y + 10, 50, BLACK);
                    if (menuMouseHover == 1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        menuOptionSelected = 1;
                        shouldShowMenu = false;
                    }
                }
                if (i == 2)
                {
                    DrawText("EXIT", menuRect[i].x + 60, menuRect[i].y + 10, 50, BLACK);
                    if (menuMouseHover == 2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        menuOptionSelected = 2;
                        shouldShowMenu = false;
                    }
                }
            }
        }
        else if(!shouldShowMenu && ship.isAlive)
        {
            switch (menuOptionSelected)
            {
            case 0:
                SetExitKey(0);
                shouldShowMenu = false;
                //nave
                drawShip();
                rotateShip();
                moveShip();

                //balas
                shoot();

                //asteroides
                drawAsteroids();
                checkAsteroidToShipCollisions();
                checkAsteroidToBulletCollision();
                divideAsteroids();

                //menu             
                drawBackButton(mousePos, shouldShowMenu);
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    shouldShowMenu = true;
                }
                break;
            case 1:
                SetExitKey(0);
                DrawText("Developed by: Daniela Gonzalez", 120, 300, 50, LIGHTGRAY);
                DrawText("2D art by: Eros Khalil Beron", 120, 380, 50, LIGHTGRAY);
                shouldShowMenu = false;
                drawBackButton(mousePos, shouldShowMenu);
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    shouldShowMenu = true;
                }
                break;
            case 2:
                exitWindow = true;
                shouldShowMenu = false;          
                break;
            }
        }
        showFinalMessage();
        EndDrawing();
    }
    CloseWindow();
}

void createMenuButtons()
{
    for (int i = 0; i < menuSize; i++)//rectangulos menu
    {
        menuRect[i].width = 250;
        menuRect[i].height = 70;
        menuRect[i].x = 380;
        menuRect[i].y = 300 + menuRect[i].height * i + 50 * i;
    }
    backRect.x = 10;
    backRect.y = 10;
    backRect.width = 50;
    backRect.height = 25;
}

void drawBackButton(Vector2 mousePos, bool& shouldShowMenu)
{
    DrawRectangle(backRect.x, backRect.y, backRect.width, backRect.height, GOLD);
    if (CheckCollisionPointRec(mousePos, backRect))//si la pos del mouse esta dentro del rec
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            shouldShowMenu = true;
        }
    }
}

void showFinalMessage()
{
    if (!ship.isAlive)
    {
        DrawText("You died", GetScreenWidth()/2, GetScreenHeight() / 2, 50, LIGHTGRAY);
    }
}