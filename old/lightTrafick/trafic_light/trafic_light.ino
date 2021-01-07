uint8_t ledpin[3]={3, 4, 5}; //Піни світлодіодів (Red, Orange, Green)
int interval[3]={3000, 1000, 3000}; //Інтервал горіння кожного кольору (мс)

#define pause 3000 //Час включення кольору (мс)
#define blink 500 //Частота мігання при зміні

unsigned long time[4]; //Час (0-Red, 1-Orange, 2-Green, 3-all)
bool colorFlag[3]={0, 0, 0}; //Флаг активного кольору
bool oldFlag[3]={1, 0, 0}; // Флаг минулого активнрого кольору

volatile bool buttonFlag;

uint8_t u; //Змінна слідуючого кольору (для удобної роботи з масивом)

int test;

void setup() {
  Serial.begin(9600);
  for (int i=0; i<3; i++) 
    pinMode(ledpin[i], OUTPUT);
    
  attachInterrupt(0, button, RISING);
}

void button() { 
  buttonFlag=1; 
}

void loop() {
  time[3]=millis();
  for (int i=0; i<3; i++){
    if (i<2) u=i+1; else u=0; //Слідуючій колір (для удобної роботи з масивом)
    test = time[3]-time[i]; //Якшо написати (time[3]-time[i]>1000) зразу в if то работає не так як нада (нада провірити на практиці) 
    lightOn(i);
    lightOff(i);
  }

  Serial.print("flag");
  buttonCheck();  
}

void lightOn(int i) {
    if (oldFlag[i]){
      digitalWrite(ledpin[u], 1);
      oldFlag[i]=0;
      colorFlag[u]=1; time[u]=millis();
    }
}
void lightOff(int i) {
    if (colorFlag[i]==1 && test>interval[i]) {      
      for (int m=0; m<3; m++) {
        digitalWrite(ledpin[i], 1);
        delay(blink);
        digitalWrite(ledpin[i], 0);
        delay(blink);
      }
      colorFlag[i]=0;
      oldFlag[i]=1;
    }
}
void buttonCheck() {
  if (buttonFlag) {    
    for (int i=0; i<3; i++)
      while (colorFlag[i]) {
        time[3]=millis();
        test = time[3]-time[i];
        lightOff(i);
        oldFlag[i]=0;
      }
//    oldFlag[0]=0;
//    oldFlag[2]=0;
    oldFlag[1]=1;
    buttonFlag=0;
  }
}
