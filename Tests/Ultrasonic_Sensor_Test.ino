// This program was used to test the ultrasonic sensor

#define TRIG_PIN 8
#define ECHO_PIN 7

void setup() 
{
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void loop() 
{
  // Send a 10-microsecond pulse to trigger the ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Measure pulse width on the echo pin
  long duration = pulseIn(ECHO_PIN, HIGH);

  // IF pulseIn returns 0, THEN echo wasn't detected, so skip the calculation
  if (duration == 0) 
  {
    Serial.println("No echo detected");
  } 
  else 
  {
    // Calculate the distance in centimeters
    float distance = (duration * 0.034) / 2;  // Speed of sound is 0.034 cm/us, and divide by 2 to get the one-way distance
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  
  delay(500); // Wait before the next reading
}
