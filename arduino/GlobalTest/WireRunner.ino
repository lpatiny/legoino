/*
MCP23008:
 - start address: B00100000 (32)
 - relay box
 - B00100100 - First relay box
 - B00100101 - Second relay box
 - LCD display
 - B00100111 - 2 x 16 LCD display
 - B00100110 - 4 x 20 LCD display
 - 8 OUTPUT EXTENSION
 - B00100010 - EXT_1 (34)
 - B00100011 - EXT_2 (35)
 */

#define WIRE_LCD_16_2 B00100111
#define WIRE_LCD_20_4 B00100110

#define WIRE_EXT_1 B00100010
#define WIRE_EXT_2 B00100011

#define WIRE_RELAY_1 B00100100 // 4-Relay 
#define WIRE_RELAY_2 B00100101 // 4-Relay 

/*
ADS7823
 - start address: B10010000
 - pH meter
 
 PCA9531
 - start address: B01100000 (96)
 Smart led driver
 
 PCF8574
 - start address: B00100000
 Open drain led drive driver
 
 
 */


#define WIRE_PHMETER_ID 0b01001000 // pH-meter v1.3
#define REGISTER_RELAY_COMMAND 0b00010001 // = 17 = R (elay)
#define REGISTER_PH_METER_READOUT 0b00001111 // = 15 = P 



LiquidCrystal lcd(WIRE_LCD_16_2);



byte* wireFlag32=(byte*) malloc(1);



boolean relayInitialized = false;

unsigned int wireEventStatus=0;



void setupWireRunner() {
  *wireFlag32=0;
}

void runWire() {
  wireEventStatus++;

  if (wireDeviceExists(WIRE_EXT_1)) {
    // Serial.println("Device exists");
    if (wireEventStatus%2==1) {
      wireWrite(WIRE_EXT_1,B01010101);
    }
    if (wireEventStatus%2==0) {
      wireWrite(WIRE_EXT_1,B10101010);
    }
  } 
  if (wireDeviceExists(WIRE_EXT_2)) {
    // Serial.println("Device exists");
    if (wireEventStatus%2==1) {
      wireWrite(WIRE_EXT_2,B11110000);
    }
    if (wireEventStatus%2==0) {
      wireWrite(WIRE_EXT_2,B00001111);
    }
  }


  if (wireDeviceExists(WIRE_LCD_16_2)) {
    if (! wireFlagStatus(wireFlag32, WIRE_LCD_16_2)) {
      // we should be able to dynamically change the LCD I2C bus address
      setWireFlag(wireFlag32, WIRE_LCD_16_2);
      lcd.begin(16, 2);
      // Print a message to the LCD.
      lcd.setCursor(0,0);
      lcd.print("Temperature A1!");
    }
    lcd.setCursor(0,1);
    lcd.print(getParameter(20));
  } 
  else {
    clearWireFlag(wireFlag32, WIRE_LCD_16_2); 
  }


  sendRelay(WIRE_RELAY_1, getParameter(PARAM_RELAY_1), wireFlag32);
  sendRelay(WIRE_RELAY_2, getParameter(PARAM_RELAY_2), wireFlag32);

  if (wireDeviceExists(WIRE_PHMETER_ID)) {
    wireWrite(WIRE_PHMETER_ID, 0b00010000); // initialize A/D conversion with 5th bit
    setParameter(REGISTER_PH_METER_READOUT, wireReadTwoBytesToInt(WIRE_PHMETER_ID)); // save pH value into 
  }
  
}





