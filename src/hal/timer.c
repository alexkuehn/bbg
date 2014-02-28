/*
 * Copyright 2013 Alexander Kühn.
 *
 * timer.c
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

#include "timer.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

static volatile uint16_t timer_tick;

void timer_init( void )
{
  /* init system timer to 1ms tick */
  TIMSK |= (1 << TOIE0);
  TCCR0 |= (1 << CS01) | (1 << CS00);

}

uint16_t timer_get( void )
{
  uint16_t tickbuffer;

  cli();
  tickbuffer = timer_tick;
  sei();

  return tickbuffer;
}

/* system timer signal */
ISR (TIMER0_OVF_vect)
{
    timer_tick++;
}
