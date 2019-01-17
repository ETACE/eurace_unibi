#include "../header.h"
#include "../Bank_agent_header.h"
#include "../my_library_header.h"


int Bank_reset_variables()
{

	BANK_STOCKS_CALENDAR.cash_day_1 = CASH;
	
	BANK_OUTFLOWS_CALENDAR.firm_loan_issues =0.0;
	BANK_OUTFLOWS_CALENDAR.debt_installment_to_ecb = 0.0;
	BANK_OUTFLOWS_CALENDAR.ecb_interest_payment =0.0;
	BANK_OUTFLOWS_CALENDAR.deposit_interest_payment =0.0;
	BANK_OUTFLOWS_CALENDAR.dividend_payment =0.0;
	BANK_OUTFLOWS_CALENDAR.tax_payment =0.0;
	BANK_OUTFLOWS_CALENDAR.deposit_outflow =0.0;
	BANK_OUTFLOWS_CALENDAR.total_expenses =0.0;
	
	BANK_INFLOWS_CALENDAR.firm_loan_installments =0.0;
	BANK_INFLOWS_CALENDAR.firm_interest_payments =0.0;
	BANK_INFLOWS_CALENDAR.new_ecb_debt =0.0;
	BANK_INFLOWS_CALENDAR.deposit_inflow =0.0;
	BANK_INFLOWS_CALENDAR.total_income =0.0;
	
	BANK_INFLOWS_CALENDAR.net_inflow =0.0;
	BANK_INFLOWS_CALENDAR.net_deposit_inflow =0.0;
	
	

	return 0;
}

/** \fn Bank_read_policy_announcements()
 * \brief Function to read the policy_announcements from Governments.
 */
int Bank_read_policy_announcements()
{
    //Message send by Government:
    START_POLICY_ANNOUNCEMENT_MESSAGE_LOOP          
        //Filter: 
        if(policy_announcement_message->gov_id == GOV_ID)
        {
            TAX_RATE_CORPORATE = policy_announcement_message->tax_rate_corporate;
        }
    FINISH_POLICY_ANNOUNCEMENT_MESSAGE_LOOP

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_CREDIT)
    {
        printf("\n Bank_read_policy_announcements ID: %d",ID);
        printf("\n \t TAX_RATE_CORPORATE: %f",TAX_RATE_CORPORATE);
    }
    #endif
        
    return 0;
}
