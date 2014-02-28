/*
 * Copyright 2013 Alexander Kühn.
 *
 * virtfb.c
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
#include "../hal/hal_framebuffer_if.h"
#include "virtfb_if.h"
#include "virtfb.h"

#include <avr/pgmspace.h>

/* logarithmic adaption of brightness to 8bit PWM values */
static const uint16_t FRAMEBUFFER_EYELOG_TABLE[32] PROGMEM =
{
    0, 1, 2, 2, 2, 3, 3, 4, 5, 6, 7, 8, 10, 11, 13, 16, 19, 23,
    27, 32, 38, 45, 54, 64, 76, 91, 108, 128, 152, 181, 215, 255
};

static uint8_t* framebuffer;

void framebuffer_init( void )
{
  framebuffer = getFramebuffer();
}

void framebuffer_update( void )
{
  framebuffer_eyelog();
  syncFramebuffer();
}

void framebuffer_eyelog( void )
{
  uint8_t i;
   for( i= 0; i < (FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT); i++)
     {
       if( framebuffer[i] <= FRAMEBUFFER_MAXLUM)
         {
           framebuffer[i] = pgm_read_byte( &FRAMEBUFFER_EYELOG_TABLE[framebuffer[i]] );
         }
     }
}

void framebuffer_copyBitmap_mem( const uint8_t* src )
{
  uint8_t i;
  for( i= 0; i < (FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT); i++)
    {
          framebuffer[i] = pgm_read_byte( &src[i] );
    }
}

void framebuffer_copyBitmap( const uint8_t* src )
{
  uint8_t i;
  for( i= 0; i < (FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT); i++)
    {
          framebuffer[i] = src[i];
    }
}

void framebuffer_add( const int8_t* src )
{
  uint8_t i;
  for( i= 0; i < (FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT); i++)
    {

          framebuffer[i] += src[i];

          if( framebuffer[i] > FRAMEBUFFER_MAXLUM)
            {
              framebuffer[i] = FRAMEBUFFER_MAXLUM;
            }
    }
}

void framebuffer_setPixel( uint8_t x, uint8_t y, uint8_t val)
{
  if( (x < FRAMEBUFFER_WIDTH) && (y < FRAMEBUFFER_HEIGHT) )
    {
      framebuffer[y+(x*FRAMEBUFFER_HEIGHT)] = val;
    }

}

void framebuffer_clear( void )
{
  uint8_t i;
   for( i= 0; i < (FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT); i++)
     {
           framebuffer[i] = 0;
     }
}

void framebuffer_drawRect( uint8_t xstart, uint8_t ystart, uint8_t width, uint8_t height, uint8_t val)
{
  uint8_t i;
  for( i = 0; i < width; i++)
     {
        framebuffer_setPixel(i+xstart, ystart, val);
        framebuffer_setPixel(i+xstart, ystart+height-1, val);
     }
   for( i = 0; i < height; i++)
     {
       framebuffer_setPixel(xstart, i+ystart, val);
       framebuffer_setPixel(xstart+width-1, i+ystart, val);
     }
}
