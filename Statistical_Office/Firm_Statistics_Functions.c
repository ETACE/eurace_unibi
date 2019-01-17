#include "../header.h"
#include "../Firm_agent_header.h"
#include "../my_library_header.h"

/** \fn Firm_send_id_to_malls()
 * \brief Firms send IDs to malls for initialization.
 */
int Firm_send_id_to_malls()
{

    //Add the message to malls
    add_msg_firm_id_to_malls_message(ID,REGION_ID);

    return 0;
}

/** \fn Firm_initialize_mall_arrays()
 * \brief Initialization of mall array data structures in firm memory for with multiple region models.
 */
int Firm_initialize_mall_arrays()
{

	//Set the sold quantities of the last month to 0

         int i,j,k,l;
        
        for(j=0; j < MALLS_SALES_STATISTICS.size;j++)
        {
			for(k = 0; k < MALLS_SALES_STATISTICS.array[j].sales.size; k++)
            {
                if(MALLS_SALES_STATISTICS.array[j].sales.array[k].period==1)
                {       
          			MALLS_SALES_STATISTICS.array[j].sales.array[0].sales=0.0;
          		}
			}     
               
        } 


	START_MSG_MALL_ID_TO_FIRMS_MESSAGE_LOOP

	for(i=0; i < MALLS_SALES_STATISTICS.size;i++)
	{
		if(MALLS_SALES_STATISTICS.array[i].mall_id==msg_mall_id_to_firms_message->mall_id)
		{
			MALLS_SALES_STATISTICS.array[i].region_id=msg_mall_id_to_firms_message->region_id;
		}

	}
	//Set the correct region id and divid the regional market sizes by the number of regions to get the correct allocation
/*
	for(i=0; i < LAST_MARKET_SIZES.size;i++)
	{
		if(LAST_MARKET_SIZES.array[i].mall_id==msg_mall_id_to_firms_message->mall_id)
		{
			LAST_MARKET_SIZES.array[i].region_id=msg_mall_id_to_firms_message->region_id;
			for(j=0;j<LAST_MARKET_SIZES.array[i].market_sizes.size;j++)
			{
				if(LAST_MARKET_SIZES.size>1)
				LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size= LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size/(LAST_MARKET_SIZES.size-1);

			}
		}

	}


		for(i=0; i < LAST_MARKET_SIZES.size;i++)
	{
		if(LAST_MARKET_SIZES.array[i].mall_id==msg_mall_id_to_firms_message->mall_id)
		{
			LAST_MARKET_SIZES.array[i].region_id=msg_mall_id_to_firms_message->region_id;
		}

	}
*/


    FINISH_MSG_MALL_ID_TO_FIRMS_MESSAGE_LOOP


		double regressor;
	   	double intercept;
	   	double variance;
		double sum_1, sum_2;

	for(i=0;i<LAST_MARKET_SIZES.size;i++)
	{
	    
		sum_1=0;
	 	sum_2=0;
		variance=0.0;

	    for (j=0;j<LAST_MARKET_SIZES.array[i].market_sizes.size; j++)
	    {
	    	sum_1+= (LAST_MARKET_SIZES.array[i].market_sizes.size + 1 - LAST_MARKET_SIZES.array[i].market_sizes.array[j].period)* LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size;
			sum_2+=  LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size;
		}
					
	    
	    regressor = (LAST_MARKET_SIZES.array[i].market_sizes.size * sum_1 - 0.5*LAST_MARKET_SIZES.array[i].market_sizes.size*(LAST_MARKET_SIZES.array[i].market_sizes.size+1)*sum_2)/
	        (1/6.0*pow(LAST_MARKET_SIZES.array[i].market_sizes.size,2)*(LAST_MARKET_SIZES.array[i].market_sizes.size+1)*
	       	(2*LAST_MARKET_SIZES.array[i].market_sizes.size+1)-1/4.0*(pow(LAST_MARKET_SIZES.array[i].market_sizes.size,2)*pow((LAST_MARKET_SIZES.array[i].market_sizes.size+1),2)));

	    intercept =  1/(1.0*LAST_MARKET_SIZES.array[i].market_sizes.size)*sum_2 - 0.5*regressor*(LAST_MARKET_SIZES.array[i].market_sizes.size+1);
	    	
	    variance = 0;
	    	
	   	for(j=0; j< LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size; j++)
	  	{
	  		variance+= pow(LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size-(intercept+ 
				(LAST_MARKET_SIZES.array[i].market_sizes.size + 1 - LAST_MARKET_SIZES.array[i].market_sizes.array[j].period)* regressor),2)
			  /(LAST_MARKET_SIZES.array[i].market_sizes.size-1);
    	}

	    LINEAR_REGRESSION_MARKET_SIZE.array[i].mall_id=LAST_MARKET_SIZES.array[i].mall_id;
		LINEAR_REGRESSION_MARKET_SIZE.array[i].region_id=LAST_MARKET_SIZES.array[i].region_id;
    	LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept=intercept;
	   	LINEAR_REGRESSION_MARKET_SIZE.array[i].regressor=regressor;
	   	LINEAR_REGRESSION_MARKET_SIZE.array[i].variance=variance;
	    	  
		
	}
	//Estimation of current market size based the linear regression 
	ESTIMATED_MARKET_SIZE  = LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept + (1+LAST_MARKET_SIZES.array[0].market_sizes.size)*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor;



		//Long term market size




		sum_1=0;
	 	sum_2=0;
		variance=0.0;

	  /*  for (i=0;i<LONG_TERM_MARKET_SIZE.size; i++)
	    {
	    	sum_1+= (LONG_TERM_MARKET_SIZE.size + 1 - LONG_TERM_MARKET_SIZE.array[i].period)* LONG_TERM_MARKET_SIZE.array[i].market_size;
			sum_2+=  LONG_TERM_MARKET_SIZE.array[i].market_size;
		}
					
	    
	    regressor = (LONG_TERM_MARKET_SIZE.size * sum_1 - 0.5*LONG_TERM_MARKET_SIZE.size*(LONG_TERM_MARKET_SIZE.size+1)*sum_2)/
	        (1/6.0*pow(LONG_TERM_MARKET_SIZE.size,2)*(LONG_TERM_MARKET_SIZE.size+1)*
	       	(2*LONG_TERM_MARKET_SIZE.size+1)-1/4.0*(pow(LONG_TERM_MARKET_SIZE.size,2)*pow((LONG_TERM_MARKET_SIZE.size+1),2)));

	    intercept =  1/(1.0*LONG_TERM_MARKET_SIZE.size)*sum_2 - 0.5*regressor*(LONG_TERM_MARKET_SIZE.size+1);
	    	
	    variance = 0;
	    	
	   	for(j=0; j< LONG_TERM_MARKET_SIZE.size; j++)
	  	{
	  		variance+= pow(LONG_TERM_MARKET_SIZE.array[i].market_size-(intercept+ 
				(LONG_TERM_MARKET_SIZE.size + 1 - LONG_TERM_MARKET_SIZE.array[i].period)* regressor),2)
			  /(LONG_TERM_MARKET_SIZE.size-1);
    	}




		LINEAR_REGRESSION_LONG_TERM_MARKET_SIZE.mall_id=0;
		LINEAR_REGRESSION_LONG_TERM_MARKET_SIZE.region_id=0;
    	LINEAR_REGRESSION_LONG_TERM_MARKET_SIZE.intercept=intercept;
	   	LINEAR_REGRESSION_LONG_TERM_MARKET_SIZE.regressor=regressor;
	   	LINEAR_REGRESSION_LONG_TERM_MARKET_SIZE.variance=variance;

	*/




if(XML_CLONED==1)
{

   
    int num_malls=0;
    double production_quantity_per_mall;

    //1. Count the number of total malls

    START_MSG_MALL_ID_TO_FIRMS_MESSAGE_LOOP

	num_malls++;

    FINISH_MSG_MALL_ID_TO_FIRMS_MESSAGE_LOOP

    //Compute the new production quantities for the malls
    production_quantity_per_mall = LAST_PLANNED_PRODUCTION_QUANTITIES.array[3] / num_malls;


    // Clean up all arrays

    for(i=0;i<SOLD_QUANTITIES.size;i++)
    {
	remove_estimators_linear_regression(&LINEAR_REGRESSION_ESTIMATORS,i);
	remove_sales_statistics(&MALLS_SALES_STATISTICS,i);
	remove_sold_quantities_per_mall(&SOLD_QUANTITIES,i);
	remove_delivery_volume_per_mall(&DELIVERY_VOLUME,i);
	remove_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME,i);
	remove_mall_info(&CURRENT_MALL_STOCKS,i);
    }

    //Set up the data arrays

    k=0;

    START_MSG_MALL_ID_TO_FIRMS_MESSAGE_LOOP

	for(l=0;l<FIRM_PLANNING_HORIZON;l++)
	{
	    add_data_type_sales(&MALLS_SALES_STATISTICS.array[k].sales,l+1,production_quantity_per_mall);
	}
	add_sold_quantities_per_mall(&SOLD_QUANTITIES,msg_mall_id_to_firms_message->mall_id, production_quantity_per_mall, 0,0.0);
	add_delivery_volume_per_mall(&DELIVERY_VOLUME,msg_mall_id_to_firms_message->mall_id,0.0,0.0,0.0);
	add_delivery_volume_per_mall(&PLANNED_DELIVERY_VOLUME,msg_mall_id_to_firms_message->mall_id,0.0,0.0,0.0);
	add_mall_info(&CURRENT_MALL_STOCKS,msg_mall_id_to_firms_message->mall_id, production_quantity_per_mall,0.0);

	k++;
    FINISH_MSG_MALL_ID_TO_FIRMS_MESSAGE_LOOP
}//end xml_cloned



	// Set the R and D indicator variable:

	PRODUCT_INNOVATION = INNOVATION_SWITCHED_ON;

    return 0;
}

