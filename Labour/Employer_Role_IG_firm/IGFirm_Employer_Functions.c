#include "../header.h"
#include "../IGFirm_agent_header.h"
#include "../my_library_header.h"
#include "Labour_aux_headers.h"


/************************************ Firm agent functions ************************************/





int IGFirm_finish_labour_market_first_round()
{
	return 0;
}


int IGFirm_start_labour_market()
{
	return 0;
}



/*************************************Firm Role: Labour Market*********************************/

/** \fn IGFirm_calculate_specific_skills_and_wage_offer()
 * \brief IGFirms calculate the specific skills for each general skill group 
 * and the according wage offer*/
int IGFirm_calculate_specific_skills_and_wage_offer()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION:  IGFirm_calculate_specific_skills_and_wage_offer() \n");
		printf("************************************* \n");
	}

	/*Sum up the specific skills of each general skill group (1-5): for average*/
	double sum_1 = 0;
	
	/*For every employee*/
	for(int n = 0; n < EMPLOYEES.size; n++)
	{
		/*If employee has general skill level 1 add specific skill to sum1*/
		if(EMPLOYEES.array[n].general_skill == 1)
		{
			sum_1 = sum_1 + EMPLOYEES.array[n].specific_skill;
		}
	}

	
	if(NO_EMPLOYEES_SKILL_1 > 0)
	{	
		/*Calculate average specific skill of skill group 1*/
		AVERAGE_S_SKILL_OF_1 = sum_1/NO_EMPLOYEES_SKILL_1;
	}
			
	/*Skill Group 1-5 get the same wage offer based on the basic wage offer and the 
	productivity of skill group 1*/
	WAGE_OFFER_FOR_SKILL_1 = WAGE_OFFER*AVERAGE_S_SKILL_OF_1;
	WAGE_OFFER_FOR_SKILL_2 = WAGE_OFFER_FOR_SKILL_1;
	WAGE_OFFER_FOR_SKILL_3 = WAGE_OFFER_FOR_SKILL_1;
 	WAGE_OFFER_FOR_SKILL_4 = WAGE_OFFER_FOR_SKILL_1;
 	WAGE_OFFER_FOR_SKILL_5 = WAGE_OFFER_FOR_SKILL_1;

	WAGE_OFFER_FOR_RD = BASE_WAGE_OFFER_FOR_RD*PRODUCTIVITY;
	
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{	
		printf("WAGE_OFFER_FOR_SKILL: %f \n",WAGE_OFFER_FOR_SKILL_1);	
		printf("WAGE_OFFER_FOR_RD: %f \n",WAGE_OFFER_FOR_RD);	
		printf("************************************************* \n");
	}	
	return 0;
}


/** \fn IGFirm_send_vacancies()
 * \brief IGFirms post vacancies and wage offer and send vacancies message
 */
int IGFirm_send_vacancies()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_send_vacancies \n");
		printf("************************************* \n");
	}
					
	/*Number of Vacancies/additional employees wanted*/
	VACANCIES = EMPLOYEES_NEEDED - NO_EMPLOYEES;
	PRODUCTION_VACANCIES_POSTED = VACANCIES;
	if(VACANCIES < 0)
	{
		VACANCIES = 0;
	}

	RESEARCH_VACANCIES = RESEARCH_EMPLOYEES_NEEDED - NO_RESEARCH_EMPLOYEES;
	RESEARCH_VACANCIES_POSTED = RESEARCH_VACANCIES;

	if(RESEARCH_VACANCIES < 0)
	{
		RESEARCH_VACANCIES = 0;
	}

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("Vacancies %d \n",VACANCIES);
		printf("Research-Vacancies %d \n",RESEARCH_VACANCIES);
	}

	/*For every skill group send vacancy message with the correspondent wage 			offer*/

	if(VACANCIES > 0 )//&& RESEARCH_VACANCIES == 0)
	{	
		add_vacancies_message(ID, REGION_ID, 
        	WAGE_OFFER_FOR_SKILL_1, WAGE_OFFER_FOR_SKILL_2, 
        	WAGE_OFFER_FOR_SKILL_3, WAGE_OFFER_FOR_SKILL_4, 
        	WAGE_OFFER_FOR_SKILL_5,0);
		
		/*1: print the printf-statements*/
		if(IGFIRM_EMPLOYER_DEBUG == 1)
		{
			printf("Send vacancies: only Production: WAGE_OFFER: %f \n",WAGE_OFFER_FOR_SKILL_1);
		}
	}

	if(RESEARCH_VACANCIES > 0)
	{	
		add_vacancies_message(ID, REGION_ID, 
        	0, 0, 0, 0, 0,WAGE_OFFER_FOR_RD);

		/*1: print the printf-statements*/
		if(IGFIRM_EMPLOYER_DEBUG == 1)
		{
			printf("Send vacancies: only R&D: WAGE_OFFER: %f \n",WAGE_OFFER_FOR_RD);
		}
	}					
	
		/*1: print the printf-statements*/
		if(IGFIRM_EMPLOYER_DEBUG == 1)
		{
			printf("****************************************************************\n");
		}

	return 0;
}



