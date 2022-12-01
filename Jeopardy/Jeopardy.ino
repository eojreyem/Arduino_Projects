#include "Button.h"
#include <Adafruit_NeoPixel.h>

const int button1pin = 15;
const int button2pin = 16;
const int button3pin = 17;
const int light1pin = 12;
const int light2pin = 13;
const int light3pin = 14;
const int buzzerPin = 9;
const int clearButtonPin = 10;
const int neopixelPin = 11;


#define NUMPIXELS 20 // Popular NeoPixel ring size

Button Team1(button1pin, &Team1buzz, 30);
Button ClearBtn(clearButtonPin, &Clear, 30); //pin, func ref, (optional) debounce
Adafruit_NeoPixel pixels(NUMPIXELS, neopixelPin, NEO_GRB + NEO_KHZ800);


void setup() {
  
  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

}

void loop() 
{
  Team1.idle();
};
 
 void Clear()
  {
    pixels.clear(); // Set all pixel colors to 'off'    
    pixels.show();   // Send the updated pixel colors to the hardware.
  }

  void Team1buzz()
  {
    
    pixels.setPixelColor(1, pixels.Color(0, 255, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
  }
