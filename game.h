#pragma once
#include <raylib.h>

const int screenWidth = 1024;
const int screenHeight = 768;


void gameLoop();
void createMenuButtons();
void drawBackButton(Vector2 mousePos, bool& shouldShowMenu);
void checkCollisions();
void initBullet(Vector2& bulletPos, Vector2& bulletSize);
void shoot(Vector2& bulletPos);