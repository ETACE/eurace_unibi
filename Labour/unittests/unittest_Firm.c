#include <CUnit/Basic.h>
//For trunk model
#include "../../header.h"
#include "../../Firm_agent_header.h"
#include "../../my_library_header.h"
#include "../Labour_aux_header.h"

/*
 * 1) initialize agent
 * 2) add memory pre-conditions
 * 3) initialise MBs
 * 4) add message pre-conditions
 * 5) create MB iterators
 * 6) evaluate function to be tested
 * 7) assertions on memory post-conditions
 * 8) assertions on message post-conditions
 * 9) free agent
 * 10) free MBs
 */

/*
 * \fn: void unittest_<Agentname>_function()
 * \brief: Unit test for: <Agentname>_function.
 * Status: NOT Tested
 */

/*CASE 0: Employees in every skill group*/
void unittest_Firm_calculate_specific_skills_and_wage_offer()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	reset_employee_array(&EMPLOYEES);
	    add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);

	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
	
	AVERAGE_S_SKILL_OF_1 = 1;
	AVERAGE_S_SKILL_OF_2 = 1;
	AVERAGE_S_SKILL_OF_3 = 1;
	AVERAGE_S_SKILL_OF_4 = 1;
	AVERAGE_S_SKILL_OF_5 = 1;
	
	WAGE_OFFER = 1.0;
	
	        	    
    /***** Function evaluation ***************************************/
	Firm_calculate_specific_skills_and_wage_offer();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_1, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_2, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_3, 3.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_4, 4.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_5, 5.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_1, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_2, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_3, 3.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_4, 4.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_5, 5.0, 1e-3);

    
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*CASE 1: Employees in skill groups 1-3*/
void unittest_Firm_calculate_specific_skills_and_wage_offer_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	reset_employee_array(&EMPLOYEES);
	    add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,3,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,3,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,3,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,3,5.0);

	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 6;
	NO_EMPLOYEES_SKILL_4 = 0;
	NO_EMPLOYEES_SKILL_5 = 0;
	
	AVERAGE_S_SKILL_OF_1 = 1;
	AVERAGE_S_SKILL_OF_2 = 1;
	AVERAGE_S_SKILL_OF_3 = 1;
	AVERAGE_S_SKILL_OF_4 = 1;
	AVERAGE_S_SKILL_OF_5 = 1;
	
	WAGE_OFFER = 1.0;
	
	        	    
    /***** Function evaluation ***************************************/
	Firm_calculate_specific_skills_and_wage_offer();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_1, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_2, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_3, 4.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_4, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_5, 1.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_1, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_2, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_3, 4.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_4, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_S_SKILL_OF_5, 1.0, 1e-3);

    
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 0: */
void unittest_Firm_send_vacancies()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	EMPLOYEES_NEEDED = 10;  
	NO_EMPLOYEES = 0;
	
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_vacancies, sizeof(m_vacancies));
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
    	    
    /***** Function evaluation ***************************************/
    Firm_send_vacancies();
	
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_vacancies, &i_vacancies);
			
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
	    	    
    
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 10, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i=1;
	
	START_VACANCIES_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(vacancies_message->firm_id, ID);
		 CU_ASSERT_EQUAL(vacancies_message->region_id, REGION_ID);
	     CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_vacancies, 10, 1e-3);
	     if(i==1)
	     {
	    	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 1);
	    	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 1.0, 1e-3);
	     }
	     if(i==2)
	     {
	     	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 2);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 2.0, 1e-3);
	     }
	     if(i==3)
	     {
	     	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 3);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 3.0, 1e-3);
	     }
	     if(i==4)
	     {
	     	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 4);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 4.0, 1e-3);
	     }
	     if(i==5)
	     {
	     	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 5);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 5.0, 1e-3);
	     }
	     i++;
	     
	     
	FINISH_VACANCIES_MESSAGE_LOOP
	
	
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: only different values of the memory variables*/
void unittest_Firm_send_vacancies_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	EMPLOYEES_NEEDED = 1;  
	NO_EMPLOYEES = 0;
	
	WAGE_OFFER_FOR_SKILL_1 = 10.0;
	WAGE_OFFER_FOR_SKILL_2 = 20.0;
	WAGE_OFFER_FOR_SKILL_3 = 30.0;
	WAGE_OFFER_FOR_SKILL_4 = 40.0;
	WAGE_OFFER_FOR_SKILL_5 = 50.0;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_vacancies, sizeof(m_vacancies));
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
    	    
    /***** Function evaluation ***************************************/
    Firm_send_vacancies();
	
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_vacancies, &i_vacancies);
			
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
	    	    
    
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 1, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i=1;
	
	START_VACANCIES_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(vacancies_message->firm_id, ID);
		 CU_ASSERT_EQUAL(vacancies_message->region_id, REGION_ID);
	     CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_vacancies, 1, 1e-3);
	     if(i==1)
	     {
	    	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 1);
	    	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 10.0, 1e-3);
	     }
	     if(i==2)
	     {
	     	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 2);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 20.0, 1e-3);
	     }
	     if(i==3)
	     {
	     	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 3);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 30.0, 1e-3);
	     }
	     if(i==4)
	     {
	     	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 4);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 40.0, 1e-3);
	     }
	     if(i==5)
	     {
	     	 CU_ASSERT_EQUAL(vacancies_message->skill_group, 5);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies_message->firm_wage_offer, 50.0, 1e-3);
	     }
	     i++;
	     
	     
	FINISH_VACANCIES_MESSAGE_LOOP
	
	
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0: Half of the employees are fired*/
void unittest_Firm_send_redundancies()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	EMPLOYEES_NEEDED = 5;  
	NO_EMPLOYEES = 10;
	
	reset_employee_array(&EMPLOYEES);
		add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);
	
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firing, sizeof(m_firing));
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
	
    /***** Function evaluation ***************************************/
    Firm_send_redundancies();
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_firing, &i_firing);
			
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
	    	    
    
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 1, 1);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_FIRING_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(firing_message->firm_id, ID);
	     CU_ASSERT_DOUBLE_EQUAL(firing_message->worker_id, 5, 5);
	FINISH_FIRING_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: All employees are fired*/
