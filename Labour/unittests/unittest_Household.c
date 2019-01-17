#include <CUnit/Basic.h>
//For trunk model
#include "../../header.h"
#include "../../Household_agent_header.h"
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

/*CASE 0*/
void unittest_Household_receive_wage()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	reset_double_array(&LAST_INCOME);
		add_double(&LAST_INCOME,1.0);
		add_double(&LAST_INCOME,2.0);
		add_double(&LAST_INCOME,3.0);
		add_double(&LAST_INCOME,4.0);
		
	PAYMENT_ACCOUNT = 2.0;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_wage_payment, sizeof(m_wage_payment));
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
    add_wage_payment_message(1,ID,1.0,1.0,1.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_wage_payment, &i_wage_payment);
			
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
	Household_receive_wage();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(MEAN_INCOME, 2.5, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 3.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_PRODUCTIVITY_EMPLOYER, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MEAN_SPECIFIC_SKILLS_EMPLOYER, 1.0, 1e-3);
	

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: Different values*/
void unittest_Household_receive_wage_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	reset_double_array(&LAST_INCOME);
		add_double(&LAST_INCOME,5.0);
		add_double(&LAST_INCOME,5.0);
		add_double(&LAST_INCOME,7.0);
		add_double(&LAST_INCOME,7.0);
		
	PAYMENT_ACCOUNT = 0.0;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_wage_payment, sizeof(m_wage_payment));
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
    add_wage_payment_message(1,ID,1.0,1.0,1.0);
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_wage_payment, &i_wage_payment);
			
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
	Household_receive_wage();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(MEAN_INCOME, 5.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(PAYMENT_ACCOUNT, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_PRODUCTIVITY_EMPLOYER, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(CURRENT_MEAN_SPECIFIC_SKILLS_EMPLOYER, 1.0, 1e-3);
	

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0:*/
void unittest_Household_update_specific_skills()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	SPECIFIC_SKILL = 1.0;
	CURRENT_PRODUCTIVITY_EMPLOYER = 2.0;
	GENERAL_SKILL = 2;
	CURRENT_MEAN_SPECIFIC_SKILLS_EMPLOYER = 1.0;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_specific_skill_update, sizeof(m_specific_skill_update));
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
    	    Household_update_specific_skills();
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_specific_skill_update, &i_specific_skill_update);
			
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
	CU_ASSERT_DOUBLE_EQUAL(SPECIFIC_SKILL, 1.04239671930143, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_SPECIFIC_SKILL_UPDATE_MESSAGE_LOOP
	     
		 CU_ASSERT_EQUAL(specific_skill_update_message->id, ID);
		 CU_ASSERT_EQUAL(specific_skill_update_message->firm_id, EMPLOYEE_FIRM_ID);
	     CU_ASSERT_DOUBLE_EQUAL(specific_skill_update_message->specific_skills, 1.04239671930143, 1e-3);
	FINISH_SPECIFIC_SKILL_UPDATE_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*CASE 1: Different Values*/
void unittest_Household_update_specific_skills_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	SPECIFIC_SKILL = 3.0;
	CURRENT_PRODUCTIVITY_EMPLOYER = 5.0;
	GENERAL_SKILL = 5;
	CURRENT_MEAN_SPECIFIC_SKILLS_EMPLOYER = 1.0;

	/***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_specific_skill_update, sizeof(m_specific_skill_update));
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
    	    Household_update_specific_skills();
    	    
    /***** Message: Adding message iterators ***************************************/
	rc = MB_Iterator_Create(b_specific_skill_update, &i_specific_skill_update);
			
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
	CU_ASSERT_DOUBLE_EQUAL(SPECIFIC_SKILL, 3.31820716949257, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_SPECIFIC_SKILL_UPDATE_MESSAGE_LOOP
	     
		 CU_ASSERT_EQUAL(specific_skill_update_message->id, ID);
		 CU_ASSERT_EQUAL(specific_skill_update_message->firm_id, EMPLOYEE_FIRM_ID);
	     CU_ASSERT_DOUBLE_EQUAL(specific_skill_update_message->specific_skills, 3.31820716949257, 1e-3);
	FINISH_SPECIFIC_SKILL_UPDATE_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



void unittest_Household_read_firing_messages()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	EMPLOYEE_FIRM_ID = 1;
	LAST_LABOUR_INCOME = 2.0;
	WAGE = 1.0;
	ON_THE_JOB_SEARCH = 1;
	DAY_OF_MONTH_RECEIVE_INCOME = 2;

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
	
	/***** Messages: pre-conditions **********************************/
    add_firing_message(EMPLOYEE_FIRM_ID,ID);
    	    
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_firing_messages();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(EMPLOYEE_FIRM_ID, -1, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(LAST_LABOUR_INCOME, 1.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(WAGE, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(ON_THE_JOB_SEARCH, 0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(DAY_OF_MONTH_RECEIVE_INCOME, 0, 1e-3);

  
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0: 6 Vacancies messages 4 applications*/
void unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	GENERAL_SKILL = 3;
	SPECIFIC_SKILL = 1.0;
	REGION_ID = 1;
	REGION_COST = 1.0;
	COMMUTING_COSTS_PRICE_LEVEL_WEIGHT = 0.5;
	WAGE_RESERVATION = 2.0;
	NUMBER_APPLICATIONS = 5;
	
	reset_int_array(&NEIGHBORING_REGION_IDS);
		add_int(&NEIGHBORING_REGION_IDS,2);

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
	
	/***** Messages: pre-conditions **********************************/
    add_vacancies_message(1,1,35,3,3.4);
    add_vacancies_message(2,1,35,3,3.1);
    add_vacancies_message(3,1,35,3,3.5);
    add_vacancies_message(4,1,35,3,1.0);
    add_vacancies_message(5,2,35,3,3.7);
    add_vacancies_message(6,2,35,3,2.1);
    	    
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
	    	    
    /***** Function evaluation ***************************************/
	Household_UNEMPLOYED_read_job_vacancies_and_send_applications();
	
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
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i = 1;
	START_JOB_APPLICATION_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_application_message->worker_id, ID);
		 CU_ASSERT_EQUAL(job_application_message->region_id, REGION_ID);
		 CU_ASSERT_EQUAL(job_application_message->general_skill, 3);
	     CU_ASSERT_DOUBLE_EQUAL(job_application_message->specific_skill, 1.0, 1e-3);
	     if(i==1)
	    	 CU_ASSERT_EQUAL(job_application_message->firm_id, 3);
	     
	     if(i==2)
	    	 CU_ASSERT_EQUAL(job_application_message->firm_id, 1);
	     
	     if(i==3)
	    	 CU_ASSERT_EQUAL(job_application_message->firm_id, 5);
	     
	     if(i==4)
	     	    	 CU_ASSERT_EQUAL(job_application_message->firm_id, 2);
	    	 
	     i++;
	FINISH_JOB_APPLICATION_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: 6 Vacancies messages; 4 applications sent; NUMBER_APPLICATIONS 5*/
void unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	GENERAL_SKILL = 3;
	SPECIFIC_SKILL = 1.0;
	REGION_ID = 1;
	REGION_COST = 1.0;
	COMMUTING_COSTS_PRICE_LEVEL_WEIGHT = 0.5;
	WAGE_RESERVATION = 2.0;
	NUMBER_APPLICATIONS = 1;
	
	reset_int_array(&NEIGHBORING_REGION_IDS);
		add_int(&NEIGHBORING_REGION_IDS,2);

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
	
	/***** Messages: pre-conditions **********************************/
    add_vacancies_message(1,1,35,3,1.4);
    add_vacancies_message(2,1,35,3,1.1);
    add_vacancies_message(3,1,35,3,1.5);
    add_vacancies_message(4,1,35,3,5.0);
    add_vacancies_message(5,2,35,3,3.7);
    add_vacancies_message(6,2,35,3,1.8);
    	    
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
	    	    
    /***** Function evaluation ***************************************/
	Household_UNEMPLOYED_read_job_vacancies_and_send_applications();
	
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
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i = 1;
	START_JOB_APPLICATION_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_application_message->worker_id, ID);
		 CU_ASSERT_EQUAL(job_application_message->region_id, REGION_ID);
		 CU_ASSERT_EQUAL(job_application_message->general_skill, 3);
	     CU_ASSERT_DOUBLE_EQUAL(job_application_message->specific_skill, 1.0, 1e-3);
	     CU_ASSERT_DOUBLE_EQUAL(job_application_message->firm_id, 4,1);
	     
	     
	FINISH_JOB_APPLICATION_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 0: choose offer from domestic region*/
void unittest_Household_read_job_offers_send_response()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	GENERAL_SKILL = 3;
	SPECIFIC_SKILL = 1.0;
	REGION_ID = 1;
	REGION_COST = 1.0;
	COMMUTING_COSTS_PRICE_LEVEL_WEIGHT = 0.5;
	WAGE_RESERVATION = 1.0;
	WAGE = 1.0;
	ON_THE_JOB_SEARCH = 0;
	DAY = 3;
	
	;
		
	reset_int_array(&NEIGHBORING_REGION_IDS);
			add_int(&NEIGHBORING_REGION_IDS,2);

	/***** Messages: initialize message boards **********************************/
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
    add_job_offer_message(1,ID,1,1.0);
    add_job_offer_message(2,ID,1,2.0);
    add_job_offer_message(3,ID,1,3.0);
    add_job_offer_message(4,ID,2,3.0);
    add_job_offer_message(5,ID,2,2.0);
    add_job_offer_message(6,ID,2,1.0);
    	    
    /***** Message: Adding message iterators ***************************************/
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_job_offers_send_response();
	
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
    
    /***** Variables: Memory post-conditions *****/
		CU_ASSERT_DOUBLE_EQUAL(WAGE, 3.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(WAGE_RESERVATION, 3.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EMPLOYEE_FIRM_ID, 3, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EMPLOYER_REGION_ID, 1, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(DAY_OF_MONTH_RECEIVE_INCOME, 3, 1e-3);
		

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_JOB_ACCEPTANCE_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_acceptance_message->worker_id, ID);
	 	 CU_ASSERT_EQUAL(job_acceptance_message->firm_id, 3);
	 	 CU_ASSERT_EQUAL(job_acceptance_message->region_id, 1);
	 	 CU_ASSERT_EQUAL(job_acceptance_message->general_skill, 3);
	     CU_ASSERT_DOUBLE_EQUAL(job_acceptance_message->specific_skill, 1.0, 1e-3);
	FINISH_JOB_ACCEPTANCE_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 1: choose offer from neighboring region*/
void unittest_Household_read_job_offers_send_response_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	GENERAL_SKILL = 3;
	SPECIFIC_SKILL = 1.0;
	REGION_ID = 1;
	REGION_COST = 1.0;
	COMMUTING_COSTS_PRICE_LEVEL_WEIGHT = 0.5;
	WAGE_RESERVATION = 1.0;
	WAGE = 1.0;
	ON_THE_JOB_SEARCH = 0;
	DAY = 3;
	
	;
		
	reset_int_array(&NEIGHBORING_REGION_IDS);
			add_int(&NEIGHBORING_REGION_IDS,2);

	/***** Messages: initialize message boards **********************************/
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
    add_job_offer_message(1,ID,1,1.0);
    add_job_offer_message(2,ID,1,2.0);
    add_job_offer_message(3,ID,1,3.0);
    add_job_offer_message(4,ID,2,5.0);
    add_job_offer_message(5,ID,2,2.0);
    add_job_offer_message(6,ID,2,1.0);
    	    
    /***** Message: Adding message iterators ***************************************/
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_job_offers_send_response();
	
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
    
    /***** Variables: Memory post-conditions *****/
		CU_ASSERT_DOUBLE_EQUAL(WAGE, 5, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(WAGE_RESERVATION, 4.5, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EMPLOYEE_FIRM_ID, 4, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EMPLOYER_REGION_ID, 2, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(DAY_OF_MONTH_RECEIVE_INCOME, 3, 1e-3);
		

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_JOB_ACCEPTANCE_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_acceptance_message->worker_id, ID);
	 	 CU_ASSERT_EQUAL(job_acceptance_message->firm_id, 4);
	 	 CU_ASSERT_EQUAL(job_acceptance_message->region_id, 1);
	 	 CU_ASSERT_EQUAL(job_acceptance_message->general_skill, 3);
	     CU_ASSERT_DOUBLE_EQUAL(job_acceptance_message->specific_skill, 1.0, 1e-3);
	FINISH_JOB_ACCEPTANCE_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0: WAGE_RESERVATION higher than 1*/
void unittest_Household_read_application_rejection_update_wage_reservation()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	WAGE_RESERVATION = 2.0;
	WAGE_RESERVATION_UPDATE = 0.1;

	/***** Messages: initialize message boards **********************************/
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
    add_application_rejection_message(1,ID);
    add_application_rejection_message(2,ID);
    	    
    /***** Message: Adding message iterators ***************************************/
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_application_rejection_update_wage_reservation();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_RESERVATION, 1.8, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 1: WAGE_RESERVATION higher than 1*/
void unittest_Household_read_application_rejection_update_wage_reservation_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	WAGE_RESERVATION = 1.0;
	WAGE_RESERVATION_UPDATE = 0.1;

	/***** Messages: initialize message boards **********************************/
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
    add_application_rejection_message(1,ID);
    add_application_rejection_message(2,ID);
    	    
    /***** Message: Adding message iterators ***************************************/
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_application_rejection_update_wage_reservation();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_RESERVATION, 1.0, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}





/*CASE 0: 6 Vacancies messages 4 applications*/
void unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	GENERAL_SKILL = 3;
	SPECIFIC_SKILL = 1.0;
	REGION_ID = 1;
	REGION_COST = 1.0;
	COMMUTING_COSTS_PRICE_LEVEL_WEIGHT = 0.5;
	WAGE_RESERVATION = 2.0;
	NUMBER_APPLICATIONS = 5;
	
	reset_int_array(&NEIGHBORING_REGION_IDS);
		add_int(&NEIGHBORING_REGION_IDS,2);

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
	
	/***** Messages: pre-conditions **********************************/
    add_vacancies2_message(1,1,35,3,3.4);
    add_vacancies2_message(2,1,35,3,3.1);
    add_vacancies2_message(3,1,35,3,3.5);
    add_vacancies2_message(4,1,35,3,1.0);
    add_vacancies2_message(5,2,35,3,3.7);
    add_vacancies2_message(6,2,35,3,2.1);
    	    
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
	    	    
    /***** Function evaluation ***************************************/
	Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2();
	
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
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	int i = 1;
	START_JOB_APPLICATION2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_application2_message->worker_id, ID);
		 CU_ASSERT_EQUAL(job_application2_message->region_id, REGION_ID);
		 CU_ASSERT_EQUAL(job_application2_message->general_skill, 3);
	     CU_ASSERT_DOUBLE_EQUAL(job_application2_message->specific_skill, 1.0, 1e-3);
	     if(i==1)
	    	 CU_ASSERT_EQUAL(job_application2_message->firm_id, 3);
	     
	     if(i==2)
	    	 CU_ASSERT_EQUAL(job_application2_message->firm_id, 1);
	     
	     if(i==3)
	    	 CU_ASSERT_EQUAL(job_application2_message->firm_id, 5);
	     
	     if(i==4)
	     	    	 CU_ASSERT_EQUAL(job_application2_message->firm_id, 2);
	    	 
	     i++;
	FINISH_JOB_APPLICATION2_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 1: 6 Vacancies messages; 4 applications sent; NUMBER_APPLICATIONS 5*/
void unittest_Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	GENERAL_SKILL = 3;
	SPECIFIC_SKILL = 1.0;
	REGION_ID = 1;
	REGION_COST = 1.0;
	COMMUTING_COSTS_PRICE_LEVEL_WEIGHT = 0.5;
	WAGE_RESERVATION = 2.0;
	NUMBER_APPLICATIONS = 1;
	
	reset_int_array(&NEIGHBORING_REGION_IDS);
		add_int(&NEIGHBORING_REGION_IDS,2);

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
	
	/***** Messages: pre-conditions **********************************/
    add_vacancies2_message(1,1,35,3,1.4);
    add_vacancies2_message(2,1,35,3,1.1);
    add_vacancies2_message(3,1,35,3,1.5);
    add_vacancies2_message(4,1,35,3,5.0);
    add_vacancies2_message(5,2,35,3,3.7);
    add_vacancies2_message(6,2,35,3,1.8);
    	    
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
	    	    
    /***** Function evaluation ***************************************/
	Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2();
	
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
    
    /***** Variables: Memory post-conditions *****/
//	CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /***** Messages: Message post-conditions *****/
	//start a reading loop

	START_JOB_APPLICATION2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_application2_message->worker_id, ID);
		 CU_ASSERT_EQUAL(job_application2_message->region_id, REGION_ID);
		 CU_ASSERT_EQUAL(job_application2_message->general_skill, 3);
	     CU_ASSERT_DOUBLE_EQUAL(job_application2_message->specific_skill, 1.0, 1e-3);
	     CU_ASSERT_DOUBLE_EQUAL(job_application2_message->firm_id, 4,1);
	     
	     
	FINISH_JOB_APPLICATION2_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 0: choose offer from domestic region*/
void unittest_Household_read_job_offers_send_response_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	GENERAL_SKILL = 3;
	SPECIFIC_SKILL = 1.0;
	REGION_ID = 1;
	REGION_COST = 1.0;
	COMMUTING_COSTS_PRICE_LEVEL_WEIGHT = 0.5;
	WAGE_RESERVATION = 1.0;
	WAGE = 1.0;
	ON_THE_JOB_SEARCH = 0;
	DAY = 3;
	
	;
		
	reset_int_array(&NEIGHBORING_REGION_IDS);
			add_int(&NEIGHBORING_REGION_IDS,2);

	/***** Messages: initialize message boards **********************************/
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
    add_job_offer2_message(1,ID,1,1.0);
    add_job_offer2_message(2,ID,1,2.0);
    add_job_offer2_message(3,ID,1,3.0);
    add_job_offer2_message(4,ID,2,3.0);
    add_job_offer2_message(5,ID,2,2.0);
    add_job_offer2_message(6,ID,2,1.0);
    	    
    /***** Message: Adding message iterators ***************************************/
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_job_offers_send_response_2();
	
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
    
    /***** Variables: Memory post-conditions *****/
		CU_ASSERT_DOUBLE_EQUAL(WAGE, 3.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(WAGE_RESERVATION, 3.0, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EMPLOYEE_FIRM_ID, 3, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EMPLOYER_REGION_ID, 1, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(DAY_OF_MONTH_RECEIVE_INCOME, 3, 1e-3);
		

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_JOB_ACCEPTANCE2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_acceptance2_message->worker_id, ID);
	 	 CU_ASSERT_EQUAL(job_acceptance2_message->firm_id, 3);
	 	 CU_ASSERT_EQUAL(job_acceptance2_message->region_id, 1);
	 	 CU_ASSERT_EQUAL(job_acceptance2_message->general_skill, 3);
	     CU_ASSERT_DOUBLE_EQUAL(job_acceptance2_message->specific_skill, 1.0, 1e-3);
	FINISH_JOB_ACCEPTANCE2_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 1: choose offer from neighboring region*/
void unittest_Household_read_job_offers_send_response_2_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	
	GENERAL_SKILL = 3;
	SPECIFIC_SKILL = 1.0;
	REGION_ID = 1;
	REGION_COST = 1.0;
	COMMUTING_COSTS_PRICE_LEVEL_WEIGHT = 0.5;
	WAGE_RESERVATION = 1.0;
	WAGE = 1.0;
	ON_THE_JOB_SEARCH = 0;
	DAY = 3;
	
	;
		
	reset_int_array(&NEIGHBORING_REGION_IDS);
			add_int(&NEIGHBORING_REGION_IDS,2);

	/***** Messages: initialize message boards **********************************/
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
    add_job_offer2_message(1,ID,1,1.0);
    add_job_offer2_message(2,ID,1,2.0);
    add_job_offer2_message(3,ID,1,3.0);
    add_job_offer2_message(4,ID,2,5.0);
    add_job_offer2_message(5,ID,2,2.0);
    add_job_offer2_message(6,ID,2,1.0);
    	    
    /***** Message: Adding message iterators ***************************************/
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_job_offers_send_response_2();
	
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
    
    /***** Variables: Memory post-conditions *****/
		CU_ASSERT_DOUBLE_EQUAL(WAGE, 5, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(WAGE_RESERVATION, 4.5, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EMPLOYEE_FIRM_ID, 4, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(EMPLOYER_REGION_ID, 2, 1e-3);
		CU_ASSERT_DOUBLE_EQUAL(DAY_OF_MONTH_RECEIVE_INCOME, 3, 1e-3);
		

    /***** Messages: Message post-conditions *****/
	//start a reading loop
	START_JOB_ACCEPTANCE2_MESSAGE_LOOP
	     CU_ASSERT_EQUAL(job_acceptance2_message->worker_id, ID);
	 	 CU_ASSERT_EQUAL(job_acceptance2_message->firm_id, 4);
	 	 CU_ASSERT_EQUAL(job_acceptance2_message->region_id, 1);
	 	 CU_ASSERT_EQUAL(job_acceptance2_message->general_skill, 3);
	     CU_ASSERT_DOUBLE_EQUAL(job_acceptance2_message->specific_skill, 1.0, 1e-3);
	FINISH_JOB_ACCEPTANCE2_MESSAGE_LOOP
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*CASE 0: WAGE_RESERVATION higher than 1*/
void unittest_Household_read_application_rejection_update_wage_reservation_2()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	WAGE_RESERVATION = 2.0;
	WAGE_RESERVATION_UPDATE = 0.1;

	/***** Messages: initialize message boards **********************************/
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
    add_application_rejection2_message(1,ID);
    add_application_rejection2_message(2,ID);
    	    
    /***** Message: Adding message iterators ***************************************/
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_application_rejection_update_wage_reservation_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_RESERVATION, 1.8, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}



/*CASE 1: WAGE_RESERVATION higher than 1*/
void unittest_Household_read_application_rejection_update_wage_reservation_2_1()
{
	int rc;
	
    /************* At start of unit test, add one agent **************/
	unittest_init_Household_agent();
	
    /***** Variables: Memory pre-conditions **************************/
	WAGE_RESERVATION = 1.0;
	WAGE_RESERVATION_UPDATE = 0.1;

	/***** Messages: initialize message boards **********************************/
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
    add_application_rejection2_message(1,ID);
    add_application_rejection2_message(2,ID);
    	    
    /***** Message: Adding message iterators ***************************************/
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
	    	    
    /***** Function evaluation ***************************************/
	Household_read_application_rejection_update_wage_reservation_2();
    
    /***** Variables: Memory post-conditions *****/
	CU_ASSERT_DOUBLE_EQUAL(WAGE_RESERVATION, 1.0, 1e-3);

    /***** Messages: Message post-conditions *****/
	
	
    /************* At end of unit test, free the agent **************/
	unittest_free_Household_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

