/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo;// create servo object to control a servo
Servo myservo2;

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin
bool goRight = true;
int grade = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo2.attach(10);
  delay(15);
  myservo2.write(90);
  myservo.write(0);
  delay(15);
}

void loop() {
  rotateSensor2();
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  //myservo.write(val);                  // sets the servo position according to the scaled value
  myservo2.write(val); 
 // delay(15);// waits for the servo to get there
 
}
/*void rotateSensor(){
if(goRight){
  for(int i=0;i<=180;i++){
    myservo.write(i);
    delay(40);
    i++;
    }
    goRight = false;
}else{
  for(int i=180;i>=0;i--){
    myservo.write(i);
    delay(40);
    i--;
  }
  goRight = true;
  }
}*/
void rotateSensor2(){
  if(goRight){
    myservo.write(grade);
    delay(30);
    grade++;
    }else{
      myservo.write(grade);
    delay(30);
    grade--;
      }
    if(grade>=180 || grade<=0){
      goRight=!goRight;;
      }
  }
