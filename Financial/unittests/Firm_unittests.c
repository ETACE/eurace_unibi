#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../../header.h"
#include "../../Firm_agent_header.h"
#include "../../my_library_header.h"

/************Firm Role: Financial Market ********************************/
/*
 * \fn: void unittest_Firm()
 * \brief: Unit test for: Firm
 * Status: NOT Tested
 */
void unittest_Firm()
{
	int rc;
	int id;

    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
    /***** Variables: Memory pre-conditions **************************/

	/***** Messages: initialize message boards **********************************/
	/* NOTE: initialize message boards is always done in this place. */
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
    	    
    /***** Message: Adding message iterators for message loops inside function-evaluation ********************************/
    /* NOTE: Adding message iterators should be done just before a message loop starts:
     * 1. if the function itself reads messages: add message iterators *before* the function evaluation, so here.
     * 2. if the function does not read messages, but adds them: add message iterators *after* the function evaluation,
     * but before the Message post-conditions.
     */
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
//	<Agentname>_function();
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Message: Adding message iterators for post-evaluation message loops ********************************/
    /* NOTE: Adding message iterators should be done just before a message loop starts:
     * 1. if the function itself reads messages: add message iterators *before* the function evaluation, so here.
     * 2. if the function does not read messages, but adds them: add message iterators *after* the function evaluation,
     * but before the Message post-conditions.
     */
	//rc = MB_Iterator_Create(b_<message>, &i_<message>);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
/*
    START_<message>_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(<message>_message->var, value);
	     CU_ASSERT_DOUBLE_EQUAL(<message>_message->var, value, 1e-3);
	FINISH_<message>_MESSAGE_LOOP
*/	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/************ Unit tests ********************************/