/** \fn IGFirm_send_redundancies()
 * \brief Firms have to dismiss employees. Therefore the send firing_messages:
 */
int IGFirm_send_redundancies()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_send_redundancies \n");
		printf("*******************************************************************\n");
	}
		
	VACANCIES = 0;
	RESEARCH_VACANCIES = 0;
	
	/*sorting employees: highest specific skills first*/
	qsort(EMPLOYEES.array, EMPLOYEES.size, sizeof(employee),
		employee_list_rank_specific_skills_function);
		
	/*For the number of redundancies*/

	
	int no_redundancies = NO_EMPLOYEES - EMPLOYEES_NEEDED;
	int j,i;

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("no_redundancies %d \n",no_redundancies);
		printf("Employees %d \n",NO_EMPLOYEES);
	}

	for(i = 0; i < (no_redundancies); i++)	
	{	
		/*Firing: by chance*/
		j = random_int(0,(EMPLOYEES.size-1));
		add_firing_message(ID, EMPLOYEES.array[j].id);

		/*Firing: lowest specific skill*/
		/*j = EMPLOYEES.size-1;
		add_firing_message(ID, EMPLOYEES.array[j].id);*/
		
		switch(EMPLOYEES.array[j].general_skill)
		{
			/*If employee have skill level 1 reduce the number of 						
			employees with skill level 1 by 1*/
			case 1:
				NO_EMPLOYEES_SKILL_1--;
				break;
					
			case 2:
				NO_EMPLOYEES_SKILL_2--;
				break;

			case 3:
				NO_EMPLOYEES_SKILL_3--;
				break;

			case 4:
				NO_EMPLOYEES_SKILL_4--;
				break;
			/*If employee have skill level 5 reduce the number of 					
			employees with skill level 5 by 1*/
			case 5:
				NO_EMPLOYEES_SKILL_5--;
				break;
		}
			
		remove_employee(&EMPLOYEES, j);
		NO_EMPLOYEES--;		
	}

	

	int no_researcher_redundancies = NO_RESEARCH_EMPLOYEES - RESEARCH_EMPLOYEES_NEEDED;
	int k;

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("Employees %d \n",NO_EMPLOYEES);
		printf("\n");
		printf("no_researcher_redundancies %d \n",no_researcher_redundancies);
		printf("Research-Employees %d \n",NO_RESEARCH_EMPLOYEES);
	}

	for(i = 0; i < (no_researcher_redundancies); i++)	
	{
		/*Firing: by chance*/
		k = random_int(0,(RESEARCH_EMPLOYEES.size-1));
		add_firing_message(ID, RESEARCH_EMPLOYEES.array[k].id);

		remove_employee(&RESEARCH_EMPLOYEES, k);
		NO_RESEARCH_EMPLOYEES--;
		
	}

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("Research-Employees %d \n",NO_RESEARCH_EMPLOYEES);
		printf("******************************************************************\n");
	}

	return 0;
}


