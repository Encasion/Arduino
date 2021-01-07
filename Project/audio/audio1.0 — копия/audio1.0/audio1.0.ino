#define LOG 1
#define LOG_OUT 1 
#define FHT_N 256  // set to 256 point fht
#include <FHT.h>
#define MIC_PIN 0 
double prevVolts = 100.0;

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define INPUT_GAIN 1.5 //усиление 

#define BASS 85
#define MID 65
#define HIGh 35  //мінімальний шум 

#define Sbu 0.15 //плавность наростания яркости bass up
#define Sbd 0.87 //плавность убывания яркости bass down
#define Smu 0.95 
#define Smd 0.9 
#define Shu 0.95 
#define Shd 0.88 

byte posSet[6] = {2, 7, 12, 30, 35, 100};

byte LOW_PASS[3] = {BASS, MID, HIGh};
// int bass, mid, high;

byte value[3];
byte oldValue[3];
byte maxValue[4], oldmax;
byte a;

unsigned long timer;

void setup() {
  Serial.begin(9600);

  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS0);

  analogReference(EXTERNAL);
  
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);

}     

void loop() { if (millis() - timer > 30){ 
  timer = millis();
  analyze();
  int q = 0;
  for (int i=0; i<3; i++){
    maxValue[i] = 0;
    value[i] = 0;  
  }
  
   if (oldmax < 25){
    if (LOW_PASS[0] > BASS-20) LOW_PASS[0]--;
    if (LOW_PASS[1] > MID-20) LOW_PASS[1]--;  
    if (LOW_PASS[2] > HIGh-5) LOW_PASS[2]--;   
   } else {
     if (LOW_PASS[0] < BASS) LOW_PASS[0]++;
     if (LOW_PASS[1] < MID) LOW_PASS[1]++;
     if (LOW_PASS[2] < HIGh) LOW_PASS[2]++;
    } 
  
  for (int i = 2; i < 128; i++) {
    if (i >= posSet[0] && i <= posSet[1]) a = 0; else 
    if (i >= posSet[2] && i <= posSet[3]) a = 1; else 
    if (i >= posSet[4] && i <= posSet[5]) a = 2; 
      if (fht_log_out[i] < LOW_PASS[a]) fht_log_out[i] = 0;
      
      fht_log_out[i] = (float)fht_log_out[i] * INPUT_GAIN;
     // fht_log_out[i] = (float)fht_log_out[i] / ((float)1 + (float)i / 128);
      if (fht_log_out[i] > maxValue[3]) maxValue[3] = fht_log_out[i];
  }
   oldmax = (oldmax + maxValue[3])/2;
  for (int pos = posSet[0]; pos <= posSet[1]; pos++){
    if (fht_log_out[pos]>0){
      value[0] += fht_log_out[pos];
      q++;
      if (fht_log_out[pos] > maxValue[0]) maxValue[0] = fht_log_out[pos];
    }  
    if (pos == posSet[1])if (q>4) value[0] = value[0] / q; else value[0] = value[0] / 4;
  }
  for (int pos = posSet[2]; pos <= posSet[3]; pos++){
    if (fht_log_out[pos]>0){
      value[1] = value[1] + fht_log_out[pos];
      q++;
      if (fht_log_out[pos] > maxValue[1]) maxValue[1] = fht_log_out[pos];
    }  
    if (pos == posSet[3])if (q>4) value[1] = value[1] / q; else value[1] = value[1] / 4; 
  }  
  for (int pos = posSet[4]; pos <= posSet[5]; pos++){
    if (fht_log_out[pos]>0){
      value[2] += fht_log_out[pos];
      q++;
      if (fht_log_out[pos] > maxValue[2]) maxValue[2] = fht_log_out[pos];
    }  
    if (pos == posSet[5])if (q>4) value[2]  = value[2] / q; else value[2] = value[2] / 4;
  }

  for (int i=0; i<3; i++)
    if (maxValue[3] >70) value[i] = map(value[i], 0, maxValue[3], 5, 255); 
    else value[i] = map(value[i], 0, 70, 5, 255);  

    
  if (value[0] > oldValue[0] && value[0] - oldValue[0] > 20) value[0] = oldValue[0] * Sbu + value[0] * (1 - Sbu); else value[0] = oldValue[0] * Sbd + value[0] * (1 - Sbd); 
  if (value[1] > oldValue[1] && value[1] - oldValue[1] > 20) value[1] = oldValue[1] * Smu + value[1] * (1 - Smu); else value[1] = oldValue[1] * Smd + value[1] * (1 - Smd);
  if (value[2] > oldValue[2] && value[2] - oldValue[2] > 20) value[2] = oldValue[2] * Shu + value[2] * (1 - Shu); else value[2] = oldValue[2] * Shd + value[2] * (1 - Shd);


  value[0] = constrain(value[0], 1, 255);
  value[1] = constrain(value[1], 1, 255);
  value[2] = constrain(value[2], 1, 255);
  
  oldValue[0] = value[0];
  oldValue[1] = value[1];
  oldValue[2] = value[2];
  
  analogWrite(11, value[0]);
  analogWrite(10, value[1]);
  analogWrite(9, value[2]);

  if (LOG){  
    /*
    Serial.print("bass: ");
    Serial.println(value[0]);
    Serial.print("mid: ");
    Serial.println(value[1]);
    Serial.print("high: ");
    Serial.println(value[2]);
    */
//    /*
    Serial.print("maxBASS: ");
    Serial.println(maxValue[0]);
    Serial.print("maxMID: ");
    Serial.println(maxValue[1]);
    Serial.print("maxHIGH: ");
    Serial.println(maxValue[2]);
    Serial.print("max: ");
    Serial.println(maxValue[3]);
//    */
    /*
    Serial.print("oldmax: ");
    Serial.println(oldmax);
    Serial.println(" "); 
    */
    
    /* 
      for (int i=0; i<3; i++){
      Serial.print("LOW_PASS[i]: ");
      Serial.println(LOW_PASS[i]);
      }
    Serial.println(" ");
    */
  }
}
}

void analyze() {
  for (int i = 0 ; i < FHT_N ; i++) {
    int sample = analogRead(MIC_PIN);
    fht_input[i] = sample; // put real data into bins
  }
  fht_window();  // window the data for better frequency response
  fht_reorder(); // reorder the data before doing the fht
  fht_run();     // process the data in the fht
  fht_mag_log(); // take the output of the fht
}
