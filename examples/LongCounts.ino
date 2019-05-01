#include "ClickButton.h"

// the LED
const int RLed = 14;
const int GLed = 15;
const int BLed = 16;

// the Button
const int buttonPin1 = 5;
ClickButton button1(buttonPin1);
int btClicks = 0;
boolean LedOn = false;

void setup()
{
  Serial.begin(57600);
  pinMode(RLed, OUTPUT);
  pinMode(GLed, OUTPUT);
  pinMode(BLed, OUTPUT);
  digitalWrite(RLed, LOW);
  digitalWrite(GLed, LOW);
  digitalWrite(BLed, LOW);
  button1.debounceTime   = 20;   // Debounce timer in ms
  button1.multiclickTime = 250;  // Time limit for multi clicks
  button1.longClickTime  = 1000; // time until "held-down clicks" register
}

void loop()
{
  // Update button state
  button1.Update();
  if (button1.longs) {
    Serial.print("Counts - ");
    Serial.println(button1.clicks);
    switch (button1.clicks) {
      case -1:
        setColor(0x0000FF);
        break;
      case -2:
        setColor(0x00FF00);
        break;
      case -3:
        setColor(0xFF0000);
        break;
      case -4:
        setColor(0xFF00FF);
        break;
    }
  }
  if (button1.changed) {
    btClicks = button1.clicks;
    Serial.println(btClicks);
    if (LedOn) {
      setColor(0x000000);
      LedOn = false;
    }
  }
}

void setColor(long color)
{
  /*
    int red = 255 - (color >> 16);
    int green = 255 - (color >> 8 & 0xFF);
    int blue = 255 - (color & 0xFF);
  */
  LedOn = true;
  int red = color >> 16;
  int green = color >> 8 & 0xFF;
  int blue = color & 0xFF;
  Serial.print("Red - ");
  Serial.print(red);
  Serial.print(" Green - ");
  Serial.print(green);
  Serial.print(" Blue - ");
  Serial.println(blue);
  analogWrite(RLed, red);
  analogWrite(GLed, green);
  analogWrite(BLed, blue);

}
