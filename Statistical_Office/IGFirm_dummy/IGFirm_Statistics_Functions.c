#include "../../header.h"
#include "../../IGFirm_agent_header.h"
#include "../../my_library_header.h"


int IGFirm_reset_variables()
{

		RECEIVED_INTEREST_IN_CALENDAR_MONTH=0;
		
		IGFIRM_STOCKS_CALENDAR.payment_account_day_1 = PAYMENT_ACCOUNT;
		
		
		
		IGFIRM_OUTFLOWS_CALENDAR.energy_costs = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.tax_payment = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.total_dividend_payment = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.value_of_repurchased_shares = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.total_expenses = 0.0;
		
		IGFIRM_INFLOWS_CALENDAR.cum_revenue = 0.0;
		IGFIRM_INFLOWS_CALENDAR.value_of_issued_shares = 0.0;
		IGFIRM_INFLOWS_CALENDAR.subsidy = 0.0;
		IGFIRM_INFLOWS_CALENDAR.total_income = 0.0;
		IGFIRM_INFLOWS_CALENDAR.deposit_interest = 0.0;
		IGFIRM_INFLOWS_CALENDAR.net_inflow = 0.0;
		
		
		int i;

	double total_assets = 0.0;
	double equity = 0.0;
	
	if (DAY==1)
	{
		//Set initial capital goods price in relation to the wage
		CAPITAL_GOOD_PRICE  = INITIAL_CAPITAL_PRICE_WAGE_RATIO * WAGE_OFFER;

		//Enter vintage array
		for (i=0; i<VINTAGES.size; i++)	
			VINTAGES.array[i].price	= INITIAL_CAPITAL_PRICE_WAGE_RATIO * WAGE_OFFER;
		
		//UNIT COSTS
		UNIT_COSTS = INITIAL_CAPITAL_PRICE_WAGE_RATIO * WAGE_OFFER;
	}
	
   
  
    total_assets = PAYMENT_ACCOUNT ;

    equity = total_assets ;
    
	
    
    IGFIRM_STOCKS_CALENDAR.equity = equity;
    IGFIRM_STOCKS_CALENDAR.total_liabilities = equity;
   	IGFIRM_STOCKS_CALENDAR.total_assets = total_assets;
    IGFIRM_STOCKS_CALENDAR.payment_account = PAYMENT_ACCOUNT;
  

	return 0;
}


/** \fn IGFirm_read_policy_announcements()
 * \brief IGFirms reads the policy_announcement_messages from Governments
 */
int IGFirm_read_policy_announcements()
{
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


/** \fn Firm_receive_data()
 * \brief Firms receive the data messages from the Eurostat*/
int IGFirm_receive_data()
{
				
	/* If day of month to act... */



		START_MSG_SKILLS_EUROSTAT_TO_IGFIRM_MESSAGE_LOOP

		ECONOMY_WIDE_GENERAL_SKILLS_IN_FIRMS=msg_skills_eurostat_to_igfirm_message->mean_general_skills;
		ECONOMY_WIDE_SPECIFIC_SKILLS_IN_FIRMS=msg_skills_eurostat_to_igfirm_message->mean_specific_skills;
		PRODUCTIVITY_PROGRESS_IN_ECONOMY=msg_skills_eurostat_to_igfirm_message->productivity_progress;
		ECONOMY_WIDE_CAPITAL_STOCK = msg_skills_eurostat_to_igfirm_message->total_capital_stock_units;

		FINISH_MSG_SKILLS_EUROSTAT_TO_IGFIRM_MESSAGE_LOOP

		UNIT_COSTS = UNIT_COSTS*(1+PRODUCTIVITY_PROGRESS_IN_ECONOMY);
		
		
		
		return 0;
}


/** \fn IGFirm_send_subsidy_notification()
 * \brief Function to send a subsidy_notification_message to the government. 
 */
int IGFirm_send_subsidy_notification()
{
      
    return 0;       
}

/** \fn IGFirm_send_transfer_notification()
 * \brief Function to send a transfer_notification_message to the government. 
 */
int IGFirm_send_transfer_notification()
{
    
        
    return 0;       
}



/** \fn Firm_send_data_to_Eurostat()
 * \brief Firms send data to Market Research: controlling results and creating macro data
 */
int IGFirm_send_data_to_Eurostat()
{


	//Increase the age of the firm in months
	AGE++;
	
	add_firm_send_data_message(ID, REGION_ID, 0, 0,0,
		0, 0, 0, 	
		0,0, 
		0,0,0,0,
		0,0, 0,0,0, 0,
		0,
		0, 0,	0, 0, 0,0,0, 0, 0, 0, 0, 0, 0,AGE, 0,0,0,0,0,IGFIRM_OUTFLOWS_CALENDAR.total_dividend_payment);
        
    return 0;       
}

/** \fn IGFirm_compute_stock_flows()
 * \brief IGFirms compute stock and flows for blanace sheets.
 */
int IGFirm_compute_stock_flows()
{
	
	IGFIRM_OUTFLOWS_CALENDAR.total_expenses =
   
    IGFIRM_OUTFLOWS_CALENDAR.energy_costs+
    IGFIRM_OUTFLOWS_CALENDAR.tax_payment+
    IGFIRM_OUTFLOWS_CALENDAR.total_dividend_payment+
    IGFIRM_OUTFLOWS_CALENDAR.value_of_repurchased_shares;
    
    IGFIRM_INFLOWS_CALENDAR.total_income =
    IGFIRM_INFLOWS_CALENDAR.cum_revenue+
    IGFIRM_INFLOWS_CALENDAR.value_of_issued_shares+
    IGFIRM_INFLOWS_CALENDAR.subsidy + 
    IGFIRM_INFLOWS_CALENDAR.deposit_interest;
    
    IGFIRM_STOCKS_CALENDAR.payment_account_day_20 = PAYMENT_ACCOUNT;
    
    IGFIRM_INFLOWS_CALENDAR.net_inflow = 
	IGFIRM_INFLOWS_CALENDAR.total_income -
	IGFIRM_OUTFLOWS_CALENDAR.total_expenses;

	double total_value_local_inventory = 0.0;
	double total_assets = 0.0;
	double equity = 0.0;
	double total_debt = 0.0;
	
    total_assets = PAYMENT_ACCOUNT;

    equity = total_assets - total_debt;
    
    IGFIRM_STOCKS_CALENDAR.equity = equity;
    IGFIRM_STOCKS_CALENDAR.total_debt = total_debt;
    IGFIRM_STOCKS_CALENDAR.total_liabilities = total_debt+equity;
    IGFIRM_STOCKS_CALENDAR.total_assets = total_assets;
    IGFIRM_STOCKS_CALENDAR.payment_account = PAYMENT_ACCOUNT;
    IGFIRM_STOCKS_CALENDAR.total_value_local_inventory = total_value_local_inventory;

	return 0;
}


int IGFirm_send_payments_to_bank()
{
	add_bank_account_update_message(ID, BANK_ID, PAYMENT_ACCOUNT);
	
	return 0;
}
