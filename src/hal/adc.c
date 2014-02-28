/*
 * Copyright 2013 Alexander Kühn.
 *
 * adc.c
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

#include "adc.h"
#include "hal_adc_if.h"

#include <avr/interrupt.h>
#include <avr/io.h>

static volatile uint8_t advalue;

void initADC( void )
{
  /* initialize the AD converter for continous sampling */
  ADMUX=0;
  ADMUX |= (1<<REFS0);
  ADMUX |= (1<<ADLAR);
  ADCSRA |= (1<<ADPS2) | (1<< ADPS1);
  ADCSRA |= (1<< ADFR);
  ADCSRA |= (1 << ADEN );
  ADCSRA |= (1 << ADIE );
  ADCSRA |= (1 << ADSC );
}

uint8_t getADCValue( void )
{
  uint8_t retval;
  /* dont allow concurrent access by AD converter */
  cli();
  retval = advalue;
  sei();
  return retval;
}

/* ADC ready signal handler */
ISR(ADC_vect)
{
  advalue = ADCH;
}
