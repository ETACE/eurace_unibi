#include <CUnit/Basic.h>

#include "../../header.h"
#include "../../Firm_agent_header.h"
#include "../../my_library_header.h"

/************Firm Role: Financial Management Role ********************************/

/************ Unit tests ********************************/
/*
 * \fn: void unittest_Firm_compute_income_statement()
 * \brief: Unit tests for: Firm_compute_income_statement
 */
void unittest_Firm_compute_income_statement()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	current_xmachine = *p_xmachine;
	
    /***** Variables: Memory pre-conditions **************************/
	DAY_OF_MONTH_TO_ACT=0;
	CUM_REVENUE=100.0;
    EBIT=0.0;
    PAYMENT_ACCOUNT=0.0;
    
	/***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Firm_compute_income_statement();
    
    /***** Variables: Memory post-conditions *****/

    CU_ASSERT_DOUBLE_EQUAL(CUM_REVENUE, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EBIT, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 100.0, 1e-3);

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Firm_compute_balance_sheet()
 * \brief: Unit tests for: Firm_compute_balance_sheet
 */
void unittest_Firm_compute_balance_sheet()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	current_xmachine = *p_xmachine;
	
    /***** Variables: Memory pre-conditions **************************/
	DAY_OF_MONTH_TO_ACT=0;
    CURRENT_SHARES_OUTSTANDING=100;
    PREVIOUS_DIVIDEND_PER_SHARE=1.0;
    CURRENT_DIVIDEND_PER_SHARE=1.0;
    TOTAL_DIVIDEND_PAYMENT=100.0;
    PLANNED_TOTAL_DIVIDEND_PAYMENT=100*85.5/100;
    
    EBIT=100.0;
    PAYMENT_ACCOUNT=100.0;
    EARNINGS=0.0;
    TAX_PAYMENT=0.0;
    TAX_RATE_CORPORATE=0.10;
    NET_EARNINGS=0.0;
    PREVIOUS_NET_EARNINGS=90.0;

    /*
    LOANS[0].bank_id =1;
    LOANS[0].loan_value=100.0;
    LOANS[0].interest_rate=0.01;
    LOANS[0].interest_payment=0.0;
    LOANS[0].debt_installment_payment=20.0;
    LOANS[0].nr_periods_before_maturity=5;

    LOANS[1].bank_id=2;
    LOANS[1].loan_value=200.0;
    LOANS[1].interest_rate=0.02;
    LOANS[1].interest_payment=0.0;
    LOANS[1].debt_installment_payment=50.0;
    LOANS[1].nr_periods_before_maturity=4;
*/
    reset_debt_item_array(&LOANS);
    add_debt_item(&LOANS, 1, 100.0, 0.01, 0.0, 20.0, 5);
    add_debt_item(&LOANS, 2, 200.0, 0.02, 0.0, 50.0, 4);

    TOTAL_INTEREST_PAYMENT=0.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT=0.0;

    PLANNED_TOTAL_INTEREST_PAYMENT=5.0;
    PLANNED_TOTAL_DEBT_INSTALLMENT_PAYMENT=70.0;
    
    PRICE=1.0;
    add_mall_info(&CURRENT_MALL_STOCKS, 1, 1.0, 1000.0);
    TOTAL_VALUE_LOCAL_INVENTORY=0.0;
    TOTAL_VALUE_CAPITAL_STOCK=1000.0;
    PAYMENT_ACCOUNT=100.0;
    TOTAL_ASSETS=0.0;
    
	/***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Firm_compute_balance_sheet();

    /***** Variables: Memory post-conditions *************************/
    CU_ASSERT_DOUBLE_EQUAL(EBIT, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EARNINGS, 95.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TAX_PAYMENT, 9.5, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TAX_RATE_CORPORATE, 0.10, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(NET_EARNINGS, 85.5, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PREVIOUS_NET_EARNINGS, 0.0, 1e-3);

/*
    loans[0]
    {
        int bank_id=1;
        double loan_value=80.0;
        double interest_rate=0.01;
        double interest_payment=1.0; //this value is updated the next time, at start of function to: interest_payment=0.8;
        double debt_installment_payment=20.0;
        int nr_periods_before_maturity=4;
    }
*/

    CU_ASSERT_EQUAL(LOANS.array[0].bank_id, 1);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].loan_value, 80.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].interest_rate, 0.01, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].interest_payment, 1.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].debt_installment_payment, 20.0, 1e-3);
    CU_ASSERT_EQUAL(LOANS.array[0].nr_periods_before_maturity, 4);
   
