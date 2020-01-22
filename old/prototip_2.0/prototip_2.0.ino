#include "Servo.h" //підключаємо бібліотеку для керування сервоприводом;
#define servop 9  //вказуєм на який пін підключений сервомотор;
Servo servo1; //вводимо клас "Servo" з імям "servo1;

#define trig 8  //пін передачі ультразвукового датчика;
#define echo 12 //пін прийому ультразвукового датчика;

#define diode 7 //пін діода;
#define pip 10 //пін пєзо динаміка;


#define in1 4 //піни драйвера для мотору;
#define in2 5
#define in3 2
#define in4 3
#define enr 6
#define enl 11

int k = 25 ; //коефіцієнт повороту машинки по відношенню до кута сервопривода *10 (ліноліум 14)
int zona = 60; //зона контролю (см)
int control = 35; //дистанція на яку машинка не підходить до цілі (см)

int speed = 255; //початкова швидкість моторів;

int i; //змінна для використання в циклі for;
bool goal = 0; //змінна для запамятовування цілі;

bool mode = 0; //змінна для переключення режиму (ручний, авто);
char datain; //змінна для прийому данних з Serial;

int distance; //змінна для запамятовування дистанції;
int impuls; //змінна для часу імпульсу з ультразвукового датчика;

void setup () {
  Serial.begin(9600); //активація Serial порта на швидкості 9600 бод;
  servo1.attach(servop); //вказання піна сервопривода (замість "servop" буде підставленне значення що вказано вище в #define;
  pinMode(diode, OUTPUT); //активація пінів на прийом та передачу сигналу;
  pinMode(pip, OUTPUT);
  
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
  
  servo1.write(90); //виставлення сервопривода на кут 90 градусів;
  
  analogWrite (enl, speed); //виставлення швидкості моторів;
  analogWrite (enr, speed);
  }
  
void loop () {
     proverka(); //запуск функцій які описані нище;
     rychnoe();
     avto(); 
 }
 
void proverka(){
  if (Serial.available() > 0){ //якщо получені данні з Serial порта то...;
    digitalWrite(diode, 0); //виключення діода;
    
    datain = Serial.read(); //запис данних з Serial порта;
    switch (datain){ //перевірка значень з Serial порта;
      case '0':
        mode=0; //переключення в ручний режим;
      break;
      case '1':
        mode=1; //автоматичний режим;
      break;
      case 'q':
        k++; //додати 1 до коефіцієнта;
      break;
      case 'e':
        k--; //відняти 1 від коефіцієнта;
      break;
    }  
  }
}
  
void rychnoe(){
  while(mode==0){
    servo1.write(90);
    digitalWrite(diode, 0); 
    
/*   Serial.print("k: ");
   Serial.println(k);
   Serial.print("speed: ");
   Serial.println(speed);
*/
   
     if (Serial.available()){ 
     datain = Serial.read();
     switch(datain){
      case 'q':
        k++;
        break;
      case 'e':
        k--;
        break;
      case '1':
        mode = 1;
        break;
      case 'f':
        forward();
        break;
      case 'b':
        backward();
        break;
      case 'l':
        left();
        break;
      case 'r':
        right();
        break;
      case 's':
        stopp();
        break;
      case 'a':
        left();
        delay(90*k/10); //поворот на 90 градусів вліво;
        stopp();
        break;
      case 'd':
        right();
        delay(90*k/10); //поворот на 90 градусів вправо;
        stopp();
        break;
      case '-':
        if (speed > 0){ //зменшення швидкості на 5;
        speed -= 5;
        analogWrite(enl, speed);
        analogWrite(enr, speed);
        }
        break;
      case '+':
        if (speed < 255){ //збільшення швидкості на 5;
        speed += 5;
        analogWrite(enl, speed);
        analogWrite(enr, speed);
        }
        break;
      } 
     } 
    } 
  } 
  
