#include "../header.h"
#include "../Household_agent_header.h"
#include "../my_library_header.h"



/************************************ Household agent functions ************************************/

int Household_reset_variables()
{
	HOUSEHOLD_STOCKS_CALENDAR.payment_account_day_1 = PAYMENT_ACCOUNT;
	
	HOUSEHOLD_OUTFLOWS_CALENDAR.consumption_expenditure = 0.0;
	HOUSEHOLD_OUTFLOWS_CALENDAR.tax_payment = 0.0;
	HOUSEHOLD_OUTFLOWS_CALENDAR.restitution_payment = 0.0;
	HOUSEHOLD_OUTFLOWS_CALENDAR.asset_purchases = 0.0;
	HOUSEHOLD_OUTFLOWS_CALENDAR.total_expenses = 0.0;
	
	HOUSEHOLD_INFLOWS_CALENDAR.wage = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.unemployment_benefit = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.subsidies = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.transfer = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.gov_interest = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.asset_sales = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.total_dividends = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.total_income = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.deposit_interest = 0.0;
	HOUSEHOLD_INFLOWS_CALENDAR.net_inflow = 0.0;


	/* Variables for analysing LM Flows.*/
	JUST_EMPLOYED = 0;
	JUST_UNEMPLOYED = 0;
	START_EMPLOYED = 0;
	START_UNEMPLOYED = 0;
	ENTER_MATCHING = 0;
	
	/* Initialization: on hte first day_of_month_to_act UNEMPLOYED_DURATION becomes zero*/
	if(DAY == DAY_OF_MONTH_TO_ACT)
	{
		UNEMPLOYED_DURATION = -1;	
	}

	/* Employment status at the beginning of a month.*/
	if(EMPLOYEE_FIRM_ID == -1)
	{
		START_UNEMPLOYED = 1;	
		UNEMPLOYED_DURATION = 0;
	}
	else
	{
		START_EMPLOYED = 1;
		UNEMPLOYED_DURATION = 0;
	}


	return 0;
}


/* \fn: int Household_initialization()
 * \brief Function to initialize. Note: this overwrites pop settings for the NEIGHBORING_REGION_IDS.
 */
int Household_initialization()
{   
    //ADD HERE SOME FUNCTIONS THAT SET THE NEIGHBORHOOD STRUCTURE OF REGIONS

    /*********** NETWORK: complete graph **************/
/*    
    int j, k=TOTAL_REGIONS; //total number of regions
    
    reset_int_array(&NEIGHBORING_REGION_IDS);
    
    for (j=1; j<=k; j++) 
        add_int(&NEIGHBORING_REGION_IDS,j);
*/

    /*********** NETWORK: k neighbors with wrap-around */
    int j, k=2;
    for (j=1; j<=k; j++)
    { 
        if((REGION_ID+j)<=TOTAL_REGIONS)
            add_int(&NEIGHBORING_REGION_IDS,(REGION_ID+j));
        else
            add_int(&NEIGHBORING_REGION_IDS,(REGION_ID+j)%TOTAL_REGIONS);
    }
    /*********** NETWORK: k neighbors without wrap-around */
    //for (REGION_ID>k): use backward neighborhood
    //for (REGION_ID<=): use forward neighborhood
    /******************************************************/
/*    
    int j, k=2; //each region has k neighbors
    
    reset_int_array(&NEIGHBORING_REGION_IDS);

    //add the region_id of regions that are in the household's neighbourhood
    if (REGION_ID>k)
    {
        //set neighbourhood_regions={REGION_ID-k,...,REGION_ID-1}
        for (j=1; j<=k; j++) 
            add_int(&NEIGHBORING_REGION_IDS,REGION_ID-j);
    }
    if (REGION_ID<=k)
    {
        //set neighbourhood_regions={REGION_ID+1,...,REGION_ID+k}
        for (j=1; j<=k; j++) 
            add_int(&NEIGHBORING_REGION_IDS,REGION_ID+j);
    }
*/

 
    return 0;   
}

