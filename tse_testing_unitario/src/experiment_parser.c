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

void setGain();
void setAutoGain();
/*=====[Prototypes (declarations) of public functions]======================*/

_Bool experimentSet(experiment_t *experiment_input)
{
	setGainTIA(experiment_input->current_range);

	convertVoltage(&experiment_input->hold_voltage);

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
	convertVoltage(&cv_data->v_max);
	convertVoltage(&cv_data->v_min);
	
	//Calcular el step segun el scan rate y vmax y vmin
}

void parseDataSWV(squareWaveVolt_t * swv_data)
{
	convertVoltage(&swv_data->v_max);
	convertVoltage(&swv_data->v_min);

	//calcular el valor de cada siguiente pulso
	
}

static void setGainTIA(uint8_t value)
{
	switch(value)
	{
		case 1:
			setGain();
			break;
		case 2:
			setGain();
			break;
		case 3:
			setGain();
			break;
		default:
			setAutoGain();
			break;
	}
}

void convertVoltage(uint16_t *voltage)
{
	*voltage = (*voltage)*(DAC_RESOLUTION / DAC_VCC) + VIRTUAL_GND;
}

/*=====[Implementations of private functions]================================*/
