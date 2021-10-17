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

int setpoint = 0; // the difference between the two sensors should be zero
// int output_diff; // the difference betwen the two sensors
double speed_diff; // the control signal - the difference between the two speeds

// gain constants
double Kp = 0.5; // proportional gain
double Ki = 0.5; // integral gain
double Kd = 0.5; // derivative gain 

// error/time tracking
int step_size; // steps inbetween sample time (ms)
unsigned long last_time;

double net_error, last_error;


int centerSpeed = 40;

void setup() {
  Serial.begin(115200);           // set up Serial library at 9600 bps

  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    while (1);
  }


  // Set the speed to start, from 0 (off) to 255 (max speed)
  rightMotor->setSpeed(fullSpeed);
  rightMotor->run(FORWARD);
  // turn on motor
  rightMotor->run(RELEASE);
  leftMotor->setSpeed(fullSpeed);
  leftMotor->run(FORWARD);
  // turn on motor
  leftMotor->run(RELEASE);

  last_time = millis();
}

void loop() {
  
 if (Serial.available()){
     String s = Serial.readStringUntil('\n');
     s.trim();
     String returnMessage = reactToInput(s);
     Serial.println(returnMessage);
  }

  leftTape = (analogRead(A0)<600);
  rightTape = (analogRead(A1)<600);

  if (isRunning){
    // pid loop goes here
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
  else {
    return "I'm confused";
  }
}

double control_signal =  PID_control(int output_diff) {
  unsigned long current_time = millis();
  int delta_time = current_time - last_time;

  if (delta_time >= step_size) {
    double current_error = setpoint - output_diff;
    total_error += current_error;
    delta_error = current_error - last_error;

    // pid equation:
    control_signal = Kp * error + (Kp * delta_time)*total_error + (Kp/deltaTime)*delta_error;

    last_error = current_error;
    last_time = current_time;
  }
}
