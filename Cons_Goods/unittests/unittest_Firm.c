#include <CUnit/Basic.h>
//For trunk model
#include "../../header.h"
#include "../../Firm_agent_header.h"
#include "../../my_library_header.h"
#include "../Mall_aux_header.h"

/*
 * 1) initialize agent
 * 2) add memory pre-conditions
 * 3) initialise MBs
 * 4) add message pre-conditions
 * 5) create MB iterators
 * 6) evaluate function to be tested
 * 7) assertions on memory post-conditions
 * 8) assertions on message post-conditions
 * 9) free agent
 * 10) free MBs
 */

/*
 * \fn: void unittest_<Agentname>_function()
 * \brief: Unit test for: <Agentname>_function.
 * Status: NOT Tested
 */
void unittest_Firm_execute_production()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	    
	        MEAN_SPECIFIC_SKILLS=1;
	        TECHNOLOGY = 1.5;
	        NO_EMPLOYEES=100;
	        ALPHA = 0.5;
	        BETA = 0.5;
	    	PLANNED_PRODUCTION_QUANTITY = 100;
	        TOTAL_UNITS_CAPITAL_STOCK=100;
	      
	   
	    
	    	    
    /***** Function evaluation ***************************************/
	Firm_execute_production();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(PRODUCTION_QUANTITY,100.0, 1e-3);

    
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
	free_messages();
}

void unittest_Firm_execute_production_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	    
	        MEAN_SPECIFIC_SKILLS=1;
	        TECHNOLOGY = 1.5;
	        NO_EMPLOYEES=100;
	        ALPHA = 0.5;
	        BETA = 0.5;
	    	PLANNED_PRODUCTION_QUANTITY = 0.0;
	        TOTAL_UNITS_CAPITAL_STOCK=100;
	      
	   
	    
	    	    
    /***** Function evaluation ***************************************/
	Firm_execute_production();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(PRODUCTION_QUANTITY,0, 1e-3);

    
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
	free_messages();
}

void unittest_Firm_execute_production_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	    
	        MEAN_SPECIFIC_SKILLS=1.5;
	        TECHNOLOGY = 1;
	        NO_EMPLOYEES=100;
		ALPHA = 0.5;
		BETA = 0.5;
	    	PLANNED_PRODUCTION_QUANTITY = 100;
	        TOTAL_UNITS_CAPITAL_STOCK=100;
	      
	   
	    
	    	    
    /***** Function evaluation ***************************************/
	Firm_execute_production();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(PRODUCTION_QUANTITY,100, 1e-3);

	

	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
	free_messages();
}



/**************************************************************************************************
Unit test of Firm Function Firm_calc_production_quantity
***************************************************************************************************
*/


/*
* Case 1: The malls are not completely sold out and current stock < critical stock
*/
void unittest_Firm_calc_production_quantity_1()
{    	
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	    
	        PRICE = 1;
		DISCOUNT_RATE = 0.01;
		UNIT_COSTS = 0.5;
		INVENTORY_COSTS_PER_UNIT= 0.5;
		LAMBDA = 1.0;
		FIRM_PLANNING_HORIZON = 10;
		ADAPTION_DELIVERY_VOLUME  = 1.0;
	      
	   
	   	reset_mall_info_array(&CURRENT_MALL_STOCKS);
    		add_mall_info(&CURRENT_MALL_STOCKS, 1, 100.0, 20.0);
   		add_mall_info(&CURRENT_MALL_STOCKS, 2, 200.0, 50.0);
		

		reset_delivery_volume_per_mall_array(&PLANNED_DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 1, 0, 0, 0);
   		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 2, 0, 0, 0);

		reset_sales_statistics_array(&MALLS_SALES_STATISTICS);

		add_sales_statistics(&MALLS_SALES_STATISTICS,1,0);
		add_sales_statistics(&MALLS_SALES_STATISTICS,2,0);

		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,1,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,2,20.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,3,30.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,4,80.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,5,90.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,6,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,7,50.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,8,60.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,9,70.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,10,40.0);

		
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,1,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,2,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,3,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,4,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,5,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,6,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,7,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,8,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,9,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,10,100.0);

   		
		
            
            	reset_double_array(&LAST_PLANNED_PRODUCTION_QUANTITIES);

		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);

  
    /***** Function evaluation ***************************************/
	Firm_calc_production_quantity();


    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[0].critical_stock,70.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[1].critical_stock,100.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_DELIVERY_VOLUME.array[0].quantity,50.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_DELIVERY_VOLUME.array[1].quantity,50.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_QUANTITY,100.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_OUTPUT,100.00, 1e-3);
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
	free_messages();
}

