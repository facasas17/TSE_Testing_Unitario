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

void test_experimentSet( void ) 
{
   //int datos[] = {1,2,3,4,5};
   //int resultado;
   experiment_t experiment_input = {.experiment_type = "XCV"};

   TEST_ASSERT_EQUAL(0, experimentSet(&experiment_input));
   //TEST_ASSERT_EQUAL(3, resultado);
}

/*=====[Prototypes (declarations) of private functions]====================*/