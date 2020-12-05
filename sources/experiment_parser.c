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

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/


/*=====[Prototypes (declarations) of private functions]====================*/
static void setGainTIA(uint8_t value);

static void setGain(uint8_t resistance);

static void clearGain(uint8_t resistance);

static void setAutoGain();
/*=====[Prototypes (declarations) of public functions]======================*/

_Bool experimentSet(experiment_t *experiment_input)
{
	setGainTIA(experiment_input->current_range);

	convertVoltageToCode(&experiment_input->hold_voltage);

	if( !strcmp(experiment_input->experiment_type, "CV") )
	{
		parseDataCV(&experiment_input->cv_data);
	}
	else if( !strcmp(experiment_input->experiment_type, "SWV") )
	{
		parseDataSWV(&experiment_input->swv_data);
	}
	else
	{
		return 0;
	}
}

void parseDataCV(cyclicVolt_t *cv_data)
{
	convertVoltageToCode(&cv_data->v_max);
	convertVoltageToCode(&cv_data->v_min);
	cv_data->cant_codes = cv_data->v_max - cv_data->v_min;
	cv_data->delay = ceil( ( (cv_data->v_max-cv_data->v_min)/cv_data->scan_rate ) / cv_data->cant_codes);
}

void parseDataSWV(squareWaveVolt_t * swv_data)
{
	convertVoltageToCode(&swv_data->v_max);
	convertVoltageToCode(&swv_data->v_min);
	convertVoltageToCode(&swv_data->pulse_amplitude);
	convertVoltageToCode(&swv_data->step_pulse);

	swv_data->cant_codes = ceil((swv_data->v_max - swv_data->v_min) / swv_data->step_pulse);
}

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

void convertVoltageToCode(uint16_t *voltage)
{
	*voltage = ceil( (*voltage)*(DAC_RESOLUTION / DAC_VCC) ) + VIRTUAL_GND;
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