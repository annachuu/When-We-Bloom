#include <MobaTools.h>

#define SERVO_PIN1 10
#define SERVO_PIN2 11
#define SERVO_PIN3 12

#define TRIG_PIN 2
#define ECHO_PIN 3

MoToServo myServo1;
MoToServo myServo2;
MoToServo myServo3;

int startPos = 0;
int stressAngle = 70;

// stage distance ranges (cm)
int stage1_far = 90;
int stage1_close = 60;

int stage2_far = 60;
int stage2_close = 40;

int stage3_far = 40;
int stage3_close = 20;

// // Distance thresholds (in cm)
// int farDistance = 50;     // fully closed
// int closeDistance = 30;   // fully open

// Servo speed
int servoSpeed = 50; // high num means faster

int currentTarget = startPos;


void setup() 
{
  myServo1.attach(SERVO_PIN1);
  myServo2.attach(SERVO_PIN2);
  myServo3.attach(SERVO_PIN3);
  
  myServo1.setSpeed(servoSpeed);
  myServo1.setSpeed(servoSpeed);
  myServo2.setSpeed(servoSpeed);
  
  myServo1.write(startPos);
  myServo2.write(startPos);
  myServo3.write(startPos);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}


void loop() 
{
  long distance = getDistance();
  int targetAngle;

  // Stage 0 (very far)
  if (distance >= stage1_far)
  {
    targetAngle = 0;
  }
  // Stage 1 (0–25°)
  else if (distance < stage1_far && distance >= stage1_close)
  {
    targetAngle = map(distance, stage1_far, stage1_close, 0, 25);
  }
  // Stage 2 (25–50°)
  else if (distance < stage2_far && distance >= stage2_close)
  {
    targetAngle = map(distance, stage2_far, stage2_close, 25, 50);
  }
  // Stage 3 (50–70°)
  else if (distance < stage3_far && distance >= stage3_close)
  {
    targetAngle = map(distance, stage3_far, stage3_close, 50, 70);
  }
  // Very close means fully open
  else
  {
    targetAngle = stressAngle;
  }
  
  // Only update if target changes
  if (targetAngle != currentTarget)
  {
    myServo1.write(targetAngle);
    myServo2.write(targetAngle);
    myServo3.write(targetAngle);
    
    currentTarget = targetAngle;
  }

  delay(100);  // small delay for stability
}


// Function to read distance from ultrasonic sensor
long getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;  // convert to cm

  return distance;
}
