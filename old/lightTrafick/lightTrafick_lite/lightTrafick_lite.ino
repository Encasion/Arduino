
unsigned long gtime, rtime, btime, time;
bool gflag, rflag, bflag, goldflag, roldflag, boldflag, buttonflag;




void setup() {
  for (int i=3; i<6; i++)
  pinMode(i, OUTPUT);
  attachInterrupt(0, button, RISING);
  goldflag=1;
}

void loop() {
 light();
}
  
  // r3 b4 g5
   
void light() {
  time=millis();
  if (goldflag==1) {
    digitalWrite(3, 1);
    goldflag=0;
    rflag=1; rtime=millis();
  }
  if (roldflag==1) {
    digitalWrite(4, 1);
    roldflag=0;
    bflag=1; btime=millis();
  }
  if (boldflag==1) {
    digitalWrite(5, 1);
    boldflag=0;
    gflag=1; gtime=millis();
  }
 
  
  if (rflag==1 && time-rtime>1000){
    digitalWrite (3, 0);
    rflag=0;
    roldflag=1;
  }
  if (bflag==1 && time-btime>1000){
    digitalWrite (4, 0);
    bflag=0;
    boldflag=1;
  }
  if (gflag==1 && time-gtime>1000){
    digitalWrite (5, 0);
    gflag=0;
    goldflag=1;
  }

  
  if (buttonflag) {
    roldflag=0;
    boldflag=1;
    goldflag=0;
    
    rflag=0;
    bflag=0;
    gflag=0;
    
    buttonflag=0;
  }
  
}

void button() {
  buttonflag=1;
}
