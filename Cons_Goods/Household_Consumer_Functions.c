#include "../header.h"
#include "../Household_agent_header.h"
#include "../my_library_header.h"


/********************************* Household agent functions *************************************/



/**********************************Household Role: Consumption Goods Market*********************/


/*\fn Household_determine_consumption_budget()
 * brief: If a household is unemployed then it receives an unemployment benefit payment
 * 
 */
int Household_determine_consumption_budget()
{
    double asset_wealth;
        
    /*Determining the consumption budget of the month*/
            //Previous rule based Deaton rule: uses PAYMENT_ACCOUNT
            /*if(PAYMENT_ACCOUNT > (INITIAL_CONSUMPTION_PROPENSITY*MEAN_INCOME))
            {
                
                CONSUMPTION_BUDGET=CONSUMPTION_PROPENSITY*PAYMENT_ACCOUNT+(1-CONSUMPTION_PROPENSITY)
                *INITIAL_CONSUMPTION_PROPENSITY*MEAN_INCOME;
            }
            else
            {
                CONSUMPTION_BUDGET = PAYMENT_ACCOUNT;
            }*/

        /*Compute the wealth income ratio*/
        
        WEALTH_INCOME_RATIO_ACTUAL = WEALTH/ MEAN_NET_INCOME;

              
    /* Based on Carrol-Rule: Determination of the consumption budget
     * Note: CONSUMPTION_BUDGET > PAYMENT_ACCOUNT means household wants to sell assets.
     *       A check is performed after transactions if the consumption budget can be financed.
     */
	//CONSUMPTION_BUDGET = MEAN_NET_INCOME + CARROL_CONSUMPTION_PARAMETER*(WEALTH - WEALTH_INCOME_RATIO_TARGET*MEAN_NET_INCOME);

    /* Rule 2:
     */
	//CONSUMPTION_BUDGET = (1-TARGET_SAVINGS_RATE)*MEAN_NET_INCOME;

    /* Sander van der Hoog, 10.9.2010
     * The following rule is the same, but split into liquid and asset wealth:
     * Liquid wealth: income plus a percentage of payment account -> consumption budget grows along with payment account
     * Asset wealth: if trading is switched on, add a percentage of (asset wealth - target wealth) to the consumption budget -> (dis)investment in assets
     */

	asset_wealth = ASSETSOWNED.units*ASSETSOWNED.lastprice;
	CONSUMPTION_BUDGET = MEAN_NET_INCOME + CARROL_CONSUMPTION_PARAMETER*PAYMENT_ACCOUNT +
						TRADING_ACTIVITY * CARROL_CONSUMPTION_PARAMETER * (asset_wealth - WEALTH_INCOME_RATIO_TARGET*MEAN_NET_INCOME);
	


    /*Print debug for PAYMENT_ACCOUNT=nan at IT 620
     * This bug: 23.08.2010
     */
    #ifdef _DEBUG_MODE 
    {
	if (PRINT_DEBUG_CONSUMPTION)
	if((DAY>=2200)&&(DAY<=2240))
	{
	    fprintf(stderr, "\n\n IT %d Household_determine_consumption_budget:", DAY); 
	    fprintf(stderr, "\n\t ID %d PAYMENT_ACCOUNT %f CONSUMPTION_BUDGET %f\n", ID, PAYMENT_ACCOUNT, CONSUMPTION_BUDGET);
	}
    }
    #endif


    /* Minimum level of consumption: life-style maintenance */
/*
    if(CONSUMPTION_BUDGET < 0.5*LAST_NET_INCOME.array[3])
    {
	CONSUMPTION_BUDGET = 0.5*LAST_NET_INCOME.array[3];
    }
*/
               
        #ifdef _DEBUG_MODE 
	if (PRINT_DEBUG_CONSUMPTION)
	{
	    //Prints to std err:
	    if(PAYMENT_ACCOUNT < 0)
            {    
		fprintf(stderr, "\n\n IT %d Household_determine_consumption_budget: PAYMENT ACCOUNT<0", DAY); 
		fprintf(stderr, "\n\t ID %d PAYMENT_ACCOUNT %f CONSUMPTION_BUDGET %f\n", ID, PAYMENT_ACCOUNT, CONSUMPTION_BUDGET);
	    }
	    
	    if(CONSUMPTION_BUDGET < 0)
            {
		fprintf(stderr, "\n\n IT %d Household_determine_consumption_budget: CONSUMPTION_BUDGET < 0", DAY);
		fprintf(stderr, "\n\t ID %d PAYMENT_ACCOUNT %f CONSUMPTION_BUDGET %f", ID, PAYMENT_ACCOUNT, CONSUMPTION_BUDGET);
	    }	    
	    if (PAYMENT_ACCOUNT < CONSUMPTION_BUDGET)
	    {
		fprintf(stderr, "\n\n IT %d Household_determine_consumption_budget: PAYMENT_ACCOUNT < CONSUMPTION_BUDGET (household wants to sell shares).", DAY);
		fprintf(stderr, "\n\t ID %d WEALTH=%f PAYMENT_ACCOUNT=%f, CONSUMPTION_BUDGET=%f.", ID, WEALTH, PAYMENT_ACCOUNT, CONSUMPTION_BUDGET);
	    }
	    
	    //Prints to std out:
		if (PAYMENT_ACCOUNT < CONSUMPTION_BUDGET)
		{
		    printf("\n\n IT %d Household_determine_consumption_budget: PAYMENT_ACCOUNT < CONSUMPTION_BUDGET (household wants to sell shares).", DAY);
		    printf("\n\t ID %d WEALTH=%f PAYMENT_ACCOUNT=%f, CONSUMPTION_BUDGET=%f.", ID, WEALTH, PAYMENT_ACCOUNT, CONSUMPTION_BUDGET);
		}

		if(PAYMENT_ACCOUNT < 0)
		{    
		    printf("\n\n IT %d Household_determine_consumption_budget: PAYMENT ACCOUNT<0", DAY); 
		    printf("\n\t ID %d PAYMENT_ACCOUNT %f CONSUMPTION_BUDGET %f\n", ID, PAYMENT_ACCOUNT, CONSUMPTION_BUDGET);
		}
		
		if(CONSUMPTION_BUDGET < 0)
		{
		    printf("\n\n IT %d Household_determine_consumption_budget: CONSUMPTION_BUDGET < 0", DAY);
		    printf("\n\t ID %d PAYMENT_ACCOUNT %f CONSUMPTION_BUDGET %f", ID, PAYMENT_ACCOUNT, CONSUMPTION_BUDGET);
		}	    
	}
        #endif            

    /* Simple case: no selling of assets is possible, so do not consume more than your liquid assets */
    if ((TRADING_ACTIVITY==0)&&(CONSUMPTION_BUDGET > PAYMENT_ACCOUNT))
	CONSUMPTION_BUDGET = PAYMENT_ACCOUNT;

    CONSUMPTION_BUDGET_IN_MONTH = CONSUMPTION_BUDGET;
                        
    WEEKLY_BUDGET = CONSUMPTION_BUDGET/4;
    WEEK_OF_MONTH = 4;
    
    //Variable was used for consumption delaying  (old code)
    EXCESS_WEEKLY_BUDGET = -1;

    return 0;   
}


