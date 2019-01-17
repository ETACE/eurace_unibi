#include <CUnit/Basic.h>
#include "../../header.h"
#include "../../Bank_agent_header.h"
//#include "my_library_header.h"

/************Bank Role: Credit Market********************************/

/************ Unit tests ********************************/

	void unittest_Bank_decide_credit_conditions()
	{
//	    /************* At start of unit test, add one agent **************/
		//add_Bank_agent_internal(init_Bank_agent(), init_Bank_state());
		//current_xmachine = *p_xmachine;
		int rc;
		unittest_init_Bank_agent();
//
//		/***** Variables: Memory pre-conditions **************************/
//		<var_name1>=0.0;
//		<var_name2>=0;
        ID = 1;
        ECB_DEBT = 0;
        VALUE_AT_RISK = 10;
        EQUITY = 30;
//        MIN_INTEREST = 2;
        BANK_GAMMA[0] = 0.05;
        BANK_GAMMA[1] = 0.06;

        rc = MB_Create(&b_loan_request, sizeof(m_loan_request));
        	    #ifdef ERRCHECK
        	    if (rc != MB_SUCCESS)
        	    {
        	       fprintf(stderr, "ERROR: Could not create 'loan_request' board\n");
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

//
//      /***** Messages: pre-conditions **********************************/
		add_loan_request_message(50,10,5,2,1);
//		rc = MB_Iterator_CreateFiltered(b_loan_request, &i_loan_request, &Bank_Bank_decide_credit_conditions_loan_request_filter, current_xmachine_Bank);
		rc = MB_Iterator_Create(b_loan_request, &i_loan_request);
				
		if (rc != MB_SUCCESS)
				{
				   fprintf(stderr, "ERROR: Could not create Iterator for 'loan_request'\n");
				   switch(rc) {
				       case MB_ERR_INVALID:
				           fprintf(stderr, "\t reason: 'loan_request' board is invalid\n");
				           break;
				       case MB_ERR_LOCKED:
			               fprintf(stderr, "\t reason: 'loan_request' board is locked\n");
			               break;
			           case MB_ERR_MEMALLOC:
			               fprintf(stderr, "\t reason: out of memory\n");
			               break;
			           case MB_ERR_INTERNAL:
			               fprintf(stderr, "\t reason: internal error. Recompile libmoard in debug mode for more info \n");
			               break;
				   }
				}
				
//	    /***** Function evaluation ***************************************/
        Bank_decide_credit_conditions();
//	    
//	    /***** Variables: Memory post-conditions *************************/
//		CU_ASSERT_DOUBLE_EQUAL(<var_name1>, <value>, 1e-3);
//		CU_ASSERT_EQUAL(<var_name2>, <value>);
//		
//     /***** Messages: post-conditions **********************************/
	 	START_LOAN_CONDITIONS_MESSAGE_LOOP
	    		CU_ASSERT_DOUBLE_EQUAL(loan_conditions_message->amount_offered_credit, 1.2959, 1e-5);
//	 		CU_ASSERT_EQUAL(<msg_name>_message-><var_name>, <value>);
		FINISH_LOAN_CONDITIONS_MESSAGE_LOOP
//	
//	    /************* At end of unit test, free the agent **************/
	    //free_agent();
		unittest_free_Bank_agent();
//     /************* At end of unit tests, free all Messages **********/
	    free_messages();
	}


/*
 * \fn: void unittest_<Agentname>_function()
 * \brief: Unit test for: <Agentname>_function.
 * Status: NOT Tested
 */
void unittest_Bank_receive_installment()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Bank_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	ID = 1;
	VALUE_AT_RISK=0;

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
    //add_installment_message(bank_id, installment_amount, interest_amount, var_per_installment, total_var)
    	add_installment_message(1, 20.0, 1.0, 1, 2);
	add_installment_message(2, 40.0, 2.0, 2, 4);

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
	Bank_receive_installment();
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);


    /***** Messages: Message post-conditions *****/
	//start a reading loop

	START_INSTALLMENT_MESSAGE_LOOP
	if(installment_message->bank_id==1)
	{
	     CU_ASSERT_DOUBLE_EQUAL(installment_message->var_per_installment, 1.0, 1e-3);
	     CU_ASSERT_DOUBLE_EQUAL(installment_message->total_var, 2.0, 1e-3);
	}
	FINISH_INSTALLMENT_MESSAGE_LOOP

	CU_ASSERT_DOUBLE_EQUAL(VALUE_AT_RISK, 1.0, 1e-3);
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Bank_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
