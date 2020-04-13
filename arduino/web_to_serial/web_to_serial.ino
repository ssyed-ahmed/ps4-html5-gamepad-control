#include <SPI.h>
//#include <nRF24L01.h>
//#include <RF24.h>
//
//RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

String inputString = "";
boolean stringComplete = false;

void setup() {
//  radio.begin();
//  radio.openWritingPipe(address);
//  radio.setPALevel(RF24_PA_HIGH);
//  radio.stopListening();
  Serial.begin(9600);
  inputString.reserve(200);
  Serial.println("Hello from arduino");
  delay(1000);
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString + "\n");
    //Transmit the inputString using the radio
    const char text[8];
    inputString.toCharArray(text, 8);
//    radio.write(&text, sizeof(text));
    delay(500);
    //Clear the string
    inputString = "";
    stringComplete = false;
  }
}

String parseInputString(String str) {
  char buff[50];
  if (str.indexOf("+") == -1) {
    return str;
  }
  char letter = str.charAt(0);
  int startIndex = str.indexOf("+") + 1;
  int endIndex = str.length();
  String s = str.substring(startIndex, endIndex);
  float value = s.toFloat();
  long mapValue = mapf(value, -1.0, 1.0, 0, 255);
  String retValue = ltoa(mapValue, buff, 10);
  return retValue;
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char) Serial.read();
    inputString += inChar;
    // Check if the string is complete
    if (inChar == '\n') {
      inputString = parseInputString(inputString);
      stringComplete = true;
    }
  }
}

long mapf(float x, float in_min, float in_max, long out_min, long out_max) {
  float val = (x - in_min) * (out_max - out_min)/(in_max - in_min) + out_min;
  return (long) val;  
}
