#include "VadimMotor.h"
VMotor mot (2, 4 , 7, 8, 9, 10);
 
#include "SoftwareSerial.h"
SoftwareSerial dfSerial(11, 13); //11-RX 13-TX; (13 need resistor 1kom)

#include <DFPlayer_Mini_Mp3.h>

char datain;
String strdatain;
uint8_t val, flag;
bool getStarted;

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
  if (Serial.available()>0 && getStarted == false) 
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
      mp3_next ();
    break;
    case 'q':
      mp3_prev ();
    break;
    case 'w':
      mp3_play ();
    break;
    case 'd':
      mp3_pause ();
    break;
    
    case '0':
      /*______________*/
    break;
    case ';':
      switch (flag) {
        case 0:
          mp3_play(val);
          Serial.print("play track: ");
          Serial.println(val);
        break;
        case 1:
          mot.speed(val);
        break;
        case 2:
          if(val<=30 && val>=0){
          mp3_set_volume(val);
          Serial.print("volume: ");
          Serial.println(val);
          }
        break;
      } 
    break;
    default:
//      Serial.println("What did you say about my mom?");
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

void check(){
  if(Serial.available() > 0){
    datain = Serial.read();
    if (getStarted && datain != ';')
      strdatain += datain;
    
    if (datain == 't'){
      getStarted = true;
      strdatain = "";
      flag = 0;
    }  
    if (datain == 's'){
      getStarted = true;
      strdatain = "";
      flag = 1; 
    }
    if (datain == 'v'){
      getStarted = true;
      strdatain = "";
      flag = 2;
    }
    
    if (datain == ';'){
      getStarted = false;
      val = strdatain.toInt();
    }
  }
    delay(10);
}
