/*********************************
 * Eurostat_aux_functions.c 
 * Eurostat auxiliary functions.
 * *********************************
 * History:
 * 16/09/08 Sander 
 *********************************/
#include <limits.h> //required to test for max. double: LONG_MAX
#include "../header.h"
#include "../my_library_header.h"
#include "../Eurostat_agent_header.h"
#include "Eurostat_aux_header.h"

#define MAX_SURVIVAL_PERIODS 12 //length of the array to store the survival rate distribution, nr of bins
#define MAX_FIRM_AGE 301         //length of the array to store the firm age distribution, nr of bins
/*
WARNING: In model.xml these variables are hard-coded with fixed sizes:
firm_age_distribution[300]
firm_age_distribution_1_period_lag[300]
firm_age_distribution_2_period_lag[300]
firm_age_distribution_multiperiod[3600]
survival_rate[300]
survival_rate_multiperiod_1[300]
survival_rate_multiperiod_2[300]
survival_rate_multiperiod[3600]
*/


/* \fn: void Eurostat_reset_data(void)
 * \brief: Function to reset the region data strucures for firms and households.
 */
void Eurostat_reset_data(void)
{
    int i;
 double mean_specific_skills;

    /*delete the content of the data arrays in order to store the data for the new month*/
    //free(REGION_HOUSEHOLD_DATA);
    //free(REGION_FIRM_DATA);
    
    
	/*Save the mean specific skills from REGION_HOUSEHOLD_DATA in a temproray memory variable in order to have an initial value for the reconstruction of the array*/

	mean_specific_skills = REGION_HOUSEHOLD_DATA.array[0].average_s_skill;


    //Remove all data arrays
    for(i = 0; i < REGION_FIRM_DATA.size; i++)
    {
        remove_firm_data(&REGION_FIRM_DATA, i);
        i--;
    }
    
    for(i = 0; i < REGION_HOUSEHOLD_DATA.size; i++)
    {
        remove_household_data(&REGION_HOUSEHOLD_DATA, i);
        i--;
    }

    //Reconstruct empty data arrays
    for(i = 1; i <= TOTAL_REGIONS; i++)
    {
        add_firm_data(&REGION_FIRM_DATA,
                i,0,0,0,                  //region_id, no_firms, no_active_firms, vacancies
                0,0,0,0,0,0,             //employees_skill
                0.0,0.0,0.0,0.0,0.0,0.0, //average_wage_skill
                0.0,0.0,0.0,0.0,0.0,0.0, //average_s_skill
                0.0,0.0,0.0,0.0,0.0,     //total_earnings -> average_debt_earnings_ratio
                0.0,0.0,0.0,0.0,0.0,0.0, //average_debt_equity_ratio -> monthly_planned_output
                0.0,0.0,                 //monthly_investment_value, investment_gdp_ratio
                0.0,1.0,1.0,             //gdp, cpi, cpi_last_month 
                0,0,                     //no_firm_births, no_firm_deaths
                0,0);                    //productivity_progress, productivity
        
        add_household_data(&REGION_HOUSEHOLD_DATA,
                i,
                0,0,0,0,0,0,
                0,0,0,0,0,0,
                0,
                0.0,0.0,0.0,0.0,0.0,0.0,
                0.0,0.0,0.0,0.0,0.0,0.0,0.0,
                mean_specific_skills,mean_specific_skills,mean_specific_skills,mean_specific_skills,mean_specific_skills,mean_specific_skills);
    }
    
}

/* \fn: void Eurostat_compute_mean_price(void)
 * \brief: Function to compute a mean price.
 */
void Eurostat_compute_mean_price(void)
{
    double sum_consumption_good_supply = 0.0;
    PRICE_INDEX = 0.0;

    /*Compute a weighted mean price*/
            
    START_FIRM_SEND_DATA_MESSAGE_LOOP
        sum_consumption_good_supply+= firm_send_data_message->total_supply;
    FINISH_FIRM_SEND_DATA_MESSAGE_LOOP
            
    START_FIRM_SEND_DATA_MESSAGE_LOOP
        PRICE_INDEX += (firm_send_data_message->price*firm_send_data_message->total_supply)/ sum_consumption_good_supply;
    FINISH_FIRM_SEND_DATA_MESSAGE_LOOP
}

/* \fn: void Eurostat_read_firm_data(void)
 * \brief: Function to read and store the region data of the firms.
 */
void Eurostat_read_firm_data(void)
{
    int i;

    NO_VACANCIES = 0.0;
	NO_POSTED_VACANCIES = 0.0;
    NO_EMPLOYEES = 0.0;
	NO_EMPLOYEES_PRODUCTION = 0.0;
    NO_EMPLOYEES_SKILL_1 = 0.0;
    NO_EMPLOYEES_SKILL_2 = 0.0;
    NO_EMPLOYEES_SKILL_3 = 0.0;
    NO_EMPLOYEES_SKILL_4 = 0.0;
    NO_EMPLOYEES_SKILL_5 = 0.0;
	NO_EMPLOYEES_R_AND_D = 0.0;

    FIRM_AVERAGE_WAGE = 0.0;

    FIRM_AVERAGE_S_SKILL = 0.0;
    FIRM_AVERAGE_S_SKILL_1 = 0.0;
    FIRM_AVERAGE_S_SKILL_2 = 0.0;
    FIRM_AVERAGE_S_SKILL_3 = 0.0;
    FIRM_AVERAGE_S_SKILL_4 = 0.0;
    FIRM_AVERAGE_S_SKILL_5 = 0.0;
    
    FIRM_AVERAGE_PRODUCTIVITY_PROGRESS = 0.0;
    FIRM_AVERAGE_PRODUCTIVITY = 0.0;

    TOTAL_CAPITAL_STOCK_UNITS = 0.0;
    TOTAL_VALUE_MALL_INVENTORIES = 0.0;
    TOTAL_DIVIDENDS=0.0;	 
    BASE_WAGE_OFFER = 0.0;	

	FIRM_AVERAGE_QUALITY =0.0;
	FIRM_AVERAGE_PRICE = 0.0;
    
    NO_FIRMS =0;
    NO_ACTIVE_FIRMS=0;

    for(i = 0; i < REGION_FIRM_DATA.size; i++)
    {
        REGION_FIRM_DATA.array[i].no_firms = 0;
                    
        START_FIRM_SEND_DATA_MESSAGE_LOOP
        
        if(firm_send_data_message->region_id == 
        REGION_FIRM_DATA.array[i].region_id)
        {
            REGION_FIRM_DATA.array[i].no_firms += 1;
            NO_FIRMS++;
		
			if (firm_send_data_message->age != -1)
        	{
            	NO_ACTIVE_FIRMS++;
				REGION_FIRM_DATA.array[i].no_active_firms += 1;
			}

            
            REGION_FIRM_DATA.array[i].vacancies += 
                firm_send_data_message->vacancies;
            NO_VACANCIES += firm_send_data_message->vacancies;
			NO_POSTED_VACANCIES += firm_send_data_message->posted_vacancies;
    
            REGION_FIRM_DATA.array[i].employees += 
                firm_send_data_message->employees;
            NO_EMPLOYEES += firm_send_data_message->employees;
    
            REGION_FIRM_DATA.array[i].employees_skill_1 += 
                firm_send_data_message->employees_skill_1;
            NO_EMPLOYEES_SKILL_1 += 
                firm_send_data_message->employees_skill_1;
    
            REGION_FIRM_DATA.array[i].employees_skill_2 += 
                firm_send_data_message->employees_skill_2;
            NO_EMPLOYEES_SKILL_2 += 
                firm_send_data_message->employees_skill_2;
    
            REGION_FIRM_DATA.array[i].employees_skill_3 += 
                firm_send_data_message->employees_skill_3;
            NO_EMPLOYEES_SKILL_3 += 
                firm_send_data_message->employees_skill_3;
    
            REGION_FIRM_DATA.array[i].employees_skill_4 += 
                firm_send_data_message->employees_skill_4;
            NO_EMPLOYEES_SKILL_4 += 
                firm_send_data_message->employees_skill_4;
    
            REGION_FIRM_DATA.array[i].employees_skill_5 += 
                firm_send_data_message->employees_skill_5;
            NO_EMPLOYEES_SKILL_5 += 
                firm_send_data_message->employees_skill_5;

			NO_EMPLOYEES_PRODUCTION += 
				firm_send_data_message->employees_production;

			NO_EMPLOYEES_R_AND_D +=
    			firm_send_data_message->employees_r_and_d;
    
            /********sum of wages of the firms++++++++*/
            REGION_FIRM_DATA.array[i].average_wage += 
                firm_send_data_message->average_wage*
                firm_send_data_message->employees;
            FIRM_AVERAGE_WAGE += firm_send_data_message->average_wage*
                firm_send_data_message->employees_production;
			FIRM_AVERAGE_PRODUCTION_WAGE += firm_send_data_message->average_wage_production*
                firm_send_data_message->employees;
    		FIRM_AVERAGE_R_AND_D_WAGE += firm_send_data_message->average_wage_r_and_d*
                firm_send_data_message->employees_r_and_d;
    
            /********sum of specific skills of the firms++++++++*/
            REGION_FIRM_DATA.array[i].average_s_skill += 
                firm_send_data_message->average_s_skill *
                firm_send_data_message->employees;
            FIRM_AVERAGE_S_SKILL += 
                firm_send_data_message->average_s_skill *
                firm_send_data_message->employees;
    
    
            REGION_FIRM_DATA.array[i].average_s_skill_1 +=
                firm_send_data_message->average_s_skill_1*
                firm_send_data_message->employees_skill_1;
            FIRM_AVERAGE_S_SKILL_1 +=
                firm_send_data_message->average_s_skill_1*
                firm_send_data_message->employees_skill_1;
    
    
            REGION_FIRM_DATA.array[i].average_s_skill_2 +=
                firm_send_data_message->average_s_skill_2*
                firm_send_data_message->employees_skill_2;
            FIRM_AVERAGE_S_SKILL_2 +=
                firm_send_data_message->average_s_skill_2*
                firm_send_data_message->employees_skill_2;
    
    
            REGION_FIRM_DATA.array[i].average_s_skill_3 +=
                firm_send_data_message->average_s_skill_3*
                firm_send_data_message->employees_skill_3;
            FIRM_AVERAGE_S_SKILL_3 +=
                firm_send_data_message->average_s_skill_3*
                firm_send_data_message->employees_skill_3;
    
    
            REGION_FIRM_DATA.array[i].average_s_skill_4 +=
                firm_send_data_message->average_s_skill_4*
                firm_send_data_message->employees_skill_4;
            FIRM_AVERAGE_S_SKILL_4 +=
                firm_send_data_message->average_s_skill_4*
                firm_send_data_message->employees_skill_4;
    
            
            REGION_FIRM_DATA.array[i].average_s_skill_5 +=
                firm_send_data_message->average_s_skill_5*
                firm_send_data_message->employees_skill_5;
            FIRM_AVERAGE_S_SKILL_5 +=
                firm_send_data_message->average_s_skill_5*
                firm_send_data_message->employees_skill_5;
            
            REGION_FIRM_DATA.array[i].productivity_progress += firm_send_data_message->firm_productivity_progress;
            FIRM_AVERAGE_PRODUCTIVITY_PROGRESS += firm_send_data_message->firm_productivity_progress;
            
            REGION_FIRM_DATA.array[i].productivity += firm_send_data_message->firm_productivity;
            FIRM_AVERAGE_PRODUCTIVITY += firm_send_data_message->firm_productivity;

		if(firm_send_data_message->age!=-1)
		{
		FIRM_AVERAGE_QUALITY+= firm_send_data_message->quality;
		FIRM_AVERAGE_PRICE+= firm_send_data_message->price;
		}


	 TOTAL_CAPITAL_STOCK_UNITS += firm_send_data_message->units_capital_stock;
 	 TOTAL_VALUE_MALL_INVENTORIES += firm_send_data_message->value_inventory;
    	 TOTAL_DIVIDENDS+=firm_send_data_message->dividends;	 
		if(NO_ACTIVE_FIRMS>1)
        	 BASE_WAGE_OFFER +=firm_send_data_message->base_wage_offer/(NO_ACTIVE_FIRMS-1) ;
   
        }


		
        FINISH_FIRM_SEND_DATA_MESSAGE_LOOP
        
    }
}
    