/*
    loans[1]
    {
        int bank_id=2;
        double loan_value=150.0;
        double interest_rate=0.02;
        double interest_payment=4.0; //this value is updated the next time, at start of function to: interest_payment=0.75;
        double debt_installment_payment=50.0;
        int nr_periods_before_maturity=3;
    }
*/

    CU_ASSERT_EQUAL(LOANS.array[1].bank_id, 2);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].loan_value, 150.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].interest_rate, 0.02, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].interest_payment, 4.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].debt_installment_payment, 50.0, 1e-3);
    CU_ASSERT_EQUAL(LOANS.array[1].nr_periods_before_maturity, 3);
    
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_INTEREST_PAYMENT, 5.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_DEBT_INSTALLMENT_PAYMENT, 70.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_DIVIDEND_PAYMENT, 100*85.5/100, 1e-3);
    CU_ASSERT_EQUAL(CURRENT_SHARES_OUTSTANDING, 100);
    CU_ASSERT_DOUBLE_EQUAL(PREVIOUS_DIVIDEND_PER_SHARE, 1.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(CURRENT_DIVIDEND_PER_SHARE, TOTAL_DIVIDEND_PAYMENT/CURRENT_SHARES_OUTSTANDING, 1e-3);

    /*
    current_mall_stocks[0]
    {
    	mall_id=1;
        price=1.0;
        critical_stock=50;
        current_stock=1000;
    }*/

    CU_ASSERT_DOUBLE_EQUAL(CURRENT_MALL_STOCKS.array[0].current_stock, 1000.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_LOCAL_INVENTORY, 1000.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, -60.5, 1e-3); //payment_account=100+100-10-5-70-5=110;
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_ASSETS, 1939.5, 1e-3); //TOTAL_VALUE_CAPITAL_STOCK=1000.0

    /***** Messages: post-conditions **********************************/
    /*
    tax_payment_message(firm_id, gov_id, tax_payment, MSGDATA)
    interest_payment_message(firm_id, bank_id, interest_payment, MSGDATA)
    debt_installment_payment_message(firm_id, bank_id, debt_installment_payment, MSGDATA)
    dividend_payment_message(firm_id, current_dividend_per_share, MSGDATA)
    */
    
 	START_TAX_PAYMENT_MESSAGE_LOOP
    	CU_ASSERT_DOUBLE_EQUAL(tax_payment_message->tax_payment, 9.5, 1e-3);
	FINISH_TAX_PAYMENT_MESSAGE_LOOP
	
 	START_INTEREST_PAYMENT_MESSAGE_LOOP
		if(interest_payment_message->bank_id==1)
		{
		 	CU_ASSERT_DOUBLE_EQUAL(interest_payment_message->interest_payment, 4.0, 1e-3);
		}
		if(interest_payment_message->bank_id==2)
		{
		 	CU_ASSERT_DOUBLE_EQUAL(interest_payment_message->interest_payment, 1.0, 1e-3);
		}
    FINISH_INTEREST_PAYMENT_MESSAGE_LOOP
    
    START_DEBT_INSTALLMENT_PAYMENT_MESSAGE_LOOP
    	if(debt_installment_payment_message->bank_id==1)
    	{
    		CU_ASSERT_DOUBLE_EQUAL(debt_installment_payment_message->debt_installment_payment, 20.0, 1e-3);
    	}
    	if(debt_installment_payment_message->bank_id==2)
    	{
    		CU_ASSERT_DOUBLE_EQUAL(debt_installment_payment_message->debt_installment_payment, 50.0, 1e-3);
    	}
    FINISH_DEBT_INSTALLMENT_PAYMENT_MESSAGE_LOOP
    
    START_DIVIDEND_PAYMENT_MESSAGE_LOOP
    	CU_ASSERT_DOUBLE_EQUAL(dividend_payment_message->current_dividend_per_share, 85.5/100, 1e-3);
    FINISH_DIVIDEND_PAYMENT_MESSAGE_LOOP

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_Firm_bankruptcy_procedure()
 * \brief: Unit test for: Firm_bankruptcy_procedure.
 * Status: NOT Tested
 */
