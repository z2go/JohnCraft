#include "Player.h"
#include <iostream>


using namespace sf;
using namespace std;



Vector2f position;


Player::Player(float startX, float startY) {
	position.x = startX;
	position.y = startY;

	playerShape.setSize(Vector2f(32, 32));
	playerShape.setPosition(position);

}
FloatRect Player::getPosition()
{
	return playerShape.getGlobalBounds();
}
RectangleShape Player::getShape() {
	return playerShape;
}
void Player::move(char direction, float speedMult) {
	switch (direction)
	{
	case 'u':
		position.y -= playerSpeed * speedMult;
		break;
	case 'd':
		position.y += playerSpeed * speedMult;
		break;
	case 'l':
		position.x -= playerSpeed * speedMult;
		break;
	case 'r':
		position.x += playerSpeed * speedMult;
		break;
	default:
		break;
	}
}
