// This program is used to test ultrasonic sensor wire length stability test
// testing maximum M-F jumper wire extension before signal becomes unstable

#define TRIG_PIN 8
#define ECHO_PIN 7

unsigned long totalReadings = 0;
unsigned long failedReadings = 0;

void setup() 
{
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.println("Ultrasonic Wire Extension Test Started");
  Serial.println("------------------------------------");
}

void loop() 
{
  totalReadings++;

  // Trigger ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  
  // waiting for echo (timeout after 30ms == about 5 meters)
  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0) 
  {
    failedReadings++;

    Serial.println("FAILED - No echo detected");
  } 
  else 
  {
    float distance = (duration * 0.0343) / 2;

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print(" cm");

    Serial.print(" | Echo time: ");
    Serial.print(duration);
    Serial.print(" us");
    
    Serial.print(" | Success rate: ");
    Serial.print(100.0 * (totalReadings - failedReadings) / totalReadings);
    Serial.println("%");
  }

  // print failure statistics every 20 readings
  if (totalReadings % 20 == 0)
  {
    Serial.println("------------------------------");
    Serial.print("Total readings: ");
    Serial.println(totalReadings);

    Serial.print("Failed readings: ");
    Serial.println(failedReadings);

    Serial.print("Failure rate: ");
    Serial.print(100.0 * failedReadings / totalReadings);
    Serial.println("%");

    Serial.println("------------------------------");
  }

  delay(100);
}
