/*
 * Copyright 2013 Alexander Kühn.
 *
 * commgr.h
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

#ifndef COMMGR_H_
#define COMMGR_H_

#define COM_TIMEOUT  (1000) /* com connection timeout -> ms */

/* protocol symbols */
#define COM_PROTOCOL_START_SLAVE 's'
#define COM_PROTOCOL_LEAVE_SLAVE 'x'
#define COM_PROTOCOL_SLAVE_STARTFRAME 'f'
#define COM_PROTOCOL_HEARTBEAT 'h'

/* communication error type */
typedef enum
{
   DATA_OK = 0,
   DATA_FAIL,
   DATA_TIMEOUT

} com_error_t;

/* communication states */
typedef enum
{
   COMSTATE_NC = 0,
   COMSTATE_DL,
   COMSTATE_SLAVE
} com_state_t;

/* slavemode states */
typedef enum
{
   COMSLAVE_WAIT = 0,
   COMSLAVE_FRAME
} com_slave_state_t;

/* function: protocol processing
 * error: actual error
 * byteval: com received byte
 */
extern void com_protocol_process( com_error_t error, uint8_t byteval );

/* function: protocol mode slave processing
 * byteval: com received byte
 */
extern uint8_t com_protocol_slave_process( uint8_t byteval );

#endif /* COMMGR_H_ */
