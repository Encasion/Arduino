#define LOG_OUT 1 // use the log output function
#define FHT_N 256  // set to 256 point fht
#include <FHT.h>
#define MIC_PIN 0 
double prevVolts = 100.0;

#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))

int bass, mid, high;

int test;
void setup() {
  Serial.begin(9600);

  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  sbi(ADCSRA, ADPS0);

  analogReference(EXTERNAL);
}

void loop() {
  for (int i = 0 ; i < FHT_N ; i++) {
    int sample = analogRead(MIC_PIN);
    fht_input[i] = sample; // put real data into bins
  }
  fht_window();  // window the data for better frequency response
  fht_reorder(); // reorder the data before doing the fht
  fht_run();     // process the data in the fht
  fht_mag_log(); // take the output of the fht

  for (int curBin = 2; curBin < 10; ++curBin) {
    test = fht_log_out[curBin] - 30;
    test = constrain(test, 0, 200);
    
    bass = bass + test;
  }
  for (int curBin2 = 12; curBin2 < 30; ++curBin2) {
    test = fht_log_out[curBin2] - 30;
    test = constrain(test, 0, 200);
    
    mid = mid + test;
  }
  for (int curBin3 = 35; curBin3 < 100; ++curBin3) {
    test = fht_log_out[curBin3] - 30;
    test = constrain(test, 0, 200);
    
    high = high + test;
  }
  Serial.println(bass);
  Serial.println(mid);
  Serial.println(high);

  Serial.println("");
  delay(200);
  bass = 0;
  mid = 0;
  high = 0;

//Serial.println(fht_log_out[100]);

}
