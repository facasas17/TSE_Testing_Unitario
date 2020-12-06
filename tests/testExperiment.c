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
#include "unity.h"
#include "experiment_parser.h"

/*=====[Definition macros of private constants]==============================*/

/*=====[Private function-like macros]========================================*/

/*=====[Definitions of private data types]===================================*/

/*=====[Definitions of external public global variables]=====================*/

/*=====[Definitions of public global variables]==============================*/

/*=====[Definitions of private global variables]=============================*/

void test_experimentSet_CV( void ) 
{
   experiment_t experiment_input = {.experiment_type = "CV", .current_range = 1,
                                    .hold_time = 1, .hold_voltage = 1500,
                                    .cv_data.cycles = 2, .cv_data.scan_rate = 10,
                                    .cv_data.v_max = 1500, .cv_data.v_min = 500};

   TEST_ASSERT_EQUAL(1, experimentSet(&experiment_input));
}

void test_experimentSet_SWV( void ) 
{
   experiment_t experiment_input = {.experiment_type = "SWV", .current_range = 1,
                                    .hold_time = 1, .hold_voltage = 1500,
                                    .swv_data.cycles = 2, .swv_data.pulse_amplitude = 100,
                                    .swv_data.pulse_period = 12, .swv_data.pulse_width = 6,
                                    .swv_data.step_pulse = 50, .swv_data.v_max = 1500,
                                    .swv_data.v_min = 200};

   TEST_ASSERT_EQUAL(1, experimentSet(&experiment_input));
}

void test_experimentSet_NULL( void ) 
{
   experiment_t experiment_input = {.experiment_type = "swv"};

   TEST_ASSERT_EQUAL(0, experimentSet(&experiment_input));
}

void test_convertVoltageToCode( void )
{
   uint16_t data_test;

   TEST_ASSERT_EQUAL(65535, convertVoltageToCode(1500));
}


/*=====[Prototypes (declarations) of private functions]====================*/