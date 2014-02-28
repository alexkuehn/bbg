/*
 * Copyright 2013 Alexander Kühn.
 *
 * sysstate.c
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

#include "sysstate_if.h"
#include "../os/scheduler_if.h"
#include "../schedule_table.h"

static sysstate_t requested_sysstate;
static sysstate_t actual_sysstate;

void sysstate_init( void )
{
   requested_sysstate = STATE_FREE;
   actual_sysstate = STATE_FREE;
}

void sysstate_request( sysstate_t new_state )
{
   requested_sysstate = new_state;
}

void sysstate_process( void )
{
   if( actual_sysstate != requested_sysstate )
   {
      switch( requested_sysstate )
      {
      case STATE_FREE:
        scheduler_control( PROCESS_FREERUN, SCHED_RUN);
        break;
      default:
        scheduler_control( PROCESS_FREERUN, SCHED_STOP);
        break;
      }
      actual_sysstate = requested_sysstate;

   }
}

sysstate_t sysstate_get( void )
{
   return actual_sysstate;
}
