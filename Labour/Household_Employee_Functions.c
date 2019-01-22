#include "../header.h"
#include "../Household_agent_header.h"
#include "../my_library_header.h"
#include "Labour_aux_headers.h"


/**********************************Household Role: Labour Market*********************************.*/
/** \fn Household_receive_wage()
 * \brief: 
    - Household receives wage if the household is employed.
    - Sets reservation wage equal to the new wage.
    - Calculates the income in this period add to last_income_array.
*/
int Household_receive_wage()
{

    /*Household reads the wage messages if employed.*/
    START_WAGE_PAYMENT_MESSAGE_LOOP

        /*Set wage and reservation wage.*/
        WAGE = wage_payment_message->payment;
        WAGE_RESERVATION = WAGE;
    
    	HOUSEHOLD_INFLOWS_CALENDAR.wage += wage_payment_message->payment;

        /*Calculate the total income.*/
        TOTAL_INCOME= wage_payment_message->payment +  CUM_TOTAL_DIVIDENDS +
        MONTHLY_BOND_INTEREST_INCOME;

        /*Add wage to payment account.*/
        PAYMENT_ACCOUNT += wage_payment_message->payment;

		if( wage_payment_message->employer_igfirm == 0 )
		{
			/*Store the productivity and the average specific skills 
			of the employer in order to update the specific skills later.*/
			EMPLOYER_IGFIRM = 0; // Employer is a consumption goods producer
			CURRENT_PRODUCTIVITY_EMPLOYER = wage_payment_message-> productivity;
			CURRENT_MEAN_SPECIFIC_SKILLS_EMPLOYER =wage_payment_message->average_specific_skills;

			if(INDIVIDUAL_LEARNING == 1)
			{
				SPECIFIC_SKILL=wage_payment_message->specific_skill;
			}
		}
		else
		{
			EMPLOYER_IGFIRM = 1; // Employer is a capital goods producer
		}

    FINISH_WAGE_PAYMENT_MESSAGE_LOOP


    return 0;
}


/** \fn Household_update_specific_skills()
 * \brief:
    - Household updates specific skills if the household is employed
    - Household sends the new specific skill to the employer
*/
int Household_update_specific_skills()
{
	int i;
	if(INDIVIDUAL_LEARNING == 0)
	{
   		/*If the specific skill of household is lower than the productivity of the employer
    		- no negative effect: no forgetting.*/
    		if(SPECIFIC_SKILL < CURRENT_PRODUCTIVITY_EMPLOYER)
    		{

			if(SKILL_UPDATE_ACC_TO_FORMULA==1)
			{
				/*Update the specific skill: depends on the actual specific skill, 
				the gap between the actual specific skills and the actual productivity of the employer,
				and the general skill which determines the speed of closing the this gap.*/
				SPECIFIC_SKILL = SPECIFIC_SKILL + 
				(CURRENT_PRODUCTIVITY_EMPLOYER - SPECIFIC_SKILL)*((1-pow(0.5,1/(20+0.25*(GENERAL_SKILL-1)*(4-20))))
				+ 0*CURRENT_MEAN_SPECIFIC_SKILLS_EMPLOYER);
			}else
			{
	   			/*Update the specific skill: depends on the actual specific skill, 
        			the gap between the actual specific skills and the actual productivity of the employer. The rate is predetermined.
				A second option is for the 2 region case to allow  for 2 different updating parameters*/
   
				for(i = 0; i<LIST_ADAPTATION_SPEED_PER_GENERAL_SKILL_GROUP.size; i++ )
				{
					if(LIST_ADAPTATION_SPEED_PER_GENERAL_SKILL_GROUP.array[i].general_skill_level == GENERAL_SKILL)   
					{
	     					SPECIFIC_SKILL = SPECIFIC_SKILL + (CURRENT_PRODUCTIVITY_EMPLOYER - SPECIFIC_SKILL)		     
						*LIST_ADAPTATION_SPEED_PER_GENERAL_SKILL_GROUP.array[i].adaptation_speed;
						break;
					}

				}
			}
        		/*Send specific skill to employer.*/
       			 add_specific_skill_update_message(ID,EMPLOYEE_FIRM_ID,SPECIFIC_SKILL,GENERAL_SKILL);
    		}
	}

	
	
    return 0;
}



/** \fn Household_read_firing_messages()
 * \brief 
    - Household reads firing messages if the household is employed
    - Household becomes unemployed: no employer and no wage
    - Stores the last_labor_income for the benefit notification
*/
int Household_read_firing_messages()
{

    /* Check for firing message*/
    START_FIRING_MESSAGE_LOOP

        /*If employee is fired.*/
        if(firing_message->worker_id == ID)
        {
            	/*No employer.*/
            	EMPLOYEE_FIRM_ID = -1;
            
            	/*Information for unemployment benefit notification.*/
      		LAST_LABOUR_INCOME = WAGE;
           	WAGE = 0;
		JUST_UNEMPLOYED = 1;
        }

    FINISH_FIRING_MESSAGE_LOOP
    
    return 0;
}



