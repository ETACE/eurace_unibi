#include <CUnit/Basic.h>

#include "../../header.h"
#include "../../Firm_agent_header.h"
#include "../../my_library_header.h"

/*
 * \fn: void unittest_Firm_set_bankruptcy_illiquidity()
 * \brief: Unit test for: Firm_set_bankruptcy_illiquidity.
 * Status: NOT Tested
 */
void unittest_Firm_set_bankruptcy_illiquidity()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_const_bankruptcy_idle_period = 240;

    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    ACTIVE =1;
    BANKRUPTCY_IDLE_COUNTER=0;
    
    BANKRUPTCY_INSOLVENCY_STATE  = 0;
    BANKRUPTCY_ILLIQUIDITY_STATE = 0;
    
    TOTAL_VALUE_LOCAL_INVENTORY = 10.0;

    
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_bankruptcy_illiquidity, sizeof(m_bankruptcy_illiquidity));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'bankruptcy_illiquidity' board\n");
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
    Firm_set_bankruptcy_illiquidity();

    /***** Message: Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_bankruptcy_illiquidity, &i_bankruptcy_illiquidity);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'bankruptcy_illiquidity'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'bankruptcy_illiquidity' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'bankruptcy_illiquidity' board is locked\n");
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
    
    CU_ASSERT_EQUAL(ACTIVE, 0);
    CU_ASSERT_EQUAL(BANKRUPTCY_IDLE_COUNTER, 240);
    CU_ASSERT_EQUAL(BANKRUPTCY_INSOLVENCY_STATE, 0);
    CU_ASSERT_EQUAL(BANKRUPTCY_ILLIQUIDITY_STATE, 1);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_LOCAL_INVENTORY, 0.0, 1e-3);
    
    /***** Messages: Message post-conditions *****/
    //start a reading loop

    START_BANKRUPTCY_ILLIQUIDITY_MESSAGE_LOOP
         CU_ASSERT_EQUAL(bankruptcy_illiquidity_message->firm_id, 1);
    FINISH_BANKRUPTCY_ILLIQUIDITY_MESSAGE_LOOP

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*
 * \fn: void unittest_Firm_set_bankruptcy_insolvency()
 * \brief: Unit test for: Firm_set_bankruptcy_insolvency.
 * Status: NOT Tested
 */
void unittest_Firm_set_bankruptcy_insolvency()
{
    int rc;

    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_const_bankruptcy_idle_period = 240;
    
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    ACTIVE =1;
    BANKRUPTCY_IDLE_COUNTER=0;
    
    BANKRUPTCY_INSOLVENCY_STATE  = 0;
    BANKRUPTCY_ILLIQUIDITY_STATE = 0;
    
    TOTAL_VALUE_LOCAL_INVENTORY = 10.0;
    
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_bankruptcy_insolvency, sizeof(m_bankruptcy_insolvency));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'bankruptcy_insolvency' board\n");
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
    Firm_set_bankruptcy_insolvency();

    /***** Message: Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_bankruptcy_insolvency, &i_bankruptcy_insolvency);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'bankruptcy_insolvency'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'bankruptcy_insolvency' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'bankruptcy_insolvency' board is locked\n");
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
    
    CU_ASSERT_EQUAL(ACTIVE, 0);
    CU_ASSERT_EQUAL(BANKRUPTCY_IDLE_COUNTER, 240);
    CU_ASSERT_EQUAL(BANKRUPTCY_INSOLVENCY_STATE, 1);
    CU_ASSERT_EQUAL(BANKRUPTCY_ILLIQUIDITY_STATE, 0);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_VALUE_LOCAL_INVENTORY, 0.0, 1e-3);
    
    /***** Messages: Message post-conditions *****/
    //start a reading loop

    START_BANKRUPTCY_INSOLVENCY_MESSAGE_LOOP
         CU_ASSERT_EQUAL(bankruptcy_insolvency_message->firm_id, 1);
    FINISH_BANKRUPTCY_INSOLVENCY_MESSAGE_LOOP

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest1_Firm_bankruptcy_insolvency_procedure()
 * \brief: Unit test for: Firm_bankruptcy_insolvency_procedure.
 * Status: NOT Tested, broken due to environment variable issue
 */