/** \fn Firm_reset_variables()
 * \brief Firms resets balance sheet flow variables. Activation: 1st of calendar month.
 */
int Firm_reset_variables()
{
	int i;
	
		//Set initial capital goods price in relation to the wage
		if (DAY==1)
		{
			ACTUAL_CAP_PRICE = INITIAL_CAPITAL_PRICE_WAGE_RATIO * WAGE_OFFER;

			for (i=0;i<CAPITAL_FINANCING.size;i++)
				CAPITAL_FINANCING.array[i].financing_per_month = TOTAL_UNITS_CAPITAL_STOCK*DEPRECIATION_RATE * 
					ACTUAL_CAP_PRICE / (CONST_INSTALLMENT_PERIODS);

			//Adjust initial loan: total value remains the same, just time to repay is changed
			LOANS.array[0].installment_amount 		= LOANS.array[0].loan_value / (CONST_INSTALLMENT_PERIODS);
			LOANS.array[0].var_per_installment 		= LOANS.array[0].residual_var / (CONST_INSTALLMENT_PERIODS);
			LOANS.array[0].nr_periods_before_repayment 	= (CONST_INSTALLMENT_PERIODS+1);
		}

	    	TOTAL_INTEREST_PAYMENT_IN_CALENDAR_MONTH =0.0;
		TOTAL_DEBT_INSTALLMENT_PAYMENT_IN_CALENDAR_MONTH =0.0; 
		TOTAL_EXTERNAL_FINANCING_OBTAINED=0.0;
		
		FIRM_STOCKS_CALENDAR.payment_account_day_1 = PAYMENT_ACCOUNT;
		
		FIRM_OUTFLOWS_CALENDAR.labour_costs = 0.0;
		FIRM_OUTFLOWS_CALENDAR.capital_costs = 0.0;
		FIRM_OUTFLOWS_CALENDAR.energy_costs = 0.0;
		FIRM_OUTFLOWS_CALENDAR.tax_payment = 0.0;
		FIRM_OUTFLOWS_CALENDAR.total_debt_installment_payment = 0.0;
		FIRM_OUTFLOWS_CALENDAR.total_interest_payment = 0.0;
		FIRM_OUTFLOWS_CALENDAR.total_dividend_payment = 0.0;
		FIRM_OUTFLOWS_CALENDAR.value_of_repurchased_shares = 0.0;
		FIRM_OUTFLOWS_CALENDAR.total_expenses = 0.0;
		
		FIRM_INFLOWS_CALENDAR.cum_revenue = 0.0;
		FIRM_INFLOWS_CALENDAR.new_loans = 0.0;
		FIRM_INFLOWS_CALENDAR.value_of_issued_shares = 0.0;
		FIRM_INFLOWS_CALENDAR.subsidy = 0.0;
		FIRM_INFLOWS_CALENDAR.total_income = 0.0;
		FIRM_INFLOWS_CALENDAR.deposit_interest = 0.0;
		FIRM_INFLOWS_CALENDAR.net_inflow = 0.0;
    
	return 0;
}