/** \fn Household_UNEMPLOYED_read_job_vacancies_and_send_applications()
 * \brief: 
    - Household reads vacancy messages. 
    - Selects vacancies regarding the posted wage offer: 
        1: Household and firm are in the same region: wage offer has to be higher than reservation wage
        2: Household and firm are not in the same region: wage offer - commuting costs has to be higher than the res-wage
    - Sends application. 
*/
int Household_UNEMPLOYED_read_job_vacancies_and_send_applications()
{

	int no_r_and_d_vacancies=0;
	int rand = random_int(1,100);
	//Probability of a household to search for a job in this iteration.
	int p = round_double_to_int(100*((double)NUMBER_APPLICATIONS/(double)(MONTH*APPLICATIONS_PER_DAY)));

	SEARCH_TODAY = 0;

	
	if(rand <= p)
	{
		SEARCH_TODAY = 1;
	}
	

	if(DAY <= 20)
	SEARCH_TODAY = 1;


	// Household searches in this iteration.
	if(SEARCH_TODAY == 1)
	{
		int i=0;
		int j=0;
		int job_type = 0;//job type = 0 -> production  =1 -> R&D
		double wage_offer=0.0;

		ENTER_MATCHING = 1;
		
		/* Create a vacancy dynamic array to store vacancies.*/
		vacancy_array  vacancy_list;
		init_vacancy_array(&vacancy_list);

		vacancy_array  r_and_d_vacancy_list;
		init_vacancy_array(&r_and_d_vacancy_list);
		
		
		/*Searchs for vacancies.*/
		START_VACANCIES_MESSAGE_LOOP
	 
		    	/*Unemployed take only the wage offer for the correspondent general skill level into account.*/
		    	if(GENERAL_SKILL == 1)
		    	{
		       		wage_offer = vacancies_message->firm_wage_offer_for_skill_1;
		        	job_type = 0;
			    }

			    if(GENERAL_SKILL == 2)
			    {
				wage_offer = vacancies_message->firm_wage_offer_for_skill_2;
				job_type = 0;
			    }

			    if(GENERAL_SKILL == 3)
			    {
				wage_offer =  vacancies_message->firm_wage_offer_for_skill_3;
				job_type = 0;
			    }

			    if(GENERAL_SKILL == 4)
			    {
				wage_offer =  vacancies_message->firm_wage_offer_for_skill_4;
				job_type = 0;
			    }

			if(GENERAL_SKILL == 5)
			{	
				wage_offer =  vacancies_message->firm_wage_offer_for_skill_5;	
				job_type = 0;			
			}


		    /*Wage offer has to be equal or higher than the reservation wage.*/
		    if(wage_offer >= WAGE_RESERVATION)
		    {
		        /*Firm and Household are in the same region: no commuting costs.*/
		        if(REGION_ID == vacancies_message->region_id)
		        {
		            /*Add vacancy to vacancy list (possible job candidates).*/
		            add_vacancy(&vacancy_list,
		            vacancies_message->firm_id, 
		            vacancies_message->region_id,
		            wage_offer,job_type);
		        }
		        /*Firm and Household are not in the same region: Household has to bear commuting costs.*/
		        else 
		        {
		            /*For every neighboring region.*/
		            for(i = 0;i < NEIGHBORING_REGION_IDS.size; i++)
		            {
		                /*If vacancy is in a neighboring region.*/
		                if(vacancies_message->region_id == NEIGHBORING_REGION_IDS.array[i])
		                {
		                    /*Wage offer minus commuting costs has to be higher than the reservation wage.*/
		                    //if((wage_offer -REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT) >= WAGE_RESERVATION)
		                    if((wage_offer - REGION_COST) >= WAGE_RESERVATION)
		                    {
		                        /*Add vacancy to vacancy list (possible job candidates).*/
		                        add_vacancy(&vacancy_list, 
		                        vacancies_message->firm_id, 
		                        vacancies_message->region_id,
		                        (wage_offer - REGION_COST),job_type);

		                        /*add_vacancy(&vacancy_list, 
		                        vacancies_message->firm_id, 
		                        vacancies_message->region_id,
		                        (wage_offer - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT),job_type);.*/
		                    }
		                    break;
		                }
		            }
		        }
		    }

		FINISH_VACANCIES_MESSAGE_LOOP


		START_VACANCIES_R_AND_D_EMPLOYEES_MESSAGE_LOOP

		wage_offer =vacancies_r_and_d_employees_message->firm_wage_offer;

		job_type =1;

		no_r_and_d_vacancies++;

		/*Wage offer has to be equal or higher than the reservation wage.*/
		    if(wage_offer >= WAGE_RESERVATION)
		    {
		        /*Firm and Household are in the same region: no commuting costs.*/
		        if(REGION_ID == vacancies_r_and_d_employees_message->region_id)
		        {
		            /*Add vacancy to vacancy list (possible job candidates).*/
		            add_vacancy(&r_and_d_vacancy_list,
		            vacancies_r_and_d_employees_message->firm_id, 
		            vacancies_r_and_d_employees_message->region_id,
		            wage_offer,job_type);
		        }
		        /*Firm and Household are not in the same region: Household has to bear commuting costs.*/
		        else 
		        {
		            /*For every neighboring region.*/
		            for(i = 0;i < NEIGHBORING_REGION_IDS.size; i++)
		            {
		                /*If vacancy is in a neighboring region.*/
		                if(vacancies_r_and_d_employees_message->region_id == NEIGHBORING_REGION_IDS.array[i])
		                {
		                    /*Wage offer minus commuting costs has to be higher than the reservation wage.*/
		                    //if((wage_offer -REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT) >= WAGE_RESERVATION)
		                    if((wage_offer - REGION_COST) >= WAGE_RESERVATION)
		                    {
		                        /*Add vacancy to vacancy list (possible job candidates).*/
		                        add_vacancy(&r_and_d_vacancy_list, 
		                        vacancies_r_and_d_employees_message->firm_id, 
		                        vacancies_r_and_d_employees_message->region_id,
		                        (wage_offer - REGION_COST),job_type);

		                        /*add_vacancy(&vacancy_list, 
		                        vacancies_message->firm_id, 
		                        vacancies_message->region_id,
		                        (wage_offer - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT),job_type);.*/
		                    }
		                    break;
		                }
		            }
		        }
		    }

		FINISH_VACANCIES_R_AND_D_EMPLOYEES_MESSAGE_LOOP

		/*If the household does not belong to skill group 5, it can only apply for production jobs */
		if(GENERAL_SKILL !=5)
		{
		/*If there are more vacancies on the list than the maximum number of applications the household can send.*/
			if(vacancy_list.size > APPLICATIONS_PER_DAY)
			{
		    	/*Remove vacancies from the list randomly until the list contains as many
		    	vacancies as a household can send applications.
		    	->imperfect information.*/
		    	while(vacancy_list.size > APPLICATIONS_PER_DAY)
		    	{
		    	    j = random_int(0, (vacancy_list.size-1));
		    	    remove_vacancy(&vacancy_list, j);
		    	}
			}
		
			/* Sends applications to all vacancies which are still on the list.*/
			for(i = 0; i < (vacancy_list.size); i++)
			{
			    add_job_application_message(ID, 
			    vacancy_list.array[i].firm_id,  
			    REGION_ID, 
			    GENERAL_SKILL, 
			    SPECIFIC_SKILL,
				vacancy_list.array[i].job_type);
			}
		}else
		{
			/*If the household belongs to GS group 5 it aplly for r and d jobs. 
			If there are less r and d vacancies than applications per day, the remaining applications are for production jobs*/

			if(r_and_d_vacancy_list.size > APPLICATIONS_PER_DAY)
			{		
				while(r_and_d_vacancy_list.size > APPLICATIONS_PER_DAY)
			   	{
		        		j = random_int(0, (r_and_d_vacancy_list.size-1));
		        		remove_vacancy(&r_and_d_vacancy_list, j);
		    		}

				for(i=0;i<r_and_d_vacancy_list.size;i++)
				{				
				 	add_job_application_message(ID, 
		   			r_and_d_vacancy_list.array[i].firm_id,  
				     	REGION_ID, 
		 		     	GENERAL_SKILL, 
		  		 	SPECIFIC_SKILL,
					r_and_d_vacancy_list.array[i].job_type);				
				}
			}else
			{
				for(i=0;i<r_and_d_vacancy_list.size;i++)
				{				
				 	add_job_application_message(ID, 
		   			r_and_d_vacancy_list.array[i].firm_id,  
				     	REGION_ID, 
		 		     	GENERAL_SKILL, 
		  		 	SPECIFIC_SKILL,
					r_and_d_vacancy_list.array[i].job_type);				
				}
				
				while(vacancy_list.size > APPLICATIONS_PER_DAY-r_and_d_vacancy_list.size)
		   		{
		        	j = random_int(0, (vacancy_list.size-1));
		        	remove_vacancy(&vacancy_list, j);
		    	}

				/* Sends applications to all vacancies which are still on the list.*/
				for(i = 0; i < (vacancy_list.size); i++)
				{
				    add_job_application_message(ID, 
				    vacancy_list.array[i].firm_id,  
				    REGION_ID, 
				    GENERAL_SKILL, 
				    SPECIFIC_SKILL,
				    vacancy_list.array[i].job_type);
				}
				
			}		
		}

		/*Sorting vacancies regarding their posted wage offer.*/
		//qsort(vacancy_list.array, vacancy_list.size, sizeof(vacancy),vacancy_list_rank_wage_offer_function);

		/*Free the vacancy dynamic array.*/
		free_vacancy_array(&r_and_d_vacancy_list);
		free_vacancy_array(&vacancy_list);
		
	}
    return 0;
}

