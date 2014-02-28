/*
 * Copyright 2013 Alexander Kühn.
 *
 * random.c
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
#include "../os/prng_if.h"

void random_process( void )
{
  uint8_t rndval;
  uint8_t i,j;


  framebuffer_clear();

  /* fill framebuffer with PRN between 0-15 */
  for( i = 0; i < FRAMEBUFFER_WIDTH; i++)
    {
      for( j = 0; j < FRAMEBUFFER_HEIGHT; j++)
        {
          rndval = prng_get() >> 3;
          framebuffer_setPixel( i, j, rndval);
        }
    }
  framebuffer_update();
}
