#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h> //Скачиваем и устанавливаем библиотеку RF24 для радио модуля!!!!!!
#define CE_PIN   9
#define CSN_PIN 10
#define JOYSTICK_X   A0
#define JOYSTICK_1_Y A1
#define JOYSTICK_Z   A2
#define JOYSTICK_Z1  A3
#define JOYSTICK_2_Y A4
const uint64_t pipe = 0xE8E8F0F0E1LL; 
RF24 radio(CE_PIN, CSN_PIN); 
int joystick[9];
void setup()
{
  radio.begin();
  delay(2);
  radio.setChannel(9);
  radio.setDataRate(RF24_250KBPS);        // Установка минимальной скорости;
  radio.setPALevel(RF24_PA_HIGH);          // Установка максимальной мощности;
  radio.openWritingPipe(pipe);
       pinMode(2, INPUT);
  digitalWrite(2, HIGH);
       pinMode(3, INPUT);
  digitalWrite(3, HIGH);
       pinMode(4, INPUT);
  digitalWrite(4, HIGH);
       pinMode(5, INPUT);
  digitalWrite(5, HIGH);
 }
void loop()   
{
  joystick[0] = analogRead(JOYSTICK_X);
  joystick[0] = map(joystick[0],0,1023,1,180);
  joystick[1] = analogRead(JOYSTICK_1_Y);
  joystick[2] = analogRead(JOYSTICK_Z);
  joystick[2] = map(joystick[2],0,1023,1,180);
  joystick[3] = analogRead(JOYSTICK_2_Y);
  joystick[4] = analogRead(JOYSTICK_Z1);
  joystick[4] = map(joystick[4],0,1023,1,180);
  joystick[5] = digitalRead(2);
  joystick[6] = digitalRead(3);
  joystick[7] = digitalRead(4);
  joystick[8] = digitalRead(5);
  radio.write( joystick, sizeof(joystick) );
}