/** \fn Household_read_job_offers_send_response()
 * \brief: 
    - Household reads job offer(s) and accepts the offer with the highest wage offer net of commuting costs.
*/
int Household_read_job_offers_send_response()
{
    /* Create a job offer dynamic array*/
    job_offer_array job_offer_list;
    init_job_offer_array(&job_offer_list);

    START_JOB_OFFER_MESSAGE_LOOP

        /*Read job offer messages for this Household.*/
        if(job_offer_message->worker_id == ID)
        {
            /*Job offers of firms in the same region: no commuting costs.*/
            if(REGION_ID == job_offer_message->region_id)
            {
                /*Add job offer to the job offer list.*/
                add_job_offer(&job_offer_list,
                job_offer_message->firm_id, 
                job_offer_message->region_id,
                job_offer_message->wage_offer,
		job_offer_message->job_type);
            }
            /*Job offers of firms in different regions: Household has to bear commuting costs.*/
            else
            {
                add_job_offer(&job_offer_list,
                job_offer_message->firm_id, 
                job_offer_message->region_id,
                (job_offer_message->wage_offer - REGION_COST),
		job_offer_message->job_type);

                /*add_job_offer(&job_offer_list,
                job_offer_message->firm_id, 
                job_offer_message->region_id,
                (job_offer_message->wage_offer - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT)
				job_offer_message->job_type);.*/
            }
        }

    FINISH_JOB_OFFER_MESSAGE_LOOP


    /*Ranks job offers regarding the posted wage offer net of commuting costs.*/
    qsort(job_offer_list.array, job_offer_list.size, sizeof(job_offer),job_offer_list_rank_wage_offer_function);

    /* Accept  job with highest net wage offer: first on the list (array[0]).*/
    if(job_offer_list.size > 0)
    {
        add_job_acceptance_message(ID, 
        job_offer_list.array[0].firm_id, 
        REGION_ID, 
        GENERAL_SKILL, 
        SPECIFIC_SKILL,
	job_offer_list.array[0].job_type);
		
        /*Sets employer_id, employer_region_id and the day when the household will receive the wage.*/
        EMPLOYEE_FIRM_ID = job_offer_list.array[0].firm_id;
        EMPLOYER_REGION_ID = job_offer_list.array[0].region_id;
        DAY_OF_MONTH_RECEIVE_INCOME = DAY%MONTH;
	JUST_EMPLOYED = 1;
	SEARCH_TODAY = 0;

        /*If household and firm are in the same region.*/
        if(REGION_ID == job_offer_list.array[0].region_id)
        {
            /*Add the new wage and sets the reservation wage to the new wage.*/
            WAGE = job_offer_list.array[0].wage_offer;
            WAGE_RESERVATION = WAGE;
        }
        /*If household and firm are not in the same region.*/
        else
        {   
            //WAGE = (job_offer_list.array[0].wage_offer + REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT);
            //WAGE_RESERVATION = WAGE - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT;
            
            /*Add the new wage minus commuting costs and 
            sets the reservation wage to the new wage minus commuting costs.*/
            WAGE = (job_offer_list.array[0].wage_offer + REGION_COST);
            WAGE_RESERVATION = WAGE - REGION_COST;
        }
    }

    /*Free the job offer dynamic array.*/
    free_job_offer_array(&job_offer_list);

    return 0;
}



