#ifdef THR_ONE_WIRE

/*******************************************
 *  THREAD TEMPERATURE
 *  This module reads the temperature of the different temperature sensors.
 *  The sensor is a dallas 1-wire ds18b20.
 *  
 *  There is only one device per plug. Instead of searching for the 
 *  adresses of the devices, we use the skip rom command which allow 
 *  us to directly ask any device on the line without address.
 *  
 *  The sequence is as follow: 
 *  
 *  We ask the sensor to update its value :
 *  1. Issue a Reset pulse and observe the Presence of the thermometer
 *  2. Issue the Skip Rom command (0xCC)
 *  3. Issue the Convert T command (0×44)
 *  
 *  The conversion in 12 bits take 750ms, so we actually read the previous value :
 *  1. Issue a Reset pulse and observe the Presence of the thermometer
 *  2. Issue the Skip Rom command (0xCC)
 *  3. Issue the Read Scratchpad command (0xBE)
 *  4. Read the next two bytes which represent the temperature
 *********************************************/

#include <OneWire.h>

void getTemperature(OneWire &ow, int parameter);

NIL_WORKING_AREA(waThreadOneWire, 50);  // should be 50 without Serial.println
NIL_THREAD(ThreadOneWire, arg) {
  nilThdSleepMilliseconds(200);
  OneWire oneWire(THR_ONE_WIRE);
  while(true){
    getTemperature(oneWire, PARAM_TEMPERATURE);
    nilThdSleepMilliseconds(5000);
  }
}


void getTemperature(OneWire &ow, int parameter) {
  byte data[2];
  // We ask to calculate the temperature
  byte present=ow.reset();
  ow.write(0xCC);
  ow.write(0x44);   
  // conversion of 12 bits takes 750mS, just wait here to be sure
  nilThdSleepMilliseconds(750);

  if (present != 0) {  //no error
    //We get the new temperature
    present=ow.reset();
    if (present !=0) {
      ow.write(0xCC);
      ow.write(0xBE);
      data[0] = ow.read();
      data[1] = ow.read();
      present=ow.reset();
      if (present !=0) {
        int16_t raw = (data[1] << 8) | data[0];
        //float celsius = (float)raw / 16.0;
        setParameter(parameter, ((long)raw*625)/100);
      }
    }
  }
}  



#endif

