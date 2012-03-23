/*
  EXROM_write_unsigned.cpp - Extended EEPROM library
  Written/extended by Tom Bloor aka. TBSliver.
  
  Based on:
  
  EEPROM library
  Copyright (c) 2006 David A. Mellis.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <avr/eeprom.h>
#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif
#include "EXROM.h"

//          Write Functions

void EXROMClass::write(int writePointer, unsigned int writeDataStore)                    //write an int to EEPROM
{
  union IntToArray {
    unsigned int i;
    byte b[2];
  } ita;
  ita.i = writeDataStore;
  write(writePointer, ita.b, 2);
}

void EXROMClass::write(int writePointer, unsigned int writeDataStore[], int writeSize)   //write an int array to EEPROM
{
  for(int i=0; i < writeSize/2; i++)
  {
    int j = writePointer + i*2;
    write(j, writeDataStore[i]);
  }
}

void EXROMClass::write(int writePointer, unsigned long writeDataStore)                  //write a long to EEPROM
{
  union LongToArray {
    unsigned long l;
    byte b[4];
  } lta;
  lta.l=writeDataStore;
  write(writePointer, lta.b, 4);
}

void EXROMClass::write(int writePointer, unsigned long writeDataStore[], int writeSize) //write a long array to EEPROM
{
  for(int i=0; i < writeSize/4; i++)
  {
    int j = writePointer + i*4;
    write(j, writeDataStore[i]);
  }
}