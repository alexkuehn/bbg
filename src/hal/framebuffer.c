/*
 * Copyright 2013 Alexander Kühn.
 *
 * framebuffer.c
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

#include "hal_framebuffer_if.h"
#include "hal_virtio_if.h"
#include "framebuffer.h"

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

#define TIMERSCALE 4*2  /* scaling factor of the timer */

/* list of timer signalling points
 * timer is scaled with bitvalue
 */

const PROGMEM uint16_t timerload[] = {
   (TIMERSCALE * 1),
   (TIMERSCALE * 2),
   (TIMERSCALE * 4),
   (TIMERSCALE * 8),
   (TIMERSCALE * 16),
   (TIMERSCALE * 32),
   (TIMERSCALE * 64),
   (TIMERSCALE * 128)
};

static volatile uint8_t* actportbseq;
static volatile uint8_t* bufportbseq;
static volatile uint8_t* actportcseq;
static volatile uint8_t* bufportcseq;
static volatile uint8_t* actportdseq;
static volatile uint8_t* bufportdseq;

static volatile uint8_t buffer_ready;

static uint8_t portbseq[(PWMSUBCYCLES+1)*(PWMROWCYCLES+1)];
static uint8_t portcseq[(PWMSUBCYCLES+1)*(PWMROWCYCLES+1)];
static uint8_t portdseq[(PWMSUBCYCLES+1)*(PWMROWCYCLES+1)];

static uint8_t portbseqb[(PWMSUBCYCLES+1)*(PWMROWCYCLES+1)];
static uint8_t portcseqb[(PWMSUBCYCLES+1)*(PWMROWCYCLES+1)];
static uint8_t portdseqb[(PWMSUBCYCLES+1)*(PWMROWCYCLES+1)];

static uint8_t framebuffer[FRAMEBUFFER_WIDTH][FRAMEBUFFER_HEIGHT];


void initPhysFramebuffer( void )
{
  /* clear the framebuffer */
   uint8_t i,j;
   for( i = 0; i < FRAMEBUFFER_WIDTH; i++ )
     {
       for(j=0; j < FRAMEBUFFER_HEIGHT; j++ )
         {
           framebuffer[i][j] = 0;
         }
     }

   /* output and backbuffer for ports are set */
   actportbseq = &portbseq[0];
   actportcseq = &portcseq[0];
   actportdseq = &portdseq[0];

   bufportbseq = &portbseqb[0];
   bufportcseq = &portcseqb[0];
   bufportdseq = &portdseqb[0];

   syncFramebufferInt(0);

   /* configure the main realtime output timer */
   TCCR1B |= _BV(CS11) | _BV(WGM12);
   OCR1A = pgm_read_word( &timerload[0] );
   TIMSK |= _BV(OCIE1A);
}

void syncFramebuffer( void )
{
  syncFramebufferInt( 1 );
}

void syncFramebufferInt( uint8_t withisr )
{
  uint8_t i,j, k,portoffset;
  uint8_t mask;

  /* decompose the PWM on/off for LED rows
   * and 4bit brightness into portpin on off states
   * first on abstract virtual IO ports and then divided into
   * real distributed pins
   */
  for( i = 0; i < (PWMROWCYCLES); i++ )
    {
      setVirtPort( VPORT1, (1<< i));
      portoffset = ((PWMROWCYCLES)*i);

      for( j = 0; j < (PWMSUBCYCLES); j++)
        {
          mask = 0;
          for( k = 0; k < FRAMEBUFFER_WIDTH; k++)
            {
              if( framebuffer[k][i] & (1 << j) )
                {
                  mask |= (1 << (k));
                }

            }
          setVirtPort( VPORT0, mask);

          bufportbseq[portoffset+j] = getBufferedPort( BUF_PORTB );
          bufportcseq[portoffset+j] = getBufferedPort( BUF_PORTC);
          bufportdseq[portoffset+j] = getBufferedPort( BUF_PORTD );
        }
    }

    if( withisr == 1)
      {
        /* swap the buffer if the display output is running only in phase
         * after complete cycle to prevent tearing
         */
        buffer_ready = 0;
        while( buffer_ready== 0);
        cli();
        swapBuffer();
        sei();
      }
    else
      {
        swapBuffer();
      }
}

extern void swapBuffer( void )
{
  /* swap the output and backbuffers */
  volatile uint8_t * tmpbuffer;

  tmpbuffer = actportbseq;
  actportbseq = bufportbseq;
  bufportbseq = tmpbuffer;

  tmpbuffer = actportcseq;
  actportcseq = bufportcseq;
  bufportcseq = tmpbuffer;

  tmpbuffer = actportdseq;
  actportdseq = bufportdseq;
  bufportdseq = tmpbuffer;
}

uint8_t* getFramebuffer( void )
{
  return &framebuffer[0][0];
}

/* realtime PWM timer signal */
ISR(TIMER1_COMPA_vect)
{

  /* cycle timer through brightness and row phases */
  static uint8_t cnt = 0;
  uint8_t subcnt;

  subcnt = cnt % 8;
  OCR1A= pgm_read_word(&timerload[subcnt]);
  TCNT1 = 0;

  if( subcnt == 0)
  {
      PORTB = 0;
      PORTC = 0;
      PORTD = 0;


  }

  PORTB = actportbseq[cnt];
  PORTC = actportcseq[cnt];
  PORTD = actportdseq[cnt];

  cnt = (cnt + 1) % (PWMSUBCYCLES*PWMROWCYCLES);
  if( cnt== 0)
  {
      /* reset semaphore for syncing */
      buffer_ready = 1;

  }

}
