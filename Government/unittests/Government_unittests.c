#include <CUnit/Basic.h>
//For trunk model
#include "../../header.h"
#include "../../Government_agent_header.h"

//For Isolated model
//#include "../header.h"
//#include "../Government_agent_header.h"
//#include "../../my_library_header.h"

/************Government: Public Sector Role ********************************/

/************ Unit tests ********************************/

/*
 * \fn: void unittest_Government_send_policy_announcements()
 * \brief: Unit tests for: Government_send_policy_announcements
 * Status: NOT Tested
 */
void unittest1_Government_send_policy_announcements()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
     TAX_RATE_HH_LABOUR=0.0;
     TAX_RATE_CORPORATE=0.0;

    /************* Setting environment variables **************/
    FLAME_environment_variable_policy_exp_stabilization = 0;
    FLAME_environment_variable_const_income_tax_rate = 0.05;

    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_policy_announcement, sizeof(m_policy_announcement));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'policy_announcement' board\n");
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
            
    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_policy_announcement, &i_policy_announcement);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'policy_announcement'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'policy_announcement' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'policy_announcement' board is locked\n");
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
    Government_send_policy_announcements();
    
    /***** Variables: Memory post-conditions *****/
//  CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Variables: Message post-conditions *****/
    //start a reading loop

    START_POLICY_ANNOUNCEMENT_MESSAGE_LOOP
         CU_ASSERT_DOUBLE_EQUAL(policy_announcement_message->tax_rate_hh_labour, 0.05, 1e-3);
	 CU_ASSERT_DOUBLE_EQUAL(policy_announcement_message->tax_rate_corporate, 0.05, 1e-3);
    FINISH_POLICY_ANNOUNCEMENT_MESSAGE_LOOP
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_send_policy_announcements()
 * \brief: Unit tests for: Government_send_policy_announcements
 * Status: NOT Tested
 */
void unittest2_Government_send_policy_announcements()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
     TAX_RATE_HH_LABOUR=0.0;
     TAX_RATE_CORPORATE=0.0;
     SUBSIDY_FLAG=0;
     GDP_GROWTH=0.01;
     SUBSIDY_TRIGGER_ON=0.03;
     SUBSIDY_TRIGGER_OFF=0.03;

    /************* Setting environment variables **************/
    FLAME_environment_variable_policy_exp_stabilization = 1;
    FLAME_environment_variable_const_income_tax_rate = 0.05;

    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_policy_announcement, sizeof(m_policy_announcement));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'policy_announcement' board\n");
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
            
    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_policy_announcement, &i_policy_announcement);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'policy_announcement'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'policy_announcement' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'policy_announcement' board is locked\n");
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
    Government_send_policy_announcements();
    
    /***** Variables: Memory post-conditions *****/
//  CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Variables: Message post-conditions *****/
    //start a reading loop

    START_POLICY_ANNOUNCEMENT_MESSAGE_LOOP
         CU_ASSERT_DOUBLE_EQUAL(policy_announcement_message->tax_rate_hh_labour, 0.01, 1e-3);
	 CU_ASSERT_DOUBLE_EQUAL(policy_announcement_message->tax_rate_corporate, 0.01, 1e-3);
    FINISH_POLICY_ANNOUNCEMENT_MESSAGE_LOOP
    
	CU_ASSERT_EQUAL(SUBSIDY_FLAG, 1);

    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_read_tax_payments()
 * \brief: Unit tests for: Government_read_tax_payments
 * Status: Tested OK
 */
void unittest_Government_read_tax_payments()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    
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

    /***** Messages: pre-conditions **********************************/
     add_tax_payment_message(ID, 100.0);
            
    /***** Adding message iterators ***************************************/

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
                
    /***** Function evaluation ***************************************/
    Government_read_tax_payments();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_TAX_REVENUES, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_TAX_REVENUES, 100.0, 1e-3);
    
    /***** Variables: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_Government_read_unemployment_benefit_notifications()
 * \brief: Unit tests for: Government_read_unemployment_benefit_notifications
 * Status: Tested OK
 * Test case for: unemployment_benefit > COUNTRY_WIDE_MEAN_WAGE*0.50
 */
