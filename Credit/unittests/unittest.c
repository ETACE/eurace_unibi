/**
 * \file  unittest.c
 * \brief Holds main function of the unittest program.
 */
#include "../../header.h"
#include <CUnit/Basic.h>
#include <gsl/gsl_rng.h>

//Must be repeated here:
gsl_rng * FLAME_GSL_RNG;  /* global GSL random generator */

/*************************** unittest prototypes ***************************
void unittest_Bank_read_loan_request_send_offers();
void unittest_Bank_read_interest_payments();
void unittest_Bank_read_debt_installment_payments();
/*************************** end prototypes ***************************/

//void unittest_Bank_decide_credit_conditions();
void unittest1_Firm_ask_loan();
void unittest2_Firm_ask_loan();
void unittest_Bank_receive_installment();

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
	/******* GSL INIT */
	const gsl_rng_type * T;

	gsl_rng_env_setup();

	//returns a pointer to a newly-created instance of gsl_rng
	T = gsl_rng_default;

	FLAME_GSL_RNG = gsl_rng_alloc (T);

	//Init on time
	unsigned long int gsl_seed = (unsigned long int)time(NULL); 
		
	gsl_rng_set(FLAME_GSL_RNG, gsl_seed);
	/******* END GSL INIT */

    CU_pSuite pSuite = NULL;
    
    /* Init FLAME */
    initialise_unit_testing();
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_Bank_unittests", init_suite1, clean_suite1);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add the tests to the suite */
    /* add extra tests using || */
    
    if(
	//CU_add_test(pSuite, "Firm_ask_loan 1", unittest1_Firm_ask_loan) == NULL ||
	//CU_add_test(pSuite, "Firm_ask_loan 2", unittest2_Firm_ask_loan) == NULL)
	CU_add_test(pSuite, "Bank_receive_installment", unittest_Bank_receive_installment) == NULL) //||
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
