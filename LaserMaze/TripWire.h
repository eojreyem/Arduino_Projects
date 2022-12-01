//Library for monitoring a long distance laser beam break.

// ensure this library description is only included once
#ifndef TripWire_h
#define TripWire_h

#include "Arduino.h"
#include "DFPlayerMini_Fast.h"

class TripWire
{
private:
    DFPlayerMini_Fast *Player;
    int sensor_pin;
    int laser_pin;
    int sensorValOn = 1023;
    int sensorValOff = 0;
    int laserCycle = 1;
    int threshold;
    unsigned long currentMillis;
    unsigned long lastMillis;

public:
    bool isActive = false;
    TripWire(DFPlayerMini_Fast *, int, int, int);
    void update();
    void activate();
    void deactivate();
};

// sensor pin, laser pin.
TripWire::TripWire(DFPlayerMini_Fast *DFplayer, int _s, int _l, int _t)
{
    Player = DFplayer;
    sensor_pin = _s;
    laser_pin = _l;
    threshold = _t;
    pinMode(sensor_pin, INPUT);
    pinMode(laser_pin, OUTPUT);
}

void TripWire::activate()
{
    sensorValOn = 1023;
    sensorValOff = 0;
    laserCycle = 1;
    isActive = true;
    digitalWrite(laser_pin, LOW);
    lastMillis = millis();
    Player->play(2);
    delay(40);
}

void TripWire::deactivate()
{
    digitalWrite(laser_pin, LOW);
    isActive = false;
}

void TripWire::update()
{
    currentMillis = millis();

    if ((currentMillis - lastMillis) > 10)
    {
        if (laserCycle == 1)
        {
            sensorValOff = analogRead(sensor_pin);
            if (isActive)
                digitalWrite(laser_pin, HIGH);
        }
        else if ((laserCycle > 1) && (isActive))
        {
            sensorValOn = analogRead(sensor_pin);
            if ((sensorValOn - sensorValOff) < threshold)
            {
                digitalWrite(laser_pin, LOW);

                Player->play(3);
                laserCycle = -300; //Turns laser off for 300 * 10 millis
            }
        }
        else if ((laserCycle == -1) && (isActive))
        {
            Player->play(2);
        }

        if (laserCycle >= 4)
        {
            digitalWrite(laser_pin, LOW);
            laserCycle = 0;
        }
        laserCycle++;
        lastMillis = currentMillis;
        Serial.println(sensorValOn - sensorValOff);
    }
};

#endif