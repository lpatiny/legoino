/* Arduino NilRTOS Library
 * Copyright (C) 2013 by William Greiman
 *
 * This file is part of the Arduino NilRTOS Library
 *
 * This Library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Arduino NilRTOS Library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
/**
 * @file    NilAnalog.h
 * @brief   Nil RTOS ADC read source
 *
 * @defgroup Analog NilAnalog
 * @details Nil RTOS ADC functions.
 * @{
 */
#ifndef NilAnalog_h
#define NilAnalog_h
//------------------------------------------------------------------------------
/** NilAnalog version YYYYMMDD */
#define NIL_ANALOG_VERSION 20130214
#ifdef __cplusplus
extern "C" {
#endif
  int nilAnalogRead(uint8_t pin);
  void nilAnalogReference(uint8_t mode);
#ifdef __cplusplus
}
#endif
#endif  // NilAnalog_h
/** @} */