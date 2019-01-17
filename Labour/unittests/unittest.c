/**
 * \file  unittest.c
 * \brief Holds main function of the unittest program.
 */
#include "../../header.h"
#include <CUnit/Basic.h>

/*************************** unittest prototypes ***************************/
void unittest_Firm_calculate_specific_skills_and_wage_offer();
void unittest_Firm_calculate_specific_skills_and_wage_offer_1();
void unittest_Firm_send_vacancies();
void unittest_Firm_send_vacancies_1();
void unittest_Firm_send_redundancies();
void unittest_Firm_send_redundancies_1();
void unittest_Firm_send_random_redundancies();
void unittest_Firm_send_random_redundancies_1();
void unittest_Firm_read_job_applications_send_job_offer_or_rejection();
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_1_1();
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_1_2();
void unittest_Firm_read_job_responses();
void unittest_Firm_read_job_responses_1_1();
void unittest_Firm_read_job_quitting();
void unittest_Firm_read_job_quitting_1_1();
void unittest_Firm_update_wage_offer();
void unittest_Firm_send_vacancies_2();
void unittest_Firm_send_vacancies_2_1();
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_2();
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_2_1();
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_2_2();
void unittest_Firm_read_job_responses_2();
void unittest_Firm_read_job_responses_2_1();
void unittest_Firm_read_job_quitting_2();
void unittest_Firm_read_job_quitting_2_1();
void unittest_Firm_update_wage_offer_2();
void unittest_Firm_update_wage_offer_2_1();
void unittest_Firm_compute_mean_wage_specific_skills();
void unittest_Firm_compute_mean_wage_specific_skills_1();