/* \fn: void Eurostat_compute_region_firm_data(void)
 * \brief: Function to compute regional data related to firms.
 */
void Eurostat_compute_region_firm_data(void)
{
    int i;

    /*Create the REGIONAL data which feed backs to firms*/
    for(i = 0; i < REGION_FIRM_DATA.size; i++)
    {
        /*********************WAGES************************/
        if(REGION_FIRM_DATA.array[i].employees > 0)
        {
            REGION_FIRM_DATA.array[i].average_wage = 
            REGION_FIRM_DATA.array[i].average_wage/
            REGION_FIRM_DATA.array[i].employees;
        }
    
    
        /*****************SPECIFIC SKILLS*********************/
        if(REGION_FIRM_DATA.array[i].employees > 0)
        {
            REGION_FIRM_DATA.array[i].average_s_skill =
            REGION_FIRM_DATA.array[i].average_s_skill/
            REGION_FIRM_DATA.array[i].employees;
        }
    
        if(REGION_FIRM_DATA.array[i].employees_skill_1 > 0)
        {
            REGION_FIRM_DATA.array[i].average_s_skill_1 =
            REGION_FIRM_DATA.array[i].average_s_skill_1/
            REGION_FIRM_DATA.array[i].employees_skill_1;
        }
    
        if(REGION_FIRM_DATA.array[i].employees_skill_2 > 0)
        {
            REGION_FIRM_DATA.array[i].average_s_skill_2 =
            REGION_FIRM_DATA.array[i].average_s_skill_2/
            REGION_FIRM_DATA.array[i].employees_skill_2;
        }
    
    
        if(REGION_FIRM_DATA.array[i].employees_skill_3 > 0)
        {
            REGION_FIRM_DATA.array[i].average_s_skill_3 =
            REGION_FIRM_DATA.array[i].average_s_skill_3/
            REGION_FIRM_DATA.array[i].employees_skill_3;
        }
    
    
        if(REGION_FIRM_DATA.array[i].employees_skill_4 > 0)
        {
            REGION_FIRM_DATA.array[i].average_s_skill_4 =
            REGION_FIRM_DATA.array[i].average_s_skill_4/
            REGION_FIRM_DATA.array[i].employees_skill_4;
        }
    
        if(REGION_FIRM_DATA.array[i].employees_skill_5 > 0)
        {
            REGION_FIRM_DATA.array[i].average_s_skill_5 =
            REGION_FIRM_DATA.array[i].average_s_skill_5/
            REGION_FIRM_DATA.array[i].employees_skill_5;
        }  
        
        if(REGION_FIRM_DATA.array[i].no_active_firms > 0)
        {
            REGION_FIRM_DATA.array[i].productivity_progress =
            REGION_FIRM_DATA.array[i].productivity_progress/
            REGION_FIRM_DATA.array[i].no_active_firms;
           
            REGION_FIRM_DATA.array[i].productivity =
            REGION_FIRM_DATA.array[i].productivity/
            REGION_FIRM_DATA.array[i].no_active_firms;
        }
	else
	{
	    REGION_FIRM_DATA.array[i].productivity_progress = 0.0;
	    REGION_FIRM_DATA.array[i].productivity = 0.0;
	}
    }
}

/* \fn: void Eurostat_compute_global_firm_data(void)
 * \brief: Function to compute global data that is related to firms.
 */
void Eurostat_compute_global_firm_data(void)
{   
    /*Create the GLOBAL data which is needed for controlling the results or sending 
     *         back to the Households*/
    
    /*********************WAGES****************/
    if(NO_EMPLOYEES > 0)
    {
        FIRM_AVERAGE_WAGE = FIRM_AVERAGE_WAGE/(double)NO_EMPLOYEES;
    }

	 if(NO_EMPLOYEES_R_AND_D > 0)
    {
        FIRM_AVERAGE_R_AND_D_WAGE = FIRM_AVERAGE_R_AND_D_WAGE/(double)NO_EMPLOYEES_R_AND_D;
    }

	 if(NO_EMPLOYEES_PRODUCTION > 0)
    {
        FIRM_AVERAGE_PRODUCTION_WAGE = FIRM_AVERAGE_PRODUCTION_WAGE/(double)NO_EMPLOYEES_PRODUCTION;
    }

 /*****************GENERAL_SKILLS******************/
    if(NO_EMPLOYEES > 0)
    {
        FIRM_AVERAGE_G_SKILL = (NO_EMPLOYEES_SKILL_1*1+ NO_EMPLOYEES_SKILL_2*2+NO_EMPLOYEES_SKILL_3*3+NO_EMPLOYEES_SKILL_4*4+NO_EMPLOYEES_SKILL_5*5)/(double)NO_EMPLOYEES;
    }
    
    
    /*****************SPECIFIC_SKILLS******************/
    if(NO_EMPLOYEES > 0)
    {
        FIRM_AVERAGE_S_SKILL = FIRM_AVERAGE_S_SKILL/(double)NO_EMPLOYEES;
    }
    
    if(NO_EMPLOYEES_SKILL_1 > 0)
    {
        FIRM_AVERAGE_S_SKILL_1 = FIRM_AVERAGE_S_SKILL_1/
                    (double)NO_EMPLOYEES_SKILL_1;
    }
    
    if(NO_EMPLOYEES_SKILL_2 > 0)
    {
        FIRM_AVERAGE_S_SKILL_2 = FIRM_AVERAGE_S_SKILL_2/
                    (double)NO_EMPLOYEES_SKILL_2;
    }
    
    if(NO_EMPLOYEES_SKILL_3 > 0)
    {
        FIRM_AVERAGE_S_SKILL_3 = FIRM_AVERAGE_S_SKILL_3/
                    (double)NO_EMPLOYEES_SKILL_3;
    }
    
    if(NO_EMPLOYEES_SKILL_4 > 0)
    {
        FIRM_AVERAGE_S_SKILL_4 = FIRM_AVERAGE_S_SKILL_4/
                    (double)NO_EMPLOYEES_SKILL_4;
    }
    
    if(NO_EMPLOYEES_SKILL_5 > 0)
    {
        FIRM_AVERAGE_S_SKILL_5 = FIRM_AVERAGE_S_SKILL_5/
                    (double)NO_EMPLOYEES_SKILL_5;
    }
    
    if(NO_ACTIVE_FIRMS > 0)
    {
        FIRM_AVERAGE_PRODUCTIVITY_PROGRESS = FIRM_AVERAGE_PRODUCTIVITY_PROGRESS/
       ( NO_ACTIVE_FIRMS-1);
        
        FIRM_AVERAGE_PRODUCTIVITY = FIRM_AVERAGE_PRODUCTIVITY/(NO_ACTIVE_FIRMS-1);

		FIRM_AVERAGE_QUALITY= FIRM_AVERAGE_QUALITY/(NO_ACTIVE_FIRMS-1);

		FIRM_AVERAGE_PRICE= FIRM_AVERAGE_PRICE/(NO_ACTIVE_FIRMS-1);
        
    }
    else
    {
	FIRM_AVERAGE_PRODUCTIVITY_PROGRESS = 0.0;
	FIRM_AVERAGE_PRODUCTIVITY = 0.0;
    }
}