/** \fn Household_rank_and_buy_goods_1()
 * \brief Household receives information about the offered range of goods in the malls.
 *  Depending on these infos the household sends its good request       
 */
int Household_rank_and_buy_goods_1()
{
    
    //Logit model parameter:
    double sum_weighted_qual_pric_ratios = 0; 
    int j=0;
    int i=0;
    double logit;

    logit_firm_id_array  logit_firm_id_list;
    init_logit_firm_id_array(&logit_firm_id_list);

    mall_quality_price_info_array mall_quality_price_info_list;
    init_mall_quality_price_info_array(&mall_quality_price_info_list);

 
	//Delete the CURRENT_PRICE_QUALITY_LIST

	for(i=0; i<CURRENT_PRICE_QUALITY_LIST.size;i++)
		{
			remove_consumption_goods_offer(&CURRENT_PRICE_QUALITY_LIST,i);
			i--;
	
		}		



        /*Household reads quality price info mesasges sent by malls   */
        START_QUALITY_PRICE_INFO_1_MESSAGE_LOOP

    	if( quality_price_info_1_message->available==1)
             {   
        add_mall_quality_price_info(&mall_quality_price_info_list,  quality_price_info_1_message->mall_id, quality_price_info_1_message->firm_id,               quality_price_info_1_message->mall_region_id,                   quality_price_info_1_message->quality,                  quality_price_info_1_message->price, 
        quality_price_info_1_message->available);
  			  }

		//Update the price and quantity list (even those which are not available)
		
			if( quality_price_info_1_message->price>1e-5)
			{
				add_consumption_goods_offer(&CURRENT_PRICE_QUALITY_LIST, quality_price_info_1_message->firm_id, quality_price_info_1_message->quality,  quality_price_info_1_message->price);
			}
					
        FINISH_QUALITY_PRICE_INFO_1_MESSAGE_LOOP

        
        //+++++ Logit Model +++++++++:

        
        /*Sum of weighted exponents of quality price ratios*/
        for(i = 0; i < mall_quality_price_info_list.size;i++) 
        {
            sum_weighted_qual_pric_ratios += (mall_quality_price_info_list.array[i]
            .available) * exp(GAMMA_CONST*(GAMMA_QUALITY*log(mall_quality_price_info_list.array[i].quality) -log(mall_quality_price_info_list.array[i].price))); 


    
        }

        /* Compute logits and add on temporary logit array   */
        for(i = 0; i < mall_quality_price_info_list.size;i++) 
        {
            logit = (mall_quality_price_info_list.array[i].available) *
			 exp(GAMMA_CONST*(GAMMA_QUALITY*log(mall_quality_price_info_list.array[i].quality) -log(mall_quality_price_info_list.array[i].price))) / 
            sum_weighted_qual_pric_ratios;
            
            logit = logit * 100;
			
            if(logit > 0)
            {
                add_logit_firm_id(&logit_firm_id_list, logit, 
                mall_quality_price_info_list.array[i].firm_id);
            }

        }

        if(sum_weighted_qual_pric_ratios > 0)
        {
            MALL_COMPLETELY_SOLD_OUT = 0;
            int random_number = random_int(0,100);
            j=0;
            int x =0, index_selected_good=j;

            for(j = 0; j < logit_firm_id_list.size;j++)
            {
            
                /*if randum number <= logit then select the corresponding good  */ 
                if((random_number < logit_firm_id_list.array[j].logit) && (x != 1))
                {
                    ORDER_QUANTITY[0].firm_id = logit_firm_id_list.
                    array[j].firm_id;
                
                    x = 1;
                    index_selected_good= j;
                }
                /*else sum logits and go to the next iteration step  */
                else
                {
                    if((j < logit_firm_id_list.size-1) )
                    {   
                        logit_firm_id_list.array[j+1].logit =
                        logit_firm_id_list.array[j+1].logit+
                        logit_firm_id_list.array[j].logit;
                    }
                }
            }

            /*This computes and stores the order quantity of the selected good and saves the price in memory */
            ORDER_QUANTITY[0].quantity = WEEKLY_BUDGET/ mall_quality_price_info_list
            .array[index_selected_good].price;
        
            ORDER_QUANTITY[0].price = mall_quality_price_info_list.
            array[index_selected_good].price;

			ORDER_QUANTITY[0].quality= mall_quality_price_info_list
            .array[index_selected_good].quality;

            /*The consumption request message is sent  */ 
            add_consumption_request_1_message(
            mall_quality_price_info_list.array[index_selected_good].mall_id,ID,REGION_ID,
            ORDER_QUANTITY[0].firm_id,
            ORDER_QUANTITY[0].quantity);

        }
        else
        {
            EXPENDITURES=0;
            MALL_COMPLETELY_SOLD_OUT =1;
            ORDER_QUANTITY[0].quantity=0;
            ORDER_QUANTITY[0].price=0;
            ORDER_QUANTITY[0].firm_id=0;
			ORDER_QUANTITY[0].quality= 0.0;
        }

    free_mall_quality_price_info_array(&mall_quality_price_info_list);
    free_logit_firm_id_array(&logit_firm_id_list);

    return 0;

}

