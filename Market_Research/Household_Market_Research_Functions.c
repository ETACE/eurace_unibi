#include "../header.h"
#include "../Household_agent_header.h"
#include "../my_library_header.h"
#include <gsl/gsl_rng.h>
#include <time.h>


/** \fn Household_decide_to_attend_interview
 */
int Household_decide_to_attend_interview()
{
	INTERVIEWER_ID = 0;
	//WILLINGNESS_TO_ATTEND = 0;
	
	WILLINGNESS_TO_ATTEND = 1;


	//Intermediate solution: 

	//double random_nummer;
	
	//random_nummer = random_int(0,100);
	
	
	
	//RANDOM_NO_TEST = random_nummer;
	
	//random_nummer  = random_nummer/100.0;
	// If random_nummer < attending propability then the household would attend an interview
	//if(random_nummer < QUESTIONNAIRE_ATTENDING_PROPABILITY)
	//{
	//	WILLINGNESS_TO_ATTEND = 1;
		
	//}
	
	return 0;
}


/** \fn Household_respond
 */
int Household_respond()
{

	int_array id_list;
	init_int_array(&id_list);

	START_INTERVIEW_REQUEST_MESSAGE_LOOP
	
	//INTERVIEWER_ID = interview_request_message->firm_id;
	
	add_int(&id_list,interview_request_message->firm_id);

	//WILLINGNESS_TO_ATTEND = 0;
	
	FINISH_INTERVIEW_REQUEST_MESSAGE_LOOP
	//Respond if attend

	INTERVIEWER_ID = id_list.array[random_int(0,id_list.size)];

	add_interview_positive_response_message(ID, REGION_ID, INTERVIEWER_ID);

	free_int_array(&id_list);
	
	return 0;
}



int Household_respond_questionnaire()
{
	
	int i;
	
	double price, quality;
	double random_number, logit, logit_denominator,logit_sum;
	

	int price_done;

	price_done=0;
	
	START_QUESTIONNAIRE_PRICING_MESSAGE_LOOP

	
	double_array price_list;
	init_double_array(&price_list);

	logit_sum=0;

	if(price_done==0)
	{
		for(i=0;i<questionnaire_pricing_message->times_increment;i++)
		{
		
			price = questionnaire_pricing_message->start_price + i *questionnaire_pricing_message->increment; 
			add_double(&price_list, price);
			price_done=1;
		}
	}
	
	quality = questionnaire_pricing_message->quality; 

	for(i=0;i<CURRENT_PRICE_QUALITY_LIST.size;i++)
	{			
		if(CURRENT_PRICE_QUALITY_LIST.array[i].id!=INTERVIEWER_ID)
		{
			logit_sum += exp(GAMMA_CONST*(GAMMA_QUALITY*log(CURRENT_PRICE_QUALITY_LIST.array[i].quality)-log(CURRENT_PRICE_QUALITY_LIST.array[i].price)));

		}
	}

	logit = 0;

	for(i=0; i< price_list.size; i++)
	{				
		logit_denominator=exp(GAMMA_CONST*(GAMMA_QUALITY*log(quality) -log(price_list.array[i]))) + logit_sum;
	 
		logit= exp(GAMMA_CONST*(GAMMA_QUALITY*log(quality) -log(price_list.array[i])))/ logit_denominator;
	 		
		//random process for purchasing decision:

	 	random_number = random_unif();

		if(random_number< logit)
		{
			QUESTIONNAIRE[i]=1;
			
	 	}else
		{
			QUESTIONNAIRE[i]=0;
		}
	}	


	//Send filled out questionnaire to firm	
	add_filled_out_questionnaire_pricing_message( INTERVIEWER_ID,REGION_ID, QUESTIONNAIRE);	


	free_double_array(&price_list);
					
	FINISH_QUESTIONNAIRE_PRICING_MESSAGE_LOOP


	int year_under_consideration;
	double quality_growth_rate, price_growth_rate;



	START_QUESTIONNAIRE_INNOVATION_MESSAGE_LOOP



	double_array price_list;
	init_double_array(&price_list);

	logit_sum=0;

	for(i=0;i<questionnaire_innovation_message->times_increment;i++)
	{
		
		price = questionnaire_innovation_message->start_price + i *questionnaire_innovation_message->increment; 
		add_double(&price_list, price);
		price_done=1;
	}

	
	quality = questionnaire_innovation_message->quality; 
	
	year_under_consideration=questionnaire_innovation_message->year_under_consideration;
	quality_growth_rate=questionnaire_innovation_message->growth_quality_index;
	price_growth_rate=questionnaire_innovation_message->growth_price_index;





	for(i=0;i<CURRENT_PRICE_QUALITY_LIST.size;i++)
	{			
		if(CURRENT_PRICE_QUALITY_LIST.array[i].id!=INTERVIEWER_ID)
		{
			logit_sum += exp(GAMMA_CONST*(GAMMA_QUALITY*log(CURRENT_PRICE_QUALITY_LIST.array[i].quality*pow(1+quality_growth_rate,year_under_consideration))
				-log(CURRENT_PRICE_QUALITY_LIST.array[i].price*pow(1+price_growth_rate,year_under_consideration))));
		}
	}

	logit = 0;

	for(i=0; i< price_list.size; i++)
	{				
		logit_denominator=exp(GAMMA_CONST*(GAMMA_QUALITY*log(quality) -log(price_list.array[i]))) + logit_sum;
	 
		logit= exp(GAMMA_CONST*(GAMMA_QUALITY*log(quality) -log(price_list.array[i])))/ logit_denominator;

		
	 		
		//random process for purchasing decision:

	 	random_number = random_unif();

		

		if(random_number< logit)
		{
			QUESTIONNAIRE[i]=1;
			
	 	}else
		{
			QUESTIONNAIRE[i]=0;
		}

	

	}	

	add_filled_out_questionnaire_product_innovation_message( INTERVIEWER_ID,REGION_ID,quality, QUESTIONNAIRE, year_under_consideration );


	free_double_array(&price_list);
					
	FINISH_QUESTIONNAIRE_INNOVATION_MESSAGE_LOOP


	
	return 0;
}
