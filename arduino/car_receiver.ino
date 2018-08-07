#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo baseServo;
String str;

RF24 radio(7, 8); // CE, CSN

// Define output pins for motors
#define motor1_pin_1 5
#define motor1_pin_2 4
#define motor2_pin_1 3
#define motor2_pin_2 2
#define MIN 0
#define MAX 180

const byte addresses[][6] = {"00001", "00002"};

int servoPos = 90;

void setup() {
  radio.begin();
  radio.openReadingPipe(1, addresses[1]);
  radio.setPALevel(RF24_PA_HIGH);
  Serial.begin(9600);

  Serial.println("Inside Rx setup");
  pinMode(motor1_pin_1, OUTPUT);
  pinMode(motor1_pin_2, OUTPUT);
  pinMode(motor2_pin_1, OUTPUT);
  pinMode(motor2_pin_2, OUTPUT);

  baseServo.attach(9);
  baseServo.write(servoPos);
}

void loop() {
  delay(5);
  radio.startListening();
  if (radio.available()) {
    Serial.println("Inside Rx available");
    while (radio.available()) {
      char text[32] = "";
      byte rxLen = radio.getDynamicPayloadSize();
      radio.read(text, rxLen);
      Serial.println(text);
      str = String(text);
      Serial.println(str);
      Serial.println(servoPos);
      if (strcmp(text, "S") == 0) {
        moveFront();
      } else {
        stopCar();
      }
      if (strcmp(text, "T") == 0) {
        moveBack();
      } else {
        stopCar();
      }
      if (strcmp(text, "U") == 0) {
        moveLeft();
      } else {
        stopCar();
      }
      if (strcmp(text, "V") == 0) {
        moveRight();
      } else {
        stopCar();
      }
      if (str.startsWith("Z")) {  
        servoPos -= 2;
        if (servoPos < 0) {
          servoPos = 0;
        }
        baseServo.write(servoPos);
        delay(5);        
      }
      if (str.startsWith("Y")) {
        servoPos += 2;
        if (servoPos > 180) {
          servoPos = 180;
        }
        baseServo.write(servoPos);
        delay(5);
      }
    }
  }
}

void moveFront() {
  Serial.println("Move front");
  digitalWrite(motor1_pin_1, HIGH);
  digitalWrite(motor1_pin_2, LOW);
  digitalWrite(motor2_pin_1, HIGH);
  digitalWrite(motor2_pin_2, LOW);
}

void moveBack() {
  Serial.println("Move back");
  digitalWrite(motor1_pin_1, LOW);
  digitalWrite(motor1_pin_2, HIGH);
  digitalWrite(motor2_pin_1, LOW);
  digitalWrite(motor2_pin_2, HIGH);
}

void moveRight() {
  Serial.println("Move left");
  digitalWrite(motor1_pin_1, HIGH);
  digitalWrite(motor1_pin_2, LOW);
  digitalWrite(motor2_pin_1, LOW);
  digitalWrite(motor2_pin_2, LOW);
}

void moveLeft() {
  Serial.println("Move left");
  digitalWrite(motor1_pin_1, LOW);
  digitalWrite(motor1_pin_2, LOW);
  digitalWrite(motor2_pin_1, HIGH);
  digitalWrite(motor2_pin_2, LOW);
}

void stopCar() {
//  Serial.println("Car stopped");
  digitalWrite(motor1_pin_1, LOW);
  digitalWrite(motor1_pin_2, LOW);
  digitalWrite(motor2_pin_1, LOW);
  digitalWrite(motor2_pin_2, LOW);
}

