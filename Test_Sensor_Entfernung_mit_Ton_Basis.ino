int trigger=9; //Sender des Signals auf Pin 9

int echo=8; //Empfänger des Signals auf Pin 8

int speaker=7; //Lautspecher für Piepton auf Pin 7

long dauer=0; //var für Entfernungsberechnung in cm

long entfernung=0; // Entfernung in cm nach Berechnung

void setup() {
  Serial.begin(9600); //Port Angabe
  // put your setup code here, to run once:
  pinMode(trigger, OUTPUT); //Definiere trigger Pin als Sender
  pinMode(echo, INPUT);// Definiere Echo Pin als Empfänger

}
void loop() {




  digitalWrite(trigger, LOW);
  delay(10);

  digitalWrite(trigger, HIGH);//Trigger sendet Signal nach Außen
  delay(100);

  digitalWrite(trigger, LOW);//Trigger wird ausgeschalten

  dauer=pulseIn(echo, HIGH);//dauer wird mit Infos von Echo beschrieben

  entfernung= (dauer/2)*0.03432;//Enrfernung wird berechnet

  if (entfernung >= 500 || entfernung <=0){//Kontrolle ob entfernung außerhalb eines bestimmten Bereiches liegt
    Serial.println("Kein Messwert");//Ausgabe für wenn Außerhalb des Messbereiches
  }
 else {
  Serial.print(entfernung);//Ausgabe der Entfernung in cm
  Serial.println("cm");
  if (entfernung <=50){//Test ob in Bereich unter 50 cm
    tone(speaker, 100);// Tonsequenz Ablauf für wenn unter 50 cm
    delay(100);//Tondauer in Millisekunden
    noTone(speaker);//Ausschalten des Passiven Lautsprechers
    delay(100);//Pause zwischen Ausschalten und neu Anschalten
  }
  else{
    noTone(speaker);//Wenn über 50 cm kein Ton
  }
  }
}
  

  