void unittest1_Government_read_unemployment_benefit_notifications()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
        
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    UNEMPLOYMENT_BENEFIT_PCT=0.70;
    COUNTRY_WIDE_MEAN_WAGE=60.0;
    MONTHLY_BENEFIT_PAYMENT=0.0;
    YEARLY_BENEFIT_PAYMENT=0.0;
    PAYMENT_ACCOUNT=0.0;
    
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_unemployment_notification, sizeof(m_unemployment_notification));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'unemployment_notification' board\n");
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
     //add_unemployment_notification_message(gov_id,last_labour_income);
     add_unemployment_notification_message(ID, 100.0);
            
    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_unemployment_notification, &i_unemployment_notification);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'unemployment_notification'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'unemployment_notification' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'unemployment_notification' board is locked\n");
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
    Government_read_unemployment_benefit_notifications();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_BENEFIT_PAYMENT, 70.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_BENEFIT_PAYMENT, 70.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, -70.0, 1e-3);   
    CU_ASSERT_EQUAL(NUM_UNEMPLOYED, 1); 
    
    /***** Variables: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest2_Government_read_unemployment_benefit_notifications()
 * \brief: Unit tests for: Government_read_unemployment_benefit_notifications
 * Status: Tested OK
 * Test case for: unemployment_benefit < COUNTRY_WIDE_MEAN_WAGE*0.50
 */
void unittest2_Government_read_unemployment_benefit_notifications()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    UNEMPLOYMENT_BENEFIT_PCT=0.70;
    COUNTRY_WIDE_MEAN_WAGE=150.0;
    MONTHLY_BENEFIT_PAYMENT=0.0;
    YEARLY_BENEFIT_PAYMENT=0.0;
    PAYMENT_ACCOUNT=0.0;
    
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_unemployment_notification, sizeof(m_unemployment_notification));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'unemployment_notification' board\n");
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
     //add_unemployment_notification_message(gov_id,last_labour_income);
     add_unemployment_notification_message(ID, 100.0);
            
    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_unemployment_notification, &i_unemployment_notification);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'unemployment_notification'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'unemployment_notification' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'unemployment_notification' board is locked\n");
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
    Government_read_unemployment_benefit_notifications();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_BENEFIT_PAYMENT, 75.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_BENEFIT_PAYMENT, 75.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, -75.0, 1e-3);   
    CU_ASSERT_EQUAL(NUM_UNEMPLOYED, 1); 
    
    /***** Variables: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Government_read_transfer_notifications()
 * \brief: Unit tests for: Government_read_transfer_notifications
 * Status: Tested OK
 */
void unittest_Government_read_transfer_notifications()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    HH_TRANSFER_PAYMENT = 100;
    FIRM_TRANSFER_PAYMENT = 200;
    PAYMENT_ACCOUNT =350;
    MONTHLY_TRANSFER_PAYMENT =0.0;
    YEARLY_TRANSFER_PAYMENT =0.0;

    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_hh_transfer_notification, sizeof(m_hh_transfer_notification));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'hh_transfer_notification' board\n");
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
    
    rc = MB_Create(&b_firm_transfer_notification, sizeof(m_firm_transfer_notification));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firm_transfer_notification' board\n");
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
     add_hh_transfer_notification_message(ID);
     add_firm_transfer_notification_message(ID);
     
    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_hh_transfer_notification, &i_hh_transfer_notification);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'hh_transfer_notification'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'hh_transfer_notification' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'hh_transfer_notification' board is locked\n");
                       break;
                   case MB_ERR_MEMALLOC:
                       fprintf(stderr, "\t reason: out of memory\n");
                       break;
                   case MB_ERR_INTERNAL:
                       fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
                       break;
               }
            }
                
    rc = MB_Iterator_Create(b_firm_transfer_notification, &i_firm_transfer_notification);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'transfer_notification'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_transfer_notification' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_transfer_notification' board is locked\n");
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
    Government_read_transfer_notifications();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_TRANSFER_PAYMENT, 300.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_TRANSFER_PAYMENT, 300.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 50.0, 1e-3);

    /***** Variables: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_read_subsidy_notifications()
 * \brief: Unit tests for: Government_read_subsidy_notifications
 * Status: Tested OK
 */
void unittest_Government_read_subsidy_notifications()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    HH_SUBSIDY_PAYMENT = 100;
    FIRM_SUBSIDY_PAYMENT = 200;
    PAYMENT_ACCOUNT =350;
    MONTHLY_SUBSIDY_PAYMENT=0.0;
    YEARLY_SUBSIDY_PAYMENT=0.0;
    
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_hh_subsidy_notification, sizeof(m_hh_subsidy_notification));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'hh_subsidy_notification' board\n");
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

    rc = MB_Create(&b_firm_subsidy_notification, sizeof(m_firm_subsidy_notification));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firm_subsidy_notification' board\n");
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
     add_hh_subsidy_notification_message(ID);
     add_firm_subsidy_notification_message(ID);
     
    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_hh_subsidy_notification, &i_hh_subsidy_notification);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'hh_subsidy_notification'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'hh_subsidy_notification' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'hh_subsidy_notification' board is locked\n");
                       break;
                   case MB_ERR_MEMALLOC:
                       fprintf(stderr, "\t reason: out of memory\n");
                       break;
                   case MB_ERR_INTERNAL:
                       fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
                       break;
               }
            }
    
    rc = MB_Iterator_Create(b_firm_subsidy_notification, &i_firm_subsidy_notification);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'firm_subsidy_notification'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_subsidy_notification' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_subsidy_notification' board is locked\n");
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
    Government_read_subsidy_notifications();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_SUBSIDY_PAYMENT, 300.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_SUBSIDY_PAYMENT, 300.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 50.0, 1e-3);
    
    /***** Variables: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_monthly_budget_accounting()
 * \brief: Unit tests for: Government_monthly_budget_accounting
 * Status: NOT Tested
 */
