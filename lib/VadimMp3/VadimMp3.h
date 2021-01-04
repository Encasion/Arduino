#ifndef VadimMp3_h
#define VadimMp3_h
#include "Arduino.h"

class VMp
{
  public:
  VMp(uint8_t playpin, uint8_t nextpin, uint8_t backpin);
  
  void t(int t1, int t2, int t3, int t4, int t5, int t6, int t7, int t8);
  void play();
  void pause();
  void next();
  void back();
  void track(uint8_t track);
  void stop();
  
  private:
  uint8_t _play, _next, _back;
  int _track;
  bool _stan;
  unsigned long _t[8], time, oldtime;

};
#endif
