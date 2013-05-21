/*
  EXROM_read_unsigned.cpp - Extended EEPROM library
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

//          Read Functions

void EXROMClass::read(int readPointer, unsigned int* readDataStore)                      //read an int from EEPROM
{
  union IntToArray {
    unsigned int i;
    byte b[2];
  } ita;
  read(readPointer, ita.b, 2);
  *readDataStore = ita.i;
}

void EXROMClass::read(int readPointer, unsigned int readDataStore[], int readSize)       //read an int array from EEPROM
{
  for(int i=0; i < readSize/2; i++)
  {
    int j = readPointer + i*2;
    read(j, &readDataStore[i]);
  }
}

void EXROMClass::read(int readPointer, unsigned long* readDataStore)                     //read a long from EEPROM
{
  union ArrayToLong {
    unsigned long l;
    byte b[4];
  } atl;
  read(readPointer, atl.b, 4);
  *readDataStore = atl.l;
}

void EXROMClass::read(int readPointer, unsigned long readDataStore[], int readSize)     //read a long array from EEPROM
{
  for (int i=0; i < readSize/4; i++)
  {
    int j = readPointer + i*4;
    read(j, &readDataStore[i]);
  }
}