/* \fn: void Eurostat_read_household_data(void)
 * \brief: Function to read household_send_data_messages and store the global/region data of the households.
 */
void Eurostat_read_household_data(void)
{   
    int i;
    NUM_HOUSEHOLDS=0;
    
    EMPLOYED = 0;
    EMPLOYED_SKILL_1 = 0;
    EMPLOYED_SKILL_2 = 0;
    EMPLOYED_SKILL_3 = 0;
    EMPLOYED_SKILL_4 = 0;
    EMPLOYED_SKILL_5 = 0;
    UNEMPLOYED = 0;  
    
    AVERAGE_WAGE = 0.0;
    AVERAGE_WAGE_SKILL_1 = 0.0;
    AVERAGE_WAGE_SKILL_2 = 0.0;
    AVERAGE_WAGE_SKILL_3 = 0.0;
    AVERAGE_WAGE_SKILL_4 = 0.0;
    AVERAGE_WAGE_SKILL_5 = 0.0;

    AVERAGE_S_SKILL = 0.0;
    AVERAGE_S_SKILL_1 = 0.0;
    AVERAGE_S_SKILL_2 = 0.0;
    AVERAGE_S_SKILL_3 = 0.0;
    AVERAGE_S_SKILL_4 = 0.0;
    AVERAGE_S_SKILL_5 = 0.0;

	JUST_EMPLOYED = 0;
	JUST_UNEMPLOYED = 0;
	START_EMPLOYED = 0;
	START_UNEMPLOYED = 0;
	ENTER_MATCHING = 0;
	UNEMPLOYED_DURATION = 0;

	TOTAL_CONSUMPTION_BUDGET =0.0;
	
	HH_PAYMENT_ACCOUNT = 0.0;
	MEAN_NET_INCOME	= 0.0;
	

    START_HOUSEHOLD_SEND_DATA_MESSAGE_LOOP
    
        /*Store the global/region data of the households*/
        for(i = 0; i < REGION_HOUSEHOLD_DATA.size; i++)
        {
            if(household_send_data_message->region_id == 
            REGION_HOUSEHOLD_DATA.array[i].region_id)
            {
    
                //if(DAY == 20)
                //{
                    NUM_HOUSEHOLDS++;
                //}
                
    
                REGION_HOUSEHOLD_DATA.array[i].no_households++;
    
                REGION_HOUSEHOLD_DATA.array[i].average_wage +=
                household_send_data_message->wage;
                AVERAGE_WAGE = AVERAGE_WAGE + 
                household_send_data_message->wage;
    
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill +=
                household_send_data_message->specific_skill;
                AVERAGE_S_SKILL = AVERAGE_S_SKILL + 
                household_send_data_message->specific_skill;

				JUST_EMPLOYED = JUST_EMPLOYED +  household_send_data_message->just_employed;
				JUST_UNEMPLOYED = JUST_UNEMPLOYED +  household_send_data_message->just_unemployed;
				START_EMPLOYED = START_EMPLOYED +  household_send_data_message->start_employed;
				START_UNEMPLOYED = START_UNEMPLOYED +  household_send_data_message->start_unemployed;
				ENTER_MATCHING	=	ENTER_MATCHING + household_send_data_message->enter_matching;
				HH_PAYMENT_ACCOUNT =  HH_PAYMENT_ACCOUNT + household_send_data_message->payment_account;
				MEAN_NET_INCOME	= MEAN_NET_INCOME + household_send_data_message->mean_net_income;

				TOTAL_CONSUMPTION_BUDGET+=household_send_data_message->consumption_budget_in_month;
				REGION_HOUSEHOLD_DATA.array[i].consumption_budget+=
				household_send_data_message->consumption_budget_in_month;
    
                /*(Region) data is subdivided by general skill level*/
                switch(household_send_data_message->general_skill)
                {  
                case 1:/*General skill level 1*/
                if(household_send_data_message->employment_status != -1)
                {
                    REGION_HOUSEHOLD_DATA.array[i].employed++;
                    REGION_HOUSEHOLD_DATA.array[i].employed_skill_1++;
                    EMPLOYED_SKILL_1++;
                    EMPLOYED++;
                }
                else
                {
                    REGION_HOUSEHOLD_DATA.array[i].unemployed++;
                    UNEMPLOYED++;
                }
    
                if(DAY == 20)
                {   
                    NO_HOUSEHOLDS_SKILL_1++;
                }
    
                REGION_HOUSEHOLD_DATA.array[i].no_households_skill_1++;
    
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_1 =
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_1 +
                household_send_data_message->wage;
    
                AVERAGE_WAGE_SKILL_1 = AVERAGE_WAGE_SKILL_1 + 
                household_send_data_message->wage;
    
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_1 =
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_1 +
                household_send_data_message->specific_skill;
    
                AVERAGE_S_SKILL_1 = AVERAGE_S_SKILL_1 + 
                household_send_data_message->specific_skill;
                break;
    
                case 2:/*General skill level 2*/
                if(household_send_data_message->employment_status != -1)
                {
                    REGION_HOUSEHOLD_DATA.array[i].employed++;
                    REGION_HOUSEHOLD_DATA.array[i].employed_skill_2++;
                    EMPLOYED_SKILL_2++;
                    EMPLOYED++;
                }
                else
                {
                    REGION_HOUSEHOLD_DATA.array[i].unemployed++;
                    UNEMPLOYED++;
                }       
        
                if(DAY == 20)
                {   
                    NO_HOUSEHOLDS_SKILL_2++;
                }
                
                REGION_HOUSEHOLD_DATA.array[i].no_households_skill_2++;
                
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_2 =
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_2 +
                household_send_data_message->wage;
    
                AVERAGE_WAGE_SKILL_2 = AVERAGE_WAGE_SKILL_2 + 
                household_send_data_message->wage;
    
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_2 =
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_2 +
                household_send_data_message->specific_skill;
    
                AVERAGE_S_SKILL_2 = AVERAGE_S_SKILL_2 + 
                household_send_data_message->specific_skill;
                break;
    
                case 3:/*General skill level 3*/
                if(household_send_data_message->employment_status != -1)
                {
                    REGION_HOUSEHOLD_DATA.array[i].employed++;
                    REGION_HOUSEHOLD_DATA.array[i].employed_skill_3++;
                    EMPLOYED_SKILL_3++;
                    EMPLOYED++;
                }
                else
                {
                    REGION_HOUSEHOLD_DATA.array[i].unemployed++;
                    UNEMPLOYED++;
                }
        
                if(DAY == 20)
                {
                    NO_HOUSEHOLDS_SKILL_3++;
                }
    
                REGION_HOUSEHOLD_DATA.array[i].no_households_skill_3++;
    
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_3 =
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_3 +
                household_send_data_message->wage;
    
                AVERAGE_WAGE_SKILL_3 = AVERAGE_WAGE_SKILL_3 + 
                household_send_data_message->wage;
    
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_3 =
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_3 +
                household_send_data_message->specific_skill;
    
                AVERAGE_S_SKILL_3 = AVERAGE_S_SKILL_3 + 
                household_send_data_message->specific_skill;
                break;
    
                case 4:/*General skill level 4*/
                if(household_send_data_message->employment_status != -1)
                {
                    REGION_HOUSEHOLD_DATA.array[i].employed++;
                    REGION_HOUSEHOLD_DATA.array[i].employed_skill_4++;
                    EMPLOYED_SKILL_4++;
                    EMPLOYED++;
                }
                else
                {
                    REGION_HOUSEHOLD_DATA.array[i].unemployed++;
                    UNEMPLOYED++;
                }
                
                if(DAY == 20)
                {
                    NO_HOUSEHOLDS_SKILL_4++;
                }
    
                REGION_HOUSEHOLD_DATA.array[i].no_households_skill_4++;
    
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_4 =
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_4 +
                household_send_data_message->wage;
    
                AVERAGE_WAGE_SKILL_4 = AVERAGE_WAGE_SKILL_4 + 
                household_send_data_message->wage;
    
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_4 =
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_4 +
                household_send_data_message->specific_skill;
    
                AVERAGE_S_SKILL_4 = AVERAGE_S_SKILL_4 + 
                household_send_data_message->specific_skill;
                break;
            
                case 5:/*General skill level 5*/
                if(household_send_data_message->employment_status != -1)
                {
                    REGION_HOUSEHOLD_DATA.array[i].employed++;
                    REGION_HOUSEHOLD_DATA.array[i].employed_skill_5++;
                    EMPLOYED_SKILL_5++;
                    EMPLOYED++;
                }
                else
                {
                    REGION_HOUSEHOLD_DATA.array[i].unemployed++;
                    UNEMPLOYED++;
                }
    
                if(DAY == 20)
                {
                    NO_HOUSEHOLDS_SKILL_5++;
                }
    
                REGION_HOUSEHOLD_DATA.array[i].no_households_skill_5++;
    
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_5 =
                REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_5 +
                household_send_data_message->wage;
    
                AVERAGE_WAGE_SKILL_5 = AVERAGE_WAGE_SKILL_5 + 
                household_send_data_message->wage;
    
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_5 =
                REGION_HOUSEHOLD_DATA.array[i].average_s_skill_5 +
                household_send_data_message->specific_skill;
    
                AVERAGE_S_SKILL_5 = AVERAGE_S_SKILL_5 + 
                household_send_data_message->specific_skill;
                break;
                }
            }
        }
    FINISH_HOUSEHOLD_SEND_DATA_MESSAGE_LOOP
}