/** \fn Household_read_application_rejection_update_wage_reservation()
 * \brief: 
    - If the household is still unemployed it updates (decreases) its wage reservation.
*/
int Household_read_application_rejection_update_wage_reservation()
{
	if(SEARCH_TODAY == 1)
	{
		/*Updates the reservation wage by a certain fraction according to the parameter WAGE_RESERVATION_UPDATE.*/
		WAGE_RESERVATION = WAGE_RESERVATION - WAGE_RESERVATION*WAGE_RESERVATION_UPDATE;

		/* Don't let wage reservation be below the current unemplyoment benefit pct.*/
		if(WAGE_RESERVATION < LAST_LABOUR_INCOME*UNEMPLOYMENT_BENEFIT_PCT)
		{
		    WAGE_RESERVATION = LAST_LABOUR_INCOME*UNEMPLOYMENT_BENEFIT_PCT;
		}
	}    
    return 0;
}


/** \fn Household_UNEMPLOYED_read_job_vacancies_and_send_applications2()
 * \brief: 
    - Household reads vacancy messages. 
    - Selects vacancies regarding the posted wage offer: 
        1: Household and firm are in the same region: wage offer has to be higher than reservation wage
        2: Household and firm are not in the same region: wage offer - commuting costs has to be higher than the res-wage
    - Sends application. 
*/
int Household_UNEMPLOYED_read_job_vacancies_and_send_applications_2()
{
	if(SEARCH_TODAY ==1 )
	{	

		int no_r_and_d_vacancies=0;
		int i=0;
		int j=0;
		int job_type=0;
		double wage_offer=0.0;

		/* Create a vacancy dynamic array*/
		vacancy_array  vacancy_list;
		init_vacancy_array(&vacancy_list);
		
		vacancy_array  r_and_d_vacancy_list;
		init_vacancy_array(&r_and_d_vacancy_list);
	
		/*Searchs for vacancies.*/
		START_VACANCIES2_MESSAGE_LOOP
		
		    /*Unemployed take only the wage offer for the correspondent general skill level into account.*/
		    if(GENERAL_SKILL == 1)
		    {
		        wage_offer = vacancies2_message->firm_wage_offer_for_skill_1;
		    }

		    if(GENERAL_SKILL == 2)
		    {
		        wage_offer = vacancies2_message->firm_wage_offer_for_skill_2;
		    }

		    if(GENERAL_SKILL == 3)
		    {
		        wage_offer =  vacancies2_message->firm_wage_offer_for_skill_3;
		    }

		    if(GENERAL_SKILL == 4)
		    {
		        wage_offer =  vacancies2_message->firm_wage_offer_for_skill_4;
		    }

			if(GENERAL_SKILL == 5)
			{
				wage_offer =  vacancies2_message->firm_wage_offer_for_skill_5;	
			}

		    /*Wage offer has to be equal or higher than the reservation wage.*/
		    if(wage_offer >= WAGE_RESERVATION)
		    {
		        /*Firm and Household are in the same region: no commuting costs.*/
		        if(REGION_ID == vacancies2_message->region_id)
		        {
		            /*Add vacancy to vacancy list (possible job candidates).*/
		            add_vacancy(&vacancy_list, 
		            vacancies2_message->firm_id, 
		            vacancies2_message->region_id,
		            wage_offer,job_type);
		        }
		        /*Firm and Household are not in the same region: Household has to bear commuting costs.*/
		        else
		        {
		            /*For every neighboring region.*/
		            for(i = 0; i < NEIGHBORING_REGION_IDS.size;i++)
		            {
		                /*If vacancy is in a neighboring region.*/
		                if(vacancies2_message->region_id == NEIGHBORING_REGION_IDS.array[i])
		                {
		                    /*Wage offer minus commuting costs has to be higher than the reservation wage.*/
		                    //if((wage_offer - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT) >=WAGE_RESERVATION)
		                    if((wage_offer - REGION_COST) >= WAGE_RESERVATION)
		                    {
		                        /*Add vacancy to vacancy list (possible job candidates).*/
		                        add_vacancy(&vacancy_list,
		                        vacancies2_message->firm_id, 
		                        vacancies2_message->region_id,
		                        (wage_offer - REGION_COST),job_type);

		                        /*add_vacancy(&vacancy_list,
		                        vacancies2_message->firm_id, 
		                        vacancies2_message->region_id,
		                        (wage_offer - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT),
								vacancies2_message->job_type);.*/
		                    }
		                
		                    break;

		                }
		            }
		        }
		    }

		FINISH_VACANCIES2_MESSAGE_LOOP


		START_VACANCIES_R_AND_D_EMPLOYEES2_MESSAGE_LOOP

		wage_offer =vacancies_r_and_d_employees2_message->firm_wage_offer;

		job_type =1;

		no_r_and_d_vacancies++;

		/*Wage offer has to be equal or higher than the reservation wage.*/
		    if(wage_offer >= WAGE_RESERVATION)
		    {
		        /*Firm and Household are in the same region: no commuting costs.*/
		        if(REGION_ID == vacancies_r_and_d_employees2_message->region_id)
		        {
		            /*Add vacancy to vacancy list (possible job candidates).*/
		            add_vacancy(&r_and_d_vacancy_list,
		            vacancies_r_and_d_employees2_message->firm_id, 
		            vacancies_r_and_d_employees2_message->region_id,
		            wage_offer,job_type);
		        }
		        /*Firm and Household are not in the same region: Household has to bear commuting costs.*/
		        else 
		        {
		            /*For every neighboring region.*/
		            for(i = 0;i < NEIGHBORING_REGION_IDS.size; i++)
		            {
		                /*If vacancy is in a neighboring region.*/
		                if(vacancies_r_and_d_employees2_message->region_id == NEIGHBORING_REGION_IDS.array[i])
		                {
		                    /*Wage offer minus commuting costs has to be higher than the reservation wage.*/
		                    //if((wage_offer -REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT) >= WAGE_RESERVATION)
		                    if((wage_offer - REGION_COST) >= WAGE_RESERVATION)
		                    {
		                        /*Add vacancy to vacancy list (possible job candidates).*/
		                        add_vacancy(&r_and_d_vacancy_list, 
		                        vacancies_r_and_d_employees2_message->firm_id, 
		                        vacancies_r_and_d_employees2_message->region_id,
		                        (wage_offer - REGION_COST),job_type);

		                        /*add_vacancy(&vacancy_list, 
		                        vacancies_message->firm_id, 
		                        vacancies_message->region_id,
		                        (wage_offer - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT),job_type);.*/
		                    }
		                    break;
		                }
		            }
		        }
		    }

		FINISH_VACANCIES_R_AND_D_EMPLOYEES2_MESSAGE_LOOP


		/*If the household does not belong to skill group 5, it can only apply for production jobs */
		if(GENERAL_SKILL !=5)
		{
		/*If there are more vacancies on the list than the maximum number of applications the household can send.*/
			if(vacancy_list.size > APPLICATIONS_PER_DAY)
			{
		    	/*Remove vacancies from the list randomly until the list contains as many
		    	vacancies as a household can send applications.
		    	->imperfect information.*/
		    	while(vacancy_list.size > APPLICATIONS_PER_DAY)
		    	{
		    	    j = random_int(0, (vacancy_list.size-1));
		    	    remove_vacancy(&vacancy_list, j);
		    	}
			}
		
			/* Sends applications to all vacancies which are still on the list.*/
			for(i = 0; i < (vacancy_list.size); i++)
			{
			    add_job_application2_message(ID, 
			    vacancy_list.array[i].firm_id,  
			    REGION_ID, 
			    GENERAL_SKILL, 
			    SPECIFIC_SKILL,
				vacancy_list.array[i].job_type);
			}
		}else
		{
			/*If the household belongs to GS group 5 it aplly for r and d jobs. 
			If there are less r and d vacancies than applications per day, the remaining applications are for production jobs*/

			if(r_and_d_vacancy_list.size > APPLICATIONS_PER_DAY)
			{		
				while(r_and_d_vacancy_list.size > APPLICATIONS_PER_DAY)
			   	{
		        	j = random_int(0, (r_and_d_vacancy_list.size-1));
		        	remove_vacancy(&r_and_d_vacancy_list, j);
		    	}
				for(i=0;i<r_and_d_vacancy_list.size;i++)
				{				
				 	add_job_application2_message(ID, 
		   			r_and_d_vacancy_list.array[i].firm_id,  
				    	REGION_ID, 
		 		        GENERAL_SKILL, 
		  		 	SPECIFIC_SKILL,
					r_and_d_vacancy_list.array[i].job_type);				
				}
			}else
			{
				for(i=0;i<r_and_d_vacancy_list.size;i++)
				{				
				 	add_job_application2_message(ID, 
		   			r_and_d_vacancy_list.array[i].firm_id,  
				     	REGION_ID, 
		 		    	GENERAL_SKILL, 
		  		 	SPECIFIC_SKILL,
					r_and_d_vacancy_list.array[i].job_type);				
				}
				
				while(vacancy_list.size > APPLICATIONS_PER_DAY-r_and_d_vacancy_list.size)
		   		{
		        		j = random_int(0, (vacancy_list.size-1));
		        		remove_vacancy(&vacancy_list, j);
		    		}

				/* Sends applications to all vacancies which are still on the list.*/
				for(i = 0; i < (vacancy_list.size); i++)
				{
				    add_job_application2_message(ID, 
				    vacancy_list.array[i].firm_id,  
				    REGION_ID, 
				    GENERAL_SKILL, 
				    SPECIFIC_SKILL,
				    vacancy_list.array[i].job_type);
				}	
			}		
		}

	
   		 /* Free the vacancy dynamic array*/
    		free_vacancy_array(&vacancy_list);
		free_vacancy_array(&r_and_d_vacancy_list);
		
	}
    return 0;
}


