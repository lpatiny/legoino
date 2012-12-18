
// we allow an array of devices
// we need to specify 3 arrays
// - the buses
// - the devices
// - the target variable

// If there is more than one device on a bus we need to specify the devices address. Otherwise we may just scan



#define ONE_WIRE_BUS1 ANALOG1

OneWire oneWire1(ONE_WIRE_BUS1);
DallasTemperature sensors1(&oneWire1);
DeviceAddress oneWireAddress;

void setupOneWire() {
  sensors1.begin();
  if (!sensors1.getAddress(oneWireAddress, 0)) debugger(DEBUG_ONEWIRE_NODEVICE, ONE_WIRE_BUS1); 
  sensors1.setWaitForConversion(false); // we don't wait for conversion (otherwise may take 900mS)
  // set the resolution to 12 bit (Each Dallas/Maxim device is capable of several different resolutions)
  sensors1.setResolution(oneWireAddress, 12);

}

void loopOneWire() {
  // following instruction takes 2ms
  sensors1.requestTemperatures(); // Send the command to get temperatures
  // we should not forget that with 12 bits it takes over 600ms to get the result so in fact we
  // will get the result of the previous conversion ...
  // Following instruction takes 14ms
  setParameter(PARAM_TEMP1,(int)(sensors1.getTempC(oneWireAddress)*100));
}


// function to print a device address
void printOneWireAddress(DeviceAddress deviceAddress, Print* output)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) output->print("0");
    output->print(deviceAddress[i], HEX);
  }
}

void oneWireInfo(Print* output) {
  output->println("One wire");
  // Loop through each device, print out address
  for(int i=0;i<sensors1.getDeviceCount(); i++)
  {
    // Search the wire for address
    if (sensors1.getAddress(oneWireAddress, i))
    {
      output->print(i);
      output->print(": ");
      printOneWireAddress(oneWireAddress, output);
      output->println();
    }
  }
}





