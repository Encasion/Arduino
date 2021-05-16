#ifndef KitEncoder_h
#define KitEncoder_h
#include "Arduino.h"

class KEncoder
{ 
  public:
  KEncoder(uint8_t pina, uint8_t pinb);
  void tick();
  bool left();
  bool right();
  
  private:
  uint8_t _pina, _pinb, a=0, b=0;
  bool _stana, _stanb;
  
};
#endif
