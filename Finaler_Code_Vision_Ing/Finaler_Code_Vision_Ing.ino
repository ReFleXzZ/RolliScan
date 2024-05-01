#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#include "./Entfernung.h"
#include "./Lichter.h"
#ifdef __AVR__
#endif

const unsigned long event = 1000;  // Setzt var event auf 1 Sekunde
unsigned long voher = 0;           // Setzt die Anfangszeit

// LEDRing -> Name des LED-Rings
int red = 255;  // Rot
int green = 0;  // Grün
int blue = 0;   // Blau

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // Portangabe
  // put your setup code here, to run once:
  pinMode(trigger, OUTPUT);  // Definiere trigger Pin als Sender
  // setBrightness(0..255)
  pinMode(4, INPUT_PULLUP);
  strip.begin();  // Initialize NeoPixel strip object (REQUIRED)
  strip.show();   // Initialize all pixels to 'off'
}

void loop() {
  delay(100);
  unsigned long gerade = millis();
  if (gerade - voher >= event) {
    Entfernung();
    LED();
  }
}