/** \fn Firm_send_redundancies()
* \brief Firms have to dismiss employees. Therefore the send firing_messages:
*/
int IGFirm_send_random_redundancies()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_send_random_redundancies \n");
		printf("************************************************\n");
	}

	int random_num = random_int(LOWER_BOUND_FIRING,UPPER_BOUND_FIRING);

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("Employees %d\n",NO_EMPLOYEES);  
		printf("Research_Employees %d\n",NO_RESEARCH_EMPLOYEES); 
	}
     
	/*sorting employees: highest specific skills first*/
	qsort(EMPLOYEES.array, EMPLOYEES.size, sizeof(employee),
	employee_list_rank_specific_skills_function);


	int no_redundancies = (random_num*NO_EMPLOYEES)/100;

	if(((random_num*NO_EMPLOYEES)%100) < 100 && ((random_num*NO_EMPLOYEES)%100)>0)
	{
		no_redundancies = no_redundancies+1;
	}

	
	int i,j;
	for(i = 0; i < no_redundancies; i++)
	{	 /*Firing: by chance*/
 		j = random_int(0,(EMPLOYEES.size-1));
		add_firing_message(ID, EMPLOYEES.array[j].id);

		/*Firing: lowest specific skill*/
		/*j = EMPLOYEES.size-1;
		add_firing_message(ID, EMPLOYEES.array[j].id);*/
		switch(EMPLOYEES.array[j].general_skill)
		{
			/*If employee have had skill level 1 reduce the number of                         employees with skill level 1 by 1*/
			case 1:
				NO_EMPLOYEES_SKILL_1--;
				break;

			case 2:
				NO_EMPLOYEES_SKILL_2--;
				break;

			case 3:
				NO_EMPLOYEES_SKILL_3--;
				break;

			case 4:
				NO_EMPLOYEES_SKILL_4--;
			break;
			/*If employee have had skill level 5 reduce the number of                         employees with skill level 5 by 1*/
			case 5:
				NO_EMPLOYEES_SKILL_5--;
		}
		remove_employee(&EMPLOYEES, j);
		NO_EMPLOYEES--;
	}

	/*Firing of Redsearchers*/
	no_redundancies = (random_num*NO_RESEARCH_EMPLOYEES)/100;

	if(((random_num*NO_RESEARCH_EMPLOYEES)%100) < 100 && 
	((random_num*NO_RESEARCH_EMPLOYEES)%100)>0)
	{
		no_redundancies = no_redundancies+1;
	}
	
	for(i = 0; i < no_redundancies; i++)
	{	 /*Firing: by chance*/
 		j = random_int(0,(RESEARCH_EMPLOYEES.size-1));
		add_firing_message(ID, RESEARCH_EMPLOYEES.array[j].id);
		
		remove_employee(&RESEARCH_EMPLOYEES, j);
		NO_RESEARCH_EMPLOYEES--;			
	}

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("random_num: %d;  no_redundancies: %d\n",random_num,no_redundancies);	
		printf("Employees %d\n",NO_EMPLOYEES);  
		printf("Research_Employees %d\n",NO_RESEARCH_EMPLOYEES);  
   		printf("************************************************************************\n");
	}
          
         return 0;
} 






/** \fn IGFirm_read_job_applications_send_offer_or_rejection()
 * \brief Read job applications, rank, and send job offers and rejections
 */
