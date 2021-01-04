#include "VadimMotor.h"
VMotor mot (2, 4 , 7, 8, 9, 10);
 
#include "SoftwareSerial.h"
SoftwareSerial dfSerial(11, 13); //11-RX 13-TX;

#include <DFPlayer_Mini_Mp3.h>

char datain;
String strdatain;
int speed;
bool flag;

void setup(){
  Serial.begin(9600);
  dfSerial.begin (9600);
  mp3_set_serial (dfSerial);
  mp3_set_volume (15);
  mp3_set_EQ (0);
  Serial.println("BOOT OK");
  Serial.println("");
}

void loop(){
  check();
  if (Serial.available()>0) 
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
    case '0':
      
    break;
    case ';':
      if (flag == 1) mot.speed(speed); 
    break;
    default:
      Serial.println("What did you say about my mom?");
    break;
  }
  datain = 0;  
}
/*
   mp3_play ();    //start play
   mp3_play (5);  //play "mp3/0005.mp3"
   mp3_next ();   //play next 
   mp3_prev ();   //play previous
   mp3_set_volume (uint16_t volume);  //0~30
   mp3_set_EQ (); //0~5
   mp3_pause ();
   mp3_stop ();
   void mp3_random_play (); 
*/

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
