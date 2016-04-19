// using my own code

const int buttonPin = 2;
const int ledPin = 13;

void setup() {

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
}

void loop() {

 int buttonState = digitalRead(buttonPin);
 int ledState = digitalRead(ledPin);
 
if (ledState == LOW && buttonState == LOW) {
 digitalWrite(ledPin, HIGH);
 delay(1000);
}

else if (ledState == HIGH && buttonState == LOW) {
 digitalWrite(ledPin, LOW);
delay(1000);
}


}