/*
* Case 2: One mall is completely sold out
*/
void unittest_Firm_calc_production_quantity_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	    
	        PRICE = 1;
		DISCOUNT_RATE = 0.01;
		UNIT_COSTS = 0.5;
		INVENTORY_COSTS_PER_UNIT= 0.5;
		LAMBDA = 1.0;
		FIRM_PLANNING_HORIZON = 10;
		ADAPTION_DELIVERY_VOLUME  = 1.0;
	      
	   
	   	reset_mall_info_array(&CURRENT_MALL_STOCKS);
    		add_mall_info(&CURRENT_MALL_STOCKS, 1, 100.0, 0.0);
   		add_mall_info(&CURRENT_MALL_STOCKS, 2, 200.0, 50.0);
		

		reset_delivery_volume_per_mall_array(&PLANNED_DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 1, 0, 0, 0);
   		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 2, 0, 0, 0);

		reset_sales_statistics_array(&MALLS_SALES_STATISTICS);

		add_sales_statistics(&MALLS_SALES_STATISTICS,1,0);
		add_sales_statistics(&MALLS_SALES_STATISTICS,2,0);

		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,1,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,2,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,3,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,4,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,5,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,6,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,7,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,8,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,9,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,10,100.0);

		
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,1,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,2,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,3,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,4,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,5,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,6,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,7,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,8,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,9,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,10,100.0);

   		
		
            
            	reset_double_array(&LAST_PLANNED_PRODUCTION_QUANTITIES);

		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);

  
    /***** Function evaluation ***************************************/
	Firm_calc_production_quantity();


    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[0].critical_stock,200.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[1].critical_stock,100.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_DELIVERY_VOLUME.array[0].quantity,200.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_DELIVERY_VOLUME.array[1].quantity,50.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_QUANTITY,250.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_OUTPUT,250.00, 1e-3);
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
	free_messages();
}


/*
* Case 3: The critical stocks are lower than current stocks
*/
void unittest_Firm_calc_production_quantity_3()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	    
	        PRICE = 1;
		DISCOUNT_RATE = 0.01;
		UNIT_COSTS = 0.5;
		INVENTORY_COSTS_PER_UNIT= 0.5;
		LAMBDA = 1.0;
		FIRM_PLANNING_HORIZON = 10;
		ADAPTION_DELIVERY_VOLUME  = 1.0;
	      
	   
	   	reset_mall_info_array(&CURRENT_MALL_STOCKS);
    		add_mall_info(&CURRENT_MALL_STOCKS, 1, 100.0, 150.0);
   		add_mall_info(&CURRENT_MALL_STOCKS, 2, 100.0, 150.0);
		

		reset_delivery_volume_per_mall_array(&PLANNED_DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 1, 0, 0, 0);
   		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 2, 0, 0, 0);

		reset_sales_statistics_array(&MALLS_SALES_STATISTICS);

		add_sales_statistics(&MALLS_SALES_STATISTICS,1,0);
		add_sales_statistics(&MALLS_SALES_STATISTICS,2,0);

		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,1,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,2,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,3,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,4,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,5,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,6,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,7,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,8,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,9,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,10,100.0);

		
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,1,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,2,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,3,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,4,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,5,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,6,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,7,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,8,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,9,100.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,10,100.0);

   		
		
            
            	reset_double_array(&LAST_PLANNED_PRODUCTION_QUANTITIES);

		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);
		add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,100.0);

  
    /***** Function evaluation ***************************************/
	Firm_calc_production_quantity();


    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[0].critical_stock,100.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[1].critical_stock,100.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_DELIVERY_VOLUME.array[0].quantity,0.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_DELIVERY_VOLUME.array[1].quantity,0.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_QUANTITY,0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_OUTPUT,0, 1e-3);
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
	free_messages();
}