/** \fn Firm_receive_data()
 * \brief Firms receive the data messages from the Eurostat.
 */
int Firm_receive_data()
{
    int i,j;

    START_EUROSTAT_SEND_SPECIFIC_SKILLS_MESSAGE_LOOP
        
        /*Specific skills of the domestic region*/
        //Filter: 
        if(eurostat_send_specific_skills_message->region_id == REGION_ID)
        {

            /*If there is no employee with general skill level 1 resp. 2-5*/
            if(NO_EMPLOYEES_SKILL_1 == 0)
            {
                AVERAGE_S_SKILL_OF_1 =                      eurostat_send_specific_skills_message->
                specific_skill_1;
            }

            if(NO_EMPLOYEES_SKILL_2 == 0)
            {
                AVERAGE_S_SKILL_OF_2 =                      eurostat_send_specific_skills_message->
                specific_skill_2;
            }

            if(NO_EMPLOYEES_SKILL_3 == 0)
            {
                AVERAGE_S_SKILL_OF_3 =                      eurostat_send_specific_skills_message->
                specific_skill_3;
            }

            if(NO_EMPLOYEES_SKILL_4 == 0)
            {
                AVERAGE_S_SKILL_OF_4 =                      eurostat_send_specific_skills_message->
                specific_skill_4;
            }

            if(NO_EMPLOYEES_SKILL_5 == 0)
            {
                AVERAGE_S_SKILL_OF_5 =                      eurostat_send_specific_skills_message->
                specific_skill_5;
            }
			
            /*Average regional specific skill level used for determining the initial production quantity after bankruptcy*/

            AVERAGE_S_SKILL_FROM_EUROSTAT =		 eurostat_send_specific_skills_message->
		specific_skill;		
            
	    /* Set averages from Eurostat */
	    if (MEAN_WAGE<1e-6) MEAN_WAGE = 		eurostat_send_specific_skills_message->average_wage;
	    AVERAGE_OUTPUT_FROM_EUROSTAT  = 		eurostat_send_specific_skills_message->average_output;
	    
            /*Increase wage offer regarding the productivity increase*/
            if(DAY%20 == 1)
            {
/*		
		    #ifdef _DEBUG_MODE    
		    if (PRINT_DEBUG_BANKRUPTCY)
		    {
			if(ID < 3)
			{
			    printf("\n\n IT %d Firm receive data ID: %d",DAY, ID);  
			    printf("\n\t eurostat_send_specific_skills_message->productivity_progress %f",eurostat_send_specific_skills_message->productivity_progress);
			    printf("\n\t eurostat_send_specific_skills_message->specific_skill %f",eurostat_send_specific_skills_message->specific_skill);
			}
		    }          
		    #endif        
*/
                               
                int i;
                for(i = 0; i < EMPLOYEES.size; i++)
                {  
                    EMPLOYEES.array[i].wage = EMPLOYEES.array[i].wage*(1+(eurostat_send_specific_skills_message->productivity_progress)*UNION_STRENGTH);    
                }

				 for(i = 0; i < R_AND_D_EMPLOYEES.size; i++)
                {  
                    R_AND_D_EMPLOYEES.array[i].wage = R_AND_D_EMPLOYEES.array[i].wage*(1+(eurostat_send_specific_skills_message->productivity_progress)*UNION_STRENGTH);    
                }
		
                CPI = eurostat_send_specific_skills_message->cpi;
				CURRENT_PRICE_INDEX = eurostat_send_specific_skills_message->price_index;
                NO_COMPETITORS = eurostat_send_specific_skills_message->no_active_firms - 1;
                CURRENT_QUALITY_INDEX = eurostat_send_specific_skills_message->average_quality;
                
                if(VARIABLES_LAST_YEAR.size==12)
                {
                	remove_dt_variables_changed(&VARIABLES_LAST_YEAR,0);
		
                }

				 add_dt_variables_changed(&VARIABLES_LAST_YEAR, CURRENT_PRICE_INDEX, CURRENT_QUALITY_INDEX,eurostat_send_specific_skills_message->productivity_progress);
              
                
			
            }
        }
        
        /* Receive data on capital stock
	// Used by firm to set size_by_capital_stock_indicator: 0 is below mean, 1 is above mean
	*/
	double mean_capital = eurostat_send_specific_skills_message->total_capital_stock_units / eurostat_send_specific_skills_message->no_firms;
	INDICATOR_SIZE_BY_CAPITAL_STOCK = (TOTAL_UNITS_CAPITAL_STOCK > mean_capital);
	        
    FINISH_EUROSTAT_SEND_SPECIFIC_SKILLS_MESSAGE_LOOP

	if(DAY>=40)
	{

	for(i=0;i<LAST_MARKET_SIZES.size;i++)
		{
			
				for(j=0;j<LAST_MARKET_SIZES.array[i].market_sizes.size;j++)
				{
					if(LAST_MARKET_SIZES.array[i].market_sizes.array[j].period==12)
					{
						remove_dt_market_size(&LAST_MARKET_SIZES.array[i].market_sizes,j);
					}
				}

				for(j=0;j<LAST_MARKET_SIZES.array[i].market_sizes.size;j++)
				{
					
						LAST_MARKET_SIZES.array[i].market_sizes.array[j].period++;
	
				}


		}


/*
	for(i=0;i<LONG_TERM_MARKET_SIZE.size;i++)
	{
		if(LONG_TERM_MARKET_SIZE.array[i].period==60)
		{
			remove_dt_market_size(&LONG_TERM_MARKET_SIZE,i);
		}
	}

	for(i=0;i<LONG_TERM_MARKET_SIZE.size;i++)
	{
					
		LONG_TERM_MARKET_SIZE.array[i].period++;
	
	}*/



	START_MSG_MARKET_SIZES_MESSAGE_LOOP
		for(i=0;i<LAST_MARKET_SIZES.size;i++)
		{
			if(msg_market_sizes_message->region_id==LAST_MARKET_SIZES.array[i].region_id)
			{
		
				if(msg_market_sizes_message->region_id==0)
				{
			 		MARKET_SIZE = msg_market_sizes_message->market_size/CURRENT_PRICE_INDEX;
					//Add to long term array: 
					//add_dt_market_size(&LONG_TERM_MARKET_SIZE,1,msg_market_sizes_message->market_size/CURRENT_PRICE_INDEX);


				}

				add_dt_market_size(&LAST_MARKET_SIZES.array[i].market_sizes,1,msg_market_sizes_message->market_size/CURRENT_PRICE_INDEX);
			}
		}


	FINISH_MSG_MARKET_SIZES_MESSAGE_LOOP
	}

    //Message send by Government:
    START_POLICY_ANNOUNCEMENT_MESSAGE_LOOP          
        //Filter: 
        if(policy_announcement_message->gov_id == GOV_ID)
        {
            TAX_RATE_CORPORATE = policy_announcement_message->tax_rate_corporate;
            TAX_RATE_VAT = policy_announcement_message->tax_rate_vat;
            TRANSFER_PAYMENT = policy_announcement_message->firm_transfer_payment;
            SUBSIDY_PCT = policy_announcement_message->firm_subsidy_pct;
        }
    FINISH_POLICY_ANNOUNCEMENT_MESSAGE_LOOP
    


    return 0;
}


