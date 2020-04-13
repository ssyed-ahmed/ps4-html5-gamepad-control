void setup() {
  Serial.begin(9600);
  Serial.println("Testing arduino map function");

//  for(float i = -1.0; i < 1.0; i = i + 0.1) {
//    long mapVal = mapf(i, -1.0, 1.0, 0, 255);
//    Serial.println(i + " = " + mapVal);
//    delay(100);
//  }
//
    float i = -0.55;
    long mapVal = mapf(i, -1.0, 1.0, 0, 255);
    Serial.println(mapVal);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

long mapf(float x, float in_min, float in_max, long out_min, long out_max) {
  float val = (x - in_min) * (out_max - out_min)/(in_max - in_min) + out_min;
  return (long) val;  
}
