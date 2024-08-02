#pragma once
#include "SFML/Graphics.hpp"


using namespace sf;


class Player
{
private:
    
    RectangleShape playerShape;
    

    float playerSpeed = 0.1f;

public:
    char direction = 'u';
    bool isWalking = false;

    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;

    Vector2f position;
    Vector2f gridPosition;

    Player(float startX, float startY);

    FloatRect getPosition();
    RectangleShape getShape();
    void move(char direction, float speedMult);
};