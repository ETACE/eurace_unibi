#include <CUnit/Basic.h>
#include "../../header.h"
#include "../../Firm_agent_header.h"
#include "../../my_library_header.h"

/************Firm Role: Financial Management Role ********************************/

/************ Unit tests ********************************/

/*
 * \fn: void unittest_Firm_compute_financial_payments()
 * \brief: Unit test for: Firm_compute_financial_payments.
 * Status: Tested OK
 */
void unittest_Firm_compute_financial_payments()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    /*
    LOANS[0].bank_id =1;
    LOANS[0].loan_value=100.0;
    LOANS[0].interest_rate=0.01;
    LOANS[0].installment_amount=20.0;
    LOANS[0].var_per_installment=0.0;
    LOANS[0].residual_var=0.0;
    LOANS[0].bad_debt=0.0;
    LOANS[0].nr_periods_before_repayment=5;

    LOANS[1].bank_id=2;
    LOANS[1].loan_value=200.0;
    LOANS[1].interest_rate=0.02;
    LOANS[1].installment_amount=50.0;
    LOANS[1].var_per_installment=0.0;
    LOANS[1].residual_var=0.0;
    LOANS[1].bad_debt=0.0;
    LOANS[1].nr_periods_before_repayment=4;
*/
    reset_debt_item_array(&LOANS);
    add_debt_item(&LOANS, 1, 100.0, 0.01, 20.0, 0.0, 0.0, 0.0, 5);
    add_debt_item(&LOANS, 2, 200.0, 0.02, 50.0, 0.0, 0.0, 0.0, 4);

    TOTAL_INTEREST_PAYMENT=0.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT=0.0;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
    //add_<message>_message();
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_compute_financial_payments();
    
    /***** Variables: Memory post-conditions *****/

        CU_ASSERT_EQUAL(LOANS.array[0].bank_id, 1);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].loan_value, 100.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].interest_rate, 0.01, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].installment_amount, 20.0, 1e-3);
        CU_ASSERT_EQUAL(LOANS.array[0].nr_periods_before_repayment, 5);

        CU_ASSERT_EQUAL(LOANS.array[1].bank_id, 2);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].loan_value, 200.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].interest_rate, 0.02, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].installment_amount, 50.0, 1e-3);
        CU_ASSERT_EQUAL(LOANS.array[1].nr_periods_before_repayment, 4);
        
        CU_ASSERT_DOUBLE_EQUAL(TOTAL_INTEREST_PAYMENT, 5.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(TOTAL_DEBT_INSTALLMENT_PAYMENT, 70.0, 1e-3);

    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Firm_compute_income_statement()
 * \brief: Unit test for: Firm_compute_income_statement.
 * Status: Tested OK
 */
void unittest_Firm_compute_income_statement()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/

    CUM_REVENUE = 130.0;
    TOTAL_INTEREST_PAYMENT = 20.0;
    CALC_PRODUCTION_COSTS = 10.0;
    EARNINGS =0.0;
    TAX_PAYMENT =0.0;
    TAX_RATE_CORPORATE = 0.25;

    PAYMENT_ACCOUNT=0.0;
    PREVIOUS_NET_EARNINGS =1.0;
    NET_EARNINGS =2.0;
    
    PREVIOUS_EARNINGS_PER_SHARE =0.0;
    CURRENT_SHARES_OUTSTANDING =75;
    EARNINGS_PER_SHARE =2.0;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_compute_income_statement();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(EARNINGS, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TAX_PAYMENT, 25.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PREVIOUS_NET_EARNINGS, 2.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(NET_EARNINGS, 75.0, 1e-3);
    
    CU_ASSERT_DOUBLE_EQUAL(PREVIOUS_EARNINGS_PER_SHARE, 2.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EARNINGS_PER_SHARE, 1.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(NET_EARNINGS, 75.0, 1e-3);
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Firm_compute_dividends()
 * \brief: Unit test for: Firm_compute_dividends.
 * Status: Tested OK
 * Case: Zero dividends at start
 */
void unittest1_Firm_compute_dividends()
{   
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_const_dividend_earnings_ratio = 0.01;

    /***** Variables: Memory pre-conditions **************************/
    TOTAL_DIVIDEND_PAYMENT =0.0;
    NET_EARNINGS = 4.0;

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_compute_dividends();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_DIVIDEND_PAYMENT, 0.04, 1e-3);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Firm_compute_dividends()
 * \brief: Unit test for: Firm_compute_dividends.
 * Status: Tested OK
 * Case: option 4: keep earnings per share constant
 */
void unittest2_Firm_compute_dividends()
{   
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    TOTAL_DIVIDEND_PAYMENT =1.0;
    
    EARNINGS_PER_SHARE = 2.0;
    PREVIOUS_EARNINGS_PER_SHARE = 1.0;
    CURRENT_SHARES_OUTSTANDING = 200;
    PREVIOUS_SHARES_OUTSTANDING = 100;
    
    CURRENT_DIVIDEND_PER_SHARE =0.0;

    NET_EARNINGS = 4.0;
    EARNINGS = 4.0;
    PREVIOUS_DIVIDEND_PER_EARNINGS = 0.0;
    CURRENT_DIVIDEND_PER_EARNINGS = 1.0;

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_compute_dividends();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_DIVIDEND_PAYMENT, 4.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PREVIOUS_DIVIDEND_PER_SHARE, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(CURRENT_DIVIDEND_PER_SHARE, 0.02, 1e-3);    
    CU_ASSERT_DOUBLE_EQUAL(PREVIOUS_DIVIDEND_PER_EARNINGS, 1.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(CURRENT_DIVIDEND_PER_EARNINGS, 1.0, 1e-3);

    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Firm_compute_dividends()
 * \brief: Unit test for: Firm_compute_dividends.
 * Status: Tested OK
 * Case: Zero dividends at start
 */
void unittest3_Firm_compute_dividends()
{   
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_const_dividend_earnings_ratio = 0.01;
    FLAME_environment_variable_const_dividend_treshold_full_payout = 0.50;

    /***** Variables: Memory pre-conditions **************************/
    TOTAL_DIVIDEND_PAYMENT =0.0;
    NET_EARNINGS = 100.0;

	LAST_REVENUES.size=1;
	LAST_REVENUES.array[0]=0.0;

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_compute_dividends();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_DIVIDEND_PAYMENT, 0.04, 1e-3);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Firm_compute_total_financial_payments()
 * \brief: Unit test for: Firm_function.
 * Status: Tested OK
 */
void unittest_Firm_compute_total_financial_payments()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    TOTAL_PAYMENTS = 0.0;
    
    TOTAL_INTEREST_PAYMENT = 1.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT = 1.0;
    TOTAL_DIVIDEND_PAYMENT = 1.0; 
    TAX_PAYMENT = 1.0;
    CALC_PRODUCTION_COSTS = 1.0;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_compute_total_financial_payments();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_PAYMENTS, 5.0, 1e-3);

    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Firm_compute_balance_sheet()
 * \brief: Unit test for: Firm_compute_balance_sheet.
 * Status: Tested OK
 */
void unittest_Firm_compute_balance_sheet()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
/*
    CURRENT_MALL_STOCKS[0].mall_id =1;
    CURRENT_MALL_STOCKS[0].critical_stock=1.0;
    CURRENT_MALL_STOCKS[0].current_stock=2.0;

    CURRENT_MALL_STOCKS[1].mall_id =2;
    CURRENT_MALL_STOCKS[1].critical_stock=1.0;
    CURRENT_MALL_STOCKS[1].current_stock=2.0;
*/
    reset_mall_info_array(&CURRENT_MALL_STOCKS);
    add_mall_info(&CURRENT_MALL_STOCKS, 1, 1.0, 2.0);
    add_mall_info(&CURRENT_MALL_STOCKS, 2, 1.0, 2.0);

    PRICE = 1.0;
    TOTAL_VALUE_LOCAL_INVENTORY =0.0;
    TOTAL_ASSETS = 0.0;
    PAYMENT_ACCOUNT = 10.0;
    TOTAL_VALUE_CAPITAL_STOCK = 1.0;
    TOTAL_DEBT = 7.5;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_compute_balance_sheet();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(CURRENT_MALL_STOCKS.size, 2);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_LOCAL_INVENTORY, 4.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_ASSETS, 15.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EQUITY, 7.5, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(DEBT_EQUITY_RATIO, 1.0, 1e-3);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Firm_compute_total_liquidity_needs()
 * \brief: Unit test for: Firm_compute_total_liquidity_needs.
 * Status: NOT Tested, gives a problem
 */
void unittest_Firm_compute_total_liquidity_needs()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    FINANCIAL_LIQUIDITY_NEEDS = 0.0; 
    PRODUCTION_LIQUIDITY_NEEDS = 0.0; 
        
    PLANNED_PRODUCTION_COSTS = 1.0;
    TOTAL_DIVIDEND_PAYMENT = 1.0;
    TOTAL_INTEREST_PAYMENT = 1.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT = 1.0;
    TAX_PAYMENT = 1.0;
    
    PAYMENT_ACCOUNT = 2.0;
    TOTAL_FINANCIAL_NEEDS = 0.0;
    EXTERNAL_FINANCIAL_NEEDS = 0.0;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_compute_total_liquidity_needs();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_FINANCIAL_NEEDS, 5.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 3.0, 1e-3);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_Firm_check_financial_and_bankruptcy_state()
 * \brief: Unit test for: Firm_check_financial_and_bankruptcy_state.
 * Status: Tested OK
 */
void unittest1_Firm_check_financial_and_bankruptcy_state()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/ 
    BANKRUPTCY_ILLIQUIDITY_STATE=1;
    FINANCIAL_CRISIS_STATE=1;

    PAYMENT_ACCOUNT = 2.0;
    TOTAL_FINANCIAL_NEEDS = 5.0;
    
    TOTAL_INTEREST_PAYMENT = 1.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT = 1.0;
    TAX_PAYMENT = 1.0;

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_check_financial_and_bankruptcy_state();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(BANKRUPTCY_ILLIQUIDITY_STATE, 1);
    CU_ASSERT_EQUAL(FINANCIAL_CRISIS_STATE, 0);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Firm_check_financial_and_bankruptcy_state()
 * \brief: Unit test for: Firm_check_financial_and_bankruptcy_state.
 * Status: Tested OK
 */
void unittest2_Firm_check_financial_and_bankruptcy_state()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/ 
    BANKRUPTCY_ILLIQUIDITY_STATE=1;
    FINANCIAL_CRISIS_STATE=1;

    PAYMENT_ACCOUNT = 3.0;
    TOTAL_FINANCIAL_NEEDS = 5.0;
    
    TOTAL_INTEREST_PAYMENT = 1.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT = 1.0;
    TAX_PAYMENT = 1.0;

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_check_financial_and_bankruptcy_state();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(BANKRUPTCY_ILLIQUIDITY_STATE, 0);
    CU_ASSERT_EQUAL(FINANCIAL_CRISIS_STATE, 1);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Firm_in_financial_crisis()
 * \brief: Unit test for: Firm_in_financial_crisis.
 * Status: Tested OK
 */
void unittest_Firm_in_financial_crisis()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    PAYMENT_ACCOUNT = 14.0;
    TOTAL_INTEREST_PAYMENT = 1.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT = 1.0;
    TAX_PAYMENT = 1.0;
    
    TOTAL_DIVIDEND_PAYMENT = 100.0;
    PLANNED_PRODUCTION_COSTS = 10.0;;
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_in_financial_crisis();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_DIVIDEND_PAYMENT, 1.0, 1e-3);
    CU_ASSERT_EQUAL(FINANCIAL_CRISIS_STATE, 0);
    CU_ASSERT_EQUAL(BANKRUPTCY_STATE, 0);

    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_Firm_execute_financial_payments()
 * \brief: Unit test for: Firm_execute_financial_payments.
 * Cases: 
 * - 1 loan with nr_periods_before_repayment=2 (to be decreased)
 * - 1 loan with nr_periods_before_repayment=1 (to be removed)
 * - 1 loan with nr_periods_before_repayment=25 (to be decreased and shifted)
 * - 1 loan with nr_periods_before_repayment=25 (to be decreased and shifted)
 * Status: Tested OK
 */
void unittest1_Firm_execute_financial_payments()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_const_installment_periods = 24;
   	FLAME_environment_variable_print_debug_finman = 1;
   	FLAME_environment_variable_id_debug_probe = 1;

    /***** Variables: Memory pre-conditions **************************/
	ID = 1;
/*
    LOANS[0].bank_id =1;
    LOANS[0].loan_value=100.0;
    LOANS[0].interest_rate=0.01;
    LOANS[0].installment_amount=20.0;
    LOANS[0].var_per_installment=20.0;
    LOANS[0].residual_var=0.0;
    LOANS[0].bad_debt=0.0;
    LOANS[0].nr_periods_before_repayment=2;

    LOANS[1].bank_id=2;
    LOANS[1].loan_value=50.0;
    LOANS[1].interest_rate=0.02;
    LOANS[1].installment_amount=50.0;
    LOANS[1].var_per_installment=50.0;
    LOANS[1].residual_var=0.0;
    LOANS[1].bad_debt=0.0;
    LOANS[1].nr_periods_before_repayment=1;

    LOANS[2].bank_id=3;
    LOANS[2].loan_value=240.0;
    LOANS[2].interest_rate=0.01;
    LOANS[2].installment_amount=10.0;
    LOANS[2].var_per_installment=10.0;
    LOANS[2].residual_var=240.0;
    LOANS[2].bad_debt=0.0;
    LOANS[2].nr_periods_before_repayment=25;

    LOANS[3].bank_id=4;
    LOANS[3].loan_value=480.0;
    LOANS[3].interest_rate=0.01;
    LOANS[3].installment_amount=20.0;
    LOANS[3].var_per_installment=20.0;
    LOANS[3].residual_var=480.0;
    LOANS[3].bad_debt=0.0;
    LOANS[3].nr_periods_before_repayment=25;
*/
    reset_debt_item_array(&LOANS);
    add_debt_item(&LOANS, 1, 100.0, 0.01, 20.0, 20.0, 0.0, 0.0, 2);
    add_debt_item(&LOANS, 2, 50.0, 0.02, 50.0, 50.0, 0.0, 0.0, 1);
    add_debt_item(&LOANS, 3, 240.0, 0.01, 10.0, 10.0, 240.0, 0.0, 25);
    add_debt_item(&LOANS, 4, 480.0, 0.01, 20.0, 20.0, 480.0, 0.0, 25);
    
    PAYMENT_ACCOUNT = 100.0;
    TOTAL_INTEREST_PAYMENT=0.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT=0.0;
    TOTAL_DEBT=0.0;
    EQUITY = 560;
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_installment, sizeof(m_installment));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'installment' board\n");
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
    //add_installment_message();
            
    /***** Message: Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_installment, &i_installment);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'installment'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'installment' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'installment' board is locked\n");
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
    Firm_execute_financial_payments();
    
    /***** Variables: Memory post-conditions *****/
/*    
    printf("\n LOANS.array[0].bank_id=%d\n", LOANS.array[0].bank_id);
    printf("\n LOANS.array[0].loan_value=%2.2f\n", LOANS.array[0].loan_value);
    printf("\n LOANS.array[0].nr_periods_before_repayment=%d\n", LOANS.array[0].nr_periods_before_repayment);
*/
    CU_ASSERT_EQUAL(LOANS.array[0].bank_id, 1);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].loan_value, 80.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].interest_rate, 0.01, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[0].installment_amount, 20.0, 1e-3);
    CU_ASSERT_EQUAL(LOANS.array[0].nr_periods_before_repayment, 1);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 28.0, 1e-3);
