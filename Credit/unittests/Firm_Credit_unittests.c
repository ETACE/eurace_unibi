#include <CUnit/Basic.h>
#include "../../header.h"
#include "../../Firm_agent_header.h"
#include "../../my_library_header.h"

/************Firm Role: Credit Role ********************************/

/************ Unit tests ********************************/

//	void unittest_<function_name>()
//	{
//	    /************* At start of unit test, add one agent **************/
//		add_<Agent_name>_agent_internal(init_<Agent_name>_agent());
//		current_xmachine = *p_xmachine;
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
//	    free_agent();
//     /************* At end of unit tests, free all Messages **********/
//	    free_messages();
//	}

void unittest1_Firm_ask_loan()
{
	    int rc;

    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();

    /***** Variables: Memory pre-conditions **************************/
	FLAME_environment_variable_print_debug_credit = 1;
	FLAME_environment_variable_number_of_banks_to_apply = 3;
	
	EXTERNAL_FINANCIAL_NEEDS = 100;
	add_int(&POTENTIAL_LENDERS, 1);
	add_int(&SET_OF_LENDERS, 1);
	
    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_bank_identity, sizeof(m_bank_identity));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'bank_identity' board\n");
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
    add_bank_identity_message(1920);
    add_bank_identity_message(1670);
	
    rc = MB_Iterator_Create(b_bank_identity, &i_bank_identity);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'bank_identity'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'bank_identity' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'bank_identity' board is locked\n");
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
	Firm_ask_loan();
	    
    /***** Variables: Memory post-conditions *************************/
//	CU_ASSERT_DOUBLE_EQUAL(<var_name1>, <value>, 1e-3);
//	CU_ASSERT_EQUAL(<var_name2>, <value>);
		
     /***** Messages: post-conditions **********************************/
//	START_<MSG_NAME>_MESSAGE_LOOP 
//	    CU_ASSERT_DOUBLE_EQUAL(<msg_name>_message-><var_name>, <value>, 1e-3);
//	    CU_ASSERT_EQUAL(<msg_name>_message-><var_name>, <value>);
//	FINISH_<MSG_NAME>_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
     /************* At end of unit tests, free all Messages **********/
	free_messages();
}


void unittest2_Firm_ask_loan()
{
    /************* At start of unit test, add one agent **************/
    unittest_init_Firm_agent();

    /***** Variables: Memory pre-conditions **************************/

    /***** Messages: pre-conditions **********************************/
//	add_<message_name>_message(<msg_var>, MSGDATA);

    /***** Function evaluation ***************************************/
	Firm_ask_loan();
	    
    /***** Variables: Memory post-conditions *************************/
//	CU_ASSERT_DOUBLE_EQUAL(<var_name1>, <value>, 1e-3);
//	CU_ASSERT_EQUAL(<var_name2>, <value>);
		
     /***** Messages: post-conditions **********************************/
//	START_<MSG_NAME>_MESSAGE_LOOP 
//	    CU_ASSERT_DOUBLE_EQUAL(<msg_name>_message-><var_name>, <value>, 1e-3);
//	    CU_ASSERT_EQUAL(<msg_name>_message-><var_name>, <value>);
//	FINISH_<MSG_NAME>_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
     /************* At end of unit tests, free all Messages **********/
	free_messages();
}

