/*
 * Copyright 2013 Alexander Kühn.
 *
 * bitmap.h
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
#ifndef BITMAP_H_
#define BITMAP_H_

#include "../os/types_if.h"

extern const uint8_t nr_of_bitmaps;
extern const uint8_t nr_of_steps;

extern const uint8_t* const bitmap_table[];

/* function: calc the difference between two bitmaps
 * begin: ptr to start bitmap
 * target: ptr to target bitmap
 */
extern void bitmap_calc_diffmatrix( const uint8_t * begin, const uint8_t *target );

#endif /* BITMAP_H_ */
