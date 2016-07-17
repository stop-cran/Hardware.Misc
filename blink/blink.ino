void setup() {
  pinMode(5, OUTPUT);
}

bool ledOn = false, buttonPressed = false;

void loop() {
  bool justPressed = digitalRead(2);

  if(!justPressed && buttonPressed)
    digitalWrite(5, ledOn = !ledOn);
  buttonPressed = justPressed;
  delay(100);
}
