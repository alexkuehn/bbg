/*
 * Copyright 2013 Alexander Kühn.
 *
 * freerun.c
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

#include "../os/types_if.h"

#include "../sys/sysstate_if.h"
#include "../hal/input_if.h"
#include "../engines/random_if.h"
#include "../engines/bitmap_player_if.h"
#include "../engines/rect_if.h"

static uint8_t speedcnt, lastselector;



void freerun_process( void )
{
  uint8_t adcnt, selector, speed, execnow;

  /* select standalone program by potentiometer on AD */
  /* voltage range is divided in coarse for the freerun programs
   * and fine for the execution speed of them
   */
  adcnt = input_get_adc();
  selector = adcnt >> 5;

  execnow = 0;
  if( selector != lastselector)
    {
      lastselector = selector;
      execnow = 1;
    }
  speed = adcnt & 0x1F;


  if( (speedcnt >= speed) || (execnow == 1) )
    {
      speedcnt = 0;

      switch( selector )
      {
      case 0:
        bitmap_player_process();
        break;
      case 1:
        random_process();
        break;
      case 2:
        rect_process();
        break;

      default:
        bitmap_player_process();
        break;

      }
    }
  else
    {
    speedcnt++;
    }
}




