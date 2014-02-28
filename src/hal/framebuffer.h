/*
 * Copyright 2013 Alexander Kühn.
 *
 * framebuffer.h
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
#ifndef FRAMEBUFFER_H_
#define FRAMEBUFFER_H_


#define PWMSUBCYCLES 8
#define PWMROWCYCLES 8

/* function: initialize the physical framebuffer
 *
 */
extern void initPhysFramebuffer( void );

/* function: sync the framebuffer and backbuffer
 * and precalculate the portpin states for PWM cycle
 * withisr: flag, if the sync should be done directly or synched with
 * PWM timer
 *
 */
extern void syncFramebufferInt( uint8_t withisr );

/* function: swap the output and backbuffer
 *
 */
extern void swapBuffer( void );

#endif /* FRAMEBUFFER_H_ */