/** \fn Household_read_job_offers_send_response2()
 * \brief: 
    - Household reads job offer(s) and accepts the offer with the highest wage offer net of commuting costs.
*/
int Household_read_job_offers_send_response_2()
{
    /* Create a job offer dynamic array*/
    job_offer_array  job_offer_list;
    init_job_offer_array(&job_offer_list);

    START_JOB_OFFER2_MESSAGE_LOOP
    
        /* Read job offer messages for this Household*/
        if(job_offer2_message->worker_id == ID)
        {
            /*Job offers of firms in the same region: no commuting costs.*/
            if(REGION_ID == job_offer2_message->region_id)
            {
                /*Add job offer to the job offer list.*/
                add_job_offer(&job_offer_list,
                job_offer2_message->firm_id,
                job_offer2_message->region_id,
                job_offer2_message->wage_offer,
		job_offer2_message->job_type);
            }
            /*Job offers of firms in different regions: Household has to bear commuting costs.*/
            else
            {
                /*add_job_offer(&job_offer_list,
                job_offer2_message->firm_id,
                job_offer2_message->region_id,
                (job_offer2_message->wage_offer - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT),
				job_offer2_message->job_type);.*/

                /*Add job offer to the job offer list.*/
                add_job_offer(&job_offer_list,
                job_offer2_message->firm_id,
                job_offer2_message->region_id,
                (job_offer2_message->wage_offer - REGION_COST),
		job_offer2_message->job_type);
            }
        }

    FINISH_JOB_OFFER2_MESSAGE_LOOP

    /*Ranks job offers regarding the posted wage offer net of commuting costs.*/
    qsort(job_offer_list.array, job_offer_list.size, sizeof(job_offer),job_offer_list_rank_wage_offer_function);

    /* Accept  job with highest net wage offer: first on the list (array[0]).*/
    if(job_offer_list.size > 0)
    {
        add_job_acceptance2_message(ID, 
        job_offer_list.array[0].firm_id,
        REGION_ID, 
        GENERAL_SKILL, 
        SPECIFIC_SKILL,
	job_offer_list.array[0].job_type);

        /*Sets employer_id, employer_region_id and the day when the household will receive the wage.*/
        EMPLOYEE_FIRM_ID = job_offer_list.array[0].firm_id;
        EMPLOYER_REGION_ID = job_offer_list.array[0].region_id;
        DAY_OF_MONTH_RECEIVE_INCOME = DAY%MONTH;
	JUST_EMPLOYED = 1;
	SEARCH_TODAY = 0;

        /*If household and firm are in the same region.*/
        if(REGION_ID == job_offer_list.array[0].region_id)
        {
            /*Add the new wage and sets the reservation wage to the new wage.*/
            WAGE = job_offer_list.array[0].wage_offer;
            WAGE_RESERVATION = WAGE;    
        }
         /*If household and firm are not in the same region.*/
        else
        {  
            //WAGE = (job_offer_list.array[0].wage_offer + REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT);
            //WAGE_RESERVATION = WAGE - REGION_COST*COMMUTING_COSTS_PRICE_LEVEL_WEIGHT;
            
            /*Add the new wage minus commuting costs and 
            sets the reservation wage to the new wage minus commuting costs.*/
            WAGE = (job_offer_list.array[0].wage_offer + REGION_COST);
            WAGE_RESERVATION = WAGE - REGION_COST;
        }
    }

    /* Free the job offer dynamic array*/
    free_job_offer_array(&job_offer_list);

    return 0;
}