void unittest_Firm_send_redundancies_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	EMPLOYEES_NEEDED = 0;  
	NO_EMPLOYEES = 10;
	
	reset_employee_array(&EMPLOYEES);
		add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);
	
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firing, sizeof(m_firing));
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
	
    /***** Function evaluation ***************************************/
    Firm_send_redundancies();
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_firing, &i_firing);
			
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
	    	    
    
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 0, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_FIRING_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(firing_message->firm_id, ID);
	     CU_ASSERT_DOUBLE_EQUAL(firing_message->worker_id, 5, 5);
	FINISH_FIRING_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0: Min 1% Max 10% are fired -> one employee*/
void unittest_Firm_send_random_redundancies()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	NO_EMPLOYEES = 10;
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
		
	reset_employee_array(&EMPLOYEES);
		add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);
		
	LOWER_BOUND_FIRING = 1.0;
	UPPER_BOUND_FIRING = 10.0;
		
	
	

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firing, sizeof(m_firing));
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
	
	
    /***** Function evaluation ***************************************/
    Firm_send_random_redundancies();	    
    	    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_firing, &i_firing);
			
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
	    	    
    
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 9, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 1, 1);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 1, 1);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_FIRING_MESSAGE_LOOP
		CU_ASSERT_EQUAL(firing_message->firm_id, ID);
		CU_ASSERT_DOUBLE_EQUAL(firing_message->worker_id, 5, 5);
	FINISH_FIRING_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 1: Min 91% Max 100% are fired -> all employees*/
void unittest_Firm_send_random_redundancies_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	NO_EMPLOYEES = 10;
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
		
	reset_employee_array(&EMPLOYEES);
		add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);
		
	LOWER_BOUND_FIRING = 91.0;
	UPPER_BOUND_FIRING = 100.0;
		
	
	

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firing, sizeof(m_firing));
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
	
	
    /***** Function evaluation ***************************************/
    Firm_send_random_redundancies();	    
    	    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_firing, &i_firing);
			
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
	    	    
    
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 0, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_FIRING_MESSAGE_LOOP
		CU_ASSERT_EQUAL(firing_message->firm_id, ID);
		CU_ASSERT_DOUBLE_EQUAL(firing_message->worker_id, 5, 5);
	FINISH_FIRING_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0: Same number of vacancies and applicants*/
