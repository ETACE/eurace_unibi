#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../../header.h"
#include "../../Eurostat_agent_header.h"
#include "../../my_library_header.h"

/************Eurostat Role: Statistical Office ********************************/

/************ Unit tests ********************************/
/*
 * \fn: void unittest_Eurostat_reset_data()
 * \brief: Unit test for: Eurostat_reset_data.
 * Status: Tested OK
 */
void unittest_Eurostat_reset_data()
{   
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    FLAME_environment_variable_total_regions = 2;

    add_firm_data(&REGION_FIRM_DATA,
            1,100,0,                   //3 region_id, no_firms, vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity
    
    add_firm_data(&REGION_FIRM_DATA,
            2,200,0,                   //3 region_id, no_firms, vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    add_household_data(&REGION_HOUSEHOLD_DATA,
            1,
            10,0,0,0,0,0,            //no_households
            0,0,0,0,0,0,
            0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,1.0,1.0,1.0,1.0,1.0);

    add_household_data(&REGION_HOUSEHOLD_DATA,
            2,
            20,0,0,0,0,0,            //no_households
            0,0,0,0,0,0,
            0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,1.0,1.0,1.0,1.0,1.0);

    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/
   
    /***** Function evaluation ***************************************/
    Eurostat_reset_data();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(REGION_FIRM_DATA.array[0].no_firms, 0);
    CU_ASSERT_EQUAL(REGION_FIRM_DATA.array[1].no_firms, 0);
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[0].no_households, 0);
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[1].no_households, 0);   
    
    /***** Messages: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_compute_mean_price()
 * \brief: Unit test for: Eurostat_compute_mean_price.
 * Status: Tested OK
 */
void unittest_Eurostat_compute_mean_price()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/

    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firm_send_data, sizeof(m_firm_send_data));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firm_send_data' board\n");
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
/*  add_firm_send_data_message(ID, REGION_ID, VACANCIES, NO_EMPLOYEES,
    NO_EMPLOYEES_SKILL_1, NO_EMPLOYEES_SKILL_2, NO_EMPLOYEES_SKILL_3, NO_EMPLOYEES_SKILL_4, NO_EMPLOYEES_SKILL_5, 
    MEAN_WAGE, MEAN_SPECIFIC_SKILLS,
    AVERAGE_S_SKILL_OF_1, AVERAGE_S_SKILL_OF_2, AVERAGE_S_SKILL_OF_3, AVERAGE_S_SKILL_OF_4, AVERAGE_S_SKILL_OF_5,
    CUM_REVENUE, CAPITAL_COSTS, NET_EARNINGS, TOTAL_DEBT, TOTAL_ASSETS, EQUITY,
    PRICE, PRICE_LAST_MONTH, TOTAL_SUPPLY, CUM_TOTAL_SOLD_QUANTITY, OUTPUT, PLANNED_OUTPUT, AGE, FIRM_PRODUCTIVITY, FIRM_PRODUCTIVITY_PROGRESS);
*/  
    //Fixture:
    //PRICE=1;
    //TOTAL_SUPPLY=10;

    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,0, 0.0,0.0);
    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 2.0,0,10.0,0,0,0,0, 0.0,0.0);
    
    /***** Message: Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_firm_send_data, &i_firm_send_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'firm_send_data'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is locked\n");
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
    Eurostat_compute_mean_price();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(PRICE_INDEX, 1.5, 1e-3);

    /***** Messages: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_read_firm_data()
 * \brief: Unit test for: Eurostat_read_firm_data.
 * Status: Tested OK
 */
void unittest_Eurostat_read_firm_data()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    add_firm_data(&REGION_FIRM_DATA,
            1,0,0,                   //3 region_id, no_firms, vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    add_firm_data(&REGION_FIRM_DATA,
            2,0,0,                   //3 region_id, no_firms, vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    
    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firm_send_data, sizeof(m_firm_send_data));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firm_send_data' board\n");
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
/*  add_firm_send_data_message(ID, REGION_ID, VACANCIES, NO_EMPLOYEES,
    NO_EMPLOYEES_SKILL_1, NO_EMPLOYEES_SKILL_2, NO_EMPLOYEES_SKILL_3, NO_EMPLOYEES_SKILL_4, NO_EMPLOYEES_SKILL_5, 
    MEAN_WAGE, MEAN_SPECIFIC_SKILLS,
    AVERAGE_S_SKILL_OF_1, AVERAGE_S_SKILL_OF_2, AVERAGE_S_SKILL_OF_3, AVERAGE_S_SKILL_OF_4, AVERAGE_S_SKILL_OF_5,
    CUM_REVENUE, CAPITAL_COSTS, NET_EARNINGS, TOTAL_DEBT, TOTAL_ASSETS, EQUITY,
    PRICE, PRICE_LAST_MONTH, TOTAL_SUPPLY, CUM_TOTAL_SOLD_QUANTITY, OUTPUT, PLANNED_OUTPUT, AGE, FIRM_PRODUCTIVITY, FIRM_PRODUCTIVITY_PROGRESS);
*/  
    //Fixture:
    //PRICE=1;
    //TOTAL_SUPPLY=10;

    add_firm_send_data_message(1,1,100,50, 10,10,10,10,10, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,0, 0.0,0.0);
    add_firm_send_data_message(2,1,100,100, 20,20,20,20,20, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 2.0,0,10.0,0,0,0,0, 0.0,0.0);
            
    add_firm_send_data_message(3,2,300,150, 30,30,30,30,30, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,0, 0.0,0.0);
    add_firm_send_data_message(4,2,300,200, 40,40,40,40,40, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 2.0,0,10.0,0,0,0,0, 0.0,0.0);

    /***** Message: Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_firm_send_data, &i_firm_send_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'firm_send_data'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is locked\n");
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
    Eurostat_read_firm_data();
    
    /***** Variables: Memory post-conditions *****/

    CU_ASSERT_EQUAL(REGION_FIRM_DATA.array[0].no_firms, 2); 
    CU_ASSERT_EQUAL(REGION_FIRM_DATA.array[1].no_firms, 2);
    
    CU_ASSERT_EQUAL(REGION_FIRM_DATA.array[0].vacancies, 200);
    CU_ASSERT_EQUAL(REGION_FIRM_DATA.array[1].vacancies, 600);
    CU_ASSERT_EQUAL(NO_VACANCIES, 800);
    
    CU_ASSERT_EQUAL(REGION_FIRM_DATA.array[0].employees, 150);
    CU_ASSERT_EQUAL(REGION_FIRM_DATA.array[1].employees, 350);
    CU_ASSERT_EQUAL(NO_EMPLOYEES, 500);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_compute_region_firm_data()
 * \brief: Unit test for: Eurostat_compute_region_firm_data.
 * Status: Tested OK
 */
