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
Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);
Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
// You can also make another motor on port M2
//Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

void setup() {
  Serial.begin(115200);           // set up Serial library at 9600 bps

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    while (1);
  }

  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(255);
  rightMotor->run(FORWARD);
  // turn on motor
  rightMotor->run(RELEASE);
  leftMotor->setSpeed(255);
  leftMotor->run(FORWARD);
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

}

String reactToInput(String input){
  if (input == "rightF"){
    rightMotor->run(FORWARD);
    return "rightF";
  }
  else if (input == "rightB"){
    rightMotor->run(BACKWARD);
    return "rightB";
  }
  else if (input == "rightS"){
    rightMotor->run(RELEASE);
    return "rightS";
  }
  else if (input == "leftF"){
    leftMotor->run(FORWARD);
    return "leftF";
  }
  else if (input == "leftB"){
    leftMotor->run(BACKWARD);
    return "leftB";
  }
  else if (input == "leftS"){
    leftMotor->run(RELEASE);
    return "leftS";
  }
  else{
    leftMotor->run(RELEASE);
    rightMotor->run(RELEASE);
    return "unknown input";
  }

  
}