void unittest_Firm_receive_capital_goods()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

		ID= 1;
		TOTAL_UNITS_CAPITAL_STOCK = 100.0;
		TECHNOLOGY= 1.0;
		TOTAL_VALUE_CAPITAL_STOCK= 1000.0;

		CONST_INSTALLMENT_PERIODS = 10;
		
		reset_financing_capital_array(&CAPITAL_FINANCING);
    		add_financing_capital(&CAPITAL_FINANCING, 100, 10);

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_capital_good_delivery, sizeof(m_capital_good_delivery));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create '<message>' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	
	/***** Messages: pre-conditions **********************************/
    add_capital_good_delivery_message(ID,100.0,2.0,20.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_capital_good_delivery, &i_capital_good_delivery);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: '<message>' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: '<message>' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}
	    	    
    /***** Function evaluation ***************************************/
	Firm_receive_capital_goods();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_UNITS_CAPITAL_STOCK,200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TECHNOLOGY,1.5, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_CAPITAL_STOCK,1500.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(CAPITAL_COSTS,2000.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(CAPITAL_FINANCING.array[1].financing_per_month,200.0, 1e-3);	
    CU_ASSERT_EQUAL(CAPITAL_FINANCING.array[1].nr_periods_before_repayment,10);
   
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


void unittest_Firm_calc_pay_costs()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	ID = 1;
	CAPITAL_COSTS = 200.0;
	TOTAL_INTEREST_PAYMENT = 10.0;
	TECHNOLOGY = 2.0;
	MEAN_SPECIFIC_SKILLS = 1.5;
	PRODUCTION_QUANTITY = 100.0;
	MARK_UP = 0.5;
	PAYMENT_ACCOUNT = 1000.0;
	PLANNED_PRODUCTION_QUANTITY=100.0;
	
	reset_employee_array(&EMPLOYEES);
    	add_employee(&EMPLOYEES,2,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,3,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,4,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,5,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,6,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,7,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,8,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,9,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,10,1,1.0,5,1.5);
	add_employee(&EMPLOYEES,11,1,1.0,5,1.5);

	reset_financing_capital_array(&CAPITAL_FINANCING);
    	add_financing_capital(&CAPITAL_FINANCING, 100, 0);	
	add_financing_capital(&CAPITAL_FINANCING, 100, 10);
	add_financing_capital(&CAPITAL_FINANCING, 100, 11);

	reset_double_array(&LAST_PLANNED_PRODUCTION_QUANTITIES);
	add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,50);
	add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,50);	

/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_pay_capital_goods, sizeof(m_pay_capital_goods));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create '<message>' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif

	 rc = MB_Create(&b_wage_payment, sizeof(m_wage_payment));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create '<message>' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	
	    /***** Function evaluation ***************************************/
		Firm_calc_pay_costs();
    	    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_pay_capital_goods, &i_pay_capital_goods);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: '<message>' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: '<message>' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

	rc = MB_Iterator_Create(b_wage_payment, &i_wage_payment);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: '<message>' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: '<message>' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(LABOUR_COSTS,10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(UNIT_COSTS,2.2, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PRICE,3.3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT,790, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PRODUCTION_COSTS,210, 1e-3);

	CU_ASSERT_DOUBLE_EQUAL(CAPITAL_FINANCING.array[0].financing_per_month,100.0, 1e-3);	
    	CU_ASSERT_EQUAL(CAPITAL_FINANCING.array[0].nr_periods_before_repayment,9);
	CU_ASSERT_DOUBLE_EQUAL(CAPITAL_FINANCING.array[1].financing_per_month,100.0, 1e-3);	
    	CU_ASSERT_EQUAL(CAPITAL_FINANCING.array[1].nr_periods_before_repayment,10);
	CU_ASSERT_DOUBLE_EQUAL(LAST_PLANNED_PRODUCTION_QUANTITIES.array[1],100.0, 1e-3);


	
	
    /***** Messages: Message post-conditions *****/
	//start a reading loop

	START_PAY_CAPITAL_GOODS_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(pay_capital_goods_message->firm_id, ID);	
	     CU_ASSERT_DOUBLE_EQUAL(pay_capital_goods_message->capital_bill, 200.0, 1e-3);
	FINISH_PAY_CAPITAL_GOODS_MESSAGE_LOOP

	START_WAGE_PAYMENT_MESSAGE_LOOP
		
		CU_ASSERT_EQUAL(wage_payment_message->firm_id, ID);	
	     	CU_ASSERT_DOUBLE_EQUAL(wage_payment_message->payment, 1.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(wage_payment_message->productivity, 2.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(wage_payment_message->average_specific_skills, 1.5, 1e-3);
	FINISH_WAGE_PAYMENT_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_calc_input_demands()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	MEAN_SPECIFIC_SKILLS=2.0;
	TECHNOLOGY=1.5;
	PLANNED_PRODUCTION_QUANTITY=100.0;
	TOTAL_UNITS_CAPITAL_STOCK=65.0;//60.0
	TOTAL_CAPITAL_DEPRECIATION_UNITS=5.0;
	TOTAL_VALUE_CAPITAL_STOCK=650;
	MEAN_WAGE = 1.0;
	

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	DEPRECIATION_RATE = 0.05;

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_productivity, sizeof(m_productivity));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'productivity,' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	
	/***** Messages: pre-conditions **********************************/
   add_productivity_message(10,2.0,10.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_productivity, &i_productivity);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'productivity'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'productivity board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'productivity' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    /***** Function evaluation ***************************************/	Firm_calc_input_demands();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(TECHNOLOGICAL_FRONTIER, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(ACTUAL_CAP_PRICE, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NEEDED_CAPITAL_STOCK, 67.98693, 1e-3);
	CU_ASSERT_EQUAL(EMPLOYEES_NEEDED, 65);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_UNITS,3.25, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_VALUE,32.5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_UNITS_CAPITAL_STOCK,61.75, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_CAPITAL_STOCK,617.5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DEMAND_CAPITAL_STOCK,6.23693, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS,129.9693, 1e-3);
 
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_calc_input_demands_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	MEAN_SPECIFIC_SKILLS=2.0;
	TECHNOLOGY=1.5;
	PLANNED_PRODUCTION_QUANTITY=100.0;
	TOTAL_UNITS_CAPITAL_STOCK=60.0;
	TOTAL_CAPITAL_DEPRECIATION_UNITS=5.0;
	TOTAL_VALUE_CAPITAL_STOCK=600;
	MEAN_WAGE = 1;
	

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	DEPRECIATION_RATE = 0.05;

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_productivity, sizeof(m_productivity));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'productivity,' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	
	/***** Messages: pre-conditions **********************************/
   add_productivity_message(10,2.0,10);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_productivity, &i_productivity);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'productivity'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'productivity board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'productivity' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    /***** Function evaluation ***************************************/	Firm_calc_input_demands();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NEEDED_CAPITAL_STOCK, 65.0, 1e-3);
	CU_ASSERT_EQUAL(EMPLOYEES_NEEDED, 68);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_UNITS,3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_VALUE,30, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_UNITS_CAPITAL_STOCK,57, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_CAPITAL_STOCK,570, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DEMAND_CAPITAL_STOCK,8, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS,150.72, 1e-3);


    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
