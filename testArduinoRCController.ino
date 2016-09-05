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
int sw = 3;

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
int middleX = 0;
int middleY = 0;

//Variables for Adjustments
int xSmooth = 25;
int ySmooth = 25;
int maxpwm = 240;
// Used for Stablish diference with two motors 
int adjpwm = -5;


void setup(){
	Serial.Begin(9600);
	
	pinMode(axisX, INPUT);
	pinMode(axisY, INPUT);
	pinMode(sw, INPUT_PULLUP);
	
	pinMode(mLDir1, OUTPUT);
	pinMode(mLDir2, OUTPUT);
	pinMode(mRDir1, OUTPUT);
	pinMode(mRDir2, OUTPUT);
	pinMode(mLPWM, OUTPUT);
	pinMode(mRPWM, OUTPUT);
	
	setZeroOnJoysticks();
}

void loop(){
	readAxis();
	updateMotors();
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
/*
* Update Motor PWM values and direction
*
*/
void updateMotors(){
	
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
