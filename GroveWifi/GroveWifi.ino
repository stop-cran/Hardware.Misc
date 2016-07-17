void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  Serial.println("AT+CWLAP");
  delay(5000);
  while(Serial.available())
    Serial.print((char)Serial.read());
  Serial.println("");
}
