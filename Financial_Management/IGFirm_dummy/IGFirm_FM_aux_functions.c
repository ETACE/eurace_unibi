/*********************************
 * IGFirm_aux_functions.c 
 * IGFirm auxiliary functions.
 * *********************************
 * History:
 * 14/09/09 Sander
 *********************************/

#include "../../header.h"
#include "../../IGFirm_agent_header.h"
#include "../../my_library_header.h"
#include "IGFirm_FM_aux_header.h"


/*
 * \fn IGFirm_compute_dividends_dummy_version()
 * \brief Function to compute dividends for *dummy* version of the IGFirm.
 */
void IGFirm_compute_dividends_dummy_version(void)
{    
	double average_last_net_profits = 0.0;
	double total_dividend_payment;
	TOTAL_DIVIDEND_PAYMENT = 0.0;
    		
	//if(LAST_NET_PROFITS.size==18)


	if(LAST_NET_PROFITS.size==IGFIRM_DIVIDEND_PAYOUT_STRETCHING_MONTH)
	{
		remove_double(&LAST_NET_PROFITS,0);
	}
	add_double(&LAST_NET_PROFITS,NET_EARNINGS); 
    		
	int p;
	for(p = 0; p < LAST_NET_PROFITS.size; p++)
	{
		average_last_net_profits += LAST_NET_PROFITS.array[p];
	}
    
	if (LAST_NET_PROFITS.size > 0) 
		average_last_net_profits = average_last_net_profits/LAST_NET_PROFITS.size;
	else
		average_last_net_profits = 0.0;

	if (CURRENT_SHARES_OUTSTANDING > 0)
		CURRENT_DIVIDEND_PER_SHARE = average_last_net_profits/ CURRENT_SHARES_OUTSTANDING;
	else
		CURRENT_DIVIDEND_PER_SHARE = 0.0;
    
	//printf("\n IGFirm %d CURRENT_DIVIDEND_PER_SHARE %f %f			\n",ID,CURRENT_DIVIDEND_PER_SHARE,CURRENT_SHARES_OUTSTANDING);
    
	total_dividend_payment = average_last_net_profits;
	//printf("3: total_dividend_payment %f \n",total_dividend_payment);
        
        		
	//decrease payment_account with the total_dividend_payment
	//PAYMENT_ACCOUNT -= total_dividend_payment;
	if(PAYMENT_ACCOUNT > total_dividend_payment+TAX_PAYMENT)
	{
		TOTAL_DIVIDEND_PAYMENT = total_dividend_payment;
	}
	else
	{
		TOTAL_DIVIDEND_PAYMENT = PAYMENT_ACCOUNT-TAX_PAYMENT;
	}
		
}

