    #include "../../header.h"
    #include "../../IGFirm_agent_header.h"
    #include "../../my_library_header.h"
    

/*
 * \fn IGFirm_receive_account_interest()
 * \brief Read account_interest message from Bank. Daily, at start of iteration.
 */
int IGFirm_receive_account_interest()
{
    double interest =0;
    double interest_rate =0;
    
    /*For validation check*/
    if(DAY%MONTH == 1)
    {
	RECEIVED_INTEREST_IN_CALENDAR_MONTH=0;
    }
        
    //Read message from bank, set risk-free rate.
    START_ACCOUNT_INTEREST_MESSAGE_LOOP
	if(account_interest_message->bank_id == BANK_ID)
	    interest_rate = account_interest_message->interest_rate;
    FINISH_ACCOUNT_INTEREST_MESSAGE_LOOP
    
    /*Add daily interest on deposits: (1/240) of the interest rate*/
    interest = (1/240.0)*interest_rate*PAYMENT_ACCOUNT;
    PAYMENT_ACCOUNT += interest;  
    
    /*For validation check*/
    RECEIVED_INTEREST_DAILY = interest;
    RECEIVED_INTEREST_IN_CALENDAR_MONTH += interest;
    IGFIRM_INFLOWS_CALENDAR.deposit_interest += interest; 

    return 0;	
}
    
