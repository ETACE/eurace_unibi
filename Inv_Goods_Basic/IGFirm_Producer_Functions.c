#include "../header.h"
#include "../IGFirm_agent_header.h"
#include "../my_library_header.h"





/***************************** Investment Goods producer function********************************/
/** \fn IGFirm_update_productivity()
 * \brief IGFirm inceases productivity via a stochastic process.
 	- Depending on the number of research employees the probability of an innovation (RD project finished) is
 	  calculated. 
	- If the project is finished the productivity progress is determined. The base progress is 2.5% plus a random 
	  progress which is (nearly) normal distributed between -5% and +5% with mean zero.*/
int IGFirm_update_productivity()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif


	int i,j;
	/*Increase this variable to get a lower variance of the normal distribution/the random
	progress*/
	int influence_the_variance = 75; 
	double k;
	double random_progress=0.0;
	double innovation_probability;
		
	/*Create normal distributed random number: mean~0, standard deviation ~ 0.01*/
	for(j = 0; j < 12; j++)
	{
		k = (double)(random_int(0, 1000))/1000;
		random_progress += ((k - 0.5)/influence_the_variance);	
	}

	/*Duration between two innovations*/
	DURATION_UNTIL_NEXT_INNOVATION += 12;
	/*Reset the indicator variable for an innovation*/
	INNOVATION_SUCCESS = 0;
		
	
	/*1.Step: Innovation process:
	Calculate the probability of completing the innovation project depending on the number of research employees: 
	The probability can not be larger than 1*/
	if((NO_RESEARCH_EMPLOYEES*EFFICIENCY_INNOVATION) <= 1)
	{
		innovation_probability = NO_RESEARCH_EMPLOYEES*EFFICIENCY_INNOVATION;	
	}
	else //if NO_RESEARCH_EMPLOYEES*EFFICIENCY_INNOVATION > 1
	{
		/*Project completed.*/
		innovation_probability = 1;	
	}


	i = random_int( 1 ,100);
	
	
	/*2.Step: Innovation process:
	Check if the innovation probability is larger than the random number i. If yes than the project is completed. */
	if((innovation_probability * 100) >= i)
	{
		/*If progress is larger than zero/positiv-> Successful Innovation. 
		Calculate the additional productivity and update the productivity. If there is negative progress
		the project was completed but was not successful and the productivity will not be updated.*/
		if((random_progress + PRODUCTIVITY_PROGRESS) > 0)
		{
			INNOVATION_SUCCESS = 1;
			ADDITIONAL_PRODUCTIVITY =  (PRODUCTIVITY_PROGRESS + random_progress);
			NEW_PRODUCTIVITY = PRODUCTIVITY*(1 + ADDITIONAL_PRODUCTIVITY);
		}
	}

	
	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_update_productivity()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," Innovation_probability: %f\n",innovation_probability);
		fprintf(file1," PRODUCTIVITY %f\n",PRODUCTIVITY);
		fprintf(file1," NEW_PRODUCTIVITY %f\n",NEW_PRODUCTIVITY);
		fprintf(file1," ADDITIONAL_PRODUCTIVITY %f\n",ADDITIONAL_PRODUCTIVITY);
		fprintf(file1,"\n");
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	}
	

/**********************TEST: NORMAL DISTRIBUTION************************************************/
	/*int l,m,counter;
	counter = 1000000;
	double one,two,three,four,five,six,seven,eight,nine,ten,small,big;
	double diff[counter];
	double  sum,variance,deviation;
	sum=0.0;
	for( l = 0 ; l < counter; l++)
	{ 
		random_progress = 0.0;
		for(j = 0; j < 12; j++)
		{
			k = (double)(random_int(0, 1000))/1000;
			random_progress += ((k - 0.5)/75);	
		}

		diff[l]= random_progress;
		random_progress = random_progress/1; //printf("PROGRESS  %f\n",random_progress);
		//printf("sum %f\n",sum);
		sum += random_progress;

		if(-0.05 < random_progress && random_progress <= -0.04)
		{
			one++;//printf(" 1 \n");
		}
		if(-0.04 < random_progress && random_progress <= -0.03)
		{
			two++;//printf(" 2 \n");
		}
		if(-0.03 < random_progress && random_progress <= -0.02)
		{
			three++;//printf(" 3 \n");
		}
		if(-0.02 < random_progress  && random_progress <= -0.01)
		{
			four++;//printf(" 4 \n");
		}
		if(-0.01 < random_progress  && random_progress <= 0)
		{
			five++;//printf(" 5 \n");
		}
		if(0 < random_progress  && random_progress <= 0.01)
		{
			six++;//printf(" 6 \n");
		}
		if(0.01 < random_progress  && random_progress <= 0.02)
		{
			seven++;//printf(" 7 \n");
		}
		if(0.02 < random_progress  && random_progress <= 0.03)
		{
			eight++;//printf(" 8 \n");
		}
		if(0.03 < random_progress  && random_progress <=0.04)
		{
			nine++;//printf(" 9 \n");
		}
		if(0.04 < random_progress  && random_progress <=0.05)
		{
			ten++;//printf(" 10 \n");
		}
		if(-0.05 >= random_progress)
		{
			small++;//printf(" small \n");
		}
		if(0.05 < random_progress)
		{
			big++;//printf(" big \n");
		}

		
	}

	sum= sum/counter;
	printf("sum %f\n",sum);

	for(m=0; m < counter; m++)
	{	
		//printf("DIFF %f\n",pow((diff[m] - sum),2));
		variance += pow((diff[m] - sum),2);
	}

	variance = variance/counter;
	printf("VARIANCE  %f\n",variance);
	deviation = pow(variance,0.5);
	printf("deviation  %f\n",deviation);

	printf("%f  %f  %f  %f  %f  %f  %f  %f  %f  %f	%f  %f\n" ,one,two,three,four,five, 	
	six,seven,eight,nine,ten,small, big);*/

	return 0;
}




/** \fn int IGFirm_calc_research_employees()
 * \brief IGFirm determines the number of research_employees.
	- IGFirm invests 10% of the last year revenues for RD (Wages for Research Employees). */
