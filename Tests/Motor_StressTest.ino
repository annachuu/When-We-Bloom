// This program was used to stress test the servo motor
#include <Servo.h>

Servo myServo;

int startPos = 0;      // starting position
int stressAngle = 80;  // how far the servo moves

void setup() 
{
  myServo.attach(10);  // attach to pin 10
  myServo.write(startPos); // startinf at 0 degrees
}

void loop() 
{
  myServo.write(stressAngle);  // move to 80 degrees
  delay(30000);                 // wait 1 second

  myServo.write(startPos);     // move back to 0 degrees
  delay(30000);                 // wait 1 second

  delay(30000);                // pause for 30 seconds

  // repeats to see how long it will last (hoping a couple hours)
}
