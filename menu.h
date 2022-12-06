#pragma once
#include "raylib.h"

void createMenuButtons();
void drawBackButton(bool& shouldShowMenu);
void drawMenu(bool& shouldShowMenu);
int getMenuOptionSelected();
void showCredits(bool& shouldShowMenu);