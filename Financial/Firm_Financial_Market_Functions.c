#include "../header.h"
#include "../Firm_agent_header.h"
#include "../my_library_header.h"

/*
 * \fn Firm_remains_in_bankruptcy()
 * \brief In bankruptcy branch: if a.external_financial_needs > 0.0, send an error message
 */
int Firm_remains_in_bankruptcy(void)
{
	printf("Error in Bankruptcy: Firm %d remains in bankruptcy. External financial needs: %f\n", ID, EXTERNAL_FINANCIAL_NEEDS);
	return 0;
}

/*
 * \fn Firm_receive_stock_info_dummy()
 * \brief Dummy for stategraph interface.
 */
int Firm_receive_stock_info_dummy(void)
{
	return 0;
}

/*
 * \fn Firm_check_minsky_class()
 * \brief Function to set the type of firm according to Minksy's Financial Instability Hypothesis.
 * MINSKY_STATE = 1: Non-borrowering firm. 
 * MINSKY_STATE = 2: Hedge borrowers, current income covers interest and principle (debt installment).
 * MINSKY_STATE = 3: Speculative borrowers: current income covers the interest but not the principle
 * MINSKY_STATE = 4: Ponzi borrowers: current income neither covers interest nor principle, nor both -- these firms have to mortgage their future income
 * MINSKY_STATE = 5: Non classified firms (could occur in principle, note that tax payments and dividend payments have been kept out of the conditions)
 */
int Firm_check_minsky_class()
{   
	MINSKY_STATE_1=0;
	MINSKY_STATE_2=0;
	MINSKY_STATE_3=0;
	MINSKY_STATE_4=0;
	MINSKY_STATE_5=0;

/* Conditions to check before the credit market opens
 * Just after Firm_compute_total_liquidity_needs
 */
	if (PAYMENT_ACCOUNT >= TOTAL_FINANCIAL_NEEDS)
		MINSKY_STATE_1 = 1;
	else if ((NET_EARNINGS +1e-5 >= TOTAL_INTEREST_PAYMENT + TOTAL_DEBT_INSTALLMENT_PAYMENT) 
			&& (PAYMENT_ACCOUNT < TOTAL_INTEREST_PAYMENT + TOTAL_DEBT_INSTALLMENT_PAYMENT + TAX_PAYMENT + TOTAL_DIVIDEND_PAYMENT + PRODUCTION_LIQUIDITY_NEEDS))
		MINSKY_STATE_2 = 1;
	else if ((NET_EARNINGS +1e-5 > TOTAL_INTEREST_PAYMENT && NET_EARNINGS < TOTAL_INTEREST_PAYMENT + TOTAL_DEBT_INSTALLMENT_PAYMENT))
		MINSKY_STATE_3 = 1;
	else if (NET_EARNINGS +1e-5 < TOTAL_INTEREST_PAYMENT && NET_EARNINGS +1e-5 < TOTAL_DEBT_INSTALLMENT_PAYMENT)
		MINSKY_STATE_4 = 1;
	else
		MINSKY_STATE_5 = 1;
	
	if(MINSKY_STATE_1) MINSKY_STATE=1;
	if(MINSKY_STATE_2) MINSKY_STATE=2;
	if(MINSKY_STATE_3) MINSKY_STATE=3;
	if(MINSKY_STATE_4) MINSKY_STATE=4;

    return 0;
}


