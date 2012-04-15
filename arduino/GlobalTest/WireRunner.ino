
#define wire_extension1 B0100000
#define wire_extension2 B0100111

#define wire_lcd B00100000
LiquidCrystal lcd(wire_lcd);

unsigned int wireEventStatus=0;

void setupWireRunner() {
  if (wireDeviceExists(wire_extension1)) {
    lcd.begin(16, 2);
    // Print a message to the LCD.
    lcd.print("Hello, world!");
  }
}

void runWire() {
  wireEventStatus++;

  if (wireDeviceExists(wire_extension1)) {
    // Serial.println("Device exists");
    if (wireEventStatus%2==1) {
      wireWrite(wire_extension1,B01010101);
    }
    if (wireEventStatus%2==0) {
      wireWrite(wire_extension1,B10101010);
    }
  } 
  if (wireDeviceExists(wire_extension2)) {
    // Serial.println("Device exists");
    if (wireEventStatus%2==1) {
      wireWrite(wire_extension2,B11110000);
    }
    if (wireEventStatus%2==0) {
      wireWrite(wire_extension2,B00001111);
    }
  } 


}