/** \fn Household_read_application_rejection_update_wage_reservation2()
 * \brief: 
    - If the household is still unemployed it updates (decreases) its wage reservation.
*/
int Household_read_application_rejection_update_wage_reservation_2()
{
	if(SEARCH_TODAY == 1)
	{
		/*Updates the reservation wage by a certain fraction according to the parameter WAGE_RESERVATION_UPDATE.*/
		WAGE_RESERVATION = WAGE_RESERVATION-WAGE_RESERVATION*WAGE_RESERVATION_UPDATE;

		/* Don't let wage reservation be below the current unemplyoment benefit pct.*/
		if(WAGE_RESERVATION < LAST_LABOUR_INCOME*UNEMPLOYMENT_BENEFIT_PCT)
		{
		    WAGE_RESERVATION = LAST_LABOUR_INCOME*UNEMPLOYMENT_BENEFIT_PCT;
		}
	}
    return 0;
}

int Household_idle()
{
    return 0;
}

int Household_finish_labour_market()
{
    return 0;
}

/**********************************Household Role: Public Sector *********************/

/** \fn Household_send_unemployment_benefit_notification()
 * \brief This function sends a message to the government in case of being unemployed that contains the unemployment benefit.
 * The government aggregates the unemployment benefit payments and subtract the amount from its payment account.
 * The household uses the own memory variable UNEMPLOYMENT_BENEFIT_PCT to calculate its own unemployment benefit.
 */