/* \fn: void Eurostat_compute_region_household_data(void)
 * \brief: Function to create the region data related to Households.
 */
void Eurostat_compute_region_household_data(void)
{
    int i;
    
    /*Create the REGIONAL data which is needed for controlling the results or sending
     *            back to the Households*/
    for(i = 0; i < REGION_HOUSEHOLD_DATA.size; i++)
    {

        /**************UNEMPLOYMENT-RATE******************/
        REGION_HOUSEHOLD_DATA.array[i].unemployment_rate = 
            100*(1 - (double)REGION_HOUSEHOLD_DATA.array[i].employed/
        (double)REGION_HOUSEHOLD_DATA.array[i].no_households);

        REGION_HOUSEHOLD_DATA.array[i].unemployment_rate_skill_1 =
            100*(1 - (double)REGION_HOUSEHOLD_DATA.array[i].employed_skill_1/
        (double)REGION_HOUSEHOLD_DATA.array[i].no_households_skill_1);

        REGION_HOUSEHOLD_DATA.array[i].unemployment_rate_skill_2 =
            100*(1 - (double)REGION_HOUSEHOLD_DATA.array[i].employed_skill_2/
        (double)REGION_HOUSEHOLD_DATA.array[i].no_households_skill_2);

        REGION_HOUSEHOLD_DATA.array[i].unemployment_rate_skill_3 =
            100*(1 - (double)REGION_HOUSEHOLD_DATA.array[i].employed_skill_3/
        (double)REGION_HOUSEHOLD_DATA.array[i].no_households_skill_3);

        REGION_HOUSEHOLD_DATA.array[i].unemployment_rate_skill_4 =
            100*(1 - (double)REGION_HOUSEHOLD_DATA.array[i].employed_skill_4/
        (double)REGION_HOUSEHOLD_DATA.array[i].no_households_skill_4);

        REGION_HOUSEHOLD_DATA.array[i].unemployment_rate_skill_5 =
            100*(1 - (double)REGION_HOUSEHOLD_DATA.array[i].employed_skill_5/
        (double)REGION_HOUSEHOLD_DATA.array[i].no_households_skill_5);
    

    
        /*******************WAGES*************************/
        if(REGION_HOUSEHOLD_DATA.array[i].employed > 0)
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage = 
            REGION_HOUSEHOLD_DATA.array[i].average_wage/
            REGION_HOUSEHOLD_DATA.array[i].employed;
        }
        else
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage = 0;
        }

        if(REGION_HOUSEHOLD_DATA.array[i].employed_skill_1 > 0)
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_1 = 
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_1/
            REGION_HOUSEHOLD_DATA.array[i].employed_skill_1;
        }
        else
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_1 = 0;
        }   

        if(REGION_HOUSEHOLD_DATA.array[i].employed_skill_2 > 0)
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_2 = 
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_2/
            REGION_HOUSEHOLD_DATA.array[i].employed_skill_2;
        }
        else
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_2 = 0;
        }

        if(REGION_HOUSEHOLD_DATA.array[i].employed_skill_3 > 0)
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_3 = 
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_3/
            REGION_HOUSEHOLD_DATA.array[i].employed_skill_3;
        }
        else
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_3 = 0;
        }

        if(REGION_HOUSEHOLD_DATA.array[i].employed_skill_4 > 0)
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_4 = 
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_4/
            REGION_HOUSEHOLD_DATA.array[i].employed_skill_4;
        }
        else
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_4 = 0;
        }

        if(REGION_HOUSEHOLD_DATA.array[i].employed_skill_5 > 0)
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_5 = 
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_5/
            REGION_HOUSEHOLD_DATA.array[i].employed_skill_5;
        }
        else
        {
            REGION_HOUSEHOLD_DATA.array[i].average_wage_skill_5 = 0;
        }

        /*******************SPECIFIC SKILLS**********************/
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill = 
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill/
        REGION_HOUSEHOLD_DATA.array[i].no_households;

        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_1 =
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_1/
        REGION_HOUSEHOLD_DATA.array[i].no_households_skill_1;

        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_2 =
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_2/
        REGION_HOUSEHOLD_DATA.array[i].no_households_skill_2;

        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_3 =
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_3/
        REGION_HOUSEHOLD_DATA.array[i].no_households_skill_3;

        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_4 =
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_4/
        REGION_HOUSEHOLD_DATA.array[i].no_households_skill_4;
    
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_5 =
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_5/
        REGION_HOUSEHOLD_DATA.array[i].no_households_skill_5;   
    }
}
    
/* \fn: void Eurostat_compute_global_household_data(void)
 * \brief: Function to compute the global macro data related to households.
 */
