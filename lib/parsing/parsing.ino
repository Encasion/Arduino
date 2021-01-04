char datain; 
String strdatain;
int speed;

void setup(){
  Serial.begin(9600);
}
void loop(){
  check();
  Serial.print("datain: ");
  Serial.println(datain);
  Serial.println(" ");
  Serial.print("speed: ");
  Serial.println(speed);
  delay(500);
  }
  
boolean getStarted; 
void check(){
  if (Serial.available() > 0){
    datain = Serial.read();
    if (getStarted == true && datain != ';'){
      strdatain += datain;
      }

     if (datain == 's'){
       getStarted = true;
       strdatain = "";
      }
     if (datain == ';'){
       getStarted = false;
       speed = strdatain.toInt();
      }     
    }
  }
