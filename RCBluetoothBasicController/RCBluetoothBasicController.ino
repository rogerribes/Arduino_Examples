/*
* Arduino Basic RC Controller
*
* Code for Control RC Robot with 2 Motors and Joystick
*
* Input: Joystick two Axis with Switch
* Output: Driver Motor L298N Controller for two Motors
*
* Author: Roger Ribes.
*
*
*/
#include <SoftwareSerial.h>
// Module Blouetooth
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

//Variables for Adjustments
int pwmIncrement = 10;
int pwmDecrement = 20;
int maxPwm = 230;
int maxTurnPwm = 150;
unsigned long previousMillis = 0;
int interval = 30;

//Throttle Motors
int m1Current = 0;
int m2Current = 0;
int lastCommand;
bool commandrec = false;
//State of Motor Driver

 // ESTATES FOR FSM
  const short S_STOP = 0;
  const short S_FWD = 1;
  const short S_REV = 2;
  const short S_LEFT = 3;
  const short S_RIGHT = 4;

 




void setup() {
  // Stablish Outputs for Motor Driver
  pinMode(mLDir1, OUTPUT);
  pinMode(mLDir2, OUTPUT);
  pinMode(mRDir1, OUTPUT);
  pinMode(mRDir2, OUTPUT);
  pinMode(mLPWM, OUTPUT);
  pinMode(mRPWM, OUTPUT);

}

void loop() {
  // Current State Not volatile on Loop Iterations
  static int state = S_STOP ;
  
  lastCommand = cmdToState(readCommand());
  
   
  if(checkState()){
    switch(state){
      case S_FWD:
        if(lastCommand == state){
          m1Current = motorIncrement(m1Current, false);
          m2Current = motorIncrement(m2Current, false);
          forward(m1Current, m2Current);
          }else{
            stopMotors();
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
            }
        state = lastCommand;
        break;
      case S_STOP:
        stopMotors();
      default:
        stopMotors();
        state = S_STOP;
      }
    }

}
/*
 * Translates recived Command to a Valid State
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
 * @output String command: 
 */
String readCommand(){
  if(mySerial.available()){
    String command = "";
    char caract = mySerial.read();
    while(caract != '/'){
      command = command + caract;
      caract = mySerial.read();
      }
      commandrec = true;
      return command;
    }else{
      commandrec = false;
      return "";
      }
  }

bool checkState(){
  volatile unsigned long currentMillis = millis();
  if(currentMillis > previousMillis + interval){
    return true;
  }else{
    return false;
    }
  }
int motorIncrement(int current, bool turn){
  
  if(turn){
    if(current + interval >= maxTurnPwm){
        return maxTurnPwm;
        }else{
          return current + interval;
          }
    }else{
      if(current + interval >= maxPwm){
        return maxPwm;
        }else{
          return current + interval;
          }
      }
  }

/*
 * Stop Motors
 */
void stopMotors(){
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
 * GO FORWARD
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
 * GO REVERSE
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
 * TURN LEFT
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
 * TURN RIGHT
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
