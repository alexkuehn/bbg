/*
 * Copyright 2013 Alexander Kühn.
 *
 * hal_init_if.h
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

#ifndef HAL_INIT_IF_H_
#define HAL_INIT_IF_H_

#define UART_BAUD_RATE 9600

/* interface: initialize hardware components
 */
extern void initHardware( void );

#endif /* HAL_INIT_IF_H_ */
