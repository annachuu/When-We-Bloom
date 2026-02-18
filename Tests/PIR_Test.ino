int state = 0;
void setup()
{
	pinMode(2,INPUT);
  	pinMode(LED_BUILTIN, OUTPUT);
  	Serial.begin(9600);
}

void loop()
{
  state = digitalRead(2);
  
  if (state==HIGH)
  {
    digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("Sensor Activated.");
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
  delay(5); // Delay a little bit to improve simulation performance
}
