const int potPin = A0;
const int buttonPin = 13;

void setup() {
  pinMode(potPin, INPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  int potValue = analogRead(potPin);
  int buttonValue = digitalRead(buttonPin);

  //Write our data to the Serial port. We must write each value
  //with a separate call to Serial.print.
  Serial.print(potValue);
  Serial.print(" ");   //note: must use double quotes, not single quotes
  Serial.print(buttonValue == HIGH ? 0 : 1);
  Serial.println("");

  delay(50);
}

