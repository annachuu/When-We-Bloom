// Difference: when in one place, it opens (no twitches like main.ino),but leave then it will close.
//             main.ino will twitch when user stands still, but it has smoother moments otherwise

#include <MobaTools.h>

#define SERVO_PIN 10
#define TRIG_PIN 2
#define ECHO_PIN 3

MoToServo myServo;

int startPos = 0;
int stressAngle = 70;

// Distance limits
int farDistance = 50;
int closeDistance = 30;

// Servo speed
int servoSpeed = 30;

// Track positions
int currentTarget = startPos;

// Track movement
long previousDistance = 0;
int tolerance = 1;  // ignore tiny fluctuations in cm

void setup() 
{
  myServo.attach(SERVO_PIN);
  myServo.setSpeed(servoSpeed);
  myServo.write(startPos);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  previousDistance = getDistance();
}

void loop() 
{
  long distance = getDistance();

  if (distance <= 0) 
    return;

  if (distance <= closeDistance)
  {
    if (currentTarget < stressAngle)
    {
      currentTarget += 2;
      myServo.write(currentTarget);
    }
    // if already at 70deg, then hold position and do nothing
  }

  // holding
  else if (distance > closeDistance && distance < farDistance)
  {
    // Do nothing → keeps current position (including 70°)
  }

  // close when far away
  else if (distance >= farDistance)
  {
    currentTarget = max(currentTarget - 2, startPos);
    myServo.write(currentTarget);
  }

  previousDistance = distance;

  delay(100);
}


long getDistance()
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;

  return distance;
}
