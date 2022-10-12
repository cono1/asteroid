#pragma once
#include <raylib.h>

const int screenWidth = 1024;
const int screenHeight = 768;

void gameLoop();
void createMenuButtons();
void drawBackButton(Vector2 mousePos, bool& shouldShowMenu);
void drawMenu();
void showCredits(Vector2 mousePos);
void showFinalMessage();