int IGFirm_read_job_applications_send_job_offer_or_rejection()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_read_job_applications_send_job_offer_or_rejection \n");
		printf("**********************************************************************\n");
	}

	/*only for printing */
	//int no_applications = 0;
	int no_PROD_applications = 0;
	int no_RD_applications = 0;
	int offer_count = 0;
	int RD_offer_count = 0;
	


	/* Create a job application dynamic array */
	job_application_array job_application_list; 
	init_job_application_array(&job_application_list);

	job_application_array job_application_RD_list; 
	init_job_application_array(&job_application_RD_list);
	
	/* If day of month to act... */

	START_JOB_APPLICATION_MESSAGE_LOOP
		
		/* Read job application messages for this Firm */
		if(job_application_message->firm_id == ID)
		{

			if(job_application_message->job_type == 0)
			{
				/*Add application to a list (array)*/
				add_job_application(&job_application_list, 
				job_application_message->worker_id,
				job_application_message->region_id,
				job_application_message->general_skill, 
				job_application_message->specific_skill);
				no_PROD_applications++;
			}
			
			
			if(job_application_message->job_type == 1)
			{
				add_job_application(&job_application_RD_list, 
				job_application_message->worker_id,
				job_application_message->region_id,
				job_application_message->general_skill, 
				job_application_message->specific_skill);
				no_RD_applications++;
				
				/*For every employee*/
				for(int y = 0; y < RESEARCH_EMPLOYEES.size; y++)
				{
					/*If employee has general skill level 1 add specific skill to sum1*/
					if(RESEARCH_EMPLOYEES.array[y].id == job_application_message->worker_id)
					{
						printf("STOP \n");
						printf("RESEARCH_EMPLOYEES.array[y].id  %d\n",RESEARCH_EMPLOYEES.array[y].id);
					}
				}
			}
		}


	FINISH_JOB_APPLICATION_MESSAGE_LOOP

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{	
		printf("Prod-Applications: %d\n",no_PROD_applications);
		printf("Research-Applications: %d\n",no_RD_applications);
	}
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

	/*Shuffle applications before sorting: If two or more applications are equal then they will be ranked by chance*/
	/*int i,k;
	job_application * i_job_application, * k_job_application;
	job_application * temp_job_application = (job_application *)malloc(sizeof
	(job_application));

	for(i = 0; i < (job_application_list.size);i++)
	{
		k = random_int(i, (job_application_list.size-1));

		i_job_application = &job_application_list.array[i];
		k_job_application = &job_application_list.array[k];*/

			/* Swap neighbours */
			/** temp_job_application = * i_job_application;
			* i_job_application = * k_job_application;
			* k_job_application = * temp_job_application;
	}

	free(temp_job_application);*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


	/*Rank job applications (function from my_library_functions) */
	//sort_job_application_list(&job_application_list);

	//qsort(job_application_list.array, job_application_list.size, 
	//sizeof(job_application), job_application_list_rank_general_skill_function);

	//qsort(job_application_RD_list.array, job_application_RD_list.size, 
	//sizeof(job_application), job_application_list_rank_general_skill_function);
	/*Send job offers to research workers*/

	
	int l,m;
	for(l = 0; l < (job_application_RD_list.size); l++)
	{
		if(l < RESEARCH_VACANCIES) 
		{
			add_job_offer_message(ID, 
			job_application_RD_list.array[l].worker_id,REGION_ID, WAGE_OFFER_FOR_RD,1);

			RD_offer_count++;

			/*In case that the worker applied for production and research he has 
			to be removed form the production-list because he can have only one job*/
			
			for(m = 0; m < (job_application_list.size); m++)
			{
				if(job_application_RD_list.array[l].worker_id ==  
				job_application_list.array[m].worker_id)
				{
					remove_job_application(&job_application_list,m);
				}
			}
		
		}
		else
		{
			//add_application_rejection_message(ID, 
			//job_application_RD_list.array[l].worker_id);
			//break;
		}
		
	}

	if(no_PROD_applications < VACANCIES)
	{ 

		int i;
		for(i = 0 ; i < (job_application_list.size); i++)
		{
			/*A firm cannot send more job offers than it has vacancies to fill*/
			/*l can be interpreted as the number of job offers which were sent to 
			research_workers. These workers should not get another offer*/

			if(i < VACANCIES)
			{
				offer_count++;
	
				add_job_offer_message(ID, job_application_list.array[i]
				.worker_id,REGION_ID, WAGE_OFFER_FOR_SKILL_1,0);
			}
		
			/* If no vacancies left then send a job rejection message */
			else
			{
				//add_application_rejection_message(ID, 
				//job_application_list.array[i].worker_id);
				//d++;
			}
		}
	}

	else //if(no_PROD_applications > VACANCIES)
	{
		int i;
		for(i = 0; i< VACANCIES; i++)
		{
			logit_array  logit_applications_list;
			init_logit_array(&logit_applications_list);

			/*Computing the dominator of the logit*/
			double denominator_logit = 0;
			double logit, sum_of_logits;
			double random_number;
		
			int j;
			for(j = 0; j< job_application_list.size;j++)
			{
				denominator_logit+= 
				exp(0.0*job_application_list.array[j].general_skill +
				0*job_application_list.array[j].specific_skill);
			}

			/*This computes the logits and stores them at the temorary array 				
			logit_applications_list*/

			for( j = 0; j< job_application_list.size;j++)
			{
				logit = exp(0.0*job_application_list.array[j].general_skill +
				0*job_application_list.array[j].specific_skill)/ denominator_logit;
		
				add_logit(&logit_applications_list, 100*logit,job_application_list.
				array[j].worker_id,job_application_list.array[j].general_skill);
			
			}
		
			/*This draws a random number*/
			random_number =  (double)random_int(0,100);
			sum_of_logits = 0;
		
			for(j = 0; j< logit_applications_list.size;j++)
			{
				sum_of_logits += logit_applications_list.array[j].logit_value;
	
				if(random_number < sum_of_logits)
				{
					/*If condition is true, the firm chooses that worker and send a
 					job offer with the corresponding wage offer   */
 					offer_count++;	

					add_job_offer_message(ID, logit_applications_list.
					array[j].worker_id,REGION_ID, WAGE_OFFER_FOR_SKILL_1,0);
					
				

				/*The chosen worker has to be removed from the application list*/

				   int k;
				   for(k = 0; k< job_application_list.size;k++)
				   {
					if(job_application_list.array[k].worker_id == 
					logit_applications_list.array[j].worker_id)
					{
						remove_job_application(&job_application_list,k);
						break;
					}
				   }

				break;	
				}	
			}

			/* Free the job application dynamic array */
			free_logit_array(&logit_applications_list);
		}
	} 
	
	/* Free the job application dynamic array */
	free_job_application_array(&job_application_list);
	free_job_application_array(&job_application_RD_list);

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("Prod-Offer: %d\n",offer_count);
		printf("Research-Offer: %d\n",RD_offer_count);	
		printf("**********************************************************************\n");	
	}

	return 0;
}



/** \fn Firm_read_job_responses()
 * \brief Read job responses and add employees
 */
