#pragma once
#include "SFML/Graphics.hpp"
#include <cmath>
#include <iostream>


using namespace sf;

class Block
{
private:
	RectangleShape blockShape;
public:
	int type = -1;
	bool isWalkable = true;;
	float speedMult = 1.0f;
	int toughness = 0;
	char bestTool = 'n';
	bool replaceable = true;
	int itemType = -1;
	bool isBreakable = false;

	int breakingForce = 0;

	Vector2f gridPosition;
	Vector2f screenPosition;

	Block();
	Block(int xPos, int yPos, int type);

	FloatRect getPosition();
	RectangleShape getShape();

	void update();
	int getBreakingAnimation();

};
