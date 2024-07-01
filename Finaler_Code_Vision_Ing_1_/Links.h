bool tastle=true;
int sensle;
bool an_links;

void Links() {
sensle=analogRead(A3);  //linker Handgriff
//Serial.println(sensle);
delay(100);
if (sensle<600) 
{
  an_links=true;
  digitalWrite(8,HIGH);
}
else
{
  an_links=false;
  digitalWrite(8,LOW);
}

if (digitalRead(6)==1) // linke Taster für helles Licht
{
  Serial.println("Taste links");
  if (tastle) 
  {
    tastle=false;
    digitalWrite(7,HIGH);
    delay(100);
  }
  else
  {
    tastle=true;
    digitalWrite(7,LOW);
    delay(100);
  }
  delay(100);
}


}