/*
    printf("\n LOANS.array[1].bank_id=%d\n", LOANS.array[1].bank_id);
    printf("\n LOANS.array[1].loan_value=%2.2f\n", LOANS.array[1].loan_value);
    printf("\n LOANS.array[1].nr_periods_before_repayment=%d\n", LOANS.array[1].nr_periods_before_repayment);
*/
    CU_ASSERT_EQUAL(LOANS.array[1].bank_id, 3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].loan_value, 240.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].interest_rate, 0.01, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[1].installment_amount, 10.0, 1e-3);
    CU_ASSERT_EQUAL(LOANS.array[1].nr_periods_before_repayment, 24);
/*    
    printf("\n LOANS.array[2].bank_id=%d\n", LOANS.array[2].bank_id);
    printf("\n LOANS.array[2].loan_value=%2.2f\n", LOANS.array[2].loan_value);
    printf("\n LOANS.array[2].nr_periods_before_repayment=%d\n", LOANS.array[2].nr_periods_before_repayment);
*/
    CU_ASSERT_EQUAL(LOANS.array[2].bank_id, 4);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[2].loan_value, 480.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[2].interest_rate, 0.01, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(LOANS.array[2].installment_amount, 20.0, 1e-3);
    CU_ASSERT_EQUAL(LOANS.array[2].nr_periods_before_repayment, 24);

    //printf("\n Total_debt=%2.2f\n", TOTAL_DEBT);

    CU_ASSERT_DOUBLE_EQUAL(TOTAL_DEBT, 870.0, 1e-3);
    CU_ASSERT_EQUAL(LOANS.size, 3);
    
    /***** Messages: Message post-conditions *****/
    //start a reading loop
    //add_installment_message(bank_id, installment_amount, interest_amount, var_per_installment, total_var)
	add_installment_message(1, 20.0, 1.0, 1, 2);
	add_installment_message(1, 20.0, 1.0, 1, 2);


    START_INSTALLMENT_MESSAGE_LOOP
    printf("\n Entering installment_message loop.\n");
