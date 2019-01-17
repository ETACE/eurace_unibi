#include <CUnit/Basic.h>
//For trunk model
#include "../../header.h"
#include "../../Household_agent_header.h"
#include "../../my_library_header.h"
#include "../Mall_aux_header.h"

/*
 * Case 1 : PAYMENT_ACCOUNT > INITIAL_CONS_PROP*MEAN_INCOME
 * 
 * */
	void unittest_Household_determine_consumption_budget()
	{
		int rc;
		
	    /************* At start of unit test, add one agent **************/
		unittest_init_Household_agent();
		
	    /***** Variables: Memory pre-conditions **************************/

		PAYMENT_ACCOUNT = 100;
		INITIAL_CONSUMPTION_PROPENSITY = 0.95;
		CONSUMPTION_PROPENSITY = 0.95;
		MEAN_INCOME = 80;
	
	    /***** Function evaluation ***************************************/
		Household_determine_consumption_budget();
	    
	    /***** Variables: Memory post-conditions *****/
		CU_ASSERT_DOUBLE_EQUAL(CONSUMPTION_BUDGET, 98.8, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(WEEKLY_BUDGET, 24.7, 1e-3);
		CU_ASSERT_EQUAL(WEEK_OF_MONTH, 4);
	    
	    /************* At end of unit test, free the agent **************/
		unittest_free_Household_agent();
	    /************* At end of unit tests, free all Messages **********/
	    free_messages();
	}
	
	/*
	 * Case 2 : PAYMENT_ACCOUNT < INITIAL_CONS_PROP*MEAN_INCOME
	 * 
	 * */
	void unittest_Household_determine_consumption_budget_2()
		{
			int rc;
			
		    /************* At start of unit test, add one agent **************/
			unittest_init_Household_agent();
			
		    /***** Variables: Memory pre-conditions **************************/

			PAYMENT_ACCOUNT = 75;
			INITIAL_CONSUMPTION_PROPENSITY = 0.95;
			CONSUMPTION_PROPENSITY = 0.95;
			MEAN_INCOME = 80;
		
		    /***** Function evaluation ***************************************/
			Household_determine_consumption_budget();
		    
		    /***** Variables: Memory post-conditions *****/
			CU_ASSERT_DOUBLE_EQUAL(CONSUMPTION_BUDGET, 75, 1e-3);
			CU_ASSERT_DOUBLE_EQUAL(WEEKLY_BUDGET, 18.75, 1e-3);
			CU_ASSERT_EQUAL(WEEK_OF_MONTH, 4);
		
		    /************* At end of unit test, free the agent **************/
			unittest_free_Household_agent();
		    /************* At end of unit tests, free all Messages **********/
		    free_messages();
		}
	
	
	void unittest_Household_rank_and_buy_goods_1()
	{
		int rc;
		
	    /************* At start of unit test, add one agent **************/
		unittest_init_Household_agent();
		
	    /***** Variables: Memory pre-conditions **************************/
		
		GAMMA_CONST = -1;
		WEEKLY_BUDGET = 100;
		ID = 1;
		REGION_ID = 1;
		

		
    	ORDER_QUANTITY[0].firm_id = 0;
    	ORDER_QUANTITY[0].quantity = 0;
    	ORDER_QUANTITY[0].price = 0;
    	
    	ORDER_QUANTITY[1].firm_id = 0;
    	ORDER_QUANTITY[1].quantity = 0;
    	ORDER_QUANTITY[1].price = 0;
    	

		/***** Messages: initialize message boards **********************************/
	
		rc = MB_Create(&b_quality_price_info_1, sizeof(m_quality_price_info_1));
	    	    #ifdef ERRCHECK
	    	    if (rc != MB_SUCCESS)
	    	    {
	    	       fprintf(stderr, "ERROR: Could not create 'quality_price_info_1' board\n");
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
	    	    
    	    rc = MB_Create(&b_consumption_request_1, sizeof(m_consumption_request_1));
    	    	    	    #ifdef ERRCHECK
    	    	    	    if (rc != MB_SUCCESS)
    	    	    	    {
    	    	    	       fprintf(stderr, "ERROR: Could not create 'consumption_request_1' board\n");
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
	   add_quality_price_info_1_message(1,1,2,1.0,1.0,1);
	   add_quality_price_info_1_message(1,1,3,1.0,2.0,1);
	   
	    	    
	    /***** Message: Adding message iterators ***************************************/
		rc = MB_Iterator_Create(b_quality_price_info_1, &i_quality_price_info_1);
				
		if (rc != MB_SUCCESS)
				{
				   fprintf(stderr, "ERROR: Could not create Iterator for 'quality_price_info_1'\n");
				   switch(rc) {
				       case MB_ERR_INVALID:
				           fprintf(stderr, "\t reason: 'quality_price_info_1' board is invalid\n");
				           break;
				       case MB_ERR_LOCKED:
			               fprintf(stderr, "\t reason: 'quality_price_info_1' board is locked\n");
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
				Household_rank_and_buy_goods_1();
		
		rc = MB_Iterator_Create(b_consumption_request_1, &i_consumption_request_1);
						
				if (rc != MB_SUCCESS)
						{
						   fprintf(stderr, "ERROR: Could not create Iterator for 'consumption_request_1'\n");
						   switch(rc) {
						       case MB_ERR_INVALID:
						           fprintf(stderr, "\t reason: 'consumption_request_1' board is invalid\n");
						           break;
						       case MB_ERR_LOCKED:
					               fprintf(stderr, "\t reason: 'consumption_request_1' board is locked\n");
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
	if(ORDER_QUANTITY[0].firm_id ==2)
	{
		printf("Random number <66");
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[0].quantity, 100.0, 1e-3);	
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[0].price, 1.0, 1e-3);
		
		START_CONSUMPTION_REQUEST_1_MESSAGE_LOOP
	
		     CU_ASSERT_EQUAL(consumption_request_1_message->worker_id, ID);	
			 CU_ASSERT_EQUAL(consumption_request_1_message->mall_id, 1);
			 CU_ASSERT_EQUAL(consumption_request_1_message->region_id, 1);
			 CU_ASSERT_EQUAL(consumption_request_1_message->firm_id, 2);
		     CU_ASSERT_DOUBLE_EQUAL(consumption_request_1_message->quantity, 100.0, 1e-3);
		FINISH_CONSUMPTION_REQUEST_1_MESSAGE_LOOP
		
		
		
	}else
	{
		printf("Random number >66");
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[0].quantity, 50.0, 1e-3);	
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[0].price, 2.0, 1e-3);
		
		START_CONSUMPTION_REQUEST_1_MESSAGE_LOOP
			     CU_ASSERT_EQUAL(consumption_request_1_message->worker_id, ID);	
				 CU_ASSERT_EQUAL(consumption_request_1_message->mall_id, 1);
				 CU_ASSERT_EQUAL(consumption_request_1_message->region_id, 1);
				 CU_ASSERT_EQUAL(consumption_request_1_message->firm_id, 3);
			     CU_ASSERT_DOUBLE_EQUAL(consumption_request_1_message->quantity, 50.0, 1e-3);
	    FINISH_CONSUMPTION_REQUEST_1_MESSAGE_LOOP
	}
		
	    /************* At end of unit test, free the agent **************/
		unittest_free_Household_agent();
	    /************* At end of unit tests, free all Messages **********/
	    free_messages();
	}
	
	
	void unittest_Household_rank_and_buy_goods_1_2()
		{
			int rc;
			
		    /************* At start of unit test, add one agent **************/
			unittest_init_Household_agent();
			
		    /***** Variables: Memory pre-conditions **************************/
			
			GAMMA_CONST = -1;
			WEEKLY_BUDGET = 100;
			ID = 1;
			REGION_ID = 1;
			
			EXPENDITURES = 1;
			MALL_COMPLETELY_SOLD_OUT=0;
			
			

			
	    	ORDER_QUANTITY[0].firm_id = 1;
	    	ORDER_QUANTITY[0].quantity = 1;
	    	ORDER_QUANTITY[0].price = 1;
	    	
	    	ORDER_QUANTITY[1].firm_id = 0;
	    	ORDER_QUANTITY[1].quantity = 0;
	    	ORDER_QUANTITY[1].price = 0;
	    	

			/***** Messages: initialize message boards **********************************/
		
			rc = MB_Create(&b_quality_price_info_1, sizeof(m_quality_price_info_1));
		    	    #ifdef ERRCHECK
		    	    if (rc != MB_SUCCESS)
		    	    {
		    	       fprintf(stderr, "ERROR: Could not create 'quality_price_info_1' board\n");
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
		   add_quality_price_info_1_message(1,1,2,1.0,1.0,0);
		   add_quality_price_info_1_message(1,1,3,1.0,2.0,0);
		   
		    	    
		    /***** Message: Adding message iterators ***************************************/
			rc = MB_Iterator_Create(b_quality_price_info_1, &i_quality_price_info_1);
					
			if (rc != MB_SUCCESS)
					{
					   fprintf(stderr, "ERROR: Could not create Iterator for 'quality_price_info_1'\n");
					   switch(rc) {
					       case MB_ERR_INVALID:
					           fprintf(stderr, "\t reason: 'quality_price_info_1' board is invalid\n");
					           break;
					       case MB_ERR_LOCKED:
				               fprintf(stderr, "\t reason: 'quality_price_info_1' board is locked\n");
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
			Household_rank_and_buy_goods_1();
		    
		    /***** Variables: Memory post-conditions *****/
		
			CU_ASSERT_DOUBLE_EQUAL(EXPENDITURES,0, 1e-3);	
			CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[0].price, 0.0, 1e-3);
			CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[0].quantity, 0.0, 1e-3);
			CU_ASSERT_EQUAL(ORDER_QUANTITY[0].firm_id, 0);
			CU_ASSERT_EQUAL(MALL_COMPLETELY_SOLD_OUT, 1);
			
		    /************* At end of unit test, free the agent **************/
			unittest_free_Household_agent();
		    /************* At end of unit tests, free all Messages **********/
		    free_messages();
		}

void unittest_Household_receive_goods_read_rationing()
	{
		int rc;
		
	    /************* At start of unit test, add one agent **************/
		unittest_init_Household_agent();
		
	    /***** Variables: Memory pre-conditions **************************/
		
			WEEKLY_BUDGET =100.0; 
		
			ORDER_QUANTITY[0].firm_id = 1;
	    	ORDER_QUANTITY[0].quantity = 50;
	    	ORDER_QUANTITY[0].price = 2.0;
	    	
	    	ORDER_QUANTITY[1].firm_id = 0;
	    	ORDER_QUANTITY[1].quantity = 0;
	    	ORDER_QUANTITY[1].price = 0;

		/***** Messages: initialize message boards **********************************/
	
		rc = MB_Create(&b_accepted_consumption_1, sizeof(m_accepted_consumption_1));
	    	    #ifdef ERRCHECK
	    	    if (rc != MB_SUCCESS)
	    	    {
	    	       fprintf(stderr, "ERROR: Could not create 'accepted_consumption_1' board\n");
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
	    add_accepted_consumption_1_message(2,1,50,0);
	    	    
	    /***** Message: Adding message iterators ***************************************/
		rc = MB_Iterator_Create(b_accepted_consumption_1, &i_accepted_consumption_1);
				
		if (rc != MB_SUCCESS)
				{
				   fprintf(stderr, "ERROR: Could not create Iterator for 'accepted_consumption_1'\n");
				   switch(rc) {
				       case MB_ERR_INVALID:
				           fprintf(stderr, "\t reason: 'accepted_consumption_1' board is invalid\n");
				           break;
				       case MB_ERR_LOCKED:
			               fprintf(stderr, "\t reason: 'accepted_consumption_1' board is locked\n");
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
		Household_receive_goods_read_rationing();
	    
	    /***** Variables: Memory post-conditions *****/
		CU_ASSERT_EQUAL(RATIONED, 0);
		CU_ASSERT_DOUBLE_EQUAL(WEEKLY_BUDGET, 0.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(RECEIVED_QUANTITY[0].quantity, 50.0, 1e-3);
		CU_ASSERT_EQUAL(RECEIVED_QUANTITY[0].firm_id,1 );
		CU_ASSERT_DOUBLE_EQUAL(EXPENDITURES, 100.0, 1e-3);
	  
	    /************* At end of unit test, free the agent **************/
		unittest_free_Household_agent();
	    /************* At end of unit tests, free all Messages **********/
	    free_messages();
}	

void unittest_Household_receive_goods_read_rationing_2()
	{
		int rc;
		
	    /************* At start of unit test, add one agent **************/
		unittest_init_Household_agent();
		
	    /***** Variables: Memory pre-conditions **************************/
		
			WEEKLY_BUDGET =100.0; 
		
			ORDER_QUANTITY[0].firm_id = 1;
	    	ORDER_QUANTITY[0].quantity = 50;
	    	ORDER_QUANTITY[0].price = 2.0;
	    	
	    	ORDER_QUANTITY[1].firm_id = 0;
	    	ORDER_QUANTITY[1].quantity = 0;
	    	ORDER_QUANTITY[1].price = 0;

		/***** Messages: initialize message boards **********************************/
	
		rc = MB_Create(&b_accepted_consumption_1, sizeof(m_accepted_consumption_1));
	    	    #ifdef ERRCHECK
	    	    if (rc != MB_SUCCESS)
	    	    {
	    	       fprintf(stderr, "ERROR: Could not create 'accepted_consumption_1' board\n");
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
	    add_accepted_consumption_1_message(2,1,30,1);
	    	    
	    /***** Message: Adding message iterators ***************************************/
		rc = MB_Iterator_Create(b_accepted_consumption_1, &i_accepted_consumption_1);
				
		if (rc != MB_SUCCESS)
				{
				   fprintf(stderr, "ERROR: Could not create Iterator for 'accepted_consumption_1'\n");
				   switch(rc) {
				       case MB_ERR_INVALID:
				           fprintf(stderr, "\t reason: 'accepted_consumption_1' board is invalid\n");
				           break;
				       case MB_ERR_LOCKED:
			               fprintf(stderr, "\t reason: 'accepted_consumption_1' board is locked\n");
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
		Household_receive_goods_read_rationing();
	    
	    /***** Variables: Memory post-conditions *****/
		CU_ASSERT_EQUAL(RATIONED, 1);
		CU_ASSERT_DOUBLE_EQUAL(WEEKLY_BUDGET, 40.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(RECEIVED_QUANTITY[0].quantity, 30.0, 1e-3);
		CU_ASSERT_EQUAL(RECEIVED_QUANTITY[0].firm_id,1 );
		CU_ASSERT_DOUBLE_EQUAL(EXPENDITURES, 60.0, 1e-3);
	  
	    /************* At end of unit test, free the agent **************/
		unittest_free_Household_agent();
	    /************* At end of unit tests, free all Messages **********/
	    free_messages();
}

void unittest_Household_receive_goods_read_rationing_3()
	{
		int rc;
		
	    /************* At start of unit test, add one agent **************/
		unittest_init_Household_agent();
		
	    /***** Variables: Memory pre-conditions **************************/
		
			MALL_COMPLETELY_SOLD_OUT = 1;
		
			ORDER_QUANTITY[0].firm_id = 1;
	    	ORDER_QUANTITY[0].quantity = 50;
	    	ORDER_QUANTITY[0].price = 2.0;
	    	
	    	ORDER_QUANTITY[1].firm_id = 1;
	    	ORDER_QUANTITY[1].quantity = 1;
	    	ORDER_QUANTITY[1].price = 1;

	    	    
	
	    /***** Function evaluation ***************************************/
		Household_receive_goods_read_rationing();	
		
		
	    /***** Variables: Memory post-conditions *****/
		CU_ASSERT_EQUAL(ORDER_QUANTITY[1].firm_id, 0);
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[1].price, 0.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[1].quantity, 0.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(RECEIVED_QUANTITY[0].quantity, 0.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(RECEIVED_QUANTITY[1].quantity, 0.0, 1e-3);
		CU_ASSERT_EQUAL(RECEIVED_QUANTITY[0].firm_id,0 );
		CU_ASSERT_EQUAL(RECEIVED_QUANTITY[1].firm_id,0);
		
	  
	    /************* At end of unit test, free the agent **************/
		unittest_free_Household_agent();
	    /************* At end of unit tests, free all Messages **********/
	    free_messages();
}

void unittest_Household_rank_and_buy_goods_2()
	{
		int rc;
		
	    /************* At start of unit test, add one agent **************/
		unittest_init_Household_agent();
		
	    /***** Variables: Memory pre-conditions **************************/
		
		GAMMA_CONST = -1;
		WEEKLY_BUDGET = 100;
		ID = 1;
		REGION_ID = 1;
		

		
    	ORDER_QUANTITY[0].firm_id = 0;
    	ORDER_QUANTITY[0].quantity = 0;
    	ORDER_QUANTITY[0].price = 0;
    	
    	ORDER_QUANTITY[1].firm_id = 0;
    	ORDER_QUANTITY[1].quantity = 0;
    	ORDER_QUANTITY[1].price = 0;
    	

		/***** Messages: initialize message boards **********************************/
	
		rc = MB_Create(&b_quality_price_info_2, sizeof(m_quality_price_info_2));
	    	    #ifdef ERRCHECK
	    	    if (rc != MB_SUCCESS)
	    	    {
	    	       fprintf(stderr, "ERROR: Could not create 'quality_price_info_2' board\n");
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
	    	    
    	    rc = MB_Create(&b_consumption_request_2, sizeof(m_consumption_request_2));
    	    	    	    #ifdef ERRCHECK
    	    	    	    if (rc != MB_SUCCESS)
    	    	    	    {
    	    	    	       fprintf(stderr, "ERROR: Could not create 'consumption_request_2' board\n");
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
	   add_quality_price_info_2_message(1,1,2,1.0,1.0,1);
	   add_quality_price_info_2_message(1,1,3,1.0,2.0,1);
	   
	    	    
	    /***** Message: Adding message iterators ***************************************/
		rc = MB_Iterator_Create(b_quality_price_info_2, &i_quality_price_info_2);
				
		if (rc != MB_SUCCESS)
				{
				   fprintf(stderr, "ERROR: Could not create Iterator for 'quality_price_info_1'\n");
				   switch(rc) {
				       case MB_ERR_INVALID:
				           fprintf(stderr, "\t reason: 'quality_price_info_2' board is invalid\n");
				           break;
				       case MB_ERR_LOCKED:
			               fprintf(stderr, "\t reason: 'quality_price_info_2' board is locked\n");
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
				Household_rank_and_buy_goods_2();
		
		rc = MB_Iterator_Create(b_consumption_request_2, &i_consumption_request_2);
						
				if (rc != MB_SUCCESS)
						{
						   fprintf(stderr, "ERROR: Could not create Iterator for 'consumption_request_2'\n");
						   switch(rc) {
						       case MB_ERR_INVALID:
						           fprintf(stderr, "\t reason: 'consumption_request_2' board is invalid\n");
						           break;
						       case MB_ERR_LOCKED:
					               fprintf(stderr, "\t reason: 'consumption_request_2' board is locked\n");
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
	if(ORDER_QUANTITY[1].firm_id ==2)
	{
		printf("Random number <66");
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[1].quantity, 100.0, 1e-3);	
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[1].price, 1.0, 1e-3);
		
		START_CONSUMPTION_REQUEST_2_MESSAGE_LOOP
		
		     CU_ASSERT_EQUAL(consumption_request_2_message->worker_id, ID);	
			 CU_ASSERT_EQUAL(consumption_request_2_message->mall_id, 1);
			 CU_ASSERT_EQUAL(consumption_request_2_message->region_id, 1);
			 CU_ASSERT_EQUAL(consumption_request_2_message->firm_id, 2);
		     CU_ASSERT_DOUBLE_EQUAL(consumption_request_2_message->quantity, 100.0, 1e-3);
		FINISH_CONSUMPTION_REQUEST_2_MESSAGE_LOOP
		
		
		
	}else
	{
		printf("Random number >66");
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[1].quantity, 50.0, 1e-3);	
		CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[1].price, 2.0, 1e-3);
		
		START_CONSUMPTION_REQUEST_2_MESSAGE_LOOP
			     CU_ASSERT_EQUAL(consumption_request_2_message->worker_id, ID);	
				 CU_ASSERT_EQUAL(consumption_request_2_message->mall_id, 1);
				 CU_ASSERT_EQUAL(consumption_request_2_message->region_id, 1);
				 CU_ASSERT_EQUAL(consumption_request_2_message->firm_id, 3);
			     CU_ASSERT_DOUBLE_EQUAL(consumption_request_2_message->quantity, 50.0, 1e-3);
	    FINISH_CONSUMPTION_REQUEST_2_MESSAGE_LOOP
	}
		
	    /************* At end of unit test, free the agent **************/
		unittest_free_Household_agent();
	    /************* At end of unit tests, free all Messages **********/
	    free_messages();
	}

void unittest_Household_rank_and_buy_goods_2_2()
		{
			int rc;
			
		    /************* At start of unit test, add one agent **************/
			unittest_init_Household_agent();
			
		    /***** Variables: Memory pre-conditions **************************/
			
			GAMMA_CONST = -1;
			WEEKLY_BUDGET = 100;
			ID = 1;
			REGION_ID = 1;
			
			EXPENDITURES = 1;
			MALL_COMPLETELY_SOLD_OUT=0;
			
			

			
	    	ORDER_QUANTITY[0].firm_id = 1;
	    	ORDER_QUANTITY[0].quantity = 1;
	    	ORDER_QUANTITY[0].price = 1;
	    	
	    	ORDER_QUANTITY[1].firm_id = 1;
	    	ORDER_QUANTITY[1].quantity = 1;
	    	ORDER_QUANTITY[1].price = 1;
	    	

			/***** Messages: initialize message boards **********************************/
		
			rc = MB_Create(&b_quality_price_info_1, sizeof(m_quality_price_info_1));
		    	    #ifdef ERRCHECK
		    	    if (rc != MB_SUCCESS)
		    	    {
		    	       fprintf(stderr, "ERROR: Could not create 'quality_price_info_1' board\n");
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
		   add_quality_price_info_2_message(1,1,2,1.0,1.0,0);
		   add_quality_price_info_2_message(1,1,3,1.0,2.0,0);
		   
		    	    
		    /***** Message: Adding message iterators ***************************************/
			rc = MB_Iterator_Create(b_quality_price_info_2, &i_quality_price_info_2);
					
			if (rc != MB_SUCCESS)
					{
					   fprintf(stderr, "ERROR: Could not create Iterator for 'quality_price_info_2'\n");
					   switch(rc) {
					       case MB_ERR_INVALID:
					           fprintf(stderr, "\t reason: 'quality_price_info_2' board is invalid\n");
					           break;
					       case MB_ERR_LOCKED:
				               fprintf(stderr, "\t reason: 'quality_price_info_2' board is locked\n");
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
			Household_rank_and_buy_goods_2();
		    
		    /***** Variables: Memory post-conditions *****/
		
			CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[1].price, 0.0, 1e-3);
			CU_ASSERT_DOUBLE_EQUAL(ORDER_QUANTITY[1].quantity, 0.0, 1e-3);
			CU_ASSERT_EQUAL(ORDER_QUANTITY[1].firm_id, 0);
		
			
		    /************* At end of unit test, free the agent **************/
			unittest_free_Household_agent();
		    /************* At end of unit tests, free all Messages **********/
		    free_messages();
		}

void unittest_Household_receive_goods_read_rationing_II()
	{
		int rc;
		
	    /************* At start of unit test, add one agent **************/
		unittest_init_Household_agent();
		
	    /***** Variables: Memory pre-conditions **************************/
		
			RATIONED = 1;
			WEEKLY_BUDGET =100.0;
			EXPENDITURES = 100;
		
			ORDER_QUANTITY[0].firm_id = 1;
	    	ORDER_QUANTITY[0].quantity = 50;
	    	ORDER_QUANTITY[0].price = 2.0;
	    	
	    	ORDER_QUANTITY[1].firm_id = 1;
	    	ORDER_QUANTITY[1].quantity = 50.0;
	    	ORDER_QUANTITY[1].price = 2.0;
	  
		    

	    	RECEIVED_QUANTITY[0].firm_id=1;
	    	RECEIVED_QUANTITY[0].quantity= 1;
	    	RECEIVED_QUANTITY[1].firm_id=99;
	    	RECEIVED_QUANTITY[1].quantity= 99;
	    	
			/***** Messages: initialize message boards **********************************/
		
			rc = MB_Create(&b_accepted_consumption_2, sizeof(m_accepted_consumption_2));
		    	    #ifdef ERRCHECK
		    	    if (rc != MB_SUCCESS)
		    	    {
		    	       fprintf(stderr, "ERROR: Could not create 'accepted_consumption_2' board\n");
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
		    add_accepted_consumption_2_message(2,1,50,0);
		    	    
		    /***** Message: Adding message iterators ***************************************/
			rc = MB_Iterator_Create(b_accepted_consumption_2, &i_accepted_consumption_2);
					
			if (rc != MB_SUCCESS)
					{
					   fprintf(stderr, "ERROR: Could not create Iterator for 'accepted_consumption_2'\n");
					   switch(rc) {
					       case MB_ERR_INVALID:
					           fprintf(stderr, "\t reason: 'accepted_consumption_2' board is invalid\n");
					           break;
					       case MB_ERR_LOCKED:
				               fprintf(stderr, "\t reason: 'accepted_consumption_2' board is locked\n");
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
		Household_receive_goods_read_rationing_2();	
	    
	    /***** Variables: Memory post-conditions *****/
	
		CU_ASSERT_EQUAL(RATIONED,0);
		CU_ASSERT_DOUBLE_EQUAL(RECEIVED_QUANTITY[1].quantity, 50.0, 1e-3);
		CU_ASSERT_EQUAL(RECEIVED_QUANTITY[1].firm_id,1 );
		CU_ASSERT_DOUBLE_EQUAL(WEEKLY_BUDGET, 0.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EXPENDITURES, 200.0, 1e-3);

		
	  
	    /************* At end of unit test, free the agent **************/
		unittest_free_Household_agent();
	    /************* At end of unit tests, free all Messages **********/
	    free_messages();
}


void unittest_Household_handle_leftover_budget()
{
	int rc;
	
   /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
	/***** Variables: Memory pre-conditions **************************/

	ID = 1;
	BANK_ID= 1000;
	CONSUMPTION_BUDGET = 100;
	EXPENDITURES = 50;
	WEEK_OF_MONTH = 3;
	PAYMENT_ACCOUNT = 120;
	SWITCH_FLOW_CONSISTENCY_CHECK =0;
	
	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_bank_account_update, sizeof(m_bank_account_update));
   	    #ifdef ERRCHECK
   	    if (rc != MB_SUCCESS)
   	    {
   	       fprintf(stderr, "ERROR: Could not create 'bank_account_update' board\n");
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
   	 	Household_handle_leftover_budget();	
   /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_bank_account_update, &i_bank_account_update);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'bank_account_update'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'bank_account_update' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'bank_account_update' board is locked\n");
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
	CU_ASSERT_DOUBLE_EQUAL(CONSUMPTION_BUDGET, 50.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT,70.0 , 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WEEKLY_BUDGET, 25.0, 1e-3);
	CU_ASSERT_EQUAL(WEEK_OF_MONTH,2);
	
   /***** Messages: Message post-conditions *****/
	//start a reading loop

   START_BANK_ACCOUNT_UPDATE_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(bank_account_update_message->id, ID);
   		 CU_ASSERT_EQUAL(bank_account_update_message->bank_id, BANK_ID);	
	   CU_ASSERT_DOUBLE_EQUAL(bank_account_update_message->payment_account, 70.0 , 1e-3);
	FINISH_BANK_ACCOUNT_UPDATE_MESSAGE_LOOP
	
   /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
   /************* At end of unit tests, free all Messages **********/
   free_messages();
}
