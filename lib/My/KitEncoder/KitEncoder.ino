#include "KitEncoder.h";
KEncoder enc(0, 2);

void setup() {
  Serial.begin(115200);
  Serial.println("x,y");
}

bool x, y, oldx, oldy;
int var=0;
void loop() {
  enc.tick();

  if (enc.left()){
    var++;
    Serial.println(var);
  }
  if (enc.right()){
    var--;
    Serial.println(var);
  } 
}
