//EN 6, 12
#define m1a 2
#define m1b 4
#define m2a 7
#define m2b 8
#define PWM1 9
#define PWM2 10

#define playpin 3
#define nextpin 5
#define backpin 11

#define diode 13

#define tr1 5 // довжина першого трека в секундах
#define tr2 10
#define tr3 30
#define tr4 5
#define tr5 7 //довжина пятого трека в секундах


int speedl = 255;
int speedr = 255;

char terminale;



int i;
int track = 1;

bool stan = 0;

unsigned long time;
unsigned long oldtime; 
 
void setup() {
 Serial.begin(9600);
 pinMode(m1a, OUTPUT);
 pinMode(m1b, OUTPUT);
 pinMode(m2a, OUTPUT);
 pinMode(m2b, OUTPUT);
 pinMode(PWM1, OUTPUT);
 pinMode(PWM2, OUTPUT);

 pinMode(playpin, OUTPUT);
 pinMode(nextpin, OUTPUT);
 pinMode(backpin, OUTPUT);
 

 analogWrite (PWM1, speedl);
 analogWrite (PWM2, speedr); 

 pinMode(13, OUTPUT);
 digitalWrite(13, 1);
}

void loop() {
  digitalWrite(diode, 0);
  if (Serial.available()){
    digitalWrite(diode, 1);
    terminale = Serial.read();
    
    switch (terminale){
      case '-':
        if (speedl>0 && speedr>0){
          speedl = speedl - 5;
          speedr = speedr - 5;
          analogWrite(PWM1, speedl);
          analogWrite(PWM2, speedr);
          }
      break;
      case '+':
        if (speedl<255 && speedr<255){
          speedl = speedl + 5;
          speedr = speedr + 5;
          analogWrite(PWM1, speedl);
          analogWrite(PWM2, speedr);
          }
       break;
        case 'v':
          vpered();
       break;
        case 'n':
          nazad();
       break;
        case 'p':
          pravo();
       break;
        case 'l':
          levo();
       break;
        case 's':
          stopp();
       break;
        case 'q':
          back();
       break;
        case 'e':
          next();
       break;  
        case 'w':
          play();
          
       break;
       case '1':
        while (track < 1)
          next();
          delay(100);
        while (track > 1) 
          back();
          delay(100);
        if (track == 1)
          play();
          oldtime = millis();

          
       break;
       case '2':
        while (track < 2)
          next();
          delay(100);
        while (track > 2) 
          back();
          delay(100);
        if (track == 2)
          play();  
        break;
        case '3':
        while (track < 3)
          next();
          delay(100);
        while (track > 3) 
          back();
          delay(100);
        if (track == 3)
          play();  
        break;
        case '4':
        while (track < 4)
          next();
          delay(100);
        while (track > 4) 
          back();
          delay(100);
        if (track == 4)
          play();  
        break;
       case '5':
        while (track < 5)
          next();
          delay(100);
        while (track > 5) 
          back();
          delay(100);
        if (track == 5)
          play();  
        break;
       
    }
  }
 // Serial.println(terminale);
 // Serial.println(speedl);
 // Serial.println(speedr);
 // Serial.println(stan);
 // Serial.println(oldtime);
 // Serial.println(track);
 // delay(1000);
 proverka();
 Serial.println(round ((millis() - oldtime)/1000));
}




void play(){
  if (stan == 0){ 
  digitalWrite(playpin, 1);
  delay(100);
  digitalWrite(playpin, 0);
  stan = !stan;  
    }  
  }
void pause(){
  if (stan == 1){
    digitalWrite(playpin, 1);
    delay(100);
    digitalWrite(playpin, 0);
    stan = !stan;
    }
  }
void next(){
  digitalWrite(nextpin, 1);
  delay(100);
  digitalWrite(nextpin, 0);
  track++;
  if (stan == 0)
  stan = !stan;
  delay(100);
  play();
  Serial.println("next");
  }
void back(){
  digitalWrite(backpin, 1);
  delay(100);
  digitalWrite(backpin, 0); 
  track--;
  if (stan == 0)
  stan = !stan;
  delay(100);
  play();
  Serial.println("back");
  }
void vpered(){
  digitalWrite (m1a, 1);
  digitalWrite (m1b, 0);
  digitalWrite (m2a, 1);
  digitalWrite (m2b, 0);
  delay(10);
  }
void nazad(){
  digitalWrite (m1a, 0);
  digitalWrite (m1b, 1);
  digitalWrite (m2a, 0);
  digitalWrite (m2b, 1);
  delay(10);
  }
void levo(){
  digitalWrite (m1a, 1);
  digitalWrite (m1b, 0);
  digitalWrite (m2a, 0);
  digitalWrite (m2b, 1);
  delay(10);
  } 
void pravo(){
  digitalWrite (m1a, 0);
  digitalWrite (m1b, 1);
  digitalWrite (m2a, 1);
  digitalWrite (m2b, 0);
  delay(10);
  }
void stopp(){
  digitalWrite (m1a, 0);
  digitalWrite (m1b, 0);
  digitalWrite (m2a, 0);
  digitalWrite (m2b, 0);
  }
void proverka (){
  switch (track){
    case 1:
       if (round ((millis() - oldtime)/1000) > tr1)
       pause();
       Serial.println("stop");
      break;
    case 2:
       if (round ((millis() - oldtime)/1000) > tr2)
       pause();
       Serial.println("stop");
      break;
    case 3:
       if (round ((millis() - oldtime)/1000) > tr3)
       pause();
       Serial.println("stop");
      break;
     case 4:
       if (round ((millis() - oldtime)/1000) > tr4)
       pause();
       Serial.println("stop");
      break;
    case 5:
       if (round ((millis() - oldtime)/1000) > tr5)
       pause();
       Serial.println("stop");
      break;
      }
  }
