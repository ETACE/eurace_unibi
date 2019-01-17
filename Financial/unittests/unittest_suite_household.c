/**
 * \file  unittest.c
 * \brief Holds main function of the unittest program.
 */
#include "../../header.h"
#include <CUnit/Basic.h>

/*************************** unittest prototypes ***************************/

void unittest_Household_receive_index_info();
void unittest1_Household_revises_expected_portfolio();
void unittest2_Household_revises_expected_portfolio();
void unittest3_Household_revises_expected_portfolio();
void unittest_Household_update_portfolio();
void unittest1_logit_decision_model();
void unittest2_logit_decision_model();
/*************************** end prototypes ***************************/

int init_suite1(void)
{
    return 0;
}

int clean_suite1(void)
{
    return 0;
}

/** \fn int main(int argc, char * argv[])
 * \brief Main program loop.
 * \param argc Argument count.
 * \param argv Pointer Pointer to Argument vector.
 */
int main(int argc, char * argv[])
{
    CU_pSuite pSuite = NULL;
    
    /* Init FLAME */
    initialise_unit_testing();
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_Eurostat_unittests", init_suite1, clean_suite1);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    /* add extra tests using || */
    
    if(
           //NULL == CU_add_test(pSuite, "Household_receive_index_info", unittest_Household_receive_index_info)) // ||
	   //NULL == CU_add_test(pSuite, "Household_revises_expected_portfolio Case 1", unittest1_Household_revises_expected_portfolio)) //||
	   //NULL == CU_add_test(pSuite, "Household_revises_expected_portfolio Case 2", unittest2_Household_revises_expected_portfolio)) //||
	   //NULL == CU_add_test(pSuite, "Household_revises_expected_portfolio Case 3", unittest3_Household_revises_expected_portfolio)) //||
	   //NULL == CU_add_test(pSuite, "Household_update_portfolio", unittest_Household_update_portfolio)) // ||
	   NULL == CU_add_test(pSuite, "logit_decision_model Case 1: Logit_beta=Inf", unittest1_logit_decision_model) ||
	   NULL == CU_add_test(pSuite, "logit_decision_model Case 2: Logit_beta=0", unittest2_logit_decision_model)) // ||
        {
            CU_cleanup_registry();
            return CU_get_error();
        }
        
        /* Run all tests using the CUnit Basic interface */
        CU_basic_set_mode(CU_BRM_VERBOSE);
        CU_basic_run_tests();
        CU_cleanup_registry();
        
        /* Free FLAME */
        clean_up(0);
        
        return CU_get_error();
    }
