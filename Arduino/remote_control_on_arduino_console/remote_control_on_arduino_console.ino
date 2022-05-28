#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9,10);//назначим пины SCK и CE соответственно
const uint64_t pipe = 0xF0F0F0F0E1LL;

//uint8_t joystick[7];
int joystick[7];

void setup() 
{
  delay(500);//подождать немного до установления напряжений на конденсаторах питания после подачи питания

  radio.begin();
  delay(2);
  radio.setRetries(15,15);
  radio.setChannel(9);                    // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
  radio.setDataRate(RF24_250KBPS);        // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
  radio.setPALevel(RF24_PA_HIGH);         // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.openWritingPipe(pipe);
  
    //инициализация входов
    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(6, INPUT);
    pinMode(7, INPUT);
    pinMode(8, INPUT);
    //pinMode(14, INPUT);//пин A0
    //pinMode(15, INPUT);//пин A1
    //pinMode(16, INPUT);//пин A2
    //pinMode(17, INPUT);//пин A3
    //pinMode(18, INPUT);//пин A4
    pinMode(19, INPUT);//пин A5
    pinMode(20, INPUT);//пин A6
    pinMode(21, INPUT);//пин A7
    //вкл. внутр. подтягивающие резисторы
    digitalWrite(2,HIGH);
    digitalWrite(3,HIGH);
    digitalWrite(4,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(6,HIGH);
    digitalWrite(7,HIGH);
    digitalWrite(8,HIGH);
    //digitalWrite(14,HIGH);
    //digitalWrite(15,HIGH);
    //digitalWrite(16,HIGH);
    //digitalWrite(17,HIGH);
    //digitalWrite(18,HIGH);
    digitalWrite(19,HIGH);
    digitalWrite(20,HIGH);
    digitalWrite(21,HIGH);
    
    delay(500);//ещё задержка на всякий случай
}

void loop() 
{
  //считывание с потенциометров для сервомоторов
  joystick[0] = analogRead(A0);
  joystick[0] = map(joystick[0],0,1023,1,180);
  joystick[1] = analogRead(A1);
  joystick[1] = map(joystick[1],0,1023,1,180);
  //опрос кнопок
  if(digitalRead(2))//если кнопка на пине 2 не нажата (т.е. на ней высокий уровень от внутренней подтяжки внутренним резистором)
  {
    joystick[2] |= 1<<0;//то запишем (в соответствующий бит) высокий уровень т.е. лог.1
  }
  else//иначе (т.е. если нажата)
  {
    joystick[2] &= ~(1<<0);//то запишем (в соответствующий бит) низкий уровень т.е. лог.0
  }
  //аналогично поступим с остальными кнопками
  if(digitalRead(3)){joystick[2] |= 1<<1;}else{joystick[2] &= ~(1<<1);}
  if(digitalRead(4)){joystick[2] |= 1<<2;}else{joystick[2] &= ~(1<<2);}
  if(digitalRead(5)){joystick[2] |= 1<<3;}else{joystick[2] &= ~(1<<3);}
  if(digitalRead(6)){joystick[2] |= 1<<4;}else{joystick[2] &= ~(1<<4);}
  if(digitalRead(7)){joystick[2] |= 1<<5;}else{joystick[2] &= ~(1<<5);}
  if(digitalRead(8)){joystick[2] |= 1<<6;}else{joystick[2] &= ~(1<<6);}
  if(digitalRead(19)){joystick[2] |= 1<<7;}else{joystick[2] &= ~(1<<7);}
  //if(digitalRead(18)){joystick[2] |= 1<<1;}else{joystick[2] &= ~(1<<1);}
  //if(digitalRead(19)){joystick[2] |= 1<<4;}else{joystick[2] &= ~(1<<4);}
  //считывание с потенциометров для ШИМов
  joystick[3] = analogRead(A2)/4;
  joystick[4] = analogRead(A3)/4;
  joystick[5] = analogRead(A4)/4;
  //ещё несколько кнопок
  if(digitalRead(20)){joystick[6] |= 1<<0;}else{joystick[6] &= ~(1<<0);}
  if(digitalRead(21)){joystick[6] |= 1<<1;}else{joystick[6] &= ~(1<<1);}
  
  //отослать данные
  radio.write( joystick, sizeof(joystick) );
  //delay(10);
}
