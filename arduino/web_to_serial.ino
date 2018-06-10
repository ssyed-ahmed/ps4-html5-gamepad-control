
String inputString = "";
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  inputString.reserve(200);
  Serial.println("Hello from arduino");
}

void loop() {
  if (stringComplete) {
    Serial.println(inputString + "\r\n");
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

