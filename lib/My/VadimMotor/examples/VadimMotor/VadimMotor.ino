#include "VadimMotor.h"

VMotor mot (2, 4 , 7, 8, 9, 10); 

char datain;
String strdatain;
int speed;

void setup(){
  Serial.begin(9600);
}
void loop(){
  check();
  switch(datain){
    case 'f':
      mot.forward();
    break;
    case 'b':
      mot.backward();
    break;
    case 'l':
      mot.left();
    break;
    case 'r':
      mot.right();
    break;
    case 'y':
      mot.stopy();
    break;
    case 'x':
      mot.stopx();
    break;
    case ';':
      mot.speed(speed);
    break;
  }
  datain = 0;  
}
bool getStarted;

void check(){
  if(Serial.available() > 0){
    datain = Serial.read();
    if (getStarted && datain != ';')
      strdatain += datain;
      
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