/** \fn Firm_send_data_to_Eurostat()
 * \brief Firms send data to Market Research: controlling results and creating macro data
 */
int Firm_send_data_to_Eurostat()
{
    
    /*Determine the productivity of the firm. Send data to Eurostat in 
     * order to calculate the productivity progress once a year*/
  

        FIRM_PRODUCTIVITY_LAST_YEAR = FIRM_PRODUCTIVITY;
        
        if(MEAN_SPECIFIC_SKILLS >= TECHNOLOGY)
        {
            FIRM_PRODUCTIVITY = TECHNOLOGY;
        }
        else
        {
            FIRM_PRODUCTIVITY = MEAN_SPECIFIC_SKILLS;
        }
	if (FIRM_PRODUCTIVITY_LAST_YEAR>1e-5)
	    FIRM_PRODUCTIVITY_PROGRESS = FIRM_PRODUCTIVITY/FIRM_PRODUCTIVITY_LAST_YEAR -1;
	else
	    FIRM_PRODUCTIVITY_PROGRESS = 0.0;
	        
    //Increase the age of the firm in months (only for firms that are active, not bankrupt)
	if (ACTIVE)
	{
	    AGE++;
	}

	//Set zero_output indicator:
	if (OUTPUT<1.0)	ZERO_OUTPUT=1; else ZERO_OUTPUT=0;

	//Set other indicators:
	if(NET_EARNINGS >0)  INDICATOR_EARNINGS=1; 	else INDICATOR_EARNINGS=0;
	if(CAPITAL_COSTS >0) INDICATOR_CAPITAL_COSTS=1; else INDICATOR_CAPITAL_COSTS=0;


    add_firm_send_data_message(ID, REGION_ID, VACANCIES,POSTED_VACANCIES, NO_EMPLOYEES,
    NO_EMPLOYEES_SKILL_1, NO_EMPLOYEES_SKILL_2, NO_EMPLOYEES_SKILL_3, NO_EMPLOYEES_SKILL_4, NO_EMPLOYEES_SKILL_5,NO_EMPLOYEES_PRODUCTION,NO_EMPLOYEES_INNOVATION, 
    TOTAL_MEAN_WAGE, MEAN_WAGE, MEAN_WAGE_R_AND_D, MEAN_SPECIFIC_SKILLS,
    AVERAGE_S_SKILL_OF_1, AVERAGE_S_SKILL_OF_2, AVERAGE_S_SKILL_OF_3, AVERAGE_S_SKILL_OF_4, AVERAGE_S_SKILL_OF_5,
    FIRM_INFLOWS_CALENDAR.cum_revenue, CAPITAL_COSTS, NET_EARNINGS, TOTAL_DEBT, TOTAL_ASSETS, EQUITY,
    PRICE, PRICE_LAST_MONTH,QUALITY, TOTAL_SUPPLY, SOLD_QUANTITY_IN_CALENDAR_MONTH, OUTPUT, PLANNED_OUTPUT, AGE,
    FIRM_PRODUCTIVITY, FIRM_PRODUCTIVITY_PROGRESS,FIRM_STOCKS_CALENDAR.total_value_local_inventory,
    TOTAL_UNITS_CAPITAL_STOCK,WAGE_OFFER, FIRM_OUTFLOWS_CALENDAR.total_dividend_payment);

 
/*Print debug for FIRM_INFLOWS_CALENDAR.cum_revenue=nan
 * This bug was resolved on 20.08.2010
 */

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_BANKRUPTCY)
    { 
	if(DAY>500)
	{
	    fprintf(stderr, "\n\n IT %d Firm_send_data_to_Eurostat ID: %d ACTIVE %d",DAY, ID, ACTIVE);
	    fprintf(stderr, "\n\t PAYMENT_ACCOUNT %f FIRM_INFLOWS_CALENDAR.cum_revenue: %f CAPITAL_COSTS: %f",PAYMENT_ACCOUNT, FIRM_INFLOWS_CALENDAR.cum_revenue, CAPITAL_COSTS);
	    fprintf(stderr, "\n\t BANKRUPTCY_INSOLVENCY_STATE: %d BANKRUPTCY_ILLIQUIDITY_STATE: %d", BANKRUPTCY_INSOLVENCY_STATE, BANKRUPTCY_ILLIQUIDITY_STATE);
    	}
    }   
    #endif

    return 0;
}

    
/** \fn Firm_compute_stock_flows()
 * \brief Firms compute stock and flows for blanace sheets.
 */
