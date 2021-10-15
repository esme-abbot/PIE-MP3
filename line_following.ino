#include <Adafruit_MotorShield.h>

/*
This is a test sketch for the Adafruit assembled Motor Shield for Arduino v2
It won't work with v1.x motor shields! Only for the v2's with built in PWM
control

For use with the Adafruit Motor Shield v2
---->  http://www.adafruit.com/products/1438
*/

#include <Adafruit_MotorShield.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *rightMotor = AFMS.getMotor(2);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(3);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);
bool isRunning = false;
bool leftTape = true;
bool rightTape = true;
int fullSpeed = 30;
int halfSpeed = 25;
int sensorSplit = 400;
int speedFactor = fullSpeed;

void setup() {
  Serial.begin(115200);           // set up Serial library at 9600 bps

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    while (1);
  }


  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(fullSpeed);
  rightMotor->run(BACKWARD);
  // turn on motor
  rightMotor->run(RELEASE);
  leftMotor->setSpeed(fullSpeed);
  leftMotor->run(BACKWARD);
  // turn on motor
  leftMotor->run(RELEASE);
}

void loop() {
  
  if (Serial.available()){
     String s = Serial.readStringUntil('\n');
     s.trim();
     String returnMessage = reactToInput(s);
     Serial.println(returnMessage);
  }

  leftTape = (analogRead(A1)>sensorSplit);
  rightTape = (analogRead(A0)>sensorSplit);

  if (isRunning){
    rightMotor->run(BACKWARD);
    leftMotor->run(BACKWARD);
    /*
    if (leftTape){
      leftMotor->setSpeed(halfSpeed + leftTape);
    } else {
      leftMotor->setSpeed(fullSpeed);
    }
    if (rightTape){
      rightMotor->setSpeed(halfSpeed);
    } else {
      rightMotor->setSpeed(fullSpeed);
    }
    */
  } else {
    rightMotor->run(RELEASE);
    leftMotor->run(RELEASE);
   
  }

  leftMotor->setSpeed(fullSpeed + leftTape * speedFactor - rightTape * speedFactor);
  rightMotor->setSpeed(fullSpeed - leftTape * speedFactor + rightTape * speedFactor);
  //leftMotor->setSpeed(25);
  //rightMotor->setSpeed(25);

}

String reactToInput(String input){
  if (input == "stop"){
    isRunning = false;
    return "stopping";
  }
  else if (input == "go"){
    isRunning = true;
    return "going";
  }
  else {
    return "I'm confused";
  }
}

