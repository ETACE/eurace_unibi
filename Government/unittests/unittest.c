/**
 * \file  unittest.c
 * \brief Holds main function of the unittest program.
 */
//#include "../header.h"
#include "../../header.h"
#include <CUnit/Basic.h>

/*************************** unittest prototypes ***************************/
void unittest1_Government_send_policy_announcements();
void unittest2_Government_send_policy_announcements();
void unittest_Government_read_tax_payments();
void unittest1_Government_read_unemployment_benefit_notifications();
void unittest2_Government_read_unemployment_benefit_notifications();
void unittest_Government_read_transfer_notifications();
void unittest_Government_read_subsidy_notifications();
void unittest_Government_budget_accounting();
void unittest_Government_send_account_update();
void unittest_Government_read_data_from_Eurostat();
void unittest_Government_set_policy();
void unittest_Government_yearly_resetting();
void unittest_Government_monthly_resetting();

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
    pSuite = CU_add_suite("Suite_Government_unittests", init_suite1, clean_suite1);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    /* add extra tests using || */
    
    if(
    	NULL == CU_add_test(pSuite, "Government_send_policy_announcements Case 1", unittest1_Government_send_policy_announcements) ||
    	NULL == CU_add_test(pSuite, "Government_send_policy_announcements Case 2", unittest2_Government_send_policy_announcements)) // ||
     	//NULL == CU_add_test(pSuite, "Government_read_tax_payments", unittest_Government_read_tax_payments) ||
    	//NULL == CU_add_test(pSuite, "Government_read_unemployment_benefit_notifications: case 1", unittest1_Government_read_unemployment_benefit_notifications) ||
    	//NULL == CU_add_test(pSuite, "Government_read_unemployment_benefit_notifications: case 2", unittest2_Government_read_unemployment_benefit_notifications) ||
    	//NULL == CU_add_test(pSuite, "Government_read_transfer_notifications", unittest_Government_read_transfer_notifications) ||
		//NULL == CU_add_test(pSuite, "Government_read_subsidy_notifications", unittest_Government_read_subsidy_notifications))

    	//NULL == CU_add_test(pSuite, "Government_budget_accounting", unittest_Government_budget_accounting))
		//NULL == CU_add_test(pSuite, "Government_send_account_update", unittest_Government_send_account_update))
		//NULL == CU_add_test(pSuite, "Government_read_data_from_Eurostat", unittest_Government_read_data_from_Eurostat))

		//NULL == CU_add_test(pSuite, "Government_set_policy", unittest_Government_set_policy))
		//NULL == CU_add_test(pSuite, "Government_yearly_resetting", unittest_Government_yearly_resetting))
   		//NULL == CU_add_test(pSuite, "Government_yearly_resetting", unittest_Government_monthly_resetting))
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
