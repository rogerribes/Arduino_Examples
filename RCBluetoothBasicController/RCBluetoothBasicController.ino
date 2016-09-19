/*
* Arduino Basic RC Controller
*
* Code for Control RC Robot with 2 Motors
* Joystick are Android Serial App from Bluetooth HC-06
*
* Input: Slave HC-06 Bluetooth Module, Android App
* Output: Driver Motor L298N Controller for two Motors
*
* Author: Roger Ribes.
*
*
*/

// Library for Serial comunication on any desired pin
#include <SoftwareSerial.h>

// Module Bluetooth
SoftwareSerial mySerial(9, 8); // RX, TX

//Pin Definition for Driver
// Left Motor
const int mLPWM = 6;
const int mLDir1 = 5;
const int mLDir2 = 7;
// Right Motor
const int mRPWM = 3;
const int mRDir1 = 2;
const int mRDir2 = 4;
/*
* Finite State Machine State Definition
* Used for Control Logic of RC Car
*/
const short S_STOP = 0;
const short S_FWD = 1;
const short S_REV = 2;
const short S_LEFT = 3;
const short S_RIGHT = 4;

//Variables for Adjustments
int pwmIncrement = 10;
int pwmDecrement = 20;
int maxPwm = 230;
int maxTurnPwm = 150;
unsigned long previousMillis = 0;
int interval = 50;

//Throttle Motors
int m1Current = 0;
int m2Current = 0;

void setup() {
  // Stablish Outputs for Motor Driver
  pinMode(mLDir1, OUTPUT);
  pinMode(mLDir2, OUTPUT);
  pinMode(mRDir1, OUTPUT);
  pinMode(mRDir2, OUTPUT);
  pinMode(mLPWM, OUTPUT);
  pinMode(mRPWM, OUTPUT);
  
  // Initialize Serial Comunications
  Serial.begin(9600);
  mySerial.begin(9600);

}

void loop() {
  // Current State Not volatile on Loop Iterations
  static int state = S_STOP ;
  int lastCommand;
   
  if(checkState(interval)){
	//  Last Command from Bluetooth Readed
    lastCommand = cmdToState(readCommand());  
    switch(state){
      case S_FWD:
        if(lastCommand == state){
          m1Current = motorIncrement(m1Current, false);
          m2Current = motorIncrement(m2Current, false);
          forward(m1Current, m2Current);
          }else{
            stopMotors();
			state = S_STOP;
            }
        state = lastCommand;
        break;
      case S_REV:
        if(lastCommand == state){
          m1Current = motorIncrement(m1Current, false);
          m2Current = motorIncrement(m2Current, false);
          reverse(m1Current, m2Current);
          }else{
            stopMotors();
			state = S_STOP;
            }
        state = lastCommand;
        break;
      case S_LEFT:
        if(lastCommand == state){
          m1Current = motorIncrement(m1Current, true);
          m2Current = motorIncrement(m2Current, true);
          turnLeft(m1Current, m2Current);
          }else{
            stopMotors();
			state = S_STOP;
            }
        state = lastCommand;
        break;
      case S_RIGHT:
        if(lastCommand == state){
          m1Current = motorIncrement(m1Current, true);
          m2Current = motorIncrement(m2Current, true);
          turnRight(m1Current, m2Current);
          }else{
            stopMotors();
			state = S_STOP;
            }
        state = lastCommand;
        break;
      case S_STOP:
        stopMotors();
		state = lastCommand;
      }
    }
	// Print On Usb Serial Monitor RC Status
	
	//Serial.println("test");
}
/*
 * Translates recived Command to a Valid State
 * @input String command: String to evaluate desired State
 * @return int State: Returns State recived from controller
 */
int cmdToState(String command){
  if(command == "FWD"){
    return S_FWD;
  }else if(command == "REV"){
    return S_FWD;
  }else if(command == "LFT"){
    return S_LEFT;
  }else if(command == "RGT"){
    return S_RIGHT;
  }
  return S_STOP;
  
  }
/* 
 * Read Incoming Command
 * @output String command: Command recived from Bluetooth
 */
String readCommand(){
  if(mySerial.available()){
    String command = "";
    char caract = mySerial.read();
    while(caract != '/'){
      command = command + caract;
      caract = mySerial.read();
      }
      return command;
    }else{
      return "";
      }
  }
