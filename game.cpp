#include <raylib.h>
#include "game.h"
#include "ship.h"


bool shouldShowMenu = true;
int menuMouseHover = 0;
int menuOptionSelected = 0;
const int menuSize = 3;
Rectangle menuRect[menuSize];


void showMenu()
{

    initShip();

    for (int i = 0; i < menuSize; i++)//dibujo rectangulos menu
    {
        menuRect[i].width = 250;
        menuRect[i].height = 70;
        menuRect[i].x = 350;
        menuRect[i].y = 200 + menuRect[i].height * i + 50 * i;
    }

    while (!WindowShouldClose())
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
                DrawText("JUGANDO", 10, 10, 50, LIGHTGRAY);
                shouldShowMenu = false;         
                drawShip();
                moveShip();
                break;
            case 1:
                DrawText("CREDITOS", 10, 10, 50, LIGHTGRAY);
                shouldShowMenu = false;
                break;
            case 2:
                DrawText("SALINEDO", 10, 10, 50, LIGHTGRAY);
                shouldShowMenu = false;
                break;
            default:
                DrawText("COSO", 10, 10, 50, LIGHTGRAY);
                shouldShowMenu = false;
                break;
            }
        }
        EndDrawing();
    }
    CloseWindow();
}