void unittest_Firm_read_job_applications_send_job_offer_or_rejection()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/		
			
	VACANCIES = 5;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	
	

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_application, sizeof(m_job_application));
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
    	    
    rc = MB_Create(&b_job_offer, sizeof(m_job_offer));
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
    	    	        	    
    	    	        	  
	    rc = MB_Create(&b_application_rejection, sizeof(m_application_rejection));
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
    	    
    	    
   
	
	/***** Messages: pre-conditions **********************************/
    add_job_application_message(1,ID,REGION_ID,1,1.0);
    add_job_application_message(2,ID,REGION_ID,2,2.0);
    add_job_application_message(3,ID,REGION_ID,3,3.0);
    add_job_application_message(4,ID,REGION_ID,4,4.0);
    add_job_application_message(5,ID,REGION_ID,5,5.0);
    
    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_application, &i_job_application);
			
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
	
	
	
	 
	/***** Function evaluation ***************************************/
		Firm_read_job_applications_send_job_offer_or_rejection();
	
	
	
	
	rc = MB_Iterator_Create(b_job_offer, &i_job_offer);
				
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
		

	rc = MB_Iterator_Create(b_application_rejection, &i_application_rejection);
					
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
			
	
	
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i = 1;		
	
	START_JOB_OFFER_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_offer_message->firm_id, ID);
		 CU_ASSERT_EQUAL(job_offer_message->region_id, REGION_ID);
		 
		 if(i == 1)
		 {
			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 5, 1e-3);
			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 5.0, 1e-3);
		 }
		 if(i == 2)
 		 {
 			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 4, 1e-3);
 			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 4.0, 1e-3);
 		 }
		 if(i == 3)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 3, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 3.0, 1e-3);
		 }
		 if(i == 4)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 2, 1e-3);
			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 2.0, 1e-3);
		 }
		 if(i == 5)
		 {
			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 1, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 1.0, 1e-3);
		 }
		 i++;
	FINISH_JOB_OFFER_MESSAGE_LOOP
	
	/*int j = 1;
	START_APPLICATION_REJECTION_MESSAGE_LOOP
		     CU_ASSERT_EQUAL(application_rejection_message->firm_id, ID);
			if(j == 1)
		        CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 6, 1e-3);
			if(j == 2)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 7, 1e-3);
			j++;
	FINISH_APPLICATION_REJECTION_MESSAGE_LOOP*/
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: one vacancies and  five applicants -> hire the applicant with highest general skill*/
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_1_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/		
			
	VACANCIES = 5;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	
	

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_application, sizeof(m_job_application));
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
    	    
    rc = MB_Create(&b_job_offer, sizeof(m_job_offer));
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
    	    	        	    
    	    	        	  
	    rc = MB_Create(&b_application_rejection, sizeof(m_application_rejection));
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
    	    
    	    
   
	
	/***** Messages: pre-conditions **********************************/
    
    add_job_application_message(5,ID,REGION_ID,5,5.0);
    
    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_application, &i_job_application);
			
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
	
	
	
	 
	/***** Function evaluation ***************************************/
		Firm_read_job_applications_send_job_offer_or_rejection();
	
	
	
	
	rc = MB_Iterator_Create(b_job_offer, &i_job_offer);
				
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
		

	rc = MB_Iterator_Create(b_application_rejection, &i_application_rejection);
					
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
			
	
	
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
			
	
	START_JOB_OFFER_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_offer_message->firm_id, ID);
		 CU_ASSERT_EQUAL(job_offer_message->region_id, REGION_ID); 
		 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 5, 1e-3);
		 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 5.0, 1e-3);	 
	FINISH_JOB_OFFER_MESSAGE_LOOP
	
	/*int j = 1;
	START_APPLICATION_REJECTION_MESSAGE_LOOP
		     CU_ASSERT_EQUAL(application_rejection_message->firm_id, ID);
			if(j == 1)
		        CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 6, 1e-3);
			if(j == 2)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 7, 1e-3);
			j++;
	FINISH_APPLICATION_REJECTION_MESSAGE_LOOP*/
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 2: more applicants than vacancies -> rejection message*/
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_1_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/		
			
	VACANCIES = 5;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	
	

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_application, sizeof(m_job_application));
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
    	    
    rc = MB_Create(&b_job_offer, sizeof(m_job_offer));
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
    	    	        	    
    	    	        	  
	    rc = MB_Create(&b_application_rejection, sizeof(m_application_rejection));
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
    	    
    	    
   
	
	/***** Messages: pre-conditions **********************************/
    add_job_application_message(1,ID,REGION_ID,1,1.0);
    add_job_application_message(2,ID,REGION_ID,2,2.0);
    add_job_application_message(3,ID,REGION_ID,3,3.0);
    add_job_application_message(4,ID,REGION_ID,4,4.0);
    add_job_application_message(5,ID,REGION_ID,5,5.0);
    add_job_application_message(6,ID,REGION_ID,5,5.0);
    add_job_application_message(7,ID,REGION_ID,5,5.0);
    
    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_application, &i_job_application);
			
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
	
	
	
	 
	/***** Function evaluation ***************************************/
		Firm_read_job_applications_send_job_offer_or_rejection();
	
	
	
	
	rc = MB_Iterator_Create(b_job_offer, &i_job_offer);
				
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
		

	rc = MB_Iterator_Create(b_application_rejection, &i_application_rejection);
					
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
			
	
	
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
			
	
	START_JOB_OFFER_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_offer_message->firm_id, ID);
		 CU_ASSERT_EQUAL(job_offer_message->region_id, REGION_ID);
		 
		 if(job_offer_message->worker_id == 1)
		 {
			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 1, 1e-3);
			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 1.0, 1e-3);
		 }
		 if(job_offer_message->worker_id == 2)
 		 {
 			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 2, 1e-3);
 			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 2.0, 1e-3);
 		 }
		 if(job_offer_message->worker_id == 3)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 3, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 3.0, 1e-3);
		 }
		 if(job_offer_message->worker_id == 4)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 4, 1e-3);
			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 4.0, 1e-3);
		 }
		 if(job_offer_message->worker_id == 5)
		 {
			 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 5, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 5.0, 1e-3);
		 }
		 if(job_offer_message->worker_id == 6)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 6, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 5.0, 1e-3);
		 }
		 if(job_offer_message->worker_id == 7)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->worker_id, 7, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer_message->wage_offer, 5.0, 1e-3);
		 }
		 
	FINISH_JOB_OFFER_MESSAGE_LOOP
	
	
	START_APPLICATION_REJECTION_MESSAGE_LOOP
		     CU_ASSERT_EQUAL(application_rejection_message->firm_id, ID);
			if(application_rejection_message->worker_id == 1)
		        CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 1, 1e-3);
			if(application_rejection_message->worker_id == 2)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 2, 1e-3);
			if(application_rejection_message->worker_id == 3)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 3, 1e-3);
			if(application_rejection_message->worker_id == 4)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 4, 1e-3);
			if(application_rejection_message->worker_id == 5)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 5, 1e-3);
			if(application_rejection_message->worker_id == 6)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 6, 1e-3);
			if(application_rejection_message->worker_id == 7)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection_message->worker_id, 7, 1e-3);
			
	FINISH_APPLICATION_REJECTION_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 0:*/
