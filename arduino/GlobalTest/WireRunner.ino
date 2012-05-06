
#define wire_extension1 B00100001
#define wire_extension2 B00100111

#define WIRE_RELAY_ID 0b00100101 // 4-Relay 
#define WIRE_PHMETER_ID 0b01001000 // pH-meter v1.3
#define REGISTER_RELAY_COMMAND 0b00010001 // = 17 = R (elay)
#define REGISTER_PH_METER_READOUT 0b00001111 // = 15 = P 

#define wire_lcd B00100000
LiquidCrystal lcd(wire_lcd);
boolean lcdInitialized=false;
boolean relayInitialized = false;

unsigned int wireEventStatus=0;



void setupWireRunner() {
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

  if (wireDeviceExists(wire_lcd)) {
    if (! lcdInitialized) {
      lcdInitialized=true;
      lcd.begin(16, 2);
      // Print a message to the LCD.
      lcd.setCursor(0,0);
      lcd.print("Hello, world!");
    }

    lcd.setCursor(0,1);
    lcd.print(getParameter(20));
  } 
  else {
    lcdInitialized=false; 
  }

  if (wireDeviceExists(WIRE_RELAY_ID)) {
    if (!relayInitialized)
    {
      relayInitialized = true;
      wireWrite(WIRE_RELAY_ID, 0x05, 0b00000100); // initialize CONFREG (0x05)
      wireWrite(WIRE_RELAY_ID, 0x00, 0b00000000); // initialize IOREG (0x00)
      wireWrite(WIRE_RELAY_ID, 0x0A, getParameter(REGISTER_RELAY_COMMAND)); // pin control
    }
    else
    {
      wireWrite(WIRE_RELAY_ID, 0x0A, getParameter(REGISTER_RELAY_COMMAND)); // pin control
    }
  }
  else
  {
    relayInitialized = false;
  }

  if (wireDeviceExists(WIRE_PHMETER_ID)) {
    wireWrite(WIRE_PHMETER_ID, 0b00010000); // initialize A/D conversion with 5th bit
    setParameter(REGISTER_PH_METER_READOUT, wireReadTwoBytesToInt(WIRE_PHMETER_ID)); // save pH value into 
  }

}






