// This program was used to stress test the servo motor
// Version 1: testing 3D model and motor duration

#include <Servo.h>

Servo myServo;

int startPos = 0;      // starting position
int stressAngle = 90;  // how far the servo moves

void setup() 
{
  myServo.attach(10);  // attach to pin 10
  myServo.write(startPos); // startinf at 0 degrees
}

void loop() 
{
  myServo.write(stressAngle);  // move to 80 degrees
  delay(1000);                 // wait 1 second

  myServo.write(startPos);     // move back to 0 degrees
  delay(5000);                 // pause for 5 seconds

  // repeats to see how long it will last (hoping a couple hours)
}
