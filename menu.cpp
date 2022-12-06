#include "menu.h"
#include <iostream>
int menuMouseHover = 0;
int menuOptionSelected = 0;
const int menuSize = 3;
Rectangle menuRect[menuSize];
Rectangle backRect;
Vector2 mousePosMenu;

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

void drawBackButton(bool& shouldShowMenu)
{
    mousePosMenu = GetMousePosition();
    DrawRectangle(backRect.x, backRect.y, backRect.width, backRect.height, GOLD);
    if (CheckCollisionPointRec(mousePosMenu, backRect))//si la pos del mouse esta dentro del rec
    {
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            shouldShowMenu = true;
        }
    }
}

void drawMenu(bool& shouldShowMenu)
{
    mousePosMenu = GetMousePosition();
    for (int i = 0; i < menuSize; i++)
    {
        if (CheckCollisionPointRec(mousePosMenu, menuRect[i]))//si la pos del mouse esta dentro del rec
        {
            menuMouseHover = i;
            break;
        }
        else
        {
            menuMouseHover = -1;
        }
    }

    int textSize = 50;
    SetExitKey(KEY_ESCAPE);
    DrawText("ANARCHY ON SPACE", 85, 100, 80, RAYWHITE);
    for (int i = 0; i < menuSize; i++)
    {
        DrawRectangle(menuRect[i].x, menuRect[i].y, menuRect[i].width, menuRect[i].height, GOLD);
        if (i == 0)
        {
            DrawText("PLAY", menuRect[i].x + 55, menuRect[i].y + 10, textSize, BLACK);
            if (menuMouseHover == 0 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menuOptionSelected = 0;
                shouldShowMenu = false;
            }
        }
        if (i == 1)
        {
            DrawText("CREDITS", menuRect[i].x + 10, menuRect[i].y + 10, textSize, BLACK);
            if (menuMouseHover == 1 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menuOptionSelected = 1;
                shouldShowMenu = false;
            }
        }
        if (i == 2)
        {
            DrawText("EXIT", menuRect[i].x + 60, menuRect[i].y + 10, textSize, BLACK);
            if (menuMouseHover == 2 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                menuOptionSelected = 2;
                shouldShowMenu = false;
            }
        }
    }
}

int getMenuOptionSelected()
{
    return menuOptionSelected;
    std::cout << menuOptionSelected << "menuoption/n";
}

void showCredits(bool& shouldShowMenu)
{
    int textSize = 50;
    SetExitKey(0);
    DrawText("Developed by: Daniela Gonzalez", 120, 300, textSize, LIGHTGRAY);
    DrawText("2D art by: Eros Khalil Beron", 120, 380, textSize, LIGHTGRAY);
    shouldShowMenu = false;
    drawBackButton(shouldShowMenu);
    if (IsKeyPressed(KEY_ESCAPE))
    {
        shouldShowMenu = true;
    }
}