/** \fn Household_read_rationing()
 * \brief The household gets information about the accepted amount of goods and,
 * if the mall is completely sold out then the households set the order and delivery volumes
 * from the second step equal 0          
 */
int Household_receive_goods_read_rationing()
{
	//Set LAST_WEEKLY_BUDGET = WEEKLY_BUDGET
	LAST_WEEKLY_BUDGET = WEEKLY_BUDGET;
	
    if(MALL_COMPLETELY_SOLD_OUT == 0)
    {
        EXPENDITURES = 0;

        /*Household reads messages containing the realized consumption of the first round*/
        START_ACCEPTED_CONSUMPTION_1_MESSAGE_LOOP

                RATIONED = accepted_consumption_1_message->rationed;

                /*Update of Budget  */
                WEEKLY_BUDGET = WEEKLY_BUDGET - accepted_consumption_1_message
                ->offered_consumption_volume * ORDER_QUANTITY[0].price;
                
                EXPENDITURES =accepted_consumption_1_message
                ->offered_consumption_volume * ORDER_QUANTITY[0].price;
                HOUSEHOLD_OUTFLOWS_CALENDAR.consumption_expenditure += 	
                accepted_consumption_1_message->offered_consumption_volume * ORDER_QUANTITY[0].price;
                
             
                RECEIVED_QUANTITY[0].quantity = accepted_consumption_1_message
                ->offered_consumption_volume;

                RECEIVED_QUANTITY[0].firm_id = ORDER_QUANTITY[0].firm_id;

        FINISH_ACCEPTED_CONSUMPTION_1_MESSAGE_LOOP
    }
    else if(MALL_COMPLETELY_SOLD_OUT == 1)
    {
        EXPENDITURES= 0;
        RECEIVED_QUANTITY[0].quantity = 0;
        RECEIVED_QUANTITY[0].firm_id = 0;
        ORDER_QUANTITY[1].quantity = 0;
        ORDER_QUANTITY[1].firm_id = 0;
        ORDER_QUANTITY[1].price = 0;
        RECEIVED_QUANTITY[1].quantity = 0;
        RECEIVED_QUANTITY[1].firm_id = 0;
        
    }    
   
    	//Reset on first day of calendar month
    if (DAY%20==1)
        MONTHLY_CONSUMPTION_EXPENDITURE = 0.0;
    
    MONTHLY_CONSUMPTION_EXPENDITURE += EXPENDITURES;
    

    return 0;
}


