/**
 * \file  unittest.c
 * \brief Holds main function of the unittest program.
 */
#include "../../header.h"
#include <CUnit/Basic.h>

/*************************** unittest prototypes ***************************/
void unittest_Firm_execute_production();
void unittest_Firm_execute_production_1();
void unittest_Firm_execute_production_2();
void unittest_Firm_calc_production_quantity_1();
void unittest_Firm_calc_production_quantity_2();
void unittest_Firm_calc_production_quantity_3();
void unittest_Firm_receive_capital_goods();
void unittest_Firm_calc_pay_costs();
void unittest_Firm_calc_input_demands();
void unittest_Firm_calc_input_demands_2();
void unittest_Firm_calc_input_demands_3();
void unittest_Firm_calc_input_demands_4();
void unittest_Firm_calc_input_demands_5();
void unittest_Firm_calc_production_quantity_II();
void unittest_Firm_calc_production_quantity_II_2();
void unittest_Firm_calc_production_quantity_II_3();
void unittest_Firm_calc_input_demands_II();
void unittest_Firm_calc_input_demands_II_2();
void unittest_Firm_send_goods_to_mall();
void unittest_Firm_send_goods_to_mall_2();
void unittest_Firm_send_goods_to_mall_3();
void unittest_Firm_send_goods_to_mall_4();
void unittest_Firm_calc_revenue();
void unittest_Firm_compute_sales_statistics();
void unittest_Firm_update_specific_skills_of_worker();

void unittest_Household_determine_consumption_budget();
void unittest_Household_determine_consumption_budget_2();
void unittest_Household_rank_and_buy_goods_1();
void unittest_Household_rank_and_buy_goods_1_2();
void unittest_Household_receive_goods_read_rationing();
void unittest_Household_receive_goods_read_rationing_2();
void unittest_Household_receive_goods_read_rationing_3();
void unittest_Household_rank_and_buy_goods_2();
void unittest_Household_rank_and_buy_goods_2_2();
void unittest_Household_receive_goods_read_rationing_II();
void unittest_Household_handle_leftover_budget();

