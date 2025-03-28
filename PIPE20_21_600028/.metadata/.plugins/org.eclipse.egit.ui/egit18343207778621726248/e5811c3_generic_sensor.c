/**
  ******************************************************************************
  * @file           generic_sensor.c
  * @author 		Datakorum Development Team
  * @brief          Low level driver to handle ADC for external analog sensor.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 Datakorum Solutions S.L.
  * All rights reserved.</center></h2>
  *
  *
  ******************************************************************************
  */
/*
 * generic_sensor.c
 *
 *  Created on: 26 oct. 2023
 *      Author: Sergio Millán López
 */
#define _GNU_SOURCE
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "generic_sensor.h"
#include "ventosa.h"
#include "pulses.h"
#include "ad.h"
#include "tick.h"

#define NUM_INPUTS (4U)

enum{OFF = 0, ON = 1};
enum{IDLE = 0, START = 1, END = 1};

typedef struct {
	uint32_t 					on_off;
	uint32_t 					end_conv;
	uint32_t                    burst_reading_by_alarm;
//	uint32_t                    send_by_alarm;
	uint32_t 					write_data;
	uint32_t                    send_data;
	uint32_t                    generic_sensor_data;
	generic_sensor_input_read 	input_read;
	generic_sensor_input_exec   input_exec;
} generic_sensor_t;

generic_sensor_t generic_sensor[4];

void generic_sensor_set_on_off(uint32_t num, uint32_t _on_off)
{
	generic_sensor[num].on_off = _on_off;
}

uint32_t generic_sensor_get_on_off(uint32_t num)
{
	return generic_sensor[num].on_off;
}

void generic_sensor_set_end_conv(uint32_t num, uint32_t _end_conv)
{
	generic_sensor[num].end_conv = _end_conv;
}

uint32_t generic_sensor_get_end_conv(uint32_t num)
{
	return generic_sensor[num].end_conv;
}

void generic_sensor_set_burst_mode(uint32_t num, uint32_t _burst_mode)
{
	generic_sensor[num].burst_reading_by_alarm = _burst_mode;
}

uint32_t generic_sensor_get_burst_mode(uint32_t num)
{
	return generic_sensor[num].burst_reading_by_alarm;
}

uint32_t generic_sensor_get_input_read(uint32_t num)
{
	return generic_sensor[num].input_read();
}

uint32_t generic_sensor_set_sensors_to_send(void)
{
	for (uint32_t i = 0; i < params_input_pulse_as_sensor_get_num(); i++)
	{
		generic_sensor[i].send_data = ON;
	}

	return 0;
}

uint32_t generic_sensor_get_next_sensor_to_send(void)
{
	static uint32_t next_sensor = 1;
	uint32_t ret = 0xFF;

	if (generic_sensor[next_sensor].send_data == ON)
	{
		ret          = next_sensor;
		next_sensor += 1;
		if (next_sensor >= params_input_pulse_as_sensor_get_num())
		{
			next_sensor = 1;
		}
	}
	return ret;
}

void generic_sensor_init(void)
{
	uint32_t i;
	for (i=0; i < NUM_INPUTS; i++)
	{
		generic_sensor[i].on_off   = OFF;
		generic_sensor[i].end_conv = IDLE;
		generic_sensor[i].write_data = OFF;
	}
	generic_sensor[0].input_read = AD_GetAverage_int;
	generic_sensor[1].input_read = ventosa_get_pt5414_data;
	generic_sensor[2].input_read = ventosa_get_pico15_data;
	generic_sensor[3].input_read = ventosa_get_kf5013_data;

	generic_sensor[0].input_exec = AD_read_sensor_pressure_sensor;
	generic_sensor[1].input_exec = ventosa_read_sensor_pt5414;
	generic_sensor[2].input_exec = ventosa_read_sensor_pico15;
	generic_sensor[3].input_exec = ventosa_read_sensor_kf5013;
}

void generic_sensor_task(void)
{
	uint32_t i;

	if ((1 == AD_GetADCData()) && (0 == pulses_get_pulse_rx()))
	{
		battery_voltage_meas(1);
		ventosa_enable_sensors();
		for (i = 0; i < params_input_pulse_as_sensor_get_num(); i++)
		{
			if ((generic_sensor[i].input_exec != NULL) && (generic_sensor[i].on_off == ON))
			{
				generic_sensor[i].end_conv = START;
				generic_sensor[i].input_exec();
				generic_sensor[i].generic_sensor_data = generic_sensor_get_input_read(i);
				generic_sensor[i].end_conv = END;
				generic_sensor[i].on_off   = OFF;
				generic_sensor_log_read_sensor(i);
//				LOGLIVE(LEVEL_2, "\r\nLOGLIVE> %d GENERIC_SENSOR> generic sensor input%d: %d; Vbat_inst: %dmV.\r\n",
//						(int)Tick_Get( SECONDS ),
//						(int)i, (int)generic_sensor[i].generic_sensor_data, (int)battery_get_Vinst());

				/** Writes Time and Date stamp in Sys_time.created_sensor_value_time/date */
				rtc_system_SetCreatedSensorValueTime(Tick_Get(SECONDS));
				rtc_system_SetCreatedSensorValueDate(Tick_Get(SECONDS));
				generic_sensor_log_Log(i);
				generic_sensor_log_pressure_store_telegram_value(i);

				if ((i+1) < params_input_pulse_as_sensor_get_num())
				{
					generic_sensor[i+1].on_off = ON;
				}
			}
		}
		ventosa_disable_sensors();
		AD_setEnd(1);
		AD_SetGetADCData(0);
	}
}
