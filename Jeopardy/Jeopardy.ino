#include "Button.h"
#include "Player.h"
#include <Adafruit_NeoPixel.h>

const int button1pin = 12;
const int button2pin = 6;
const int button3pin = 7;
const int light1pin = 13;
const int light2pin = 3;
const int light3pin = 4;
const int buzzerPin = 16;
const int clearButtonPin = 2;
const int neopixelPin = 14;
int num_of_teams_in = 0;
int playerIn = 0;

#define NUMPIXELS 20 // Popular NeoPixel ring size

Adafruit_NeoPixel pixels(NUMPIXELS, neopixelPin, NEO_GRB + NEO_KHZ800);

int NUMBER_OF_PLAYERS = 3;
int order[] = {9, 9, 9};
Player players[] = {
    Player(light1pin, button1pin, pixels.Color(0, 50, 0)), //TODO Store Player color 
    Player(light2pin, button2pin, pixels.Color(0, 0, 50)),
    Player(light3pin, button3pin, pixels.Color(50, 0, 0))};

Button ClearBtn(clearButtonPin, &Clear, 30); // pin, func ref, (optional) debounce

void setup()
{
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pixels.setPixelColor(10, pixels.Color(0, 15, 0));

  pixels.show(); // Send the updated pixel colors to the hardware.
}

void loop()
{
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
  {
    if (players[i].CheckPlayerIn())
    {
      order[playerIn] = i;

      pixels.setPixelColor(playerIn, players[i].getColor()); // Set the color for the Player who buzzed in using the stored color
      pixels.show(); // Send the updated pixel colors to the hardware.

      playerIn++;
    }
  }
  ClearBtn.update();
};

void Clear(int state)
{
  playerIn = 0;
  for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
  {
    players[i].reset();
  }
  pixels.clear(); // Set all pixel colors to 'off'
  pixels.show();  // Send the updated pixel colors to the hardware.
}
