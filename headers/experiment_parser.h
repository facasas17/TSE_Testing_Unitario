/*=====[experiment_parser.h]======================================================
 * Copyright 2020 
 * Author: Fabiola de las Casas Escardó <fabioladelascasas@gmail.com>
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

/**
 * @file experiment_parser.h
 * @brief Libreria para convertir la configuracion ingresada por el usuario a la necesario para el conversor digital analogico utilizado
 * 
 * El usuario ingresa los datos del experimento en mV y ms. Segun la resolucion del DAC utilizado y la configuracion del hardware,
 * se convierten estos valores al codigo correspondiente a enviar al DAC para generar la señal deseada.
 * 
 */
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

/**
 * @brief Estructura con los parametros de Voltametria Ciclica (CV)
 * 
 */
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

/**
 * @brief Estructura con los parametros de Voltametria Cuadrada (SWV)
 * 
 */
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

/**
 * @brief Estructura con los parametros generales de un experimento
 * 
 */
typedef struct{
	char *experiment_type;
	uint8_t hold_time;
	uint16_t hold_voltage;
	uint8_t current_range;
	cyclicVolt_t cv_data;
	squareWaveVolt_t swv_data;
}experiment_t;

/*=====[Prototypes (declarations) of public functions]=======================*/
/**
 * @brief Funcion para parsear los datos del experimentos seleccionados, segun el DAC utilizado
 * 
 * @param experiment_input estructura con los datos ingresados por el usuario
 * @return _Bool 1 si el experimento elegido es correcto, 0 si es incorrecto
 */
_Bool experimentSet(experiment_t *experiment_input);

/**
 * @brief Convierte el codigo en mV al codigo correspondiente para el DAC
 * 
 * @param voltage valor a transformar
 * @return uint16_t valor transformado
 */
uint16_t convertVoltageToCode(int16_t voltage);

/**
 * @brief Parsea los datos de una voltametrica cuadrada (SWV) al codigo correspondiente del DAC.
 * 
 * @param swv_data estructura con todos los parametros de una SWV
 */
void parseDataSWV(squareWaveVolt_t *swv_data);

/**
 * @brief Parsea los datos de una voltametrica ciclica (CV) al codigo correspondiente del DAC.
 * 
 * @param cv_data estructura con todos los parametros de una CV
 */
void parseDataCV(cyclicVolt_t *cv_data);

/*=====[C++ - end]===========================================================*/

#ifdef __cplusplus
}
#endif

/*=====[Avoid multiple inclusion - end]======================================*/

#endif /* EXPERIMENT_PARSER_H */