int IGFirm_read_job_responses()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_read_job_responses \n");
		printf("**************************************************************************\n");
	}
			
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{	
		printf("Vacancies %d\n",VACANCIES);
		printf("Research-Vacancies %d\n",RESEARCH_VACANCIES);
	}
	
	START_JOB_ACCEPTANCE_MESSAGE_LOOP
		
		/* Read job acceptance messages for this Firm */
		if(job_acceptance_message->firm_id == ID)
		{
			
			/*Add employee to employee list */
			if(job_acceptance_message->job_type == 0)
			{
				VACANCIES--;
				NO_EMPLOYEES++;
			}
			else//if(job_acceptance_message->job_type == 1)
			{
				NO_RESEARCH_EMPLOYEES++;
					RESEARCH_VACANCIES--;
			}

			switch(job_acceptance_message->general_skill)
			{
				/*If new employee has general skill level 1*/
				case 1:
					add_employee(&EMPLOYEES, 
					job_acceptance_message->worker_id,
					job_acceptance_message->region_id, 								
					WAGE_OFFER_FOR_SKILL_1, 
					job_acceptance_message->general_skill, 
					job_acceptance_message->specific_skill);

					NO_EMPLOYEES_SKILL_1++;
					break;
			
				case 2:
					add_employee(&EMPLOYEES, 
					job_acceptance_message->worker_id,
					job_acceptance_message->region_id, 							
					WAGE_OFFER_FOR_SKILL_2, 
					job_acceptance_message->general_skill, 
					job_acceptance_message->specific_skill);

					NO_EMPLOYEES_SKILL_2++;
					break;
			
				case 3:
					add_employee(&EMPLOYEES, 
					job_acceptance_message->worker_id,
					job_acceptance_message->region_id, 							
					WAGE_OFFER_FOR_SKILL_3, 
					job_acceptance_message->general_skill, 
					job_acceptance_message->specific_skill);

					NO_EMPLOYEES_SKILL_3++;
					break;
			
				case 4:
					add_employee(&EMPLOYEES, 
					job_acceptance_message->worker_id,
					job_acceptance_message->region_id, 							
					WAGE_OFFER_FOR_SKILL_4, 
					job_acceptance_message->general_skill, 
					job_acceptance_message->specific_skill);
					
					NO_EMPLOYEES_SKILL_4++;
					break;
				/*If new employee has general skill level 5*/
				case 5:
					
					// Add to production workers
					if(job_acceptance_message->job_type == 0)
					{	
						add_employee(&EMPLOYEES, 
						job_acceptance_message->worker_id,
						job_acceptance_message->region_id, 						
						WAGE_OFFER_FOR_SKILL_5, 
						job_acceptance_message->general_skill, 
						job_acceptance_message->specific_skill);

						NO_EMPLOYEES_SKILL_5++;
					}
					// Add to Researchers
					else//if(job_acceptance_message->job_type == 1)
					{
						add_employee(&RESEARCH_EMPLOYEES, 
						job_acceptance_message->worker_id,
						job_acceptance_message->region_id, 						
						WAGE_OFFER_FOR_RD, 
						job_acceptance_message->general_skill, 
						job_acceptance_message->specific_skill);
					}	
					break;		
			}			
		}

	FINISH_JOB_ACCEPTANCE_MESSAGE_LOOP

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("Employees %d\n",NO_EMPLOYEES);
		printf("Research-Employees %d\n",NO_RESEARCH_EMPLOYEES);
		printf("Vacancies %d\n",VACANCIES);
		printf("Research-Vacancies %d\n",RESEARCH_VACANCIES);
		printf("***************************************************************************\n");	
	}


	return 0;
}



int IGFirm_read_job_quitting()
{
	
	return 0;
}


/** \fn IGFirm_update_wage_offer()
 * \brief IGFirms update wage_offer to get more applications
 */
int IGFirm_update_wage_offer()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_update_wage_offer \n");
		printf("*********************************************************************** \n");
		printf("WAGE_OFFER %f\n",WAGE_OFFER);
		printf("BASE_WAGE_OFFER_FOR_RD %f\n",BASE_WAGE_OFFER_FOR_RD);
	}
		
	/*If there are "a lot" of vacancies still open...*/	
	if(VACANCIES > MIN_VACANCY)  
	{
		WAGE_OFFER = WAGE_OFFER*(1+WAGE_UPDATE);
	}


	/*If research vacancies are still open*/
	if(RESEARCH_VACANCIES > 0)
	{
		BASE_WAGE_OFFER_FOR_RD = BASE_WAGE_OFFER_FOR_RD*(1+WAGE_UPDATE);
	}

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("WAGE_OFFER %f\n",WAGE_OFFER);
		printf("BASE_WAGE_OFFER_FOR_RD %f\n",BASE_WAGE_OFFER_FOR_RD);		
		printf("******************************************************************* \n");
	}	
	return 0;
}


