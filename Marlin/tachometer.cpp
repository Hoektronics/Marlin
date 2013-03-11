/*
  tachometer.cpp - tachometer/spindle control
  Part of Marlin
  
 Copyright (C) 2013 Zach Hoeken
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Marlin.h"
#include "mcp41xxx.h"
#include "tachometer.h"

volatile unsigned int tachometer_pulse_count;
unsigned int spindle_rpm_current = 0;
unsigned long last_tachometer_time;

unsigned int get_tachometer_speed()
{
  unsigned long elapsed = micros() - last_tachometer_time;
  unsigned int pulses = tachometer_pulse_count;

  if (elapsed > 500000)
  {
    if (tachometer_pulse_count == 0)
      spindle_rpm_current = 0;
    else if (tachometer_pulse_count < 5)
      return spindle_rpm_current;

    spindle_rpm_current = TACH_PULSE_MICROS / (elapsed / pulses);

    // MYSERIAL.print(elapsed);
    // MYSERIAL.print(" | ");
    // MYSERIAL.print(tachometer_pulse_count);
    // MYSERIAL.print(" | ");
    // MYSERIAL.println(spindle_rpm_current);

    tachometer_pulse_count = 0;
    last_tachometer_time = micros();
  }

  return spindle_rpm_current;
}

void setup_spindle()
{
  tachometer_pulse_count = 0;
  
  #ifdef SPINDLE_RELAY_PIN
    SET_OUTPUT(SPINDLE_RELAY_PIN);
    WRITE(SPINDLE_RELAY_PIN, INVERT_SPINDLE_ON);
    
    #ifdef MCP41XXX_SELECT_PIN
      mcp41xxx_init(MCP41XXX_SELECT_PIN);
      SET_OUTPUT(MCP41XXX_SELECT_PIN);
      WRITE(MCP41XXX_SELECT_PIN, HIGH);
    #endif
    
    #ifdef TACHOMETER_INTERRUPT
      attachInterrupt(TACHOMETER_INTERRUPT, tachometer_increment, RISING);
    #endif
  #endif
}