int IGFirm_calc_research_employees()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif
	
	/*If there was a successfull innovation in this period.*/
	if(INNOVATION_SUCCESS == 1)
	{	
		/*"Start" of new innovation period*/
		DURATION_UNTIL_NEXT_INNOVATION = 0;
		CAPITAL_GOOD_DEMAND_AFTER_LAST_INNOVATION = 0;	
	}


	/*1. option: The number Research employees is determined when there is a successful 	
	Innovation*/
	
	/*if(INNOVATION_SUCCESS == 1 )
	{
		RESEARCH_EMPLOYEES_NEEDED = (int) (PERCENT_REVENUE_FOR_INNOVATION*
		(REVENUE_FOR_INNOVATION/DURATION_UNTIL_NEXT_INNOVATION)
		/WAGE_OFFER_FOR_RD);

		REVENUE_FOR_INNOVATION = 0;

	}*/

	/*To be sure to have at least some R&D*/
	/*if(NO_RESEARCH_EMPLOYEES == 0 && INNOVATION_SUCCESS == 0)
	{
		RESEARCH_EMPLOYEES_NEEDED = (int) (PERCENT_REVENUE_FOR_INNOVATION*
		(REVENUE_FOR_INNOVATION/DURATION_UNTIL_NEXT_INNOVATION)
		/WAGE_OFFER_FOR_RD);

		if(RESEARCH_EMPLOYEES_NEEDED > 10)
		{
			RESEARCH_EMPLOYEES_NEEDED = 10;
		}
		
	}*/

	/*2. option: The number Research employees is determined every year*/
	
	/*Determine the number of research employees based on the monthly RD 
	budget (REVENUE_FOR_INNOVATION/12) and the expected wages.*/
	RESEARCH_EMPLOYEES_NEEDED = (int) (PERCENT_REVENUE_FOR_INNOVATION*
	(REVENUE_FOR_INNOVATION/12))/WAGE_OFFER_FOR_RD;

	/*Resetting: REVENUE_FOR_INNOVATION sums up the revenues in the next year.*/
	REVENUE_FOR_INNOVATION = 0;
	

	/*1: complete functionality of the IGFirm -- 0: Exogenous stochastic innovation process  */
	if(IGFIRM_SWITCH_ON == 0)
	{
		/*Research employees are not needed if IGFirm is not switched on.*/
		RESEARCH_EMPLOYEES_NEEDED = 0;
	}

	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_calc_research_employees()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," REVENUE_FOR_INNOVATION = %f\n",REVENUE_FOR_INNOVATION/12);
		fprintf(file1," WAGE_OFFER_FOR_RD = %f\n",WAGE_OFFER_FOR_RD);
		fprintf(file1," RESEARCH_EMPLOYEES_NEEDED = %d \n",RESEARCH_EMPLOYEES_NEEDED);
		fprintf(file1,"\n");
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	}

	return 0;
}




int IGFirm_set_quantities_zero()
{

	return 0;
}




/** \fn IGFirm_update_productivity_price()
 * \brief IGFirm send quality and price information.
	- If the functionality of the IGFirm is switched off it updates the productivity and the price. */
