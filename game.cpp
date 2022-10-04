#include <iostream>
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
extern Bullet bullet;

void gameLoop()
{
    initShip();
    initAsteroids();
    initBullet();
    generateAsteroids();
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
            for (int i = 0; i < menuSize; i++)
            {
                DrawRectangle(menuRect[i].x, menuRect[i].y, menuRect[i].width, menuRect[i].height, RED);
                if (i == 0)
                {
                    DrawText("PLAY", menuRect[i].x + 35, menuRect[i].y + 10, 50, LIGHTGRAY);
                    if (menuMouseHover == 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        menuOptionSelected = 0;
                        shouldShowMenu = false;
                    }
                }
                if (i == 1)
                {
                    DrawText("CREDITS", menuRect[i].x, menuRect[i].y + 10, 50, LIGHTGRAY);
                    if (menuMouseHover == 1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        menuOptionSelected = 1;
                        shouldShowMenu = false;
                    }
                }
                if (i == 2)
                {
                    DrawText("EXIT", menuRect[i].x + 35, menuRect[i].y + 10, 50, LIGHTGRAY);
                    if (menuMouseHover == 2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                    {
                        menuOptionSelected = 2;
                        shouldShowMenu = false;
                    }
                }
            }
        }
        else
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
                shoot(bullet.pos);

                //asteroides
                drawAsteroids();
                moveAsteoids();
                checkCollisions();

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
        menuRect[i].x = 350;
        menuRect[i].y = 200 + menuRect[i].height * i + 50 * i;
    }
    backRect.x = 10;
    backRect.y = 10;
    backRect.width = 70;
    backRect.height = 40;
}

void drawBackButton(Vector2 mousePos, bool& shouldShowMenu)
{
    DrawRectangle(backRect.x, backRect.y, backRect.width, backRect.height, RED);
    if (CheckCollisionPointRec(mousePos, backRect))//si la pos del mouse esta dentro del rec
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            shouldShowMenu = true;
        }
    }
}

void checkCollisions() //(?
{
    ship.closestPointToAsteroid.x = bigAsteroid.pos.x;
    if (ship.closestPointToAsteroid.x < bigAsteroid.pos.x)//vertex
    {
        ship.closestPointToAsteroid.x = bigAsteroid.pos.x;
    }
    if (ship.closestPointToAsteroid.x > bigAsteroid.pos.x + bigAsteroid.scale)
    {
        ship.closestPointToAsteroid.x = bigAsteroid.pos.x + bigAsteroid.scale; 
    }

    //paddle1.closestPointToBall.y = ball.centerY;
    //if (paddle1.closestPointToBall.y < paddle1.lowerVertexY)
    //{
    //    paddle1.closestPointToBall.y = paddle1.lowerVertexY;
    //}
    //if (paddle1.closestPointToBall.y > paddle1.lowerVertexY + paddle1.height)
    //{
    //    paddle1.closestPointToBall.y = paddle1.lowerVertexY + paddle1.height;
    //}

    float distance1 = sqrt(pow(bigAsteroid.pos.x - ship.closestPointToAsteroid.x, 2) + pow(bigAsteroid.pos.y - ship.closestPointToAsteroid.y, 2));
    if (distance1 < bigAsteroid.scale/2) // Colisión detectada 
    {
        std::cout << "colision";
    }
}