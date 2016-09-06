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

// Pin Definition Joystick

int axisX = A0;
int axisY = A1;
int sw = 2;

//Pin Definition for Driver

// Left Motor
int mLPWM = 4;
int mLDir1 = 5;
int mLDir2 = 6;

// Right Motor
int mRPWM = 7;
int mRDir1 = 8;
int mRDir2 = 9;

//Global Variables
int vectorX = 0;
int vectorY = 0;

//Middle Joystick Values
int middleX = 656;
int middleY = 322;

//Variables for Adjustments
int xSmooth = 25;
int ySmooth = 25;
int maxpwm = 230;
// Used for Stablish diference with two motors 
int adjpwmMotorLeft = -5;
int adjpwmMotorRight = 0;

void setup(){
	Serial.begin(9600);
	
	pinMode(axisX, INPUT);
	pinMode(axisY, INPUT);
	pinMode(sw, INPUT_PULLUP);
	
	pinMode(mLDir1, OUTPUT);
	pinMode(mLDir2, OUTPUT);
	pinMode(mRDir1, OUTPUT);
	pinMode(mRDir2, OUTPUT);
	pinMode(mLPWM, OUTPUT);
	pinMode(mRPWM, OUTPUT);
	
	//setZeroOnJoysticks();
}

void loop(){
	readAxis();
}
/*
 * Check if Joysticks Values Changes significally and updates her values.
 */
void readAxis(){
 	volatile int tempX, tempY;
	tempX = analogRead(axisX);
	tempY = analogRead(axisY);
	
	if(vectorX < tempX + xSmooth || vectorX > tempX + xSmooth){
		vectorX = tempX;
	};
	if(vectorY < tempY + ySmooth || vectorY > tempY + ySmooth){
		vectorX = tempX;
	};
}
/**
 * Prepares values to send to motors 
 */
void parseDirection(){
   volatile int motorLeft; 
   volatile int motorRight;
   volatile bool leftDir; 
   volatile bool rightDir;

  if(vectorX == middleX && vectorY == middleY){
    stopMotors();
    }
 
  if(vectorY<middleY){
      motorLeft = map(vectorY, 0, middleY, 0, maxpwm);
      motorRight = map(vectorY, 0, middleY, 0, maxpwm);
      updateMotors(,,0,0);
    }else if(vectorY>middleY){
        motorLeft = map(vectorY, middleY, 1023, 0, maxpwm);
        motorRight = map(vectorY, middleY, 1023, 0, maxpwm);
        updateMotors(,,1,1);
      }

   if(vectorY>1000){
      motorLeft = map(vectorY, middleY, 1023, 0, maxpwm);
      motorRight = map(vectorY, middleY, 1023, 0, maxpwm);
      updateMotors(motorLeft, motorRight,1,1);
    }else if(vectorY<25){
      motorLeft = map(vectorY, 0, middleY, 0, maxpwm);
      motorRight = map(vectorY, 0, middleY, 0, maxpwm);
      updateMotors(motorLeft, motorRight,0,0);
    }
  
  }
  // Axis X goes from 0 to 1023. MiddleX are center.
  // have to modificate speed on motors.
  // less than middleX as Left, else Right.
  // Acelerate left motor goes to Right.
  // bool motor: 0 Left, 1 Right
  
 /*
  * Modifies Trottle for motor evaluating axis X
  * @input int motorpwm: value of pwm for motor with Y evaluated
  * @input bool motor: Wich motor are evaluating
  * @returns int finalpwm: Final value for Trottle motor
  */
  int applyAxisX(int motorpwm, bool motor){
    int dirMotor;
    int finalpwm = motorpwm;

    // Calculates in PWM value and Direction of Axis X  
    if(vectorX<middleX){
        dirMotor = map(vectorX, 0, middleX, 0, maxpwm);
      }else if(vectorX>middleX){
        dirMotor = map(vectorX, middleX, 1023, 0, maxpwm);
        }
    if(vectorX<middleX){
    // bool motor: 0 Left, 1 Right
    if (!motor){
       finalpwm = (motorpwm*0.7)+(dirMotor*0.3);
      }else{
          finalpwm = motorpwm * 0.8;
      }
    }else if(vectorX<middleX){
        // bool motor: 0 Left, 1 Right
        if(motor){
            finalpwm = (motorpwm*0.7)+(dirMotor*0.3);    
            }else{
          finalpwm = motorpwm * 0.8;
      }
    }
      return finalpwm;
  }

/*
* Update Motor PWM values and direction
* @input int m1pwm: throttle Motor Left 
* @input int m2pwm: throttle Motor Right
* @input bool m1: direction 1 forward, 0 backward
* @input bool m2: direction 1 forward, 0 backward
*/
void updateMotors(int m1pwm, int m2pwm, bool m1, bool m2){
	if(m1){
    digitalWrite(mLDir1, HIGH);
    digitalWrite(mLDir2, LOW);
    analogWrite(mLPWM, m1pwm + adjpwmMotorLeft);
     
	  }else{
	    digitalWrite(mLDir1, LOW);
      digitalWrite(mLDir2, HIGH);
      analogWrite(mLPWM, m1pwm + adjpwmMotorLeft);
	    };

  if(m2){
    digitalWrite(mRDir1, HIGH);
    digitalWrite(mRDir2, LOW);
    analogWrite(mRPWM, m2pwm + adjpwmMotorRight);
      
    }else{
      digitalWrite(mRDir1, LOW);
      digitalWrite(mRDir2, HIGH);
      analogWrite(mRPWM, m2pwm + adjpwmMotorRight);
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
 * Save middle entry point from joystick Axis
 * On this position Motors will be stop
 */
void setZeroOnJoysticks(){
	delay(1000);
	middleX = analogRead(axisX);
	middleY = analogRead(axisY);
}
