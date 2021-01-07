#include "Arduino.h"
#include "VadimMotor.h"

/*
VMotor::VMotor(char standart){
  VMotor::VMotor(2, 4 , 7, 8, 9, 10);
}
*/

VMotor::VMotor(uint8_t m1a, uint8_t m1b, uint8_t m2a, uint8_t m2b, uint8_t m1pwm, uint8_t m2pwm) {
  _m1a = m1a;
  _m1b = m1b;
  _m2a = m2a;
  _m2b = m2b;
  _m1pwm = m1pwm;
  _m2pwm = m2pwm;

  _speed = 255;

  _cs1 = A0;
  _cs2 = A1;
  
  pinMode (_m1a, OUTPUT);
  pinMode (_m1b, OUTPUT);
  pinMode (_m2a, OUTPUT);
  pinMode (_m2b, OUTPUT);
  pinMode (_m1pwm, OUTPUT);
  pinMode (_m1pwm, OUTPUT);

  VMotor::speed(_speed);
}

char VMotor::flag(){
  if (flagforward){
    Serial.println("return f");
    return 'f';
  } else if (flagbackward){
    Serial.println("return b");
    return 'b';
  } else if (flagleft){
    Serial.println("return l");
    return 'l';
  } else if (flagright){
    Serial.println("return r");
    return 'r';
  } else {
    Serial.println("return 0");
    return '0';  
  }
}  
void VMotor::speed(uint8_t speed){
  _speed = speed;
  analogWrite(_m1pwm, speed);
  analogWrite(_m2pwm, speed);
  Serial.print("motor speed: ");       //delete
  Serial.println(speed);               //delete
}
void VMotor::forward(){
  if (flagforward == 0) 
    flagforward = !flagforward;
  if (flagright == 1)
    rdiagonale();
  else if (flagleft == 1)
    ldiagonale(); 
  else { 
    VMotor::speed(_speed);
    digitalWrite (_m1a, 1);
    digitalWrite (_m1b, 0);
    digitalWrite (_m2a, 1);
    digitalWrite (_m2b, 0);
    Serial.println("Go forward");     //delete
    Serial.println("");               //delete
    }
  flagbackward = 0;
  delay(10);
}
void VMotor::backward(){
  if (flagbackward == 0) 
    flagbackward = !flagbackward;
  if (flagright == 1)
    rdiagonale();
  else if (flagleft == 1)
    ldiagonale();  
  else {
    VMotor::speed(_speed);
    digitalWrite (_m1a, 0);
    digitalWrite (_m1b, 1);
    digitalWrite (_m2a, 0);
    digitalWrite (_m2b, 1);
    Serial.println("Go backward");      //delete  
    Serial.println("");                 //delete
      }
  flagforward = 0;
  delay(10);
}
void VMotor::left(){
  if (flagforward == 1 || flagbackward == 1){
    ldiagonale();  
  } else {
      VMotor::speed(_speed);
      digitalWrite (_m1a, 0);
      digitalWrite (_m1b, 1);
      digitalWrite (_m2a, 1);
      digitalWrite (_m2b, 0);
      Serial.println("Go left");        //delete
      Serial.println("");                //delete
    }
  if (flagleft == 0) 
    flagleft = !flagleft;
  flagright = 0;
  delay(10);
} 
void VMotor::right(){
  if (flagforward == 1 || flagbackward == 1){
    rdiagonale();
  } else {
    VMotor::speed(_speed);
    digitalWrite (_m1a, 1);
    digitalWrite (_m1b, 0);
    digitalWrite (_m2a, 0);
    digitalWrite (_m2b, 1);
    Serial.println("Go right");         //delete
    Serial.println("");                 //delete
  }
  if (flagright == 0) 
    flagright = !flagright;
  flagleft = 0;
  delay(10);
}
void VMotor::stopx(){
  digitalWrite (_m1a, 0);
  digitalWrite (_m1b, 0);
  digitalWrite (_m2a, 0);
  digitalWrite (_m2b, 0);
  flagleft = 0;
  flagright = 0;
  Serial.println("stop X");               //delete
  Serial.println(" ");                     //delete
  if (flagforward) 
    VMotor::forward();
  if (flagbackward)
    VMotor::backward();
  }
void VMotor::stopy(){
  digitalWrite (_m1a, 0);
  digitalWrite (_m1b, 0);
  digitalWrite (_m2a, 0);
  digitalWrite (_m2b, 0);
  flagforward = 0;
  flagbackward = 0;
  Serial.println("stop Y");               //delete
  Serial.println(" ");                    //delete
  if (flagleft) 
    VMotor::left();
  if (flagright)
    VMotor::right();
  }
  
void VMotor::rdiagonale(){ 
  if (_speed+100 <255 && _speed-100 >0){
  analogWrite(_m1pwm, _speed + 100);
  analogWrite(_m2pwm, _speed - 100);
  } else if (255- _speed > _speed){
  analogWrite(_m1pwm, 200);
  analogWrite(_m2pwm, 0);  
  } else if (255- _speed < _speed){
  analogWrite(_m1pwm, 255);
  analogWrite(_m2pwm, 55);  
  }

//   analogWrite(_m1pwm, 255);
//   analogWrite(_m2pwm, 0);

  if (flagforward){
    digitalWrite (_m1a, 1);
    digitalWrite (_m1b, 0);
    digitalWrite (_m2a, 1);
    digitalWrite (_m2b, 0);
  } else if (flagbackward){
    digitalWrite (_m1a, 0);
    digitalWrite (_m1b, 1);
    digitalWrite (_m2a, 0);
    digitalWrite (_m2b, 1);
  }
  Serial.println("Go right-diagonale");   //delete
  Serial.println(" ");                    //delete
}
void VMotor::ldiagonale(){
  if (_speed+100 <255 && _speed-100 >0){
  analogWrite(_m1pwm, _speed - 100);
  analogWrite(_m2pwm, _speed + 100);
  } else if (255- _speed > _speed){
  analogWrite(_m1pwm, 0);
  analogWrite(_m2pwm, 200);  
  } else if (255- _speed < _speed){
  analogWrite(_m1pwm, 55);
  analogWrite(_m2pwm, 255);  
  }

//   analogWrite(_m1pwm, 0);
//   analogWrite(_m2pwm, 255);

  if (flagforward){
    digitalWrite (_m1a, 1);
    digitalWrite (_m1b, 0);
    digitalWrite (_m2a, 1);
    digitalWrite (_m2b, 0);
  } else if (flagbackward){
    digitalWrite (_m1a, 0);
    digitalWrite (_m1b, 1);
    digitalWrite (_m2a, 0);
    digitalWrite (_m2b, 1);
  }
  Serial.println("Go left-diagonale");    //delete
  Serial.println("");                     //delete
}

String VMotor::current()
{
  String current1 = "";
  String current2 = "";
  current1 = analogRead(A0);
  current2 = analogRead(A1) * 34;
  current1 = current1.toInt() * 34;
  return ("current1: " + current1 + ", current2: " + current2);
}
