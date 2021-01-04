#include <SoftwareSerial.h>
#include "VadimMotor.h"
#include "VadimMp3.h"
VMotor mot (2, 4 , 7, 8, 9, 10); 
VMp mpe (8, 6, 7);

char datain;
String strdatain;
int speed, track;
bool flag;

void setup(){
  Serial.begin(9600);
  mpe.t(10,5,15,3,2,7,4,0); //длина треков в с (8шт);
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
    case 'e':
      mpe.next();
    break;
    case 'q':
      mpe.back();
    break;
    case 'w':
      mpe.play();
    break;
    case 'd':
      mpe.pause(); 
    break;
    case 'a':
      mpe.track(1);
    break;
    case ';':
      if (flag == 1) mot.speed(speed); 
      else if (flag == 0) mpe.track(track);
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
      flag = 1; 
    }
    if (datain == 't'){
      getStarted = true;
      strdatain = "";
      flag = 0;
    }
    if (datain == ';'){
      getStarted = false;
      speed = strdatain.toInt();
      track = strdatain.toInt();
    }
  }
}
