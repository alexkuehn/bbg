/*
 * Copyright 2013 Alexander Kühn.
 *
 * sysstate_if.h
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
#ifndef SYSSTATE_IF_H_
#define SYSSTATE_IF_H_

/* definition of system states */
typedef enum {
   STATE_FREE,
   STATE_SLAVE,
   STATE_DOWNLOAD
} sysstate_t;

/* function: initialize system state handler
 */
extern void sysstate_init( void );

/* function: system state processing
 */
extern void sysstate_process( void );

/* function: request new system state
 * new_state: new system state
 */
extern void sysstate_request( sysstate_t new_state );

/* function: gets the current system state
 * returns: actual system state
 */
extern sysstate_t sysstate_get( void );

#endif /* SYSSTATE_IF_H_ */
