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

// Servo speed
int servoSpeed = 50; // high num means faster

// Movement threshold
long lastDistance = 0;
int movementThreshold = 5;

void setup() 
{
  Serial.begin(9600);
  
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

  lastDistance = getDistance();
}


void loop() 
{
  long distance = getDistance();
  int targetAngle;
  int stage;

 

  // Stage 0 (very far)
  if (distance >= stage1_far)
  {
    stage = 0;
    targetAngle = 0;
  }
  // Stage 1 (0–25°)
  else if (distance < stage1_far && distance >= stage1_close)
  {
    stage = 1;
    targetAngle = map(distance, stage1_far, stage1_close, 0, 25);
  }
  // Stage 2 (25–50°)
  else if (distance < stage2_far && distance >= stage2_close)
  {
    stage = 2;
    targetAngle = map(distance, stage2_far, stage2_close, 25, 50);
  }
  // Stage 3 (50–70°)
  else if (distance < stage3_far && distance >= stage3_close)
  {
    stage = 3;
    targetAngle = map(distance, stage3_far, stage3_close, 50, maxAngle);
  }
  else
  {
    stage = 3;
    targetAngle = maxAngle; // cap at 70°
  }
  
  // move if distance change significantly
  if (abs(distance - lastDistance) >= movementThreshold)
  {
    Serial.println("------------------------------");
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    Serial.print("Stage: ");
    Serial.println(stage);

    Serial.print("Target Angle: ");
    Serial.println(targetAngle);

    myServo1.write(targetAngle);
    myServo2.write(targetAngle);
    myServo3.write(targetAngle);

    lastDistance = distance;
  }
  else
  {
    Serial.print("IGNORED (small movement) -> ");
    Serial.println(distance);
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
