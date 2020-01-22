#include "Arduino.h"
#include "VadimMp3.h"

VMp::VMp(uint8_t playpin, uint8_t nextpin, uint8_t backpin) {
  _play = playpin;
  _next = nextpin;
  _back = backpin;
  _track = 1;
  _stan = 0;
  pinMode (_play, OUTPUT);
  pinMode (_next, OUTPUT);
  pinMode (_back, OUTPUT);
}
void VMp::t(int t1, int t2, int t3, int t4, int t5, int t6, int t7, int t8){
  _t[0]=t1;
  _t[1]=t2;
  _t[2]=t3;
  _t[3]=t4;
  _t[4]=t5;
  _t[5]=t6;
  _t[6]=t7;
  _t[7]=t8;
  
}
void VMp::stop(){
  if (_track > 0 && _track < 9)
  if (round ((millis() - oldtime)/1000) > _t[_track-1]){
       pause();
       Serial.println("stop");
       }
  }
void VMp::track(uint8_t track){
  while (_track < track)
    next();
  while (_track > track) 
     back();
  if (track == _track)
     play();
}

void VMp::play(){
  if (_stan == 0){ 
    digitalWrite(_play, 1);
    delay(100);
    digitalWrite(_play, 0);
    _stan = !_stan;
    Serial.println("play");  
    }
    oldtime = millis();  
}
void VMp::pause(){
  if (_stan == 1){
    digitalWrite(_play, 1);
    delay(100);
    digitalWrite(_play, 0);
    _stan = !_stan;
    delay(80);
    Serial.println("pause");
    }
}
void VMp::next(){
  digitalWrite(_next, 1);
  delay(100);
  digitalWrite(_next, 0);
  delay(80);
  Serial.println("next");
  _track++;
  if (_stan == 0){
  _stan = !_stan;
  }
  oldtime = millis();
}
void VMp::back(){
  digitalWrite(_back, 1);
  delay(100);
  digitalWrite(_back, 0);
  delay(80);
  Serial.println("back"); 
  _track--;
  if (_stan == 0){
  _stan = !_stan;
  }
  oldtime = millis();
}
