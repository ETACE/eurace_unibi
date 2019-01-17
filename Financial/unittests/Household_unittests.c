#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../../header.h"
#include "../../Household_agent_header.h"
#include "../../my_library_header.h"

/************Household Role: Financial Market ********************************/

/************ Unit tests ********************************/

/*
 * \fn: void unittest_Household_receive_index_info()
 * \brief: Unit test for: Household_receive_index_info.
 * Status: NOT Tested
 */
void unittest_Household_receive_index_info()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    ASSETSOWNED.units=10;
    ASSETSOWNED.moving_avg_price=0.0;
    
	/***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_index_info, sizeof(m_index_info));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'index_info' board\n");
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
    double dividend_per_share=1.0;
    double price=1.0;
    double moving_avg_price=1.0;
    
    add_index_info_message(dividend_per_share, price, moving_avg_price);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_index_info, &i_index_info);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'index_info'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'index_info' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'index_info' board is locked\n");
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
    Household_receive_index_info();
    
    /***** Variables: Memory post-conditions *****/
    
    CU_ASSERT_DOUBLE_EQUAL(RECEIVED_DIVIDEND, 10.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(ASSETSOWNED.lastprice, price, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(ASSETSOWNED.moving_avg_price, moving_avg_price, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest1_Household_revises_expected_portfolio()
 * \brief: Unit test for: Household_revises_expected_portfolio.
 * Status: NOT Tested
 */
void unittest1_Household_revises_expected_portfolio()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    //Set beliefs
    /*
    BELIEFS.expected_dividend
    BELIEFS.expected_price
    BELIEFS.expected_return
    BELIEFS.expected_volatility
    BELIEFS.last_price
    */
    
    //Case 1: sell, and can
    //portfolio_budget = PAYMENT_ACCOUNT + ASSETSOWNED.lastprice*ASSETSOWNED.units - CONSUMPTION_BUDGET;
    
    //PAYMENT_ACCOUNT     = 100;
    //ASSETSOWNED.units	  = 100;
    //CONSUMPTION_BUDGET  = 190; 
    //portfolio value 	  = 100
    //portfolio_budget	  = 10
    //net_investment	  = -90
    //limit sales 	  = 100
    //net_investment	  = -90
    RISK_FREE_RATE        = 0.01;
    PAYMENT_ACCOUNT       = 100;
    ASSETSOWNED.lastprice = 1.0;
    ASSETSOWNED.units	  = 100;
    CONSUMPTION_BUDGET    = 190; 
    
    /***** Messages: initialize message boards **********************************/
	rc = MB_Create(&b_order, sizeof(m_order));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'order' board\n");
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
    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_order, &i_order);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'order'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'order' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'order' board is locked\n");
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
	Household_revises_expected_portfolio();
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    START_ORDER_MESSAGE_LOOP
	printf("order_message->value = %f", order_message->value);
	CU_ASSERT_DOUBLE_EQUAL(order_message->value, -90.0, 1e-3);
    FINISH_ORDER_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest2_Household_revises_expected_portfolio()
 * \brief: Unit test for: Household_revises_expected_portfolio.
 * Status: NOT Tested
 */
void unittest2_Household_revises_expected_portfolio()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    //Set beliefs
    /*
    BELIEFS.expected_dividend
    BELIEFS.expected_price
    BELIEFS.expected_return
    BELIEFS.expected_volatility
    BELIEFS.last_price
    */
    
    //portfolio_budget = PAYMENT_ACCOUNT + ASSETSOWNED.lastprice*ASSETSOWNED.units - CONSUMPTION_BUDGET;

    //Case 2: sell, but cannot
    //ASSETSOWNED.units   =  0;
    //CONSUMPTION_BUDGET  = 190; 

    //portfolio_budget= -90
    //portfolio_value = 0
    //net_investment= -90
    //limit sales = 0
    //net_investment= 0
    RISK_FREE_RATE        = 0.01;
    PAYMENT_ACCOUNT       = 100;
    ASSETSOWNED.lastprice = 1.0;
    ASSETSOWNED.units	  = 0;
    CONSUMPTION_BUDGET    = 190; 

    /***** Messages: initialize message boards **********************************/
	rc = MB_Create(&b_order, sizeof(m_order));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'order' board\n");
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
    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_order, &i_order);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'order'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'order' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'order' board is locked\n");
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
	Household_revises_expected_portfolio();
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    START_ORDER_MESSAGE_LOOP
	printf("order_message->value = %f", order_message->value);
	CU_ASSERT_DOUBLE_EQUAL(order_message->value, 0.0, 1e-3);
    FINISH_ORDER_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest3_Household_revises_expected_portfolio()
 * \brief: Unit test for: Household_revises_expected_portfolio.
 * Status: NOT Tested
 */
void unittest3_Household_revises_expected_portfolio()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    //Set beliefs
    /*
    BELIEFS.expected_dividend
    BELIEFS.expected_price
    BELIEFS.expected_return
    BELIEFS.expected_volatility
    BELIEFS.last_price
    */
    
    //portfolio_budget = PAYMENT_ACCOUNT + ASSETSOWNED.lastprice*ASSETSOWNED.units - CONSUMPTION_BUDGET;

    //Case 3: buy, and can
    //PAYMENT_ACCOUNT       = 100;
    //ASSETSOWNED.lastprice = 1.0;
    //ASSETSOWNED.units	  = 100;
    //CONSUMPTION_BUDGET  = 50; 
    //portfolio_budget    = 150
    //portfolio_value     = 100
    //net_investment      = +50
    //limit sales         =   0
    //net_investment      = +50
    RISK_FREE_RATE        = 0.01;
    PAYMENT_ACCOUNT       = 100;
    ASSETSOWNED.lastprice = 1.0;
    ASSETSOWNED.units	  = 100;
    CONSUMPTION_BUDGET    = 50; 
    
    /***** Messages: initialize message boards **********************************/
	rc = MB_Create(&b_order, sizeof(m_order));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'order' board\n");
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
    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_order, &i_order);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'order'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'order' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'order' board is locked\n");
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
	Household_revises_expected_portfolio();
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    START_ORDER_MESSAGE_LOOP
	printf("order_message->value = %f", order_message->value);
	CU_ASSERT_DOUBLE_EQUAL(order_message->value, 50.0, 1e-3);
    FINISH_ORDER_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Household_update_portfolio()
 * \brief: Unit test for: Household_update_portfolio.
 * Status: NOT Tested
 */
