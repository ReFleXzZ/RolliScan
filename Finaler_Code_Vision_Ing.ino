#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
const unsigned long event = 1000;//Setzt var event auf 1 Sekunde

unsigned long voher = 0; //Setzt die Anfangszeit

int BUTTON_PIN = 4;

int trigger = 9; //Sender des Signals auf Pin 9

int echo = 8; //Empfänger des Signals auf Pin 8

int speaker = 12; //Lautspecher für Piepton auf Pin 12/Verändert von 7 wegen dem Ausprobieren der Tastsensoren

long dauer = 0; //var für Entfernungsberechnung in cm

long entfernung = 0; // Entfernung in cm nach Berechnung
//Pin, an dem der LED Ring angeschlossen ist
#define PIXEL_PIN 13

// Anzahl der LEDs → muss angepasst werden
# define PIXEL_COUNT 24
// LEDRing -> Name des LED-Rings
int red = 255; //Rot
int green = 0; //Grün
int blue = 0;  //Blau
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //Port Angabe
  // put your setup code here, to run once:
  pinMode(trigger, OUTPUT); //Definiere trigger Pin als Sender
  // setBrightness(0..255)
  pinMode(4,INPUT_PULLUP);
    strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
}

void loop() {
  unsigned long gerade = millis();
  if (gerade - voher >= event) {
    Entfernung();
    LED();
  }
  // put your main code here, to run repeatedly:

}
