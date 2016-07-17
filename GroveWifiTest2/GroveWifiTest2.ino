#include <SoftwareSerial.h>

SoftwareSerial mySerial(3, 4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);
  // wait for serial port to connect. Needed for native USB port only

  mySerial.begin(115200);
  while (!mySerial);
  Serial.println("Goodnight moon!");
}

void loop() {
  bool available;
  mySerial.println("AT+CWLAP");
  while(!mySerial.available());
  while(mySerial.available())
     Serial.print((char)mySerial.read());
  Serial.println();

  do
  {
    available = false;
    delay(1000);
    while(mySerial.available())
    {
      Serial.print((char)mySerial.read());
      available = true;
    }
    if(available)
      Serial.println();
  }  
  while(available);
  
  delay(10000);
}