void unittest_Firm_read_job_responses()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	VACANCIES = 10;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	NO_EMPLOYEES = 10;
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
	
	reset_employee_array(&EMPLOYEES);
		    add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
			add_employee(&EMPLOYEES,10,1,1.0,5,5.0);

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_acceptance, sizeof(m_job_acceptance));
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
	
	/***** Messages: pre-conditions **********************************/
    add_job_acceptance_message(11,ID,REGION_ID,1,1.0);
    add_job_acceptance_message(12,ID,REGION_ID,2,2.0);
    add_job_acceptance_message(13,ID,REGION_ID,3,3.0);
    add_job_acceptance_message(14,ID,REGION_ID,4,4.0);
    add_job_acceptance_message(15,ID,REGION_ID,5,5.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_acceptance, &i_job_acceptance);
			
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
	    	    
    /***** Function evaluation ***************************************/
	Firm_read_job_responses();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 15, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 3, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 5, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.size, 15, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[10].id, 11, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[10].wage, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[10].general_skill, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[10].specific_skill, 1.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[11].id, 12, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[11].wage, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[11].general_skill, 2, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[11].specific_skill, 2.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[12].id, 13, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[12].wage, 3.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[12].general_skill, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[12].specific_skill, 3.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[13].id, 14, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[13].wage, 4.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[13].general_skill, 4, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[13].specific_skill, 4.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[14].id, 15, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[14].wage, 5.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[14].general_skill, 5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[14].specific_skill, 5.0, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: only different values*/
void unittest_Firm_read_job_responses_1_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	VACANCIES = 5;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	NO_EMPLOYEES = 5;
	NO_EMPLOYEES_SKILL_1 = 1;
	NO_EMPLOYEES_SKILL_2 = 1;
	NO_EMPLOYEES_SKILL_3 = 1;
	NO_EMPLOYEES_SKILL_4 = 1;
	NO_EMPLOYEES_SKILL_5 = 1;
	
	reset_employee_array(&EMPLOYEES);
		    add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
			

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_acceptance, sizeof(m_job_acceptance));
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
	
	/***** Messages: pre-conditions **********************************/
    add_job_acceptance_message(2,ID,REGION_ID,1,1.0);
    add_job_acceptance_message(4,ID,REGION_ID,1,2.0);
    add_job_acceptance_message(6,ID,REGION_ID,1,3.0);
    add_job_acceptance_message(8,ID,REGION_ID,1,4.0);
    add_job_acceptance_message(10,ID,REGION_ID,1,5.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_acceptance, &i_job_acceptance);
			
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
	    	    
    /***** Function evaluation ***************************************/
	Firm_read_job_responses();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 10, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 6, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.size, 10, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[5].id, 2, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[6].id, 4, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[7].id, 6, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[8].id, 8, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[9].id, 10, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}




/*CASE 0: 10 employees 5 quittings*/
void unittest_Firm_read_job_quitting()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	NO_EMPLOYEES = 10;
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
	
	VACANCIES = 0;
		
	reset_employee_array(&EMPLOYEES);
		add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_quitting, sizeof(m_quitting));
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
	
	/***** Messages: pre-conditions **********************************/
    add_quitting_message(1,ID);
    add_quitting_message(3,ID);
    add_quitting_message(5,ID);
    add_quitting_message(7,ID);
    add_quitting_message(9,ID);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_quitting, &i_quitting);
			
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
	    	    
    /***** Function evaluation ***************************************/
	Firm_read_job_quitting();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[0].id, 2, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[1].id, 4, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[2].id, 6, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[3].id, 8, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[4].id, 10, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.size, 5, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 1: 10 employees 10 quittings*/
void unittest_Firm_read_job_quitting_1_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	NO_EMPLOYEES = 10;
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
	
	VACANCIES = 0;
		
	reset_employee_array(&EMPLOYEES);
		add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_quitting, sizeof(m_quitting));
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
	
	/***** Messages: pre-conditions **********************************/
    add_quitting_message(1,ID);
    add_quitting_message(2,ID);
    add_quitting_message(3,ID);
    add_quitting_message(4,ID);
    add_quitting_message(5,ID);
    add_quitting_message(6,ID);
    add_quitting_message(7,ID);
    add_quitting_message(8,ID);
    add_quitting_message(9,ID);
    add_quitting_message(10,ID);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_quitting, &i_quitting);
			
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
	    	    
    /***** Function evaluation ***************************************/
	Firm_read_job_quitting();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 10, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.size, 0, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}




void unittest_Firm_update_wage_offer()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	VACANCIES = 10;
	MIN_VACANCY = 2;
	WAGE_UPDATE = 0.1;
	WAGE_OFFER = 1.0;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	
	    	    
    /***** Function evaluation ***************************************/
	Firm_update_wage_offer();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER, 1.1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_1, 1.1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_2, 2.2, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_3, 3.3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_4, 4.4, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_5, 5.5, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0:*/