int Firm_compute_stock_flows()
{

    FIRM_OUTFLOWS_CALENDAR.total_expenses =
    FIRM_OUTFLOWS_CALENDAR.labour_costs+
    FIRM_OUTFLOWS_CALENDAR.capital_costs+
    FIRM_OUTFLOWS_CALENDAR.energy_costs+
    FIRM_OUTFLOWS_CALENDAR.tax_payment+
    FIRM_OUTFLOWS_CALENDAR.total_debt_installment_payment+
    FIRM_OUTFLOWS_CALENDAR.total_interest_payment+
    FIRM_OUTFLOWS_CALENDAR.total_dividend_payment+
    FIRM_OUTFLOWS_CALENDAR.value_of_repurchased_shares;
    
    
    FIRM_INFLOWS_CALENDAR.total_income =
    FIRM_INFLOWS_CALENDAR.cum_revenue+
    FIRM_INFLOWS_CALENDAR.new_loans+
    FIRM_INFLOWS_CALENDAR.value_of_issued_shares+
    FIRM_INFLOWS_CALENDAR.subsidy +
    FIRM_INFLOWS_CALENDAR.deposit_interest;
    
    FIRM_STOCKS_CALENDAR.payment_account_day_20 = PAYMENT_ACCOUNT;
    
    FIRM_INFLOWS_CALENDAR.net_inflow = 
	FIRM_INFLOWS_CALENDAR.total_income -
	FIRM_OUTFLOWS_CALENDAR.total_expenses;
	
	
	int i;
	
	TOTAL_VALUE_LOCAL_INVENTORY = 0.0;
	for (i=0; i<CURRENT_MALL_STOCKS.size; i++)
	{
		TOTAL_VALUE_LOCAL_INVENTORY += CURRENT_PRICE_INDEX*CURRENT_MALL_STOCKS.array[i].current_stock;
	}
	
	TOTAL_DEBT = 0.0;
	for (i=LOANS.size-1; i>-1; i--)
	{
		TOTAL_DEBT += LOANS.array[i].loan_value;
	}

	TOTAL_ASSETS = PAYMENT_ACCOUNT + TOTAL_VALUE_CAPITAL_STOCK
		+ TOTAL_VALUE_LOCAL_INVENTORY;

	EQUITY = TOTAL_ASSETS - TOTAL_DEBT;
	
	FIRM_STOCKS_CALENDAR.equity = EQUITY;
	FIRM_STOCKS_CALENDAR.total_debt = TOTAL_DEBT;
	FIRM_STOCKS_CALENDAR.total_liabilities = TOTAL_DEBT+EQUITY;
	FIRM_STOCKS_CALENDAR.total_assets = TOTAL_ASSETS;
	FIRM_STOCKS_CALENDAR.payment_account = PAYMENT_ACCOUNT;
	FIRM_STOCKS_CALENDAR.total_value_capital_stock = TOTAL_VALUE_CAPITAL_STOCK;
	FIRM_STOCKS_CALENDAR.total_value_local_inventory = TOTAL_VALUE_LOCAL_INVENTORY;


    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FINMAN)
    { 
		if(ID==ID_DEBUG_PROBE)
		{
        	printf("\n\n Firm_compute_stock_flows ID: %d",ID);
        	printf("\n\t PAYMENT_ACCOUNT: %f TOTAL_VALUE_CAPITAL_STOCK: %f",PAYMENT_ACCOUNT,TOTAL_VALUE_CAPITAL_STOCK);
        	printf("\n\t TOTAL_VALUE_LOCAL_INVENTORY: %f TOTAL_ASSETS: %f",TOTAL_VALUE_LOCAL_INVENTORY,TOTAL_ASSETS);
        	printf("\n\t EQUITY: %f DEBT: %f",EQUITY,TOTAL_DEBT);
		}    
	}   
    #endif


	return 0;
}

