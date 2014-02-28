/*
 * Copyright 2013 Alexander Kühn.
 *
 * ioports.c
 * This file is part of BBG.
 *
 * BBG is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BBG is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BBG.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ioports.h"
#include "hal_virtio_if.h"
#include <avr/io.h>


static uint8_t PORTBUFFER_B;
static uint8_t PORTBUFFER_C;
static uint8_t PORTBUFFER_D;

void initIOPorts( void )
{
  DDRB = IOMASK_PORTB;
  PORTB = INIT_PORTB;
  DDRC = IOMASK_PORTC;
  PORTC = INIT_PORTC;
  DDRD = IOMASK_PORTD;
  PORTD = INIT_PORTD;
}

void inline setVirtPort( virtio_t port, uint8_t value)
{
  static uint8_t portbuf_b = 0;
  static uint8_t portbuf_c = 0;
  static uint8_t portbuf_d = 0;

  switch( port )
  {
  case VPORT0:
    portbuf_b &= (uint8_t)(~MAPMASK_PORTB_VPORT0);
    portbuf_b |= value & 0x81;
    portbuf_b |= (value & 0x40) >> 3;
    portbuf_c &= (uint8_t)(~MAPMASK_PORTC_VPORT0);
    portbuf_c |= (value & 0x3E);
    break;
  case VPORT1:
    portbuf_b &= (uint8_t)(~MAPMASK_PORTB_VPORT1);
    portbuf_b |= (value & 0x03) << 1;
    portbuf_b |= (value & 0x80) >> 2;
    portbuf_d &= (uint8_t)(~MAPMASK_PORTD_VPORT1);
    portbuf_d |= (value & 0x7C) << 1;
    break;
  default:
    break;
  }
  PORTBUFFER_B = portbuf_b & IOMASK_PORTB;
  PORTBUFFER_C = portbuf_c & IOMASK_PORTC;
  PORTBUFFER_D = portbuf_d & IOMASK_PORTD;
}

uint8_t getBufferedPort( portbuffer_t portindex )
{
  uint8_t outbuf;

  switch( portindex )
  {
  case BUF_PORTB:
    outbuf = PORTBUFFER_B;
    break;
  case BUF_PORTC:
    outbuf = PORTBUFFER_C;
    break;
  case BUF_PORTD:
    outbuf = PORTBUFFER_D;
    break;
  default:
    outbuf = 0;
    break;
  }

  return outbuf;
}
