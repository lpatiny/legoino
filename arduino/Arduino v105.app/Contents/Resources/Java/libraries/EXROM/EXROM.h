/*
  EXROM.h - Extended EEPROM library
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

#ifndef EXROM_h
#define EXROM_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif


class EXROMClass
{
public:
//          write functions
void write(int, byte);
void write(int, byte*, int);
void write(int, char);
void write(int, char*, int);
void write(int, int);
void write(int, int*, int);
void write(int, float);
void write(int, float*, int);
void write(int, long);
void write(int, long*, int);
void write(int, unsigned int);
void write(int, unsigned int*, int);
void write(int, unsigned long);
void write(int, unsigned long*, int);
//          read functions
void read(int, byte*);
void read(int, byte*, int);
void read(int, char*);
void read(int, char*, int);
void read(int, int*);
void read(int, int*, int);
void read(int, float*);
void read(int, float*, int);
void read(int, long*);
void read(int, long*, int);
void read(int, unsigned int*);
void read(int, unsigned int*, int);
void read(int, unsigned long*);
void read(int, unsigned long*, int);
private:
byte read(int);
};

extern EXROMClass EXROM;

#endif

