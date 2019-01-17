#include "../header.h"
#include "../Household_agent_header.h"
#include "../my_library_header.h"
#include "Household_aux_header.h"
 
/*
 * \fn Household_receive_index_info()
 * \brief Read index_info message from Clearinghouse.
 */
int Household_receive_index_info()
{
    double dividend;
    RECEIVED_DIVIDEND=0;
    
    //Here the household sets its monthly consumption counter to zero at the first day of the month    
    if(DAY%MONTH==1)
    {
        MONTHLY_CONSUMPTION_EXPENDITURE = 0.0;
    }

    /*For validation check*/
    if(DAY%MONTH == 1)
    {
    	RECEIVED_DIVIDEND_IN_CALENDAR_MONTH=0;
    }

    //Set deposit rate to ECB base rate
    RISK_FREE_RATE = ECB_INTEREST_RATE;
    
    //Read message from bank, set risk-free rate.
    /*
    START_ACCOUNTINTEREST_MESSAGE_LOOP
	if(accountInterest_message->bank_id == BANK_ID)
	    RISK_FREE_RATE = accountInterest_message->interest;
    FINISH_ACCOUNTINTEREST_MESSAGE_LOOP
    */
    
    //Read index_info message from Clearinghouse, add dividends.
    START_INDEX_INFO_MESSAGE_LOOP
        //if (PRINT_DEBUG_AFM) printf("\n ID=%d In Household_receive_index_info: Reading the index_info_message with dividend_per_share = %f\t price = %f", ID, index_info_message->dividend_per_share, index_info_message->price);
	dividend = index_info_message->dividend_per_share*ASSETSOWNED.units;
    FINISH_INDEX_INFO_MESSAGE_LOOP
    
    /*For validation check*/
    RECEIVED_DIVIDEND += dividend;
    RECEIVED_DIVIDEND_IN_CALENDAR_MONTH += dividend;
    CUM_TOTAL_DIVIDENDS += dividend;
    PAYMENT_ACCOUNT += dividend;  
    HOUSEHOLD_INFLOWS_CALENDAR.total_dividends += dividend;        

    return 0;	
}

/*
 * \fn Household_receive_index_price()
 * \brief Read index_price message from Clearinghouse. Monthly on activation day, at start of iteration.
 */
int Household_receive_index_price()
{
    //Read index_info message from Clearinghouse.
    START_INDEX_PRICE_MESSAGE_LOOP
	ASSETSOWNED.lastprice = index_price_message->price;
	ASSETSOWNED.moving_avg_price = index_price_message->moving_avg_price;
    FINISH_INDEX_PRICE_MESSAGE_LOOP

    return 0;	
}
    
/*
 * \fn Household_revises_expected_portfolio()
 * \brief Function to revise the index portfolio
 */
