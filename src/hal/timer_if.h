/*
 * Copyright 2013 Alexander Kühn.
 *
 * timer_if.h
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
#ifndef TIMER_IF_H_
#define TIMER_IF_H_

#include <stdint.h>

/* interface: get timer value
 * returns: 16bit timer increased every ms
 */
extern uint16_t timer_get( void );

#endif /* TIMER_IF_H_ */
