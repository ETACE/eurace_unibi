#include <CUnit/Basic.h>

#include "../../header.h"
#include "../../Firm_agent_header.h"
#include "../../my_library_header.h"


/*
 * \fn: void unittest1_Firm_bankruptcy_rescale_loans()
 * \brief: Unit test for: Firm_bankruptcy_rescale_loans.
 * Status: OK
 */
void unittest1_Firm_bankruptcy_rescale_loans()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_debt_rescaling_factor = 0.33333333333;
    FLAME_environment_variable_target_leverage_ratio = 2.00;
    FLAME_environment_variable_target_liquidity_ratio = 0.0;
	FLAME_environment_variable_print_debug_bankruptcy=1;
    
	FLAME_environment_variable_const_bankruptcy_idle_period=240;
	BANKRUPTCY_INSOLVENCY_STATE=1;

	/***** Variables: Memory pre-conditions **************************/
    TOTAL_VALUE_CAPITAL_STOCK = 130.0;
    TOTAL_ASSETS =0.0;
    TOTAL_DEBT = 150.0; 
    PAYMENT_ACCOUNT = 20.0; //degree of freedom to set this value
    EXTERNAL_FINANCIAL_NEEDS =0.0;
    
    //target_debt: 80
    //write_off_ratio: 70/150
    //target_equity: 40
    //external_needs: 0
    
/*
    LOANS[0].bank_id =1;
    LOANS[0].loan_value=150.0;
    LOANS[0].interest_rate=0.01;
    LOANS[0].installment_amount=50.0;
    LOANS[0].var_per_installment=50.0;
    LOANS[0].residual_var=0.0;
    LOANS[0].bad_debt=0.0;
    LOANS[0].nr_periods_before_repayment=3;
*/
    reset_debt_item_array(&LOANS);
    add_debt_item(&LOANS, 1, 150.0, 0.01, 50.0, 50.0, 150.0, 0.0, 3);
    
    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_bankruptcy, sizeof(m_bankruptcy));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'bankruptcy' board\n");
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
    BANKRUPTCY_IDLE_COUNTER=239;
    Firm_bankruptcy_rescale_loans();    
    BANKRUPTCY_IDLE_COUNTER=40;
    Firm_bankruptcy_rescale_loans();    
    BANKRUPTCY_IDLE_COUNTER=20;
    Firm_bankruptcy_rescale_loans();    
    /***** Message: Adding message iterators ***************************************/
    //add_bankruptcy_message(bank_id, bad_debt, credit_refunded, writeoff_var);

    rc = MB_Iterator_Create(b_bankruptcy, &i_bankruptcy);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'bankruptcy'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'bankruptcy' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'bankruptcy' board is locked\n");
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
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 0.0, 1e-3);

    /***** Messages: Message post-conditions *****/

    //Test this:
    //bad_debt = write_off_ratio*LOANS.array[i].loan_value; = (70/150)*150 = 70;
    //credit_refunded = (PAYMENT_ACCOUNT/TOTAL_DEBT)*LOANS.array[i].loan_value; = (10/150)*150=10
    //PAYMENT_ACCOUNT -= credit_refunded;
    //TOTAL_ASSETS -= credit_refunded;

/*
    START_BANKRUPTCY_MESSAGE_LOOP
        //printf("\n Found a bankruptcy message.\n");
        CU_ASSERT_EQUAL(bankruptcy_message->bank_id, 1);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->bad_debt, 70.0, 1e-3);     
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->credit_refunded, 10.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->writeoff_var, 150.0, 1e-3);
    FINISH_BANKRUPTCY_MESSAGE_LOOP
*/
/*
	CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_ASSETS, 120.0, 1e-3);
*/    
    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Firm_bankruptcy_rescale_loans()
 * \brief: Unit test for: Firm_bankruptcy_rescale_loans.
 * Status: OK
 */
void unittest2_Firm_bankruptcy_rescale_loans()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_debt_rescaling_factor = 0.33333333333;
    FLAME_environment_variable_target_leverage_ratio = 2.00;
    FLAME_environment_variable_target_liquidity_ratio = 0.0;
	FLAME_environment_variable_print_debug_bankruptcy=1;
    
	FLAME_environment_variable_const_bankruptcy_idle_period=240;
	BANKRUPTCY_INSOLVENCY_STATE=0;
	BANKRUPTCY_ILLIQUIDITY_STATE=1;
	
	/***** Variables: Memory pre-conditions **************************/
    TOTAL_VALUE_CAPITAL_STOCK = 130.0;
    TOTAL_ASSETS =0.0;
    TOTAL_DEBT = 150.0; 
    PAYMENT_ACCOUNT = 50.0; //degree of freedom to set this value
    EXTERNAL_FINANCIAL_NEEDS =0.0;
    
    //target_debt: 80
    //write_off_ratio: 70/150
    //target_equity: 40
    //external_needs: 0
    
/*
    LOANS[0].bank_id =1;
    LOANS[0].loan_value=150.0;
    LOANS[0].interest_rate=0.01;
    LOANS[0].installment_amount=50.0;
    LOANS[0].var_per_installment=50.0;
    LOANS[0].residual_var=0.0;
    LOANS[0].bad_debt=0.0;
    LOANS[0].nr_periods_before_repayment=3;
*/
    reset_debt_item_array(&LOANS);
    add_debt_item(&LOANS, 1, 150.0, 0.01, 50.0, 50.0, 150.0, 0.0, 3);
    
    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_bankruptcy, sizeof(m_bankruptcy));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'bankruptcy' board\n");
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
	BANKRUPTCY_IDLE_COUNTER=239;
    Firm_bankruptcy_rescale_loans();    
    BANKRUPTCY_IDLE_COUNTER=40;
    Firm_bankruptcy_rescale_loans();    
    BANKRUPTCY_IDLE_COUNTER=20;
    Firm_bankruptcy_rescale_loans();    
    /***** Message: Adding message iterators ***************************************/
    //add_bankruptcy_message(bank_id, bad_debt, credit_refunded, writeoff_var);

    rc = MB_Iterator_Create(b_bankruptcy, &i_bankruptcy);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'bankruptcy'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'bankruptcy' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'bankruptcy' board is locked\n");
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
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 0.0, 1e-3);

    /***** Messages: Message post-conditions *****/

    //Test this:
    //bad_debt = write_off_ratio*LOANS.array[i].loan_value; = (70/150)*150 = 70;
    //credit_refunded = (PAYMENT_ACCOUNT/TOTAL_DEBT)*LOANS.array[i].loan_value; = (10/150)*150=10
    //PAYMENT_ACCOUNT -= credit_refunded;
    //TOTAL_ASSETS -= credit_refunded;

/*
    START_BANKRUPTCY_MESSAGE_LOOP
        //printf("\n Found a bankruptcy message.\n");
        CU_ASSERT_EQUAL(bankruptcy_message->bank_id, 1);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->bad_debt, 70.0, 1e-3);     
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->credit_refunded, 10.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->writeoff_var, 150.0, 1e-3);
    FINISH_BANKRUPTCY_MESSAGE_LOOP
*/
/*
	CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_ASSETS, 120.0, 1e-3);
*/    
    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