//    if(installment_message->bank_id==1)
//    {
        CU_ASSERT_DOUBLE_EQUAL(installment_message->installment_amount, 20.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(installment_message->interest_amount, 1.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(installment_message->var_per_installment, 20.0, 1e-3);
//    }
    if(installment_message->bank_id==2)
    {
        CU_ASSERT_DOUBLE_EQUAL(installment_message->installment_amount, 50.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(installment_message->interest_amount, 1.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(installment_message->var_per_installment, 50.0, 1e-3);
    }
    FINISH_INSTALLMENT_MESSAGE_LOOP
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Firm_execute_financial_payments()
 * \brief: Unit test for: Firm_execute_financial_payments.
 * Status: Tested OK
 */
void unittest2_Firm_execute_financial_payments()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_const_installment_periods = 24;

    /***** Variables: Memory pre-conditions **************************/
    GOV_ID=1;
    ID =2;
    TAX_PAYMENT=100.0;
    PAYMENT_ACCOUNT = 200.0;
    
    CURRENT_DIVIDEND_PER_SHARE = 0.0;
    TOTAL_DIVIDEND_PAYMENT = 100.0;
    CURRENT_SHARES_OUTSTANDING = 100;
    
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_tax_payment, sizeof(m_tax_payment));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'tax_payment' board\n");
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
    printf("\n rc=%d MB_SUCCESS=%d\n", rc, MB_SUCCESS);
            
        rc = MB_Create(&b_dividend_info, sizeof(m_dividend_info));
                #ifdef ERRCHECK
                if (rc != MB_SUCCESS)
                {
                   fprintf(stderr, "ERROR: Could not create 'dividend_per_share' board\n");
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
    printf("\n rc=%d MB_SUCCESS=%d\n", rc, MB_SUCCESS);
            
    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_tax_payment, &i_tax_payment);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'tax_payment'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'tax_payment' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'tax_payment' board is locked\n");
                       break;
                   case MB_ERR_MEMALLOC:
                       fprintf(stderr, "\t reason: out of memory\n");
                       break;
                   case MB_ERR_INTERNAL:
                       fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
                       break;
               }
            }
    printf("\n rc=%d MB_SUCCESS=%d\n", rc, MB_SUCCESS);

    rc = MB_Iterator_Create(b_dividend_info, &i_dividend_info);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'dividend_per_share'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'dividend_per_share' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'dividend_per_share' board is locked\n");
                       break;
                   case MB_ERR_MEMALLOC:
                       fprintf(stderr, "\t reason: out of memory\n");
                       break;
                   case MB_ERR_INTERNAL:
                       fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
                       break;
               }
            }

    printf("\n rc=%d MB_SUCCESS=%d\n", rc, MB_SUCCESS);

    /***** Function evaluation ***************************************/
    Firm_execute_financial_payments();
    
    /***** Variables: Memory post-conditions *****/
