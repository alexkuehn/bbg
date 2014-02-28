/*
 * Copyright 2013 Alexander Kühn.
 *
 * ioports.h
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

#ifndef IOPORTS_H_
#define IOPORTS_H_

/* mapping of physical IOports to virtual ports */
#define IOMASK_PORTB (_BV(PB0) | _BV(PB1) | _BV(PB2) | _BV(PB3) | _BV(PB5) | _BV(PB7) )
#define IOMASK_PORTC ( _BV(PC1)| _BV(PC2) | _BV(PC3) | _BV(PC4) | _BV(PC5) )
#define IOMASK_PORTD ( _BV(PD3) | _BV(PD4) | _BV(PD5) | _BV(PD6) | _BV(PD7) )

#define INIT_PORTB 0
#define INIT_PORTC 0
#define INIT_PORTD 0

#define MAPMASK_PORTB_VPORT0 (_BV(PB0) | _BV(PB3) | _BV(PB7) )
#define MAPMASK_PORTC_VPORT0 (_BV(PC1) | _BV(PC2) | _BV(PC3) | _BV(PC4) | _BV(PC5)  )
#define MAPMASK_PORTB_VPORT1 (_BV(PB1) | _BV(PB2) | _BV(PB5) )
#define MAPMASK_PORTD_VPORT1 (_BV(PD3) | _BV(PD4) | _BV(PD5) | _BV(PD6) | _BV(PD7)  )


/* function: initialize ioports
 */
void initIOPorts( void );

#endif /* IOPORTS_H_ */
