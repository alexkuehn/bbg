/*
 * Copyright 2013 Alexander Kühn.
 *
 * datautil_if.h
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
#ifndef DATAUTIL_IF_H_
#define DATAUTIL_IF_H_

/* interface: compress 64 byte 5bit values to 40 byte
 * source: pointer to 64 byte source elements
 * dest: pointer to 40byte target buffer
 */
extern void dataset_compress_resolution( uint8_t *source, uint8_t *dest  );

/* interface: uncompress 40byte 4bit values to 64byte
 * source: pointer to 40 byte source elements
 * dest: pointer to 64byte target buffer
 */
extern void dataset_uncompress_resolution( uint8_t *source, uint8_t *dest );


#endif /* DATAUTIL_IF_H_ */
