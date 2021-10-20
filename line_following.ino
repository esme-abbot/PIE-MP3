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
  }

  leftTape = (analogRead(A1)>sensorSplit);
  rightTape = (analogRead(A0)>sensorSplit);
  centerTape = (analogRead(A2)>sensorSplit);
  Serial.print(millis());
  Serial.print(",");

  if (isRunning) {
    if (centerTape) {
      rightMotor->run(BACKWARD);
      leftMotor->run(BACKWARD);
      leftMotor->setSpeed(fullSpeed + leftTape * speedFactor - rightTape * speedFactor);
      Serial.print(fullSpeed + leftTape * speedFactor - rightTape * speedFactor);
      Serial.print(",");
      rightMotor->setSpeed(fullSpeed - leftTape * speedFactor + rightTape * speedFactor);
      Serial.print(fullSpeed - leftTape * speedFactor + rightTape * speedFactor);
      Serial.print(",");      
    } else {
      leftMotor->setSpeed(fullSpeed);
      rightMotor->setSpeed(fullSpeed);
      if (leftTape) {
        leftMotor->run(FORWARD);
        Serial.print(-1 * fullSpeed);
        Serial.print(",");
        rightMotor->run(BACKWARD);
        Serial.print(fullSpeed);
        Serial.print(",");        
      } else if (rightTape) {
        leftMotor->run(BACKWARD);
        Serial.print(fullSpeed);
        Serial.print(",");         
        rightMotor->run(FORWARD);
        Serial.print(-1 * fullSpeed);
        Serial.print(",");        
      } else {
        leftMotor->run(FORWARD);
        Serial.print(-1 * fullSpeed);
        Serial.print(",");  
        rightMotor->run(FORWARD);
        Serial.print(-1 * fullSpeed);
        Serial.print(",");  
        delay(250 * 35 / minSpeed);
      }

    }

  } else {
    rightMotor->run(RELEASE);
    leftMotor->run(RELEASE);
    Serial.print("0,0,");
    
  }
  Serial.print(analogRead(A1)); //left sensor
  Serial.print(",");
  Serial.print(analogRead(A2)); //middle sensor
  Serial.print(",");
  Serial.print(analogRead(A0)); //right sensor
  Serial.println(",");    

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
    return "Set Speed";
  }
}