void unittest_Household_receive_wage();
void unittest_Household_receive_wage_1();
void unittest_Household_update_specific_skills();
void unittest_Household_update_specific_skills_1();
void unittest_Household_read_firing_messages();
void unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications();
void unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_1();
void unittest_Household_read_job_offers_send_response();
void unittest_Household_read_job_offers_send_response_1();
void unittest_Household_read_application_rejection_update_wage_reservation();
void unittest_Household_read_application_rejection_update_wage_reservation_1();
void unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2();
void unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2_1();
void unittest_Household_read_job_offers_send_response_2();
void unittest_Household_read_job_offers_send_response_2_1();
void unittest_Household_read_application_rejection_update_wage_reservation_2();
void unittest_Household_read_application_rejection_update_wage_reservation_2_1();

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
    CU_pSuite pSuite2 = NULL;
   
    
    /* Init FLAME */
    initialise_unit_testing();
    
    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("Suite_Firm_unittests", init_suite1, clean_suite1);
    if (NULL == pSuite)
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
   
    /* add the tests to the suite */
    /* add extra tests using || */
    

    if(NULL == CU_add_test(pSuite, "Firm_calculate_specific_skills_and_wage_offer CASE 0",unittest_Firm_calculate_specific_skills_and_wage_offer)||
    		NULL == CU_add_test(pSuite, "Firm_calculate_specific_skills_and_wage_offer CASE 1",unittest_Firm_calculate_specific_skills_and_wage_offer_1)||
    		NULL == CU_add_test(pSuite, "Firm_send_vacancies CASE 0",unittest_Firm_send_vacancies)||
    		NULL == CU_add_test(pSuite, "Firm_send_vacancies CASE 1",unittest_Firm_send_vacancies_1)||
    		NULL == CU_add_test(pSuite, "Firm_send_redundancies CASE 0",unittest_Firm_send_redundancies)||
    		NULL == CU_add_test(pSuite, "Firm_send_redundancies CASE 1",unittest_Firm_send_redundancies_1)||
    		NULL == CU_add_test(pSuite, "Firm_send_random_redundancies CASE 0",unittest_Firm_send_random_redundancies)||
    		NULL == CU_add_test(pSuite, "Firm_send_random_redundancies CASE 1",unittest_Firm_send_random_redundancies_1)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_applications_send_job_offer_or_rejection CASE 0",unittest_Firm_read_job_applications_send_job_offer_or_rejection)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_applications_send_job_offer_or_rejection CASE 1",unittest_Firm_read_job_applications_send_job_offer_or_rejection_1_1)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_applications_send_job_offer_or_rejection CASE 2",unittest_Firm_read_job_applications_send_job_offer_or_rejection_1_2)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_responses CASE 0",unittest_Firm_read_job_responses)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_responses CASE 1",unittest_Firm_read_job_responses_1_1)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_quitting CASE 0",unittest_Firm_read_job_quitting)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_quitting CASE 1",unittest_Firm_read_job_quitting_1_1)||
    		NULL == CU_add_test(pSuite, "Firm_update_wage_offer",unittest_Firm_update_wage_offer)||
    		NULL == CU_add_test(pSuite, "Firm_send_vacancies_2 CASE 0",unittest_Firm_send_vacancies_2)||
    		NULL == CU_add_test(pSuite, "Firm_send_vacancies_2 CASE 1",unittest_Firm_send_vacancies_2_1)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_applications_send_job_offer_or_rejection_2 CASE 0",unittest_Firm_read_job_applications_send_job_offer_or_rejection_2)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_applications_send_job_offer_or_rejection_2 CASE 1",unittest_Firm_read_job_applications_send_job_offer_or_rejection_2_1)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_applications_send_job_offer_or_rejection_2 CASE 2",unittest_Firm_read_job_applications_send_job_offer_or_rejection_2_2)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_responses_2 CASE 0",unittest_Firm_read_job_responses_2)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_responses_2 CASE 1",unittest_Firm_read_job_responses_2_1)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_quitting_2 CASE 0",unittest_Firm_read_job_quitting_2)||
    		NULL == CU_add_test(pSuite, "Firm_read_job_quitting_2 CASE 1",unittest_Firm_read_job_quitting_2_1)||
    		NULL == CU_add_test(pSuite, "Firm_update_wage_offer_2 CASE 0",unittest_Firm_update_wage_offer_2)||
    		NULL == CU_add_test(pSuite, "Firm_update_wage_offer_2 CASE 1",unittest_Firm_update_wage_offer_2_1)||
    		NULL == CU_add_test(pSuite, "Firm_compute_mean_wage_specific_skills CASE 0",unittest_Firm_compute_mean_wage_specific_skills)||
    		NULL == CU_add_test(pSuite, "Firm_compute_mean_wage_specific_skills CASE 1",unittest_Firm_compute_mean_wage_specific_skills_1)
    	)
    	
	{
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    printf("\n");
    printf(" ");
        
        pSuite2 = CU_add_suite("Suite_Household_unittests", init_suite1, clean_suite1);
              if (NULL == pSuite2)
              {
                  CU_cleanup_registry();
                  return CU_get_error();
              }
              
                    
               
        if(NULL == CU_add_test(pSuite2, "Household_receive_wage CASE 0 ",unittest_Household_receive_wage)||
        		NULL == CU_add_test(pSuite2, "Household_receive_wage CASE 1",unittest_Household_receive_wage_1)||
        		NULL == CU_add_test(pSuite2, "Household_update_specific_skills CASE 0",unittest_Household_update_specific_skills)||
        		NULL == CU_add_test(pSuite2, "Household_update_specific_skills CASE 1",unittest_Household_update_specific_skills_1)||
        		NULL == CU_add_test(pSuite2, "Household_read_firing_messages CASE 0",unittest_Household_read_firing_messages)||
        		NULL == CU_add_test(pSuite2, "Household_UNEMPLOYED_read_job_vacancies_and_send_applications CASE 0",unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications)||
        		NULL == CU_add_test(pSuite2, "Household_UNEMPLOYED_read_job_vacancies_and_send_applications CASE 1",unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_1)||
        		NULL == CU_add_test(pSuite2, "Household_read_job_offers_send_response CASE 0",unittest_Household_read_job_offers_send_response)||
        		NULL == CU_add_test(pSuite2, "Household_read_job_offers_send_response CASE 1",unittest_Household_read_job_offers_send_response_1)||
        		NULL == CU_add_test(pSuite2, "Household_read_application_rejection_update_wage_reservation CASE 0",unittest_Household_read_application_rejection_update_wage_reservation)||
        		NULL == CU_add_test(pSuite2, "Household_read_application_rejection_update_wage_reservation CASE 1",unittest_Household_read_application_rejection_update_wage_reservation_1)||
        		NULL == CU_add_test(pSuite2, "Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2 CASE 0",unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2)||
        		NULL == CU_add_test(pSuite2, "Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2 CASE 1",unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2_1)||
        		NULL == CU_add_test(pSuite2, "Household_read_job_offers_send_response_2 CASE 0",unittest_Household_read_job_offers_send_response_2)||
        		NULL == CU_add_test(pSuite2, "Household_read_job_offers_send_response_2 CASE 1",unittest_Household_read_job_offers_send_response_2_1)||
        		NULL == CU_add_test(pSuite2, "Household_read_application_rejection_update_wage_reservation_2 CASE 0",unittest_Household_read_application_rejection_update_wage_reservation_2)||
        		        		NULL == CU_add_test(pSuite2, "Household_read_application_rejection_update_wage_reservation_2 CASE 1",unittest_Household_read_application_rejection_update_wage_reservation_2_1)
           )
        	
        	
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