/** \fn IGFirm_send_vacancies_2()
 * \brief IGFirms which  did not fill all vacancies post vacancies and wage offer and send vacancies message
 */
int IGFirm_send_vacancies_2()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_send_vacancies_2 \n");
		printf("**************************************************************************** \n");

		printf("Vacancies %d \n",VACANCIES);
		printf("Research-Vacancies %d \n",RESEARCH_VACANCIES);
	}


	if(VACANCIES > 0)// && RESEARCH_VACANCIES == 0)
	{	
		add_vacancies2_message(ID, REGION_ID, 
        	WAGE_OFFER_FOR_SKILL_1, WAGE_OFFER_FOR_SKILL_2, 
        	WAGE_OFFER_FOR_SKILL_3, WAGE_OFFER_FOR_SKILL_4, 
        	WAGE_OFFER_FOR_SKILL_5,0);

		/*1: print the printf-statements*/
		if(IGFIRM_EMPLOYER_DEBUG == 1)
		{
			printf("Send vacancies: only Production WAGE OFFER %f\n",WAGE_OFFER_FOR_SKILL_1);
		}
	}

	if(RESEARCH_VACANCIES > 0)
	{	
		add_vacancies2_message(ID, REGION_ID, 
        	0, 0, 0, 0, 0,WAGE_OFFER_FOR_RD);
		
		/*1: print the printf-statements*/
		if(IGFIRM_EMPLOYER_DEBUG == 1)
		{
			printf("Send vacancies: only research WAGE OFFER %f\n",WAGE_OFFER_FOR_RD);
		}

	}	
			
			
	/*1: print the printf-statements*/
		if(IGFIRM_EMPLOYER_DEBUG == 1)
		{	
			printf("******************************************************************** \n");
		}

	return 0;
}

/** \fn IGFirm_read_job_applications_send_offer_or_rejection()_2
 * \brief Read job applications, rank, and send job offers and rejections
 */
