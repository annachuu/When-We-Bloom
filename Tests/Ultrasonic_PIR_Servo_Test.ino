// This program is used to test the Ultrasonic, PIR, and SERVO Motors altogether
// first attempt allow gradual feedback with closer proximity

#include <Servo.h>

#define TRIG_PIN 2
#define ECHO_PIN 3
#define PIR_PIN 4
#define SERVO_PIN 10

#define FAR_DISTANCE 50     // at 50 = fully closed
#define FULL_OPEN_DIST 30   // at 30 = fully open

Servo myServo;

bool systemActive = false;

int currentAngle = 0;
int targetAngle = 0;

void setup() 
{
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(0);
}

void loop() 
{
  // activate system when PIR detects motion
  if (digitalRead(PIR_PIN) == HIGH)
  {
    systemActive = true;
    Serial.println("Motion detected - Ultrasonic now active");
  }

  if (systemActive)
  {
    float distance = readDistance();  // distance in centimeters

    if (distance > 0)
    {
      // IF closer than or equal to 30, then fully open
      if (distance <= FULL_OPEN_DIST)
      {
        targetAngle = 180;
      }
      // IF between 30 and 50, then proportional opening
      else if (distance > FULL_OPEN_DIST && distance <= FAR_DISTANCE)
      {
        targetAngle = map(distance, FAR_DISTANCE, FULL_OPEN_DIST, 0, 180);
      }
      // ELSE more than 50, then fully closed
      else
      {
        targetAngle = 0;
      }

      targetAngle = constrain(targetAngle, 0, 180);
    }

    // gradual movement (stops when person stops)      !! note: need more work on
    if (currentAngle < targetAngle)
    {
      currentAngle++;
      myServo.write(currentAngle);
    }
    else if (currentAngle > targetAngle)
    {
      currentAngle--;
      myServo.write(currentAngle);
    }
  }

  delay(15);  // controls movement speed
}


// Ultrasonic function (returns cm)
float readDistance() 
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);

  if (duration == 0)
  {
    return -1;
  }

  float distance = (duration * 0.0343) / 2;  // cm

  Serial.print("Distance (cm): ");        // !! note: double check units next time
  Serial.println(distance);

  return distance;
}
