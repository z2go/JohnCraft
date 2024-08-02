#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class FloorItem {
public:
	int type = -1;

	int stack = 0;
	Vector2f position;


	FloorItem();
	FloorItem(int t, int s, int x, int y);
};