/** \fn Firm_compute_stock_flows()
 * \brief Function to send end-of-day payment account data to the bank to update the account.
 */
int Firm_send_payments_to_bank()
{
     FILE *file1;
     char *filename;
	int i;
	double value_at_risk;
     
    add_bank_account_update_message(ID, BANK_ID, PAYMENT_ACCOUNT);

	//Total VAR for loans
	value_at_risk=0.0;
	for (i=0;i<LOANS.size;i++)
	{
		//Send credit_var_update msg to bank
		add_credit_var_update_message(ID, LOANS.array[i].bank_id, LOANS.array[i].residual_var);
	}


    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_PRODUCTION)
    {
	if(PAYMENT_ACCOUNT<-1e-6)
	    printf("PAYMENT_ACCOUNT of Firm %d:  %f \n",ID,PAYMENT_ACCOUNT);
    }
    #endif
    
    if (PRINT_DEBUG_FILE_EXP1)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/firms_balance_sheet.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %d %f %f %f %f",DAY,ID,TOTAL_UNITS_CAPITAL_STOCK,TOTAL_VALUE_CAPITAL_STOCK,TOTAL_UNITS_LOCAL_INVENTORY,TOTAL_VALUE_LOCAL_INVENTORY);
        fprintf(file1," %f %f %f %f %d",PAYMENT_ACCOUNT,TOTAL_ASSETS,TOTAL_DEBT,EQUITY,REGION_ID);
        fclose(file1);
        free(filename);

    }    
    
    return 0;
}