int IGFirm_read_job_applications_send_job_offer_or_rejection_2()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_read_job_applications_send_job_offer_or_rejection2 \n");
		printf("************************************************\n");
	}

	/*only for printing */
	int no_applications = 0;
	int no_PROD_applications = 0;
	int no_RD_applications = 0;
	int offer_count = 0;
	int RD_offer_count = 0;


	/* Create a job application dynamic array */
	job_application_array job_application_list; 
	init_job_application_array(&job_application_list);

	job_application_array job_application_RD_list; 
	init_job_application_array(&job_application_RD_list);
	
	/* If day of month to act... */

	START_JOB_APPLICATION2_MESSAGE_LOOP
		
		/* Read job application messages for this Firm */
		if(job_application2_message->firm_id == ID)
		{

			if(job_application2_message->job_type == 0)
			{
				/*Add application to a list (array)*/
				add_job_application(&job_application_list, 
				job_application2_message->worker_id,
				job_application2_message->region_id,
				job_application2_message->general_skill, 
				job_application2_message->specific_skill);
				no_PROD_applications++;
			}
			
			
			if(job_application2_message->job_type == 1)
			{
				add_job_application(&job_application_RD_list, 
				job_application2_message->worker_id,
				job_application2_message->region_id,
				job_application2_message->general_skill, 
				job_application2_message->specific_skill);
				no_RD_applications++;
			}
			no_applications++;


		}


	FINISH_JOB_APPLICATION2_MESSAGE_LOOP
	
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{	
		printf("Prod-Applications: %d\n",no_PROD_applications);
		printf("Research-Applications: %d\n",no_RD_applications);
	}

	/* Rank job applications (function from my_library_functions) */
	//sort_job_application_list(&job_application_list);
	
	//qsort(job_application_list.array, job_application_list.size, 
	//sizeof(job_application), job_application_list_rank_general_skill_function);

	//qsort(job_application_RD_list.array, job_application_RD_list.size, 
	//sizeof(job_application), job_application_list_rank_general_skill_function);
	/*Send job offers to research workers*/

	
	int l,m;
	for(l = 0; l < (job_application_RD_list.size); l++)
	{
		if(l < RESEARCH_VACANCIES) //&& job_application_list.array[l].general_skill == 6)
		{
			add_job_offer2_message(ID, job_application_RD_list.array[l]
				.worker_id,REGION_ID, WAGE_OFFER_FOR_RD,1);
	
			RD_offer_count++;

			/*In case that the worker applied for production and research he has 
			to be removed form the production-list because he can have only one job*/
			for(m = 0; m < (job_application_list.size); m++)
			{
				if(job_application_RD_list.array[l].worker_id ==  
				job_application_list.array[m].worker_id)
				{
					remove_job_application(&job_application_list,m);
				}
			}
		}
		else
		{
			//add_application_rejection2_message(ID, 
			//job_application_RD_list.array[l].worker_id);
			//break;
		}
		
	}

	
	/*For each job application message... */

	if(no_PROD_applications < VACANCIES)
	{ 
		int i;
		for(i = 0 /*l*/; i < (job_application_list.size); i++)
		{
			/*A firm cannot send more job offers than it has vacancies to fill*/
			/*l can be interpreted as the number of job offers which were sent to 
			research_workers. These workers should not get another offer*/

			if(i < VACANCIES)
			{
				offer_count++;

				add_job_offer2_message(ID, 
				job_application_list.array[i].worker_id,REGION_ID, WAGE_OFFER_FOR_SKILL_1,0);
			}
		
			/* If no vacancies left then send a job rejection message */
			else
			{
				//add_application_rejection2_message(ID, 
				//job_application_list.array[i].worker_id);
				//d++;
			}
		}
	}

	else //if(no_PROD_applications > VACANCIES)
	{
		int i;
		for(i = 0; i< VACANCIES; i++)
		{
			logit_array  logit_applications_list;
			init_logit_array(&logit_applications_list);

			/*Computing the dominator of the logit*/
			double denominator_logit = 0;
			double logit, sum_of_logits;
			double random_number;
		
			int j;
			for(j = 0; j< job_application_list.size;j++)
			{
				denominator_logit+= 
				exp(0.0*job_application_list.array[j].general_skill +
				0*job_application_list.array[j].specific_skill);
			}

			/*This computes the logits and stores them at the temorary array 				logit_applications_list*/

			for(j = 0; j< job_application_list.size;j++)
			{
				logit = exp(0.0*job_application_list.array[j].general_skill +
				0*job_application_list.array[j].specific_skill)/ denominator_logit;
		
				add_logit(&logit_applications_list, 100*logit,job_application_list.
				array[j].worker_id,job_application_list.array[j].general_skill);
			
			}
		
			/*This draws a random number*/
			random_number =  (double)random_int(0.0,100.0);
			sum_of_logits = 0;
		
			for(j = 0; j< logit_applications_list.size;j++)
			{
				sum_of_logits += logit_applications_list.array[j].logit_value;
	
				if(random_number < sum_of_logits)
				{
					/*If condition is true, the firm chooses that worker and send a
 					job offer with the corresponding wage offer   */
 				
					offer_count++;
				   
					add_job_offer2_message(ID, logit_applications_list.
					array[j].worker_id,REGION_ID, WAGE_OFFER_FOR_SKILL_1,0);

				/*The chosen worker has to be removed from the application list*/
					
				int k;
				   for(k = 0; k< job_application_list.size;k++)
				   {
					if(job_application_list.array[k].worker_id == 
					logit_applications_list.array[j].worker_id)
					{
						remove_job_application(&job_application_list,k);
						break;
					}
				  }
				break;	
				}	
			}

			/* Free the job application dynamic array */
			free_logit_array(&logit_applications_list);
		}
	} 

	/* Free the job application dynamic array */
	free_job_application_array(&job_application_list);
	free_job_application_array(&job_application_RD_list);

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{	
		printf("Prod-Offer: %d\n",offer_count);
		printf("Research-Offer: %d\n",RD_offer_count);
		printf("************************************************************************\n");	
	}

	return 0;
}


/** \fn IGFirm_read_job_responses_2()
 * \brief Read job responses and add employees
 */