void unittest1_Firm_bankruptcy_insolvency_procedure()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_debt_rescaling_factor = 0.33333333333;
    FLAME_environment_variable_target_leverage_ratio = 2.00;
    FLAME_environment_variable_target_liquidity_ratio = 0.0;

    /***** Variables: Memory pre-conditions **************************/
    TOTAL_VALUE_CAPITAL_STOCK = 130.0;
    TOTAL_ASSETS =0.0;
    TOTAL_DEBT = 150.0; 
    PAYMENT_ACCOUNT = 10.0; //degree of freedom to set this value
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
    Firm_bankruptcy_insolvency_procedure();    
    
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

    START_BANKRUPTCY_MESSAGE_LOOP
        //printf("\n Found a bankruptcy message.\n");
        CU_ASSERT_EQUAL(bankruptcy_message->bank_id, 1);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->bad_debt, 70.0, 1e-3);     
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->credit_refunded, 10.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->writeoff_var, 150.0, 1e-3);
    FINISH_BANKRUPTCY_MESSAGE_LOOP

    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_ASSETS, 120.0, 1e-3);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Firm_bankruptcy_insolvency_procedure()
 * \brief: Unit test for: Firm_bankruptcy_insolvency_procedure.
 * Status: NOT Tested, broken due to environment variable issue
 */
void unittest2_Firm_bankruptcy_insolvency_procedure()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();

    /************* Setting environment variables **************/
    FLAME_environment_variable_debt_rescaling_factor = 0.3333333;
    FLAME_environment_variable_target_leverage_ratio = 1.25;
    FLAME_environment_variable_target_liquidity_ratio = 0.0;

    /***** Variables: Memory pre-conditions **************************/
    TOTAL_VALUE_CAPITAL_STOCK = 130.0;
    TOTAL_ASSETS =0.0;
    TOTAL_DEBT = 150.0;
    PAYMENT_ACCOUNT = 10.0;
    EXTERNAL_FINANCIAL_NEEDS =0.0;
    
    //target_debt: 80
    //write_off_ratio: 70/150
    //target_equity: 64
    //external_needs: 24
    
/*
    LOANS[0].bank_id =1;
    LOANS[0].loan_value=150.0;
    LOANS[0].interest_rate=0.01;
    LOANS[0].installment_amount=50.0;
    LOANS[0].var_per_installment=50.0;
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
    Firm_bankruptcy_insolvency_procedure();

    /***** Message: Adding message iterators ***************************************/
    //add_bankruptcy_message(bank_id, bad_debt, credit_refunded, residual_var);

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
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 24.0, 1e-3);

    /***** Messages: Message post-conditions *****/

    //Test this:
    //bad_debt = write_off_ratio*LOANS.array[i].loan_value; = (70/150)*150 = 70;
    //credit_refunded = (PAYMENT_ACCOUNT/TOTAL_DEBT)*LOANS.array[i].loan_value; = (10/150)*150=10
    //PAYMENT_ACCOUNT -= credit_refunded;
    //TOTAL_ASSETS -= credit_refunded;

    START_BANKRUPTCY_MESSAGE_LOOP
        //printf("\n Found a bankruptcy message.\n");
        CU_ASSERT_EQUAL(bankruptcy_message->bank_id, 1);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->bad_debt, 70.0, 1e-3);     
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->credit_refunded, 10.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->writeoff_var, 150.0, 1e-3);
    FINISH_BANKRUPTCY_MESSAGE_LOOP

    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_ASSETS, 120.0, 1e-3);

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest3_Firm_bankruptcy_insolvency_procedure()
 * \brief: Unit test for: Firm_bankruptcy_insolvency_procedure.
 * Status: NOT Tested, broken due to environment variable issue
 */