int IGFirm_send_quality_price_info()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif

	int i,j;
	double prod_progress, price_worst_vintage_last_month, discounted_productivity_worst_vintage_last_month, sum, s_skills;

	price_worst_vintage_last_month= VINTAGES.array[0].price;
        discounted_productivity_worst_vintage_last_month = VINTAGES.array[0].discounted_productivity;
	
	/*1: complete functionality of the IGFirm -- 0: Exogenous stochastic innovation process  */
	if(IGFIRM_SWITCH_ON == 0)
	{
		RESEARCH_EMPLOYEES_NEEDED = 0;
		
		/*Reinitialize some variables for a correct balance sheet if the functionality of the IGFirm is switched off.*/
		if(DAY == 1)
		{
			//CAPITAL_GOOD_PRICE = PRODUCTIVITY;
			PAYMENT_ACCOUNT = 0.0;
			CAPITAL_GOOD_STORE = 0.0;
			TOTAL_VALUE_LOCAL_INVENTORY = 0.0;
			EQUITY = 0.0;
			TOTAL_ASSETS = 0.0;
			RESEARCH_EMPLOYEES_NEEDED = 0.0;
		}

		/*If the innovation progress is random and has not a predetermined shape*/
		if(INNOVATION_BY_RANDOM==1)
		{
			/*If transition phase is over. During the transition phase there is no productivity progress.*/
			if(DAY >= TRANSITION_PHASE)
	 		{
				if(DAY%MONTH == DAY_OF_MONTH_TO_ACT)
				{	
					i = random_int( 0 ,100);
					/*If i is smaller than the exogenous innovation probability the productivity and the price will be increased.*/
					if(i < IGFIRM_EXOGENOUS_INNOVATION_PROBABILITY)
					{
						PRODUCTIVITY = PRODUCTIVITY*(1 + IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);
						CAPITAL_GOOD_PRICE = 
						CAPITAL_GOOD_PRICE*(1 +IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);	

						
						//add new one:
						add_vintage(&VINTAGES,PRODUCTIVITY, CAPITAL_GOOD_PRICE,0,0);	

						add_adt_sales_per_vintage(&SALES_PER_VINTAGE,PRODUCTIVITY, 0.0,0.0 );

					}
	 			}
			}
		}
		else//Innovation progress has a predetermined shape: 3 cases, with low, medium and high tech progress
		{
			if(STRENGHT_OF_TECH_PROGRESS ==2)
			{
				if(DAY==INNOVATION_SHEME_MEDIUM_PROGRESS.array[0])
				{
				prod_progress =PRODUCTIVITY*IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS;

				PRODUCTIVITY =PRODUCTIVITY*(1+IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);

				CAPITAL_GOOD_PRICE = CAPITAL_GOOD_PRICE*(1
				+IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);
				
				remove_int(&INNOVATION_SHEME_MEDIUM_PROGRESS,0);
				
				//add new one:
				add_vintage(&VINTAGES,PRODUCTIVITY, CAPITAL_GOOD_PRICE,0,0);

				add_adt_sales_per_vintage(&SALES_PER_VINTAGE,PRODUCTIVITY, 0.0,0.0 );
				
				}
			}else if(STRENGHT_OF_TECH_PROGRESS==3)
			{
				if(DAY==INNOVATION_SHEME_HIGH_PROGRESS.array[0])
				{
				prod_progress =PRODUCTIVITY*IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS;

				PRODUCTIVITY =PRODUCTIVITY*(1+IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);

				CAPITAL_GOOD_PRICE = CAPITAL_GOOD_PRICE*(1
				+IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);
				
				remove_int(&INNOVATION_SHEME_HIGH_PROGRESS,0);

				//add new one:
				add_vintage(&VINTAGES,PRODUCTIVITY, CAPITAL_GOOD_PRICE,0,0);

				add_adt_sales_per_vintage(&SALES_PER_VINTAGE,PRODUCTIVITY, 0.0,0.0 );
				}

			}else
			{

				if(DAY==INNOVATION_SHEME_LOW_PROGRESS.array[0])
				{
				prod_progress =PRODUCTIVITY*IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS;

				PRODUCTIVITY =PRODUCTIVITY*(1+IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);

				CAPITAL_GOOD_PRICE = CAPITAL_GOOD_PRICE*(1
				+IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);
				
				remove_int(&INNOVATION_SHEME_LOW_PROGRESS,0);


				if(IG_GOOD_LIMITED_OFFER == 1 && VINTAGES.size >= MAX_OFFER_IG_GOOD)
			{
				//remove last entry (oldest vintage)				
				//remove_vintage(&VINTAGES,0);
				}				

	//add new one:
				add_vintage(&VINTAGES,PRODUCTIVITY, CAPITAL_GOOD_PRICE,0,0);

				add_adt_sales_per_vintage(&SALES_PER_VINTAGE,PRODUCTIVITY, 0.0,0.0 );
				}
			}
		}
	}

	/*IGFirm sends the producitivity and the capital good price to the consumption good firms.*/
	
	/*based on the total value of the capital stock and last month investments the firm computes mean mean productivity value for each vintage*/

	//printf(" ECONOMY_WIDE_SPECIFIC_SKILLS_IN_FIRMS %f\n", ECONOMY_WIDE_SPECIFIC_SKILLS_IN_FIRMS);

	for(i=0;i<VINTAGES.size;i++)
	{
		 
	//printf("ECONOMY_WIDE_SPECIFIC_SKILLS_IN_FIRMS %f\n",ECONOMY_WIDE_SPECIFIC_SKILLS_IN_FIRMS);

		// here we compute the discounted sum of productivites over a planning period
		sum =0.0;
		s_skills = ECONOMY_WIDE_SPECIFIC_SKILLS_IN_FIRMS;
		for(j=0;j<24;j++)
		{
			if(SKILL_UPGRADE_PREDETERMINED==0)
				{
      				/*Update the specific skill: depends on the actual specific skill, 
        			the gap between the actual specific skills and the actual productivity of the employer,
        			and the general skill which determines the speed of closing the this gap.*/
       				s_skills = max(s_skills,s_skills+ (VINTAGES.array[i].productivity - s_skills)
				*((1-pow(0.5,1/(20+0.25*(ECONOMY_WIDE_GENERAL_SKILLS_IN_FIRMS-1)*(4-20))))));
				}else
				{
	 			 /*Update the specific skill: depends on the actual specific skill, 
       				 the gap between the actual specific skills and the actual productivity of the employer. The rate is predetermined.*/
					
					if(SKILL_UPGRADE_PREDETERMINED_PER_REGION==0)
					{
      				s_skills = max(s_skills, s_skills+ (VINTAGES.array[i].productivity - s_skills)*SKILL_UPGRADE_PARAMETER);		}else
					{
						s_skills = max(s_skills, s_skills+ (VINTAGES.array[i].productivity - s_skills)*(SKILL_UPGRADE_PARAMETER_REGION_1+SKILL_UPGRADE_PARAMETER_REGION_2)/2.0);	

					}
				}
		
		
		
		sum+= pow(1/(1+DISCONT_RATE),j)*min(VINTAGES.array[i].productivity, s_skills );
		}
	

	VINTAGES.array[i].discounted_productivity = sum;

//printf("VINTAGES.array[i].discounted_productivity %f discounted_productivity_worst_vintage_last_month %f  price_worst_vintage_last_month %f\n", VINTAGES.array[i].discounted_productivity,discounted_productivity_worst_vintage_last_month, price_worst_vintage_last_month);
			
	//Compute new price: Price is a linear combination ofproductivity gains and costs



	
	//printf("UNIT_COSTS: %f	PRODUCTIVITY_PROGRESS: %f\n",UNIT_COSTS,PRODUCTIVITY_PROGRESS_IN_ECONOMY);


	if(DAY>1)
	VINTAGES.array[i].price= (1-LINEAR_COMBINATION_PRICING_IG_GOOD)*price_worst_vintage_last_month * VINTAGES.array[i].discounted_productivity  /discounted_productivity_worst_vintage_last_month 
+ LINEAR_COMBINATION_PRICING_IG_GOOD* UNIT_COSTS;

	//printf("VINTAGES.array[%d].price:	%f\n",i,VINTAGES.array[i].price);

		//Send the message:
		add_productivity_message(ID,VINTAGES.array[i].productivity,VINTAGES.array[i].price);
		
	}



	if((DAY%MONTH==DAY_OF_MONTH_TO_ACT) || (DAY%MONTH==(DAY_OF_MONTH_TO_ACT+1)))
	{
		if (IGFIRM_PRODUCER_DEBUG)
		{
			filename = malloc(40*sizeof(char));
			filename[0]=0;
			strcpy(filename, "its/IGFirm_producer.txt");  
			file1 = fopen(filename,"a");
			fprintf(file1,"IGFirm_send_quality_price_info()\n");
			fprintf(file1,"---------------------------------------------------------------------------------\n");
			fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
			fprintf(file1," PRODUCTIVITY = %f \n",PRODUCTIVITY);
			fprintf(file1," CAPITAL_GOOD_PRICE = %f \n",CAPITAL_GOOD_PRICE);
			fprintf(file1,"\n");
			fprintf(file1,"\n");
			fclose(file1);
			free(filename);
		}
	}
	return 0;
}