void unittest_Firm_send_vacancies_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	VACANCIES = 5;
	
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_vacancies2, sizeof(m_vacancies2));
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
    	    
    /***** Function evaluation ***************************************/
    Firm_send_vacancies_2();
	
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_vacancies2, &i_vacancies2);
			
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
	    	    
    
    
    /***** Variables: Memory post-conditions *****/
	

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i=1;
	
	START_VACANCIES2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(vacancies2_message->firm_id, ID);
		 CU_ASSERT_EQUAL(vacancies2_message->region_id, REGION_ID);
	     CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_vacancies, 5, 1e-3);
	     if(i==1)
	     {
	    	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 1);
	    	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, WAGE_OFFER_FOR_SKILL_1, 1e-3);
	     }
	     if(i==2)
	     {
	     	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 2);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, WAGE_OFFER_FOR_SKILL_2, 1e-3);
	     }
	     if(i==3)
	     {
	     	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 3);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, WAGE_OFFER_FOR_SKILL_3, 1e-3);
	     }
	     if(i==4)
	     {
	     	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 4);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, WAGE_OFFER_FOR_SKILL_4, 1e-3);
	     }
	     if(i==5)
	     {
	     	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 5);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, WAGE_OFFER_FOR_SKILL_5, 1e-3);
	     }
	     i++;
	     
	     
	FINISH_VACANCIES2_MESSAGE_LOOP
	
	
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 1: only different values*/
void unittest_Firm_send_vacancies_2_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	VACANCIES = 10;
	
	WAGE_OFFER_FOR_SKILL_1 = 11.0;
	WAGE_OFFER_FOR_SKILL_2 = 21.0;
	WAGE_OFFER_FOR_SKILL_3 = 31.0;
	WAGE_OFFER_FOR_SKILL_4 = 41.0;
	WAGE_OFFER_FOR_SKILL_5 = 51.0;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_vacancies2, sizeof(m_vacancies2));
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
    	    
    /***** Function evaluation ***************************************/
    Firm_send_vacancies_2();
	
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_vacancies2, &i_vacancies2);
			
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
	    	    
    
    
    /***** Variables: Memory post-conditions *****/
	

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i=1;
	
	START_VACANCIES2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(vacancies2_message->firm_id, ID);
		 CU_ASSERT_EQUAL(vacancies2_message->region_id, REGION_ID);
	     CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_vacancies, 10, 1e-3);
	     if(i==1)
	     {
	    	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 1);
	    	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, 11.0, 1e-3);
	     }
	     if(i==2)
	     {
	     	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 2);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, 21.0, 1e-3);
	     }
	     if(i==3)
	     {
	     	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 3);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, 31.0, 1e-3);
	     }
	     if(i==4)
	     {
	     	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 4);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, 41.0, 1e-3);
	     }
	     if(i==5)
	     {
	     	 CU_ASSERT_EQUAL(vacancies2_message->skill_group, 5);
	     	 CU_ASSERT_DOUBLE_EQUAL(vacancies2_message->firm_wage_offer, 51.0, 1e-3);
	     }
	     i++;
	     
	     
	FINISH_VACANCIES2_MESSAGE_LOOP
	
	
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0: same number of vacancies and applicants*/
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/		
			
	VACANCIES = 5;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	
	

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_application2, sizeof(m_job_application2));
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
    	    
    rc = MB_Create(&b_job_offer2, sizeof(m_job_offer2));
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
    	    	        	    
    	    	        	  
	    rc = MB_Create(&b_application_rejection2, sizeof(m_application_rejection2));
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
    	    
    	    
   
	
	/***** Messages: pre-conditions **********************************/
    add_job_application2_message(1,ID,REGION_ID,1,1.0);
    add_job_application2_message(2,ID,REGION_ID,2,2.0);
    add_job_application2_message(3,ID,REGION_ID,3,3.0);
    add_job_application2_message(4,ID,REGION_ID,4,4.0);
    add_job_application2_message(5,ID,REGION_ID,5,5.0);
    
    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_application2, &i_job_application2);
			
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
	
	
	
	 
	/***** Function evaluation ***************************************/
		Firm_read_job_applications_send_job_offer_or_rejection_2();
	
	
	
	
	rc = MB_Iterator_Create(b_job_offer2, &i_job_offer2);
				
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
		

	rc = MB_Iterator_Create(b_application_rejection2, &i_application_rejection2);
					
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
			
	
	
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i = 1;		
	
	START_JOB_OFFER2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_offer2_message->firm_id, ID);
		 CU_ASSERT_EQUAL(job_offer2_message->region_id, REGION_ID);
		 
		 if(i == 1)
		 {
			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 5, 1e-3);
			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 5.0, 1e-3);
		 }
		 if(i == 2)
 		 {
 			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 4, 1e-3);
 			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 4.0, 1e-3);
 		 }
		 if(i == 3)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 3, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 3.0, 1e-3);
		 }
		 if(i == 4)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 2, 1e-3);
			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 2.0, 1e-3);
		 }
		 if(i == 5)
		 {
			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 1, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 1.0, 1e-3);
		 }
		 i++;
	FINISH_JOB_OFFER2_MESSAGE_LOOP
	
	/*int j = 1;
	START_APPLICATION_REJECTION2_MESSAGE_LOOP
		     CU_ASSERT_EQUAL(application_rejection2_message->firm_id, ID);
			if(j == 1)
		        CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 6, 1e-3);
			if(j == 2)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 7, 1e-3);
			j++;
	FINISH_APPLICATION_REJECTION2_MESSAGE_LOOP*/
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: same number of vacancies and applicants*/
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_2_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/		
			
	VACANCIES = 5;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	
	

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_application2, sizeof(m_job_application2));
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
    	    
    rc = MB_Create(&b_job_offer2, sizeof(m_job_offer2));
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
    	    	        	    
    	    	        	  
	    rc = MB_Create(&b_application_rejection2, sizeof(m_application_rejection2));
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
    	    
    	    
   
	
	/***** Messages: pre-conditions **********************************/
    add_job_application2_message(1,ID,REGION_ID,1,1.0);
    add_job_application2_message(2,ID,REGION_ID,2,2.0);
    add_job_application2_message(3,ID,REGION_ID,3,3.0);
    add_job_application2_message(4,ID,REGION_ID,4,4.0);
    add_job_application2_message(5,ID,REGION_ID,5,5.0);
    add_job_application2_message(6,ID,REGION_ID,1,1.0);
    add_job_application2_message(7,ID,REGION_ID,1,1.0);
    
    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_application2, &i_job_application2);
			
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
	
	
	
	 
	/***** Function evaluation ***************************************/
		Firm_read_job_applications_send_job_offer_or_rejection_2();
	
	
	
	
	rc = MB_Iterator_Create(b_job_offer2, &i_job_offer2);
				
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
		

	rc = MB_Iterator_Create(b_application_rejection2, &i_application_rejection2);
					
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
			
	
	
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i = 1;		
	
	START_JOB_OFFER2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_offer2_message->firm_id, ID);
		 CU_ASSERT_EQUAL(job_offer2_message->region_id, REGION_ID);
		 
		 if(job_offer2_message->worker_id == 1)
		 {
			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 1, 1e-3);
			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 1.0, 1e-3);
		 }
		 if(job_offer2_message->worker_id == 2)
 		 {
 			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 2, 1e-3);
 			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 2.0, 1e-3);
 		 }
		 if(job_offer2_message->worker_id == 3)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 3, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 3.0, 1e-3);
		 }
		 if(job_offer2_message->worker_id == 4)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 4, 1e-3);
			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 4.0, 1e-3);
		 }
		 if(job_offer2_message->worker_id == 5)
		 {
			 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 5, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 5.0, 1e-3);
		 }
		 if(job_offer2_message->worker_id == 6)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 6, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 1.0, 1e-3);
		 }
		 if(job_offer2_message->worker_id == 7)
		 {
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 7, 1e-3);
		 	 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 1.0, 1e-3);
		 }
	FINISH_JOB_OFFER2_MESSAGE_LOOP
	
	
	START_APPLICATION_REJECTION2_MESSAGE_LOOP
		     CU_ASSERT_EQUAL(application_rejection2_message->firm_id, ID);
			if(application_rejection2_message->worker_id == 1)
		        CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 1, 1e-3);
			if(application_rejection2_message->worker_id == 2)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 2, 1e-3);
			if(application_rejection2_message->worker_id == 3)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 3, 1e-3);
			if(application_rejection2_message->worker_id == 4)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 4, 1e-3);
			if(application_rejection2_message->worker_id == 5)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 5, 1e-3);
			if(application_rejection2_message->worker_id == 6)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 6, 1e-3);
			if(application_rejection2_message->worker_id == 7)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 7, 1e-3);
			
	FINISH_APPLICATION_REJECTION2_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 2: only one applicant*/
