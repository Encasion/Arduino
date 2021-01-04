#include "VadimMotor.h"
#include "VadimMp3.h"
VMotor mot (2, 4 , 7, 8, 9, 10); 
VMp mpe (3, 5, 11);

char datain;
String strdatain;
int speed, track;
bool flag;

void setup(){
  Serial.begin(9600);
  mpe.t(0.9,1,12,21,14,8,99,0); //длина треков в сек (8шт);
  delay(1500);
  mpe.next();
  mpe.back();
  mpe.pause();
  Serial.println("BOOT OK");
  Serial.println("");
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
    mpe.stop();
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
