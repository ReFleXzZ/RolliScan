
int sensre;



void Rechts() {
sensre=analogRead(A4);  //linker Handgriff
Serial.println(sensre);
delay(100);
if (sensre<600) 
{
  an_rechts=true;
}
else
{
  an_rechts=false;
}
}