//    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 0.0, 1e-3);

    /***** Messages: Message post-conditions *****/
    //start a reading loop

    START_TAX_PAYMENT_MESSAGE_LOOP
         printf("\n Entering tax_payment_message loop.\n");
         CU_ASSERT_EQUAL(tax_payment_message->gov_id, 1);
         CU_ASSERT_DOUBLE_EQUAL(tax_payment_message->tax_payment, 100.0, 1e-3);
    FINISH_TAX_PAYMENT_MESSAGE_LOOP
 

//NEW:	add_dividend_info_message(ID, TOTAL_DIVIDEND_PAYMENT);    

    START_DIVIDEND_INFO_MESSAGE_LOOP
         printf("\n Entering dividend_info_message loop.\n");
         CU_ASSERT_EQUAL(dividend_info_message->firm_id, 2);
         CU_ASSERT_DOUBLE_EQUAL(dividend_info_message->total_dividend, 100.0, 1e-3);
    FINISH_DIVIDEND_INFO_MESSAGE_LOOP

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Firm_bankruptcy_idle_counter()
 * \brief: Unit test for: Firm_bankruptcy_idle_counter.
 * Status: NOT Tested
 */
void unittest_Firm_bankruptcy_idle_counter()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    BANKRUPTCY_IDLE_COUNTER = 10;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_bankruptcy_idle_counter();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(BANKRUPTCY_IDLE_COUNTER, 9);

    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Firm_reset_bankruptcy_flags()
 * \brief: Unit test for: Firm_reset_bankruptcy_flags.
 * Status: NOT Tested
 */
void unittest_Firm_reset_bankruptcy_flags()
{
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    ACTIVE=0;
    BANKRUPTCY_INSOLVENCY_STATE  = 1;
    BANKRUPTCY_ILLIQUIDITY_STATE = 0;
    BANKRUPTCY_IDLE_COUNTER = -1;
    EXTERNAL_FINANCIAL_NEEDS = 0.0;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Firm_reset_bankruptcy_flags();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(ACTIVE, 1);
    CU_ASSERT_EQUAL(BANKRUPTCY_INSOLVENCY_STATE, 0);
    CU_ASSERT_EQUAL(BANKRUPTCY_ILLIQUIDITY_STATE, 0);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
