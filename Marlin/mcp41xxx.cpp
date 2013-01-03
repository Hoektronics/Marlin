/*
  mcp41xxx.c - interface for controlling a MCP41XXX digital potentiometer
  Part of Grbl

  Copyright (c) 2013 Zach Hoeken <zach@hoektronics.com>
  
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

#include "Marlin.h"
#include "SPI.h"

void mcp41xxx_init(uint8_t cs_pin)
{
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  SPI.setClockDivider(SPI_CLOCK_DIV4);
  
  pinMode(cs_pin, OUTPUT);
  digitalWrite(cs_pin, HIGH);
}

uint8_t mcp41xxx_write(uint8_t cs_pin, uint8_t data, bool pot0, bool pot1)
{
  uint8_t command = (0x01 << 5) | (pot1 << 1) | pot0;
  
  digitalWrite(cs_pin, LOW);
  SPI.transfer(command);
  uint8_t result = SPI.transfer(data);
  digitalWrite(cs_pin, HIGH);
  
  return result;
}

uint8_t mcp41xxx_shutdown(uint8_t cs_pin, bool pot0, bool pot1)
{
  uint8_t command = (0x02 << 5) | (pot1 << 1) | pot0;
  
  digitalWrite(cs_pin, LOW);
  SPI.transfer(command);
  uint8_t result = SPI.transfer(0);
  digitalWrite(cs_pin, HIGH);
  
  return result;
}

uint8_t mcp41xxx_get_wiper_position(int total_resistance, int resistance_aw)
{
  //from the datasheet:
  //resistance_aw = (total_resistance * (256-position)) / 256
  //resistance_aw * 256 = total_resistance * (256-position)
  //((resistance_aw * 256) / total_resistance) = 256-position
  //((resistance_aw * 256) / total_resistance) = 256-position
  
  return 256 - ((resistance_aw * 256) / total_resistance);
}
