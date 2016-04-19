
const int pinPot = A0;
const int pinLed1 = 11;
const int pinLed2 = 10;
const int pinButton = 9;
int state = 0;
int counter = 0;

void setup() {

  Serial.begin(9600);
  pinMode(pinPot, INPUT);
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  pinMode(pinButton, INPUT);

  
}

void loop() {
  int level = analogRead(pinPot);
  if (level < 20) { level = 20; }
  int buttonPressed = digitalRead(pinButton);

  if (buttonPressed == LOW) {

    // if (state == 2) { state = 0; }
    // else { state ++; }
    state ++;

    
  }
  
  digitalWrite(pinLed1, HIGH);
  digitalWrite(pinLed2, LOW);
  delay(level);
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, HIGH);
  delay(level);  

  Serial.println(level);
  //Serial.println(counter);
  //Serial.println(state);
  //counter ++;
  
}


