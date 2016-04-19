const int buttonPin = 2;
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:


  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);


}

void loop() {
  // put your main code here, to run repeatedly:

  int pinState = digitalRead(buttonPin);

    digitalWrite(ledPin, HIGH);
 delay(50);
    digitalWrite(ledPin, LOW);
delay(100);


}

