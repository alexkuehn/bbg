/*
 * Copyright 2013 Alexander Kühn.
 *
 * prng.c
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
#include "types_if.h"

uint8_t prng_get( void )
{
  static uint8_t seed = 0xAA;
  static uint8_t a=0;

  seed ^=seed << 3;
  seed ^=seed >> 5;
  seed ^= a++ >> 2;
  return seed;
}
