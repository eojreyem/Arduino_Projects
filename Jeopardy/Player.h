// Library for creating jeopardy players.

// ensure this library description is only included once
#ifndef Player_h
#define Player_h

#include "Arduino.h"

class Player
{
private:
    int button_pin;
    int light_pin;
    int number;
    int color;

public:
    bool isIn = false;
    Player(int, int, int);
    bool CheckPlayerIn();
    void lightOn();
    void lightOff();
    int getColor();
    void reset();
};

// player number, light pin, button pin.
Player::Player(int _l, int _b, int _c)
{
    button_pin = _b;
    light_pin = _l;
    color = _c;
    pinMode(button_pin, INPUT_PULLUP);
    pinMode(light_pin, OUTPUT);
    lightOn();
}

void Player::lightOn()
{
    digitalWrite(light_pin, HIGH);
}

void Player::lightOff()
{
    digitalWrite(light_pin, LOW);
}

int Player::getColor()
{
    return (color);
}

void Player::reset()
{
    isIn = false;
    lightOn();
}

bool Player::CheckPlayerIn()
{
    if (!(isIn)) // If not in
    {
        if (!digitalRead(button_pin)) // button is pushed
        {
            isIn = true;
            lightOff();
            return (isIn);
        }
        return (0);
    }
    return (0);
};

#endif