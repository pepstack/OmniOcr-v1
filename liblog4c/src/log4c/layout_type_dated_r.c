/*
* layout.c
*
* Copyright 2001-2003, Meiosys (www.meiosys.com). All rights reserved.
*
* See the COPYING file for the terms of usage and distribution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <xplatform/xplatform.h>
#include <sd/sprintf.h>
#include <log4c/layout.h>
#include <log4c/priority.h>



/*******************************************************************************/
static const char* dated_r_format(
								  const log4c_layout_t*  	a_layout,
								  const log4c_logging_event_t*a_event)
{
	int n, i;

	const log4c_common_time_t* tm = &a_event->evt_timestamp;

	n = snprintf(a_event->evt_buffer.buf_data, a_event->evt_buffer.buf_size, "%04d%02d%02d %02d:%02d:%02d.%03d %-8s %s- %s\n",
		tm->tm_year , tm->tm_mon + 1, tm->tm_mday,
		tm->tm_hour, tm->tm_min, tm->tm_sec,
		tm->tm_milli,
		log4c_priority_to_string(a_event->evt_priority),
		a_event->evt_category, a_event->evt_msg);

	if (n >= (int)a_event->evt_buffer.buf_size) {
		/*
		* append '...' at the end of the message to show it was
		* trimmed
		*/
		for (i = 0; i < 3; i++)
			a_event->evt_buffer.buf_data[a_event->evt_buffer.buf_size - 4 + i] = '.';
	}

	return a_event->evt_buffer.buf_data;
}

/*******************************************************************************/
const log4c_layout_type_t log4c_layout_type_dated_r = {
	"dated_r",
	dated_r_format,
};