/** \fn IGFirm_calc_production_quantity()
 * \brief IGFirm calculate the intended production volume depending on the current stocks in the malls.
	- IGFirm sorts the last ten sales: lowest sales first.
	- IGFirm takes the x-th sales for the determination of the critical stock.
	- If the critical stock is higher than the capital good store it will produce otherwise not.
	*/
int IGFirm_calc_production_quantity()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif

	int i;
	int random_num;
	double sales[FIRM_PLANNING_HORIZON];
	double mean_of_last_sales=0.0;
	double mean_last_demand = 0.0;
	double temp_planned_production_quantity =0.0;
	double temp1;
	double temp2;


	/*Remove the oldest capital good sales and add the capital good salesof the last 	
	period.*/
	remove_double(&LAST_CAPITAL_GOOD_SALES,0);
	add_double(&LAST_CAPITAL_GOOD_SALES, SALES);

	/*Remove the oldest capital good demand and add the capital good demand of the last 	
	period.*/
	remove_double(&LAST_CAPITAL_GOOD_DEMAND,0);
	add_double(&LAST_CAPITAL_GOOD_DEMAND, CAPITAL_GOOD_DEMAND);
	
	/*Count the number of zero demands: faster adaption of the 
	production when there is no demand for capital goods*/
	if(CAPITAL_GOOD_DEMAND > 0)
	{
		NO_ZERO_DEMAND = 0;
	}
	else
	{
		NO_ZERO_DEMAND++;
	}

	
	/*Calculate the average of the last sales.*/
	for(i = 0; i < FIRM_PLANNING_HORIZON; i++)
	{
		sales[i] = LAST_CAPITAL_GOOD_SALES.array[i];
		mean_of_last_sales += LAST_CAPITAL_GOOD_SALES.array[i];
	}

	mean_of_last_sales = mean_of_last_sales/FIRM_PLANNING_HORIZON;	

	/*Sort the last sales: lowest sales first.*/
	for(i = 0; i < 10; i++)
	{
		int j;
		for(j = (i+1); j < 10;j++)
		{
			temp1 = sales[i];
			temp2 = sales[j];

			if(temp2 < temp1)
			{
				sales[i] = temp2;
				sales[j] = temp1;
			}
		}
	}

	/*Setting the critical stock.*/
	CRITICAL_STOCK = sales[8];
	
	/*If the critical stock is zero set the critical stock equal to the mean of the last sales with 
	a certain probability.*/						
	if(CRITICAL_STOCK == 0)
	{
		random_num = random_int(0,100);
		if(random_num < DELIVERY_PROB_IF_CRITICAL_STOCK_0)
		{
			CRITICAL_STOCK = mean_of_last_sales;		
		}

	}

	/*If capital good store is smaller than the critical stock.*/
	if(CAPITAL_GOOD_STORE <= CRITICAL_STOCK)
	{
		/*If capital goods are left produce the difference between the critical stock and the actual store.*/
		if(CAPITAL_GOOD_STORE > 0)
		{
			PLANNED_PRODUCTION_QUANTITY = CRITICAL_STOCK - CAPITAL_GOOD_STORE;
		}
		/*If no stocks are left produce the critical stock plus an additional 
		fraction because the IGFirm could have sold more goods in the last period.*/
		else
		{
			PLANNED_PRODUCTION_QUANTITY = CRITICAL_STOCK*
			(1 + ADDITIONAL_CAPITAL_GOOD_PRODUCTION);
		}


		/*Calculate the average of the last capital good demands.*/
		for(i = 0; i < LAST_CAPITAL_GOOD_DEMAND.size; i++)
		{
			mean_last_demand += LAST_CAPITAL_GOOD_DEMAND.array[i];	
		}

		mean_last_demand = mean_last_demand/(double)LAST_CAPITAL_GOOD_DEMAND.size;
		
		/*Smooth the production quantity by taking also the average of the last demands into account.*/
		temp_planned_production_quantity = PLANNED_PRODUCTION_QUANTITY;
		PLANNED_PRODUCTION_QUANTITY = IG_LAMBDA*PLANNED_PRODUCTION_QUANTITY +
		(1-IG_LAMBDA)*mean_last_demand;

		/*If there was no capital good demand in the last three periods than the IGFirm should not produce anymore.*/
		if(NO_ZERO_DEMAND > 10)
		{
			PLANNED_PRODUCTION_QUANTITY = 0.0;	
		}

	}
	/*If capital good store is greater than the critical stock the IGFirm will not produce.*/
	else
	{
		PLANNED_PRODUCTION_QUANTITY = 0.0;
	}


	

	
	/*1: complete functionality of the IGFirm  0: ISOLATED MODEL UNIBI MAY 09 */
	if(IGFIRM_SWITCH_ON == 0)
	{
		PLANNED_PRODUCTION_QUANTITY = 0.0;
	}
	
	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_calc_production_quantity()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," CAPITAL_GOOD_DEMAND = %f \n",CAPITAL_GOOD_DEMAND);
		fprintf(file1," SALES = %f  \n",SALES);
		fprintf(file1,"\n");
		fprintf(file1," CAPITAL_GOOD_STORE = %f \n",CAPITAL_GOOD_STORE);
		fprintf(file1," CRITICAL_STOCK = %f \n",CRITICAL_STOCK);
		fprintf(file1," temp_planned_production_quantity = %f \n",temp_planned_production_quantity);
		fprintf(file1," mean_last_demand = %f \n",mean_last_demand);
		fprintf(file1," IG_LAMBDA = %f \n",IG_LAMBDA);
		fprintf(file1," PLANNED_PRODUCTION_QUANTITY = %f  \n",PLANNED_PRODUCTION_QUANTITY);
		fprintf(file1,"\n");
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	} 

	return 0;
}





/* \fn IGFirm_calc_input_demands()
 * \brief IGFirms calculate the labor demand.
	- IGFirm computes the number of production employees and the corresponding production costs.*/
