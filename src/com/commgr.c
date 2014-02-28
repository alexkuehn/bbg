/*
 * Copyright 2013 Alexander Kühn.
 *
 * commgr.c
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

#include "../sys/sysstate_if.h"
#include "../hal/timer_if.h"
#include "../os/types_if.h"
#include "../lib/uart/uart.h"
#include "commgr.h"


static uint16_t time_lastdata;
static uint8_t arm_timeout;
static com_state_t comstate;
static com_slave_state_t comslavestate;
static uint8_t blockbuffer[64];

void com_init( void )
{
   /* initial state of COM stack: not connected */
   comstate = COMSTATE_NC;
}

void com_process( void )
{
   uint16_t recvword;
   uint16_t time_act;
   uint8_t hrecv, lrecv;

   /* fetch received uart word */
   recvword = uart_getc();
   hrecv = (uint8_t)((recvword & 0xFF00) >> 8);
   lrecv = (uint8_t)(recvword & 0x00FF);

   if( hrecv == 0 )
   {
      /* valid data available */
      time_lastdata = timer_get();
      /* start com timeout countdown */
      arm_timeout = 1;
      com_protocol_process( DATA_OK, lrecv );
   }
   else
   {
      /* no valid data */
      if( hrecv & (uint8_t)(UART_NO_DATA >> 8) )
      {
         /* no new data arrived */

         /* measure com timeout countdown */
         time_act = timer_get();
         if(
             ((time_act - time_lastdata) > COM_TIMEOUT) &&
             (arm_timeout == 1)
           )
         {
            com_protocol_process(DATA_TIMEOUT, 0x00 );
            arm_timeout = 0;
         }
      }
      else
      {
         /* data transfer fail */
         com_protocol_process(DATA_FAIL, 0x00 );

      }

   }


}

void com_protocol_process( com_error_t error, uint8_t byteval )
{
   uint8_t substate;

   /* main protocol state machine */
   switch( comstate )
   {
   case COMSTATE_NC:
     /* not connected */
      if( error == DATA_OK )
      {
         if( byteval == COM_PROTOCOL_START_SLAVE)
         {
            comstate = COMSTATE_SLAVE;
            comslavestate = COMSLAVE_WAIT;
            sysstate_request(STATE_SLAVE);

         }
      }
      break;
   case COMSTATE_SLAVE:
      /* slave mode */
      if( error == DATA_OK )
      {
         substate = com_protocol_slave_process( byteval );
      }

      if( (error != DATA_OK) ||
          (substate != 0)
        )
      {
         comstate = COMSTATE_NC;
         sysstate_request(STATE_FREE);
      }
      break;
   default:
      break;
   }
}

uint8_t com_protocol_slave_process( uint8_t byteval )
{
   static uint8_t blockcount;
   uint8_t retstate;
   retstate = 0;

   /* slave mode sub statemachine */
   switch( comslavestate )
   {
   case COMSLAVE_WAIT:
      if( byteval == COM_PROTOCOL_LEAVE_SLAVE )
      {
         retstate = 1;
      }

      if( byteval == COM_PROTOCOL_SLAVE_STARTFRAME )
      {
         /* start of new bitmap frame */
         blockcount = 0;
         comslavestate = COMSLAVE_FRAME;
      }
      break;
   case COMSLAVE_FRAME:
      /* receiving frame */
      blockbuffer[blockcount] = byteval;
      blockcount++;
      if( blockcount > 63 )
      {
         comslavestate = COMSLAVE_WAIT;
         // slavemode_newframe( blockbuffer );
      }
      break;
   default:
      break;

   }

   return retstate;
}
