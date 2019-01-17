#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../../header.h"
#include "../../ClearingHouse_agent_header.h"
#include "../../my_library_header.h"

/************ClearingHouse: ********************************/

/************ Unit tests ********************************/
void unittest_Minitest()
{
    printf("\n Testing: ceiling, floor, int\n");
    printf("\n floor(2.3)=%f, (int)floor(2.3)=%d, (int)(2.3)=%d\n", floor(2.3), (int)floor(2.3), (int)(2.3));
    printf("\n ceil(-2.3)=%f, (int)ceil(-2.3)=%d, (int)(-2.3)=%d\n", ceil(-2.3), (int)ceil(-2.3), (int)(-2.3));
    
}


/*
 * \fn: void unittest_ClearingHouse_send_index_info()
 * \brief: Unit test for: ClearingHouse_send_index_info.
 * Case: Test the random number vector. Output of index_info_message->dividend_per_share should be a "random number".
 * Status: Tested;
 * Note: for test, uncomment line 23 (adding the RANDOM_NUMBERS_NORMAL) and comment line 24 in the function ClearingHouse_send_index_info().
 */
void unittest_ClearingHouse_send_index_info()
{
	int rc;
	double value;
	
    /************* At start of unit test, add one agent **************/
    unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    STOCK_INDEX.price=1.0;
    STOCK_INDEX.weight = 0.5;
    STOCK_INDEX.nr_shares = 10;
    STOCK_INDEX.moving_avg_price = 1.0;
    
    MONTHLY_COUNTER_TOTAL_DIVIDEND = 20;
    
    add_double(&RANDOM_NUMBERS_NORMAL, 2.0);
    printf("\n RANDOM_NUMBERS_NORMAL.array[0] = %f\n", RANDOM_NUMBERS_NORMAL.array[0]);
    
    DSRATIO=10.0;
    FLAME_environment_variable_index_price_adj=1;
    FLAME_environment_variable_index_price_adj_max = 1.10;
    FLAME_environment_variable_index_price_adj_min = 0.90;
    FLAME_environment_variable_print_debug_afm=1;
    
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
    	    
    /***** Function evaluation ***************************************/
    ClearingHouse_send_index_info();
    
    /***** Variables: Memory post-conditions *****/
    printf("\n STOCK_INDEX.dividend_per_share = %f\n", STOCK_INDEX.dividend_per_share);
    CU_ASSERT_DOUBLE_EQUAL(STOCK_INDEX.dividend_per_share, 2.0, 1e-3);

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
    /***** Messages: Message post-conditions *****/
    //start a reading loop
    value=0.0;
    
    START_INDEX_INFO_MESSAGE_LOOP
	value = index_info_message->dividend_per_share;
	printf("\n In message loop dividend_per_share = %f price = %f moving_avg_price=%f\n", value, index_info_message->price, index_info_message->moving_avg_price);
    FINISH_INDEX_INFO_MESSAGE_LOOP
    
    printf("\n Outside message loop dividend_per_share = %f\n", value);
    CU_ASSERT_DOUBLE_EQUAL(value, 2.0, 1e-3);
	
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_ClearingHouse_receive_dividend_info()
 * \brief: Unit test for: ClearingHouse_receive_dividend_info.
 * Status: Tested OK
 */
void unittest_ClearingHouse_receive_dividend_info()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/

    //DAY==1:
    iteration_loop = 1;

    STOCK_INDEX.price=1.0;
    STOCK_INDEX.weight = 1.0;
    STOCK_INDEX.nr_shares = 100;
    
    /***** Messages: initialize message boards **********************************/
	rc = MB_Create(&b_dividend_info, sizeof(m_dividend_info));
/*	
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'dividend_info' board\n");
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
*/	
    /***** Messages: pre-conditions **********************************/
    //add_dividend_info_message(firm_id, total_dividend);
    add_dividend_info_message(0, 200);

    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_dividend_info, &i_dividend_info);