void Eurostat_compute_global_household_data(void)
{

    /*Create the GLOBAL data which is needed for controlling the results or sending         back to the Households*/
    
    /*******************UNEMPLOYMENT RATE**********************/
    UNEMPLOYMENT_RATE = 100*(1 - (double)EMPLOYED/(double)NUM_HOUSEHOLDS);
	EMPLOYMENT_RATE = 100-UNEMPLOYMENT_RATE;
    UNEMPLOYMENT_RATE_SKILL_1 = 100*(1 - (double)EMPLOYED_SKILL_1/
                    (double)NO_HOUSEHOLDS_SKILL_1);
    UNEMPLOYMENT_RATE_SKILL_2 = 100*(1 - (double)EMPLOYED_SKILL_2/
                    (double)NO_HOUSEHOLDS_SKILL_2);
    UNEMPLOYMENT_RATE_SKILL_3 = 100*(1 - (double)EMPLOYED_SKILL_3/
                    (double)NO_HOUSEHOLDS_SKILL_3);
    UNEMPLOYMENT_RATE_SKILL_4 = 100*(1 - (double)EMPLOYED_SKILL_4/
                    (double)NO_HOUSEHOLDS_SKILL_4);
    UNEMPLOYMENT_RATE_SKILL_5 = 100*(1 - (double)EMPLOYED_SKILL_5/
                    (double)NO_HOUSEHOLDS_SKILL_5);

	
    
    
    /*******************WAGES**********************/
    
    if(EMPLOYED > 0)
    {
        AVERAGE_WAGE = AVERAGE_WAGE/(double)EMPLOYED;
    }
    else
    {
        AVERAGE_WAGE = 0;
    }
    
    if(EMPLOYED_SKILL_1 > 0)
    {
        AVERAGE_WAGE_SKILL_1 = AVERAGE_WAGE_SKILL_1/(double)EMPLOYED_SKILL_1;
    }
    else
    {
        AVERAGE_WAGE_SKILL_1 = 0;
    }
    
    if(EMPLOYED_SKILL_2 > 0)
    {
        AVERAGE_WAGE_SKILL_2 = AVERAGE_WAGE_SKILL_2/(double)EMPLOYED_SKILL_2;
    }
    else
    {
        AVERAGE_WAGE_SKILL_2 = 0;
    }
    
    if(EMPLOYED_SKILL_3 > 0)
    {
        AVERAGE_WAGE_SKILL_3 = AVERAGE_WAGE_SKILL_3/(double)EMPLOYED_SKILL_3;
    }
    else
    {
        AVERAGE_WAGE_SKILL_3 = 0;
    }
    
    if(EMPLOYED_SKILL_4 > 0)
    {
        AVERAGE_WAGE_SKILL_4 = AVERAGE_WAGE_SKILL_4/(double)EMPLOYED_SKILL_4;
    }
    else
    {
        AVERAGE_WAGE_SKILL_4 = 0;
    }
    
    if(EMPLOYED_SKILL_5 > 0)
    {
        AVERAGE_WAGE_SKILL_5 = AVERAGE_WAGE_SKILL_5/(double)EMPLOYED_SKILL_5;
    }
    else
    {
        AVERAGE_WAGE_SKILL_5 = 0;
    }
    
    
    /*******************SPECIFIC SKILLS**********************/
    AVERAGE_S_SKILL = AVERAGE_S_SKILL/(double)NUM_HOUSEHOLDS;
    AVERAGE_S_SKILL_1 = AVERAGE_S_SKILL_1/(double)NO_HOUSEHOLDS_SKILL_1;
    AVERAGE_S_SKILL_2 = AVERAGE_S_SKILL_2/(double)NO_HOUSEHOLDS_SKILL_2;
    AVERAGE_S_SKILL_3 = AVERAGE_S_SKILL_3/(double)NO_HOUSEHOLDS_SKILL_3;
    AVERAGE_S_SKILL_4 = AVERAGE_S_SKILL_4/(double)NO_HOUSEHOLDS_SKILL_4;
    AVERAGE_S_SKILL_5 = AVERAGE_S_SKILL_5/(double)NO_HOUSEHOLDS_SKILL_5;
}
    
/* \fn: void Eurostat_calc_macro_data(void)
 * \brief: Function to compute macro data from firm micro data.
 */
void Eurostat_calc_macro_data(void)
{
    int i;
    FILE *file1;
     char *filename;
    //Auxiliary sums:
    double sum_total_debt_earnings_ratios;
    double sum_total_debt_equity_ratios;
    double sum_total_labour_share_ratios;

    double sum_total_sold_quantity;
    double sum_total_output;
    double sum_total_cum_revenue;
    double sum_total_planned_output;
    
    double sum_region_debt_earnings_ratios;
    double sum_region_debt_equity_ratios;
    double sum_region_labour_share_ratios;
    
    double sum_region_sold_quantity;
    double sum_region_output;
    double sum_region_cum_revenue;
    double sum_region_planned_output;
        
    int counter_firms_in_region;
    
    GDP = 0.0;
    TOTAL_EARNINGS = 0.0;
    TOTAL_DEBT = 0.0;
    TOTAL_ASSETS = 0.0;
    TOTAL_EQUITY = 0.0;
    AVERAGE_DEBT_EARNINGS_RATIO = 0.0;
    AVERAGE_DEBT_EQUITY_RATIO = 0.0;
    LABOUR_SHARE_RATIO = 0.0;

    MONTHLY_SOLD_QUANTITY = 0.0;
    MONTHLY_OUTPUT = 0.0;
    MONTHLY_REVENUE = 0.0;
    MONTHLY_PLANNED_OUTPUT = 0.0;
    MONTHLY_INVESTMENT_VALUE =0.0;

    //Reset total economy sums: these are updated inside the message loop to sum across all firms
    sum_total_debt_earnings_ratios = 0.0;
    sum_total_debt_equity_ratios   = 0.0;
    sum_total_labour_share_ratios  = 0.0;
    sum_total_sold_quantity        = 0.0;
    sum_total_output               = 0.0;
    sum_total_cum_revenue          = 0.0;
    sum_total_planned_output       = 0.0;


	/*****************LABOR MARKET FLOWS****************/

	if(START_EMPLOYED > 0)
	{
		JOB_SEPERATION_RATE = (double)JUST_UNEMPLOYED/(double)START_EMPLOYED;
	}
	else
	{
		JOB_SEPERATION_RATE = 0.0;
	}

	if(ENTER_MATCHING > 0)
	{
		JOB_FINDING_RATE = (double)JUST_EMPLOYED/(double)ENTER_MATCHING;
	}
	else
	{
		JOB_FINDING_RATE = 0.0;
	}

	if(UNEMPLOYED > 0)
	{	
		V_U_RATIO = (double)NO_VACANCIES/(double)UNEMPLOYED;
	}
	else
	{
		V_U_RATIO = 0.0;
	}

	if(NO_POSTED_VACANCIES > 0)
	{
		MATCHING_RATE = (double)JUST_EMPLOYED/(double)NO_POSTED_VACANCIES;
	}
	else
	{
		MATCHING_RATE = 0.0;
	}



    /*Store the region data of the firms*/
    for(i = 0; i < REGION_FIRM_DATA.size; i++)
    {
//      printf("\n Entering region %d", i+1);
        
        counter_firms_in_region =0;
        
        //Reset region sums: these are updated to sum across all firms in the region
        sum_region_debt_earnings_ratios = 0.0;
        sum_region_debt_equity_ratios   = 0.0;
        sum_region_labour_share_ratios  = 0.0;
        sum_region_sold_quantity        = 0.0;
        sum_region_output               = 0.0;
        sum_region_cum_revenue          = 0.0;
        sum_region_planned_output       = 0.0;

        //Reading loop
        START_FIRM_SEND_DATA_MESSAGE_LOOP
        if(firm_send_data_message->region_id == REGION_FIRM_DATA.array[i].region_id)
        {
            counter_firms_in_region++;

            /********sum of GDP: total consumption and investment costs++++++++*/
            REGION_FIRM_DATA.array[i].gdp += firm_send_data_message->cum_revenue + firm_send_data_message->capital_costs;
            GDP += firm_send_data_message->cum_revenue + firm_send_data_message->capital_costs;

            /********sum of: total investment costs++++++++*/
            REGION_FIRM_DATA.array[i].monthly_investment_value += firm_send_data_message->capital_costs;
            MONTHLY_INVESTMENT_VALUE += firm_send_data_message->capital_costs;
            
            /********sum of net earnings of the firms++++++++*/
            REGION_FIRM_DATA.array[i].total_earnings += firm_send_data_message->net_earnings;
            TOTAL_EARNINGS += firm_send_data_message->net_earnings;
            
            
            /********sum of total debt of the firms++++++++*/
            REGION_FIRM_DATA.array[i].total_debt += firm_send_data_message->total_debt;
            TOTAL_DEBT += firm_send_data_message->total_debt;
            
            
            /********sum of total assets of the firms++++++++*/
            REGION_FIRM_DATA.array[i].total_assets += firm_send_data_message->total_assets;
            TOTAL_ASSETS += firm_send_data_message->total_assets;
            
            
            /********sum of total equity of the firms++++++++*/
            REGION_FIRM_DATA.array[i].total_equity += firm_send_data_message->equity;
            TOTAL_EQUITY += firm_send_data_message->equity;
            
            /***************** average debt/earnings ratio *********************/
            if (firm_send_data_message->net_earnings>0.0)
            {
                sum_region_debt_earnings_ratios += firm_send_data_message->total_debt/firm_send_data_message->net_earnings;
                sum_total_debt_earnings_ratios += firm_send_data_message->total_debt/firm_send_data_message->net_earnings;
            }
            
            /***************** average debt/equity ratio *********************/
            if (firm_send_data_message->equity>0.0)
            {
                sum_region_debt_equity_ratios += firm_send_data_message->total_debt/firm_send_data_message->equity;
                sum_total_debt_equity_ratios += firm_send_data_message->total_debt/firm_send_data_message->equity;
            }
            
            /***************** average labour share *********************/
            if (firm_send_data_message->net_earnings>0.0)
            {               
                sum_region_labour_share_ratios += firm_send_data_message->average_wage*firm_send_data_message->employees/firm_send_data_message->net_earnings;
                sum_total_labour_share_ratios += firm_send_data_message->average_wage*firm_send_data_message->employees/firm_send_data_message->net_earnings;
            }
            
            /***************** Sum of: total_sold_quantity *********************/
            sum_region_sold_quantity += firm_send_data_message->cum_total_sold_quantity;
            sum_total_sold_quantity  += firm_send_data_message->cum_total_sold_quantity;
    
            /***************** Sum of: output *********************/
            sum_region_output += firm_send_data_message->output;
            sum_total_output  += firm_send_data_message->output;
            
            /***************** Sum of: cum_revenue *********************/                                 
            sum_region_cum_revenue += firm_send_data_message->cum_revenue;
            sum_total_cum_revenue  += firm_send_data_message->cum_revenue;
            
            /***************** Sum of: planned_output *********************/
            sum_region_planned_output += firm_send_data_message->planned_output;
            sum_total_planned_output  += firm_send_data_message->planned_output;
            
        }
        FINISH_FIRM_SEND_DATA_MESSAGE_LOOP
        
        //Compute regional averages after the regional-specific message loop
        REGION_FIRM_DATA.array[i].average_debt_earnings_ratio = sum_region_debt_earnings_ratios/counter_firms_in_region;
        REGION_FIRM_DATA.array[i].average_debt_equity_ratio = sum_region_debt_equity_ratios/counter_firms_in_region;
        REGION_FIRM_DATA.array[i].labour_share_ratio = sum_region_labour_share_ratios/counter_firms_in_region;
        
        REGION_FIRM_DATA.array[i].monthly_sold_quantity = sum_region_sold_quantity;
        REGION_FIRM_DATA.array[i].monthly_output = sum_region_output;
        REGION_FIRM_DATA.array[i].monthly_revenue = sum_region_cum_revenue;
        REGION_FIRM_DATA.array[i].monthly_planned_output = sum_region_planned_output;
        REGION_FIRM_DATA.array[i].investment_gdp_ratio = REGION_FIRM_DATA.array[i].monthly_investment_value/REGION_FIRM_DATA.array[i].gdp;
    }
    
    //Compute total averages after the region for-loop
    AVERAGE_DEBT_EARNINGS_RATIO = sum_total_debt_earnings_ratios/NO_FIRMS;
    AVERAGE_DEBT_EQUITY_RATIO = sum_total_debt_equity_ratios/NO_FIRMS;
    LABOUR_SHARE_RATIO  = sum_total_labour_share_ratios/NO_FIRMS;

    MONTHLY_SOLD_QUANTITY = sum_total_sold_quantity;
    MONTHLY_OUTPUT = sum_total_output;
    MONTHLY_REVENUE = sum_total_cum_revenue;
    MONTHLY_PLANNED_OUTPUT = sum_total_planned_output;
    INVESTMENT_GDP_RATIO = MONTHLY_INVESTMENT_VALUE/GDP;

	HERFINDAHL_INDEX =0.0;

	START_FIRM_SEND_DATA_MESSAGE_LOOP

	HERFINDAHL_INDEX += pow(firm_send_data_message->cum_total_sold_quantity/MONTHLY_SOLD_QUANTITY,2);

	FINISH_FIRM_SEND_DATA_MESSAGE_LOOP
	 

    
     if (PRINT_DEBUG_FILE_EXP1)
        {
            filename = malloc(40*sizeof(char));
            filename[0]=0;
            strcpy(filename, "its/eurostat2.txt"); 
            file1 = fopen(filename,"a");
            fprintf(file1,"\n %d %f %f",DAY,MONTHLY_SOLD_QUANTITY,MONTHLY_OUTPUT);
            fprintf(file1," %f %f",MONTHLY_REVENUE,MONTHLY_INVESTMENT_VALUE);
            fclose(file1);
            free(filename);
        }
   
}
    