int Household_send_unemployment_benefit_notification()
{
    
    /*Compute unemployment_benefit*/
    //Sander, 23.10.09: Transferred this code from the government to the household
    //Now the household does the complete computation and only sends the outcome to government
            
    //Compute the individual unemployment benefit payment as a fraction of the last labour income       
    //if unemployment benefit is larger than the mean wage:
        if(LAST_LABOUR_INCOME*UNEMPLOYMENT_BENEFIT_PCT > REGION_WIDE_MEAN_WAGE*0.5 )
        {       
            UNEMPLOYMENT_PAYMENT = LAST_LABOUR_INCOME*UNEMPLOYMENT_BENEFIT_PCT;  
        }
        else    
        {
            //if unemployment benefit is below the mean wage: pay 0.5 * MEAN_WAGE
            UNEMPLOYMENT_PAYMENT =  REGION_WIDE_MEAN_WAGE*0.5; 
        }
    
    /*Add unemployment_benefit message */
    add_unemployment_notification_message(GOV_ID, UNEMPLOYMENT_PAYMENT );
    HOUSEHOLD_INFLOWS_CALENDAR.unemployment_benefit += UNEMPLOYMENT_PAYMENT;
    
    /*Add unemployment_benefit to account */
    PAYMENT_ACCOUNT +=  UNEMPLOYMENT_PAYMENT;

    TOTAL_INCOME=  UNEMPLOYMENT_PAYMENT + CUM_TOTAL_DIVIDENDS + MONTHLY_BOND_INTEREST_INCOME;


    //Set the benefit reception day
    DAY_OF_MONTH_RECEIVE_BENEFIT = DAY_OF_MONTH_RECEIVE_INCOME;

    return 0;

}