/*****************
*Case 3: A > B , C_needed < C_stock + Inv_inertia
******************/
void unittest_Firm_calc_input_demands_3()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	MEAN_SPECIFIC_SKILLS=1.5;
	TECHNOLOGY=2;
	PLANNED_PRODUCTION_QUANTITY=100.0;
	TOTAL_UNITS_CAPITAL_STOCK=65.0;//60.0
	TOTAL_CAPITAL_DEPRECIATION_UNITS=5.0;
	TOTAL_VALUE_CAPITAL_STOCK=650;
	MEAN_WAGE = 1.0;
	

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	DEPRECIATION_RATE = 0.05;

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_productivity, sizeof(m_productivity));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'productivity,' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	
	/***** Messages: pre-conditions **********************************/
   add_productivity_message(10,2.0,10.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_productivity, &i_productivity);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'productivity'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'productivity board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'productivity' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    /***** Function evaluation ***************************************/	Firm_calc_input_demands();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(TECHNOLOGICAL_FRONTIER, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(ACTUAL_CAP_PRICE, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NEEDED_CAPITAL_STOCK, 67.98693, 1e-3);
	CU_ASSERT_EQUAL(EMPLOYEES_NEEDED, 65);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_UNITS,3.25, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_VALUE,32.5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_UNITS_CAPITAL_STOCK,61.75, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_CAPITAL_STOCK,617.5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DEMAND_CAPITAL_STOCK,6.23693, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS,129.9693, 1e-3);
   

    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
