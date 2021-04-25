// Подключаем библиотеку SoftwareSerial
#include "SoftwareSerial.h"

// Создаем класс BTserial для работы с bluetooth модулем.
SoftwareSerial BTserial(8, 9); // порт RX, порт TX
 

// declare pins 

//left motor
int lm1=5;
int lm2=6;

//right motor
int rm1=2;
int rm2=3;

char command;
byte speed=5;

void setup()
{
    //init
    pinMode(lm1,OUTPUT);
    pinMode(lm2,OUTPUT);
    pinMode(rm1,OUTPUT);
    pinMode(rm2,OUTPUT);

    //set serial
    Serial.begin(9600);

    // Set BT
    BTserial.begin(9600);
}

void setMotors(uint8_t leftForward, uint8_t leftBackward,uint8_t rightForward, uint8_t rightBackward)
{
    digitalWrite(lm1,leftForward);
    digitalWrite(lm2,leftBackward);
    digitalWrite(rm1,rightForward);
    digitalWrite(rm2,rightBackward);
    
}

void loop()

{
    //while(Serial.available()==0);
    //val=Serial.read();
    //Serial.print(val);

    // Получаем данные от bluetooth модуля и передаем их в монитор порта.
    if (BTserial.available())
    {
      command=BTserial.read();
    }
  

    if (command<=9 and command>=0) {
              Serial.print('Set speed');
              Serial.print(command);
            }
            else
            {
              switch (command)
                     {
                      case 'F':
                              //forward
                              setMotors(HIGH,LOW,HIGH,LOW); 
                              break;
                      case 'B':
                              //backward
                              setMotors(LOW,HIGH,LOW,HIGH);
                              break;
                      case 'R':
                              //Right
                              setMotors(HIGH,LOW,LOW,HIGH);
                              break;
                      case 'L':
                              //Left
                              setMotors(LOW,HIGH,HIGH,LOW);
                              break; 
                      default:
                              //stop
                              Serial.print(command);
                              setMotors(LOW,LOW,LOW,LOW);
                              break;
                     }
    
              delay(500);
          }
}
