// These are the pin connections for the motor controller, they won't change.
const byte A_EN = 2;    //right wheel
const byte A_RPWM = 3;    //(forward)
const byte A_DIS = 4;    
const byte A_LPWM = 11;   //(reverse)

const byte B_EN = 8;   //left wheel
const byte B_RPWM = 9;   //(forward)
const byte B_DIS = 7;   
const byte B_LPWM = 10;  //(reverse)
const byte goButton = 14; //this button will execute our functions


  
  // Let's declare some things first.  Leave these ones alone...
#define pinMode(A_EN, OUTPUT);
#define pinMode(A_DIS, OUTPUT);
#define pinMode(B_EN, OUTPUT);
#define pinMode(B_DIS, OUTPUT);
  /** PWM pin configurate */
#define pinMode(A_RPWM, OUTPUT);
#define pinMode(A_LPWM, OUTPUT);
#define pinMode(B_RPWM, OUTPUT);
#define pinMode(B_LPWM, OUTPUT);
#define pinMode(goButton, INPUT);
  

void forward (int duration, byte speed)
{
  Serial.println("Forward");
  leftMotorF(speed);
  rightMotorF(speed);
  delay (duration);
  stop();
}

void reverse (int duration, byte speed)
{
  Serial.println ("Reverse");
  leftMotorR(speed);
  rightMotorR(speed);
  delay (duration);
  stop();
}

void stop()
{
  Serial.println ("Stop");
  digitalWrite(A_EN, LOW);
  digitalWrite(B_EN, LOW);
  digitalWrite(A_RPWM, HIGH);
  digitalWrite(A_LPWM, HIGH);
  digitalWrite(B_RPWM, HIGH);
  digitalWrite(B_LPWM, HIGH);
  delay(100);
  digitalWrite(A_EN, HIGH);
  digitalWrite(B_EN, HIGH);
}

void turnRight(int duration, int speed)   //add gyro code later angle = seconds of turn
{
  Serial.println ("turnRight");
  leftMotorF (speed);
  rightMotorR (speed);
  delay(duration);
  stop();
}

void turnLeft(int duration, int speed)   //add gyro code later angle = seconds of turn
{
  Serial.println ("turnLeft");
  leftMotorR (speed);
  rightMotorF (speed);
  delay(duration);
  stop();
}

void leftMotorF(byte speed)
{
  Serial.println ("leftMotorF");
  digitalWrite(A_RPWM, HIGH); //left motor forward
  analogWrite(A_LPWM, 255-speed);
}

void rightMotorF (byte speed)
{
  Serial.println ("rightMotorF");
  digitalWrite(B_LPWM, HIGH);  //right motor forward
  analogWrite(B_RPWM, 255-speed);
}

void leftMotorR(byte speed)
{
  Serial.println ("leftMotorR");
  analogWrite(A_RPWM, (255-speed)); //left motor reverse
  digitalWrite(A_LPWM, HIGH);
}

void rightMotorR(byte speed)
{
  Serial.println ("rightMotorR");
  digitalWrite(B_RPWM, HIGH);  //right motor reverse
  analogWrite(B_LPWM, (255-speed));
}

void wait()
{
    while  (digitalRead(goButton) == LOW);
  {
    stop();
  }
}


/*
Channel A
EN pin 2
RPWM pin 3
DIS pin 4
LPWM pin 11

Channel B
EN pin 8
RPWM pin 9
DIS pin 7
LPWM pin 10

Rotate forward: EN = HIGH, RPWM = PWM, LPWM = HIGH, DIS = vacant
Rotate reverse: EN = HIGH, RPWM = HIGH, LPWM = PWM, DIS = vacant
Stop and brake: EN = HIGH, RPWM = HIGH, LPWM = HIGH, DIS = vacant
Stop but not brake: EN = 0, RPWM = HIGH, LPWM = HIGH, DIS = vacant
Prohibit : EN = X, RPWM = X, LPWM = X, DIS = HIGH

*/
