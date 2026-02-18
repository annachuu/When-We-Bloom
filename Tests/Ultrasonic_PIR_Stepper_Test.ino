#include <Stepper.h>

#define STEPS 2038             // steps per full revolution
#define TRIG_PIN 2
#define ECHO_PIN 3
#define PIR_PIN 4
#define DISTANCE_THRESHOLD 10
#define ABSENCE_DELAY 3000     // 3 seconds

Stepper stepper(STEPS, 8, 10, 9, 11);

bool handPresent = false;      // hand currently close
bool actionDone = false;       // 360° rotation done
unsigned long handGoneTime = 0;
bool lastHumanDetected = false; // for state change printing

void setup() 
{
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  stepper.setSpeed(5); // RPM
}

void loop() 
{
  bool humanDetected = digitalRead(PIR_PIN) == HIGH;

  // Check ultrasonic IF human detected
  if (humanDetected) 
  {

    if (!lastHumanDetected) 
    {
      Serial.println("PIR motion detected: human presence confirmed");
    }
    lastHumanDetected = true;

    float distance = readDistance();

    // HAND CLOSE -> rotate forward
    if (distance > 0 && distance < DISTANCE_THRESHOLD) 
    {
      if (!handPresent) 
      {
        handPresent = true;
        actionDone = false;
        Serial.println("Hand detected: preparing to rotate forward 360deg");
      }

      if (!actionDone) 
      {
        Serial.println("Rotating 360° forward");
        stepper.step(STEPS);     // forward rotation
        actionDone = true;
      }
    }

    // HAND AWAY → pause 3s then rotate backward
    else 
    {
      if (handPresent) 
      {
        handPresent = false;
        actionDone = false;
        handGoneTime = millis();
        Serial.println("Hand removed: waiting 3secs before reverse rotation");
      }

      if (!handPresent && !actionDone && (millis() - handGoneTime >= ABSENCE_DELAY)) 
      {
        Serial.println("Rotating 360° backward");
        stepper.step(-STEPS);    // reverse rotation
        actionDone = true;
      }
    }

  } 
  else 
  {
    if (lastHumanDetected) 
    {
      Serial.println("No human detected by PIR, ignoring ultrasonic");
    }
    lastHumanDetected = false;
  }

  delay(50);
}


// Ultrasonic Function
float readDistance() 
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 20000);   // 20ms timeout
  if (duration == 0) 
  {
    return -1;
  }

  float distance = (duration * 0.034) / 2; // cm
  Serial.print("Distance: ");
  Serial.println(distance);
  return distance;
}
