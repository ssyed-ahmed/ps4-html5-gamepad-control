#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

String inputString = "";
boolean stringComplete = false;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.stopListening();
  Serial.begin(9600);
  inputString.reserve(200);
  Serial.println("Hello from arduino");
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString + "\r\n");
    //Transmit the inputString using the radio
    const char text[8];
    inputString.toCharArray(text, 8);
    radio.write(&text, sizeof(text));
    delay(500);
    //Clear the string
    inputString = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char) Serial.read();
    inputString += inChar;
    // Check if the string is complete
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