void unittest_Eurostat_compute_region_firm_data()
{   
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    add_firm_data(&REGION_FIRM_DATA,
            1,100,0,                   //3 region_id, no_firms, vacancies 
            10,0,0,0,0,0,             //6 employees, employees_skill_1 5
            100.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage, average_wage_skill_1 5
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    add_firm_data(&REGION_FIRM_DATA,
            2,200,0,                   //3 region_id, no_firms, vacancies 
            20,0,0,0,0,0,             //6 employees, employees_skill_1 5
            200.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage, average_wage_skill_1 5
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/
  
    /***** Function evaluation ***************************************/
    Eurostat_compute_region_firm_data();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[0].average_wage, 10.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[1].average_wage, 10.0, 1e-3);
    
    /***** Messages: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_compute_global_firm_data()
 * \brief: Unit test for: Eurostat_compute_global_firm_data.
 * Status: Tested OK
 */
void unittest_Eurostat_compute_global_firm_data()
{   
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    FIRM_AVERAGE_WAGE = 100.0;
    NO_EMPLOYEES = 10;
    
    /***** Messages: initialize message boards **********************************/

    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/
        
    /***** Function evaluation ***************************************/
    Eurostat_compute_global_firm_data();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(FIRM_AVERAGE_WAGE, 10.0, 1e-3);

    /***** Messages: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_read_household_data()
 * \brief: Unit test for: Eurostat_read_household_data.
 * Status: Tested OK
 */
void unittest_Eurostat_read_household_data()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    add_household_data(&REGION_HOUSEHOLD_DATA,
            1,
            0,0,0,0,0,0,             //no_households
            0,0,0,0,0,0,
            0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,1.0,1.0,1.0,1.0,1.0);

    add_household_data(&REGION_HOUSEHOLD_DATA,
            2,
            0,0,0,0,0,0,             //no_households
            0,0,0,0,0,0,
            0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,1.0,1.0,1.0,1.0,1.0);

    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_household_send_data, sizeof(m_household_send_data));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'household_send_data' board\n");
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
    
    //add_household_send_data_message(int household_id, int region_id, int general_skill, int employment_status, double wage, double specific_skill)        
    add_household_send_data_message(0,1,1,1, 0.0, 0.0);
    add_household_send_data_message(0,1,2,-1, 0.0, 0.0);
    
    add_household_send_data_message(0,2,1,1, 0.0, 0.0);
    add_household_send_data_message(0,2,2,-1, 0.0, 0.0);
    
    /***** Message: Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_household_send_data, &i_household_send_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'household_send_data'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'household_send_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'household_send_data' board is locked\n");
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
    Eurostat_read_household_data();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(NUM_HOUSEHOLDS, 4);
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[0].no_households, 2);
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[1].no_households, 2);
    
    CU_ASSERT_EQUAL(UNEMPLOYED, 2);
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[0].unemployed, 1);
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[1].unemployed, 1);
    
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[0].no_households_skill_1, 1);
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[1].no_households_skill_1, 1);
    
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[0].no_households_skill_2, 1);
    CU_ASSERT_EQUAL(REGION_HOUSEHOLD_DATA.array[1].no_households_skill_2, 1);

    /***** Messages: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_compute_region_household_data()
 * \brief: Unit test for: Eurostat_compute_region_household_data.
 * Status: Tested OK
 */
void unittest_Eurostat_compute_region_household_data()
{   
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    add_household_data(&REGION_HOUSEHOLD_DATA,
            1,                       //region_id
            10,0,0,0,0,0,            //no_households, no_households_skill_1 5
            10,0,0,0,0,0,            //employed, employed_skill_1 5
            0,                       //unemployed
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,1.0,1.0,1.0,1.0,1.0);

    add_household_data(&REGION_HOUSEHOLD_DATA,
            2,
            20,0,0,0,0,0,            //no_households
            0,0,0,0,0,0,             //employed, employed_skill_1 5
            20,                      //unemployed
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,1.0,1.0,1.0,1.0,1.0);

    /***** Messages: initialize message boards **********************************/
    
    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/
            
    /***** Function evaluation ***************************************/
    Eurostat_compute_region_household_data();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(REGION_HOUSEHOLD_DATA.array[0].unemployment_rate, 0.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_HOUSEHOLD_DATA.array[1].unemployment_rate, 100.0, 1e-3);
    
    /***** Messages: Message post-conditions *****/
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_compute_global_household_data()
 * \brief: Unit test for: Eurostat_compute_global_household_data.
 * Status: Tested OK
 */
void unittest_Eurostat_compute_global_household_data()
{   
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    EMPLOYED = 75;
    NUM_HOUSEHOLDS = 100;
    AVERAGE_WAGE = 7500.0;
    /***** Messages: initialize message boards **********************************/
    
    /***** Messages: pre-conditions **********************************/
            
    /***** Message: Adding message iterators ***************************************/
            
    /***** Function evaluation ***************************************/
    Eurostat_compute_global_household_data();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(UNEMPLOYMENT_RATE, 25.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(AVERAGE_WAGE, 100.0, 1e-3);
    
    /***** Messages: Message post-conditions *****/

    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_calc_macro_data()
 * \brief: Unit test for: Eurostat_calc_macro_data.
 * Status: Tested OK
 */
void unittest_Eurostat_calc_macro_data()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    MONTHLY_SOLD_QUANTITY=0.0;
    MONTHLY_REVENUE=0.0;
    LABOUR_SHARE_RATIO=0.0;
    
    //Allocate memory
/*  firm_data(REGION_ID, FIRMS, VACANCIES, NO_EMPLOYEES,
    NO_EMPLOYEES_SKILL_1, NO_EMPLOYEES_SKILL_2, NO_EMPLOYEES_SKILL_3, NO_EMPLOYEES_SKILL_4, NO_EMPLOYEES_SKILL_5, 
    AVERAGE_WAGE, AVERAGE_WAGE_SKILL_1, AVERAGE_WAGE_SKILL_2, AVERAGE_WAGE_SKILL_3, AVERAGE_WAGE_SKILL_4, AVERAGE_WAGE_SKILL_5, 
    AVERAGE_S_SKILLS, AVERAGE_S_SKILL_1, AVERAGE_S_SKILL_2, AVERAGE_S_SKILL_3, AVERAGE_S_SKILL_4, AVERAGE_S_SKILL_5,
    GDP, TOTAL_EARNINGS, TOTAL_DEBT, TOTAL_ASSETS, TOTAL_EQUITY,
    AVERAGE_DEBT_EARNINGS_RATIO, AVERAGE_DEBT_EQUITY_RATIO, LABOR_SHARE_RATIO,
    MONTHLY_SOLD_QUANTITY, MONTHLY_OUTPUT, MONTHLY_REVENUE, MONTHLY_PLANNED_OUTPUT,
    GDP, CPI, CPI_LAST_MONTH
    no_firm_births, no_firm_deaths);
*/  
    add_firm_data(&REGION_FIRM_DATA,
            1,0,0,                   //3 region_id -> vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    add_firm_data(&REGION_FIRM_DATA,
            2,0,0,                   //3 region_id -> vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firm_send_data, sizeof(m_firm_send_data));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firm_send_data' board\n");
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
    //Set 4 firms in 2 regions, using these vars:
    //  firm_send_data_message->region_id;
    //  firm_send_data_message->cum_revenue;
    //  firm_send_data_message->capital_costs;
    //  firm_send_data_message->cum_total_sold_quantity;

/*  add_firm_send_data_message(ID, REGION_ID, VACANCIES, NO_EMPLOYEES,
    NO_EMPLOYEES_SKILL_1, NO_EMPLOYEES_SKILL_2, NO_EMPLOYEES_SKILL_3, NO_EMPLOYEES_SKILL_4, NO_EMPLOYEES_SKILL_5, 
    MEAN_WAGE, MEAN_SPECIFIC_SKILLS,
    AVERAGE_S_SKILL_OF_1, AVERAGE_S_SKILL_OF_2, AVERAGE_S_SKILL_OF_3, AVERAGE_S_SKILL_OF_4, AVERAGE_S_SKILL_OF_5,
    CUM_REVENUE, CAPITAL_COSTS, NET_EARNINGS, TOTAL_DEBT, TOTAL_ASSETS, EQUITY,
    PRICE, PRICE_LAST_MONTH, TOTAL_SUPPLY, CUM_TOTAL_SOLD_QUANTITY, OUTPUT, PLANNED_OUTPUT, AGE, FIRM_PRODUCTIVITY, FIRM_PRODUCTIVITY_PROGRESS);
*/  
    //Fixture:
    //NO_EMPLOYEES=10
    //MEAN_WAGE=1
    //NET_EARNINGS=100
    //labour_share=1*10/100 = 0.10

    add_firm_send_data_message(1,1,0, 10, 0,0,0,0,0, 0,0, 1,0,0,0,0, 100,100,100,0,0,0, 0,0,0,1000,0,0,0, 0.0,0.0);
    add_firm_send_data_message(2,1,0, 10, 0,0,0,0,0, 0,0, 1,0,0,0,0, 100,100,100,0,0,0, 0,0,0,1000,0,0,0, 0.0,0.0);
    add_firm_send_data_message(3,2,0, 10, 0,0,0,0,0, 0,0, 1,0,0,0,0, 10,10,100,0,0,0,   0,0,0,100, 0,0,0, 0.0,0.0);
    add_firm_send_data_message(4,2,0, 10, 0,0,0,0,0, 0,0, 1,0,0,0,0, 10,10,100,0,0,0,   0,0,0,100, 0,0,0, 0.0,0.0);

    /***** Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_firm_send_data, &i_firm_send_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is locked\n");
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
    Eurostat_calc_macro_data();
    
    /***** Variables: Memory post-conditions *****/
    //CU_ASSERT_DOUBLE_EQUAL(, result, 1e-3);
    
    //After the message loop, check the aggregate in both regions
    //GDP=cum_revenue+capital_costs
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[0].gdp, 400.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[0].monthly_sold_quantity, 2000.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[0].monthly_revenue, 200.0, 1e-3);
    
    //GDP=cum_revenue+capital_costs
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[1].gdp, 40.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[1].monthly_sold_quantity, 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[1].monthly_revenue, 20.0, 1e-3);
    
    //And the economy-wide totals
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_SOLD_QUANTITY, 2200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_REVENUE, 220.0, 1e-3);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_calc_price_index()
 * \brief: Unit test for: Eurostat_calc_price_index.
 * Status: Tested OK
 */
void unittest_Eurostat_calc_price_index()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/

    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firm_send_data, sizeof(m_firm_send_data));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firm_send_data' board\n");
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
//    add_<message_name>_message();
            
    /***** Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_firm_send_data, &i_firm_send_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is locked\n");
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
    Eurostat_calc_price_index();
    
    /***** Variables: Memory post-conditions *****/
//  CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest_Eurostat_calc_firm_population()
 * \brief: Unit test for: Eurostat_calc_firm_population.
 * Status: PASSED
 * Fixture: We set up a matrix with row(0)=1, row(1)=2, 
 * FIRM_AGE_DISTRIBUTION[]=1
 * FIRM_AGE_DISTRIBUTION_MULTIPERIOD[]=0
 * TEST: incoming msgs: 1 msg with age 0;
 * Post: FIRM_AGE_DISTRIBUTION_MULTIPERIOD matrix with
 * FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]=3
 * FIRM_AGE_DISTRIBUTION_MULTIPERIOD[299]=2 (all firms older than 300)
 */
void unittest_Eurostat_calculate_data()
{
    int i,j,rc;
	int MAX_FIRM_AGE=301;
	int MAX_SURVIVAL_PERIODS=12;
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/

        for (i=0; i<MAX_FIRM_AGE; i++) //MAX_FIRM_AGE=300
        {
				FIRM_AGE_DISTRIBUTION[i]=1;//this is reset to 0 in the evaluated function
	        for (j=0; j<MAX_SURVIVAL_PERIODS; j++) //MAX_FIRM_AGE=300
    	    {
				FIRM_AGE_DISTRIBUTION_MULTIPERIOD[j*MAX_FIRM_AGE+i] = i;
			}
		}

    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firm_send_data, sizeof(m_firm_send_data));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firm_send_data' board\n");
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
/*  add_firm_send_data_message(ID, REGION_ID, VACANCIES, NO_EMPLOYEES,
    NO_EMPLOYEES_SKILL_1, NO_EMPLOYEES_SKILL_2, NO_EMPLOYEES_SKILL_3, NO_EMPLOYEES_SKILL_4, NO_EMPLOYEES_SKILL_5, 
    MEAN_WAGE, MEAN_SPECIFIC_SKILLS,
    AVERAGE_S_SKILL_OF_1, AVERAGE_S_SKILL_OF_2, AVERAGE_S_SKILL_OF_3, AVERAGE_S_SKILL_OF_4, AVERAGE_S_SKILL_OF_5,
    CUM_REVENUE, CAPITAL_COSTS, NET_EARNINGS, TOTAL_DEBT, TOTAL_ASSETS, EQUITY,
    PRICE, PRICE_LAST_MONTH, TOTAL_SUPPLY, CUM_TOTAL_SOLD_QUANTITY, OUTPUT, PLANNED_OUTPUT, AGE, FIRM_PRODUCTIVITY, FIRM_PRODUCTIVITY_PROGRESS);
*/  
    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,0, 0.0,0.0);

    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_firm_send_data, &i_firm_send_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is locked\n");
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
    Eurostat_calculate_data();
    
    /***** Variables: Memory post-conditions *****/
    //CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

	printf("\nFIRM_AGE_DISTRIBUTION[0]=%d\n", FIRM_AGE_DISTRIBUTION[0]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]);

	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0],1);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION[0],1);

    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_Eurostat_calc_firm_population()
 * \brief: Unit test for: Eurostat_calc_firm_population.
 * Status: PASSED
 * Fixture: We set up a matrix with row(0)=1, row(1)=2, 
 * FIRM_AGE_DISTRIBUTION[]=1
 * FIRM_AGE_DISTRIBUTION_MULTIPERIOD[]=0
 * TEST: incoming msgs: 3 msg with age 1; 2 with age 301
 * Post: FIRM_AGE_DISTRIBUTION_MULTIPERIOD matrix with
 * FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]=3
 * FIRM_AGE_DISTRIBUTION_MULTIPERIOD[299]=2 (all firms older than 300)
 */
