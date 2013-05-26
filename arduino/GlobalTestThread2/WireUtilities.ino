



void wireWrite(uint8_t address, uint8_t _data ) {
  Wire.beginTransmission(address);
  Wire.write(_data);
  Wire.endTransmission();
}

void wireWrite(uint8_t address, uint8_t reg, uint8_t _data ) // used by 4-relay
{
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(_data);
  Wire.endTransmission();
}

byte wireRead(uint8_t address) {
  byte _data;
  Wire.requestFrom(address, (uint8_t)1);
  if(Wire.available()) {
    _data = Wire.read();
  }
  return _data;
}

int wireReadTwoBytesToInt(uint8_t address) {
  int i = 0;
  int _data;
  int byteWithMSB;
  int byteWithLSB;

  Wire.requestFrom(address, (uint8_t)2);
  while(Wire.available()) {
    if (i > 2) return 0; // security mechanism
    else i++;
    byteWithMSB = Wire.read();
    byteWithLSB = Wire.read();
    _data = (byteWithMSB<<8) | byteWithLSB;
  }
  return _data;
}

void wireInfo(Print* output) {
  // wireUpdateList();
  output->println("I2C");

  for (byte i=0; i<numberI2CDevices; i++) {
    output->print(i);
    output->print(": ");
    output->print(wireDeviceID[i]);
    output->print(" - ");
    output->println(wireDeviceID[i],BIN);
  }
}

void wireUpdateList() {
  // 16ms
  byte _data;
  byte currentPosition=0;
  // I2C Module Scan, from_id ... to_id
  for (byte i=0; i<=127; i++)
  {
    Wire.beginTransmission(i);
    Wire.write(&_data, 0);
    // I2C Module found out!
    if (Wire.endTransmission()==0)
    {
      // there is a device, we need to check if we should add or remove a previous device
      if (currentPosition<numberI2CDevices && wireDeviceID[currentPosition]==i) { // it is still the same device that is at the same position, nothing to do
        currentPosition++;
        //Serial.print("ok: ");
        //Serial.println(i);
      } 
      else if (currentPosition<numberI2CDevices && wireDeviceID[currentPosition]<i) { // some device(s) disappear, we need to delete them
        //Serial.print("delete: ");
        //Serial.println(wireDeviceID[currentPosition]);
        wireRemoveDevice(currentPosition);
        i--;
      } 
      else if (currentPosition>=numberI2CDevices || wireDeviceID[currentPosition]>i) { // we need to add a device
        //Serial.print("add: ");
        //Serial.println(i);
        wireInsertDevice(currentPosition, i);
        currentPosition++;
      }
      nilThdSleepMilliseconds(1);
    }
  }
  while (currentPosition<numberI2CDevices) {
    //Serial.print("delete: ");
    //Serial.println(wireDeviceID[currentPosition]);
    wireRemoveDevice(currentPosition);
  }
}

void wireRemoveDevice(byte id) {
  debugger(DEBUG_WIRE_REMOVED_DEVICE,wireDeviceID[id]);
  for (byte i=id; i<numberI2CDevices-1; i++) {
    wireDeviceID[i]=wireDeviceID[i+1];
  }
  numberI2CDevices--;
}

void wireInsertDevice(byte id, byte newDevice) {
  //Serial.println(id);
  debugger(DEBUG_WIRE_ADDED_DEVICE,newDevice);
  if (numberI2CDevices<WIRE_MAX_DEVICES) {
    for (byte i=id+1; i<numberI2CDevices-1; i++) {
      wireDeviceID[i]=wireDeviceID[i+1];
    }
    wireDeviceID[id]=newDevice;
    numberI2CDevices++;
  } 
  else {
    logger(LOGGER_I2C_CAPACITY_EXCEEDED);
  }
}

boolean wireDeviceExists(byte id) {
  for (byte i=0; i<numberI2CDevices; i++) {
    if (wireDeviceID[i]==id) return true;
  }
  return false; 
}


void sendRelay(byte id, byte value, byte* flag) {
  if (wireDeviceExists(id)) {
    if (!wireFlagStatus(flag, id))
    {
      setWireFlag(flag, id);
      wireWrite(id, 0x05, 0b00000100); // initialize CONFREG (0x05)
      wireWrite(id, 0x00, 0b00000000); // initialize IOREG (0x00)
    }
    wireWrite(id, 0x0A, value); // pin control
  }
  else
  {
    clearWireFlag(flag, id);
  }
}




// We will combine flags in a byte. Using pointer does not seems to improve
// memory size so we don't use pointer
void setWireFlag(byte *aByte, byte address) {
  *aByte |= (1 << (address & 0b00000111));
}

void clearWireFlag(byte *aByte, byte address) {
  *aByte &= ~(1 << (address & 0b00000111));
}

boolean wireFlagStatus(byte *aByte, byte address) {
  return *aByte & (1 << (address & 0b00000111));
}




