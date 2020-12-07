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
/*=====[Inclusion of own header]=============================================*/
#include "unity.h"
#include "experiment_parser.h"
#include "string.h"

/*=====[Definition macros of private constants]==============================*/
#define cantidad(variable, tipo) (sizeof(variable) / sizeof(tipo))

/*=====[Definitions of private global variables]=============================*/
experiment_t EXPERIMENTOS[] = {
   {
      .experiment_type = "CV", .current_range = 1,  .hold_time = 1, .hold_voltage = 1500,
      .cv_data.cycles = 2, .cv_data.scan_rate = 10, .cv_data.v_max = 1500, .cv_data.v_min = 500,
   },{
      .experiment_type = "SWV", .current_range = 1, .hold_time = 1, .hold_voltage = 1500,
      .swv_data.cycles = 2, .swv_data.pulse_amplitude = 100, .swv_data.pulse_period = 12, 
      .swv_data.pulse_width = 6, .swv_data.step_pulse = 50, .swv_data.v_max = 1500, .swv_data.v_min = 200,
   }
};

/*=====[Definitions of test functions]=============================*/

void test_experimentSet( void )
{
   char mensaje[32];

   for (int i = 0; i < cantidad(EXPERIMENTOS, experiment_t); i++) 
   {
      experiment_t *experimento = &EXPERIMENTOS[i];
      sprintf(mensaje, "Ejemplo %d", i);
      TEST_ASSERT_EQUAL_MESSAGE(1, experimentSet(experimento),mensaje);
   }
}

void test_experimentSet_NULL( void )
{
   experiment_t test = { .experiment_type = "cv", .current_range = 1,  .hold_time = 1, .hold_voltage = 1500,
                         .cv_data.cycles = 2, .cv_data.scan_rate = 10, .cv_data.v_max = 1500, .cv_data.v_min = 500};

   TEST_ASSERT_EQUAL(0, experimentSet(&test));
}

void test_convertVoltageToCode( void )
{
   experiment_t *experimento = &EXPERIMENTOS[1];

   TEST_ASSERT_EQUAL(65535, convertVoltageToCode(experimento->swv_data.v_max));
}

void test_parseDataCV( void )
{
   cyclicVolt_t *experimento = &EXPERIMENTOS[0].cv_data;

   parseDataCV(experimento);

   TEST_ASSERT_EQUAL(21845, experimento->cant_codes);
   TEST_ASSERT_EQUAL(4, experimento->delay);
}

void test_parseDataSWV( void )
{
   squareWaveVolt_t *experimento = &EXPERIMENTOS[1].swv_data;

   parseDataSWV(experimento);

   TEST_ASSERT_EQUAL(26,experimento->cant_codes);
}

/*=====[Prototypes (declarations) of private functions]====================*/