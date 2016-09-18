#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 8); // RX, TX

void setup() {

Serial.begin(115200);
mySerial.begin(9600);

}

void loop(){
 
if (mySerial.available()){
Serial.println(whatElse());
delay(20);
}
/**
 * Sends to Bluetooth (android) whatelse recieved on
 * Serial Monitor from Arduino IDE
 */
if (Serial.available())

mySerial.write(Serial.read());


}
/**
 * Reads Bluetooth Serial until recives / Character
 * Then return String with action to perform
 * @output String command: Output String Recieved
 */
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
