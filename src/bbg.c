/*
 * Copyright 2013 Alexander Kühn.
 *
 * bbg.c
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

#include "hal/hal_init_if.h"

#include "com/com_if.h"
#include "os/scheduler_if.h"
#include "virtfb/virtfb_if.h"
#include "sys/sysstate_if.h"
#include <util/delay.h>

#include <avr/pgmspace.h>

#include "hal/timer_if.h"

#include "sys/freerun_if.h"


/* the main entry point */

int main( void )
{
  /* initialize subsystems */

  initHardware();
  framebuffer_init();
  com_init();
  sysstate_init();
  scheduler_init();

  /* loop forever */
  for(;;)
  {
      /* execute processes */

      com_process();            // communication stack
      sysstate_process();       // system state calculation
      scheduler_process();      // scheduler
  }
  return 0;
}






