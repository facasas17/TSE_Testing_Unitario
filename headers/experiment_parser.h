/*=====[experiment_parser.h]======================================================
 * Copyright 2020 Author:
 * Fabiola de las Casas Escardó <fabioladelascasas@gmail.com>
 *
 * All rights reserved.
 * License: license text or at least name and link
         (example: BSD-3-Clause <https://opensource.org/licenses/BSD-3-Clause>)
 *
 * Version: 0.0.1
 * Creation Date: 2020/12/2
 */

/*=====[Avoid multiple inclusion - begin]====================================*/

#ifndef EXPERIMENT_PARSER_H
#define EXPERIMENT_PARSER_H

/*=====[Inclusions of public function dependencies]==========================*/
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "math.h"

/*=====[C++ - begin]=========================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/*=====[Definition macros of public constants]===============================*/
#define DAC_RESOLUTION			65535
#define DAC_VCC					3000	//Expresado en mV
#define VIRTUAL_GND				1500	// Tierra virtual aplicada a los electrodos
#define VIRTUAL_GND_CODE		(DAC_RESOLUTION / 2)

/*=====[Definitions of public data types]====================================*/

typedef struct{
	int16_t v_max;
	int16_t v_min;
	uint16_t v_max_code;
	uint16_t v_min_code;
	uint8_t scan_rate;
	uint8_t cycles;
	uint16_t cant_codes;
	uint32_t delay;	//en ms
}cyclicVolt_t;

typedef struct{
	int16_t v_max;
	int16_t v_min;
	uint16_t v_max_code;
	uint16_t v_min_code;
	uint16_t pulse_amplitude;
	uint16_t pulse_amplitude_code;
	uint8_t pulse_width;
	uint8_t pulse_period;
	uint16_t step_pulse;
	uint16_t step_pulse_code;
	uint8_t cycles;
	uint16_t cant_codes;
}squareWaveVolt_t;

typedef struct{
	char *experiment_type;
	uint8_t hold_time;
	uint16_t hold_voltage;
	uint8_t current_range;
	cyclicVolt_t cv_data;
	squareWaveVolt_t swv_data;
}experiment_t;

/*=====[Prototypes (declarations) of public functions]=======================*/
_Bool experimentSet(experiment_t *experiment_input);

uint16_t convertVoltageToCode(int16_t voltage);

void parseDataSWV(squareWaveVolt_t *swv_data);

void parseDataCV(cyclicVolt_t *cv_data);

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* EXPERIMENT_PARSER_H */