int Household_set_values_zero()
{
        ORDER_QUANTITY[1].quantity = 0;
        ORDER_QUANTITY[1].firm_id = 0;
        ORDER_QUANTITY[1].price = 0;
        RECEIVED_QUANTITY[1].quantity = 0;
        RECEIVED_QUANTITY[1].firm_id = 0;

    return 0;
}

/*If rationed repeat ranking and request of goods: */
int Household_rank_and_buy_goods_2()    
{
            int j = 0;
            int i = 0;
            double logit;
            double sum_weighted_qual_pric_ratios = 0; 

            //Temporary arrays
            logit_firm_id_array logit_firm_id_list;
            init_logit_firm_id_array(&logit_firm_id_list);

            mall_quality_price_info_array mall_quality_price_info_list;
            init_mall_quality_price_info_array(&mall_quality_price_info_list);

        /*The updated quality price message is read  */
        START_QUALITY_PRICE_INFO_2_MESSAGE_LOOP

        if( quality_price_info_2_message->available==1)
        {
                add_mall_quality_price_info(&mall_quality_price_info_list,quality_price_info_2_message->mall_id, 
                quality_price_info_2_message->firm_id, 
                quality_price_info_2_message->mall_region_id, 
                quality_price_info_2_message->quality, 
                quality_price_info_2_message->price, 
                quality_price_info_2_message->available);
        }          
        FINISH_QUALITY_PRICE_INFO_2_MESSAGE_LOOP



        //+++++ Logit Model +++++++++:

        /*Sum of weighted exponents of quality price ratios   */
        for(i = 0;i < mall_quality_price_info_list.size; i++) 
        {
            sum_weighted_qual_pric_ratios +=(mall_quality_price_info_list
            .array[i].available) *
            exp(GAMMA_CONST*(GAMMA_QUALITY*log(mall_quality_price_info_list.array[i].quality) -log(mall_quality_price_info_list.array[i].price))); 
        }

        /*This computes the logits  */
        for(i = 0; i < mall_quality_price_info_list.size; i++) 
        {
            logit = (mall_quality_price_info_list.array[i].available) * 
			exp(GAMMA_CONST*(GAMMA_QUALITY*log(mall_quality_price_info_list.array[i].quality) -log(mall_quality_price_info_list.array[i].price))) / 
            sum_weighted_qual_pric_ratios;

            logit = logit*100;

            add_logit_firm_id(&logit_firm_id_list, logit,
            mall_quality_price_info_list.array[i].firm_id);
        }

        if(sum_weighted_qual_pric_ratios>0)
        {
            int random_number = random_int(0,100);
            j = 0;
            int x = 0, index_selected_good=j;

            for(j = 0; j < logit_firm_id_list.size;j++)
            {
                /*if random number <= logit then select the corresponding good  */ 
                if((random_number < logit_firm_id_list.array[j].logit)
                && (x!=1))
                {
                    ORDER_QUANTITY[1].firm_id = logit_firm_id_list
                    .array[j].firm_id; //Seleced Good
                
                    x =1;
                    index_selected_good= j;
                }
                /*else sum logits and go to next iteration step */
                else
                {
                    if((j < logit_firm_id_list.size-1) )
                    {
                        logit_firm_id_list.array[j+1].logit = logit_firm_id_list.array[j+1].logit+ 
                        logit_firm_id_list.array[j].logit;
                    }
                }
            }
        
            /*This computes the order quantity  and store the price */
            ORDER_QUANTITY[1].quantity = WEEKLY_BUDGET/
            mall_quality_price_info_list.array[index_selected_good].price;

            ORDER_QUANTITY[1].price = mall_quality_price_info_list
            .array[index_selected_good].price;
		
			ORDER_QUANTITY[1].quality= mall_quality_price_info_list
            .array[index_selected_good].quality;

            /*Sending the second consumption request message  */
            add_consumption_request_2_message(
            mall_quality_price_info_list.array[index_selected_good].mall_id,
            ID,REGION_ID,ORDER_QUANTITY[1].firm_id,
            ORDER_QUANTITY[1].quantity);
        }
        else
        {       
            ORDER_QUANTITY[1].quantity = 0;
            ORDER_QUANTITY[1].firm_id= 0;
            ORDER_QUANTITY[1].price= 0;
			ORDER_QUANTITY[1].quality= 1.0;
        }

    free_mall_quality_price_info_array(&mall_quality_price_info_list);
    free_logit_firm_id_array(&logit_firm_id_list);

    return 0;
}