/*			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'dividend_info'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'dividend_info' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'dividend_info' board is locked\n");
		               break;
		           case MB_ERR_MEMALLOC:
		               fprintf(stderr, "\t reason: out of memory\n");
		               break;
		           case MB_ERR_INTERNAL:
		               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
		               break;
			   }
			}
*/
    /***** Function evaluation ***************************************/
    ClearingHouse_receive_dividend_info();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_COUNTER_TOTAL_DIVIDEND, 200, 1e-3);

    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_ClearingHouse_receive_orders()
 * \brief: Unit test for: ClearingHouse_receive_orders.
 * Status: NOT Tested
 */
void unittest_ClearingHouse_receive_orders()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    STOCK_INDEX.price=1.0;
    STOCK_INDEX.weight = 0.5;
    STOCK_INDEX.nr_shares = 100;

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
	//add_order_message(ID, monetary_value);
	add_order_message(1, 100);
	add_order_message(2, -100);
    	    
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
    ClearingHouse_receive_orders();
    
    /***** Variables: Memory post-conditions *****/
    //PENDING_ORDERS:
/*    
    PENDING_ORDERS.array[0].trader_id 	= 1
    PENDING_ORDERS.array[0].value	= 100
    PENDING_ORDERS.array[1].trader_id 	= 2
    PENDING_ORDERS.array[1].value	= -100
*/
    CU_ASSERT_DOUBLE_EQUAL(PENDING_ORDERS.array[0].value, 100, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PENDING_ORDERS.array[1].value, -100, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(PENDING_ORDERS.array[0].quantity, 100, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PENDING_ORDERS.array[1].quantity, -100, 1e-3);
    
    /***** Messages: Message post-conditions *****/
	//start a reading loop
/*
    START_ORDER_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(order_message->var, value);
	     CU_ASSERT_DOUBLE_EQUAL(order_message->var, value, 1e-3);
	FINISH_ORDER_MESSAGE_LOOP
*/	
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_ClearingHouse_compute_transactions()
 * \brief: Unit test for: ClearingHouse_compute_transactions.R
 * Case: Demand = 100, Supply =100. Transactions: 100 units. Rationing: none. Price update: none.
 * Status: Tested
 */
void unittest1_ClearingHouse_compute_transactions()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    STOCK_INDEX.price=1.0;
    STOCK_INDEX.weight = 0.5;
    STOCK_INDEX.nr_shares = 100;
    
    DSRATIO=0.0;
/*    
    PENDING_ORDERS.array[0].trader_id 	= 1;
    PENDING_ORDERS.array[0].value	= 100;
    PENDING_ORDERS.array[1].trader_id 	= 2;
    PENDING_ORDERS.array[1].value	= -100;
*/
    add_order(&PENDING_ORDERS, 1, 100,0);
    add_order(&PENDING_ORDERS, 2,-100,0);

    FLAME_environment_variable_print_debug_afm=1;
    FLAME_environment_variable_print_debug_afm_ch=1;
    
    /***** Function evaluation ***************************************/
    ClearingHouse_compute_transactions();
    
    /***** Variables: Memory post-conditions *****/
/*
    PROCESSED_ORDERS.array[0].value	= 100
    PROCESSED_ORDERS.array[1].value	= -100
    DSRATIO	= 1
    STOCK_INDEX.price = 1
*/
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[0].value, 100, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[1].value, -100, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(DSRATIO, 1, 1e-3);
    
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_ClearingHouse_compute_transactions()
 * \brief: Unit test for: ClearingHouse_compute_transactions.
 * Case: Demand = 0, Supply >0. Transactions: none. Rationing: supply. Price update: none.
 * Status: NOT Tested
 */
void unittest2_ClearingHouse_compute_transactions()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    STOCK_INDEX.price=1.0;
    STOCK_INDEX.weight = 0.5;
    STOCK_INDEX.nr_shares = 100;
    
    DSRATIO=0.0;
/*    
    PENDING_ORDERS.array[0].trader_id 	= 1;
    PENDING_ORDERS.array[0].value	= 0;
    PENDING_ORDERS.array[1].trader_id 	= 2;
    PENDING_ORDERS.array[1].value	= -100;
*/
    add_order(&PENDING_ORDERS, 1, 0,0);
    add_order(&PENDING_ORDERS, 2,-100,0);

    FLAME_environment_variable_print_debug_afm=1;
    FLAME_environment_variable_print_debug_afm_ch=1;

    /***** Function evaluation ***************************************/
    ClearingHouse_compute_transactions();
    
    /***** Variables: Memory post-conditions *****/
/*
    PROCESSED_ORDERS.array[0].value	= 100
    PROCESSED_ORDERS.array[1].value	= -100
    DSRATIO	= 1
    STOCK_INDEX.price = 1
*/
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[0].value, 0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[1].value, 0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(DSRATIO, 1, 1e-3);
    
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest3_ClearingHouse_compute_transactions()
 * \brief: Unit test for: ClearingHouse_compute_transactions.
 * Case: Supply = 0, demand >0. Transactions: none. Rationing: demand. Price update: none.
 * Status: Tested
 */
void unittest3_ClearingHouse_compute_transactions()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    STOCK_INDEX.price=1.0;
    STOCK_INDEX.weight = 0.5;
    STOCK_INDEX.nr_shares = 100;
    
    DSRATIO=0.0;
/*    
    PENDING_ORDERS.array[0].trader_id 	= 1;
    PENDING_ORDERS.array[0].value	= 100;
    PENDING_ORDERS.array[1].trader_id 	= 2;
    PENDING_ORDERS.array[1].value	= 0;
*/
    add_order(&PENDING_ORDERS, 1, 100,0);
    add_order(&PENDING_ORDERS, 2, 0,0);

    FLAME_environment_variable_print_debug_afm=1;
    FLAME_environment_variable_print_debug_afm_ch=1;
    
    /***** Function evaluation ***************************************/
    ClearingHouse_compute_transactions();

    /***** Variables: Memory post-conditions *****/
/*
    PROCESSED_ORDERS.array[0].value	= 100
    PROCESSED_ORDERS.array[1].value	= -100
    DSRATIO	= 1
    STOCK_INDEX.price = 1
*/
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[0].value, 0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[1].value, 0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(DSRATIO, 1, 1e-3);
    
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest4_ClearingHouse_compute_transactions()
 * \brief: Unit test for: ClearingHouse_compute_transactions.
 * Case: Demand = 100, Supply = 50. Price=1. Transactions: 50 units. Rationing: demand. Price update: 1.10*1=1.10 (max).
 * Status: NOT Tested
 */
void unittest4_ClearingHouse_compute_transactions()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    STOCK_INDEX.price=1.0;
    STOCK_INDEX.weight = 0.5;
    STOCK_INDEX.nr_shares = 100;
    
    DSRATIO=0.0;
/*    
    PENDING_ORDERS.array[0].trader_id 	= 1;
    PENDING_ORDERS.array[0].value	= 100;
    PENDING_ORDERS.array[1].trader_id 	= 2;
    PENDING_ORDERS.array[1].value	= -50;
*/
    add_order(&PENDING_ORDERS, 1, 100,0);
    add_order(&PENDING_ORDERS, 2,-50,0);

    FLAME_environment_variable_print_debug_afm=1;
    FLAME_environment_variable_print_debug_afm_ch=1;
    
    /***** Function evaluation ***************************************/
    ClearingHouse_compute_transactions();
    
    /***** Variables: Memory post-conditions *****/
/*
    PROCESSED_ORDERS.array[0].value	= 100
    PROCESSED_ORDERS.array[1].value	= -100
    DSRATIO	= 1
    STOCK_INDEX.price = 1
*/
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[0].value, 50, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[1].value, -50, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(DSRATIO, 2, 1e-3);
    
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest5_ClearingHouse_compute_transactions()
 * \brief: Unit test for: ClearingHouse_compute_transactions.
 * Case: Demand = 100, Supply = 200. Price=2. Transactions: 50 units. Rationing: supply. Price update: 0.90*2=1.8 (min).
 * Status: NOT Tested
 */
void unittest5_ClearingHouse_compute_transactions()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    STOCK_INDEX.price=2.0;
    STOCK_INDEX.weight = 0.5;
    STOCK_INDEX.nr_shares = 100;
    
    DSRATIO=0.0;
/*    
    PENDING_ORDERS.array[0].trader_id 	= 1;
    PENDING_ORDERS.array[0].value	= 100;
    PENDING_ORDERS.array[1].trader_id 	= 2;
    PENDING_ORDERS.array[1].value	= -200;
*/
    add_order(&PENDING_ORDERS, 1, 100,0);
    add_order(&PENDING_ORDERS, 2,-200,0);

    FLAME_environment_variable_print_debug_afm=1;
    FLAME_environment_variable_print_debug_afm_ch=1;

    /***** Function evaluation ***************************************/
    ClearingHouse_compute_transactions();
    
    /***** Variables: Memory post-conditions *****/
/*
    PROCESSED_ORDERS.array[0].value	= 100
    PROCESSED_ORDERS.array[1].value	= -100
    DSRATIO	= 1
    STOCK_INDEX.price = 1
*/
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[0].value, 100, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PROCESSED_ORDERS.array[1].value, -100, 1e-3);

    
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_ClearingHouse_send_transaction_info()
 * \brief: Unit test for: ClearingHouse_send_transaction_info.
 * Status: NOT Tested
 */
