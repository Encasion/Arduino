#include "SoftwareSerial.h"
SoftwareSerial dfSerial(11, 13); //11-RX 13-TX;
#include <DFPlayer_Mini_Mp3.h>

char datain;
void setup(){
  Serial.begin (9600);
  dfSerial.begin (9600);
  mp3_set_serial (dfSerial);
  delay(1000);
  mp3_set_volume (15);
  mp3_set_EQ (0);
}

void loop(){
  if (Serial.available()>0){
    datain = Serial.read();
    switch(datain){
      case '1':
       mp3_play(1);
       break;
      case '2':
       mp3_play(2);
       break;
      case '3':
       mp3_play(3);
       break;
      case '4':
       mp3_play(4);
       break;
      case '5':
       mp3_play(5);
       break;
      case 'n':
       mp3_next();
       break;
      case 'p':
       mp3_prev();
       break;
      case 'q':
       mp3_pause();
       break;
      case 'e':
       mp3_play();
       break;
      default:
       //Serial.println("What did you say about my mom?");
       Serial.println(datain);
       break;  
    }//switch
  } //Serial Available
} //loop

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