void unittest_Mall_update_mall_stock();
void unittest_Mall_update_mall_stock_2();
void unittest_Mall_send_quality_price_info_1();
void unittest_Mall_update_mall_stocks_sales_rationing_1();
void unittest_Mall_update_mall_stocks_sales_rationing_1_2();
void unittest_Mall_update_mall_stocks_sales_rationing_2();
void unittest_Mall_update_mall_stocks_sales_rationing_2_2();
void unittest_Mall_pay_firm();
void unittest_Mall_pay_firm_2();
void unittest_Mall_read_insolvency_bankruptcy();
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
    CU_pSuite pSuite3 = NULL;
    
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
    

    if(NULL == CU_add_test(pSuite, "Firm_execute_production Case 1",unittest_Firm_execute_production) ||
    		NULL == CU_add_test(pSuite, "Firm_execute_production Case 2",unittest_Firm_execute_production_1)||
    		NULL == CU_add_test(pSuite, "Firm_execute_production Case 3",unittest_Firm_execute_production_2)||
    		NULL == CU_add_test(pSuite, "Firm_calc_production_quantity(), Case 1",unittest_Firm_calc_production_quantity_1) ||
    		NULL == CU_add_test(pSuite, "Firm_calc_production_quantity(), Case 2",unittest_Firm_calc_production_quantity_2) || 
    		NULL == CU_add_test(pSuite, "Firm_calc_production_quantity() Case 3",unittest_Firm_calc_production_quantity_3)||
    		NULL == CU_add_test(pSuite, "Firm_receive_capital_goods",unittest_Firm_receive_capital_goods)||
NULL == CU_add_test(pSuite, "Firm_calc_pay_costs()",unittest_Firm_calc_pay_costs)|| 
NULL == CU_add_test(pSuite, "Firm_calc_input_demands Case 1",unittest_Firm_calc_input_demands)||
NULL == CU_add_test(pSuite, "Firm_calc_input_demands Case 2",unittest_Firm_calc_input_demands_2)|| 
NULL == CU_add_test(pSuite, "Firm_calc_input_demands Case 3",unittest_Firm_calc_input_demands_3)||
NULL == CU_add_test(pSuite, "Firm_calc_input_demands Case 4",unittest_Firm_calc_input_demands_4)|| 
NULL == CU_add_test(pSuite, "Firm_calc_input_demands Case 5",unittest_Firm_calc_input_demands_5)||
NULL == CU_add_test(pSuite,  "Firm_calc_production_quantity_2 Case 1",unittest_Firm_calc_production_quantity_II)||
NULL == CU_add_test(pSuite,  "Firm_calc_production_quantity_2 Case 2",unittest_Firm_calc_production_quantity_II_2)||
NULL == CU_add_test(pSuite,  "Firm_calc_production_quantity_2 Case 3",unittest_Firm_calc_production_quantity_II_3)||
NULL == CU_add_test(pSuite,  "Firm_calc_input_demands_2 Case 1",unittest_Firm_calc_input_demands_II)||
NULL == CU_add_test(pSuite,  "Firm_calc_input_demands_2 Case 2",unittest_Firm_calc_input_demands_II_2)||
NULL == CU_add_test(pSuite,  "Firm_send_goods_to_mall Case 1",unittest_Firm_send_goods_to_mall)||
NULL == CU_add_test(pSuite,  "Firm_send_goods_to_mall Case 2",unittest_Firm_send_goods_to_mall_2)||
NULL == CU_add_test(pSuite,  "Firm_send_goods_to_mall Case 3",unittest_Firm_send_goods_to_mall_3)||
NULL == CU_add_test(pSuite,  "Firm_send_goods_to_mall Case 4",unittest_Firm_send_goods_to_mall_4)||
NULL == CU_add_test(pSuite,  "Firm_calc_revenue",unittest_Firm_calc_revenue)||
NULL == CU_add_test(pSuite,  "Firm_compute_sales_statistics",unittest_Firm_compute_sales_statistics)||
NULL == CU_add_test(pSuite,  "Firm_update_specific_skills_of_worker",unittest_Firm_update_specific_skills_of_worker))

	{
        CU_cleanup_registry();
        return CU_get_error();
    }
    

 printf("\n");
    
    pSuite2 = CU_add_suite("Suite_Household_unittests", init_suite1, clean_suite1);
          if (NULL == pSuite2)
          {
              CU_cleanup_registry();
              return CU_get_error();
          }
          
                
           
    if(NULL == CU_add_test(pSuite2, "Household_determine_consumption_budget Case 1",unittest_Household_determine_consumption_budget)||
       NULL == CU_add_test(pSuite2, "Household_determine_consumption_budget Case 2",unittest_Household_determine_consumption_budget_2)||
       NULL == CU_add_test(pSuite2, "Household_rank_and_buy_goods_1 Case 1", unittest_Household_rank_and_buy_goods_1)||
       NULL == CU_add_test(pSuite2, "Household_rank_and_buy_goods_1 Case 2", unittest_Household_rank_and_buy_goods_1_2)||
       NULL == CU_add_test(pSuite2, "Household_receive_goods_read_rationin Case 1", unittest_Household_receive_goods_read_rationing)||
       NULL == CU_add_test(pSuite2, "Household_receive_goods_read_rationing Case 2", unittest_Household_receive_goods_read_rationing_2)||
       NULL == CU_add_test(pSuite2, "Household_receive_goods_read_rationing Case 3", unittest_Household_receive_goods_read_rationing_3)||
       NULL == CU_add_test(pSuite2, "Household_rank_and_buy_goods_2 Case 1", unittest_Household_rank_and_buy_goods_2)||
       NULL == CU_add_test(pSuite2, "Household_rank_and_buy_goods_2 Case 2", unittest_Household_rank_and_buy_goods_2_2)||
       NULL == CU_add_test(pSuite2, "Household_receive_goods_read_rationing_2", unittest_Household_receive_goods_read_rationing_II)||
       NULL == CU_add_test(pSuite2, "Household_handle_leftover_budget", unittest_Household_handle_leftover_budget))


   	{
           CU_cleanup_registry();
           return CU_get_error();
       }
    printf("\n");   
    
    pSuite3 = CU_add_suite("Suite_Mall_unittests", init_suite1, clean_suite1);
             if (NULL == pSuite3)
             {
                 CU_cleanup_registry();
                 return CU_get_error();
             }
             
                        
                
       if(	   NULL == CU_add_test(pSuite3, "Mall_update_mall_stock",unittest_Mall_update_mall_stock)||
    		   NULL == CU_add_test(pSuite3, "Mall_update_mall_stock Case 2",unittest_Mall_update_mall_stock_2)||
    		   NULL == CU_add_test(pSuite3, "Mall_send_quality_price_info_1",unittest_Mall_send_quality_price_info_1)||
    		   NULL == CU_add_test(pSuite3, "Mall_update_mall_stocks_sales_rationing_1 Case 1",unittest_Mall_update_mall_stocks_sales_rationing_1)||
    		   NULL == CU_add_test(pSuite3, "Mall_update_mall_stocks_sales_rationing_1 Case 2",unittest_Mall_update_mall_stocks_sales_rationing_1_2)||
    		   NULL == CU_add_test(pSuite3, "Mall_update_mall_stocks_sales_rationing_2 Case 1",unittest_Mall_update_mall_stocks_sales_rationing_2)||
    		   NULL == CU_add_test(pSuite3, "Mall_update_mall_stocks_sales_rationing_2 Case 2",unittest_Mall_update_mall_stocks_sales_rationing_2_2)||
    		   NULL == CU_add_test(pSuite3, "Mall_pay_firm Case 1",unittest_Mall_pay_firm)||
    		   NULL == CU_add_test(pSuite3, "Mall_pay_firm Case 2",unittest_Mall_pay_firm_2)||
    		   NULL == CU_add_test(pSuite3, "Mall_read_insolvency_bankruptcy",unittest_Mall_read_insolvency_bankruptcy))
         

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
