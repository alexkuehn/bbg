/*
 * Copyright 2013 Alexander Kühn.
 *
 * prng_if.h
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

#ifndef PRNG_IF_H_
#define PRNG_IF_H_

#include "types_if.h"

/* interface: get a pseudo random number
 * returns: 8bit PRN
 */
extern uint8_t prng_get( void );


#endif /* PRNG_IF_H_ */
