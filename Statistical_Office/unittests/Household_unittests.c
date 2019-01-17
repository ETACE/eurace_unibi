#include <CUnit/Basic.h>
//For trunk model
#include "../../header.h"
#include "../../Household_agent_header.h"
#include "../../my_library_header.h"

/************ Unit tests ********************************/
/*
 * \fn: void unittest_Household_receive_data()
 * \brief: Unit test for: Eurostat_reset_data.
 * Status: Tested NO
 */
void unittest_Household_receive_data()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	reset_int_array(&LIST_OF_BANKRUPT_FIRMS);
	add_int(&LIST_OF_BANKRUPT_FIRMS,1);
    add_int(&LIST_OF_BANKRUPT_FIRMS,2);
    
	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_bankruptcy, sizeof(m_bankruptcy));
    	    #ifdef ERRCHECK
    	    if (rc != MB_SUCCESS)
    	    {
    	       fprintf(stderr, "ERROR: Could not create 'bankruptcy_message' board\n");
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
    //add_bankruptcy_message(firm_id, bank_id, bad_debt, credit_refunded, residual_var);
    add_bankruptcy_message(3, 0, 0.0, 0.0, 0.0);
    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_bankruptcy, &i_bankruptcy);
			
	if (rc != MB_SUCCESS)
			{
			   fprintf(stderr, "ERROR: Could not create Iterator for 'bankruptcy_message'\n");
			   switch(rc) {
			       case MB_ERR_INVALID:
			           fprintf(stderr, "\t reason: 'bankruptcy_message' board is invalid\n");
			           break;
			       case MB_ERR_LOCKED:
		               fprintf(stderr, "\t reason: 'bankruptcy_message' board is locked\n");
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
	Household_receive_data();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_EQUAL(LIST_OF_BANKRUPT_FIRMS.array[0], 1);
	CU_ASSERT_EQUAL(LIST_OF_BANKRUPT_FIRMS.array[1], 2);
	CU_ASSERT_EQUAL(LIST_OF_BANKRUPT_FIRMS.array[2], 3);
	
    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_BANKRUPTCY_MESSAGE_LOOP
		CU_ASSERT_EQUAL(bankruptcy_message->firm_id, 3);
	FINISH_BANKRUPTCY_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}
