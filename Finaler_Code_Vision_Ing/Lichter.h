int BUTTON_PIN = 5;

//Pin, an dem der LED Ring angeschlossen ist
#define PIXEL_PIN 6

// Anzahl der LEDs → muss angepasst werden
# define PIXEL_COUNT 24

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState = HIGH;
int     mode     = 0;    // Currently-active animation mode, 0-9
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

void LED() {
  // Get current button state.
  bool newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if ((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {     // Yes, still low
      if (++mode > 1) mode = 0; // Advance to next mode, wrap around after #1
      switch (mode) {          // Start the new animation...
        case 0:
          colorWipe(strip.Color(  0,   0,   0), 50);    // Black/off
          break;
        case 1:
          colorWipe(strip.Color(255,   255,   255), 50);    // White
          //colorWipe(strip.Color(138,43,226),50); //andere Farben zum Spaß & ausprobieren.
          break;

      }
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;
}
