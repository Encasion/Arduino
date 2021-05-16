#include "Arduino.h"
#include "KitEncoder.h"
/*
 * нада замутити шоб лефт і райт скідувались не при запуску їх,  а при запуску tick;
 */
#define maska 0b1001
#define maskA 0b0110

#define maskb 0b0011
#define maskB 0b1100

KEncoder::KEncoder(uint8_t pina, uint8_t pinb){
  _pina=pina;
  _pinb=pinb;
  
  pinMode(_pina, 0);
  pinMode(_pinb, 0);
}

void KEncoder::tick(){
  _stana=digitalRead(_pina);
  _stanb=digitalRead(_pinb);
  
  if(   ((_stana==1)&&(~a&1))||((_stana==0)&&(a&1)) || (((_stanb==1)&&(~b&1))||((_stanb==0)&&(b&1))) )
  {
    a<<=1;
    a|=_stana;
    b<<=1;
    b|=_stanb;  
  }
}
bool KEncoder::left(){
  if ((a&maska)==maska && (~a&maskA)==maskA)
      if ((b&maskb)==maskb && (~b&maskB)==maskB){
        a<<=1;
        b<<=1;
        return 1;
      }
  return 0;
}

bool KEncoder::right(){
  if ((b&maska)==maska && (~b&maskA)==maskA)
      if ((a&maskb)==maskb && (~a&maskB)==maskB){
        a<<=1;
        b<<=1;
        return 1;
      }
  return 0;
}