/** \fn Household_receive_goods_read_rationing_2()
 * \brief This function stores in memory the realized consumption if HH was rationed in the first round.
 */
int Household_receive_goods_read_rationing_2()
{

    if(RATIONED ==1)
    {
        /*Read the message about accepted consumption */
        START_ACCEPTED_CONSUMPTION_2_MESSAGE_LOOP

                RATIONED = accepted_consumption_2_message->rationed;

                RECEIVED_QUANTITY[1].quantity=
                accepted_consumption_2_message->offered_consumption_volume;
                
                RECEIVED_QUANTITY[1].firm_id = 
                ORDER_QUANTITY[1].firm_id; 

        FINISH_ACCEPTED_CONSUMPTION_2_MESSAGE_LOOP
    }
    else
    {
        RECEIVED_QUANTITY[1].quantity=0.0;
        RECEIVED_QUANTITY[1].firm_id =0; 
    }

    WEEKLY_BUDGET = WEEKLY_BUDGET - RECEIVED_QUANTITY[1].quantity 
    *ORDER_QUANTITY[1].price;
    
    EXPENDITURES += RECEIVED_QUANTITY[1].quantity * ORDER_QUANTITY[1].price;
    HOUSEHOLD_OUTFLOWS_CALENDAR.consumption_expenditure += 
    RECEIVED_QUANTITY[1].quantity * ORDER_QUANTITY[1].price;
    
    MONTHLY_CONSUMPTION_EXPENDITURE += EXPENDITURES;

    return 0;
}

/** \fn Household_receive_dividends_dummy()
 * \brief Dummy to prevent households from reading the dividend payments from firms.
 */
int Household_receive_dividends_dummy()
{
        return 0;   
}


/** \fn Household_handle_leftover_budget()
 * \brief This function converts the remaining budget, that is not spent in both consumption steps, into the PAYMENT_ACCOUNT            
 */
int Household_handle_leftover_budget()
{
        CONSUMPTION_BUDGET -= EXPENDITURES; 

        if(WEEK_OF_MONTH !=1)
        {               
            PAYMENT_ACCOUNT -= EXPENDITURES;
            WEEK_OF_MONTH--;
            WEEKLY_BUDGET = CONSUMPTION_BUDGET / WEEK_OF_MONTH;
        }
        else
        {
            PAYMENT_ACCOUNT =PAYMENT_ACCOUNT - EXPENDITURES;
            
            WEEK_OF_MONTH--;
        }
        
        //set rationed back to zero:
        RATIONED = 0;
    
    return 0;
}


/** \fn Household_send_account_update()
 * \brief This function sends the PAYMENT_ACCOUNT to the bank            
 */
int Household_send_account_update()
{
	//send msg to bank
	add_bank_account_update_message(ID, BANK_ID, PAYMENT_ACCOUNT);

    return 0;
}
