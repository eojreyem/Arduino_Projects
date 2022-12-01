#include "DFPlayerMini_Fast.h"
#include "TripWire.h"
#include <SoftwareSerial.h>
#include "Button.h"

const int fakeRx = 13;
const int softSerialTX1 = 7;
const int s_pin = A0;
const int l_pin = 12;
const int start_pin = 5;
const int finish_pin = 6;
const int sensorThreshold = 25;

DFPlayerMini_Fast MiPlayer;
TripWire Laser1(&MiPlayer, s_pin, l_pin, sensorThreshold);
TripWire Laser2(&MiPlayer, A1, 11, sensorThreshold);
Button StartBtn(start_pin, &Activate, 40); // pin, function reference, (optional)debounce in milliseconds.
Button FinishBtn(finish_pin, &Finish, 40); // pin, function reference, (optional)debounce in milliseconds.

SoftwareSerial MSerial(fakeRx, softSerialTX1); // open software serial

// the setup routine runs once when you press reset:
void setup()
{
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(start_pin, INPUT_PULLUP);
  pinMode(fakeRx, INPUT);
  pinMode(softSerialTX1, OUTPUT);
  MSerial.begin(9600);
  delay(40);

  MiPlayer.begin(MSerial);
  delay(40);
  MiPlayer.volume(29);
}

void loop()
{
  StartBtn.update();
  Laser1.update();
  Laser2.update();
  FinishBtn.update();

  // if (!Laser1.isActive)
  // {
  //   MiPlayer.play(3); // "Honk!"
  //   Serial.println("laser 1 path blocked");
  // }
};

void Activate(int state)
{
  if (state == 1)
  {
    MiPlayer.play(1);
    delay(2000);

    Laser1.activate();
    Laser2.activate();
    Serial.println("Laser Field Activated.");
  }
}

void Finish(int state)
{
  if (state == 1)
  {
    Laser1.deactivate();
    Laser2.deactivate();
  }

  MiPlayer.play(4);
  delay(40);
  Serial.println("Finished");
}
