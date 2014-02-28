/*
 * Copyright 2013 Alexander Kühn.
 *
 * hal_init.c
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

#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#include "hal_init_if.h"
#include "ioports.h"
#include "../lib/uart/uart.h"
#include "adc.h"
#include "framebuffer.h"
#include "timer.h"

void initHardware( void )
{
  initIOPorts();
  uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
  initADC();
  initPhysFramebuffer();
  timer_init();

  /* start the interrupt system */
  sei();
}

