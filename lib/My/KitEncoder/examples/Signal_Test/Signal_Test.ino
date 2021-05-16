#define pin1 0
#define pin2 2

void setup() {
  Serial.begin(115200);
  Serial.println("x,y");
//  Serial.print("\nStart OK");
  pinMode(pin1, 0);
  pinMode(pin2, 0);
}

bool x, y, oldx, oldy;
void loop() {
  x=digitalRead(pin1);
  y=digitalRead(pin2);

  //if(x!=oldx || y!=oldy){
    Serial.print(x);
    Serial.print(",");
    Serial.println(y);
  //}
  oldx=x; oldy=y;
  delay(10);
}
