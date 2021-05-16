#include <Servo.h>

Servo servo;
void setup() {
  Serial.begin(9600);
  servo.attach(9); 


}

int val, val2;
void loop() {
/*
  servo.write(65);
  delay(2000);
  servo.write(145);
  delay(2000);
  servo.write(65);
  delay(3000);
  servo.write(145);
  delay(3000); 
  servo.write(65);
  delay(500);
  servo.write(145);
  delay(500);
*/  
 /* if (Serial.available()>1) {
  val = Serial.parseInt();

   servo.write(val);
   Serial.println(val);
   Serial.flush();
  
  }
*/

  val = analogRead(A0);
  val=map(val, 0, 1023, 65, 145);
  servo.write(val);
  delay(10);
  

  
}