void unittest_Government_monthly_budget_accounting()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Government_monthly_budget_accounting();
    
    /***** Variables: Memory post-conditions *****/
//  CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Variables: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_yearly_budget_accounting()
 * \brief: Unit tests for: Government_yearly_budget_accounting
 * Status: NOT Tested
 */
void unittest_Government_yearly_budget_accounting()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Adding message iterators ***************************************/

    /***** Function evaluation ***************************************/
    Government_yearly_budget_accounting();
    
    /***** Variables: Memory post-conditions *****/
//  CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Variables: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_send_account_update()
 * \brief: Unit tests for: Government_send_account_update
 * Status: Tested OK
 */
void unittest_Government_send_account_update()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    PAYMENT_ACCOUNT=100.0;

    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_central_bank_account_update, sizeof(m_central_bank_account_update));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'central_bank_account_update' board\n");
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
    Government_send_account_update();
    
    /***** Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_central_bank_account_update, &i_central_bank_account_update);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'central_bank_account_update'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'central_bank_account_update' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'central_bank_account_update' board is locked\n");
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

    /***** Variables: Message post-conditions *****/
    //start a reading loop

    //add_central_bank_account_update_message(ID, PAYMENT_ACCOUNT);
    START_CENTRAL_BANK_ACCOUNT_UPDATE_MESSAGE_LOOP
         CU_ASSERT_EQUAL(central_bank_account_update_message->id, 1);
         CU_ASSERT_DOUBLE_EQUAL(central_bank_account_update_message->payment_account, 100.0, 1e-3);
    FINISH_CENTRAL_BANK_ACCOUNT_UPDATE_MESSAGE_LOOP
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_read_data_from_Eurostat()
 * \brief: Unit tests for: Government_read_data_from_Eurostat
 * Status: Test broken due to envionment vars
 */

void unittest_Government_read_data_from_Eurostat()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();

    /************* Setting environment variables **************/
    FLAME_environment_variable_no_regions_per_gov = 2;

    /***** Variables: Memory pre-conditions **************************/
    ID=1;
    GDP=10.0;
    GDP_GROWTH=0.0;
    
    LIST_OF_REGIONS.array[0]=1;
    LIST_OF_REGIONS.array[1]=2;
    
    /***** Messages: initialize message boards **********************************/

    rc = MB_Create(&b_data_for_government, sizeof(m_data_for_government));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'data_for_government' board\n");
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
     //add_data_for_government_message(region_id, gdp, mean_wage);
     add_data_for_government_message(1, 10.0, 1.0);
     add_data_for_government_message(2, 10.0, 1.0);

    /***** Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_data_for_government, &i_data_for_government);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'data_for_government'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'data_for_government' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'data_for_government' board is locked\n");
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
     Government_read_data_from_Eurostat();
    
    /***** Variables: Memory post-conditions *****/
        
    /***** Variables: Message post-conditions *****/
    //start a reading loop

    START_DATA_FOR_GOVERNMENT_MESSAGE_LOOP
    if(data_for_government_message->region_id==LIST_OF_REGIONS.array[0])
    {
        //printf("\n region=%d\n", data_for_government_message->region_id);
         CU_ASSERT_EQUAL(data_for_government_message->region_id, 1);
        //printf("\n data_for_government_message->gdp=%2.2f\n", data_for_government_message->gdp);
         CU_ASSERT_DOUBLE_EQUAL(data_for_government_message->gdp, 10.0, 1e-3);
        //printf("\n data_for_government_message->mean_wage=%2.2f\n", data_for_government_message->mean_wage);
         CU_ASSERT_DOUBLE_EQUAL(data_for_government_message->mean_wage, 1.0, 1e-3);
    }
    if(data_for_government_message->region_id==LIST_OF_REGIONS.array[1])
    {
        //printf("\n region=%d\n", data_for_government_message->region_id);
         CU_ASSERT_EQUAL(data_for_government_message->region_id, 2);
        //printf("\n data_for_government_message->gdp=%2.2f\n", data_for_government_message->gdp);
        CU_ASSERT_DOUBLE_EQUAL(data_for_government_message->gdp, 10.0, 1e-3);
        //printf("\n data_for_government_message->mean_wage=%2.2f\n", data_for_government_message->mean_wage);
         CU_ASSERT_DOUBLE_EQUAL(data_for_government_message->mean_wage, 1.0, 1e-3);
    }
     FINISH_DATA_FOR_GOVERNMENT_MESSAGE_LOOP
    
    //printf("\n COUNTRY_WIDE_MEAN_WAGE=%2.2f\n", COUNTRY_WIDE_MEAN_WAGE);
    CU_ASSERT_DOUBLE_EQUAL(COUNTRY_WIDE_MEAN_WAGE, 1.0, 1e-3);
    //printf("\n GDP=%2.2f\n", GDP);
    CU_ASSERT_DOUBLE_EQUAL(GDP, 20.0, 1e-3);
    //printf("\n GDP_GROWTH=%2.2f\n", GDP_GROWTH);
    CU_ASSERT_DOUBLE_EQUAL(GDP_GROWTH, 2.0, 1e-3);

    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_set_policy()
 * \brief: Unit tests for: Government_set_policy
 * Status: Tested OK
 */
