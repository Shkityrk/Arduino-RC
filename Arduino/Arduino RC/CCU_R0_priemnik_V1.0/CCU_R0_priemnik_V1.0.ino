#include <SPI.h>
#include <nRF24L01.h> 
#include <RF24.h> //Скачиваем и устанавливаем библиотеку RF24 для радио модуля!!!!!!!!!
#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
#define CE_PIN   2
#define CSN_PIN 9
int pwm = 0;
int pwm2 = 0;
const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(CE_PIN, CSN_PIN); 
int joystick[9];
//unsigned long time;
void setup()   
{
  delay(50);
  radio.begin();
  radio.setChannel(9);
  radio.setDataRate(RF24_250KBPS);        // Установка минимальной скорости;
  radio.setPALevel(RF24_PA_HIGH);          // Установка максимальной мощности;
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  myservo1.attach(4);
  myservo2.attach(8); 
  myservo3.attach(3);
  pinMode(7, OUTPUT);
  pinMode(10, OUTPUT);
  digitalWrite(10,LOW);
  pinMode(14, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
}


void loop()  
{
  if ( radio.available() )
  {
    //time = millis();
    bool done = false;
    while (!done)
    {
      done = radio.read( joystick, sizeof(joystick) );
     // if (millis() - time > 1000){
      //joystick[0]=0;
      //joystick[1]=0;
      //joystick[2]=0;
      //joystick[3]=0;
      //joystick[4]=0;
      //joystick[5]=0;
      //joystick[6]=0;
      //joystick[7]=0;
      //joystick[8]=0;}
      myservo1.write(joystick[0]);
      myservo2.write(joystick[2]);
      myservo3.write(joystick[4]);
      digitalWrite(14, !joystick[5]);
      digitalWrite(15, !joystick[6]);
      digitalWrite(16, !joystick[7]);
      digitalWrite(7, !joystick[8]);  
      
     if(joystick[1]==512)
{    digitalWrite(17,LOW);
     digitalWrite(10,LOW);
}
             if(joystick[1]>524)
             {   pwm = map(joystick[1], 524,1024,10,255);
                 analogWrite(5,pwm);
                 digitalWrite(17,LOW);
                 digitalWrite(10,HIGH);
             }
                         if(joystick[1]<500)
                         {   pwm = map(joystick[1],500,0,10,255);
                             analogWrite(5,pwm);
                             digitalWrite(17,HIGH);
                             digitalWrite(10,LOW);
                         }
                         
if(joystick[3]==512)
{    digitalWrite(18,LOW);
     digitalWrite(19,LOW);
}
             if(joystick[3]>524)
             {   pwm2 = map(joystick[3], 524,1024,10,255);
                 analogWrite(6,pwm2);
                 digitalWrite(18,LOW);
                 digitalWrite(19,HIGH);
             }
                           if(joystick[3]<500)
                           {   pwm2 = map(joystick[3],500,0,10,255);
                               analogWrite(6,pwm2);
                               digitalWrite(18,HIGH);
                               digitalWrite(19,LOW);
                           }          
  }
  }
  else
  {       
  }
  }
