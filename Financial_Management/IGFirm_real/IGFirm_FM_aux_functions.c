/*********************************
 * IGFirm_aux_functions.c 
 * IGFirm auxiliary functions.
 * *********************************
 * History:
 * 14/09/09 Sander
 *********************************/

#include "../header.h"
#include "../IGFirm_agent_header.h"
#include "../my_library_header.h"
#include "IGFirm_FM_aux_header.h"

/*
 * \fn IGFirm_compute_dividends_real_version()
 * \brief Function to compute dividends for real version of the IGFirm.
 */
void IGFirm_compute_dividends_real_version(void)
{    
    //option 2: total dividend payment increases with same ratio as net earnings
    //This is very dangerous, since earnings may fluctuate violently
    //TOTAL_DIVIDEND_PAYMENT *= NET_EARNINGS/PREVIOUS_NET_EARNINGS;

    //option 3: keep dividend per share constant
    //total divided payment increases with same ratio as current_shares_outstanding
    //TOTAL_DIVIDEND_PAYMENT *= CURRENT_SHARES_OUTSTANDING/PREVIOUS_SHARES_OUTSTANDING;

    //option 4: keep earnings per share constant
    //total divided payment increases with same ratio as earnings per share
    //this keeps earnings per share constant
    if ((PREVIOUS_EARNINGS_PER_SHARE>0.0)&&(PREVIOUS_SHARES_OUTSTANDING>0))
    {
        TOTAL_DIVIDEND_PAYMENT *= (EARNINGS_PER_SHARE/PREVIOUS_EARNINGS_PER_SHARE)
                                   *(CURRENT_SHARES_OUTSTANDING/PREVIOUS_SHARES_OUTSTANDING);
	}
	else
	{
		if(PREVIOUS_SHARES_OUTSTANDING == 0 || CURRENT_SHARES_OUTSTANDING == 0)
		printf("ERROR in Firm_compute_dividends: PREVIOUS_SHARES_OUTSTANDING = %d --- CURRENT_SHARES_OUTSTANDING = %d\n", PREVIOUS_SHARES_OUTSTANDING, CURRENT_SHARES_OUTSTANDING);	
	}

    //Determine total_dividend_payment when it is zero, and there are positive net earnings.
    //Set total divided payment equal to some dividend-earnings ratio (a parameter)
    
    if(TOTAL_DIVIDEND_PAYMENT<1e-6 && NET_EARNINGS>0.0)
    {
        TOTAL_DIVIDEND_PAYMENT = CONST_DIVIDEND_EARNINGS_RATIO * NET_EARNINGS;
        //printf("\n In Firm_compute_dividends: setting TOTAL_DIVIDEND_PAYMENT = %2.4f\n", TOTAL_DIVIDEND_PAYMENT):
    }
    
    //Always check:
    if (EARNINGS<0.0)
        TOTAL_DIVIDEND_PAYMENT = 0.0;
    
    //Continue with computation of ratios
    PREVIOUS_DIVIDEND_PER_SHARE = CURRENT_DIVIDEND_PER_SHARE;
    
    if (CURRENT_SHARES_OUTSTANDING>0)
        CURRENT_DIVIDEND_PER_SHARE = TOTAL_DIVIDEND_PAYMENT/CURRENT_SHARES_OUTSTANDING;
    else
    {
    	CURRENT_DIVIDEND_PER_SHARE = 0.0;
    	TOTAL_DIVIDEND_PAYMENT = 0.0;
    }
    
    PREVIOUS_DIVIDEND_PER_EARNINGS = CURRENT_DIVIDEND_PER_EARNINGS;
    
    if (NET_EARNINGS>0.0)
        CURRENT_DIVIDEND_PER_EARNINGS = TOTAL_DIVIDEND_PAYMENT/NET_EARNINGS;
    else
        CURRENT_DIVIDEND_PER_EARNINGS = 0.0;

		#ifdef _DEBUG_MODE         
		if (PRINT_DEBUG)
		{ 
		    printf("\n\n IGFirm_compute_dividends ID: %d",ID);
		    printf("\n\t NET_EARNINGS: %f TOTAL_DIVIDEND_PAYMENT: %f",NET_EARNINGS,TOTAL_DIVIDEND_PAYMENT);
		}
		#endif
}

/*
 * \fn IGFirm_compute_dividends_dummy_version()
 * \brief Function to compute dividends for *dummy* version of the IGFirm.
 */
void IGFirm_compute_dividends_dummy_version(void)
{    
    		double average_last_net_profits = 0.0;
    		double total_dividend_payment;
    		TOTAL_DIVIDEND_PAYMENT = 0.0;
    		
    		remove_double(&LAST_NET_PROFITS,0);
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