int IGFirm_calc_input_demands()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif

	/*Calculated the number of production employees*/
	EMPLOYEES_NEEDED = (int)(PLANNED_PRODUCTION_QUANTITY
	/PRODUCTION_PRODUCTIVITY);

	
	/*Planned production costs for the next period: for the calculation of
	PRODUCTION_LIQUIDITY_NEEDS in IGFirm_compute_total_liquidity_needs() (Fin-Man)*/
	PLANNED_PRODUCTION_COSTS = EMPLOYEES_NEEDED*MEAN_WAGE +
 	RESEARCH_EMPLOYEES_NEEDED*MEAN_RESEARCH_WAGE;

	
	/*1: complete functionality of the IGFirm  0: ISOLATED MODEL UNIBI MAY 09 */
	if(IGFIRM_SWITCH_ON == 0)
	{
		PLANNED_PRODUCTION_COSTS = 0;
		EMPLOYEES_NEEDED = 0;
	}

	
	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_calc_input_demands()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," PRODUCTION_PRODUCTIVITY = %f \n",PRODUCTION_PRODUCTIVITY);	
		fprintf(file1," PLANNED_PRODUCTION_QUANTITY = %f \n",PLANNED_PRODUCTION_QUANTITY);
		fprintf(file1," EMPLOYEES_NEEDED %d \n",EMPLOYEES_NEEDED);
		fprintf(file1,"\n");
		fprintf(file1," EMPLOYEES_NEEDED %d \n",EMPLOYEES_NEEDED);
		fprintf(file1," MEAN_WAGE = %f \n",MEAN_WAGE);
		fprintf(file1," RESEARCH_EMPLOYEES_NEEDED = %d \n",RESEARCH_EMPLOYEES_NEEDED);
		fprintf(file1," MEAN_RESEARCH_WAGE = %f \n",MEAN_RESEARCH_WAGE);
		fprintf(file1," PLANNED_PRODUCTION_COSTS = %f \n",PLANNED_PRODUCTION_COSTS);
		fprintf(file1,"\n");
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	} 
	

	return 0;	
}





/* \fn IGFirm_calc_input_demands2()
 * \brief IGFirms recalculate the labor demand if it did not receive enough external capital to 
	finance the planned production.
	- IGFirm computes the number of production and research employees which can be paid out of the available 
	financial resources.*/
int IGFirm_calc_production_quantity_2()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif

	double temp_planned_production_costs = 0.0;
	temp_planned_production_costs = PLANNED_PRODUCTION_COSTS;
	
	/*Calculate the available financial resources for the production.*/
	FINANCIAL_RESOURCES_FOR_PRODUCTION = PAYMENT_ACCOUNT - FINANCIAL_LIQUIDITY_NEEDS;
	
	/*If the available financial resources are not sufficient for the production....*/
	if(FINANCIAL_RESOURCES_FOR_PRODUCTION < PLANNED_PRODUCTION_COSTS)
	{
		/*...and there are at least some financial ressources the IGFirm decreases the number of number of needed
		 production and research employees until the available financial resources are sufficient to pay 
		 the recalculated number of workers.*/
		if( FINANCIAL_RESOURCES_FOR_PRODUCTION > 0.0)
		{
			/*As long as the available financial resources are not sufficient for the production 
			decrease the number of workers*/
			while (PLANNED_PRODUCTION_COSTS > FINANCIAL_RESOURCES_FOR_PRODUCTION)
			{
				if(EMPLOYEES_NEEDED >0)
				{
					EMPLOYEES_NEEDED -= 1;

					PLANNED_PRODUCTION_COSTS = EMPLOYEES_NEEDED*MEAN_WAGE +
 					RESEARCH_EMPLOYEES_NEEDED*MEAN_RESEARCH_WAGE;
				}

			
				if(PLANNED_PRODUCTION_COSTS > FINANCIAL_RESOURCES_FOR_PRODUCTION && 
				RESEARCH_EMPLOYEES_NEEDED > 0)
				{
					RESEARCH_EMPLOYEES_NEEDED -= 1;

					PLANNED_PRODUCTION_COSTS = EMPLOYEES_NEEDED*MEAN_WAGE +
 					RESEARCH_EMPLOYEES_NEEDED*MEAN_RESEARCH_WAGE;
				}
	
			}
		}
		/*If the IGFirm has no resources for production it will not produce and will not need any workers.*/
		else
		{	
			EMPLOYEES_NEEDED = 0;
			RESEARCH_EMPLOYEES_NEEDED = 0;
		}
	}


	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_calc_production_quantity_2()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," RESOURCES_FOR_PRODUCTION = %f \n",FINANCIAL_RESOURCES_FOR_PRODUCTION);	
		fprintf(file1," temp_planned_production_costs = %f\n",temp_planned_production_costs);
		fprintf(file1,"\n");
		fprintf(file1," EMPLOYEES_NEEDED %d \n",EMPLOYEES_NEEDED);
		fprintf(file1," MEAN_WAGE = %f \n",MEAN_WAGE);
		fprintf(file1," RESEARCH_EMPLOYEES_NEEDED = %d \n",RESEARCH_EMPLOYEES_NEEDED);
		fprintf(file1," MEAN_RESEARCH_WAGE = %f \n",MEAN_RESEARCH_WAGE);
		fprintf(file1," PLANNED_PRODUCTION_COSTS = %f \n",PLANNED_PRODUCTION_COSTS);
		fprintf(file1,"\n");
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	} 

	return 0;
}





/* \fn IGFirm_produce_capital_good()
 * \brief IGFirms produce the capital good*/
