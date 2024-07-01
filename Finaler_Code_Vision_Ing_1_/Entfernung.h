int trigger = 3; //Sender des Signals auf Pin 3
int echo = 2; //Empfänger des Signals auf Pin 2
long dauer = 0; //var für Entfernungsberechnung in cm
long entfernung = 0; // Entfernung in cm nach Berechnung
int speaker = 4; //Lautspecher für Piepton auf Pin 12/Verändert von 7 wegen dem Ausprobieren der Tastsensoren
#define PIXEL_PIN 12
unsigned long gerade = millis();
unsigned long voher2 = 0;
const unsigned long ton = 100;
bool tastere;

bool an_rechts;

// Anzahl der LEDs → muss angepasst werden
#define PIXEL_COUNT 24

Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
void colorWipe(uint32_t color, int wait) {
   for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
  }

bool oldState = HIGH;
int     mode     = 0;
int lampe = 0;


void Entfernung () {

  if (digitalRead(5) == 1) // rechter Taster für Ultraschall
  {
    Serial.println("Taste rechts");
    if (tastere)
    {
      tastere = false;
      Serial.println("rechts an");

    }
    else
    {
      tastere = true;
      Serial.println("rechs aus");


    }
  }
  if (tastere == true) {
    colorWipe(strip.Color(0,   255,   51), 20);
    digitalWrite(trigger, HIGH); // Trigger sendet Signal nach Außen
    delayMicroseconds(10);
    digitalWrite(trigger, LOW); // Trigger wird ausgeschalten

    dauer = pulseIn(echo, HIGH); // dauer wird mit Infos von Echo beschrieben

    entfernung = (dauer / 2) * 0.03432; // Entfernung wird berechnet

    //  while (entfernung >= 500 || entfernung <= 0) { // Kontrolle ob entfernung außerhalb eines bestimmten Bereiches liegt
    //    Serial.println("Kein Messwert"); // Ausgabe für wenn Außerhalb des Messbereiches
    //    Serial.print(entfernung); // Ausgabe der Entfernung in cm
    //    Serial.println("cm");}
    if (entfernung <= 50) {
      colorWipe(strip.Color(255,   0,   0), 50);
      tone(speaker, 300);// Tonsequenz Ablauf für wenn unter 50 cm
      delay(50);//Tondauer in Millisekunden
      noTone(speaker);//Ausschalten des Passiven Lautsprechers
      delay(100);//Pause zwischen Ausschalten und neu Anschalten
      tone(speaker, 300);// Tonsequenz Ablauf für wenn unter 50 cm
      delay(50);//Tondauer in Millisekunden
      noTone(speaker);//Ausschalten des Passiven Lautsprechers
      delay(100);//Pause zwischen Ausschalten und neu Anschalten
      tone(speaker, 400);// Tonsequenz Ablauf für wenn unter 50 cm
      delay(50);//Tondauer in Millisekunden
      noTone(speaker);//Ausschalten des Passiven Lautsprechers
    }
    else {
      noTone(speaker); // Wenn über 50 cm kein Ton
      colorWipe(strip.Color(0,   0,   0), 50);
    }

  }
  else {
      colorWipe(strip.Color(0,   0,   50), 50);
    }
  }
