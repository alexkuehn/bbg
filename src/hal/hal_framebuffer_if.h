/*
 * Copyright 2013 Alexander Kühn.
 *
 * hal_framebuffer_if.h
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

#ifndef HAL_FRAMEBUFFER_IF_H_
#define HAL_FRAMEBUFFER_IF_H_

#include <stdint.h>

/* dimensions of the framebuffer */
#define FRAMEBUFFER_WIDTH 8
#define FRAMEBUFFER_HEIGHT 8

/* interface: get framebuffer pointer
 * returns: pointer to framebuffer
 */
extern uint8_t* getFramebuffer( void );

/* interface: synchronizeFramebuffer
 */
extern void syncFramebuffer( void );

#endif /* HAL_FRAMEBUFFER_IF_H_ */
