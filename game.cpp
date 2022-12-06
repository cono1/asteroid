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

Music gameMusic;
extern int score;
int maxScore = 100;
extern Asteroid bigAsteroid;
extern SpaceShip ship;

void gameLoop()
{
    SetRandomSeed(time(NULL));
    InitWindow(screenWidth, screenHeight, "asteroids");
    //gameMusic = LoadMusicStream(const char* fileName);
    //UnloadMusicStream(gameMusic);(?
    loadTexture();
    initShip();
    initAsteroids();
    initBullet();
    createMenuButtons();

    while (!WindowShouldClose() && !exitWindow)
    {
        if (ship.collide)
        {
            restartShipPos();
            initAsteroids();
        }
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < menuSize; i++)
        {
            if (CheckCollisionPointRec(mousePos, menuRect[i]))//si la pos del mouse esta dentro del rec
            {
                menuMouseHover = i;
                break;
            }
            else
            {
                menuMouseHover = -1;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);
        if (shouldShowMenu)
        {
            drawMenu();
        }
        else if(!shouldShowMenu && ship.isAlive && score < maxScore)
        {
            switch (menuOptionSelected)
            {
            case 0:
                SetExitKey(0);
                shouldShowMenu = false;
                DrawText(TextFormat(" HP: %i", ship.lives), screenWidth - 150, 10, 40, WHITE);
                DrawText(TextFormat(" SCORE: %i", score), 50, 10, 40, WHITE);
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
                showCredits(mousePos);
                break;
            case 2:
                exitWindow = true;
                shouldShowMenu = false;          
                break;
            }
        }
        showFinalMessage();
        if (IsKeyPressed(KEY_ENTER))
        {
            restartShipPos();
            initAsteroids();
            shouldShowMenu = false;
            ship.isAlive = true;
            score = 0;
        }

        if (IsKeyPressed(KEY_ESCAPE))
        {
            shouldShowMenu = true;
            ship.isAlive = true;
            score = 0;
        }

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

void drawMenu()
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

void showCredits(Vector2 mousePos)
{
    SetExitKey(0);
    DrawText("Developed by: Daniela Gonzalez", 120, 300, 50, LIGHTGRAY);
    DrawText("2D art by: Eros Khalil Beron", 120, 380, 50, LIGHTGRAY);
    shouldShowMenu = false;
    drawBackButton(mousePos, shouldShowMenu);
    if (IsKeyPressed(KEY_ESCAPE))
    {
        shouldShowMenu = true;
    }
}

void showFinalMessage()
{
    if (!ship.isAlive)
    {
        DrawText("Press ENTER  to play again", GetScreenWidth() / 3, GetScreenHeight() / 4, 30, LIGHTGRAY);
        DrawText("Press ESC  to go to menu", GetScreenWidth() / 3, GetScreenHeight() / 3, 30, LIGHTGRAY);
        DrawText("You died", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, LIGHTGRAY);
    }
    if (score >= maxScore)
    {
        DrawText("Press ENTER  to play again", GetScreenWidth() / 3, GetScreenHeight() / 4, 30, LIGHTGRAY);
        DrawText("You won!", GetScreenWidth() / 2, GetScreenHeight() / 2, 50, LIGHTGRAY);
    }
}

// rectangulos menuhttps://www.raylib.com/examples/textures/loader.html?name=textures_mouse_painting