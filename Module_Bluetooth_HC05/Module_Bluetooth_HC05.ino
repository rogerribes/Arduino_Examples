#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 8); // RX, TX
int pinled = 13;
int pwrBlue = 11;
int gndBlue = 10;

void setup() {

Serial.begin(115200);
pinMode(13,OUTPUT);
digitalWrite(pinled, LOW);
pinMode(gndBlue, OUTPUT); digitalWrite(gndBlue, LOW);
pinMode(pwrBlue,OUTPUT); digitalWrite(pwrBlue,HIGH);


mySerial.begin(9600);

}

void loop()

{
 

if (mySerial.available()){
  //String line = GetLine();
  //Serial.write(mySerial.read());
Serial.println(whatElse());
//Serial.println(" ");
delay(20);
}

if (Serial.available())

mySerial.write(Serial.read());
/*
delay(5000);
digitalWrite(pinled,HIGH);
mySerial.write("AT+NAMEARDIBLUE");
delay(8000);
mySerial.write("AT+PIN000000");
delay(4000);
digitalWrite(pinled, LOW);
delay(30000);*/

}
String GetLine()
   {   String S = "" ;
       if (mySerial.available())
          {    
                while ( mySerial.available())            //Hasta que el caracter sea intro
                  { 
                   int  c = mySerial.read();    
                    S = S + c ;
                        delay(25) ;
                  }
                return( S) ;
          }
   }
String whatElse(){
  if(mySerial.available()){
    String command = "";
    char caract = mySerial.read();
    while(caract != '/'){
      command = command + caract;
      caract = mySerial.read();
      }
      return command;
    }
  }