/** \fn Household_send_subsidy_notification()
 * \brief This function sends a message to the government in case the household applies for a subsidy.
 */
int Household_send_subsidy_notification()
{
    if (POLICY_EXP_STABILIZATION_SUBSIDY==1)
    {
        SUBSIDY_PAYMENT = SUBSIDY_PCT*MONTHLY_CONSUMPTION_EXPENDITURE;
    
        /*Add subsidy message */
        add_hh_subsidy_notification_message(GOV_ID, SUBSIDY_PAYMENT);
        PAYMENT_ACCOUNT += SUBSIDY_PAYMENT;
        HOUSEHOLD_INFLOWS_CALENDAR.subsidies += SUBSIDY_PAYMENT;
    }
    return 0;
}

/** \fn Household_send_transfer_notification()
 * \brief This function sends a message to the government in case the household applies for a transfer.
 */
int Household_send_transfer_notification()
{
    /*Add transfer message */
    add_hh_transfer_notification_message(GOV_ID);
    PAYMENT_ACCOUNT += TRANSFER_PAYMENT;
    HOUSEHOLD_INFLOWS_CALENDAR.transfer += TRANSFER_PAYMENT;

    return 0;
}

/** \fn Household_send_tax_payment()
 * \brief Household pays the income taxes
 */
int Household_send_tax_payment()
{
    // #ifdef _DEBUG_MODE  
       // FILE *file1=NULL;
       // char *filename="";
   // #endif
    double restitution_payment=0.0;
    int i;
   
    //Benefit restitution: repayment of the already received monthly unemployment benefits if recently re-employed
    if (DAY_OF_MONTH_RECEIVE_BENEFIT != DAY_OF_MONTH_RECEIVE_INCOME )
    {
        restitution_payment = ((DAY_OF_MONTH_RECEIVE_BENEFIT + 
		(20-DAY_OF_MONTH_RECEIVE_INCOME)%20)/20.0)* UNEMPLOYMENT_PAYMENT;
		
        //Reset
        DAY_OF_MONTH_RECEIVE_BENEFIT = DAY_OF_MONTH_RECEIVE_INCOME;   
	}
    
     
    
    
    /*Send a message to the government*/
    add_unemployment_benefit_restitution_message(GOV_ID, restitution_payment);
    HOUSEHOLD_OUTFLOWS_CALENDAR.restitution_payment +=restitution_payment;

    /*Compute the total taxes*/
    TAX_PAYMENT = CUM_TOTAL_DIVIDENDS*TAX_RATE_HH_CAPITAL + WAGE*TAX_RATE_HH_LABOUR;
    
    
    //Store the net income in an array
    remove_double(&LAST_NET_INCOME,0);
         add_double(&LAST_NET_INCOME,TOTAL_INCOME-TAX_PAYMENT);
         
    //Compute the mean net income:
         
         double net_inc = 0;
         for(i=0;i<LAST_NET_INCOME.size;i++)
         {
        	 net_inc+=LAST_NET_INCOME.array[i];
         }
         MEAN_NET_INCOME = net_inc/LAST_NET_INCOME.size;

    /*Send a message to the government*/
    add_tax_payment_message(GOV_ID, TAX_PAYMENT);
    HOUSEHOLD_OUTFLOWS_CALENDAR.tax_payment += TAX_PAYMENT;

    /*Reduce the payment account*/
    PAYMENT_ACCOUNT -= restitution_payment + TAX_PAYMENT;

    /*Setting the counter of monthly dividends = 0*/
    CUM_TOTAL_DIVIDENDS=0;
    
  /*  if (PRINT_DEBUG_FILE_EXP1)
        {                       
            filename = malloc(40*sizeof(char));
            filename[0]=0;
            strcpy(filename, "its/households_tax_payments.txt");      
            file1 = fopen(filename,"a");
            fprintf(file1,"\n %d %d %f %f",DAY,ID,restitution_payment,TAX_PAYMENT);
            fclose(file1);
            free(filename);
        }  */


    return 0;

}