void unittest_Household_update_portfolio()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    ASSETSOWNED.units=0;
    PAYMENT_ACCOUNT = 10.0;
    HOUSEHOLD_INFLOWS_CALENDAR.asset_sales=0.0;
    HOUSEHOLD_OUTFLOWS_CALENDAR.asset_purchases=0.0;
    
    /***** Messages: initialize message boards **********************************/

	rc = MB_Create(&b_order_status, sizeof(m_order_status));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'order_status' board\n");
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
    //add_order_status_message(trader_id, value, quantity);
    add_order_status_message(1, 7.0, 2);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_order_status, &i_order_status);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'order_status'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'order_status' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'order_status' board is locked\n");
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
	Household_update_portfolio();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 3.0, 1e-3);
    CU_ASSERT_EQUAL(ASSETSOWNED.units, 2);
    CU_ASSERT_DOUBLE_EQUAL(HOUSEHOLD_OUTFLOWS_CALENDAR.asset_purchases, 7.0, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest1_logit_decision_model()
 * \brief: Unit test for: logit_decision_model.
 * Status: Tested
 * Case: LOGIT_BETA=60 (=inf), performance[0]=0.01, performance[0]=1.0
 * Result: BELIEFS.fraction_to_invest=1.0 (100% to risky asset)
 * LOGIT_BETA max value: 700
 */
void unittest1_logit_decision_model()
{
	int rc;
    /************* At start of unit test, add one agent **************/
    unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    LOGIT_BETA = 60.0;
    BELIEFS.expected_return = 0.0;
    BELIEFS.fraction_to_invest = 0.0;
    RISK_FREE_RATE=0.01;
    ASSETSOWNED.moving_avg_price=1.0;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
    	    
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    logit_decision_model();

    /***** Variables: Memory post-conditions *****/
    printf("\n proportion = %f \t RISK_FREE_RATE = %f\t BELIEFS.expected_return=%f\n", BELIEFS.fraction_to_invest, RISK_FREE_RATE, BELIEFS.expected_return);
     
    //CU_ASSERT_DOUBLE_EQUAL(memvar, value, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_logit_decision_model()
 * \brief: Unit test for: logit_decision_model.
 * Status: Tested
 * Case: LOGIT_BETA=0 (=inf), performance[0]=0.01, performance[0]=1.0
 * Result: BELIEFS.fraction_to_invest=0.50 (random choice)
 * LOGIT_BETA max value: 700
 */
void unittest2_logit_decision_model()
{
	int rc;
    /************* At start of unit test, add one agent **************/
    unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    LOGIT_BETA = 0.0;
    BELIEFS.expected_return = 0.0;
    BELIEFS.fraction_to_invest = 0.0;
    RISK_FREE_RATE=0.01;
    ASSETSOWNED.moving_avg_price=1.0;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
    	    
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    logit_decision_model();

    /***** Variables: Memory post-conditions *****/
    printf("\n BELIEFS.fraction_to_invest = %f \t RISK_FREE_RATE = %f\t BELIEFS.expected_return=%f\n", BELIEFS.fraction_to_invest, RISK_FREE_RATE, BELIEFS.expected_return);
     
    //CU_ASSERT_DOUBLE_EQUAL(memvar, value, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