/*************************************Household Role: Statistics *********************************/
/** \fn Household_read_policy_announcements()
 * \brief This function reads messages send by the government announcing tax rates, benefits, transfer payments and subsidies.
 */
int Household_read_policy_announcements()
{
    /*Read tax announcement*/
    /*Read unemployment benefit announcement*/
    /*Read transfer announcement*/
    /*Read subsidy announcement*/
    START_POLICY_ANNOUNCEMENT_MESSAGE_LOOP
    if(policy_announcement_message->gov_id == GOV_ID)
    {
        TAX_RATE_HH_LABOUR  = policy_announcement_message->tax_rate_hh_labour;
        TAX_RATE_HH_CAPITAL = policy_announcement_message->tax_rate_hh_capital;

        /*This is the endogeneous unemployment percentage (the global parameter is: GOV_POLICY_UNEMPLOYMENT_BENEFIT_PCT)*/
        UNEMPLOYMENT_BENEFIT_PCT = policy_announcement_message->unemployment_benefit_pct;
        TRANSFER_PAYMENT = policy_announcement_message->hh_transfer_payment;
        SUBSIDY_PCT = policy_announcement_message->hh_subsidy_pct;
    }
    FINISH_POLICY_ANNOUNCEMENT_MESSAGE_LOOP

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_HOUSEHOLD)
    {
        printf("\n Household_read_policy_announcements ID: %d",ID);
        printf("\n \t TAX_RATE_HH_LABOUR: %f TAX_RATE_HH_CAPITAL: %f",TAX_RATE_HH_LABOUR,TAX_RATE_HH_CAPITAL);
        printf("\n \t UNEMPLOYMENT_BENEFIT_PCT: %f TRANSFER_PAYMENT: %f SUBSIDY_PCT: %f", UNEMPLOYMENT_BENEFIT_PCT, TRANSFER_PAYMENT, SUBSIDY_PCT);
    }
    #endif

	// HC Policy: Announcement
	if(GOV_POLICY_SWITCH_HUMAN_CAPITAL_IMPROVEMENT==1)
	{
	// If human capital policy is installed:
	START_HUMAN_CAPITAL_POLICY_ANNOUNCEMENT_MESSAGE_LOOP

		HUMAN_CAPITAL_POLICY_FLAG = 1;

		add_human_capital_policy_general_skill_information_message(ID,GOV_ID,GENERAL_SKILL);
	
	FINISH_HUMAN_CAPITAL_POLICY_ANNOUNCEMENT_MESSAGE_LOOP
    }	
    return 0;
}


/*
 * \fn Household_human_capital_policy()
 * \brief Update of general skills if there is a human capital policy
 */
int Household_human_capital_policy()
{

	START_HUMAN_CAPITAL_POLICY_NEW_GENERAL_SKILL_NOTIFICATION_MESSAGE_LOOP

	//printf("GENERAL_SKILL vorher: %d \n",GENERAL_SKILL);
	GENERAL_SKILL = human_capital_policy_new_general_skill_notification_message->general_skills;

	HUMAN_CAPITAL_POLICY_FLAG = 0;
	//printf("GENERAL_SKILL nachher: %d \n",GENERAL_SKILL);
	FINISH_HUMAN_CAPITAL_POLICY_NEW_GENERAL_SKILL_NOTIFICATION_MESSAGE_LOOP
return 0;
}









/*
 * \fn Household_receive_account_interest()
 * \brief Read account_interest message from Bank. Daily, at start of iteration.
 */
int Household_receive_account_interest()
{
    double interest =0;
    
    /*For validation check*/
    if(DAY%MONTH == 1)
    {
	RECEIVED_INTEREST_IN_CALENDAR_MONTH=0;
    }
    
    //Set deposit rate to ECB base rate
    //RISK_FREE_RATE = ECB_INTEREST_RATE;
    
    //Read message from bank, set risk-free rate.
    START_ACCOUNT_INTEREST_MESSAGE_LOOP
	if(account_interest_message->bank_id == BANK_ID)
	    RISK_FREE_RATE = account_interest_message->interest_rate;
    FINISH_ACCOUNT_INTEREST_MESSAGE_LOOP
    
    /*Add daily interest on deposits: (1/240) of the interest rate*/
    interest = (1/240.0)*RISK_FREE_RATE*PAYMENT_ACCOUNT;
    PAYMENT_ACCOUNT += interest;  
    
    /*For validation check*/
    RECEIVED_INTEREST_DAILY = interest;
    RECEIVED_INTEREST_IN_CALENDAR_MONTH += interest;
    HOUSEHOLD_INFLOWS_CALENDAR.deposit_interest += interest; 

    return 0;	
}

