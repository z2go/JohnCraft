#include "Entity.h"

using namespace std;

Entity::Entity() {

}
Entity::Entity(int x, int y, int t) {
	position.x = x;
	position.y = y;

	type = t;

	switch (type) {
	case 0: //Boss
		health = 200.0f;
		damage = 7.0f;
		size.x = 32;
		size.y = 60;
		AIType = 0;
		speed = 0.18;
		break;
	}
}

void Entity::move(char d) {
	direction = d;
	switch (d)
	{
	case 'u':
		position.y -= speed;
		break;
	case 'd':
		position.y += speed;
		break;
	case 'l':
		position.x -= speed;
		break;
	case 'r':
		position.x += speed;
		break;
	}
}

void Entity::takeDamage(int d) {
	health -= d;

}