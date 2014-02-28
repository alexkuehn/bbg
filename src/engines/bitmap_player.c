/*
 * Copyright 2013 Alexander Kühn.
 *
 * bitmap_player.c
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
#include "../virtfb/virtfb_if.h"

#include "bitmap.h"

static uint8_t actbitmap;
static uint8_t actstep;
static int8_t diffmatrix[FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT];

void bitmap_player_process( void )
{
  uint8_t nextbitmap;
  uint8_t bitmapcount = pgm_read_byte(&nr_of_bitmaps);

  /* roll around the bitmaps */
  if( actbitmap >= bitmapcount )
       {
         actbitmap = 0;
       }

  nextbitmap = actbitmap + 1;

  if( nextbitmap >= bitmapcount )
     {
       nextbitmap = 0;
     }

  if( actstep == 0 )
    {
      /* next bitmap started */
      framebuffer_clear();
      /* load new bitmap into framebuffer */
      framebuffer_copyBitmap_mem( (const uint8_t *)pgm_read_word(&bitmap_table[actbitmap]) );
      /* calculate per step delta change to next bitmap */
      bitmap_calc_diffmatrix(  (const uint8_t *)pgm_read_word(&bitmap_table[actbitmap]),
          (const uint8_t *)pgm_read_word(&bitmap_table[nextbitmap]) );
    }
  else
    {
      /* add the stepwise difference to framebuffer */
      framebuffer_add( &diffmatrix[0]);
    }

  if( actstep >= pgm_read_byte(&nr_of_steps) )
    {
      actstep = 0;
      actbitmap++;
    }
  else
    {
      actstep++;
    }

  /* display the framebuffer */
  framebuffer_update();


}

void bitmap_calc_diffmatrix( const uint8_t * begin, const uint8_t *target )
{
  uint8_t i, begin_element, target_element;
  uint8_t stepcount = pgm_read_byte(&nr_of_steps);

  int8_t diff;

  for( i= 0; i < (FRAMEBUFFER_WIDTH*FRAMEBUFFER_HEIGHT); i++ )
    {
      begin_element = pgm_read_byte( &begin[i]);
      target_element = pgm_read_byte( &target[i]);

      diff = target_element - begin_element;

      diffmatrix[i] = (int8_t)(  diff/ stepcount );
    }
}
