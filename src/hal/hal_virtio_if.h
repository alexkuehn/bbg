/*
 * Copyright 2013 Alexander Kühn.
 *
 * hal_virtio_if.h
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

#ifndef HAL_VIRTIO_IF_H_
#define HAL_VIRTIO_IF_H_

#include <stdint.h>

/* definition of virtual ports */
typedef enum
{
  VPORT0 = 0,
  VPORT1
} virtio_t;

/* definition of real ports */
typedef enum
{
  BUF_PORTB =0,
  BUF_PORTC,
  BUF_PORTD
} portbuffer_t;


/* interface: set value of virtual port
 * port: virtual port ID
 * value: port value
 */
extern void setVirtPort( virtio_t port, uint8_t value);

/* interface: get buffered value for real port
 * portindex: id of real port
 */
extern uint8_t getBufferedPort( portbuffer_t portindex );

#endif /* HAL_VIRTIO_IF_H_ */
