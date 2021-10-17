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
bool centerTape = true;
int fullSpeed = 35;
int minSpeed = 35;
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
  centerTape = (analogRead(A2)>sensorSplit);

  if (isRunning) {
    if (centerTape) {
      rightMotor->run(BACKWARD);
      leftMotor->run(BACKWARD);
      leftMotor->setSpeed(fullSpeed + leftTape * speedFactor - rightTape * speedFactor);
      rightMotor->setSpeed(fullSpeed - leftTape * speedFactor + rightTape * speedFactor);
    } else {
      leftMotor->setSpeed(minSpeed);
      rightMotor->setSpeed(minSpeed);
      if (leftTape) {
        leftMotor->run(FORWARD);
        rightMotor->run(BACKWARD);
      } else if (rightTape) {
        leftMotor->run(BACKWARD);
        rightMotor->run(FORWARD);
      } else {
        leftMotor->run(FORWARD);
        rightMotor->run(FORWARD);
        delay(250 * 35 / minSpeed);
      }

    }
  } else {
    rightMotor->run(RELEASE);
    leftMotor->run(RELEASE);
    
   
  }

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
  else if (input == "snail"){
    fullSpeed = 35;
    return "snail";
  }
  else if (input == "normal"){
    fullSpeed = 50;
    return "normal";
  }  
 else if (input == "extreme"){
    fullSpeed = 70;
    return "xtreme";
  }
  else {
    fullSpeed = input.toInt();
    Serial.print(fullSpeed);
    return "Set Speed";
  }
}