void unittest1_Firm_bankruptcy_procedure()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	WRITE_OFF_RATIO = 1/3;
	TARGET_LEVERAGE_RATIO = 1.25;
	TOTAL_ASSETS = 120.0;
	TOTAL_DEBT = 150.0;
	PAYMENT_ACCOUNT = 120.0;
	IPO_AMOUNT =0.0;
	
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
/*
	rc = MB_Iterator_Create(b_<message>, &i_<message>);
			
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
	Firm_bankruptcy_procedure();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(IPO_AMOUNT, 24.0, 1e-3);

	
    /***** Messages: Message post-conditions *****/
	//start a reading loop
/*
	START_BANKRUPTCY_MESSAGE_LOOP
	     //CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->credit_refunded, value);
	     //CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->bad_debt, value, 1e-3);
	FINISH_BANKRUPTCY_MESSAGE_LOOP
*/	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Firm_bankruptcy_procedure()
 * \brief: Unit test for: Firm_bankruptcy_procedure.
 * Status: NOT Tested
 */
void unittest2_Firm_bankruptcy_procedure()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	WRITE_OFF_RATIO = 1/3;
	TARGET_LEVERAGE_RATIO = 2.0;
	TOTAL_ASSETS = 120.0;
	TOTAL_DEBT = 150.0;
	PAYMENT_ACCOUNT = 120.0;
	IPO_AMOUNT =0.0;
	
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
/*
	rc = MB_Iterator_Create(b_<message>, &i_<message>);
			
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
	Firm_bankruptcy_procedure();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(IPO_AMOUNT, 0.0, 1e-3);

	
    /***** Messages: Message post-conditions *****/
	//start a reading loop
/*
	START_BANKRUPTCY_MESSAGE_LOOP
	     //CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->credit_refunded, value);
	     //CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->bad_debt, value, 1e-3);
	FINISH_BANKRUPTCY_MESSAGE_LOOP
*/	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest3_Firm_bankruptcy_procedure()
 * \brief: Unit test for: Firm_bankruptcy_procedure.
 * Status: NOT Tested
 */
void unittest3_Firm_bankruptcy_procedure()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	WRITE_OFF_RATIO = 1/3;
	TARGET_LEVERAGE_RATIO = 4.0;
	TOTAL_ASSETS = 120.0;
	TOTAL_DEBT = 150.0;
	PAYMENT_ACCOUNT = 120.0;
	IPO_AMOUNT =0.0;
	
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
/*
	rc = MB_Iterator_Create(b_<message>, &i_<message>);
			
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
	Firm_bankruptcy_procedure();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(IPO_AMOUNT, 0.0, 1e-3);

	
    /***** Messages: Message post-conditions *****/
	//start a reading loop
/*
	START_BANKRUPTCY_MESSAGE_LOOP
	     //CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->credit_refunded, value);
	     //CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->bad_debt, value, 1e-3);
	FINISH_BANKRUPTCY_MESSAGE_LOOP
*/	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Firm_compute_payout_policy()
 * \brief: Unit tests for: Firm_compute_payout_policy
 */
void unittest_Firm_compute_payout_policy()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	current_xmachine = *p_xmachine;

    /***** Variables: Memory pre-conditions **************************/
	DAY_OF_MONTH_TO_ACT=0;
    CURRENT_SHARE_PRICE=1.0;
    PLANNED_PRODUCTION_COSTS=100.0;
    PAYMENT_ACCOUNT=0.0;
    
    NET_EARNINGS=100.0;
    PREVIOUS_NET_EARNINGS=90.0;
    EARNINGS_PER_SHARE_RATIO=100.0;
    
/*
    LOANS[0].bank_id=1;
    LOANS[0].loan_value=100.0;
    LOANS[0].interest_rate=0.01;
    LOANS[0].interest_payment=0.0;
    LOANS[0].debt_installment_payment=20.0;
    LOANS[0].nr_periods_before_maturity=5;

    LOANS[1].bank_id=2;
    LOANS[1].loan_value=200.0;
    LOANS[1].interest_rate=0.02;
    LOANS[1].interest_payment=0.0;
    LOANS[1].debt_installment_payment=50.0;
    LOANS[1].nr_periods_before_maturity=4;
*/
    reset_debt_item_array(&LOANS);
    add_debt_item(&LOANS, 1, 100.0, 0.01, 0.0, 20.0, 5);
    add_debt_item(&LOANS, 2, 200.0, 0.02, 0.0, 50.0, 4);
