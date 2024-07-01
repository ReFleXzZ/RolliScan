#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>  // Required for 16 MHz Adafruit Trinket
#include "./Entfernung.h"
#include "./Links.h"
#include "./Rechts.h"
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
boolean hasRun = false;


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
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(13, HIGH);
 
  strip.begin();  // Initialize NeoPixel strip object (REQUIRED)
  strip.show();   // Initialize all pixels to 'off'
}
void loop() {
  if(hasRun == false){
    int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for (int a = 0; a < 10; a++) { // Repeat 30 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(100);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
   for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(1000);  // Pause for a moment
  }
  }
  hasRun = true;
  const unsigned long event = 100;// Setzt var event auf 0,1 Sekunden
  unsigned long voher = 0;           // Setzt die Anfangszeit
  unsigned long gerade = millis();
  if (gerade - voher >= event) {
    Entfernung();
    Links();
    Rechts();
    gerade = voher;
    if (an_links == true && an_rechts == true) {
      digitalWrite(10, HIGH);
    }
    else {
      digitalWrite(10, LOW);
    }
  }
}