/*
 * \fn Firm_set_minsky_state_crisis()
 * \brief Function to set the type of firm according to Minksy's Financial Instability Hypothesis.
 * Based on the previously determined Minsky type, now check subclasses:
 *
 * Hedge borrowers
 * MINSKY_STATE = 20: Successful
 * MINSKY_STATE = 21: financial crisis state == 1, Unsuccessful hedge borrowers 
 * MINSKY_STATE = 22: illiquidity state == 1, Unsuccessful hedge borrowers
 * MINSKY_STATE = 23: insolvency state == 1, Unsuccessful hedge borrowers
 * 
 * Speculative borrowers
 * MINSKY_STATE = 30: Successful
 * MINSKY_STATE = 31: financial crisis state == 1, Unsuccessful speculative borrowers 
 * MINSKY_STATE = 32: illiquidity state == 1, Unsuccessful speculative borrowers
 * MINSKY_STATE = 33: insolvency state == 1, Unsuccessful speculative borrowers
 * 
 * Ponzi borrowers
 * MINSKY_STATE = 40: Successful
 * MINSKY_STATE = 41: financial crisis state == 1, Unsuccessful Ponzi borrowers
 * MINSKY_STATE = 42: illiquidity state == 1, Unsuccessful Ponzi borrowers
 * MINSKY_STATE = 43: insolvency state == 1, Unsuccessful Ponzi borrowers
 */
int Firm_set_minsky_state_crisis()
{   
	MINSKY_STATE_20=0; //no problem
	MINSKY_STATE_21=0; //crisis
	MINSKY_STATE_22=0; //illiquidity
	MINSKY_STATE_23=0; //insolvent

	MINSKY_STATE_30=0;
	MINSKY_STATE_31=0;
	MINSKY_STATE_32=0;
	MINSKY_STATE_33=0;

	MINSKY_STATE_40=0;
	MINSKY_STATE_41=0;
	MINSKY_STATE_42=0;
	MINSKY_STATE_43=0;

	if (MINSKY_STATE_2)
	{		
		if (FINANCIAL_CRISIS_STATE==1)
			MINSKY_STATE_21 = 1;
	}

	if (MINSKY_STATE_3)
	{		
		if (FINANCIAL_CRISIS_STATE==1)
			MINSKY_STATE_31 = 1;
	}

	if (MINSKY_STATE_4)
	{
		if (FINANCIAL_CRISIS_STATE==1)
			MINSKY_STATE_41 = 1;
	}

    return 0;
}
/*
 * \fn Firm_set_minsky_state_bankruptcy()
 * \brief Function to set the Minsky type in case of bankruptcy.
 * Note: In these cases, we should reset MINSKY_STATE_*1=0 for financial crisis.
*/
int Firm_set_minsky_state_bankruptcy()
{   
	MINSKY_STATE_20=0;
	//MINSKY_STATE_21=0; //No reset
	MINSKY_STATE_22=0;
	MINSKY_STATE_23=0;

	MINSKY_STATE_30=0;
	//MINSKY_STATE_31=0; //No reset
	MINSKY_STATE_32=0;
	MINSKY_STATE_33=0;

	MINSKY_STATE_40=0;
	//MINSKY_STATE_41=0; //No reset
	MINSKY_STATE_42=0;
	MINSKY_STATE_43=0;

	if (MINSKY_STATE_2)
	{		
		if (BANKRUPTCY_ILLIQUIDITY_STATE==1)
			{MINSKY_STATE_22 = 1; MINSKY_STATE_21=0;}
		else if (BANKRUPTCY_INSOLVENCY_STATE==1)
			{MINSKY_STATE_23 = 1; MINSKY_STATE_21=0;}
		else
			{MINSKY_STATE_20 = 1; MINSKY_STATE_21=0;}
	}

	if (MINSKY_STATE_3)
	{		
		if (BANKRUPTCY_ILLIQUIDITY_STATE==1)
			{MINSKY_STATE_32 = 1; MINSKY_STATE_31=0;}
		else if (BANKRUPTCY_INSOLVENCY_STATE==1)
			{MINSKY_STATE_33 = 1; MINSKY_STATE_31=0;}
		else
			{MINSKY_STATE_30 = 1; MINSKY_STATE_31=0;}
	}

	if (MINSKY_STATE_4)
	{
		if (BANKRUPTCY_ILLIQUIDITY_STATE==1)
			{MINSKY_STATE_42 = 1; MINSKY_STATE_41=0;}
		else if (BANKRUPTCY_INSOLVENCY_STATE==1)
			{MINSKY_STATE_43 = 1; MINSKY_STATE_41=0;}
		else
			{MINSKY_STATE_40 = 1; MINSKY_STATE_41=0;}
	}

    return 0;
}