int IGFirm_produce_capital_good()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif

	/*1: complete functionality of the IGFirm  0: ISOLATED MODEL UNIBI MAY 09 */
	if(IGFIRM_SWITCH_ON == 1)
	{
		/*Variables for getdata*/
		OUTPUT = 0;
		PLANNED_OUTPUT = 0;
	
		PLANNED_OUTPUT = PLANNED_PRODUCTION_QUANTITY;
	
		/*Determine the production quantity based on the number of production workers.*/
		PRODUCTION_QUANTITY = NO_EMPLOYEES*PRODUCTION_PRODUCTIVITY;
		OUTPUT = PRODUCTION_QUANTITY;
		
		/*Note: The production quantity is added to the capital store in IGFirm_send_capital_good(). 
		The consumption good producers which buy the capital goods on the day_of_month_to_act of 
		the IGFirm will receive "old" capital good with the productivity and the price which 
		were announced earlier in this period.*/
	
		remove_double(&LAST_PRODUCTION_QUANTITIES,0);
		add_double(&LAST_PRODUCTION_QUANTITIES, PRODUCTION_QUANTITY);
	}

	
	
	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_produce_capital_good()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," CAP_STORE_BEFORE_PRODUCTION = %f \n",CAPITAL_GOOD_STORE_BEFORE_PRODUCTION);
		fprintf(file1,"\n");
		fprintf(file1," PLANNED_PRODUCTION_QUANTITY = %f\n",PLANNED_PRODUCTION_QUANTITY);
		fprintf(file1," NO_EMPLOYEES = %d \n",NO_EMPLOYEES);
		fprintf(file1," PRODUCTION_PRODUCTIVITY  = %f \n",PRODUCTION_PRODUCTIVITY);	
		fprintf(file1," PRODUCTION_QUANTITY = %f\n",PRODUCTION_QUANTITY);
		fprintf(file1,"\n");
		fprintf(file1," CAP_STORE_AFTER_PRODUCTION = %f \n",CAPITAL_GOOD_STORE_AFTER_PRODUCTION);
		fprintf(file1,"\n");
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	} 

	return 0;
}





/* \fn IGFirm_calc_pay_costs()
 * \brief IGFirm calculates the labour/production costs and determines the capital good price based 
	on a mark_up on the unit costs.*/
int IGFirm_calc_pay_costs()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif

	int i,m;
	double average_production_quantity = 0.0;
	double temp_payment_account= 0.0;
	
	/*Labour costs are the sum of all wages.*/
	LABOUR_COSTS = 0.0;
	CALC_PRODUCTION_COSTS=0.0;

	/*Sum up the wages for production workers and send the wage payment message to employees.*/
	for(i=0; i<EMPLOYEES.size;i++)
	{
		LABOUR_COSTS += EMPLOYEES.array[i].wage;

		add_wage_payment_message(ID,
		EMPLOYEES.array[i].id,
		EMPLOYEES.array[i].wage,
		TECHNOLOGY,
		MEAN_SPECIFIC_SKILLS,1);	//1: Indicates that the Firm is an IGFirm.
	}
	
	/*Sum up the wages for researchers and send the wage payment message to employees.*/
	for(i=0; i<RESEARCH_EMPLOYEES.size;i++)
	{
		LABOUR_COSTS += RESEARCH_EMPLOYEES.array[i].wage;

		add_wage_payment_message(ID,
		RESEARCH_EMPLOYEES.array[i].id,
		RESEARCH_EMPLOYEES.array[i].wage,
		TECHNOLOGY,
		MEAN_SPECIFIC_SKILLS,1);	//1: Indicates that the Firm is an IGFirm.
	}
	
	IGFIRM_OUTFLOWS_CALENDAR.labour_costs = LABOUR_COSTS;

	temp_payment_account =PAYMENT_ACCOUNT;
	/*Decrease the payment account by the sum of wages.*/
	PAYMENT_ACCOUNT -= LABOUR_COSTS;

	/*Store the production costs for getdata.*/
	PRODUCTION_COSTS_LAST_MONTH = PRODUCTION_COSTS;

	/*Production costs are only labor costs.*/
	PRODUCTION_COSTS = LABOUR_COSTS;
	CALC_PRODUCTION_COSTS= LABOUR_COSTS;

	
	/*Calculate the average of the last production quantities*/
	for(m = 0; m < LAST_PRODUCTION_QUANTITIES.size; m++)
	{
		average_production_quantity += LAST_PRODUCTION_QUANTITIES.array[m];
	}

	average_production_quantity = 
	average_production_quantity/(double)LAST_PRODUCTION_QUANTITIES.size;

	
	/*1: complete functionality of the IGFirm  0: ISOLATED MODEL UNIBI MAY 09 */
	if(IGFIRM_SWITCH_ON == 1)
	{
		/*If the IGFirm has produced capital goods.*/	
		if(PRODUCTION_QUANTITY > 0)
		{
			/*The average of the last production quantities is used to smooth the capital good price.*/
			UNIT_COSTS = (LABOUR_COSTS+TOTAL_INTEREST_PAYMENT)/average_production_quantity;
			NEW_CAPITAL_GOOD_PRICE = UNIT_COSTS*(1+IG_MARK_UP);
			
			if(NEW_CAPITAL_GOOD_PRICE > CAPITAL_GOOD_PRICE*1.5)
			{
				NEW_CAPITAL_GOOD_PRICE = CAPITAL_GOOD_PRICE*1.5;
			}
		}
		/*If there was no production.*/
		else
		{	/*Take the unit costs of the last period and also the price*/
			UNIT_COSTS = UNIT_COSTS;
			NEW_CAPITAL_GOOD_PRICE = CAPITAL_GOOD_PRICE;
		}
	}
	
	
	
	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_calc_pay_costs()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," LABOUR_COSTS = %f  \n",LABOUR_COSTS);
		fprintf(file1," TOTAL_INTEREST_PAYMENT = %f  \n",TOTAL_INTEREST_PAYMENT);
		fprintf(file1," AVERAGE PRODUCTION QUANTITY = %f  \n",average_production_quantity);
		fprintf(file1," UNIT_COSTS = %f \n",UNIT_COSTS);
		fprintf(file1," NEW_CAPITAL_GOOD_PRICE = %f \n",NEW_CAPITAL_GOOD_PRICE);
		fprintf(file1," CAPITAL_GOOD_PRICE = %f \n",CAPITAL_GOOD_PRICE);
		fprintf(file1,"\n");
		fprintf(file1," temp_payment_account = %f \n",temp_payment_account);
		fprintf(file1," PAYMENT_ACCOUNT = %f \n",PAYMENT_ACCOUNT);
		fprintf(file1,"\n");
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	} 

	return 0;
}