void unittest1_Eurostat_calc_firm_population()
{
    int i,j,rc;
	int MY_MAX_FIRM_AGE=301;
	int MY_MAX_SURVIVAL_PERIODS=12;
    /************* At start of unit test, add one agent **************/

    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/

        for (i=0; i<MY_MAX_FIRM_AGE; i++) //MY_MAX_FIRM_AGE=301
        {
			FIRM_AGE_DISTRIBUTION[i]=1;  //this is reset to 0 in the evaluated function
	        for (j=0; j<MY_MAX_SURVIVAL_PERIODS; j++) //MY_MAX_FIRM_AGE=301
    	    {
				FIRM_AGE_DISTRIBUTION_MULTIPERIOD[j*MY_MAX_FIRM_AGE+i] = i;
			}
		}

    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_firm_send_data, sizeof(m_firm_send_data));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'firm_send_data' board\n");
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
/*  add_firm_send_data_message(ID, REGION_ID, VACANCIES, NO_EMPLOYEES,
    NO_EMPLOYEES_SKILL_1, NO_EMPLOYEES_SKILL_2, NO_EMPLOYEES_SKILL_3, NO_EMPLOYEES_SKILL_4, NO_EMPLOYEES_SKILL_5, 
    MEAN_WAGE, MEAN_SPECIFIC_SKILLS,
    AVERAGE_S_SKILL_OF_1, AVERAGE_S_SKILL_OF_2, AVERAGE_S_SKILL_OF_3, AVERAGE_S_SKILL_OF_4, AVERAGE_S_SKILL_OF_5,
    CUM_REVENUE, CAPITAL_COSTS, NET_EARNINGS, TOTAL_DEBT, TOTAL_ASSETS, EQUITY,
    PRICE, PRICE_LAST_MONTH, TOTAL_SUPPLY, CUM_TOTAL_SOLD_QUANTITY, OUTPUT, PLANNED_OUTPUT, AGE, FIRM_PRODUCTIVITY, FIRM_PRODUCTIVITY_PROGRESS);
*/  
    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,0, 0.0,0.0);

    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,1, 0.0,0.0);
    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,1, 0.0,0.0);
    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,1, 0.0,0.0);

    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,2, 0.0,0.0);
    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 1.0,0,10.0,0,0,0,2, 0.0,0.0);

    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 2.0,0,10.0,0,0,0,301, 0.0,0.0);
    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 2.0,0,10.0,0,0,0,301, 0.0,0.0);

    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 2.0,0,10.0,0,0,0,302, 0.0,0.0);
    add_firm_send_data_message(0,0,0,0, 0,0,0,0,0, 0,0, 0,0,0,0,0, 0,0,0,0,0,0, 2.0,0,10.0,0,0,0,302, 0.0,0.0);

    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_firm_send_data, &i_firm_send_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is locked\n");
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
    Eurostat_calc_firm_population();
    
    /***** Variables: Memory post-conditions *****/
    //CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

	printf("\nFIRM_AGE_DISTRIBUTION[0]=%d\n", FIRM_AGE_DISTRIBUTION[0]);
	printf("FIRM_AGE_DISTRIBUTION[1]=%d\n", FIRM_AGE_DISTRIBUTION[1]);
	printf("FIRM_AGE_DISTRIBUTION[2]=%d\n", FIRM_AGE_DISTRIBUTION[2]);
	printf("FIRM_AGE_DISTRIBUTION[300]=%d\n", FIRM_AGE_DISTRIBUTION[300]);

	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[1]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[1]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[2]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[2]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[299]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[299]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[300]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[300]);

	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0],1);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[1],3);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[2],2);

	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[300],4);

	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION[0],1);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION[1],3);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION[2],2);

	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION[300],4);
    
        for (i=0; i<MY_MAX_FIRM_AGE; i++) //MAX_FIRM_AGE=300
        {
				CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[i],FIRM_AGE_DISTRIBUTION[i]);
		}

    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest2_Eurostat_calc_firm_population()
 * \brief: Unit test for: Eurostat_calc_firm_population.
 * Status: PASSED
 * Fixture: We set up a matrix with row(0)=1, row(1)=2, FIRM_AGE_DISTRIBUTION[]=0.
 * Post: FIRM_AGE_DISTRIBUTION_MULTIPERIOD matrix with row(0)=0, row(1)=1.
 */