void unittest_Firm_read_job_applications_send_job_offer_or_rejection_2_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/		
			
	VACANCIES = 5;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	
	

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_application2, sizeof(m_job_application2));
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
    	    
    rc = MB_Create(&b_job_offer2, sizeof(m_job_offer2));
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
    	    	        	    
    	    	        	  
	    rc = MB_Create(&b_application_rejection2, sizeof(m_application_rejection2));
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
    	    
    	    
   
	
	/***** Messages: pre-conditions **********************************/
    add_job_application2_message(1,ID,REGION_ID,1,1.0);
    
    
    
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_application2, &i_job_application2);
			
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
	
	
	
	 
	/***** Function evaluation ***************************************/
		Firm_read_job_applications_send_job_offer_or_rejection_2();
	
	
	
	
	rc = MB_Iterator_Create(b_job_offer2, &i_job_offer2);
				
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
		

	rc = MB_Iterator_Create(b_application_rejection2, &i_application_rejection2);
					
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
			
	
	
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
			
	
	START_JOB_OFFER2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_offer2_message->firm_id, ID);
		 CU_ASSERT_EQUAL(job_offer2_message->region_id, REGION_ID);
		 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->worker_id, 1, 1e-3);
		 CU_ASSERT_DOUBLE_EQUAL(job_offer2_message->wage_offer, 1.0, 1e-3);	 
	FINISH_JOB_OFFER2_MESSAGE_LOOP
	
	/*int j = 1;
	START_APPLICATION_REJECTION2_MESSAGE_LOOP
		     CU_ASSERT_EQUAL(application_rejection2_message->firm_id, ID);
			if(j == 1)
		        CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 6, 1e-3);
			if(j == 2)
				CU_ASSERT_DOUBLE_EQUAL(application_rejection2_message->worker_id, 7, 1e-3);
			j++;
	FINISH_APPLICATION_REJECTION2_MESSAGE_LOOP*/
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*CASE 0:*/
void unittest_Firm_read_job_responses_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	VACANCIES = 10;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	NO_EMPLOYEES = 10;
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
	
	reset_employee_array(&EMPLOYEES);
		    add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
			add_employee(&EMPLOYEES,10,1,1.0,5,5.0);

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_acceptance2, sizeof(m_job_acceptance2));
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
	
	/***** Messages: pre-conditions **********************************/
    add_job_acceptance2_message(11,ID,REGION_ID,1,1.0);
    add_job_acceptance2_message(12,ID,REGION_ID,2,2.0);
    add_job_acceptance2_message(13,ID,REGION_ID,3,3.0);
    add_job_acceptance2_message(14,ID,REGION_ID,4,4.0);
    add_job_acceptance2_message(15,ID,REGION_ID,5,5.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_acceptance2, &i_job_acceptance2);
			
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
	    	    
    /***** Function evaluation ***************************************/
	Firm_read_job_responses_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 15, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 3, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 5, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.size, 15, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[10].id, 11, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[10].wage, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[10].general_skill, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[10].specific_skill, 1.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[11].id, 12, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[11].wage, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[11].general_skill, 2, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[11].specific_skill, 2.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[12].id, 13, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[12].wage, 3.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[12].general_skill, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[12].specific_skill, 3.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[13].id, 14, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[13].wage, 4.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[13].general_skill, 4, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[13].specific_skill, 4.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[14].id, 15, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[14].wage, 5.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[14].general_skill, 5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[14].specific_skill, 5.0, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 1:*/