/** \fn IGFirm_send_capital_good()
 * \brief IGFirm sends capital goods.
	- IGFirm collects daily capital good demand. Depended on the level of capital good store the demand of 
	the consumption good producers can be satisfied completely or only by a certain fraction. 
 */
int IGFirm_send_capital_good()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif


	int v,i;
	double fraction_order;
	double daily_capital_good_demand = 0.0;
	double daily_sales = 0.0;	
	double temp_capital_good_store = CAPITAL_GOOD_STORE;
	double selling_capital_good_price = CAPITAL_GOOD_PRICE;

	/*Initialize a temporary capital_good_request array in order to store the incoming request messages.*/	
	capital_good_request_array capital_good_request_list;
	init_capital_good_request_array(&capital_good_request_list); 

	if(DAY%MONTH==DAY_OF_MONTH_TO_ACT)
	{	
		/*Store the demand for and sales of the capital good of the last twenty days in order to have the monthly
	 	demand and monthly sales for getdata_region*/
		CAPITAL_GOOD_DEMAND_LAST_MONTH = CAPITAL_GOOD_DEMAND;
		CAPITAL_GOOD_DEMAND = 0.0;
		SALES_LAST_MONTH = SALES;
		SALES = 0.0;
	}

	/*Clean the vintage sales array on first day of month*/
	if(DAY%MONTH==1)
	{
	for(i=0;i<SALES_PER_VINTAGE.size;i++)
		{
			SALES_PER_VINTAGE.array[i].sales=0.0;
			SALES_PER_VINTAGE.array[i].revenue=0.0;
		}

	for(i=0;i<VINTAGES.size;i++)
		{
		VINTAGES.array[i].sales=0;
		}	

	}

	
	START_CAPITAL_GOOD_REQUEST_MESSAGE_LOOP

		/*Store the IDs and quanities*/
		add_capital_good_request(&capital_good_request_list,
		capital_good_request_message->firm_id,
		capital_good_request_message->capital_good_demand,capital_good_request_message->vintage );

		daily_capital_good_demand += capital_good_request_message->capital_good_demand;

	FINISH_CAPITAL_GOOD_REQUEST_MESSAGE_LOOP

	/*Sum up the daily demand in order to get the mothly demand.*/
	CAPITAL_GOOD_DEMAND += daily_capital_good_demand;

	CAPITAL_GOOD_DEMAND_AFTER_LAST_INNOVATION += daily_capital_good_demand;


	/*1: complete functionality of the IGFirm  0: ISOLATED MODEL UNIBI MAY 09 */
	if(IGFIRM_SWITCH_ON == 1)
	{
	
		/*Capital good store is bigger than capital good demand: daily demand can be satisfied.*/
		if(daily_capital_good_demand <= CAPITAL_GOOD_STORE)
		{
			for(v = 0; v < capital_good_request_list.size; v++)
			{
				/*Send the capital goods to the consumption good producers.*/
				add_capital_good_delivery_message(
				capital_good_request_list.array[v].firm_id,
				capital_good_request_list.array[v].capital_good_order, 	
				PRODUCTIVITY, 
				CAPITAL_GOOD_PRICE);
	
				/*Decrease the capital good store by the sold quantity.*/
				CAPITAL_GOOD_STORE -= capital_good_request_list.
				array[v].capital_good_order;
				temp_capital_good_store = CAPITAL_GOOD_STORE;
	
				/*Increase the sales by the sold quantity.*/
				SALES += capital_good_request_list.
				array[v].capital_good_order;
	
				daily_sales += capital_good_request_list.
				array[v].capital_good_order;
			}
		}
		else
		{	/*Capital good demand is higher than capital good store and 
			the store is positive: every consumption good producer gets a fraction of their order*/
			if(CAPITAL_GOOD_STORE > 0)
			{
				fraction_order = CAPITAL_GOOD_STORE/daily_capital_good_demand;

				for(v = 0; v < capital_good_request_list.size; v++)
				{
					/*Send the capital goods to the consumption good producers. Every consumption goods 
					producer receives a fration of its demand.*/
					add_capital_good_delivery_message(
					capital_good_request_list.array[v].firm_id,
					capital_good_request_list.array[v].capital_good_order*fraction_order, 
					PRODUCTIVITY, 	
					CAPITAL_GOOD_PRICE);
	
					/*Decrease the capital good store by the sold quantity.*/
					CAPITAL_GOOD_STORE -= capital_good_request_list.
					array[v].capital_good_order *fraction_order;
					temp_capital_good_store = CAPITAL_GOOD_STORE;
	
					/*Increase the sales by the sold quantity.*/
					SALES += capital_good_request_list.
					array[v].capital_good_order*fraction_order;
				
					daily_sales += capital_good_request_list.
					array[v].capital_good_order*fraction_order;
				}	
			}
			/*Capital goods store is empty: no delivery*/
			else
			{
				for(v = 0; v < capital_good_request_list.size; v++)
				{
					add_capital_good_delivery_message(
					capital_good_request_list.array[v].firm_id,
					0, 
					PRODUCTIVITY, 	
					CAPITAL_GOOD_PRICE);
	
					SALES += 0.0;
				}
			}
		}
	}
	/*If IGFIRM_SWITCH_ON is zero: demand of the firms is satisfied*/
	else
	{
		for(v = 0; v < capital_good_request_list.size; v++)
		{
			/*Send the capital goods to the consumption good producers.*/
			add_capital_good_delivery_message(
			capital_good_request_list.array[v].firm_id,
			capital_good_request_list.array[v].capital_good_order, 	
			VINTAGES.array[capital_good_request_list.array[v].vintage].productivity, 
			VINTAGES.array[capital_good_request_list.array[v].vintage].price);
		
			/*Increase the sales by the sold quantity.*/
			SALES += capital_good_request_list.
			array[v].capital_good_order;
			VINTAGES.array[capital_good_request_list.array[v].vintage].sales+=capital_good_request_list.array[v].capital_good_order;
	
			daily_sales += capital_good_request_list.
			array[v].capital_good_order;
			/*Compute sales and revenues for all vintages*/
			for(i=0;i<SALES_PER_VINTAGE.size;i++)
				{
				if(SALES_PER_VINTAGE.array[i].productivity_of_vintage==VINTAGES.array[capital_good_request_list.array[v].vintage].productivity)
					{
					SALES_PER_VINTAGE.array[i].sales +=capital_good_request_list.array[v].capital_good_order;
					SALES_PER_VINTAGE.array[i].revenue+=capital_good_request_list.array[v].capital_good_order*VINTAGES.array[capital_good_request_list.array[v].vintage].price;	
					break;
					}
	
				}		


		}
	}

	free_capital_good_request_array(&capital_good_request_list);

	
	
	if(IGFIRM_SWITCH_ON == 1)
	{	
		if((DAY%240 == DAY_OF_MONTH_TO_ACT) && (NEW_PRODUCTIVITY > PRODUCTIVITY))
		{
			/*The new productivity is set here to make sure that the new productivity together with the new price is
			sent on the first day after the production. Hence it is avoided that the IGFIRM sent the new productivity 
			with the old price. */
			PRODUCTIVITY = NEW_PRODUCTIVITY;
		}

		if(DAY%MONTH==DAY_OF_MONTH_TO_ACT)
		{
			/*Firms which buy goods on the day_of_month_to_act of the IGFIRM should pay the price which 
			was announced in IGFirm_send_quality_price_info_message. Hence the new price after the 
			last production is set here for the next 20 days.*/
			CAPITAL_GOOD_PRICE = NEW_CAPITAL_GOOD_PRICE;
			
			CAPITAL_GOOD_STORE_BEFORE_PRODUCTION = CAPITAL_GOOD_STORE;
		
			/*Add the production quantity to the capital good store.*/
			CAPITAL_GOOD_STORE += PRODUCTION_QUANTITY;
	
			/*Maximum of the capital good store: directly after production.*/
			CAPITAL_GOOD_STORE_AFTER_PRODUCTION = CAPITAL_GOOD_STORE;
		}
	}
	
	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_send_capital_good()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," CAPITAL_GOOD_DEMAND = %f\n",CAPITAL_GOOD_DEMAND);
		fprintf(file1," daily_capital_good_demand = %f\n",daily_capital_good_demand);
		fprintf(file1," daily_sales = %f\n",daily_sales);
		fprintf(file1," SALES = %f\n",SALES);
		fprintf(file1," selling_capital_good_price = %f \n",selling_capital_good_price);
		fprintf(file1," CAPITAL_GOOD_STORE = %f \n",temp_capital_good_store);
		fprintf(file1,"\n");
		if(DAY%MONTH == DAY_OF_MONTH_TO_ACT)
		{
			fprintf(file1," CAP_STORE_BEFORE_PRODUCTION = %f \n",CAPITAL_GOOD_STORE_BEFORE_PRODUCTION);
			fprintf(file1," CAP_STORE_AFTR_PRODUCTION = %f \n",CAPITAL_GOOD_STORE_AFTER_PRODUCTION);
		}
		fprintf(file1," CAPITAL_GOOD_PRICE = %f \n",CAPITAL_GOOD_PRICE);
		fprintf(file1," PRODUCTIVITY = %f \n",PRODUCTIVITY);
		fprintf(file1,"\n");
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	} 

	return 0;
}