void unittest2_Eurostat_calc_firm_population()
{
    int rc, i,x, index;
	int MY_MAX_FIRM_AGE=301;
	int MY_MAX_SURVIVAL_PERIODS=12;

    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    //Setup a 0 age distribution
        for (i=0; i<MY_MAX_FIRM_AGE; i++) //MAX_FIRM_AGE=300
        {
				FIRM_AGE_DISTRIBUTION[i]=0;
		}

    //Setup the multiperiod age distribution, the previous age distribution is in the first row
        for (x=0; x<MY_MAX_SURVIVAL_PERIODS; x++) //MAX_SURVIVAL_PERIODS=12
        {
	        for (i=0; i<MY_MAX_FIRM_AGE; i++)//MAX_FIRM_AGE=300
	        {        
                index = x*MY_MAX_FIRM_AGE+i; 
				FIRM_AGE_DISTRIBUTION_MULTIPERIOD[index] = x+1;
			}
		}

	//Fixture: We set up a matrix with row(0)=1, row(1)=2.
	printf("\nFIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[300]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[300]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[301]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[301]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[601]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[601]);

    
    /***** Messages: pre-conditions **********************************/

    /***** Adding message iterators ***************************************/

    rc = MB_Iterator_Create(b_firm_send_data, &i_firm_send_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'firm_send_data' board is locked\n");
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
    Eurostat_calc_firm_population();
    
    /***** Variables: Memory post-conditions *****/
    //CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

	printf("\nFIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[300]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[300]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[301]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[301]);
	printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[601]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[601]);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0],0);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[300],0);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[301],1);
	CU_ASSERT_EQUAL(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[601],1);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest3_Eurostat_calc_firm_population()
 * \brief: Unit test for: Eurostat_calc_firm_population.
 * Status: PASSED
 * Fixture: We add messages to test if the parent function Eurostat_calculate_data() is correctly giving access to the MBs.
 * BANKRUPTCY_ILLIQUIDITY_MESSAGE
 * BANKRUPTCY_INSOLVENCY
 * Post: NO_FIRM_DEATHS==2;
 */
void unittest3_Eurostat_calc_firm_population()
{
    int rc, rc2;

    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
	 NO_FIRM_DEATHS=0;
    
    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_bankruptcy_illiquidity, sizeof(m_bankruptcy_illiquidity));
    rc = MB_Create(&b_bankruptcy_insolvency, sizeof(m_bankruptcy_insolvency));

    /***** Messages: pre-conditions **********************************/
	add_bankruptcy_illiquidity_message(1);
	add_bankruptcy_insolvency_message(2);

    /***** Adding message iterators ***************************************/
    rc = MB_Iterator_Create(b_bankruptcy_illiquidity, &i_bankruptcy_illiquidity);
    rc2 = MB_Iterator_Create(b_bankruptcy_insolvency, &i_bankruptcy_insolvency);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for '<message>'\n");
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
        
    /***** Function evaluation ***************************************/
//    Eurostat_calc_firm_population();
    Eurostat_calculate_data(); //The parent function

    /***** Variables: Memory post-conditions *****/
    //CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

	printf("\nNO_FIRM_DEATHS=%d\n", NO_FIRM_DEATHS);

	CU_ASSERT_EQUAL(NO_FIRM_DEATHS,2);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_calc_firm_survival_rates()
 * \brief: Unit test for: Eurostat_calc_firm_survival_rates.
 * Status: PASSED
 */
