#include "game.h"

#include <iostream>
#include <ctime>

#include "raylib.h"

#include "menu.h"
#include "ship.h"
#include "asteroids.h"
#include "bullets.h"

Music gameMusic;
extern int score;
int maxScore = 100;
extern Asteroid bigAsteroid;
extern SpaceShip ship;

void gameLoop()
{
    bool shouldShowMenu = true;
    bool exitWindow = false;
    int textSize = 40;
    int textPositionY = 10;
    SetRandomSeed(time(NULL));
    InitWindow(screenWidth, screenHeight, "asteroids");
    //gameMusic = LoadMusicStream(const char* fileName);
    //UnloadMusicStream(gameMusic);
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

        BeginDrawing();
        ClearBackground(BLACK);
        if (shouldShowMenu)
        {
            drawMenu(shouldShowMenu);
        }
        else if(!shouldShowMenu && ship.isAlive && score < maxScore)
        {
            switch (getMenuOptionSelected())
            {
            case 0:
                SetExitKey(0);
                shouldShowMenu = false;
                DrawText(TextFormat(" HP: %i", ship.lives), screenWidth - 150, textPositionY, textSize, WHITE);
                DrawText(TextFormat(" SCORE: %i", score), 50, textPositionY, textSize, WHITE);
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
                drawBackButton(shouldShowMenu);
                if (IsKeyPressed(KEY_ESCAPE))
                {
                    shouldShowMenu = true;
                }
                break;
            case 1:
                showCredits(shouldShowMenu);
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
    unloadTexture();
    unloadTextures();
    CloseWindow();
}

void showFinalMessage()
{
    int firstTextSize = 30;
    int secondTextSize = 50;

    if (!ship.isAlive)
    {
        DrawText("Press ENTER  to play again", GetScreenWidth() / 3, GetScreenHeight() / 4, firstTextSize, LIGHTGRAY);
        DrawText("Press ESC to go to menu", GetScreenWidth() / 3, GetScreenHeight() / 3, firstTextSize, LIGHTGRAY);
        DrawText("You died", GetScreenWidth() / 2, GetScreenHeight() / 2, secondTextSize, LIGHTGRAY);
    }
    if (score >= maxScore)
    {
        DrawText("Press ENTER  to play again", GetScreenWidth() / 3, GetScreenHeight() / 4, firstTextSize, LIGHTGRAY);
        DrawText("Press ESC to go to menu", GetScreenWidth() / 3, GetScreenHeight() / 3, firstTextSize, LIGHTGRAY);
        DrawText("You won!", GetScreenWidth() / 2, GetScreenHeight() / 2, secondTextSize, LIGHTGRAY);
    }
}

// rectangulos menuhttps://www.raylib.com/examples/textures/loader.html?name=textures_mouse_painting