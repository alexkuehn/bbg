/*
 * Copyright 2013 Alexander Kühn.
 *
 * virtfb_if.h
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
#ifndef VIRTFB_IF_H_
#define VIRTFB_IF_H_

#include "../hal/hal_framebuffer_if.h"


#define FRAMEBUFFER_MAXLUM 31 /* maximum lumiosity range (5bit)*/

/* interface: initialize graphic framebuffer
 */
extern void framebuffer_init( void );

/* interface: update the display with backbuffer content
 */
extern void framebuffer_update( void );

/* interface: copy bitmap from flash memory
 * src: 64byte framebuffer pointer
 */
extern void framebuffer_copyBitmap_mem( const uint8_t* src );

/* interface: copy bitmap from ram memory
 * src: 64byte framebuffer pointer
 */
extern void framebuffer_copyBitmap( const uint8_t* src );

/* interface: add bitmap from ram memory
 * src: 64byte pointer with signed values
 */
extern void framebuffer_add( const int8_t* src );

/* interface: set pixel in framebuffer
 * x,y: coordinate of pixel
 * val: brightness value
 */
extern void framebuffer_setPixel( uint8_t x, uint8_t y, uint8_t val);

/* interface: clear framebuffer
 */
extern void framebuffer_clear( void );

/* interface: draw rectangle
 * xstart, ystart: start coordinate
 * width, height: size of rectangle
 * val: brightness
 */
extern void framebuffer_drawRect( uint8_t xstart, uint8_t ystart, uint8_t width, uint8_t height, uint8_t val);


#endif /* VIRTFB_IF_H_ */
