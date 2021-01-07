#define CLK 3 //Индикатор
#define DIO 4 //Индикатор

#define DATA 2  //Датчик

#include "GyverTM1637.h"
GyverTM1637 disp(CLK, DIO); 

#include "SimpleDHT.h"
SimpleDHT11 dht(DATA);

byte t, h;
int err=SimpleDHTErrSuccess;

byte error[] = {_E, _r, _r, _r, _o, _r, _empty, _4, _0, _4};
const uint8_t DigitHex[] = {  //Цифры (вроде)
  0x3f, 0x06, 0x5b, 0x4f,
  0x66, 0x6d, 0x7d, 0x07,
  0x7f, 0x6f, 0x00, 0x40
};

byte DispData[4];

void setup() {  
  Serial.begin(9600);
  disp.clear();
  disp.brightness(1);
}

void loop() {
  
  while ((err = dht.read(&t, &h, NULL)) != SimpleDHTErrSuccess) {
    disp.runningString(error, sizeof(error), 150);
    delay(1000);
  }
   
  Serial.print(t);
  Serial.println(h);

  byte a = t/10;  //Разделение температуры на десятки
  byte b = t-(a*10);  //Разделение температуры на единицы
  a = DigitHex[a];  //Цифры в HEX формате
  b = DigitHex[b];
  
  DispData[0]= a;
  DispData[1]= b;
  DispData[2]= _empty; //пробел
  DispData[3]= _C;
  
  disp.displayByte(DispData);
  delay(1500);

  a = h/10;
  b = h-(a*10);
  a = DigitHex[a];
  b = DigitHex[b];
  
  DispData[0]= a;
  DispData[1]= b;
  DispData[2]= _empty;
  DispData[3]= _H;
  
  disp.displayByte(DispData);
  delay(1500);
} 
