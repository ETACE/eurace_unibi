/**
 * \file  unittest.c
 * \brief Holds main function of the unittest program.
 */
#include "../../header.h"
#include <CUnit/Basic.h>

/*************************** unittest prototypes ***************************/
void unittest_Eurostat_reset_data();
void unittest_Eurostat_compute_mean_price();

void unittest_Eurostat_read_firm_data();
void unittest_Eurostat_compute_region_firm_data();
void unittest_Eurostat_compute_global_firm_data();

void unittest_Eurostat_read_household_data();
void unittest_Eurostat_compute_region_household_data();
void unittest_Eurostat_compute_global_household_data();

void unittest_Eurostat_calc_macro_data();
void unittest_Eurostat_calc_price_index();
void unittest_Eurostat_calc_firm_population();
void unittest_Eurostat_calc_firm_survival_rates();

void unittest1_Eurostat_store_history_monthly();
void unittest2_Eurostat_store_history_monthly();
void unittest3_Eurostat_store_history_monthly();

void unittest1_Eurostat_store_history_quarterly();
void unittest2_Eurostat_store_history_quarterly();
void unittest3_Eurostat_store_history_quarterly();
void unittest4_Eurostat_store_history_quarterly();

void unittest1_Eurostat_compute_growth_rates_monthly();
void unittest2_Eurostat_compute_growth_rates_monthly();

void unittest1_Eurostat_compute_growth_rates_quarterly();
void unittest2_Eurostat_compute_growth_rates_quarterly();

void unittest_Eurostat_firm_creation();
void unittest1_Eurostat_measure_recession();
void unittest2_Eurostat_measure_recession();
void unittest3_Eurostat_measure_recession();
void unittest4_Eurostat_measure_recession();
void unittest_Eurostat_measure_export();

void unittest_Household_receive_data();
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
   		NULL == CU_add_test(pSuite, "Eurostat_reset_data", unittest_Eurostat_reset_data) ||
     	NULL == CU_add_test(pSuite, "Eurostat_compute_mean_price", unittest_Eurostat_compute_mean_price) ||
     	NULL == CU_add_test(pSuite, "Eurostat_read_firm_data", unittest_Eurostat_read_firm_data) ||
     	NULL == CU_add_test(pSuite, "Eurostat_compute_region_firm_data", unittest_Eurostat_compute_region_firm_data) ||
     	NULL == CU_add_test(pSuite, "Eurostat_compute_global_firm_data", unittest_Eurostat_compute_global_firm_data) ||
     	NULL == CU_add_test(pSuite, "Eurostat_read_household_data", unittest_Eurostat_read_household_data) ||
     	NULL == CU_add_test(pSuite, "Eurostat_compute_region_household_data", unittest_Eurostat_compute_region_household_data) ||
     	NULL == CU_add_test(pSuite, "Eurostat_compute_global_household_data", unittest_Eurostat_compute_global_household_data) ||

       	NULL == CU_add_test(pSuite, "Eurostat_calc_macro_data", unittest_Eurostat_calc_macro_data) ||

    	NULL == CU_add_test(pSuite, "Eurostat_calc_price_index", unittest_Eurostat_calc_price_index) ||
    	NULL == CU_add_test(pSuite, "Eurostat_calc_firm_population", unittest_Eurostat_calc_firm_population) ||
    	NULL == CU_add_test(pSuite, "Eurostat_calc_firm_survival_rates", unittest_Eurostat_calc_firm_survival_rates) ||

     	NULL == CU_add_test(pSuite, "Eurostat_store_history_monthly 1: history storage and shifting of economy-wide data", unittest1_Eurostat_store_history_monthly) ||
     	NULL == CU_add_test(pSuite, "Eurostat_store_history_monthly 2: history storage of region data", unittest2_Eurostat_store_history_monthly) ||
     	NULL == CU_add_test(pSuite, "Eurostat_store_history_monthly 3: history shifting of region data", unittest3_Eurostat_store_history_monthly) ||

     	NULL == CU_add_test(pSuite, "Eurostat_store_history_quarterly 1: history storage of economy-wide data", unittest1_Eurostat_store_history_quarterly)  ||
    	NULL == CU_add_test(pSuite, "Eurostat_store_history_quarterly 2: history shifting of economy-wide data", unittest2_Eurostat_store_history_quarterly) ||
    	NULL == CU_add_test(pSuite, "Eurostat_store_history_quarterly 3: history storage of region data", unittest3_Eurostat_store_history_quarterly) ||
		NULL == CU_add_test(pSuite, "Eurostat_store_history_quarterly 4: history shifting of region data", unittest4_Eurostat_store_history_quarterly) ||

    	NULL == CU_add_test(pSuite, "Eurostat_compute_growth_rates_monthly 1: monthly growth rates of economy-wide data", unittest1_Eurostat_compute_growth_rates_monthly) ||
    	NULL == CU_add_test(pSuite, "Eurostat_compute_growth_rates_monthly 2: monthly growth rates of region data", unittest2_Eurostat_compute_growth_rates_monthly) ||
    	NULL == CU_add_test(pSuite, "Eurostat_compute_growth_rates_quarterly 1: quarterly growth rates of economy-wide data", unittest1_Eurostat_compute_growth_rates_quarterly) ||
    	NULL == CU_add_test(pSuite, "Eurostat_compute_growth_rates_quarterly 2: quarterly growth rates of region data", unittest1_Eurostat_compute_growth_rates_quarterly) ||
    	NULL == CU_add_test(pSuite, "Eurostat_firm_creation", unittest_Eurostat_firm_creation) ||
    	
    	NULL == CU_add_test(pSuite, "Eurostat_measure_recession 1: Detect recession", unittest1_Eurostat_measure_recession) ||
    	NULL == CU_add_test(pSuite, "Eurostat_measure_recession 2: Recession in progress, duration updated by 1, recession continues", unittest2_Eurostat_measure_recession) ||
    	NULL == CU_add_test(pSuite, "Eurostat_measure_recession 3: Recession in progress, duration updated by 1, recession stops", unittest3_Eurostat_measure_recession) ||
    	NULL == CU_add_test(pSuite, "Eurostat_measure_recession 4: No recession occurs", unittest4_Eurostat_measure_recession) ||

    	NULL == CU_add_test(pSuite, "Eurostat_measure_export", unittest_Eurostat_measure_export))    	
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
