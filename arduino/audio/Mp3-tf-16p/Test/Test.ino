
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
while(Serial1.available()) {
 Serial.write(Serial1.read()); 
}

  delay(1000);        // delay in between reads for stability
}



void sendCommand() {
  Serial1.print(0x7E);
  Serial1.print(0xFF); // version information
  Serial1.print(0x06); // Number of bytes
  Serial1.print(0x03); // Indicate the specific operations, such as play / pause, etc.
  Serial1.print(0x01); // If need for feedback, 1: feedback, 0: no feedback
  Serial1.print(0x00); // Query high data byte
  Serial1.print(0x00); // Accumulation and verification [not include start bit $]
  Serial1.print(0xEF); // Number of bytes
}