int Household_revises_expected_portfolio()
{
    double monetary_value=0.0;
    double portfolio_budget=0.0;
    double net_investment=0.0;
    int planned_shares=0;
    int net_shares=0;
    
    //In Household_Consumer_Functions.c, Household_determine_consumption_budget we set: PORTFOLIO_BUDGET (no longer used).
    //Step 1: Compute the value of the planned asset portfolio (deposits + index)
    portfolio_budget = PAYMENT_ACCOUNT + ASSETSOWNED.lastprice*ASSETSOWNED.units - CONSUMPTION_BUDGET;

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM)
    {
	printf("\n\n Household_revises_expected_portfolio: ID %d Activation day=%d", ID, DAY_OF_MONTH_TO_ACT);
	printf("\n\t PAYMENT_ACCOUNT = %f CONSUMPTION_BUDGET = %f\t portfolio_budget = %f\t", PAYMENT_ACCOUNT, CONSUMPTION_BUDGET, portfolio_budget);
    }
    #endif

    //Step 2: Compute composition of the new planned portfolio, using mean-variance maximization framework
    //Step 2a: Update beliefs
    logit_decision_model();
 
    //Step 3a: The proportion of the portfolio budget to be invested in the index is derived from any theory
    if (TRADING_RANDOM==0)
	monetary_value = BELIEFS.fraction_to_invest*portfolio_budget;

    //Step 3b: Random value: a random fraction of portfolio_budget is to be invested in the index
    if (TRADING_RANDOM==1)
	monetary_value = random_unif()*portfolio_budget;

    //Step 3c: (Test) The full portfolio_budget is to be invested in the index, no deposits
    //monetary_value =  portfolio_budget;

    //Step 4: Transform monetary_value to net monetary_value to invest/disinvest, based on the value of the current asset portfolio:
    net_investment = monetary_value - ASSETSOWNED.lastprice*ASSETSOWNED.units;    

    planned_shares = (int) (monetary_value/ASSETSOWNED.lastprice);
    net_shares 	   = (int) (net_investment/ASSETSOWNED.lastprice);

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM)
    {
	printf("\n\t monetary_value = %f asset value = %f net_investment = %f\n", monetary_value, ASSETSOWNED.lastprice*ASSETSOWNED.units, net_investment);
	printf("\n\t planned shares = %d owned shares = %d net shares = %d my current price = %f\n", planned_shares, ASSETSOWNED.units, net_shares, ASSETSOWNED.lastprice);
    }
    #endif

    //Step 5: Check if units to sell > units owned; if so, sell all units in portfolio
    if ((net_investment<0.0) && (ASSETSOWNED.units + net_shares<0))
    {    
	net_investment = -ASSETSOWNED.lastprice*ASSETSOWNED.units;
	if (PRINT_DEBUG_AFM) printf("\n\t Adjusting sales (units to sell > units owned): net_investment = %f", net_investment);
    }	
    
    //Step 6: Send market order: negative value means sell, positive means buy
    add_order_message(ID, net_investment);
    
    return 0;	
}



/*
 * \fn Household_update_portfolio()
 * \brief Function to update the index portfolio after transactions have occurred.
 */
int Household_update_portfolio()
{
    //Read order_status message
    START_ORDER_STATUS_MESSAGE_LOOP
	
	//Update assetsowned
	//(negative quantity means selling, positive quantity means buying)	
	if ((ASSETSOWNED.units + order_status_message->quantity) <0) 
	{
	    printf("\n\n Household_update_portfolio: ID %d Error: after transactions nr_shares negative ASSETSOWNED.units=%d.", ID, ASSETSOWNED.units+order_status_message->quantity);
	    printf("\n\t I did not add them, and do not want to update the PAYMENT_ACCOUNT and WEALTH.\n");
	}    
	else
	{
	    ASSETSOWNED.units  += order_status_message->quantity;

	    //Update payment account (negative value means selling, positive value means buying)
	    PAYMENT_ACCOUNT -= order_status_message->value;
	    
	    //Update the wealth
	    WEALTH = PAYMENT_ACCOUNT + ASSETSOWNED.lastprice*ASSETSOWNED.units;
	}

	//Determine cash flow of the transaction and add to flow variables
	//(negative value means selling, positive value means buying)
       if(order_status_message->quantity < 0)
       {
       		HOUSEHOLD_INFLOWS_CALENDAR.asset_sales += -(order_status_message->value);
       }
       else
       {
       		HOUSEHOLD_OUTFLOWS_CALENDAR.asset_purchases += (order_status_message->value);
       }
	
    FINISH_ORDER_STATUS_MESSAGE_LOOP


    //Rescaling the consumption budget to accomodate the payment account
    //Preventing negative payment accounts (occurs when wealth is very high, but household cannot sell its shares)
    if (PAYMENT_ACCOUNT < CONSUMPTION_BUDGET)
    {
	CONSUMPTION_BUDGET = PAYMENT_ACCOUNT;
	CONSUMPTION_BUDGET_IN_MONTH = PAYMENT_ACCOUNT;

	#ifdef _DEBUG_MODE    
	if (PRINT_DEBUG_AFM)
	{
	    printf("\n\n IT %d Household_update_portfolio: PAYMENT_ACCOUNT < CONSUMPTION_BUDGET", DAY);
	    printf("\n\t Rescaling consumption budget to payment account (insufficient selling).");
	    printf("\n\t ID %d WEALTH=%f PAYMENT_ACCOUNT=%f, CONSUMPTION_BUDGET=%f.\n", ID, WEALTH, PAYMENT_ACCOUNT, CONSUMPTION_BUDGET);
	}
	#endif                    

    }


    return 0;	
}
