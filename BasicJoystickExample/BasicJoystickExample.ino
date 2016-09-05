
int axisX = A0 ;
int axisY = A1 ;
int sw = A2 ;

int xvalue = 0;
int yvalue = 0;

int tempx, tempy;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(axisX, INPUT);
  pinMode(axisY, INPUT);
  pinMode(sw, INPUT);

  

}

void loop() {
  // put your main code here, to run repeatedly:

  if(analogRead(axisX)!=tempx){
    tempx = analogRead(axisX);
    Serial.print("Valor eje X: ");
    Serial.println(tempx);
    }
    
  

}
