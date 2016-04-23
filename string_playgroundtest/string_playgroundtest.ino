      char *value = (char *)"OFF";
      int current = atoi(value);

void setup() {
  // put your setup code here, to run once:

      Serial.begin(115200);


}

void loop() {
  // put your main code here, to run repeatedly:
Serial.println(current);

}