//    printf("\n init loan_value: %f\n", LOANS.array[0].loan_value);
//    printf("\n init loan_value: %f\n", LOANS.array[1].loan_value);
    
    PLANNED_TOTAL_INTEREST_PAYMENT=0.0;
    PLANNED_TOTAL_DEBT_INSTALLMENT_PAYMENT=0.0;
    PLANNED_TOTAL_DIVIDEND_PAYMENT=100.0;
    CURRENT_SHARES_OUTSTANDING=5;

    TOTAL_FINANCIAL_NEEDS=0.0;
    INTERNAL_FINANCIAL_NEEDS=0.0;
    EXTERNAL_FINANCIAL_NEEDS=0.0;

	/***** Messages: pre-conditions **********************************/

    /***** Function evaluation ***************************************/
     Firm_compute_payout_policy();

    /***** Variables: Memory post-conditions *************************/
    
    CU_ASSERT_DOUBLE_EQUAL(CURRENT_SHARE_PRICE, 1.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_PRODUCTION_COSTS, 100.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(NET_EARNINGS, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PREVIOUS_NET_EARNINGS, 90.0, 1e-3);

    /*
        loans[0]
        {
            int bank_id=1;
            double loan_value=80.0;
            double interest_rate=0.01;
            double interest_payment=1.0; //this value is updated the next time, at start of function to: interest_payment=0.8;
            double debt_installment_payment=20.0;
            int nr_periods_before_maturity=4;
        }
    */

        CU_ASSERT_EQUAL(LOANS.array[0].bank_id, 1);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].loan_value, 100.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].interest_rate, 0.01, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].interest_payment, 1.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].debt_installment_payment, 20.0, 1e-3);
        CU_ASSERT_EQUAL(LOANS.array[0].nr_periods_before_maturity, 5);
       
    /*
        loans[1]
        {
            int bank_id=2;
            double loan_value=150.0;
            double interest_rate=0.02;
            double interest_payment=4.0; //this value is updated the next time, at start of function to: interest_payment=0.75;
            double debt_installment_payment=50.0;
            int nr_periods_before_maturity=3;
        }
    */

        CU_ASSERT_EQUAL(LOANS.array[1].bank_id, 2);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].loan_value, 200.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].interest_rate, 0.02, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].interest_payment, 4.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].debt_installment_payment, 50.0, 1e-3);
        CU_ASSERT_EQUAL(LOANS.array[1].nr_periods_before_maturity, 4);
        
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_TOTAL_INTEREST_PAYMENT, 5.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_TOTAL_DEBT_INSTALLMENT_PAYMENT, 70.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_TOTAL_DIVIDEND_PAYMENT, 100.0*EARNINGS_PER_SHARE_RATIO, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 0.0, 1e-3);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * UNIT TEST 1: No external financing needed:
 * payment_account >= direct_financial_needs + delayed_financial_needs
 */ 
void unittest1_Firm_compute_payout_policy()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	current_xmachine = *p_xmachine;
	
    /***** Variables: Memory pre-conditions **************************/
	ID=1;
	BANK_ID=2;
	EARNINGS_PER_SHARE_RATIO=0.0; //This sets the PLANNED_TOTAL_DIVIDEND_PAYMENT=0
	
	DIRECT_FINANCIAL_NEEDS=0.0;
	DELAYED_FINANCIAL_NEEDS=0.0;
	
	TOTAL_FINANCIAL_NEEDS=0.0;
	EXTERNAL_FINANCIAL_NEEDS=0.0;
	INTERNAL_FINANCIAL_NEEDS=0.0;
   	DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;
    DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;

	//PLANNED_CUM_REVENUE=0.0;
	//PLANNED_CUM_REVENUE = PRICE*PLANNED_PRODUCTION_QUANTITY;
	PRICE=1.0;
	PLANNED_PRODUCTION_QUANTITY=0.0;
	
	PAYMENT_ACCOUNT=30.0;
	//DIRECT_FINANCIAL_NEEDS=10.0:
	PLANNED_PRODUCTION_COSTS=10.0;
	
	//DELAYED_FINANCIAL_NEEDS=20.0:
	/*
	    LOANS[0].bank_id=2;
	    LOANS[0].loan_value=100.0;
	    LOANS[0].interest_rate=0.0;
	    LOANS[0].interest_payment=0.0;
	    LOANS[0].debt_installment_payment=20.0;
	    LOANS[0].nr_periods_before_maturity=5;
	*/
	    reset_debt_item_array(&LOANS);
	    add_debt_item(&LOANS, 2, 100.0, 0.00, 0.0, 20.0, 5);
	
	/***** Messages: pre-conditions **********************************/
	
    /***** Function evaluation ***************************************/
	Firm_compute_payout_policy();
    
    /***** Variables: Memory post-conditions *************************/
	CU_ASSERT_DOUBLE_EQUAL(DIRECT_FINANCIAL_NEEDS, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELAYED_FINANCIAL_NEEDS, 20.0, 1e-3);
	
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_FINANCIAL_NEEDS, 30.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(INTERNAL_FINANCIAL_NEEDS, 30.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_CUM_REVENUE, 0.0, 1e-3);
    
    CU_ASSERT_EQUAL(DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,0);
    CU_ASSERT_EQUAL(DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,0);

    //    printf("TOTAL_FINANCIAL_NEEDS: %f", TOTAL_FINANCIAL_NEEDS);
    //    printf("DIRECT_FINANCIAL_NEEDS: %f", DIRECT_FINANCIAL_NEEDS);
    //    printf("DELAYED_FINANCIAL_NEEDS: %f", DELAYED_FINANCIAL_NEEDS);
    //    printf("EXTERNAL_FINANCIAL_NEEDS: %f", EXTERNAL_FINANCIAL_NEEDS);
    //    printf("INTERNAL_FINANCIAL_NEEDS: %f", INTERNAL_FINANCIAL_NEEDS);
   
    /***** Messages: post-conditions **********************************/

	/************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * UNIT TEST 2: No external financing needed:
 * payment_account >= direct_financial_needs
 * AND payment_account - direct_financial_needs + planned_cum_revenues >= delayed_financial_needs
 * AND payment_account < direct_financial_needs + delayed_financial_needs
 */ 
