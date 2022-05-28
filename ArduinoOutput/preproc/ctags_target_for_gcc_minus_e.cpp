# 1 "d:\\Arduino\\Arduino\\remote_control_on_arduino\\remote_control_on_arduino.ino"
# 2 "d:\\Arduino\\Arduino\\remote_control_on_arduino\\remote_control_on_arduino.ino" 2
# 3 "d:\\Arduino\\Arduino\\remote_control_on_arduino\\remote_control_on_arduino.ino" 2
# 4 "d:\\Arduino\\Arduino\\remote_control_on_arduino\\remote_control_on_arduino.ino" 2
# 5 "d:\\Arduino\\Arduino\\remote_control_on_arduino\\remote_control_on_arduino.ino" 2

RF24 radio(9,10);//назначим пины SCK и CE соответственно
const uint64_t pipe = 0xF0F0F0F0E1LL;

//uint8_t joystick[7];
int joystick[7];
Servo servo1;
Servo servo2;

long previousMillis = 0;

void setup()
{
  delay(500);//подождать немного до установления напряжений на конденсаторах питания после подачи питания

  radio.begin();
  radio.setRetries(15,15);
  radio.setChannel(9); // Указываем канал передачи данных (от 0 до 127), 5 - значит передача данных осуществляется на частоте 2,405 ГГц (на одном канале может быть только 1 приёмник и до 6 передатчиков)
  radio.setDataRate(RF24_250KBPS); // Указываем скорость передачи данных (RF24_250KBPS, RF24_1MBPS, RF24_2MBPS), RF24_1MBPS - 1Мбит/сек
  radio.setPALevel(RF24_PA_HIGH); // Указываем мощность передатчика (RF24_PA_MIN=-18dBm, RF24_PA_LOW=-12dBm, RF24_PA_HIGH=-6dBm, RF24_PA_MAX=0dBm)
  radio.openReadingPipe(1,pipe);
  radio.startListening();


  //инициализация сервомоторов
  servo1.attach(14);
  servo2.attach(15);

  //инициализация цифровых выходов
  pinMode(2, 0x1);
  pinMode(3, 0x1);//ШИМ с A2 передатчика
  pinMode(4, 0x1);
  pinMode(5, 0x1);//ШИМ с A3 передатчика
  pinMode(6, 0x1);//ШИМ с A4 передатчика
  pinMode(7, 0x1);//пьезодинамик
  pinMode(8, 0x1);//пьезодинамик

  pinMode(14, 0x1);//пин A0//сервомотор1
  pinMode(15, 0x1);//пин A1//сервомотор2
  pinMode(16, 0x1);//пин A2//с кнопки на пине 3 передатчика
  pinMode(17, 0x1);//пин A3//с кнопки на пине 5 передатчика
  pinMode(18, 0x1);//пин A4//с кнопки на пине 6 передатчика
  pinMode(19, 0x1);//пин A5
  pinMode(20, 0x1);//пин A6
  pinMode(21, 0x1);//пин A7

  //для правильной работы сирены в последующем
  digitalWrite(7, 0x1);
  digitalWrite(8, 0x0);

  delay(500);//ещё задержка на всякий случай
}

void loop()
{
  if ( radio.available() )
  {
    bool done = false;
    while (!(radio.read( joystick, sizeof(joystick) ))
    {
      //radio.read( joystick, sizeof(joystick) );

      //поворачиваем сервомоторы
      servo1.write(joystick[0]);
      servo2.write(joystick[1]);

      //выводим состояния кнопок
      digitalWrite( 2, joystick[2] & (1<<0) );
      digitalWrite( 4, joystick[2] & (1<<2) );
      digitalWrite( 16, joystick[2] & (1<<1) );
      digitalWrite( 17, joystick[2] & (1<<3) );
      digitalWrite( 18, joystick[2] & (1<<4) );
      digitalWrite( 19, joystick[2] & (1<<7) );
      digitalWrite( 20, joystick[6] & (1<<0) );
      digitalWrite( 21, joystick[6] & (1<<1) );

      //звуковой сигнал
      if( !(joystick[2] & (1<<5)) )
      {
         if (micros() -previousMillis >200)
         {
           previousMillis = micros();
           //сирена
           digitalWrite(7,!digitalRead(7));
           digitalWrite(8,!digitalRead(8));
         }
      }
      //звуковой сигнал
      if( !(joystick[2] & (1<<6)) )
      {
         if (micros() -previousMillis >500)
         {
           previousMillis = micros();
           //сирена
           digitalWrite(7,!digitalRead(7));
           digitalWrite(8,!digitalRead(8));
         }
      }

      //выводим состояния потенцимометров для ШИМов
      analogWrite(3, joystick[3]);
      analogWrite(5, joystick[4]);
      analogWrite(6, joystick[5]);

    }
  }
}
