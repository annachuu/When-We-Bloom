// !!! Modified Program used for Exhibition !!!

// Difference: uses more sensors and motors (per circuit)

#include <MobaTools.h>

// servo pins
#define SERVO_PIN0 8
#define SERVO_PIN1 9
#define SERVO_PIN2 10
#define SERVO_PIN3 11
#define SERVO_PIN4 12
#define SERVO_PIN5 13

// sensor 1
#define TRIG_PIN0 2
#define ECHO_PIN0 3

// sensor 2
#define TRIG_PIN1 4
#define ECHO_PIN1 5

// sensor 3
#define TRIG_PIN2 6
#define ECHO_PIN2 7

// sensor 4
// scratch 4th sensor
// possibility: connect to analog pin A0 (TRIG_PIN3),
//                                    A1 (ECHO_PIN3)
//              then set pinMode A0 (TRIG_PIN3) to OUTPUT,
//                               A1 (ECHO_PIN3) to INPUT

//objects of servos
MoToServo myServo0;
MoToServo myServo1;
MoToServo myServo2;
MoToServo myServo3;
MoToServo myServo4;
MoToServo myServo5;


//global variables
int startPos = 0;
int maxAngle = 70;

int stage1_far = 95;
int stage1_close = 70;

int stage2_far = 70;
int stage2_close = 55;

int stage3_far = 55;
int stage3_close = 40;

int servoSpeed = 50;
int movementThreshold = 5;

#define MAX_VALID_DISTANCE 150  // ignore anything beyond this distance

// last tracked distance
long lastDistance0 = 0;
long lastDistance1 = 0;
long lastDistance2 = 0;

void setup() 
{
  Serial.begin(9600);

  // Attach servos
  myServo0.attach(SERVO_PIN0);
  myServo1.attach(SERVO_PIN1);
  myServo2.attach(SERVO_PIN2);
  myServo3.attach(SERVO_PIN3);
  myServo4.attach(SERVO_PIN4);
  myServo5.attach(SERVO_PIN5);

  
  // Set speed
  myServo0.setSpeed(servoSpeed);
  myServo1.setSpeed(servoSpeed);
  myServo2.setSpeed(servoSpeed);
  myServo3.setSpeed(servoSpeed);
  myServo4.setSpeed(servoSpeed);
  myServo5.setSpeed(servoSpeed);

  
  // Start at 0deg
  myServo0.write(startPos);
  delay(100);
  myServo1.write(startPos);
  delay(100);
  myServo2.write(startPos);
  delay(100);
  myServo3.write(startPos);
  delay(100);
  myServo4.write(startPos);
  delay(100);
  myServo5.write(startPos);
  delay(100);

  
  // Ultrasonic pins
  pinMode(TRIG_PIN0, OUTPUT);
  pinMode(ECHO_PIN0, INPUT);

  pinMode(TRIG_PIN1, OUTPUT);
  pinMode(ECHO_PIN1, INPUT);

  pinMode(TRIG_PIN2, OUTPUT);
  pinMode(ECHO_PIN2, INPUT);

  // Initial readings starst at 0
  lastDistance0 = 0;
  lastDistance1 = 0;
  lastDistance2 = 0;
}


void loop() 
{
  long distance0 = getDistance(TRIG_PIN0, ECHO_PIN0);
  delay(20);                                          // prevent sensors sensing each other's sound wave echos
  long distance1 = getDistance(TRIG_PIN1, ECHO_PIN1);
  delay(20);
  long distance2 = getDistance(TRIG_PIN2, ECHO_PIN2);

  
  // sensor 0 controls motor 0 and 1
  if (distance0 != -1)
  {
    int angle0 = calculateAngle(distance0);

    if (distance0 < stage1_far && abs(distance0 - lastDistance0) >= movementThreshold)
    {
      myServo0.write(angle0);
      myServo1.write(angle0);

      Serial.println("=== SENSOR 0 ACTIVE ===");
      Serial.print("Distance: ");
      Serial.println(distance0);
      Serial.print("Angle: ");
      Serial.println(angle0);

      lastDistance0 = distance0;
    }
  }
  else
  {
    // No object → STOP
    myServo0.write(0);
    myServo1.write(0);
  }

  // sensor 1 controls motor 2 and 3
  if (distance1 != -1)
  {
    int angle1 = calculateAngle(distance1);

    if (distance1 < stage1_far && abs(distance1 - lastDistance1) >= movementThreshold)
    {
      myServo2.write(angle1);
      myServo3.write(angle1);

      Serial.println("=== SENSOR 1 ACTIVE ===");
      Serial.print("Distance: ");
      Serial.println(distance1);
      Serial.print("Angle: ");
      Serial.println(angle1);

      lastDistance1 = distance1;
    }
  }
  else
  {
    // No object → STOP
    myServo2.write(0);
    myServo3.write(0);
  }

  // sensor 2 controls motor 4 and 5
  if (distance2 != -1)
  {
    int angle2 = calculateAngle(distance2);

    if (distance2 < stage1_far && abs(distance2 - lastDistance2) >= movementThreshold)
    {
      myServo4.write(angle2);
      myServo5.write(angle2);

      Serial.println("=== SENSOR 2 ACTIVE ===");
      Serial.print("Distance: ");
      Serial.println(distance2);
      Serial.print("Angle: ");
      Serial.println(angle2);

      lastDistance2 = distance2;
    }
  }
  else
  {
    // No object → STOP
    myServo4.write(0);
    myServo5.write(0);
  }

  delay(50);                          // CHANGE: 100 to 50
}


// Function for ultrasonic sensor
long getDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout

  if (duration == 0) return -1; // no signal

  long distance = duration * 0.034 / 2;

  if (distance > MAX_VALID_DISTANCE) return -1; // out of range

  return distance;
}

// Stages
int calculateAngle(long distance)
{
  if (distance >= stage1_far)
  {
    return 0;
  }
  else if (distance >= stage1_close)
  {
    return map(distance, stage1_far, stage1_close, 0, 25);
  }
  else if (distance >= stage2_close)
  {
    return map(distance, stage2_far, stage2_close, 25, 50);
  }
  else if (distance >= stage3_close)
  {
    return map(distance, stage3_far, stage3_close, 50, maxAngle);
  }
  else
  {
    return maxAngle;
  }
}
