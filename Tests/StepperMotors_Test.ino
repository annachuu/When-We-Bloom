// This program was used to test the stepper motors
#include <Stepper.h>                   // the stepper library

#define STEPS 2038                     // defining # of steps per revolution for motor
Stepper stepper(STEPS, 8, 9, 10, 11);  // initialize stepper object and set pin connections (IN1, IN3, IN2, IN4)

void setup() 
{
}

void loop() 
{
  stepper.setSpeed(5);  // Rotate clockwise at 5 RPM
  stepper.step(STEPS);  // Rotate one full revolution clockwise
  delay(1000);          // Wait for 1 second
}