void poisk(){
    digitalWrite(diode, 0);
    digitalWrite(pip, 0);
    
    for (int d=0; d<5 && goal==0; d++){ //пять разів сканувати перед собою (для зменшення похибки);
      proverka(); //перевірка режиму роботи;
      if (mode==0) //якщо режим ручний то вийти з цикла;
      break;
                  
      servo1.write(90); //поворот серво на 90; 
      delay(5);
      digitalWrite(trig, 1); 
      delayMicroseconds(10);
      digitalWrite(trig, 0);
      impuls = pulseIn(echo, 1); //перевірка довжини імпульсу;
      distance = impuls/58; //конвертація довжини імпульсу в сантиметри;
      
//   Serial.print("SM: ");
//   Serial.println(distance);     

  if (distance < zona && distance > 0){ //якщо дистанція менше чім охороняйма зона то активація цілі;
       goal = 1; 
       break;
       }
      }
      
   for (i=90; i>0 && i<179 && goal==0; i--){ //поворот серво від центру вліво;
      proverka();
      if (mode==0)
      break;
                  
      servo1.write(i);
      delay(5);
      digitalWrite(trig, 1);
      delayMicroseconds(10);
      digitalWrite(trig, 0);
      impuls = pulseIn(echo, 1);
      distance = impuls/58; 

//   Serial.print("SM: ");
//   Serial.println(distance);

        
       if (distance < zona && distance > 0){
       goal = 1;
       break;
       }
       
      if (i==1)
      for (i=90; i<180 && goal==0; i++){
      proverka();
      if (mode==0)
      break;
            
      servo1.write(i);
      delay(5);
      digitalWrite(trig, 1);
      delayMicroseconds(10);
      digitalWrite(trig, 0);
      impuls = pulseIn(echo, 1);
      distance = impuls/58;

//   Serial.print("SM: ");
//   Serial.println(distance);
    
      if (distance < zona && distance > 0){
       goal = 1;
       break;
      } 
        } 
   } 
} 
    
void avto(){ 
  while (mode==1){
      poisk();  
      if (goal==0 && mode==1){  //якщо після пошуку цілі не знайдено то повернутись на 90 градусів вправо;
       right();
       delay(90*k/10);
       stopp();
       } 
   while (goal==1){
    if (i<93 && i>87){ //якщо ціль перед нами - рухатись вперед;
      if (distance > control){
      digitalWrite(diode, 1);
      digitalWrite(pip, 1);
      forward();
      delay(100);
      stopp();
      goal=0;
      break;
      } else {
        digitalWrite(diode, 1);
        digitalWrite(pip, 1);
        delay(50);
        goal=0;
        break;}
    } 
    if (i<90){ //якщо ціль зліва - рухатись вліво;
      digitalWrite(diode, 1);
      digitalWrite(pip, 1);  
      left();
      delay((90-i)*k/10);
      stopp();
      goal=0;
      break;
      }
    if (i>90){ //якщо ціль зправа - рухатись вправо;
      digitalWrite(diode, 1);
      digitalWrite(pip, 1);
      right();
      delay((i-90)*k/10);
      stopp();
      goal=0;
      break;
      } 
    } 
  } 
}
  
void forward(){ //рух вперед;
  digitalWrite (in1, 1);
  digitalWrite (in2, 0);
  digitalWrite (in3, 1);
  digitalWrite (in4, 0);
  delay(10);
  }
void backward(){ //рух назад
  digitalWrite (in1, 0);
  digitalWrite (in2, 1);
  digitalWrite (in3, 0);
  digitalWrite (in4, 1);
  delay(10);
  }
void left(){ //рух вліво;
  digitalWrite (in1, 0);
  digitalWrite (in2, 1);
  digitalWrite (in3, 1);
  digitalWrite (in4, 0);
  delay(10);
  } 
void right(){ //рух вправо;
  digitalWrite (in1, 1);
  digitalWrite (in2, 0);
  digitalWrite (in3, 0);
  digitalWrite (in4, 1);
  delay(10);
  }
void stopp(){ //припинення руху;
  digitalWrite (in1, 0);
  digitalWrite (in2, 0);
  digitalWrite (in3, 0);
  digitalWrite (in4, 0);
  }
