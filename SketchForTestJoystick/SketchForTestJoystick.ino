
int axisX=A0;
int axisY= A1;
int sw = 2;

//Limits for Potentiometer
int minX = 1024;
int maxX = 0;
int minY = 1024;
int maxY = 0;



void setup() {
  // put your setup code here, to run once:
  pinMode(axisX, INPUT);
  pinMode(axisY, INPUT);
  pinMode(sw, INPUT_PULLUP);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
int tempx, tempy, tempsw;
tempsw = digitalRead(sw);
tempx = analogRead(axisX);
tempy = analogRead(axisY);
Serial.print("max X: ");
Serial.print(maxX);
Serial.print(" || minX: ");
Serial.println(minX);
//Serial.print(tempx);
//Serial.print(" |||| eje Y: ");
//Serial.print(tempy);
Serial.print("max Y: ");
Serial.print(maxY);
Serial.print("|| min Y: ");
Serial.println(minY);
//Serial.println(tempsw);
saveLimits(tempx,tempy);

delay(1000);
}
void saveLimits(int tempx, int tempy){
  if(minX > tempx){
     minX = tempx;
    }else if(maxX < tempx){
      maxX = tempx;
      };
  if(minY > tempy){
     minY = tempy;
    }else if(maxY < tempy){
      maxY = tempy;
      };
  
   
  
  
  }