void unittest2_Firm_compute_payout_policy()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	current_xmachine = *p_xmachine;
	
    /***** Variables: Memory pre-conditions **************************/
	ID=1;
	BANK_ID=2;
	EARNINGS_PER_SHARE_RATIO=0.0; //This sets the PLANNED_TOTAL_DIVIDEND_PAYMENT=0
	
	DIRECT_FINANCIAL_NEEDS=0.0;
	DELAYED_FINANCIAL_NEEDS=0.0;

	TOTAL_FINANCIAL_NEEDS=0.0;
	EXTERNAL_FINANCIAL_NEEDS=0.0;
	INTERNAL_FINANCIAL_NEEDS=0.0;
   	DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;
    DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;

	//PLANNED_CUM_REVENUE=15.0;
	//PLANNED_CUM_REVENUE = PRICE*PLANNED_PRODUCTION_QUANTITY;
	PRICE=1.0;
	PLANNED_PRODUCTION_QUANTITY=15.0;
	
	PAYMENT_ACCOUNT=15.0;
	//DIRECT_FINANCIAL_NEEDS=10.0:
	PLANNED_PRODUCTION_COSTS=10.0;
	
	//DELAYED_FINANCIAL_NEEDS=20.0:    
	/*
	    LOANS[0].bank_id=2;
	    LOANS[0].loan_value=100.0;
	    LOANS[0].interest_rate=0.0;
	    LOANS[0].interest_payment=0.0;
	    LOANS[0].debt_installment_payment=20.0;
	    LOANS[0].nr_periods_before_maturity=5;
	*/
	    reset_debt_item_array(&LOANS);
	    add_debt_item(&LOANS, 2, 100.0, 0.00, 0.0, 20.0, 5);

	/***** Messages: pre-conditions **********************************/
	
    /***** Function evaluation ***************************************/
	Firm_compute_payout_policy();
    
    /***** Variables: Memory post-conditions *************************/
	CU_ASSERT_DOUBLE_EQUAL(DIRECT_FINANCIAL_NEEDS, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELAYED_FINANCIAL_NEEDS, 20.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(TOTAL_FINANCIAL_NEEDS, 30.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(INTERNAL_FINANCIAL_NEEDS, 30.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_CUM_REVENUE, 15.0, 1e-3);
    CU_ASSERT_EQUAL(DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,0);
    CU_ASSERT_EQUAL(DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,0);

    //    printf("TOTAL_FINANCIAL_NEEDS: %f", TOTAL_FINANCIAL_NEEDS);
    //    printf("DIRECT_FINANCIAL_NEEDS: %f", DIRECT_FINANCIAL_NEEDS);
    //    printf("DELAYED_FINANCIAL_NEEDS: %f", DELAYED_FINANCIAL_NEEDS);
    //    printf("EXTERNAL_FINANCIAL_NEEDS: %f", EXTERNAL_FINANCIAL_NEEDS);
    //    printf("INTERNAL_FINANCIAL_NEEDS: %f", INTERNAL_FINANCIAL_NEEDS);
    
    /***** Messages: post-conditions **********************************/

	/************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * UNIT TEST 3: External financing needed for direct payments, not for delayed payments:
 * payment_account < direct_financial_needs AND
 * payment_account - direct_financial_needs + planned_cum_revenues >= delayed_financial_needs
 */ 
void unittest3_Firm_compute_payout_policy()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	current_xmachine = *p_xmachine;
	
    /***** Variables: Memory pre-conditions **************************/
	ID=1;
	BANK_ID=2;
	EARNINGS_PER_SHARE_RATIO=0.0; //This sets the PLANNED_TOTAL_DIVIDEND_PAYMENT=0
	
	DIRECT_FINANCIAL_NEEDS=0.0;
	DELAYED_FINANCIAL_NEEDS=0.0;

	TOTAL_FINANCIAL_NEEDS=0.0;
	EXTERNAL_FINANCIAL_NEEDS=0.0;
	INTERNAL_FINANCIAL_NEEDS=0.0;
   	DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;
    DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;

	//PLANNED_CUM_REVENUE=20.0;
	//PLANNED_CUM_REVENUE = PRICE*PLANNED_PRODUCTION_QUANTITY;
	PRICE=1.0;
	PLANNED_PRODUCTION_QUANTITY=20.0;
	
	PAYMENT_ACCOUNT=5.0;
	//DIRECT_FINANCIAL_NEEDS=10.0:
	PLANNED_PRODUCTION_COSTS=10.0;
	
	//DELAYED_FINANCIAL_NEEDS=15.0:
	/*
	    LOANS[0].bank_id=2;
	    LOANS[0].loan_value=100.0;
	    LOANS[0].interest_rate=0.0;
	    LOANS[0].interest_payment=0.0;
	    LOANS[0].debt_installment_payment=15.0;
	    LOANS[0].nr_periods_before_maturity=5;
	*/
	    reset_debt_item_array(&LOANS);
	    add_debt_item(&LOANS, 2, 100.0, 0.00, 0.0, 15.0, 5);

	/***** Messages: pre-conditions **********************************/
	
    /***** Function evaluation ***************************************/
	Firm_compute_payout_policy();
    
    /***** Variables: Memory post-conditions *************************/
	CU_ASSERT_DOUBLE_EQUAL(DIRECT_FINANCIAL_NEEDS, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELAYED_FINANCIAL_NEEDS, 15.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(TOTAL_FINANCIAL_NEEDS, 25.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(INTERNAL_FINANCIAL_NEEDS, 5.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 5.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_CUM_REVENUE, 20.0, 1e-3);
    CU_ASSERT_EQUAL(DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,1);
    CU_ASSERT_EQUAL(DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,0);

    //    printf("TOTAL_FINANCIAL_NEEDS: %f", TOTAL_FINANCIAL_NEEDS);
    //    printf("DIRECT_FINANCIAL_NEEDS: %f", DIRECT_FINANCIAL_NEEDS);
    //    printf("DELAYED_FINANCIAL_NEEDS: %f", DELAYED_FINANCIAL_NEEDS);
    //    printf("EXTERNAL_FINANCIAL_NEEDS: %f", EXTERNAL_FINANCIAL_NEEDS);
    //    printf("INTERNAL_FINANCIAL_NEEDS: %f", INTERNAL_FINANCIAL_NEEDS);
    
    /***** Messages: post-conditions **********************************/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * UNIT TEST 4: External financing needed for delayed payments, not for direct payments:
 * payment_account >= direct_financial_needs AND
 * payment_account - direct_financial_needs + planned_cum_revenues < delayed_financial_needs
 */ 
void unittest4_Firm_compute_payout_policy()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	current_xmachine = *p_xmachine;
	
    /***** Variables: Memory pre-conditions **************************/
	ID=1;
	BANK_ID=2;
	EARNINGS_PER_SHARE_RATIO=0.0; //This sets the PLANNED_TOTAL_DIVIDEND_PAYMENT=0
	
	DIRECT_FINANCIAL_NEEDS=0.0;
	DELAYED_FINANCIAL_NEEDS=0.0;

	TOTAL_FINANCIAL_NEEDS=0.0;
	EXTERNAL_FINANCIAL_NEEDS=0.0;
	INTERNAL_FINANCIAL_NEEDS=0.0;
   	DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;
    DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;

	//PLANNED_CUM_REVENUE=0.0;
	//PLANNED_CUM_REVENUE = PRICE*PLANNED_PRODUCTION_QUANTITY;
	PRICE=1.0;
	PLANNED_PRODUCTION_QUANTITY=0.0;
	
	PAYMENT_ACCOUNT=10.0;
	//DIRECT_FINANCIAL_NEEDS=10.0:
	PLANNED_PRODUCTION_COSTS=10.0;
	
	//DELAYED_FINANCIAL_NEEDS=20.0:
	/*
	    LOANS[0].bank_id=2;
	    LOANS[0].loan_value=100.0;
	    LOANS[0].interest_rate=0.00;
	    LOANS[0].interest_payment=0.0;
	    LOANS[0].debt_installment_payment=20.0;
	    LOANS[0].nr_periods_before_maturity=5;
	*/
	    reset_debt_item_array(&LOANS);
	    add_debt_item(&LOANS, 2, 100.0, 0.00, 0.0, 20.0, 5);

	/***** Messages: pre-conditions **********************************/
	
    /***** Function evaluation ***************************************/
	Firm_compute_payout_policy();
    
    /***** Variables: Memory post-conditions *************************/
	CU_ASSERT_DOUBLE_EQUAL(DIRECT_FINANCIAL_NEEDS, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELAYED_FINANCIAL_NEEDS, 20.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(TOTAL_FINANCIAL_NEEDS, 30.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(INTERNAL_FINANCIAL_NEEDS, 10.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 20.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_CUM_REVENUE, 0.0, 1e-3);
    CU_ASSERT_EQUAL(DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,0);
    CU_ASSERT_EQUAL(DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,1);

    //    printf("TOTAL_FINANCIAL_NEEDS: %f", TOTAL_FINANCIAL_NEEDS);
    //    printf("DIRECT_FINANCIAL_NEEDS: %f", DIRECT_FINANCIAL_NEEDS);
    //    printf("DELAYED_FINANCIAL_NEEDS: %f", DELAYED_FINANCIAL_NEEDS);
    //    printf("EXTERNAL_FINANCIAL_NEEDS: %f", EXTERNAL_FINANCIAL_NEEDS);
    //    printf("INTERNAL_FINANCIAL_NEEDS: %f", INTERNAL_FINANCIAL_NEEDS);

    /***** Messages: post-conditions **********************************/

	/************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * UNIT TEST 5: External financing is needed to pay for both the direct and delayed payments:
 * payment_account < direct_financial_needs AND
 * payment_account - direct_financial_needs + planned_cum_revenues < delayed_financial_needs
 */ 
void unittest5_Firm_compute_payout_policy()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	current_xmachine = *p_xmachine;
	
    /***** Variables: Memory pre-conditions **************************/
	ID=1;
	BANK_ID=2;
	EARNINGS_PER_SHARE_RATIO=0.0; //This sets the PLANNED_TOTAL_DIVIDEND_PAYMENT=0
	
	DIRECT_FINANCIAL_NEEDS=0.0;
	DELAYED_FINANCIAL_NEEDS=0.0;

	TOTAL_FINANCIAL_NEEDS=0.0;
	EXTERNAL_FINANCIAL_NEEDS=0.0;
	INTERNAL_FINANCIAL_NEEDS=0.0;
   	DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;
    DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING=-1;

	//PLANNED_CUM_REVENUE=24.0;
	//PLANNED_CUM_REVENUE = PRICE*PLANNED_PRODUCTION_QUANTITY;
	PRICE=1.0;
	PLANNED_PRODUCTION_QUANTITY=24.0;
	
	PAYMENT_ACCOUNT=5.0;
	//DIRECT_FINANCIAL_NEEDS=10.0:
	PLANNED_PRODUCTION_COSTS=10.0;
	
	//DELAYED_FINANCIAL_NEEDS=20.0:
	/*
	    LOANS[0].bank_id=2;
	    LOANS[0].loan_value=100.0;
	    LOANS[0].interest_rate=0.0;
	    LOANS[0].interest_payment=0.0;
	    LOANS[0].debt_installment_payment=20.0;
	    LOANS[0].nr_periods_before_maturity=5;
	*/
	    reset_debt_item_array(&LOANS);
	    add_debt_item(&LOANS, 2, 100.0, 0.00, 0.0, 20.0, 5);

	/***** Messages: pre-conditions **********************************/
	
    /***** Function evaluation ***************************************/
	Firm_compute_payout_policy();
    
    /***** Variables: Memory post-conditions *************************/
	CU_ASSERT_DOUBLE_EQUAL(DIRECT_FINANCIAL_NEEDS, 10.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DELAYED_FINANCIAL_NEEDS, 20.0, 1e-3);

    CU_ASSERT_DOUBLE_EQUAL(TOTAL_FINANCIAL_NEEDS, 30.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(INTERNAL_FINANCIAL_NEEDS, 5.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 1.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PLANNED_CUM_REVENUE, 24.0, 1e-3);
    CU_ASSERT_EQUAL(DIRECT_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,1);
    CU_ASSERT_EQUAL(DELAYED_FINANCIAL_NEEDS_REQUIRE_EXTERNAL_FINANCING,1);

    //    printf("TOTAL_FINANCIAL_NEEDS: %f", TOTAL_FINANCIAL_NEEDS);
    //    printf("DIRECT_FINANCIAL_NEEDS: %f", DIRECT_FINANCIAL_NEEDS);
    //    printf("DELAYED_FINANCIAL_NEEDS: %f", DELAYED_FINANCIAL_NEEDS);
    //    printf("EXTERNAL_FINANCIAL_NEEDS: %f", EXTERNAL_FINANCIAL_NEEDS);
    //    printf("INTERNAL_FINANCIAL_NEEDS: %f", INTERNAL_FINANCIAL_NEEDS);
    
    /***** Messages: post-conditions **********************************/

	/************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_compute_and_send_stock_orders()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();

	/***** Variables: Memory pre-conditions **************************/
	ID=1;
    
	/***** Messages: pre-conditions **********************************/
	
    /***** Function evaluation ***************************************/
	Firm_compute_and_send_stock_orders();
    
    /***** Variables: Memory post-conditions *************************/

    /***** Messages: post-conditions *********************************/
 	START_STOCK_ORDER_MESSAGE_LOOP 
 		//add_stock_message(ID, stock_id, limit_price, limit_quantity, MSGDATA);
 		CU_ASSERT_EQUAL(stock_order_message->trader_id, 1);
 		CU_ASSERT_EQUAL(stock_order_message->stock_id, 2);
 		CU_ASSERT_DOUBLE_EQUAL(stock_order_message->limit_price, 1.0, 1e-3);
 		CU_ASSERT_DOUBLE_EQUAL(stock_order_message->limit_quantity, 1.0, 1e-3);
	FINISH_STOCK_ORDER_MESSAGE_LOOP

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

void unittest_Firm_read_stock_transactions()
{
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();

	
	/***** Variables: Memory pre-conditions **************************/
    
	/***** Messages: pre-conditions **********************************/
	
    /***** Function evaluation ***************************************/
	Firm_read_stock_transactions();
    
    /***** Variables: Memory post-conditions *************************/

	/***** Messages: post-conditions *********************************/
	
    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


//	void unittest_<function_name>()
//	{
//	    /************* At start of unit test, add one agent **************/
//		unittest_init_<Agent_name>_agent();
//
//		/***** Variables: Memory pre-conditions **************************/
//		<var_name1>=0.0;
//		<var_name2>=0;
//
//      /***** Messages: pre-conditions **********************************/
//		add_<message_name>_message(<msg_var>, MSGDATA);
//
//	    /***** Function evaluation ***************************************/
//		<functionname>();
//	    
//	    /***** Variables: Memory post-conditions *************************/
//		CU_ASSERT_DOUBLE_EQUAL(<var_name1>, <value>, 1e-3);
//		CU_ASSERT_EQUAL(<var_name2>, <value>);
//		
//     /***** Messages: post-conditions **********************************/
//	 	START_<MSG_NAME>_MESSAGE_LOOP 
//	    	CU_ASSERT_DOUBLE_EQUAL(<msg_name>_message-><var_name>, <value>, 1e-3);
//	 		CU_ASSERT_EQUAL(<msg_name>_message-><var_name>, <value>);
//		FINISH_<MSG_NAME>_MESSAGE_LOOP
//	
//	    /************* At end of unit test, free the agent **************/
//	    unittest_free_<Agent_name>_agent();
//     /************* At end of unit tests, free all Messages **********/
//	    free_messages();
//	}
