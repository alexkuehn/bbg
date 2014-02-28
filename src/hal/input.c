/*
 * Copyright 2013 Alexander Kühn.
 *
 * input.c
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

#include "hal_adc_if.h"
#include "input_if.h"


#include <stdint.h>

#define INPUT_ADC_MEANS 4    /* nr of consecutive measurements */

static uint16_t adbuffer;
static uint8_t meanadval;
static uint8_t meancnt;


void input_process( void )
{
  /* accumulate raw AD values and build mean value */
  adbuffer += getADCValue();
  if( meancnt == (INPUT_ADC_MEANS-1))
    {
      meancnt = 0;
      meanadval = (uint8_t)(adbuffer / INPUT_ADC_MEANS);
      adbuffer = 0;
    }
  else
    {
      meancnt++;
    }
}

uint8_t input_get_adc( void )
{
  return meanadval;
}
