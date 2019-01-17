/**
 * \file  unittest.c
 * \brief Holds main function of the unittest program.
 */
#include "../../header.h"
#include <CUnit/Basic.h>

/*************************** unittest prototypes ***************************/
void unittest_Minitest();
void unittest_ClearingHouse_send_index_info();
void unittest_ClearingHouse_receive_dividend_info();
void unittest_ClearingHouse_receive_orders();
void unittest1_ClearingHouse_compute_transactions();
void unittest2_ClearingHouse_compute_transactions();
void unittest3_ClearingHouse_compute_transactions();
void unittest4_ClearingHouse_compute_transactions();
void unittest5_ClearingHouse_compute_transactions();
void unittest_ClearingHouse_send_transaction_info();
void unittest_ClearingHouse_update_price();
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
           //NULL == CU_add_test(pSuite, "Minitest", unittest_Minitest)) // ||
           NULL == CU_add_test(pSuite, "ClearingHouse_send_index_info", unittest_ClearingHouse_send_index_info)) // ||
	   //NULL == CU_add_test(pSuite, "ClearingHouse_receive_dividend_info", unittest_ClearingHouse_receive_dividend_info)) // ||
           //NULL == CU_add_test(pSuite, "ClearingHouse_receive_orders", unittest_ClearingHouse_receive_orders) ||
	   //NULL == CU_add_test(pSuite, "ClearingHouse_receive_compute_transactions, Case 1", unittest1_ClearingHouse_compute_transactions)) // ||
	   //NULL == CU_add_test(pSuite, "ClearingHouse_receive_compute_transactions, Case 2", unittest2_ClearingHouse_compute_transactions)) // ||
           //NULL == CU_add_test(pSuite, "ClearingHouse_receive_compute_transactions, Case 3", unittest3_ClearingHouse_compute_transactions)) // ||
	   //NULL == CU_add_test(pSuite, "ClearingHouse_receive_compute_transactions, Case 4", unittest4_ClearingHouse_compute_transactions)) // ||
	   //NULL == CU_add_test(pSuite, "ClearingHouse_receive_compute_transactions, Case 5", unittest5_ClearingHouse_compute_transactions)) // ||
	   //NULL == CU_add_test(pSuite, "ClearingHouse_send_transaction_info", unittest_ClearingHouse_send_transaction_info))
	   //NULL == CU_add_test(pSuite, "ClearingHouse_update_price", unittest_ClearingHouse_update_price)) // ||
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