/* \fn: void Eurostat_calc_firm_population(void)
 * \brief: Function to compute the firm population, number of new firm births and firm deaths.
 */
void Eurostat_calc_firm_population(void)
{
    int i, index, x, index2, age;

    /* Reset the content of the memory variables*/
   // NO_FIRMS =0;
    NO_FIRM_BIRTHS=0;
    NO_FIRM_DEATHS=0;
	NO_ACTIVE_FIRMS=0;

    //Reset the age distribution, and store the previous distribution (needed to compute the 1-period survival rates)
    for (i=0;i<MAX_FIRM_AGE;i++)
    {
        FIRM_AGE_DISTRIBUTION_2_PERIOD_LAG[i]=FIRM_AGE_DISTRIBUTION_1_PERIOD_LAG[i];
        FIRM_AGE_DISTRIBUTION_1_PERIOD_LAG[i]=FIRM_AGE_DISTRIBUTION[i];
        FIRM_AGE_DISTRIBUTION[i]=0;
        SURVIVAL_RATE[i]=0.0;
    }
    
    /*Start reading loop*/
    START_FIRM_SEND_DATA_MESSAGE_LOOP
        /***************** Sum of: no_firm_births *********************/
        if (firm_send_data_message->age==1)
        {
            NO_FIRM_BIRTHS++;
            for(i = 0; i < REGION_FIRM_DATA.size; i++)
            {
                REGION_FIRM_DATA.array[i].no_firm_births++;
            }
        }
        /***************** Sum of: no active firms *********************/

        if (firm_send_data_message->age != -1)
        {
            NO_ACTIVE_FIRMS++;
		}

        /***************** Firm age distribution *********************/
        //add the firm's age to correct bin (we assume max. age is 300 months, all firms older than 300 are in the last bin)
		age = firm_send_data_message->age;
        if ( (age >= 0)&&(age < MAX_FIRM_AGE))
        {
			index=firm_send_data_message->age;
            FIRM_AGE_DISTRIBUTION[index] += 1;
        }

		else if (age==-1)
		{
			//all bankrupt firms
		}
        else if (age >= MAX_FIRM_AGE)
        {
            FIRM_AGE_DISTRIBUTION[MAX_FIRM_AGE-1] += 1;
        }

    FINISH_FIRM_SEND_DATA_MESSAGE_LOOP


	    //Rotate the multiperiod age distribution, shift row x to row (x+1)
        for (x=0; x<MAX_SURVIVAL_PERIODS; x++) //MAX_SURVIVAL_PERIODS=12
        {
	        for (i=0; i<MAX_FIRM_AGE; i++)//MAX_FIRM_AGE=300
	        {        
                index = x*MAX_FIRM_AGE+i; 
                index2 = (x+1)*MAX_FIRM_AGE+i;
				//store the age distribution at row x in row (x+1)
				FIRM_AGE_DISTRIBUTION_MULTIPERIOD[index2] = FIRM_AGE_DISTRIBUTION_MULTIPERIOD[index];
		        #ifdef _DEBUG_MODE
		        if (PRINT_DEBUG)
				{
					printf("Entering element [%d][%d], setting FIRM_AGE_DISTRIBUTION_MULTIPERIOD[%d] equal to FIRM_AGE_DISTRIBUTION_MULTIPERIOD[%d]\n", x, i, index2, index);
				}
		        #endif
			}
		}

		//store the new age distribution in the first row
        for (i=0; i<MAX_FIRM_AGE; i++) //MAX_FIRM_AGE=300
        {
				FIRM_AGE_DISTRIBUTION_MULTIPERIOD[i] = FIRM_AGE_DISTRIBUTION[i];
		}

    /***************** Sum of: no_firm_deaths *********************/
    //NO_FIRM_DEATHS = HISTORY_MONTHLY[0].no_firms + NO_FIRM_BIRTHS - NO_FIRMS;
    
    START_BANKRUPTCY_ILLIQUIDITY_MESSAGE_LOOP
        NO_FIRM_DEATHS++;
    FINISH_BANKRUPTCY_ILLIQUIDITY_MESSAGE_LOOP    
    
    START_BANKRUPTCY_INSOLVENCY_MESSAGE_LOOP
        NO_FIRM_DEATHS++;
    FINISH_BANKRUPTCY_INSOLVENCY_MESSAGE_LOOP    

/*
 *   Compute firm demises in a region as follows:
 *   F_t = F_{t-1} + B_t - D_t this gives the nr of firms alive in t, thus
 *   D_t = F_{t-1} + B_t - F_t gives nr of firm deaths
 * 20.08.2010 
 * NOTE: 
 *    HISTORY_MONTHLY[0].region_data.array[i].no_firms should be: HISTORY_MONTHLY[0].region_data.array[i].no_active_firms
 *    REGION_FIRM_DATA.array[i].no_firms should be: REGION_FIRM_DATA.array[i].no_active_firms
 * 
 */  
    for(i = 0; i < REGION_FIRM_DATA.size; i++)
    {
        REGION_FIRM_DATA.array[i].no_firm_deaths = 
            HISTORY_MONTHLY[0].region_data.array[i].no_active_firms + REGION_FIRM_DATA.array[i].no_firm_births - REGION_FIRM_DATA.array[i].no_active_firms; 
    }
    
    /***************** Firm birth rate *********************/
    //Def: nr of newborn firms in period x / nr of firms in period x
    if(NO_FIRMS == 0) FIRM_BIRTH_RATE = 0.0;
    else FIRM_BIRTH_RATE = NO_FIRM_BIRTHS / NO_FIRMS;
        
    /***************** Firm death rate *********************/
    //Def: nr of firm demises in period x / nr of firms in period x
    if(NO_FIRMS == 0) 
        FIRM_DEATH_RATE = 0.0;
    else
        FIRM_DEATH_RATE = NO_FIRM_DEATHS / NO_FIRMS;
}