void unittest_Firm_read_job_responses_2_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	VACANCIES = 10;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	NO_EMPLOYEES = 0;
	NO_EMPLOYEES_SKILL_1 = 0;
	NO_EMPLOYEES_SKILL_2 = 0;
	NO_EMPLOYEES_SKILL_3 = 0;
	NO_EMPLOYEES_SKILL_4 = 0;
	NO_EMPLOYEES_SKILL_5 = 0;
	
	reset_employee_array(&EMPLOYEES);
		    //add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
			

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_job_acceptance2, sizeof(m_job_acceptance2));
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
	
	/***** Messages: pre-conditions **********************************/
    add_job_acceptance2_message(11,ID,REGION_ID,1,1.0);
    add_job_acceptance2_message(12,ID,REGION_ID,2,2.0);
    add_job_acceptance2_message(13,ID,REGION_ID,3,3.0);
    add_job_acceptance2_message(14,ID,REGION_ID,4,4.0);
    add_job_acceptance2_message(15,ID,REGION_ID,5,5.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_job_acceptance2, &i_job_acceptance2);
			
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
	    	    
    /***** Function evaluation ***************************************/
	Firm_read_job_responses_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 1, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 5, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.size, 5, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[0].id, 11, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[0].wage, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[0].general_skill, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[0].specific_skill, 1.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[1].id, 12, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[1].wage, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[1].general_skill, 2, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[1].specific_skill, 2.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[2].id, 13, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[2].wage, 3.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[2].general_skill, 3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[2].specific_skill, 3.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[3].id, 14, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[3].wage, 4.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[3].general_skill, 4, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[3].specific_skill, 4.0, 1e-3);
	
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[4].id, 15, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[4].wage, 5.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[4].general_skill, 5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEES.array[4].specific_skill, 5.0, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}




/*CASE 0: 10 employees 5 quittings*/
void unittest_Firm_read_job_quitting_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	NO_EMPLOYEES = 10;
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
	
	VACANCIES = 0;
		
	reset_employee_array(&EMPLOYEES);
		add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_quitting2, sizeof(m_quitting2));
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
	
	/***** Messages: pre-conditions **********************************/
    add_quitting2_message(1,ID);
    add_quitting2_message(3,ID);
    add_quitting2_message(5,ID);
    add_quitting2_message(7,ID);
    add_quitting2_message(9,ID);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_quitting2, &i_quitting2);
			
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
	    	    
    /***** Function evaluation ***************************************/
	Firm_read_job_quitting_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 5, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: 10 employees 10 quittings*/