void unittest_Government_set_policy()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /************* Setting environment variables **************/
    FLAME_environment_variable_gov_policy_gdp_fraction_consumption = 0.20;
    FLAME_environment_variable_gov_policy_gdp_fraction_investment = 0.30;
    
    /***** Variables: Memory pre-conditions **************************/
    GDP=100.0;
    GDP_GROWTH=1.00;
    
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Adding message iterators ***************************************/
    
    /***** Function evaluation ***************************************/
    Government_set_policy();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(GDP_FORECAST, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_CONSUMPTION_EXPENDITURE, 20.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_INVESTMENT_EXPENDITURE, 30.0, 1e-3);

    /***** Variables: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_yearly_resetting()
 * \brief: Unit tests for: Government_yearly_resetting
 * Status: Tested OK
 */
void unittest_Government_yearly_resetting()
{
    int rc;
    double result;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    YEARLY_TAX_REVENUES =10.0;
    YEARLY_BENEFIT_PAYMENT =10.0;
    YEARLY_TRANSFER_PAYMENT =10.0;
    YEARLY_SUBSIDY_PAYMENT =10.0;
    YEARLY_BOND_INTEREST_PAYMENT =10.0;
    YEARLY_INVESTMENT_EXPENDITURE =10.0;
    YEARLY_CONSUMPTION_EXPENDITURE =10.0;

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Adding message iterators ***************************************/
            
    /***** Function evaluation ***************************************/
    Government_yearly_resetting();
    
    /***** Variables: Memory post-conditions *****/
    result=0.0;
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_TAX_REVENUES, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_BENEFIT_PAYMENT, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_TRANSFER_PAYMENT, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_SUBSIDY_PAYMENT, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_BOND_INTEREST_PAYMENT, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_INVESTMENT_EXPENDITURE, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(YEARLY_CONSUMPTION_EXPENDITURE, result, 1e-3);
    
    /***** Variables: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Government_monthly_resetting()
 * \brief: Unit tests for: Government_monthy_resetting
 * Status: Tested OK
 */
void unittest_Government_monthly_resetting()
{
    int rc;
    double result;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Government_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    MONTHLY_TAX_REVENUES =10.0;
    MONTHLY_BENEFIT_PAYMENT =10.0;
    MONTHLY_TRANSFER_PAYMENT =10.0;
    MONTHLY_SUBSIDY_PAYMENT =10.0;
    MONTHLY_BOND_INTEREST_PAYMENT =10.0;
    MONTHLY_INVESTMENT_EXPENDITURE =10.0;
    MONTHLY_CONSUMPTION_EXPENDITURE =10.0;

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Adding message iterators ***************************************/
            
    /***** Function evaluation ***************************************/
    Government_monthly_resetting();
    
    /***** Variables: Memory post-conditions *****/
    result=0.0;
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_TAX_REVENUES, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_BENEFIT_PAYMENT, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_TRANSFER_PAYMENT, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_SUBSIDY_PAYMENT, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_BOND_INTEREST_PAYMENT, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_INVESTMENT_EXPENDITURE, result, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_CONSUMPTION_EXPENDITURE, result, 1e-3);
    
    /***** Variables: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Government_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
