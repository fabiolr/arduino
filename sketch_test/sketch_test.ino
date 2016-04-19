
const int pinLed = 11;

void setup() {
  
  pinMode(pinLed, OUTPUT);
  //pinMode(pinLed, INPUT_PULLUP);

  
}

void loop() {
  
  digitalWrite(pinLed, HIGH);
  delay(500);
  digitalWrite(pinLed, LOW);

}


