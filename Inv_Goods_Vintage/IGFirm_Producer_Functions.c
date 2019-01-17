//For testing GSL:
#include <gsl/gsl_rng.h>

#include "../header.h"
#include "../IGFirm_agent_header.h"
#include "../my_library_header.h"

/* External defined GSL random generator: see main.c */
extern gsl_rng * FLAME_GSL_RNG;  

extern int FLAME_GSL_SEED;  
extern int FLAME_GSL_GEN_NO;

/***************************** Investment Goods producer function********************************/


int IGFirm_initialize_variables()
{
	int i;
		
		if(LAST_SALES.size== 6)
		{
			remove_double(&LAST_SALES,0);
			
		}
		add_double(&LAST_SALES,SALES);

		MEAN_SALES_LAST_MONTHS=0.0;
		for(i=0; i< LAST_SALES.size;i++)
		{
			MEAN_SALES_LAST_MONTHS+= LAST_SALES.array[i];
		}

		if(LAST_SALES.size>0)
		{
			MEAN_SALES_LAST_MONTHS = MEAN_SALES_LAST_MONTHS/(1.0*LAST_SALES.size);
		}



		CAPITAL_GOOD_DEMAND_LAST_MONTH = CAPITAL_GOOD_DEMAND;
		CAPITAL_GOOD_DEMAND = 0.0;
		SALES_LAST_MONTH = SALES;
		SALES = 0.0;
#


		MEAN_PRODUCTIVITY_OF_SALES = 0.0;

		double sum_sales = 0.0;
		for(i=0;i<VINTAGES.size;i++)
		{
			sum_sales += VINTAGES.array[i].sales;
			MEAN_PRODUCTIVITY_OF_SALES +=  VINTAGES.array[i].productivity*VINTAGES.array[i].sales;
		}	
		if(sum_sales > 0)
		{
			MEAN_PRODUCTIVITY_OF_SALES = MEAN_PRODUCTIVITY_OF_SALES/ sum_sales;
		}else
		{
			MEAN_PRODUCTIVITY_OF_SALES =0.0;
		}
		RATIO_SOLD_PRODUCTIVITY_BEST_PRACTICE = MEAN_PRODUCTIVITY_OF_SALES/PRODUCTIVITY ;
	
		CUM_REVENUE = 0.0;


return 0;

}





/** \fn IGFirm_update_productivity_price()
 * \brief IGFirm send quality and price information.
	- If the functionality of the IGFirm is switched off it updates the productivity and the price. */