/* \fn: void Eurostat_calc_firm_survival_rates(void)
 * \brief: Function to compute the (monthly) survival rates.
 */
void Eurostat_calc_firm_survival_rates(void)
{
    int i,x,index, index2, index3, a;
    

    /***************** Firm survival rate *********************/
    //Def: The survival rate after x years (or months) is the percentage of all enterprise births of year n which are still active in year n+x.
    //This is related to the age. We measure the age in months.
    //We need information on: the age distribution in the current period, and the age distribution in the previous period
    //Then we take into account that the demographics moves along the distribution from left to right.
    //For each age, we then define the survival rate as the percentage.

    //1-month survival rate
    //The survival rate for firms that in the previous period had an age in the range [0,59] months:
    for (i=0; i<MAX_FIRM_AGE; i++)
    {
        if(FIRM_AGE_DISTRIBUTION_1_PERIOD_LAG[i]>0)
        {
            SURVIVAL_RATE[i]=
                FIRM_AGE_DISTRIBUTION[i+1]/FIRM_AGE_DISTRIBUTION_1_PERIOD_LAG[i];
        }
        else
        {
            SURVIVAL_RATE[i]=0.0;
        }
    }
    

        /*********************************************
         * NEW FEATURE: Multi-period survival rates
         *********************************************/
        
        //Temporary code: should be double-indexed array
        //SURVIVAL_RATE_MULTIPERIOD_1[60]: 1-period survival rate
        //SURVIVAL_RATE_MULTIPERIOD_2[60]: 2-period survival rate
    
        /******************************* 1-period survival rate code *******************************/
        #ifdef _DEBUG_MODE
        if (PRINT_DEBUG)
        {
            printf("Entering 1-period ahead survival rate: SURVIVAL_RATE_MULTIPERIOD_1\n");
        }
        #endif
        
        x=0;
        for (i=0; i<MAX_FIRM_AGE-x-1; i++)
        {
            #ifdef _DEBUG_MODE
            if (PRINT_DEBUG)
			{
				printf("Entering element %d, using element %d of FIRM_AGE_DISTRIBUTION[%d] and comparing it to FIRM_AGE_DISTRIBUTION_1_PERIOD_LAG[%d]\n", i, i+x+1, i+x+1, i);
			}
            #endif
            
            if(FIRM_AGE_DISTRIBUTION_1_PERIOD_LAG[i]>0)
            {
                SURVIVAL_RATE_MULTIPERIOD_1[i]=
                    FIRM_AGE_DISTRIBUTION[i+x+1]/FIRM_AGE_DISTRIBUTION_1_PERIOD_LAG[i];
            }
            else
            {
                SURVIVAL_RATE_MULTIPERIOD_1[i]=0.0;
            }
        }
        for (i=MAX_FIRM_AGE-x-1; i<MAX_FIRM_AGE; i++)
        {
            #ifdef _DEBUG_MODE
            if (PRINT_DEBUG)
			{
				printf("Entering element %d, padding element %d of SURVIVAL_RATE_MULTIPERIOD with 0.0\n", i, i);
			}
            #endif
            
            //padding
            SURVIVAL_RATE_MULTIPERIOD_1[i]=0.0;
        }

        /******************************* 2-period survival rate code *******************************/
        #ifdef _DEBUG_MODE
        if (PRINT_DEBUG){fprintf(stdout,"Entering 2-period ahead survival rate: SURVIVAL_RATE_MULTIPERIOD_2\n");}
        #endif
        
        x=1;
        for (i=0; i<MAX_FIRM_AGE-x-1; i++)
        {
            #ifdef _DEBUG_MODE
            if (PRINT_DEBUG)
			{
				printf("Entering element %d, using element %d of FIRM_AGE_DISTRIBUTION[%d] and comparing it to FIRM_AGE_DISTRIBUTION_2_PERIOD_LAG[%d]\n", i, i+x+1, i+x+1, i);
			}
            #endif
            
            if(FIRM_AGE_DISTRIBUTION_2_PERIOD_LAG[i]>0)
            {
                SURVIVAL_RATE_MULTIPERIOD_2[i]=
                    FIRM_AGE_DISTRIBUTION[i+x+1]/FIRM_AGE_DISTRIBUTION_2_PERIOD_LAG[i];
            }
            else
            {
                SURVIVAL_RATE_MULTIPERIOD_2[i]=0.0;
            }
        }
        for (i=MAX_FIRM_AGE-x-1; i<MAX_FIRM_AGE; i++)
        {
            #ifdef _DEBUG_MODE
            if (PRINT_DEBUG)
			{
				printf("Entering element %d, padding element %d of SURVIVAL_RATE_MULTIPERIOD with 0.0\n", i, i);
			}
            #endif
            
            //padding
            SURVIVAL_RATE_MULTIPERIOD_2[i]=0.0;
        }

        /******************************* General survival rate code *******************************/
        //Generalized code for any x-period survival rate: we can set MAX_SURVIVAL_PERIODS (12)
        //For each period x, we need bins i = 0...299 FOR THE FIRM AGE: we can set MAX_FIRM_AGE (300)
        //SURVIVAL_RATE_MULTIPERIOD[0][i]:  0.0
        //SURVIVAL_RATE_MULTIPERIOD[1][i]:  1-period survival rate
        //SURVIVAL_RATE_MULTIPERIOD[x][i]:  x-period survival rate
        //SURVIVAL_RATE_MULTIPERIOD[11][i]: 11-period survival rate

        //In model.xml we need to add these variables:
        // <variable><type>int</type><name>firm_age_distribution_multiperiod[12][60]</name><description>Multi-period firm_age_distributions.</description></variable>
        // <variable><type>double</type><name>survival_rate_multiperiod[12][300]</name><description>Multi-period survival rates. Definition: "The survival rate after x years is the percentage of all enterprise births of year n which are still active in year n+x." The 2nd row survival_rate_multiperiod[1][.] equals survival_rate[], and contains the 1-period survival rates (for all age bins 0-299). The 3rd row survival_rate_multiperiod[2][.] contains the 2-period survival rates (for all age bins 0-299), etc.</description></variable>
        //Using matrix-to-array translation:
        // <variable><type>int</type><name>firm_age_distribution_multiperiod[MAX_SURVIVAL_PERIODS*MAX_FIRM_AGE]</name><description>Multi-period firm_age_distributions.</description></variable>
        // <variable><type>double</type><name>survival_rate_multiperiod[MAX_SURVIVAL_PERIODS*MAX_FIRM_AGE]</name><description>Multi-period survival rates. Definition: "The survival rate after x years is the percentage of all enterprise births of year n which are still active in year n+x." The 1st row survival_rate_multiperiod[0][.] equals survival_rate[], and contains the 1-period survival rates (for all age bins 0-59). The 2nd row survival_rate_multiperiod[1][.] contains the 2-period survival rates (for all age bins 0-59), etc.</description></variable>        
        
        /* ROW | AGE i    |   flat index    | Store survival rate at index (col i)
         *     | [x][i]   |   [           ] | [0][i]  | flat index|
         * ----|----------|-----------------|---------|------------------------------------
         * 0:  | [0][i]   |   [       i   ] | [0][i]  | --        | 
         * 1:  | [1][i-1] |   [  301+(i-1)] | [1][i]  | [  301+i] | 1-period survival rate
         * 2:  | [2][i-2] |   [2*301+(i-2)] | [2][i]  | [2*301+i] | 2-period survival rate
         * a:  | [a][i-a] |   [a*301+(i-a)] | [3][i]  | [a*301+i] | a-period survival rate
         */
		    for (x=0; x<MAX_SURVIVAL_PERIODS-1; x++)
		    {
	            for (i=0; i<MAX_FIRM_AGE; i++)
	            {
						//Padding of elements not treated
		                //SURVIVAL_RATE_MULTIPERIOD[x][i]=0.0;
	
    		            //Translation:                
    		            index = x*MAX_FIRM_AGE+i;
    		            SURVIVAL_RATE_MULTIPERIOD[index]=0.0;
    	        }
			}

			//Only use 1st row of FIRM_AGE_DISTRIBUTION_MULTIPERIOD[0][i] as baseline, divide by value in [a][i-a], for a=1...12, a<i
			x=0;
            for (i=1; i<MAX_FIRM_AGE; i++)
            {
/*              
                if(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[x+1][i-x-1]>0)
                {
                    SURVIVAL_RATE_MULTIPERIOD[x][i]=
                        FIRM_AGE_DISTRIBUTION_MULTIPERIOD[x][i]/FIRM_AGE_DISTRIBUTION_MULTIPERIOD[x+1][i-x-1];
                }
                else
                {
                    SURVIVAL_RATE_MULTIPERIOD[x][i]=0.0;
                }
*/
	            for (a=1; a<i; a++)
	            {
						//Translation of matrix notation to flattened array notation:
			            index  = i;						//index: [0][i]
			            index2 = a*MAX_FIRM_AGE+(i-a);	//index: [a][i-a]
	 					index3 = a*MAX_FIRM_AGE+i;		//index: [a][i]
						if(a<MAX_SURVIVAL_PERIODS)		//prevent overrun to [12][-1]
						{

				            if(FIRM_AGE_DISTRIBUTION_MULTIPERIOD[index2]>0)
				            {
				                SURVIVAL_RATE_MULTIPERIOD[index3]=
				                    (double)FIRM_AGE_DISTRIBUTION_MULTIPERIOD[index]/(double)FIRM_AGE_DISTRIBUTION_MULTIPERIOD[index2];
	
				            }
						}
				}

			}
        /******************************* end of general survival rate code *******************************/        
}


