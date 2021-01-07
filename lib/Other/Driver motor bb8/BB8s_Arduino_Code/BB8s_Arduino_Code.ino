#include "DualVNH5019MotorShield.h"
DualVNH5019MotorShield md;
/*
#include <Servo.h>
Servo myservo; 
*/

char dataIn='S';
char determinant;
char det;
int vel = 200; //Bluetooth Stuff

int overdrive = 13; //Press Toggle Switch #1, the pin13 LED will light up

void setup(){
Serial.begin(9600);md.init();

/*
myservo.attach(6);delay(100);
myservo.write(90);delay(100);
*/

}

void loop(){ det = check();  // You'll need to reconstruct this if your not using the Pololu Dual VNH5019
     
      while (det == 'F')   // F, move forward
       {md.setSpeeds(vel,vel);det = check();}
     
      while (det == 'B')   // B, move back
       {md.setSpeeds(-vel,-vel);det = check();}

      while (det == 'L')   // L, move wheels left
       {md.setSpeeds(-vel,vel);det = check();}
      
      while (det == 'R')   // R, move wheels right
       {md.setSpeeds(vel,-vel);det = check();}
    
      while (det == 'I')   // I, turn right forward
       {md.setSpeeds(vel,vel/2);det = check();}
    
      while (det == 'J')   // J, turn right back
       {md.setSpeeds(-vel,-vel/2);det = check();}  
     
      while (det == 'G')   // G, turn left forward
       {md.setSpeeds(vel/2,vel);det = check();}
    
      while (det == 'H')   // H, turn left back
       {md.setSpeeds(-vel/2,-vel);det = check();}  
     
      while (det == 'S')   // S, stop
       {md.setSpeeds(0,0);det = check();}
      
      //---------------------Toggle switch code------------------//
      /*while (det == 'W'){myservo.write(180);delay(100);det = check();} 
      while (det == 'w'){myservo.write(90);delay(100);det = check();} 
       
      while (det == 'U'){myservo.write(0);delay(100);det = check();} 
      while (det == 'u'){myservo.write(90);delay(100);det = check();} 
      */

}

int check()
{if (Serial.available() > 0) {dataIn = Serial.read(); 
        if (dataIn == 'F'){determinant = 'F';} 
        else if (dataIn == 'B'){determinant = 'B';}else if (dataIn == 'L'){determinant = 'L';}
        else if (dataIn == 'R'){determinant = 'R';}else if (dataIn == 'I'){determinant = 'I';} 
        else if (dataIn == 'J'){determinant = 'J';}else if (dataIn == 'G'){determinant = 'G';}   
        else if (dataIn == 'H'){determinant = 'H';}else if (dataIn == 'S'){determinant = 'S';}
        else if (dataIn == '0'){vel = 400;}else if (dataIn == '1'){vel = 380;}
        else if (dataIn == '2'){vel = 340;}else if (dataIn == '3'){vel = 320;}
        else if (dataIn == '4'){vel = 280;}else if (dataIn == '5'){vel = 240;}
        else if (dataIn == '6'){vel = 200;}else if (dataIn == '7'){vel = 160;}
        else if (dataIn == '8'){vel = 120;}else if (dataIn == '9'){vel = 80;}
        else if (dataIn == 'q'){vel = 40;}
        else if (dataIn == 'U'){determinant = 'U';}else if (dataIn == 'u'){determinant = 'u';}
        else if (dataIn == 'W'){determinant = 'W';}else if (dataIn == 'w'){determinant = 'w';}
        
        }return determinant;}
