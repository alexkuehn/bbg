/*
 * Copyright 2013 Alexander Kühn.
 *
 * schedule_table.h
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


#ifndef SCHEDULE_TABLE_H_
#define SCHEDULE_TABLE_H_

#include "sys/freerun_if.h"
#include "hal/input_if.h"

/* definition of scheduled tasks */
/* structure is built according to following rule
 * { scheduler_period_ms( <<PERIODIC_TIME>> ), <<PTR TO TASK PROCESS>> }
 */
#define schedule_cb_table                          \
{                                                  \
   { scheduler_period_ms(50),  &freerun_process  },       \
   { scheduler_period_ms(100), &input_process   },      \
}

#define PROCESS_FREERUN 0

#endif /* SCHEDULE_TABLE_H_ */