void unittest_Eurostat_calc_firm_survival_rates()
{
    int rc, i,x, index;
	int MY_MAX_FIRM_AGE=301;
	int MY_MAX_SURVIVAL_PERIODS=12;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
		//FIRM_AGE_DISTRIBUTION_MULTIPERIOD[x][i]==0
		//SURVIVAL_RATE_MULTIPERIOD[x][i]==0
        for (x=0; x<MY_MAX_SURVIVAL_PERIODS; x++) //MAX_SURVIVAL_PERIODS=12
        {
	        for (i=0; i<MY_MAX_FIRM_AGE; i++)//MAX_FIRM_AGE=300
	        {        
                index = x*MY_MAX_FIRM_AGE+i; 
				FIRM_AGE_DISTRIBUTION_MULTIPERIOD[index] = 0;
				SURVIVAL_RATE_MULTIPERIOD[index] = 0.0;
			}
		}
/*
		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0][9]=10; //10 firms age 10, now
		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[1][8]=20; //20 firms age 9, previously (1*300+8)
		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[2][7]=40; //40 firms age 8, 2 periods ago (2*300+7)
*/
		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[9]=10;    //10 firms age 10, now
		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[MY_MAX_FIRM_AGE+8]=20;  //20 firms age 9, previously
		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[2*MY_MAX_FIRM_AGE+7]=40;  //40 firms age 8, 2 periods ago
	    printf("\nFIRM_AGE_DISTRIBUTION_MULTIPERIOD[9]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[9]);
		printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[%d]=%d\n", MY_MAX_FIRM_AGE+8, FIRM_AGE_DISTRIBUTION_MULTIPERIOD[MY_MAX_FIRM_AGE+8]);
   		printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[%d]=%d\n", 2*MY_MAX_FIRM_AGE+7, FIRM_AGE_DISTRIBUTION_MULTIPERIOD[2*MY_MAX_FIRM_AGE+7]);

		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[10]=10;    //10 firms age 10, now
		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[MY_MAX_FIRM_AGE+9]=30;  //20 firms age 9, previously
		FIRM_AGE_DISTRIBUTION_MULTIPERIOD[2*MY_MAX_FIRM_AGE+8]=60;  //40 firms age 8, 2 periods ago
	    printf("\nFIRM_AGE_DISTRIBUTION_MULTIPERIOD[10]=%d\n", FIRM_AGE_DISTRIBUTION_MULTIPERIOD[10]);
		printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[%d]=%d\n", MY_MAX_FIRM_AGE+9, FIRM_AGE_DISTRIBUTION_MULTIPERIOD[MY_MAX_FIRM_AGE+9]);
   		printf("FIRM_AGE_DISTRIBUTION_MULTIPERIOD[%d]=%d\n", 2*MY_MAX_FIRM_AGE+8, FIRM_AGE_DISTRIBUTION_MULTIPERIOD[2*MY_MAX_FIRM_AGE+8]);

//SURVIVAL_RATE_MULTIPERIOD[0][9]=0.00;
//SURVIVAL_RATE_MULTIPERIOD[1][8]=0.50; //1-period survival rate of age 10 firms: 10/20 (1*300+8)
//SURVIVAL_RATE_MULTIPERIOD[2][7]=0.25; //2-period survival rate of age 10 firms: 10/40 (2*300+7)

//SURVIVAL_RATE_MULTIPERIOD[308]=0.50;
//SURVIVAL_RATE_MULTIPERIOD[607]=0.25;

    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_calc_firm_survival_rates();
    
    /***** Variables: Memory post-conditions *****/
//      CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
    printf("\nSURVIVAL_RATE_MULTIPERIOD[0][9]=%2.2f\n", SURVIVAL_RATE_MULTIPERIOD[9]);
	printf("SURVIVAL_RATE_MULTIPERIOD[1][%d]=%2.2f\n", MY_MAX_FIRM_AGE+9, SURVIVAL_RATE_MULTIPERIOD[MY_MAX_FIRM_AGE+9]);
	printf("SURVIVAL_RATE_MULTIPERIOD[2][%d]=%2.2f\n", 2*MY_MAX_FIRM_AGE+9, SURVIVAL_RATE_MULTIPERIOD[2*MY_MAX_FIRM_AGE+9]);

    printf("\nSURVIVAL_RATE_MULTIPERIOD[0][10]=%2.2f\n", SURVIVAL_RATE_MULTIPERIOD[10]);
	printf("SURVIVAL_RATE_MULTIPERIOD[1][%d]=%2.2f\n", MY_MAX_FIRM_AGE+10, SURVIVAL_RATE_MULTIPERIOD[MY_MAX_FIRM_AGE+10]);
	printf("SURVIVAL_RATE_MULTIPERIOD[2][%d]=%2.2f\n", 2*MY_MAX_FIRM_AGE+10, SURVIVAL_RATE_MULTIPERIOD[2*MY_MAX_FIRM_AGE+10]);

	CU_ASSERT_DOUBLE_EQUAL(SURVIVAL_RATE_MULTIPERIOD[9],0.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(SURVIVAL_RATE_MULTIPERIOD[MY_MAX_FIRM_AGE+9],0.50, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(SURVIVAL_RATE_MULTIPERIOD[2*MY_MAX_FIRM_AGE+9],0.25, 1e-3);

	CU_ASSERT_DOUBLE_EQUAL(SURVIVAL_RATE_MULTIPERIOD[10],0.0, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(SURVIVAL_RATE_MULTIPERIOD[MY_MAX_FIRM_AGE+10],0.333, 1e-3);
	CU_ASSERT_DOUBLE_EQUAL(SURVIVAL_RATE_MULTIPERIOD[2*MY_MAX_FIRM_AGE+10],0.166, 1e-3);

    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_Eurostat_store_history_monthly()
 * \brief: Unit test for: Eurostat_store_history_monthly.
 * Test: history storage and shifting of economy-wide macro data
 * Status: Tested OK
 */
void unittest1_Eurostat_store_history_monthly()
{
    int k;
    double var, result;
    //PRINT_LOG =0;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    for (k=1;k<=13;k++)
    {
        HISTORY_MONTHLY[k].cpi = (double) k;
        //printf("\n HISTORY_MONTHLY[%d].cpi=%f\n", k, HISTORY_MONTHLY[k].cpi);
    }
    CPI=0.0;
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_store_history_monthly();
    
    /***** Variables: Memory post-conditions *****/
    for (k=1;k<13;k++)
    {
        var = HISTORY_MONTHLY[k].cpi;
        result = (double) (k-1);

        //printf("\n HISTORY_MONTHLY[%d].cpi=%f\n", k, HISTORY_MONTHLY[k].cpi);
        //printf("\n k=%d, var=%f, result=%f\n", k, var, result);       
        
        CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
    }
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Eurostat_store_history_monthly()
 * \brief: Unit test for: Eurostat_store_history_monthly.
 * Test: history storage of region data
 * Init: REGION_FIRM_DATA.array[region].cpi
 * Out: HISTORY_MONTHLY[0].region_data.array[region].cpi
 * Status: Tested OK
 */
void unittest2_Eurostat_store_history_monthly()
{
    int k,  region;
    double var, result;
    //PRINT_LOG =0;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    FLAME_environment_variable_total_regions=2;
    
    //run initializing function to init the region data arrays:
    Eurostat_initialization();
    
    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
            //checking whether inputting new data works:
            //init REGION_FIRM_DATA.array[region].cpi
            REGION_FIRM_DATA.array[region].cpi = (double) region;
            
            //printf("\n REGION_FIRM_DATA.array[%d].cpi=%f\n", region, REGION_FIRM_DATA.array[region].cpi);
    }
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_store_history_monthly();
    
    /***** Variables: Memory post-conditions *****/
    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        
        var = HISTORY_MONTHLY[0].region_data.array[region].cpi;

        result = (double) region;

        //printf("\n HISTORY_MONTHLY[%d].region_data.array[%d].cpi=%f\n", 0, region, HISTORY_MONTHLY[k].region_data.array[region].cpi);
        //printf("\n k=%d, var=%f, result=%f\n", k, var, result);       
        
        CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
    }
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest3_Eurostat_store_history_monthly()
 * \brief: Unit test for: Eurostat_store_history_monthly.
 * Test: history shifting of region data
 * Init: HISTORY_MONTHLY[k].array[region].cpi = (double) k;
 *       REGION_FIRM_DATA.array[region].cpi =0.0;
 * Out:  HISTORY_MONTHLY[k].array[region].cpi = (double) (k-1);
 * Status: Tested OK
 */
void unittest3_Eurostat_store_history_monthly()
{
    int k,  region;
    double var, result;
    //PRINT_LOG =0;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    FLAME_environment_variable_total_regions=2;
    
    //run initializing function to init the region data arrays:
    Eurostat_initialization();
    
    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
            //checking whether shifting history works:
            for (k=0;k<=13;k++)
            {
                HISTORY_MONTHLY[k].region_data.array[region].cpi = (double) k;
                //printf("\n HISTORY_MONTHLY[%d].region_data.array[%d].cpi=%f\n", k, region, HISTORY_MONTHLY[k].region_data.array[region].cpi);
            }
            REGION_FIRM_DATA.array[region].cpi =0.0;
    }
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_store_history_monthly();
    
    /***** Variables: Memory post-conditions *****/
    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        //printf("\n ================================================");
        //printf("\n After Function evaluation: Shifting history");
        //printf("\n ================================================");

        for (k=1;k<13;k++)
        {
            var = HISTORY_MONTHLY[k].region_data.array[region].cpi;
    
            result = (double) (k-1);
    
            //printf("\n HISTORY_MONTHLY[%d].region_data.array[%d].cpi=%f\n", k, region, HISTORY_MONTHLY[k].region_data.array[region].cpi);
            //printf("\n k=%d, var=%f, result=%f\n", k, var, result);       
            
            CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
        }
    }
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_Eurostat_store_history_quarterly()
 * \brief: Unit test for: Eurostat_store_history_quarterly.
 * Test: history storage of economy-wide data: sums or averages of monthly data
 * Init: HISTORY_MONTHLY[k].cpi = 1.01;  for k=0..2
 * Out:  HISTORY_QUARTERLY[0].cpi = 1.0303; 
 * Status: Tested OK
 */
void unittest1_Eurostat_store_history_quarterly()
{
    int k;
    double var, result;
    //PRINT_LOG =0;

    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    //test product
    for (k=0;k<3;k++)
    {
        HISTORY_MONTHLY[k].cpi = 1.01;
    }
    //test sum
    for (k=0;k<3;k++)
    {
        HISTORY_MONTHLY[k].gdp = 100.0;
    }
    //test average
    for (k=0;k<3;k++)
    {
        HISTORY_MONTHLY[k].unemployment_rate = 100.0;
    }

    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_store_history_quarterly();
    
    /***** Variables: Memory post-conditions *****/
    var = HISTORY_QUARTERLY[0].cpi;
    result = 1.0303;
    CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
    
    var = HISTORY_QUARTERLY[0].gdp;
    result = 300.0;
    CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
            
    var = HISTORY_QUARTERLY[0].unemployment_rate;
    result = 100.0;
    CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Eurostat_store_history_quarterly()
 * \brief: Unit test for: Eurostat_store_history_quarterly.
 * Test: history shifting of economy-wide data
 * Init: HISTORY_QUARTERLY[k].cpi = (double) k;
 *       HISTORY_QUARTERLY[0].cpi = 0.0;
 * Out:  HISTORY_QUARTERLY[k].cpi = (double) (k-1); 
 * Status: Tested OK
 */
void unittest2_Eurostat_store_history_quarterly()
{
    int k;
    double var, result;
    //PRINT_LOG =0;

    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    for (k=1;k<=5;k++)
    {
        HISTORY_QUARTERLY[k].cpi = (double) k;
    }
    for (k=0;k<3;k++)
    {
        HISTORY_MONTHLY[k].cpi = 0.0;
    }

    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_store_history_quarterly();
    
    /***** Variables: Memory post-conditions *****/
    for (k=1;k<5;k++)
    {
        var = HISTORY_QUARTERLY[k].cpi;
        result = (double) (k-1);
    
        CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
    }
            
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest3_Eurostat_store_history_quarterly()
 * \brief: Unit test for: Eurostat_store_history_quarterly.
 * Test: history storage of region data: sums or averages of monthly data
 * Init: HISTORY_MONTHLY[k].region_data.array[region].cpi for k=0..2
 * Out:  HISTORY_QUARTERLY[0].region_data.array[region].cpi 
 * Status: Tested OK
 */
void unittest3_Eurostat_store_history_quarterly()
{
    int k, region;
    double var, result;
    //PRINT_LOG =0;

    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();

    /***** Variables: Memory pre-conditions **************************/
    FLAME_environment_variable_total_regions=2;
    //run initializing function to init the region data arrays:
    Eurostat_initialization();

    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        for (k=0;k<3;k++)
        {
            HISTORY_MONTHLY[k].region_data.array[region].cpi = 1.01;
            HISTORY_MONTHLY[k].region_data.array[region].gdp = 100.0;
            HISTORY_MONTHLY[k].region_data.array[region].unemployment_rate = 0.10;
            //printf("\n HISTORY_MONTHLY[%d].region_data.array[%d].cpi=%f\n", k, region, HISTORY_MONTHLY[k].region_data.array[region].cpi);
        }
    }    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_store_history_quarterly();
    
    /***** Variables: Memory post-conditions *****/ 
    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        //checking whether storing data works:  

        var = HISTORY_QUARTERLY[0].region_data.array[region].cpi;
        result = 1.0303;
        CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
        
        var = HISTORY_QUARTERLY[0].region_data.array[region].gdp;
        result = 300.0;
        CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);

        var = HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate;
        result = 0.10;
        CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
    }           
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest4_Eurostat_store_history_quarterly()
 * \brief: Unit test for: Eurostat_store_history_quarterly.
 * Test: history shifting of region data
 * Init: HISTORY_QUARTERLY[k].array[region].cpi = (double) k;
 *       HISTORY_QUARTERLY[0].array[region].cpi = 0.0;
 * Out:  HISTORY_QUARTERLY[k].array[region].cpi = (double) (k-1); 
 * Status: Tested OK
 */
void unittest4_Eurostat_store_history_quarterly()
{
    int k, region;
    double var, result;
    //PRINT_LOG =0;

    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    FLAME_environment_variable_total_regions=2;
    //run initializing function to init the region data arrays:
    Eurostat_initialization();

    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        //checking whether shifting data works: 
        for (k=0;k<=5;k++)
        {
            HISTORY_QUARTERLY[k].region_data.array[region].cpi = (double) k;
        }
        for (k=0;k<3;k++)
        {
            HISTORY_MONTHLY[k].region_data.array[region].cpi = 0.0;
        }
    }
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_store_history_quarterly();
    
    /***** Variables: Memory post-conditions *****/
    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        for (k=1;k<5;k++)
        {
            var = HISTORY_QUARTERLY[k].region_data.array[region].cpi;
            result = (double) (k-1);
        
            CU_ASSERT_DOUBLE_EQUAL(var, result, 1e-3);
        }
    }           
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest1_Eurostat_compute_growth_rates_monthly()
 * \brief: Unit test for: Eurostat_compute_growth_rates_monthly.
 * Test:  growth_rates_monthly of economy-wide data
 * GDP: growth of GDP in pct over previous month and last 12 months
 * CPI: compounded inflation rate in pct over previous month and last 12 months
 * Status: Tested OK
 */
void unittest1_Eurostat_compute_growth_rates_monthly()
{
    int i;
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    HISTORY_MONTHLY[0].gdp = 2.0;
    HISTORY_MONTHLY[1].gdp = 1.0;
    HISTORY_MONTHLY[12].gdp = 0.20;

    for (i=0; i<13; i++)
    {
        HISTORY_MONTHLY[i].cpi = 1.01;
    }
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_compute_growth_rates_monthly();
    
    /***** Variables: Memory post-conditions *****/
    //monthly gdp has grown 100%
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_GROWTH_RATES.gdp, 100.0, 1e-3);
    
    //annualy gdp has grown 900%
    CU_ASSERT_DOUBLE_EQUAL(ANNUAL_GROWTH_RATES_MONTHLY.gdp, 900.0, 1e-3);

    //Every month shows a 1% inflation (price growth rate)
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_GROWTH_RATES.cpi, 1.0, 1e-3);
    
    //annual price growth rate: (1.01)^12=1.1268
    CU_ASSERT_DOUBLE_EQUAL(ANNUAL_GROWTH_RATES_MONTHLY.cpi, 12.68, 1e-2);

    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Eurostat_compute_growth_rates_monthly()
 * \brief: Unit test for: Eurostat_compute_growth_rates_monthly.
 * Test:  growth_rates_monthly of region data
 * GDP: growth of regional GDP in pct over previous month and last 12 months
 * CPI: compounded regional inflation rate in pct over previous month and last 12 months
 * Status: Tested OK
 */
void unittest2_Eurostat_compute_growth_rates_monthly()
{
    int i,k;
    int region;
    double result;
    
    region=0;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    //add 1 item to the REGION_FIRM_DATA struct
    add_firm_data(&REGION_FIRM_DATA,
            i,0,0,                   //3 region_id -> vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    //construct monthly history data structure for regions
    for (k=12; k>0; k--)
    {
        add_region_data_item(&HISTORY_MONTHLY[k].region_data,
                1.0,1.0,0.0,0.0,0,
                0.0,0.0,0.0,0.0,0.0,0.0,
                0.0,0,0,0);        
    }
    
    //construct quarterly history data structure for regions
    for (k=4; k>0; k--)
    {
        add_region_data_item(&HISTORY_QUARTERLY[k].region_data,
                1.0,1.0,0.0,0.0,0,
                0.0,0.0,0.0,0.0,0.0,0.0,
                0.0,0,0,0);        
    }
    
    //construct growth rates data structure for regions
    add_region_data_item(&MONTHLY_GROWTH_RATES.region_data,
            1.0,1.0,0.0,0.0,0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0,0,0);        
    add_region_data_item(&ANNUAL_GROWTH_RATES_MONTHLY.region_data,
            1.0,1.0,0.0,0.0,0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0,0,0);        
    add_region_data_item(&QUARTERLY_GROWTH_RATES.region_data,
            1.0,1.0,0.0,0.0,0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0,0,0);        
    add_region_data_item(&ANNUAL_GROWTH_RATES_QUARTERLY.region_data,
            1.0,1.0,0.0,0.0,0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0,0,0);  
    
    /***** Variables: Memory pre-conditions **************************/
    HISTORY_MONTHLY[0].region_data.array[region].gdp = 2.0; 
    HISTORY_MONTHLY[1].region_data.array[region].gdp = 1.0; 
    HISTORY_MONTHLY[12].region_data.array[region].gdp = 0.20;
    
    for (i=0; i<13; i++)
    {
        HISTORY_MONTHLY[i].region_data.array[region].cpi = 1.01;
    }
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_compute_growth_rates_monthly();
    
    /***** Variables: Memory post-conditions *****/
    //monthly gdp has grown 100%
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_GROWTH_RATES.region_data.array[region].gdp, 100.0, 1e-3);
    
    //annualy gdp has grown 900%
    CU_ASSERT_DOUBLE_EQUAL(ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].gdp, 900.0, 1e-3);
    
    //Every month shows a 1% growth rate
    CU_ASSERT_DOUBLE_EQUAL(MONTHLY_GROWTH_RATES.region_data.array[region].cpi, 1.0, 1e-3);
    
    //annual growth rate: (1.01)^12=1.1268
    CU_ASSERT_DOUBLE_EQUAL(ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].cpi, 12.68, 1e-2);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest1_Eurostat_compute_growth_rates_quarterly()
 * \brief: Unit test for: Eurostat_compute_growth_rates_quarterly.
 * Test:  growth_rates_quarterly of economy-wide data
 * GDP: growth of GDP in pct over previous 3 months and last 4 quarters
 * CPI: compounded inflation rate in pct over previous 3 months and last 4 quarters
 * Status: Tested OK
 */
void unittest1_Eurostat_compute_growth_rates_quarterly()
{
    int i;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    HISTORY_QUARTERLY[0].gdp = 2.0;
    HISTORY_QUARTERLY[1].gdp = 1.0;
    HISTORY_QUARTERLY[4].gdp = 0.20;
    
    for (i=0; i<13; i++)
    {
        HISTORY_MONTHLY[i].cpi = 1.01;
    }

    for (i=0; i<4; i++)
    {
        HISTORY_QUARTERLY[i].cpi = 1.0303;
    }
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_compute_growth_rates_quarterly();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(QUARTERLY_GROWTH_RATES.gdp, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(ANNUAL_GROWTH_RATES_QUARTERLY.gdp, 900.0, 1e-3);
    
    //Every MONTH shows a 1% inflation (price growth rate), hence (1.01)^3=1.0303 per quarter
    //take the last 3 months:
    CU_ASSERT_DOUBLE_EQUAL(QUARTERLY_GROWTH_RATES.cpi, 3.03, 1e-3);
    
    //annual price growth rate: (1.01)^12=1.1268
    //take the last 4 quarters (same as last 12 months):
    CU_ASSERT_DOUBLE_EQUAL(ANNUAL_GROWTH_RATES_QUARTERLY.cpi, 12.68, 1e-2);

    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Eurostat_compute_growth_rates_quarterly()
 * \brief: Unit test for: Eurostat_compute_growth_rates_quarterly.
 * Test:  growth_rates_quarterly of region data
 * GDP: growth of regional GDP in pct over previous 3 months and last 4 quarters
 * CPI: compounded regional inflation rate in pct over previous 3 months and last 4 quarters
 * Status: Tested OK
 */
void unittest2_Eurostat_compute_growth_rates_quarterly()
{
    int i,k,region;
    region=0;
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    //add 1 item to the REGION_FIRM_DATA struct
    add_firm_data(&REGION_FIRM_DATA,
            i,0,0,                   //3 region_id -> vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,0.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    //construct monthly history data structure for regions
    for (k=12; k>0; k--)
    {
        add_region_data_item(&HISTORY_MONTHLY[k].region_data,
                1.0,1.0,0.0,0.0,0,
                0.0,0.0,0.0,0.0,0.0,0.0,
                0.0,0,0,0);        
    }
    
    //construct quarterly history data structure for regions
    for (k=4; k>0; k--)
    {
        add_region_data_item(&HISTORY_QUARTERLY[k].region_data,
                1.0,1.0,0.0,0.0,0,
                0.0,0.0,0.0,0.0,0.0,0.0,
                0.0,0,0,0);        
    }
    
    //construct growth rates data structure for regions
    add_region_data_item(&MONTHLY_GROWTH_RATES.region_data,
            1.0,1.0,0.0,0.0,0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0,0,0);        
    add_region_data_item(&ANNUAL_GROWTH_RATES_MONTHLY.region_data,
            1.0,1.0,0.0,0.0,0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0,0,0);        
    add_region_data_item(&QUARTERLY_GROWTH_RATES.region_data,
            1.0,1.0,0.0,0.0,0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0,0,0);        
    add_region_data_item(&ANNUAL_GROWTH_RATES_QUARTERLY.region_data,
            1.0,1.0,0.0,0.0,0,
            0.0,0.0,0.0,0.0,0.0,0.0,
            0.0,0,0,0);  
    
    /***** Variables: Memory pre-conditions **************************/
    HISTORY_QUARTERLY[0].region_data.array[region].gdp = 2.0;
    HISTORY_QUARTERLY[1].region_data.array[region].gdp = 1.0;
    HISTORY_QUARTERLY[4].region_data.array[region].gdp = 0.20;
    
    for (i=0; i<13; i++)
    {
        HISTORY_MONTHLY[i].region_data.array[region].cpi = 1.01;
    }
    for (i=0; i<4; i++)
    {
        HISTORY_QUARTERLY[i].region_data.array[region].cpi = 1.0303;
    }

    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_compute_growth_rates_quarterly();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_DOUBLE_EQUAL(QUARTERLY_GROWTH_RATES.region_data.array[region].gdp, 100.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].gdp, 900.0, 1e-3);
    
    //Every MONTH shows a 1% inflation (price growth rate), hence (1.01)^3=1.0303 per quarter
    //take the last 3 months:
    CU_ASSERT_DOUBLE_EQUAL(QUARTERLY_GROWTH_RATES.region_data.array[region].cpi, 3.03, 1e-3);
    
    //take the last 4 quarters (same as last 12 months):
    CU_ASSERT_DOUBLE_EQUAL(ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].cpi, 12.68, 1e-2);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_firm_creation()
 * \brief: Unit test for: Eurostat_firm_creation.
 * Status: Not tested
 */
void unittest_Eurostat_firm_creation()
{
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_firm_creation();
    
    /***** Variables: Memory post-conditions *****/
    //CU_ASSERT_DOUBLE_EQUAL(EXPORT_MATRIX[0][0], 100.0, 1e-3);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


/*
 * \fn: void unittest1_Eurostat_measure_recession()
 * \brief: Unit test for: Eurostat_measure_recession.
 * Status: Not tested
 */
void unittest1_Eurostat_measure_recession()
{
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    RECESSION_STARTED=0;
    HISTORY_QUARTERLY[0].gdp=90;
    HISTORY_QUARTERLY[1].gdp=100;
    HISTORY_QUARTERLY[2].gdp=110;
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_measure_recession();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(RECESSION_STARTED, 1);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest2_Eurostat_measure_recession()
 * \brief: Unit test for: Eurostat_measure_recession.
 * Case: RECESSION_STARTED=1 and after updating RECESSION_DURATION from 0 to 1, the recession continues: RECESSION_STARTED=1
 * Status: Not tested
 */
void unittest2_Eurostat_measure_recession()
{
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    RECESSION_STARTED=1;
    RECESSION_DURATION=0;
    HISTORY_QUARTERLY[0].gdp=90;
    HISTORY_QUARTERLY[1].gdp=100;
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_measure_recession();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(RECESSION_STARTED, 1);
    CU_ASSERT_EQUAL(RECESSION_DURATION, 1); 
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest3_Eurostat_measure_recession()
 * \brief: Unit test for: Eurostat_measure_recession.
 * Case: RECESSION_STARTED=1 and after updating RECESSION_DURATION from 0 to 1, the recession is ended: RECESSION_STARTED=0.
 * Status: Not tested
 */
void unittest3_Eurostat_measure_recession()
{
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    RECESSION_STARTED=1;
    RECESSION_DURATION=0;
    HISTORY_QUARTERLY[0].gdp=110;
    HISTORY_QUARTERLY[1].gdp=100;
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_measure_recession();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(RECESSION_STARTED, 0);
    CU_ASSERT_EQUAL(RECESSION_DURATION, 1);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest4_Eurostat_measure_recession()
 * \brief: Unit test for: Eurostat_measure_recession.
 * Case: Recession does not occur: before RECESSION_STARTED=0, and after RECESSION_STARTED=0.
 * Status: Not tested
 */
void unittest4_Eurostat_measure_recession()
{
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    RECESSION_STARTED=0;
    HISTORY_QUARTERLY[0].gdp=90;
    HISTORY_QUARTERLY[1].gdp=100;
    HISTORY_QUARTERLY[2].gdp=90;
    
    /***** Messages: pre-conditions **********************************/
    
    /***** Function evaluation ***************************************/
    Eurostat_measure_recession();
    
    /***** Variables: Memory post-conditions *****/
    CU_ASSERT_EQUAL(RECESSION_STARTED, 0);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}

/*
 * \fn: void unittest_Eurostat_measure_export()
 * \brief: Unit test for: Eurostat_measure_export.
 * Tests if the mall_data_message is correctly read and values are added to memory.
 * Status: Tested OK
 */
void unittest_Eurostat_measure_export()
{
    int rc;
    
    /************* At start of unit test, add one agent **************/
    unittest_init_Eurostat_agent();
    
    /***** Variables: Memory pre-conditions **************************/
    FLAME_environment_variable_total_regions=2;
    
    add_firm_data(&REGION_FIRM_DATA,
            1,100,0,                   //3 region_id, no_firms, vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,1.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    add_firm_data(&REGION_FIRM_DATA,
            2,200,0,                   //3 region_id, no_firms, vacancies 
            0,0,0,0,0,0,             //6 employees_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_wage_skill
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_s_skill
            0.0,0.0,0.0,0.0,0.0,     //5 total_earnings -> average_debt_earnings_ratio
            0.0,0.0,0.0,0.0,0.0,0.0, //6 average_debt_equity_ratio -> monthly_planned_output
            0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
            0.0,1.0,0.0,             //3 gdp, cpi, cpi_last_month 
            0,0,                     //2 no_firm_births, no_firm_deaths
            0.0,0.0);				 //2 productivity_progress, productivity

    /***** Messages: initialize message boards **********************************/
    rc = MB_Create(&b_mall_data, sizeof(m_mall_data));
            #ifdef ERRCHECK
            if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create 'mall_data' board\n");
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
    //mall_data_message(ID, firm_region, household_region, export_volume, export_value, export_previous_value);
    //Adding mall 1 elements
    add_mall_data_message(1, 1, 1,   1.0,   1.0,   1.0);
    add_mall_data_message(1, 1, 2, 100.0, 100.0, 100.0);
    add_mall_data_message(1, 2, 1, 100.0, 100.0, 100.0);
    add_mall_data_message(1, 2, 2,   1.0,   1.0,   1.0);

    //Adding mall 2 elements
    add_mall_data_message(2, 1, 1,   1.0,   1.0,   1.0);
    add_mall_data_message(2, 1, 2, 100.0, 100.0, 100.0);
    add_mall_data_message(2, 2, 1, 100.0, 100.0, 100.0);
    add_mall_data_message(2, 2, 2,   1.0,   1.0,   1.0);

    rc = MB_Iterator_Create(b_mall_data, &i_mall_data);
            
    if (rc != MB_SUCCESS)
            {
               fprintf(stderr, "ERROR: Could not create Iterator for 'mall_data'\n");
               switch(rc) {
                   case MB_ERR_INVALID:
                       fprintf(stderr, "\t reason: 'mall_data' board is invalid\n");
                       break;
                   case MB_ERR_LOCKED:
                       fprintf(stderr, "\t reason: 'mall_data' board is locked\n");
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
    Eurostat_measure_export();
    
    /***** Variables: Memory post-conditions *****/
    //VOLUME
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_VOLUME_MATRIX[0], 2.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_VOLUME_MATRIX[1], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_VOLUME_MATRIX[2], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_VOLUME_MATRIX[3], 2.0, 1e-3);
    
    CU_ASSERT_DOUBLE_EQUAL(REGION_EXPORT_VOLUME[0], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_EXPORT_VOLUME[1], 200.0, 1e-3);
    
    CU_ASSERT_DOUBLE_EQUAL(REGION_IMPORT_VOLUME[0], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_IMPORT_VOLUME[1], 200.0, 1e-3);

    //VALUE
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_VALUE_MATRIX[0], 2.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_VALUE_MATRIX[1], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_VALUE_MATRIX[2], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_VALUE_MATRIX[3], 2.0, 1e-3);
    
    CU_ASSERT_DOUBLE_EQUAL(REGION_EXPORT_VALUE[0], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_EXPORT_VALUE[1], 200.0, 1e-3);
    
    CU_ASSERT_DOUBLE_EQUAL(REGION_IMPORT_VALUE[0], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_IMPORT_VALUE[1], 200.0, 1e-3);

    //PREVIOUS_VALUE
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_PREVIOUS_VALUE_MATRIX[0], 2.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_PREVIOUS_VALUE_MATRIX[1], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_PREVIOUS_VALUE_MATRIX[2], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(EXPORT_PREVIOUS_VALUE_MATRIX[3], 2.0, 1e-3);
    
    //PREVIOUS_IMPORT_VALUE: used for CPI
    CU_ASSERT_DOUBLE_EQUAL(REGION_IMPORT_PREVIOUS_VALUE[0], 200.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_IMPORT_PREVIOUS_VALUE[1], 200.0, 1e-3);
    
    //REGION_IMPORT_VALUE/REGION_PREVIOUS_IMPORT_VALUE:
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[0].cpi, 1.0, 1e-3);
    CU_ASSERT_DOUBLE_EQUAL(REGION_FIRM_DATA.array[1].cpi, 1.0, 1e-3);
    
    /************* At end of unit test, free the agent **************/
    unittest_free_Eurostat_agent();
    /************* At end of unit tests, free all Messages **********/
    free_messages();
}