int IGFirm_innovation_process()
{
	int i;

	double prod_progress ;
	/*1: complete functionality of the IGFirm -- 0: Exogenous stochastic innovation process  */
	
		
	/*Reinitialize some variables for a correct balance sheet if the functionality of the IGFirm is switched off.*/
	if(DAY == 1)
	{
		//CAPITAL_GOOD_PRICE = PRODUCTIVITY;
		PAYMENT_ACCOUNT = 0.0;
		EQUITY = 0.0;
		TOTAL_ASSETS = 0.0;

	}

	/*If the innovation progress is random and has not a predetermined shape*/
	if(INNOVATION_BY_RANDOM==1)
	{
		/*If transition phase is over. During the transition phase there is no productivity progress.*/
		if(DAY >= TRANSITION_PHASE)
 		{
			if(DAY%MONTH == DAY_OF_MONTH_TO_ACT)
			{	

				if(SWITCH_IGFIRM_ENDOGENOUS_INNOVATION_PROBABILITY==1)
				{
					/* Assumption: The probability is a linear function. If the mean sales is 0, then the probability is 0 as well. If the mean sales correspond to the depreciation of the economy wide dcapital stock, then the probability is
			 		has the same value as the exogeneous innovation probability*/
			
					IGFIRM_ENDOGENOUS_INNOVATION_PROBABILITY = IGFIRM_EXOGENOUS_INNOVATION_PROBABILITY* pow(MEAN_SALES_LAST_MONTHS /(1.0* DEPRECIATION_RATE*ECONOMY_WIDE_CAPITAL_STOCK),POWER_OF_END_PROBABILITY_FUNCTION);

					i = random_int( 0 ,100);
					//int min=0;
					//int max=100;
					//i = (int)(gsl_rng_uniform(FLAME_GSL_RNG)*(max - min + 1) + min);

					if(i < IGFIRM_ENDOGENOUS_INNOVATION_PROBABILITY)
					{
						PRODUCTIVITY = PRODUCTIVITY*(1 + IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);
						CAPITAL_GOOD_PRICE = 
						CAPITAL_GOOD_PRICE*(1 +IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);	

						//add new one:
						add_vintage(&VINTAGES,PRODUCTIVITY, CAPITAL_GOOD_PRICE,0,0);	

						add_adt_sales_per_vintage(&SALES_PER_VINTAGE,PRODUCTIVITY, 0.0,0.0 );

						if(IG_GOOD_LIMITED_OFFER == 1 && VINTAGES.size >= MAX_OFFER_IG_GOOD)
						{
							//remove last entry (oldest vintage)				
							remove_vintage(&VINTAGES,0);
						}		



					}
			

				}else
				{
					i = random_int( 0 ,100);
					//int min=0;
					//int max=100;
					//i = (int)(gsl_rng_uniform(FLAME_GSL_RNG)*(max - min + 1) + min);

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
	}
	else//Innovation progress has a predetermined shape: 3 cases, with low, medium and high tech progress
	{
		if(STRENGHT_OF_TECH_PROGRESS ==2)
		{

			printf("DAY %d    TRANSITION_PHASE+INNOVATION_SHEME_MEDIUM_PROGRESS.array[0] %d\n",DAY, TRANSITION_PHASE+INNOVATION_SHEME_MEDIUM_PROGRESS.array[0]);
			if(DAY==TRANSITION_PHASE+INNOVATION_SHEME_MEDIUM_PROGRESS.array[0])
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
			if(DAY==TRANSITION_PHASE+INNOVATION_SHEME_HIGH_PROGRESS.array[0])
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

			if(DAY==TRANSITION_PHASE+INNOVATION_SHEME_LOW_PROGRESS.array[0])
			{
				prod_progress =PRODUCTIVITY*IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS;

				PRODUCTIVITY =PRODUCTIVITY*(1+IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);

				CAPITAL_GOOD_PRICE = CAPITAL_GOOD_PRICE*(1
				+IGFIRM_EXOGENOUS_PRODUCTIVITY_PROGRESS);
				
				remove_int(&INNOVATION_SHEME_LOW_PROGRESS,0);


				if(IG_GOOD_LIMITED_OFFER == 1 && VINTAGES.size >= MAX_OFFER_IG_GOOD)
				{
					//remove last entry (oldest vintage)				
					remove_vintage(&VINTAGES,0);
				}				

				//add new one:
				add_vintage(&VINTAGES,PRODUCTIVITY, CAPITAL_GOOD_PRICE,0,0);

				add_adt_sales_per_vintage(&SALES_PER_VINTAGE,PRODUCTIVITY, 0.0,0.0 );
			}
		}
	}

return 0;
}	


/** \fn IGFirm_update_productivity_price()
 * \brief IGFirm sets the prices of the vintages and sends quality and price information to the consumption goods producer.
	*/
int IGFirm_set_price_send_info()
{

	int i,j;
	double  price_worst_vintage_last_month, discounted_productivity_worst_vintage_last_month, sum, s_skills;

	price_worst_vintage_last_month= VINTAGES.array[0].price;
    discounted_productivity_worst_vintage_last_month = VINTAGES.array[0].discounted_productivity;

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
			if(SKILL_UPDATE_ACC_TO_FORMULA==1)
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
					
									
					double x1 = (ECONOMY_WIDE_GENERAL_SKILLS_IN_FIRMS - LIST_ADAPTATION_SPEED.array[0].general_skill_level)
						/( 1.0*LIST_ADAPTATION_SPEED.array[LIST_ADAPTATION_SPEED.size-1].general_skill_level- 1.0*LIST_ADAPTATION_SPEED.array[0].general_skill_level);
	
					MEAN_ADAPTATION_SPEED =LIST_ADAPTATION_SPEED.array[0].adaptation_speed + x1*
						(LIST_ADAPTATION_SPEED.array[LIST_ADAPTATION_SPEED.size-1].adaptation_speed - LIST_ADAPTATION_SPEED.array[0].adaptation_speed);		


				
      				s_skills = max(s_skills, s_skills+ (VINTAGES.array[i].productivity - s_skills)*MEAN_ADAPTATION_SPEED);		
					
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

	// Store the price and productivity outside the array for plotting  
	PRODUCTIVITY = VINTAGES.array[VINTAGES.size-1].productivity;
	CAPITAL_GOOD_PRICE = VINTAGES.array[VINTAGES.size-1].price;



	if((DAY%MONTH==DAY_OF_MONTH_TO_ACT) || (DAY%MONTH==(DAY_OF_MONTH_TO_ACT+1)))
	{
		if (IGFIRM_PRODUCER_DEBUG)
		{
		
			printf("IGFirm_send_quality_price_info()\n");
			printf("---------------------------------------------------------------------------------\n");
			printf(" DAY %d \t ID %d \n",DAY,ID);
			printf(" PRODUCTIVITY = %f \n",PRODUCTIVITY);
			printf(" CAPITAL_GOOD_PRICE = %f \n",CAPITAL_GOOD_PRICE);
			printf("\n");
			printf("\n");
			
		}
	}
	return 0;
}







/** \fn IGFirm_send_capital_good()
 * \brief IGFirm sends capital goods.
	- IGFirm collects daily capital good demand. There is an infinite supply of the good such that the consumtion goods producer are never rationed.
 */
int IGFirm_receive_order_delivers_capital_goods()
{

	int v,i;
	double daily_capital_good_demand = 0.0;
	double daily_sales = 0.0;	


	/*Initialize a temporary capital_good_request array in order to store the incoming request messages.*/	
	capital_good_request_array capital_good_request_list;
	init_capital_good_request_array(&capital_good_request_list); 

	

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
	

	free_capital_good_request_array(&capital_good_request_list);


	return 0;
}





/** \fn IGFirm_calc_revenue()
 * \brief IGFirm calculates revenues.
 */
int IGFirm_calc_revenue()
{
	int i;

	/*Reset CUM_REVENUE_LAST_MONTH on the first day of every month for getdata and validation check.*/
	if(DAY%MONTH == 1)
	{
	
			

		CUM_REVENUE_LAST_MONTH = 0.0;
	}

	REVENUE_PER_DAY = 0;
	

	START_PAY_CAPITAL_GOODS_MESSAGE_LOOP

		REVENUE_PER_DAY += pay_capital_goods_message->capital_bill;

	FINISH_PAY_CAPITAL_GOODS_MESSAGE_LOOP  
	
	
	CUM_REVENUE += REVENUE_PER_DAY; 
	PAYMENT_ACCOUNT += REVENUE_PER_DAY;
	CUM_REVENUE_LAST_MONTH +=REVENUE_PER_DAY;
	IGFIRM_INFLOWS_CALENDAR.cum_revenue += REVENUE_PER_DAY;
	
	
	return 0;
}




/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


int IGFirm_idle()
{
	return 0;
}