/** \fn Household_send_data_to_Eurostat()
 * \brief Households send data to Eurostat
 */
int Household_send_data_to_Eurostat()
{   
	double portfolio_value = 0.0;
	int nr_assets = 0;

	add_household_send_data_message(ID, REGION_ID, GENERAL_SKILL,EMPLOYEE_FIRM_ID,
	WAGE, SPECIFIC_SKILL,JUST_EMPLOYED,JUST_UNEMPLOYED,START_EMPLOYED,START_UNEMPLOYED,ENTER_MATCHING,UNEMPLOYED_DURATION, 		
	CONSUMPTION_BUDGET_IN_MONTH,PAYMENT_ACCOUNT,MEAN_NET_INCOME);
	
	
	HOUSEHOLD_STOCKS_CALENDAR.payment_account_day_20 = PAYMENT_ACCOUNT;
	
	HOUSEHOLD_OUTFLOWS_CALENDAR.total_expenses = 
	HOUSEHOLD_OUTFLOWS_CALENDAR.consumption_expenditure +
	HOUSEHOLD_OUTFLOWS_CALENDAR.tax_payment +
	HOUSEHOLD_OUTFLOWS_CALENDAR.restitution_payment +
	HOUSEHOLD_OUTFLOWS_CALENDAR.asset_purchases; 
	
	HOUSEHOLD_INFLOWS_CALENDAR.total_income = 
	HOUSEHOLD_INFLOWS_CALENDAR.wage +
	HOUSEHOLD_INFLOWS_CALENDAR.unemployment_benefit +
	HOUSEHOLD_INFLOWS_CALENDAR.subsidies +
	HOUSEHOLD_INFLOWS_CALENDAR.transfer +
	HOUSEHOLD_INFLOWS_CALENDAR.gov_interest +
	HOUSEHOLD_INFLOWS_CALENDAR.asset_sales +
	HOUSEHOLD_INFLOWS_CALENDAR.total_dividends + 
	HOUSEHOLD_INFLOWS_CALENDAR.deposit_interest;
	
	HOUSEHOLD_INFLOWS_CALENDAR.net_inflow = 
	HOUSEHOLD_INFLOWS_CALENDAR.total_income -
	HOUSEHOLD_OUTFLOWS_CALENDAR.total_expenses;
	
		
	portfolio_value = ASSETSOWNED.units*ASSETSOWNED.lastprice;
	nr_assets 	= ASSETSOWNED.units;
				
	HOUSEHOLD_STOCKS_CALENDAR.payment_account = PAYMENT_ACCOUNT;
	HOUSEHOLD_STOCKS_CALENDAR.portfolio_value = portfolio_value;
	HOUSEHOLD_STOCKS_CALENDAR.total_assets = PAYMENT_ACCOUNT + portfolio_value;
	HOUSEHOLD_STOCKS_CALENDAR.nr_assets = nr_assets;
	
    return 0;
}


/** \fn Household_read_data_from_Eurostat()
 * \brief Households read data from Eurostat
 */
int Household_read_data_from_Eurostat()
{   
    //The household reads the mean wage in its region (we assume this is a country)
    START_DATA_FOR_GOVERNMENT_MESSAGE_LOOP
            if(data_for_government_message->region_id==REGION_ID)
            {
                //Read region mean wage
                REGION_WIDE_MEAN_WAGE = data_for_government_message->mean_wage;
            }
    FINISH_DATA_FOR_GOVERNMENT_MESSAGE_LOOP
    
    return 0;
}
