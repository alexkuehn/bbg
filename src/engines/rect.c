/*
 * Copyright 2013 Alexander Kühn.
 *
 * rect.c
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

static uint8_t cnt,cnt2,cnt3,cnt4, updown;

void rect_process( void )
{
  /* animation of rectangle blending */
  cnt2 = FRAMEBUFFER_MAXLUM-cnt;
  cnt3 = cnt;
  cnt4 = cnt2;
  framebuffer_clear();
  framebuffer_drawRect( 0, 0, FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT, cnt);
  framebuffer_drawRect( 1, 1, 6, 6, cnt2);
  framebuffer_drawRect( 2, 2, 4, 4, cnt3);
  framebuffer_drawRect( 3, 3, 2, 2, cnt4);

  framebuffer_update();
  if( (cnt == FRAMEBUFFER_MAXLUM) && (updown==0) )
  {
      updown = 1;
  }

  if( (cnt == 0) && (updown==1) )
  {
      updown = 0;
  }

  if( updown == 1)
  {
    cnt--;
  }
  else
  {
    cnt++;
  }

}
