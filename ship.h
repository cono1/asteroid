#pragma once

struct SpaceShip
{
	Vector2 pos;
	Vector2 newPos;
	Vector2 pivot;
	Vector2 dir;
	Vector2 acceleration;
	float rotation;
};

void loadTexture();
void initShip();
void drawShip();
void rotateShip();
void moveShip();