/*
  tachometer.h - tachometer controller
  Part of Marlin

  Copyright (c) 2013 Zach Hoeken

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef tachometer_h
#define tachometer_h 

#include "Marlin.h"

extern volatile unsigned int tachometer_pulse_count;

#define TACH_PULSE_MICROS 60000000

unsigned int get_tachometer_speed();
void setup_spindle();

FORCE_INLINE void tachometer_increment()
{
  tachometer_pulse_count++;
};

#endif //tachometer_h