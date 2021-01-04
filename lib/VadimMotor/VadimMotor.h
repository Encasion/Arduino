#ifndef VadimMotor_h
#define VadimMotor_h
#include "Arduino.h"

class VMotor
{
  public:
  VMotor(char standart);
  VMotor(uint8_t m1a, uint8_t m1b, uint8_t m2a, uint8_t m2b, uint8_t m1pwm, uint8_t m2pwm);
  
  void forward();
  void backward();
  void left();
  void right(); 
  void stopy();
  void stopx();
  void speed(uint8_t speed);
  char flag();
  String current();
  
  private:
  void rdiagonale();
  void ldiagonale();
  uint8_t _m1a, _m1b, _m2a, _m2b, _m1pwm, _m2pwm, _speed, _cs1, _cs2;
  bool flagforward, flagbackward, flagleft, flagright;

};

#endif
