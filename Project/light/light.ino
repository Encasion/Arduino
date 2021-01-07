#define s1 6
#define s2 7
#define key 5
#define sensory 2

byte line[3] = {9, 10, 11};
byte bright[3] = {255, 255, 255};

byte step1 = 7;
byte step2 = 12;

#include <GyverEncoder.h>
Encoder enc(s1, s2, key, 2); 

void setup(){
  Serial.begin(9600);
  pinMode(3, OUTPUT); //питание сенсорной кнопки
  digitalWrite(3, HIGH);
  pinMode(4, OUTPUT); //питание энкодера
  digitalWrite(4, HIGH);
  
  pinMode(sensory, INPUT); //сигнал сенсорной кнопки

} 
void loop(){
  enc.tick();
  bool button = digitalRead(sensory);
  if (button)
    for (int i=0; i<=2; i++) analogWrite(line[i], bright[i]); 
  else for (int i=0; i<=2; i++) analogWrite(line[i], 0);

  if (enc.isRight()) for (int i=0; i<=2; i++) if (bright[i]<=(255-step1)) bright[i] = bright[i] + step1; else bright[i]=255;
  if (enc.isLeft()) for (int i=0; i<=2; i++) if (bright[i]>=step1) bright[i] = bright[i] - step1; else bright[i]=0;
  if (enc.isFastR()) for (int i=0; i<=2; i++) if (bright[i]<=(255-step2)) bright[i] = bright[i] + step2; else bright[i]=255;
  if (enc.isFastL()) for (int i=0; i<=2; i++) if (bright[i]>=step2) bright[i] = bright[i] - step2; else bright[i]=0;

  
//  if (enc.isPress()) 
} 