/*****************
*Case 4: A > B , C_needed > C_stock + Inv_inertia
******************/
void unittest_Firm_calc_input_demands_4()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	MEAN_SPECIFIC_SKILLS=1.5;
	TECHNOLOGY=2;
	PLANNED_PRODUCTION_QUANTITY=100.0;
	TOTAL_UNITS_CAPITAL_STOCK=60.0;
	TOTAL_CAPITAL_DEPRECIATION_UNITS=5.0;
	TOTAL_VALUE_CAPITAL_STOCK=600;
	MEAN_WAGE = 1;
	

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	DEPRECIATION_RATE = 0.05;

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_productivity, sizeof(m_productivity));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'productivity,' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	
	/***** Messages: pre-conditions **********************************/
   add_productivity_message(10,2.0,10);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_productivity, &i_productivity);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'productivity'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'productivity board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'productivity' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    /***** Function evaluation ***************************************/	Firm_calc_input_demands();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NEEDED_CAPITAL_STOCK, 65.0, 1e-3);
	CU_ASSERT_EQUAL(EMPLOYEES_NEEDED, 68);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_UNITS,3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_VALUE,30, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_UNITS_CAPITAL_STOCK,57, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_CAPITAL_STOCK,570, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DEMAND_CAPITAL_STOCK,8, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS,150.72, 1e-3);

 
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*****************
*Case 5: A > B , C_needed < C_stock => C_demand = 0
******************/
void unittest_Firm_calc_input_demands_5()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	MEAN_SPECIFIC_SKILLS=1.5;
	TECHNOLOGY=2;
	PLANNED_PRODUCTION_QUANTITY=100.0;
	TOTAL_UNITS_CAPITAL_STOCK=80.0;
	TOTAL_CAPITAL_DEPRECIATION_UNITS=5.0;
	TOTAL_VALUE_CAPITAL_STOCK=800;
	MEAN_WAGE = 1;
	

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	DEPRECIATION_RATE = 0.05;

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_productivity, sizeof(m_productivity));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'productivity,' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	
	/***** Messages: pre-conditions **********************************/
   add_productivity_message(10,2.0,10);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_productivity, &i_productivity);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'productivity'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'productivity board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'productivity' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    /***** Function evaluation ***************************************/	Firm_calc_input_demands();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NEEDED_CAPITAL_STOCK, 67.98693, 1e-3);
	CU_ASSERT_EQUAL(EMPLOYEES_NEEDED, 58);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_UNITS,4, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_CAPITAL_DEPRECIATION_VALUE,40, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_UNITS_CAPITAL_STOCK,76, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_CAPITAL_STOCK,760, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DEMAND_CAPITAL_STOCK,0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS,60.32, 1e-3);

 
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
* Case 1: PLANNED_PRODUCTION_COSTS > PAYMENT_ACCOUNT
*
*/


void unittest_Firm_calc_production_quantity_II()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	PLANNED_PRODUCTION_QUANTITY = 100.0;
	PAYMENT_ACCOUNT = 85.0;
	ADAPTION_PRODUCTION_VOLUME_DUE_TO_INSUFFICIENT_FINANCES=0.05;
	PLANNED_PRODUCTION_COSTS =100.0;

	MEAN_SPECIFIC_SKILLS=1;
	TECHNOLOGY=1;
	TOTAL_UNITS_CAPITAL_STOCK=100.0;
	MEAN_WAGE = 1;
	
	

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	ACTUAL_CAP_PRICE = 10;

    /***** Function evaluation ***************************************/
	Firm_calc_production_quantity_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_QUANTITY , 90, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_OUTPUT , 90, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS , 84.24, 1e-3);
    
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
* Case 1: PLANNED_PRODUCTION_COSTS < PAYMENT_ACCOUNT
*
*/


void unittest_Firm_calc_production_quantity_II_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	PLANNED_PRODUCTION_QUANTITY = 100.0;
	PAYMENT_ACCOUNT = 120.0;
	ADAPTION_PRODUCTION_VOLUME_DUE_TO_INSUFFICIENT_FINANCES=0.05;
	PLANNED_PRODUCTION_COSTS =100.0;

	MEAN_SPECIFIC_SKILLS=1;
	TECHNOLOGY=1;
	TOTAL_UNITS_CAPITAL_STOCK=100.0;
	MEAN_WAGE = 1;
	
	

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	ACTUAL_CAP_PRICE = 10;

    /***** Function evaluation ***************************************/
	Firm_calc_production_quantity_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_QUANTITY , 100.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_OUTPUT , 100.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS , 100.0, 1e-3);
    
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
* Case 3: PAYMENT_ACCOUNT = 0
*
*/