void unittest_Firm_read_job_quitting_2_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	NO_EMPLOYEES = 10;
	NO_EMPLOYEES_SKILL_1 = 2;
	NO_EMPLOYEES_SKILL_2 = 2;
	NO_EMPLOYEES_SKILL_3 = 2;
	NO_EMPLOYEES_SKILL_4 = 2;
	NO_EMPLOYEES_SKILL_5 = 2;
	
	VACANCIES = 0;
		
	reset_employee_array(&EMPLOYEES);
		add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
		add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
		add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
		add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
		add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
		add_employee(&EMPLOYEES,10,1,1.0,5,5.0);

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_quitting2, sizeof(m_quitting2));
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
	
	/***** Messages: pre-conditions **********************************/
    add_quitting2_message(1,ID);
    add_quitting2_message(2,ID);
    add_quitting2_message(3,ID);
    add_quitting2_message(4,ID);
    add_quitting2_message(5,ID);
    add_quitting2_message(6,ID);
    add_quitting2_message(7,ID);
    add_quitting2_message(8,ID);
    add_quitting2_message(9,ID);
    add_quitting2_message(10,ID);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_quitting2, &i_quitting2);
			
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
	    	    
    /***** Function evaluation ***************************************/
	Firm_read_job_quitting_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_1, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_2, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_3, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_4, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(NO_EMPLOYEES_SKILL_5, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(VACANCIES, 10, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0:*/
void unittest_Firm_update_wage_offer_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	VACANCIES = 10;
	MIN_VACANCY =2;
	WAGE_UPDATE = 0.1;
	WAGE_OFFER = 1.0;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	reset_employee_array(&EMPLOYEES);
			add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
			add_employee(&EMPLOYEES,10,1,1.0,5,5.0);
	
	NO_EMPLOYEES = 10;
	
	
	    	    
    /***** Function evaluation ***************************************/
	Firm_update_wage_offer_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER, 1.1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_1, 1.1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_2, 2.2, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_3, 3.3, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_4, 4.4, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_5, 5.5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_G_SKILL, 3, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: no increase of wage offer*/
void unittest_Firm_update_wage_offer_2_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	VACANCIES = 1;
	MIN_VACANCY =2;
	WAGE_UPDATE = 0.1;
	WAGE_OFFER = 1.0;
	WAGE_OFFER_FOR_SKILL_1 = 1.0;
	WAGE_OFFER_FOR_SKILL_2 = 2.0;
	WAGE_OFFER_FOR_SKILL_3 = 3.0;
	WAGE_OFFER_FOR_SKILL_4 = 4.0;
	WAGE_OFFER_FOR_SKILL_5 = 5.0;
	
	reset_employee_array(&EMPLOYEES);
			add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,3,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,4,1,1.0,2,2.0);
			add_employee(&EMPLOYEES,5,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,6,1,1.0,3,3.0);
			add_employee(&EMPLOYEES,7,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,8,1,1.0,4,4.0);
			add_employee(&EMPLOYEES,9,1,1.0,5,5.0);
			add_employee(&EMPLOYEES,10,1,1.0,5,5.0);
	
	NO_EMPLOYEES = 10;
	
	
	    	    
    /***** Function evaluation ***************************************/
	Firm_update_wage_offer_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_1, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_2, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_3, 3.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_4, 4.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE_OFFER_FOR_SKILL_5, 5.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(AVERAGE_G_SKILL, 3, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0:*/
void unittest_Firm_compute_mean_wage_specific_skills()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	reset_employee_array(&EMPLOYEES);
			add_employee(&EMPLOYEES,1,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,2,1,1.0,1,1.0);
			add_employee(&EMPLOYEES,3,1,2.0,2,2.0);
			add_employee(&EMPLOYEES,4,1,2.0,2,2.0);
			add_employee(&EMPLOYEES,5,1,3.0,3,3.0);
			add_employee(&EMPLOYEES,6,1,3.0,3,3.0);
			add_employee(&EMPLOYEES,7,1,4.0,4,4.0);
			add_employee(&EMPLOYEES,8,1,4.0,4,4.0);
			add_employee(&EMPLOYEES,9,1,5.0,5,5.0);
			add_employee(&EMPLOYEES,10,1,5.0,5,5.0);
		
	NO_EMPLOYEES = 10;
	WAGE_OFFER = 1.0;
	
	
	    	    
    /***** Function evaluation ***************************************/
	Firm_compute_mean_wage_specific_skills();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(MEAN_WAGE, 3.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(MEAN_SPECIFIC_SKILLS, 3.0, 1e-3);

    /***** Messages: Message post-conditions *****/
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*CASE 1: Different values*/
void unittest_Firm_compute_mean_wage_specific_skills_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Firm_agent();
	
    /***** Variables: Memory pre-conditions **************************/

	reset_employee_array(&EMPLOYEES);
			add_employee(&EMPLOYEES,1,1,2.0,1,2.0);
			add_employee(&EMPLOYEES,2,1,2.0,1,2.0);
			add_employee(&EMPLOYEES,3,1,2.0,2,2.0);
			add_employee(&EMPLOYEES,4,1,2.0,2,2.0);
			add_employee(&EMPLOYEES,5,1,2.0,3,2.0);
			add_employee(&EMPLOYEES,6,1,2.0,3,2.0);
			add_employee(&EMPLOYEES,7,1,2.0,4,2.0);
			add_employee(&EMPLOYEES,8,1,2.0,4,2.0);
			add_employee(&EMPLOYEES,9,1,2.0,5,2.0);
			add_employee(&EMPLOYEES,10,1,2.0,5,2.0);
		
	NO_EMPLOYEES = 10;
	WAGE_OFFER = 1.0;
	
	
	    	    
    /***** Function evaluation ***************************************/
	Firm_compute_mean_wage_specific_skills();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(MEAN_WAGE, 2.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(MEAN_SPECIFIC_SKILLS, 2.0, 1e-3);

    /***** Messages: Message post-conditions *****/
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Firm_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}