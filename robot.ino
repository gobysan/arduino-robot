
#include "SoftwareSerial.h"

#define BTrxPin 7
#define BTtxPin 8
 
// инициализируем новый последовательный порт
SoftwareSerial BTserial =  SoftwareSerial(BTrxPin, BTtxPin);
 
char cmd;
#define maxSpeed 255
byte speed=128;


//left motor
#define leftMotor1 5
#define leftMotor2 6

//right motor
#define rightMotor1 9
#define rightMotor2 10

//ШИМ пины для mini pro - 3,5,6,9,10,11


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // задаем режим работы выводов tx, rx:
  pinMode(BTrxPin, INPUT);
  pinMode(BTtxPin, OUTPUT);
  BTserial.begin(9600);
}

void setMotorsD(uint8_t leftForward, uint8_t leftBackward,uint8_t rightForward, uint8_t rightBackward)
{
    digitalWrite(leftMotor1,leftForward);
    digitalWrite(leftMotor2,leftBackward);
    digitalWrite(rightMotor1,rightForward);
    digitalWrite(rightMotor2,rightBackward);
    
}

void setMotorsA(uint8_t leftForward, uint8_t leftBackward,uint8_t rightForward, uint8_t rightBackward)
{
    analogWrite(leftMotor1,leftForward);
    analogWrite(leftMotor2,leftBackward);
    analogWrite(rightMotor1,rightForward);
    analogWrite(rightMotor2,rightBackward);
    
}


void loop() {
  // put your main code here, to run repeatedly:
  if (BTserial.available())
  {
    cmd=BTserial.read();
    Serial.println(cmd);  
    if (cmd<='9' && cmd>='0') {
              Serial.print("Set speed: ");
              Serial.print(cmd);
              Serial.print("0% ");
              speed=maxSpeed*(cmd-48)/9;
              Serial.println(speed);
            }
            else
            {
                switch (cmd) {
                      case 'F':
                              //forward
                              Serial.println("FORWARD");
                              //setMotorsD(HIGH,LOW,HIGH,LOW);
                              setMotorsA(speed,LOW,speed,LOW); 
                              break;
                      
                      case 'B':
                              //backward
                              Serial.println("BACK");
                              //setMotorsD(LOW,HIGH,LOW,HIGH);
                              setMotorsA(LOW,speed,LOW,speed);
                              break;
                      case 'R':
                              //Right
                              Serial.println("RIGHT");
                              //setMotorsD(HIGH,LOW,LOW,HIGH);
                              setMotorsA(speed,LOW,LOW,speed);
                              break;
                      case 'L':
                              //Left
                              Serial.println("LEFT");
                              //setMotorsD(LOW,HIGH,HIGH,LOW);
                              setMotorsA(LOW,speed,speed,LOW);
                              break; 
                      case 'D':
                              //stop
                              Serial.println("STOP");
                              //setMotorsD(LOW,LOW,LOW,LOW);
                              setMotorsA(LOW,LOW,LOW,LOW);
                              break;
                              
                     }
            }
  delay(100);
    }
}
