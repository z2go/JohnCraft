#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace sf;

class Entity {
public:
	Vector2f position;
	Vector2i size;

	float speed = 0.1f;
	int dimension = 1;
	int type = -1;
	float health;
	float damage;
	bool isMoving = true;

	char direction = 'd';

	int AIType;

	void move(char direction);
	void takeDamage(int damage);
	Entity();
	Entity(int x, int y,int t);

};