void unittest_Firm_calc_production_quantity_II_3()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	PLANNED_PRODUCTION_QUANTITY = 100.0;
	PAYMENT_ACCOUNT = 0.0;
	ADAPTION_PRODUCTION_VOLUME_DUE_TO_INSUFFICIENT_FINANCES=0.05;
	PLANNED_PRODUCTION_COSTS =100.0;

	MEAN_SPECIFIC_SKILLS=1;
	TECHNOLOGY=1;
	TOTAL_UNITS_CAPITAL_STOCK=100.0;
	MEAN_WAGE = 1;
	
	

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	ACTUAL_CAP_PRICE = 10;

    /***** Function evaluation ***************************************/
	Firm_calc_production_quantity_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_QUANTITY , 0.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_OUTPUT , 0.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS , 0.0, 1e-3);
    
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_calc_input_demands_II()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	MEAN_SPECIFIC_SKILLS=2.0;
	TECHNOLOGY=1.5;
	PLANNED_PRODUCTION_QUANTITY=100.0;
	TOTAL_UNITS_CAPITAL_STOCK=65.0;
	MEAN_WAGE = 1.0;
	TOTAL_CAPITAL_DEPRECIATION_UNITS=5.0;
	ACTUAL_CAP_PRICE=10.0;

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	DEPRECIATION_RATE = 0.05;

	
    /***** Function evaluation ***************************************/	Firm_calc_input_demands_2();
    
    /***** Variables: Memory post-conditions *****/

	CU_ASSERT_DOUBLE_EQUAL(NEEDED_CAPITAL_STOCK, 67.98693, 1e-3);
	CU_ASSERT_EQUAL(EMPLOYEES_NEEDED, 65);
	CU_ASSERT_DOUBLE_EQUAL(DEMAND_CAPITAL_STOCK,2.98693, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS,97.4693, 1e-3);
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_calc_input_demands_II_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	MEAN_SPECIFIC_SKILLS=2.0;
	TECHNOLOGY=1.5;
	PLANNED_PRODUCTION_QUANTITY=100.0;
	TOTAL_UNITS_CAPITAL_STOCK=65.0;
	MEAN_WAGE = 1.0;
	TOTAL_CAPITAL_DEPRECIATION_UNITS=1.0;
	ACTUAL_CAP_PRICE=10.0;

	BETA=0.5;
	ALPHA=0.5;
	CONST_INSTALLMENT_PERIODS=10;
	INV_INERTIA=2;
	DEPRECIATION_RATE = 0.05;

	
    /***** Function evaluation ***************************************/	Firm_calc_input_demands_2();
    
    /***** Variables: Memory post-conditions *****/

	CU_ASSERT_DOUBLE_EQUAL(NEEDED_CAPITAL_STOCK, 66, 1e-3);
	CU_ASSERT_EQUAL(EMPLOYEES_NEEDED, 67);
	CU_ASSERT_DOUBLE_EQUAL(DEMAND_CAPITAL_STOCK,1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS,79.68, 1e-3);
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
*Case 2: sum(PLANNED_DELIVERY_VOLUMES) == PRODUCTION_QUANTITY;
*/
void unittest_Firm_send_goods_to_mall()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

		QUALITY = 1.0;
		PRICE = 1.0;
		PRICE_LAST_MONTH =1.0;
		PRODUCTION_QUANTITY= 30; //15 , 45 , 0

		reset_delivery_volume_per_mall_array(&PLANNED_DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 1, 10, 1, 0);
   		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 2, 20, 1, 0);

		reset_delivery_volume_per_mall_array(&DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&DELIVERY_VOLUME, 1,0 , 0, 0);
   		add_delivery_volume_per_mall(&DELIVERY_VOLUME, 2, 0, 0, 0);

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_update_mall_stock, sizeof(m_update_mall_stock));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'update_mall_stock' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif	    /***** Function evaluation ***************************************/
	  	Firm_send_goods_to_mall();
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_update_mall_stock, &i_update_mall_stock);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: '<message>' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: '<message>' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

  
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(DELIVERY_VOLUME.array[0].quantity,10.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELIVERY_VOLUME.array[1].quantity,20.00, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    START_UPDATE_MALL_STOCK_MESSAGE_LOOP
		if(update_mall_stock_message->mall_id ==1)
	     CU_ASSERT_DOUBLE_EQUAL(update_mall_stock_message->quantity, 10.0, 1e-3);
		if(update_mall_stock_message->mall_id ==2)
			CU_ASSERT_DOUBLE_EQUAL(update_mall_stock_message->quantity, 20.0, 1e-3);
	
	FINISH_UPDATE_MALL_STOCK_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
*Case 2: sum(PLANNED_DELIVERY_VOLUMES) > PRODUCTION_QUANTITY;
*/
void unittest_Firm_send_goods_to_mall_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

		QUALITY = 1.0;
		PRICE = 1.0;
		PRICE_LAST_MONTH =1.0;
		PRODUCTION_QUANTITY= 15.0;

		reset_delivery_volume_per_mall_array(&PLANNED_DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 1, 10, 1, 0);
   		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 2, 20, 1, 0);

		reset_delivery_volume_per_mall_array(&DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&DELIVERY_VOLUME, 1,0 , 0, 0);
   		add_delivery_volume_per_mall(&DELIVERY_VOLUME, 2, 0, 0, 0);

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_update_mall_stock, sizeof(m_update_mall_stock));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'update_mall_stock' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	    /***** Function evaluation ***************************************/
	    	Firm_send_goods_to_mall();   	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_update_mall_stock, &i_update_mall_stock);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: '<message>' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: '<message>' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(DELIVERY_VOLUME.array[0].quantity,5.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELIVERY_VOLUME.array[1].quantity,10.00, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    START_UPDATE_MALL_STOCK_MESSAGE_LOOP
		if(update_mall_stock_message->mall_id ==1)
	     CU_ASSERT_DOUBLE_EQUAL(update_mall_stock_message->quantity, 5.0, 1e-3);
		if(update_mall_stock_message->mall_id ==2)
			CU_ASSERT_DOUBLE_EQUAL(update_mall_stock_message->quantity, 10.0, 1e-3);
	
	FINISH_UPDATE_MALL_STOCK_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
*Case 3: sum(PLANNED_DELIVERY_VOLUMES) < PRODUCTION_QUANTITY;
*/
void unittest_Firm_send_goods_to_mall_3()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

		QUALITY = 1.0;
		PRICE = 1.0;
		PRICE_LAST_MONTH =1.0;
		PRODUCTION_QUANTITY= 45.0;

		reset_delivery_volume_per_mall_array(&PLANNED_DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 1, 10, 1, 0);
   		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 2, 20, 1, 0);

		reset_delivery_volume_per_mall_array(&DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&DELIVERY_VOLUME, 1,0 , 0, 0);
   		add_delivery_volume_per_mall(&DELIVERY_VOLUME, 2, 0, 0, 0);

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_update_mall_stock, sizeof(m_update_mall_stock));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'update_mall_stock' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	    /***** Function evaluation ***************************************/
	    	Firm_send_goods_to_mall();	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_update_mall_stock, &i_update_mall_stock);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: '<message>' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: '<message>' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(DELIVERY_VOLUME.array[0].quantity,15.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELIVERY_VOLUME.array[1].quantity,30.00, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    START_UPDATE_MALL_STOCK_MESSAGE_LOOP
		if(update_mall_stock_message->mall_id ==1)
	     CU_ASSERT_DOUBLE_EQUAL(update_mall_stock_message->quantity, 15.0, 1e-3);
		if(update_mall_stock_message->mall_id ==2)
			CU_ASSERT_DOUBLE_EQUAL(update_mall_stock_message->quantity, 30.0, 1e-3);
	
	FINISH_UPDATE_MALL_STOCK_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
/*
*Case 4: PRODUCTION_QUANTITY = 0;
*/
void unittest_Firm_send_goods_to_mall_4()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

		QUALITY = 1.0;
		PRICE = 1.0;
		PRICE_LAST_MONTH =1.0;
		PRODUCTION_QUANTITY= 0.0;

		reset_delivery_volume_per_mall_array(&PLANNED_DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 1, 10, 1, 0);
   		add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME, 2, 20, 1, 0);

		reset_delivery_volume_per_mall_array(&DELIVERY_VOLUME);
    		add_delivery_volume_per_mall(&DELIVERY_VOLUME, 1,0 , 0, 0);
   		add_delivery_volume_per_mall(&DELIVERY_VOLUME, 2, 0, 0, 0);

   	  /***** Function evaluation ***************************************/
   		Firm_send_goods_to_mall();
   		
	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_update_mall_stock, sizeof(m_update_mall_stock));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'update_mall_stock' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_update_mall_stock, &i_update_mall_stock);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: '<message>' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: '<message>' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

  
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(DELIVERY_VOLUME.array[0].quantity,0.00, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELIVERY_VOLUME.array[1].quantity,0.00, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    START_UPDATE_MALL_STOCK_MESSAGE_LOOP
		if(update_mall_stock_message->mall_id ==1)
	     CU_ASSERT_DOUBLE_EQUAL(update_mall_stock_message->quantity, 0.0, 1e-3);
		if(update_mall_stock_message->mall_id ==2)
			CU_ASSERT_DOUBLE_EQUAL(update_mall_stock_message->quantity, 0.0, 1e-3);
	
	FINISH_UPDATE_MALL_STOCK_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_calc_revenue()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	ID = 10;
	PAYMENT_ACCOUNT = 100.0;
	PRICE = 1.0;
	CUM_REVENUE = 10.0;
	CUM_TOTAL_SOLD_QUANTITY = 10.0;

	reset_sold_quantities_per_mall_array(&SOLD_QUANTITIES);
    	add_sold_quantities_per_mall(&SOLD_QUANTITIES, 1, 10, 1, 0);
   	add_sold_quantities_per_mall(&SOLD_QUANTITIES, 2, 20, 1, 0);

	reset_mall_info_array(&CURRENT_MALL_STOCKS);
    	add_mall_info(&CURRENT_MALL_STOCKS, 1, 10, 10);
   	add_mall_info(&CURRENT_MALL_STOCKS, 2, 20, 20);

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_sales, sizeof(m_sales));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'sales' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
  	 #endif
	/***** Messages: pre-conditions **********************************/
    add_sales_message(1,10,10.0,1,0.0);
    add_sales_message(2,10,5.0,0,15.0);
      
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_sales, &i_sales);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'sales' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'sales' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    /***** Function evaluation ***************************************/
	Firm_calc_revenue();
    
  	CU_ASSERT_DOUBLE_EQUAL(TOTAL_SOLD_QUANTITY, 15.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(REVENUE_PER_DAY, 15.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 115.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CUM_TOTAL_SOLD_QUANTITY, 25.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(SOLD_QUANTITIES.array[0].sold_quantity, 20.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(SOLD_QUANTITIES.array[1].sold_quantity, 25.0, 1e-3);


	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[0].current_stock,0.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[1].current_stock, 15.0, 1e-3);
   
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_compute_sales_statistics()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

		FIRM_PLANNING_HORIZON = 10;

		add_sales_statistics(&MALLS_SALES_STATISTICS,1,0);
		add_sales_statistics(&MALLS_SALES_STATISTICS,2,0);

		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,1,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,2,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,3,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,4,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,5,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,6,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,7,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,8,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,9,50.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[0].sales,10,66.0);

		
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,1,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,2,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,3,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,4,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,5,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,6,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,7,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,8,10.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,9,50.0);
		add_data_type_sales(&MALLS_SALES_STATISTICS.array[1].sales,10,66.0);

		reset_sold_quantities_per_mall_array(&SOLD_QUANTITIES);
    	add_sold_quantities_per_mall(&SOLD_QUANTITIES, 1, 99.0, 1, 0);
   	add_sold_quantities_per_mall(&SOLD_QUANTITIES, 2, 99.0, 1, 0);
	
    /***** Function evaluation ***************************************/
	Firm_compute_sales_statistics();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(MALLS_SALES_STATISTICS.array[0].sales.array[0].sales, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(MALLS_SALES_STATISTICS.array[0].sales.array[8].sales, 50.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(MALLS_SALES_STATISTICS.array[0].sales.array[9].sales, 99.0, 1e-3);
	CU_ASSERT_EQUAL(MALLS_SALES_STATISTICS.array[0].sales.array[9].period, 1);

	CU_ASSERT_DOUBLE_EQUAL(MALLS_SALES_STATISTICS.array[1].sales.array[0].sales, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(MALLS_SALES_STATISTICS.array[1].sales.array[8].sales, 50.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(MALLS_SALES_STATISTICS.array[1].sales.array[9].sales, 99.0, 1e-3);
	CU_ASSERT_EQUAL(MALLS_SALES_STATISTICS.array[1].sales.array[9].period, 1);
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_update_specific_skills_of_worker()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	reset_employee_array(&EMPLOYEES);
    	add_employee(&EMPLOYEES,2,1,1.0,5,1.0);
	add_employee(&EMPLOYEES,3,1,1.0,5,1.0);
	add_employee(&EMPLOYEES,4,1,1.0,5,1.0);
	add_employee(&EMPLOYEES,5,1,1.0,5,1.0);
	

	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_specific_skill_update, sizeof(m_specific_skill_update));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'specific_skill_update' board\n");
    	       switch(rc) {
    	           case MB_ERR_INVALID:
    	               fprintf(stderr, "\t reason: Invalid message size\n");
    	               break;
    	           case MB_ERR_MEMALLOC:
    	               fprintf(stderr, "\t reason: out of memory\n");
    	               break;
    	           case MB_ERR_INTERNAL:
    	               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
    	               break;
    	       }
    	    }
    	    #endif
	
	/***** Messages: pre-conditions **********************************/
    	add_specific_skill_update_message(2,1,1.5);
	add_specific_skill_update_message(3,1,2.0);	
	add_specific_skill_update_message(4,1,2.5);
	add_specific_skill_update_message(5,1,3.5);
 
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_specific_skill_update, &i_specific_skill_update);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'specific_skill_update'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'specific_skill_update' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'specific_skill_update' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}

    /***** Function evaluation ***************************************/
	Firm_update_specific_skills_of_workers();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[0].specific_skill, 1.5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[1].specific_skill, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[2].specific_skill, 2.5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[3].specific_skill, 3.5, 1e-3);
	
 
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
		