/** \fn IGFirm_calc_revenue()
 * \brief IGFirm calculates revenues.
 */
int IGFirm_calc_revenue()
{
	//  #ifdef _DEBUG_MODE
	FILE *file1;
	char *filename;
	// #endif

	/*Reset CUM_REVENUE_LAST_MONTH on the first day of every month for getdata and validation check.*/
	if(DAY%MONTH == 1)
	{
		CUM_REVENUE_LAST_MONTH = 0.0;
	}

	/*Reset CUM_REVENUE on the day_of_month_to_act. This variable sums up the revenues during 
	on production cycle.*/
	if(DAY%MONTH==DAY_OF_MONTH_TO_ACT)
	{
		CUM_REVENUE = 0.0;
	}

	REVENUE_PER_DAY = 0;
	

	START_PAY_CAPITAL_GOODS_MESSAGE_LOOP

		REVENUE_PER_DAY += pay_capital_goods_message->capital_bill;

	FINISH_PAY_CAPITAL_GOODS_MESSAGE_LOOP  
	
	
	CUM_REVENUE += REVENUE_PER_DAY; 
	PAYMENT_ACCOUNT += REVENUE_PER_DAY;
	CUM_REVENUE_LAST_MONTH +=REVENUE_PER_DAY;
	IGFIRM_INFLOWS_CALENDAR.cum_revenue += REVENUE_PER_DAY;
	/*Sum up revenues for the R&D budget: not necessary if research employees are 
	calculated every year -> then: CUM_REVENUES = REVENUE FOR INNOVATION*/
	REVENUE_FOR_INNOVATION += REVENUE_PER_DAY;

	
	if (IGFIRM_PRODUCER_DEBUG)
	{
		filename = malloc(40*sizeof(char));
		filename[0]=0;
		strcpy(filename, "its/IGFirm_producer.txt");  
		file1 = fopen(filename,"a");
		fprintf(file1,"IGFirm_calc_revenue()\n");
		fprintf(file1,"---------------------------------------------------------------------------------\n");
		fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
		fprintf(file1," CUM_REVENUE = %f\n",CUM_REVENUE);
		fprintf(file1," PAYMENT_ACCOUNT = %f\n",PAYMENT_ACCOUNT);
		fprintf(file1,"\n");
		fprintf(file1," CUM_REVENUE_LAST_MONTH = %f\n",CUM_REVENUE_LAST_MONTH);
		fprintf(file1,"\n");
		fclose(file1);
		free(filename);
	} 
	
	return 0;
}




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
int day_of_month_to_act()
{
	if(DAY%MONTH == DAY_OF_MONTH_TO_ACT) return 1;
	else return 0;
}

int not_day_of_month_to_act()
{
	if(DAY%MONTH == DAY_OF_MONTH_TO_ACT) return 0;
	else return 1;
}


int IGFirm_idle()
{
	return 0;
}








