#include "VadimMp3.h"
VMp mpe (8, 6, 7);
char datain;
String strdatain;

int track;
void setup(){
  Serial.begin(9600);
  mpe.t(10,5,15,3,2,7,4,0);
}
void loop(){
  check();
  mpe.stop();
  switch(datain){
    case 'n':
      mpe.next();
    break;
    case 'b':
      mpe.back();
    break;
    case 'w':
      mpe.play();
    break;
    case 's':
      mpe.pause(); 
    break;
    case ';':
      mpe.track(track);
    break;
    case 'q':
      mpe.track(1);
    break;
   }
}
bool getStarted;
void check(){
  if(Serial.available() > 0){
    datain = Serial.read();
    if (getStarted && datain != ';')
      strdatain += datain;
    if (datain == 't'){
      getStarted = true;
      strdatain = ""; 
    }
    if (datain == ';'){
      getStarted = false;
      track = strdatain.toInt();
    }
  }
}
