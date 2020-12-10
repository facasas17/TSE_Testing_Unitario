/*=====[experiment_parser.h]======================================================
 * Copyright 2020 Author:
 * Fabiola de las Casas Escardó <fabioladelascasas@gmail.com>
 *
 * All rights reserved.
 * License: license text or at least name and link
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.1
 * Creation Date: 2020/10/26
 */

/*=====[Inclusion of own header]=============================================*/
#include "experiment_parser.h"

/*=====[Prototypes (declarations) of private functions]====================*/
static void setGainTIA(uint8_t value);

static void setGain(uint8_t resistance);

static void clearGain(uint8_t resistance);

static void setAutoGain();
/*=====[Prototypes (declarations) of public functions]======================*/

_Bool experimentSet(experiment_t *experiment_input)
{
	setGainTIA(experiment_input->current_range);

	experiment_input->hold_voltage = convertVoltageToCode(experiment_input->hold_voltage);

	if( !strcmp(experiment_input->experiment_type, "CV") )
	{
		parseDataCV(&experiment_input->cv_data);
		return 1;
	}
	else if( !strcmp(experiment_input->experiment_type, "SWV") )
	{
		parseDataSWV(&experiment_input->swv_data);
		return 1;
	}
	else
	{
		return 0;
	}
}

void parseDataCV(cyclicVolt_t *cv_data)
{
	cv_data->v_max_code = convertVoltageToCode(cv_data->v_max);
	cv_data->v_min_code = convertVoltageToCode(cv_data->v_min);
	cv_data->cant_codes = cv_data->v_max_code - cv_data->v_min_code;
	cv_data->delay = ( (1000*(cv_data->v_max - cv_data->v_min) / cv_data->scan_rate ) / cv_data->cant_codes);
}

void parseDataSWV(squareWaveVolt_t * swv_data)
{
	swv_data->v_max_code = convertVoltageToCode(swv_data->v_max);
	swv_data->v_min_code = convertVoltageToCode(swv_data->v_min);
	swv_data->pulse_amplitude_code = convertVoltageToCode(swv_data->pulse_amplitude);
	swv_data->step_pulse_code = convertVoltageToCode(swv_data->step_pulse);
	swv_data->cant_codes = (swv_data->v_max - swv_data->v_min)/swv_data->step_pulse;
}

/**
 * @brief Setea la ganancia del TIA 
 * 
 * @param value rango de corriente elegido
 */
static void setGainTIA(uint8_t value)
{
	switch(value)
	{
		case 1:
			setGain(1);
			clearGain(2);
			clearGain(3);
			break;
		case 2:
			setGain(2);
			clearGain(1);
			clearGain(3);
			break;
		case 3:
			setGain(3);
			clearGain(1);
			clearGain(2);
			break;
		default:
			setAutoGain();
			break;
	}
}

uint16_t convertVoltageToCode(int16_t voltage)
{
	voltage = voltage + VIRTUAL_GND;

	return (voltage*DAC_RESOLUTION/DAC_VCC);
}

/*=====[Implementations of private functions]================================*/

static void setGain(uint8_t resistance)
{
	// Ver como mandar msj a switch para setear una salida
}

static void clearGain(uint8_t resistance)
{
	// Ver como mandar msj a switch para setear una salida
}

static void setAutoGain()
{

}