/* \fn: void Eurostat_firm_creation(void)
 * \brief: The firm creation process
 */
void Eurostat_firm_creation(void)
{
    int i;
    double sum;
    int nr_new_firms;
    
    //The average 1-period survival rate of firms age 0-12 months: 
    sum=0.0;
    for (i=0; i<12; i++)
    {
        //sum += SURVIVAL_RATE_MULTIPERIOD[0][i];
        sum += SURVIVAL_RATE[i];
    }
    
    //Total number of new firms created is between 0 and MAX_FIRM_CREATION
    nr_new_firms = (int)MAX_FIRM_CREATION*sum/12;
    
    //add new firms
    printf("Adding new firms: %d", nr_new_firms);
    for (i=0; i<nr_new_firms; i++)
    {
        //new unique id
        //random activation day
        //some payment account?
        //some capital?
        
        //add_firm_agent();
    }

}

/* \fn: void Eurostat_measure_export(void)
 * \brief: Function to measure exports between regions.
 */
void Eurostat_measure_export(void)
{
    int i,j,index;
    
    //reset export matrix
    for (i=0; i<TOTAL_REGIONS; i++)
    {
        REGION_EXPORT_VOLUME[i]=0.0;
        REGION_IMPORT_VOLUME[i]=0.0;
        REGION_EXPORT_VALUE[i]=0.0;
        REGION_IMPORT_VALUE[i]=0.0;
        REGION_IMPORT_PREVIOUS_VALUE[i]=0.0;
        
        for (j=0; j<TOTAL_REGIONS; j++)
        {
            index=i*TOTAL_REGIONS+j;
            EXPORT_VOLUME_MATRIX[index]=0.0;
            EXPORT_VALUE_MATRIX[index]=0.0;
            EXPORT_PREVIOUS_VALUE_MATRIX[index]=0.0;
        }
    }
    
    //read in all data from the malls
    START_MALL_DATA_MESSAGE_LOOP
        index = (mall_data_message->firm_region-1)*TOTAL_REGIONS + (mall_data_message->household_region-1);        
        EXPORT_VOLUME_MATRIX[index] += mall_data_message->export_volume;
        EXPORT_VALUE_MATRIX[index] += mall_data_message->export_value;
        EXPORT_PREVIOUS_VALUE_MATRIX[index] += mall_data_message->export_previous_value;
    FINISH_MALL_DATA_MESSAGE_LOOP
    
    //sum total exports (row sum) and imports (column sum)
    for (i=0; i<TOTAL_REGIONS; i++)
    {
        for (j=0; j<TOTAL_REGIONS; j++)
        {
            if(i!=j)
            {
                index=i*TOTAL_REGIONS+j;
                REGION_EXPORT_VOLUME[i] += EXPORT_VOLUME_MATRIX[index];
                REGION_IMPORT_VOLUME[j] += EXPORT_VOLUME_MATRIX[index];
                REGION_EXPORT_VALUE[i] += EXPORT_VALUE_MATRIX[index];
                REGION_IMPORT_VALUE[j] += EXPORT_VALUE_MATRIX[index];
                REGION_IMPORT_PREVIOUS_VALUE[j] += EXPORT_PREVIOUS_VALUE_MATRIX[index];
            }
        }
    }
                           
}


/*\fn: void Eurostat_calc_price_index(void)
 * \brief: Compute the regional CPI and the economy-wide CPI.
 * Q: MONTHLY_SOLD_QUANTITY: total quantity sold in economy
 * q: REGION_FIRM_DATA.array[i].monthly_sold_quantity: total quantity sold in region             
 * weight=q/Q
 * p: REGION_FIRM_DATA.array[i].cpi
 * p_previous = REGION_FIRM_DATA.array[i].cpi_last_month
 * sum_1= sum_regions(weight * p * q)
 * sum_2= sum_regions(weight * p_previous * q)
 * PRICE_INDEX =sum_1/sum2;
*/
void Eurostat_calc_price_index(void)
{
    int j, index;
    double weight, price, price_last_month, quantity, sum_1, sum_2;
    weight=0.0; price=0.0; price_last_month=0.0; quantity=0.0; sum_1=0.0; sum_2=0.0;
        
    //Compute the regional CPI as the ratio between sum(p_t*q_t)/sum(p_t-1*q_t)
    //Then the price index is the multiplication of all previous CPI factors.
    //NOTE: we also need to include the diagonal value of the original export_value_matrix, which was excluded from the import/export sums.
    for (j=0; j<TOTAL_REGIONS; j++)
    {    
        index=j*TOTAL_REGIONS+j;
        REGION_FIRM_DATA.array[j].cpi_last_month = HISTORY_MONTHLY[0].region_data.array[j].cpi;

        if((REGION_IMPORT_PREVIOUS_VALUE[j]+EXPORT_PREVIOUS_VALUE_MATRIX[index])>1e-5)
            REGION_FIRM_DATA.array[j].cpi = REGION_FIRM_DATA.array[j].cpi * (REGION_IMPORT_VALUE[j]+EXPORT_VALUE_MATRIX[index])/(REGION_IMPORT_PREVIOUS_VALUE[j]+EXPORT_PREVIOUS_VALUE_MATRIX[index]);
        else
            printf("\n DIVISION BY ZERO: In Eurostat_aux_functions.c, line 1350:"
                    "REGION_IMPORT_PREVIOUS_VALUE[%d]+EXPORT_PREVIOUS_VALUE_MATRIX[%d][%d](index=%d)=%f", j,j,j,index, REGION_IMPORT_PREVIOUS_VALUE[j]+EXPORT_PREVIOUS_VALUE_MATRIX[index]);
    }                

    //Compute overall economy-wide price index: loop over regions
    sum_1 = 0.0;
    sum_2 = 0.0;
    for(j=0; j<REGION_FIRM_DATA.size; j++)
    {   
        #ifdef _DEBUG_MODE
        if (PRINT_DEBUG)
        {
            //Diagnostics: 
            if (REGION_FIRM_DATA.array[j].monthly_sold_quantity<1e-5)
                printf("\n DIVISION BY ZERO: In Eurostat_aux_functions.c, line 1360: "
                "Monthly_sold_quantity in region %d =%f\n", j, REGION_FIRM_DATA.array[j].monthly_sold_quantity);
        
            if (MONTHLY_SOLD_QUANTITY<1e-5)
                printf("\n DIVISION BY ZERO: In Eurostat_aux_functions.c, line 1364: "
                "MONTHLY_SOLD_QUANTITY=%f\n", MONTHLY_SOLD_QUANTITY);
                
            if (MONTHLY_SOLD_QUANTITY<1e-5)
                printf("\n DIVISION BY ZERO: In Eurostat_aux_functions.c, line 1380: "
                "weight=%f\n", weight);
        }
        #endif
        
            quantity = REGION_FIRM_DATA.array[j].monthly_sold_quantity;
            if (MONTHLY_SOLD_QUANTITY>0.0)
             weight = quantity/MONTHLY_SOLD_QUANTITY;
            else weight = 1;
            
            price = REGION_FIRM_DATA.array[j].cpi;
            price_last_month = REGION_FIRM_DATA.array[j].cpi_last_month;
            sum_1 += weight * price * quantity;
            sum_2 += weight * price_last_month * quantity;
    }
    
    if (sum_2>1e-5)
        CPI = CPI*sum_1/sum_2;

	//Added: 31.05.2010
	//Harmonized Price Index: invcludes capital goods price by adding the investment value to the CPI sum
    if (sum_2+HISTORY_MONTHLY[0].investment_value>1e-5)
        HPI = HPI*(sum_1+MONTHLY_INVESTMENT_VALUE)/(sum_2+HISTORY_MONTHLY[0].investment_value);


    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG)
    {
        if (sum_2 < 1e-5)
            printf("\n DIVISION BY ZERO: In Eurostat_aux_functions.c, line 1388: sum_2=%f", sum_2);

        fprintf(stdout,"\n Economy-wide CPI = %f\n", CPI);
    }
    #endif

}