/** \fn Firm_send_subsidy_notification()
 * \brief Function to send a subsidy_notification_message to the government. 
 */
int Firm_send_subsidy_notification()
{
    if (POLICY_EXP_STABILIZATION_SUBSIDY==1)
    {    
        SUBSIDY_PAYMENT = SUBSIDY_PCT*CAPITAL_COSTS;
        
        /*Add subsidy message */
        add_firm_subsidy_notification_message(GOV_ID, SUBSIDY_PAYMENT);
        
        PAYMENT_ACCOUNT += SUBSIDY_PAYMENT;
    }   


	if (POLICY_EXP_BEST_TECHNOLOGY_SUBSIDY==1)
	{
        
        /*Add subsidy message */
        add_firm_subsidy_notification_message(GOV_ID, SUBSIDY_PAYMENT);
        
        PAYMENT_ACCOUNT += SUBSIDY_PAYMENT;

	}


     
    return 0;       
}

/** \fn Firm_send_transfer_notification()
 * \brief Function to send a transfer_notification_message to the government. 
 */
int Firm_send_transfer_notification()
{
    /*Add transfer message */
    add_firm_transfer_notification_message(GOV_ID);
    PAYMENT_ACCOUNT += TRANSFER_PAYMENT;
        
    return 0;       
}
