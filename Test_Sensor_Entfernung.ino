int trigger=9;

int echo=8;

int speaker=7;

long dauer=0;

long entfernung=0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);

}

void loop() {
  digitalWrite(trigger, LOW);
  delay(10);

  digitalWrite(trigger, HIGH);
  delay(1000);

  digitalWrite(trigger, LOW);

  dauer=pulseIn(echo, HIGH);

  entfernung= (dauer/2)*0.03432;

  if (entfernung >= 500 || entfernung <=0){
    Serial.println("Kein Messwert");
  }
 else {
  Serial.print(entfernung);
  Serial.println("cm");
  if (entfernung <=30){
    tone(speaker, 100);
    delay(1000);
    noTone(speaker);
    delay(100);
  }
  else{
    noTone(speaker);
  }
  }
}