int IGFirm_read_job_responses_2()
{
	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("IN FUNCTION: IGFirm_read_job_responses_2 \n");
		printf("*************************************************************************\n");
	
		printf("Vacancies %d\n",VACANCIES);
		printf("Research-Vacancies %d\n",RESEARCH_VACANCIES);
	}
	
	START_JOB_ACCEPTANCE2_MESSAGE_LOOP

		/* Read job acceptance messages for this Firm */
		if(job_acceptance2_message->firm_id == ID)
		{
			/*Add employee to employee list*/ 
			if(job_acceptance2_message->job_type == 0)
			{
				VACANCIES--;
				NO_EMPLOYEES++;
			}
			else//if(job_acceptance2_message->job_type == 1)
			{
				NO_RESEARCH_EMPLOYEES++;
				RESEARCH_VACANCIES--;
			}

			switch(job_acceptance2_message->general_skill)
			{
				/*If new employees has general skill level 1*/
				case 1:
					add_employee(&EMPLOYEES, 
					job_acceptance2_message->worker_id,
					job_acceptance2_message->region_id, 							
					WAGE_OFFER_FOR_SKILL_1, 
					job_acceptance2_message->general_skill, 						
					job_acceptance2_message->specific_skill);
					
					NO_EMPLOYEES_SKILL_1++;
					break;
			
				case 2:
					add_employee(&EMPLOYEES, 
					job_acceptance2_message->worker_id,
					job_acceptance2_message->region_id, 							
					WAGE_OFFER_FOR_SKILL_2, 
					job_acceptance2_message->general_skill, 						
					job_acceptance2_message->specific_skill);

					NO_EMPLOYEES_SKILL_2++;
					break;
			
				case 3:
					add_employee(&EMPLOYEES, 
					job_acceptance2_message->worker_id,
					job_acceptance2_message->region_id, 							
					WAGE_OFFER_FOR_SKILL_3, 
					job_acceptance2_message->general_skill, 						
					job_acceptance2_message->specific_skill);

					NO_EMPLOYEES_SKILL_3++;
					break;
			
				case 4:
					add_employee(&EMPLOYEES, 
					job_acceptance2_message->worker_id,
					job_acceptance2_message->region_id, 							
					WAGE_OFFER_FOR_SKILL_4, 
					job_acceptance2_message->general_skill, 						
					job_acceptance2_message->specific_skill);

					NO_EMPLOYEES_SKILL_4++;
					break;
				/*If new employees has general skill level 5*/
				case 5:

					if(job_acceptance2_message->job_type == 0)
					{
						add_employee(&EMPLOYEES, 
						job_acceptance2_message->worker_id,
						job_acceptance2_message->region_id, 						
						WAGE_OFFER_FOR_SKILL_5, 
						job_acceptance2_message->general_skill, 
						job_acceptance2_message->specific_skill);

						NO_EMPLOYEES_SKILL_5++;
					}
					else//if(job_acceptance2_message->job_type == 1)
					{
						add_employee(&RESEARCH_EMPLOYEES, 
						job_acceptance2_message->worker_id,
						job_acceptance2_message->region_id, 						
						WAGE_OFFER_FOR_RD, 
						job_acceptance2_message->general_skill, 
						job_acceptance2_message->specific_skill);	
					}
					break;
			}
		}

	FINISH_JOB_ACCEPTANCE2_MESSAGE_LOOP

	/*1: print the printf-statements*/
	if(IGFIRM_EMPLOYER_DEBUG == 1)
	{
		printf("Employees %d\n",NO_EMPLOYEES);
		printf("Research-Employees %d\n",NO_RESEARCH_EMPLOYEES);
		printf("Vacancies %d\n",VACANCIES);
		printf("Research-Vacancies %d\n",RESEARCH_VACANCIES);
		printf("***********************************************************************\n");
	}
		
	return 0;
}



int IGFirm_read_job_quitting_2()
{


	return 0;
}

/** \fn IGFirm_update_wage_offer_2()
 * \brief Firms update wage_offer to get more applications in next iteration
 */
int IGFirm_update_wage_offer_2()
{
	return 0;
}


int IGFirm_compute_mean_wage_specific_skills()
{

	double ave_wage =0.0;
	double ave_spec_skills =0.0;

	double ave_research_wage =0.0;
	double ave_research_spec_skills =0.0;
	
	for(int i=0;i<EMPLOYEES.size;i++)
	{
		ave_wage+=EMPLOYEES.array[i].wage;
		ave_spec_skills += EMPLOYEES.array[i].specific_skill;
	}

	for(int i=0;i<RESEARCH_EMPLOYEES.size;i++)
	{
		ave_research_wage+=RESEARCH_EMPLOYEES.array[i].wage;
		ave_research_spec_skills += RESEARCH_EMPLOYEES.array[i].specific_skill;
	}
	
	double no_employees = (double) NO_EMPLOYEES;
	if(no_employees==0)
	{
		MEAN_WAGE = WAGE_OFFER;
		MEAN_SPECIFIC_SKILLS = MEAN_SPECIFIC_SKILLS;
	}
	else
	{
		MEAN_WAGE = ave_wage /( no_employees);
		MEAN_SPECIFIC_SKILLS =ave_spec_skills/no_employees;
	}

	double no_research_employees = (double) NO_RESEARCH_EMPLOYEES;
	if(no_research_employees==0)
	{
		MEAN_RESEARCH_WAGE = WAGE_OFFER_FOR_RD;
		MEAN_RESEARCH_SPECIFIC_SKILLS = AVERAGE_S_SKILL_OF_5;
	}
	else
	{
		MEAN_RESEARCH_WAGE = ave_research_wage /( no_research_employees);
		MEAN_RESEARCH_SPECIFIC_SKILLS =ave_research_spec_skills/no_research_employees;
	}


	return 0;
}