/*
 * Determines if it's time to check state Machine
 * Verifies if pass enough time from last machine update
 *
 */
bool checkState(int interval){
  unsigned long currentMillis = millis();
  if(currentMillis >= previousMillis + interval){
	previousMillis = currentMillis;
	printOnSerial(state, lastCommand);
    return true;
  }else{
    return false;
    }
  }
/*
 * Function to increment Value of PWM Motors. Check if raise stablished Limit
 * @ input int current: Value to evaluate increment
 * @ input bool turn: Define its turn operation. Have another pwm Limit
 * @ output int increment: Return increment to apply to Motor Pwm Pin 
 *
 */  
int motorIncrement(int current, bool turn){
  
  if(turn){
    if(current + pwmIncrement >= maxTurnPwm){
        return maxTurnPwm;
        }else{
          return current + pwmIncrement;
          }
    }else{
      if(current + pwmIncrement >= maxPwm){
        return maxPwm;
        }else{
          return current + pwmIncrement;
          }
      }
  }
 /*
  * Function to Provide Feedback to Usb Serial and PC
  * print on Serial Monitor current State, Command, and Values
  */
  void printOnSerial(int state, int lastCommand){
	  if(checkState(200)){
		  Serial.print("Current State: ");
		  Serial.print(state);
		  Serial.print(", Last Command: ");
		  Serial.print(lastCommand);
		  Serial.print(" // Motor Left: ");
		  Serial.print(m1Current);
		  Serial.print(", Motor Right: ");
		  Serial.println(m2Current);
	  }
  }

/*
 * Apply to Motor Driver a Stop Configuration
 */
void stopMotors(){
  // Reset currentPWM motor Values
  m1Current = 0;
  m2Current = 0;
  //stop Left Motor
  digitalWrite(mLDir1, LOW);
  digitalWrite(mLDir2, LOW);
  analogWrite(mLPWM, 0);
  //stop Right Motor
  digitalWrite(mRDir1, LOW);
  digitalWrite(mRDir2, LOW);
  analogWrite(mRPWM, 0);
  }

/*
 * Apply to Motor Driver configuration to go Forward
 * @input int m1pwm: Throttle for Motor Left
 * @input int m2pwm: Throttle for Motor Right 
 */
 void forward(int m1pwm, int m2pwm){
  digitalWrite(mLDir1, HIGH);
  digitalWrite(mLDir2, LOW);
  analogWrite(mLPWM, m1pwm);
  // Right Motor
  digitalWrite(mRDir1, HIGH);
  digitalWrite(mRDir2, LOW);
  analogWrite(mRPWM, m2pwm);
  }
/*
 * Apply to Motor Driver configuration to go Reverse
 * @input int m1pwm: Throttle for Motor Left
 * @input int m2pwm: Throttle for Motor Right 
 */
 void reverse( int m1pwm, int m2pwm){
  digitalWrite(mLDir1, LOW);
  digitalWrite(mLDir2, HIGH);
  analogWrite(mLPWM, m1pwm);
  // Right Motor
  digitalWrite(mRDir1, LOW);
  digitalWrite(mRDir2, HIGH);
  analogWrite(mRPWM, m2pwm);
  }
/*
 * Apply to Motor Driver configuration to Turn Left
 * @input int m1pwm: Throttle for Motor Left
 * @input int m2pwm: Throttle for Motor Right 
 */
 void turnLeft( int m1pwm, int m2pwm){
  digitalWrite(mLDir1, LOW);
  digitalWrite(mLDir2, HIGH);
  analogWrite(mLPWM, m1pwm/2);
  // Right Motor
  digitalWrite(mRDir1, HIGH);
  digitalWrite(mRDir2, LOW);
  analogWrite(mRPWM, m2pwm);
  }
/*
 * Apply to Motor Driver configuration to Turn Right
 * @input int m1pwm: Throttle for Motor Left
 * @input int m2pwm: Throttle for Motor Right 
 */
 void turnRight(int m1pwm, int m2pwm){
  digitalWrite(mLDir1, HIGH);
  digitalWrite(mLDir2, LOW);
  analogWrite(mLPWM, m1pwm);
  // Right Motor
  digitalWrite(mRDir1, LOW);
  digitalWrite(mRDir2, HIGH);
  analogWrite(mRPWM, m2pwm/2);
  }