void unittest3_Firm_bankruptcy_insolvency_procedure()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_debt_rescaling_factor = 0.3333333333;
    FLAME_environment_variable_target_leverage_ratio = 4.0;
    FLAME_environment_variable_target_liquidity_ratio = 0.0;

    /***** Variables: Memory pre-conditions **************************/
    TOTAL_VALUE_CAPITAL_STOCK = 130.0;
    TOTAL_ASSETS =0.0;
    TOTAL_DEBT = 150.0;
    PAYMENT_ACCOUNT = 10.0;
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
    Firm_bankruptcy_insolvency_procedure();

    /***** Message: Adding message iterators ***************************************/
    //add_bankruptcy_message(bank_id, bad_debt, credit_refunded, residual_var);

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

    START_BANKRUPTCY_MESSAGE_LOOP
        //printf("\n Found a bankruptcy message.\n");
        CU_ASSERT_EQUAL(bankruptcy_message->bank_id, 1);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->bad_debt, 70.0, 1e-3);     
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->credit_refunded, 10.0, 1e-3);
        CU_ASSERT_DOUBLE_EQUAL(bankruptcy_message->residual_var, 150.0, 1e-3);
    FINISH_BANKRUPTCY_MESSAGE_LOOP

    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(TOTAL_ASSETS, 120.0, 1e-3);

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Firm_bankruptcy_illiquidity_procedure()
 * \brief: Unit test for: Firm_bankruptcy_illiquidity_procedure.
 * Status: Tested OK
 */
void unittest_Firm_bankruptcy_illiquidity_procedure()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    //employee(worker_id, region_id, wage, general_skill, specific_skill);
    reset_employee_array(&EMPLOYEES);
    add_employee(&EMPLOYEES, 2, 1, 1.0,1,1.0,1.0);
    
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_firing, sizeof(m_firing));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firing' board\n");
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
    Firm_bankruptcy_illiquidity_procedure();
            
    /***** Message: Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_firing, &i_firing);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'firing'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firing' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firing' board is locked\n");
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
//  CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
    //start a reading loop

    START_FIRING_MESSAGE_LOOP
         CU_ASSERT_EQUAL(firing_message->firm_id,1);
         CU_ASSERT_EQUAL(firing_message->worker_id,2);
    FINISH_FIRING_MESSAGE_LOOP
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Firm_compute_and_send_stock_orders()
 * \brief: Unit test for: Firm_compute_and_send_stock_orders.
 * Status: Tested OK
 */
void unittest_Firm_compute_and_send_stock_orders()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    CURRENT_SHARE_PRICE=100.0;
    EXTERNAL_FINANCIAL_NEEDS = 120.0;
    
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
    
    /***** Function evaluation ***************************************/
    Firm_compute_and_send_stock_orders();

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
    
    /***** Variables: Memory post-conditions *****/

    /***** Messages: Message post-conditions *****/
    //start a reading loop
    //add_order_message(trader_id, asset_id, limit_price, quantity)
    START_ORDER_MESSAGE_LOOP
        CU_ASSERT_EQUAL(order_message->trader_id, 1);
        CU_ASSERT_EQUAL(order_message->asset_id, 1);
        CU_ASSERT_DOUBLE_EQUAL(order_message->limit_price, 99.0, 1e-3);
        CU_ASSERT_EQUAL(order_message->quantity, -2);
    FINISH_ORDER_MESSAGE_LOOP

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Firm_read_stock_transactions()
 * \brief: Unit test for: Firm_read_stock_transactions.
 * Status: Test FAILED: quantity = -100
 */
void unittest_Firm_read_stock_transactions()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    PREVIOUS_SHARES_OUTSTANDING =-1;
    CURRENT_SHARES_OUTSTANDING = 0;
    PAYMENT_ACCOUNT = 0.0;
    EXTERNAL_FINANCIAL_NEEDS = 100.0;
    
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
    //add_order_status_message(trader_id, asset_id, price, quantity)
    add_order_status_message(ID, ID, 1.0, -100);
            
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
    Firm_read_stock_transactions();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(PREVIOUS_SHARES_OUTSTANDING, 0);
    CU_ASSERT_EQUAL(CURRENT_SHARES_OUTSTANDING, 100);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXTERNAL_FINANCIAL_NEEDS, 0.0, 1e-3);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

