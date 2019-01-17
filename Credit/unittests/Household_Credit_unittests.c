#include <CUnit/Basic.h>
#include "header.h"
#include "Household_agent_header.h"
#include "my_library_header.h"

/************Household Role: Credit Role ********************************/

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
