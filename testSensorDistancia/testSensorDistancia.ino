#define trigPin 13
#define sLeft 12
#define sMiddle 11
#define sRight 10

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(sLeft, INPUT);
  pinMode(sMiddle, INPUT);
  pinMode(sRight, INPUT);
}

void loop() {
   long dLeft, distLeft, dMiddle, distMiddle, dRight, distRight;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  dLeft = pulseIn(sLeft, HIGH);
  distLeft = (dLeft/2) / 29.1;
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  dMiddle = pulseIn(sMiddle, HIGH);
  distMiddle = (dMiddle/2) / 29.1;
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  dRight = pulseIn(sRight, HIGH);
  distRight = (dRight/2) / 29.1;
Serial.print("S. Izquierdo: ");
Serial.print(distLeft);
Serial.println(" cm"); 

Serial.print("S. Centro: ");
Serial.print(distMiddle);
Serial.println(" cm"); 

Serial.print("S. Derecho: ");
Serial.print(distRight);
Serial.println(" cm"); 
 /* if (distance < 4) {  // This is where the LED On/Off happens
    digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
  digitalWrite(led2,LOW);
}
  else {
    digitalWrite(led,LOW);
    digitalWrite(led2,HIGH);
  }
  if (distance >= 400 || distance <= 0){
    Serial.println("Out of range");
  }
  else {
    Serial.print("Distancia Sensor 1: ");
    Serial.print(distance);
    Serial.println(" cm");
  }*/
  delay(400);
}
