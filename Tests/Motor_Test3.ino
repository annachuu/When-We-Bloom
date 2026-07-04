// This program was used to reset all motors and test models
// Version 3: rest and review

#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;


int startPos = 0;      // starting position


void setup() 
{
  servo1.attach(8);         // attach to pin 8 - 13
  servo2.attach(9);  
  servo3.attach(10);  
  servo4.attach(11);  
  servo5.attach(12); 
  servo6.attach(13); 


  servo1.write(startPos);     // startinf at 0 degrees
  servo2.write(startPos);
  servo3.write(startPos);
  servo4.write(startPos);
  servo5.write(startPos);
  servo6.write(startPos);
}


void loop() 
{
  servo1.write(startPos);     // move back to 0 degrees
  servo2.write(startPos);
  servo3.write(startPos);
  servo4.write(startPos);
  servo5.write(startPos);
  servo6.write(startPos);

  servo1.write(40);           // move to 40 degrees
  servo2.write(40);
  servo3.write(40);
  servo4.write(40);
  servo5.write(40);
  servo6.write(40);
  delay(1000);                 // wait 1 second = 1000
  servo1.write(startPos);     // move back to 0 degrees
  servo2.write(startPos);
  servo3.write(startPos);
  servo4.write(startPos);
  servo5.write(startPos);
  servo6.write(startPos);
  delay(5000);                // pause for 5 seconds


  servo1.write(60);           // move to 60 degrees
  servo2.write(60);
  servo3.write(60);
  servo4.write(60);
  servo5.write(60);
  servo6.write(60);
  delay(1000);                 // wait 1 second = 1000
  servo1.write(startPos);     // move back to 0 degrees
  servo2.write(startPos);
  servo3.write(startPos);
  servo4.write(startPos);
  servo5.write(startPos);
  servo6.write(startPos);
  delay(5000);                // pause for 5 seconds


  servo1.write(80);           // move to 80 degrees
  servo2.write(80);
  servo3.write(80);
  servo4.write(80);
  servo5.write(80);
  servo6.write(80);
  delay(1000);                 // wait 1 second = 1000


  // repeats to see how long it will last (hoping a couple hours)
}