void unittest_ClearingHouse_send_transaction_info()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	/***** Messages: initialize message boards **********************************/
/*
	rc = MB_Create(&b_<message>, sizeof(m_<message>));
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
*/	
	/***** Messages: pre-conditions **********************************/
    //add_<message>_message();
    	    
    /***** Message: Adding message iterators ***************************************/
	//rc = MB_Iterator_Create(b_<message>, &i_<message>);
/*			
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
*/
    /***** Function evaluation ***************************************/
    ClearingHouse_send_transaction_info();
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
/*
    START_<message>_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(<message>_message->var, value);
	     CU_ASSERT_DOUBLE_EQUAL(<message>_message->var, value, 1e-3);
	FINISH_<message>_MESSAGE_LOOP
*/	
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_ClearingHouse_update_price()
 * \brief: Unit test for: ClearingHouse_update_price.
 * Status: NOT Tested
 */
void unittest_ClearingHouse_update_price()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
    unittest_init_ClearingHouse_agent();
	
    /***** Variables: Memory pre-conditions **************************/
    STOCK_INDEX.price=2.0;
    DSRATIO = 0.5;	//new price to be added: 1.80

    //Set price=[1.0, 2.0]
    add_double(&STOCK_INDEX.price_history,1.0);
    add_double(&STOCK_INDEX.price_history,2.0);

    printf("\n In unittest before: price = [%f %f]\n", STOCK_INDEX.price_history.array[0], STOCK_INDEX.price_history.array[1]);
    
    FLAME_environment_variable_index_price_adj=1;
    FLAME_environment_variable_index_price_adj_max = 1.10;
    FLAME_environment_variable_index_price_adj_min = 0.90;
    FLAME_environment_variable_print_debug_afm=1;
    FLAME_environment_variable_print_debug_afm_ch=1;

/***** Messages: initialize message boards **********************************/

/***** Messages: pre-conditions **********************************/
    	    
    /***** Message: Adding message iterators ***************************************/
	
    /***** Function evaluation ***************************************/
    ClearingHouse_update_price();
    
    /***** Variables: Memory post-conditions *****/
    //Price=[2.0, 1.8]
    printf("\n In unittest after: price = [%f %f]\n", STOCK_INDEX.price_history.array[0], STOCK_INDEX.price_history.array[1]);
    printf("STOCK_INDEX.moving_avg_price = %f\n", STOCK_INDEX.moving_avg_price);
    
    /************* At end of unit test, free the agent **************/
	unittest_free_ClearingHouse_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
