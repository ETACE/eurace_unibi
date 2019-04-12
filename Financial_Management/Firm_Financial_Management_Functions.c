#include "../header.h"
#include "../Firm_agent_header.h"
#include "../my_library_header.h"

/************Firm Role: Financial Management Role ********************************/

/*
 * \fn Firm_compute_financial_payments()
 * \brief Function to compute the prior financial commitments of the firm: interests, installments, taxes.
 * 
 * The firm computes the commitments by setting these values:
 *  - total_debt_installment_payment
 *  - total_interest_payments
 */
int Firm_compute_financial_payments()
{
    int i;
    
    //double PAYMENT_ACCOUNT            : account out of which payments are made

    //double_array LOANS                : dynamic array of structs with each struct a loan_item
    //struct debt_item
    //int bank_id                       : bank at which the loan was obtained
    //double loan_value                 : total value of the loan remaining
    //double interest_rate              : interest for this loan
    //double interest_payment           : interest to be paid this period
    //double debt_installment_payment   : installment payment per period
    //int nr_periods_before_maturity    : nr of periods to go before the loan has to be fully repaid

    TOTAL_INTEREST_PAYMENT=0.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT=0.0;

    for (i=0; i<LOANS.size; i++)
    {
        if(LOANS.array[i].loan_value < 0.0)
        printf("\n ERROR in function Firm_compute_financial_payments: loan_value is NEGATIVE: %f.\n", LOANS.array[i].loan_value);

        //step 1: compute total interest payments
        TOTAL_INTEREST_PAYMENT += (LOANS.array[i].interest_rate/12.0) * LOANS.array[i].loan_value;
                
        //step 2: compute total debt installment payments
        TOTAL_DEBT_INSTALLMENT_PAYMENT += LOANS.array[i].installment_amount;
        
		#ifdef _DEBUG_MODE    
		if (PRINT_DEBUG)
		{ 
			
			printf("\n\n Firm_compute_financial_payments ID: %d Activity day: %d",ID,DAY_OF_MONTH_TO_ACT);
			printf("\n\t interest_rate: %f loan_value: %f",LOANS.array[i].interest_rate,LOANS.array[i].loan_value);
			printf("\n\t TOTAL_INTEREST_PAYMENT: %f TOTAL_DEBT_INSTALLMENT_PAYMENT: %f",TOTAL_INTEREST_PAYMENT,TOTAL_DEBT_INSTALLMENT_PAYMENT);    // }    
					
		}
		#endif
    }

    
    return 0;
}

/*
 * \fn Firm_compute_income_statement()
 * \brief Function to compute the income statement of the firm.
 */
int Firm_compute_income_statement()
{
    //  #ifdef _DEBUG_MODE        
        FILE *file1;
        char *filename;
   // #endif

	double d = 1-FLAME_environment_variable_ecb_interest_rate_markdown;
	double i = FLAME_environment_variable_ecb_interest_rate;

    // compute net earnings
    EARNINGS = CUM_REVENUE + (1/12)*PAYMENT_ACCOUNT *d*i - TOTAL_INTEREST_PAYMENT - CALC_PRODUCTION_COSTS - LABOUR_COSTS_INNOVATION;

	// For testing the goodness of the test market estimations
	EXPECTED_OUTPUT_IN_PREVIOUS_MONTH=EXPECTED_OUTPUT_IN_CURRENT_MONTH;
	EXPECTED_PROFIT_IN_PREVIOUS_MONTH=EXPECTED_PROFIT_IN_CURRENT_MONTH;
	EXPECTED_LABOR_COSTS_IN_PREVIOUS_MONTH = EXPECTED_LABOR_COSTS_IN_CURRENT_MONTH;
	EXPECTED_CAPITAL_COSTS_IN_PREVIOUS_MONTH= EXPECTED_CAPITAL_COSTS_IN_CURRENT_MONTH;
	EXPECTED_INTERESTS_IN_PREVIOUS_MONTH = EXPECTED_INTERESTS_IN_CURRENT_MONTH;
	EXPECTED_WAGE_IN_PREVIOUS_MONTH=EXPECTED_WAGE_IN_CURRENT_MONTH;
	EXPECTED_MEAN_SPECIFIC_SKILLS_IN_PREVIOUS_MONTH =EXPECTED_MEAN_SPECIFIC_SKILLS_IN_CURRENT_MONTH ;
	EXPECTED_AVERAGE_PRODUCTIVITY_IN_PREVIOUS_MONTH = EXPECTED_AVERAGE_PRODUCTIVITY_IN_CURRENT_MONTH ;
	EXPECTED_INVESTMENT_NOMINAL_IN_PREVIOUS_MONTH =EXPECTED_INVESTMENT_NOMINAL_IN_CURRENT_MONTH;
	EXPECTED_ACTUAL_SOLD_QUANTITY_IN_PREVIOUS_MONTH= EXPECTED_ACTUAL_SOLD_QUANTITY_IN_CURRENT_MONTH;


	CUM_EARNINGS_LAST_R_D_PROJECT+= EARNINGS*CHANGE_DUE_TO_LAST_INNOVATION;


    if (EARNINGS>0.0)
        TAX_PAYMENT = TAX_RATE_CORPORATE * EARNINGS;
    else
        TAX_PAYMENT = 0.0;
    
    PREVIOUS_NET_EARNINGS = NET_EARNINGS;
    NET_EARNINGS = EARNINGS - TAX_PAYMENT;

	//AVG 4 month earnings: used in dividend rule
	if(EARNINGS_HISTORY.size>4)
		remove_double(&EARNINGS_HISTORY,0);
	add_double(&EARNINGS_HISTORY,NET_EARNINGS);


    //continue balance sheet (data pertaining to the period that just ended)
    PREVIOUS_EARNINGS_PER_SHARE = EARNINGS_PER_SHARE;
    if (CURRENT_SHARES_OUTSTANDING>0)
        EARNINGS_PER_SHARE = NET_EARNINGS/CURRENT_SHARES_OUTSTANDING;

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_FINMAN)
    { 
		if(ID==ID_DEBUG_PROBE)
		{
		    printf("\n\n Firm_compute_income_statement ID: %d",ID);
		    printf("\n\t CUM_REVENUE: %f CALC_PRODUCTION_COSTS: %f",CUM_REVENUE,CALC_PRODUCTION_COSTS);
		    printf("\n\t TOTAL_INTEREST_PAYMENT: %f EARNINGS: %f",TOTAL_INTEREST_PAYMENT,EARNINGS);
		    printf("\n\t TAX_PAYMENT: %f NET_EARNINGS: %f",TAX_PAYMENT,NET_EARNINGS);
	    }
    }    
    #endif
    
	#ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_FILE_EXP1)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/firms_income_statement.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %d %f %f %f",DAY,ID,CUM_REVENUE,CALC_PRODUCTION_COSTS,TOTAL_INTEREST_PAYMENT);
        fprintf(file1," %f %f %f %d",EARNINGS,TAX_PAYMENT,NET_EARNINGS,REGION_ID);
        fclose(file1);
        free(filename);
    }    
	#endif
    
    return 0;
}

/*
 * \fn Firm_compute_dividends()
 * \brief Function to compute the total dividend payout of the firm.
 */
int Firm_compute_dividends()
{

	int i;


	/*1. Compute average revenues of last half year*/

	int size = LAST_REVENUES.size;
	int mos = min(6,size);

	double average_revenue = 0.0;
	for(i=0; i<mos; i++)
	{
		average_revenue += LAST_REVENUES.array[size-i-1];

	}
	
	if(mos!=0)
	{
		average_revenue = average_revenue/mos;
	}

	//5.11.2012: new rules uses smoothed earnings; fixes too high payout due to fluctuating earnings

		double sum=0.0;
		double average_net_earnings=0.0;

		for(i=0; i<EARNINGS_HISTORY.size; i++)
			sum += EARNINGS_HISTORY.array[i];
		
		if(EARNINGS_HISTORY.size != 0)
			average_net_earnings = sum/EARNINGS_HISTORY.size;

	/*2. determine dividend ratio*/

	//option 1: total dividend payment a fixed ratio of net earnings
	//	EXCEPTION: 100% dividends if payment account > threshold*average_revenue
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_FINMAN)
    { 
		printf("\n Firm financial managmt: average_revenue %f",average_revenue);
    }    
    #endif

	FLAG_FULL_DIVIDEND =0;

	// Payment account smaller than threshold AND avg_revenue positive
	// or:  avg_revenue negative
	if ( ((PAYMENT_ACCOUNT < CONST_DIVIDEND_TRESHOLD_FULL_PAYOUT*average_revenue && average_revenue>1e-6) || average_revenue< 1e-6 ) )
	{
		TOTAL_DIVIDEND_PAYMENT = CONST_DIVIDEND_EARNINGS_RATIO * max(average_net_earnings,0);

		#ifdef _DEBUG_MODE    
		if (PRINT_DEBUG_FINMAN)
		{ 
			printf("Case 1: below threshold DIVIDEND %f = %2.2f * average_net_earnings  %f\n [PAYMENT_ACCOUNT %f < %2.2f *average_revenue %f or average_revenue=0]\n",TOTAL_DIVIDEND_PAYMENT,CONST_DIVIDEND_EARNINGS_RATIO , average_net_earnings, PAYMENT_ACCOUNT, CONST_DIVIDEND_TRESHOLD_FULL_PAYOUT, average_revenue);
		}    
		#endif
		

	}else
	{
		//5.11.2012: new rule uses smoothed earnings; fixes too high payout due to fluctuating earnings
		// Payment account larger than threshold AND avg_revenue positive
		// if ((PAYMENT_ACCOUNT > CONST_DIVIDEND_TRESHOLD_FULL_PAYOUT*average_revenue && average_revenue>1e-6)

		TOTAL_DIVIDEND_PAYMENT =  max(average_net_earnings,0);
		FLAG_FULL_DIVIDEND =1;

		#ifdef _DEBUG_MODE    
		if (PRINT_DEBUG_FINMAN)
		{ 
			printf("Case 2: above threshold DIVIDEND %f = 1.0 * average_net_earnings  %f\n [PAYMENT_ACCOUNT %f > %2.2f *average_revenue %f & average_revenue>0]\n",TOTAL_DIVIDEND_PAYMENT, average_net_earnings, PAYMENT_ACCOUNT, CONST_DIVIDEND_TRESHOLD_FULL_PAYOUT, average_revenue);
		}    
		#endif
	}
    
    //Continue with computation of ratios
    PREVIOUS_DIVIDEND_PER_SHARE = CURRENT_DIVIDEND_PER_SHARE;
    
    if (CURRENT_SHARES_OUTSTANDING>0)
        CURRENT_DIVIDEND_PER_SHARE = TOTAL_DIVIDEND_PAYMENT/CURRENT_SHARES_OUTSTANDING;
    else {
    	CURRENT_DIVIDEND_PER_SHARE = 0.0;
    	TOTAL_DIVIDEND_PAYMENT = 0.0;
    }
    
    PREVIOUS_DIVIDEND_PER_EARNINGS = CURRENT_DIVIDEND_PER_EARNINGS;
    
    if (NET_EARNINGS>0.0)
        CURRENT_DIVIDEND_PER_EARNINGS = TOTAL_DIVIDEND_PAYMENT/NET_EARNINGS;
    else
        CURRENT_DIVIDEND_PER_EARNINGS = 0.0;

    #ifdef _DEBUG_MODE         
    if (PRINT_DEBUG_FINMAN)
    { 
		if(ID==ID_DEBUG_PROBE)
		{
			printf("\n\n Firm_compute_dividends ID: %d",ID);
			printf("\n\t NET_EARNINGS: %f TOTAL_DIVIDEND_PAYMENT: %f",NET_EARNINGS,TOTAL_DIVIDEND_PAYMENT);
		}
    }
    #endif
    
    return 0;
}

/*
 * \fn Firm_compute_total_financial_payments()
 * \brief Function to compute the total financial payments of the firm: interest, installments, taxes, production costs, dividends.
 * 
 *  - total_interest_payment
 *  - total_debt_installment_payment
 *  - total_dividend_payment
 *  - tax_payment
 *  - production_costs
 */
int Firm_compute_total_financial_payments()
{
    //This variable is not used anywhere: it is the sum of financial_liquidity_needs and production_liquidity_needs
    //but excluding the tax_payments. The tax_payments do not need to be financed since we assume they can always be paid out of earnings. 

	TOTAL_PAYMENTS = TOTAL_INTEREST_PAYMENT + TOTAL_DEBT_INSTALLMENT_PAYMENT
            + TOTAL_DIVIDEND_PAYMENT + TAX_PAYMENT + PRODUCTION_COSTS;

    #ifdef _DEBUG_MODE         
    if (PRINT_DEBUG_FINMAN)
    { 
		if(ID==ID_DEBUG_PROBE)
		{
        	printf("\n\n Firm_compute_total_financial_payments ID: %d",ID);
        	printf("\n\t TOTAL_PAYMENTS: %f",TOTAL_PAYMENTS);
        } 
    }    
    #endif
            
    return 0;
}

/*
 * \fn Firm_compute_balance_sheet()
 * \brief Function to compute the balance sheet of the firm.
 * We compute these values:
 *  - total_value_capital_stock
 *  - total_value_inventory_stock
 *  - total_assets
 *  - equity
 */
int Firm_compute_balance_sheet()
{
    int i;

      
    //compute the equity of the firm
    //TOTAL_ASSETS=
    //+ PAYMENT_ACCOUNT: remaining cash holdings of the firm
    //+ TOTAL_VALUE_CAPITAL_STOCK: estimated value of the capital stock (this is determined in the capital goods market role)
    //+ TOTAL_VALUE_LOCAL_INVENTORY: value of all the local inventory stocks held at the malls        

    //TOTAL_VALUE_LOCAL_INVENTORY: estimated value of local inventory stocks at current mall prices
    //We loop over the malls and sum the value of all local inventory stocks

    TOTAL_VALUE_LOCAL_INVENTORY=0.0;
    for (i=0; i<CURRENT_MALL_STOCKS.size; i++)
    {
        TOTAL_VALUE_LOCAL_INVENTORY += CURRENT_PRICE_INDEX*CURRENT_MALL_STOCKS.array[i].current_stock;
    }

    TOTAL_ASSETS = PAYMENT_ACCOUNT + TOTAL_VALUE_CAPITAL_STOCK
            + TOTAL_VALUE_LOCAL_INVENTORY;

    EQUITY = TOTAL_ASSETS - TOTAL_DEBT;
    
	EQUITY_BALANCE_SHEET = EQUITY;
	TOTAL_DEBT_BALANCE_SHEET = TOTAL_DEBT;
	PAYMENT_ACCOUNT_BALANCE_SHEET = PAYMENT_ACCOUNT;
    TOTAL_VALUE_CAPITAL_STOCK_BALANCE_SHEET = TOTAL_VALUE_CAPITAL_STOCK;
    TOTAL_VALUE_LOCAL_INVENTORY_BALANCE_SHEET =TOTAL_VALUE_LOCAL_INVENTORY;
    
    FIRM_STOCKS_CALENDAR.equity = EQUITY;
    FIRM_STOCKS_CALENDAR.total_debt = TOTAL_DEBT;
    FIRM_STOCKS_CALENDAR.total_liabilities = TOTAL_DEBT+EQUITY;
    FIRM_STOCKS_CALENDAR.total_assets = TOTAL_ASSETS;
    FIRM_STOCKS_CALENDAR.payment_account = PAYMENT_ACCOUNT;
    FIRM_STOCKS_CALENDAR.total_value_capital_stock = TOTAL_VALUE_CAPITAL_STOCK;
    FIRM_STOCKS_CALENDAR.total_value_local_inventory = TOTAL_VALUE_LOCAL_INVENTORY;
    
    

    if (EQUITY>0.0)
        DEBT_EQUITY_RATIO = TOTAL_DEBT/EQUITY;
    else DEBT_EQUITY_RATIO = 0.0;
    
    if(NET_EARNINGS>0.0)
        DEBT_EARNINGS_RATIO = TOTAL_DEBT/NET_EARNINGS;
    else DEBT_EARNINGS_RATIO = 0.0;

    if (TOTAL_ASSETS>0.0 && ACTIVE==1)
        EQUITY_ASSET_RATIO = EQUITY/TOTAL_ASSETS;
    else EQUITY_ASSET_RATIO = 0.0;

	//profit-asset-ratio
    if (TOTAL_ASSETS>0.0 && ACTIVE==1)
        PROFIT_ASSET_RATIO = NET_EARNINGS/TOTAL_ASSETS;
    else PROFIT_ASSET_RATIO = 0.0;

	//sales-asset-ratio
    if (TOTAL_ASSETS>0.0 && ACTIVE==1)
        SALES_ASSET_RATIO = CUM_REVENUE/TOTAL_ASSETS;
    else SALES_ASSET_RATIO = 0.0;

	//investment-asset-ratio
    if (TOTAL_ASSETS>0.0 && ACTIVE==1)
        INVESTMENT_ASSET_RATIO = CAPITAL_COSTS/TOTAL_ASSETS;
    else INVESTMENT_ASSET_RATIO = 0.0;


    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FINMAN)
    { 
		if(ID==ID_DEBUG_PROBE)
		{
        	printf("\n\n Firm_compute_balance_sheet ID: %d",ID);
        	printf("\n\t PAYMENT_ACCOUNT: %f TOTAL_VALUE_CAPITAL_STOCK: %f",PAYMENT_ACCOUNT,TOTAL_VALUE_CAPITAL_STOCK);
        	printf("\n\t TOTAL_VALUE_LOCAL_INVENTORY: %f TOTAL_ASSETS: %f",TOTAL_VALUE_LOCAL_INVENTORY,TOTAL_ASSETS);
        	printf("\n\t EQUITY: %f DEBT: %f",EQUITY,TOTAL_DEBT);
		}    
	}   
    #endif
                                                          
    return 0;
}

/*
 * \fn Firm_compute_total_liquidity_needs()
 * \brief Function to compute the total liquidity needs for executing payments.
 * The values computed in this function:
 *  - financial_liquidity_needs: to finance prior commitments + dividend payment
 *  - production_liquidity_needs: to finance production costs
 * The payout policy can be subject to revision if it turns out to be insupportable by the obtained financial resources.
 */
int Firm_compute_total_liquidity_needs()
{
    //step 12B: set production and payout financial_needs
    PRODUCTION_LIQUIDITY_NEEDS = PLANNED_EXPENDITURES_PRODUCTION_INNOVATION;
    FINANCIAL_LIQUIDITY_NEEDS = TOTAL_INTEREST_PAYMENT
            + TOTAL_DEBT_INSTALLMENT_PAYMENT + TAX_PAYMENT;

    //step 12C:
    //Check if additional external financial needs are required for total financial needs (direct payable and delayed payable)    
    TOTAL_FINANCIAL_NEEDS = PRODUCTION_LIQUIDITY_NEEDS
            + FINANCIAL_LIQUIDITY_NEEDS + TOTAL_DIVIDEND_PAYMENT;

    //step 12D:
    //Check if external financing is needed

    //CASE 1: No external financing needed
    if (PAYMENT_ACCOUNT >= TOTAL_FINANCIAL_NEEDS)
    {
        EXTERNAL_FINANCIAL_NEEDS = 0.0;
    }
    else
    {
        //external financing needed
        EXTERNAL_FINANCIAL_NEEDS = TOTAL_FINANCIAL_NEEDS - PAYMENT_ACCOUNT;
    }

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FINMAN)
    {
		if(ID==ID_DEBUG_PROBE)
		{
        	printf("\n\n Firm_compute_total_liquidity_needs ID: %d",ID);
        	printf("\n\t PRODUCTION_LIQUIDITY_NEEDS %f",PRODUCTION_LIQUIDITY_NEEDS);
        	printf("\n\t TOTAL_DEBT_INSTALLMENT_PAYMENT %f TOTAL_INTEREST_PAYMENT %f",TOTAL_DEBT_INSTALLMENT_PAYMENT, TOTAL_INTEREST_PAYMENT);
        	printf("\n\t TAX_PAYMENT %f FINANCIAL_LIQUIDITY_NEEDS %f",TAX_PAYMENT, FINANCIAL_LIQUIDITY_NEEDS);
        	printf("\n\t TOTAL_DIVIDEND_PAYMENT %f TOTAL_FINANCIAL_NEEDS %f",TOTAL_DIVIDEND_PAYMENT,TOTAL_FINANCIAL_NEEDS);
        	printf("\n\t EXTERNAL_FINANCIAL_NEEDS %f",EXTERNAL_FINANCIAL_NEEDS);
        	printf("\n\t PAYMENT_ACCOUNT: %f TOTAL_VALUE_CAPITAL_STOCK: %f",PAYMENT_ACCOUNT,TOTAL_VALUE_CAPITAL_STOCK);
        	printf("\n\t TOTAL_VALUE_LOCAL_INVENTORY: %f TOTAL_ASSETS: %f",TOTAL_VALUE_LOCAL_INVENTORY,TOTAL_ASSETS);
        	printf("\n\t EQUITY: %f DEBT: %f",EQUITY,TOTAL_DEBT);

        }
    }
    #endif    
    
    return 0;
}

/*
 * \fn Firm_check_financial_and_bankruptcy_state()
 * \brief Function that checks the balance sheet and sets flags for the bankruptcy- or financial crisis state.
 */
int Firm_check_financial_and_bankruptcy_state()
{

    BANKRUPTCY_ILLIQUIDITY_STATE=0;
    FINANCIAL_CRISIS_STATE=0;

    //Check bankrupcy condition
    if (PAYMENT_ACCOUNT < TOTAL_FINANCIAL_NEEDS)
    {

	

        //Code: check if payment account is also less than financial payments
       if (PAYMENT_ACCOUNT >= TOTAL_INTEREST_PAYMENT
                + TOTAL_DEBT_INSTALLMENT_PAYMENT + TAX_PAYMENT-1e-5)
        {
            //Financial crisis condition
            FINANCIAL_CRISIS_STATE=1;
        }else 
		{
            BANKRUPTCY_ILLIQUIDITY_STATE=1;

			#ifdef _DEBUG_MODE    
		    if (PRINT_DEBUG_FINMAN)
		    {
				if(ID==ID_DEBUG_PROBE)
				{
					printf("\nPAYMENT_ACCOUNT %f TOTAL_INTEREST_PAYMENT %f TOTAL_DEBT_INSTALLMENT_PAYMENT %f  TAX_PAYMENT %f", PAYMENT_ACCOUNT, TOTAL_INTEREST_PAYMENT, TOTAL_DEBT_INSTALLMENT_PAYMENT, TAX_PAYMENT);
				}
			}	
			#endif
	     }
       
    }

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_FINMAN)
    {
		if(ID==ID_DEBUG_PROBE)
		{
        	printf("\n\n IT: %d Firm_check_financial_and_bankruptcy_state ID: %d", DAY, ID);
        	printf("\n\t BANKRUPTCY_ILLIQUIDITY_STATE: %d FINANCIAL_CRISIS_STATE: %d",BANKRUPTCY_ILLIQUIDITY_STATE,FINANCIAL_CRISIS_STATE);
			printf("\n\t TOTAL_FINANCIAL_NEEDS: %f EXTERNAL_FINANCIAL_NEEDS: %f", TOTAL_FINANCIAL_NEEDS, EXTERNAL_FINANCIAL_NEEDS);
		}    
	}
    #endif
        
    return 0;
}

/*
 * \fn Firm_set_bankruptcy_illiquidity()
 * \brief Function to set the type of bankruptcy to illiquidity, set the active flag to 0,
 *  start the bankruptcy idle counter, and then go to end_Firm state.
 */
int Firm_set_bankruptcy_illiquidity()
{
    FILE *file1;
    char *filename;
    
    //Set active flag to 0
    ACTIVE=0;
    INACTIVE=1;

	//Store data at bankruptcy
	AGE_AT_BANKRUPTCY=AGE;
    AGE = -1;
	DEBT_AT_BANKRUPTCY = TOTAL_DEBT;
	EQUITY_AT_BANKRUPTCY = EQUITY;
	NO_EMPLOYEES_AT_BANKRUPTCY = NO_EMPLOYEES;

    //Start the idle counter
    BANKRUPTCY_IDLE_COUNTER = CONST_BANKRUPTCY_IDLE_PERIOD;
    
    //Set type of bankruptcy
    //Type 1: illiquidity
    BANKRUPTCY_INSOLVENCY_STATE  = 0;
    BANKRUPTCY_ILLIQUIDITY_STATE = 1;
    
    //send msg to malls
    add_bankruptcy_illiquidity_message(ID);

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
        printf("\n\n Firm_set_bankruptcy_illiquidity: IT %d ID %d", DAY, ID);
        printf("\n\t ACTIVE: %d BANKRUPTCY_IDLE_COUNTER: %d Workers: %d",ACTIVE,BANKRUPTCY_IDLE_COUNTER, EMPLOYEES.size);
        printf("\n\t BANKRUPTCY_INSOLVENCY_STATE: %d BANKRUPTCY_ILLIQUIDITY_STATE: %d\n",BANKRUPTCY_INSOLVENCY_STATE,BANKRUPTCY_ILLIQUIDITY_STATE);
    }
    #endif
        
    if (PRINT_DEBUG_FILE_EXP1)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/firms_bankruptcies.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %d %f %f %f %d %d",DAY,ID,PAYMENT_ACCOUNT,TOTAL_DEBT,EQUITY,-1,REGION_ID);
        fclose(file1);
        free(filename);
    }    
        
    //Reset immediate variables related to production
    //Run: Firm_bankruptcy_reset_immediately();
    
    return 0;
}

/*
 * \fn Firm_in_financial_crisis()
 * \brief Function to resolve the financial crisis by lowering dividends.
 */
int Firm_in_financial_crisis()
{
    double payment_account_after_compulsory_payments;

    //Try to resolve the crisis

    //Recompute dividend
    //Set TOTAL_DIVIDEND_PAYMENT
    payment_account_after_compulsory_payments = PAYMENT_ACCOUNT
            - (TOTAL_INTEREST_PAYMENT + TOTAL_DEBT_INSTALLMENT_PAYMENT
                    + TAX_PAYMENT);

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_FINMAN)
    {
		if(ID==ID_DEBUG_PROBE)
		{
        	printf("\n\n Firm_in_financial_crisis ID: %d",ID);
        	printf("\n\t former TOTAL_DIVIDEND_PAYMENT: %f",TOTAL_DIVIDEND_PAYMENT);
		}    
	}
    #endif
    
    TOTAL_DIVIDEND_PAYMENT = max(0, payment_account_after_compulsory_payments
            - PLANNED_EXPENDITURES_PRODUCTION_INNOVATION);

    //Set flag if resolved:
    if (PAYMENT_ACCOUNT >= TOTAL_INTEREST_PAYMENT
            + TOTAL_DEBT_INSTALLMENT_PAYMENT + TAX_PAYMENT
            + TOTAL_DIVIDEND_PAYMENT -1e-7)
    {
        FINANCIAL_CRISIS_STATE=0;
        BANKRUPTCY_STATE=0;
    }
    else
        //If not resolved: payment account remains below total needs
        //Code should never reach this point
         printf("\nERROR in Firm_in_financial_crisis: financial crisis not resolved. \n");

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FINMAN)
    {       
		if(ID==ID_DEBUG_PROBE)
		{        
        	printf("\n\t new TOTAL_DIVIDEND_PAYMENT: %f",TOTAL_DIVIDEND_PAYMENT);
        	printf("\n\t new FINANCIAL_CRISIS_STATE: %d BANKRUPTCY_STATE: %d",FINANCIAL_CRISIS_STATE,BANKRUPTCY_STATE);
        }
    }
    #endif
    
     return 0;
}

/*
 * \fn Firm_not_in_bankruptcy()
 * \brief Idle function to transit from state Firm_bankruptcy_checked to state Firm_checks_financial_crisis.
 */
int Firm_not_in_bankruptcy()
{   
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_FINMAN)
	{ 
		if(ID==ID_DEBUG_PROBE)
		{	
			printf("\n\n Firm_not_in_bankruptcy");
		}
	}    
	#endif
        
    return 0;
}

/*
 * \fn Firm_execute_financial_payments()
 * \brief Function to execute financial payments:
 *  - tax_payment
 *  - total_debt_installment_payment
 *  - total_interest_payments
 *  - total_dividend_payment
 * All payments are subtracted from the payment account.
 * After this, all that is left over on the payment account can be used to pay for factor inputs for production.
 */
int Firm_execute_financial_payments()
{

    //No bankruptcy
    char * filename="";
    FILE * file1=NULL;
    int i;
    double temp_interest=0.0;
    
    //step 1: actual tax_payment to government
    add_tax_payment_message(GOV_ID, TAX_PAYMENT);
    PAYMENT_ACCOUNT -= TAX_PAYMENT;
    
    TAX_PAYMENT_IN_CALENDAR_MONTH=TAX_PAYMENT;
    FIRM_OUTFLOWS_CALENDAR.tax_payment = TAX_PAYMENT;

     if (PRINT_DEBUG_FILE_EXP1)
        {                       
            filename = malloc(40*sizeof(char));
            filename[0]=0;
            strcpy(filename, "its/firms_tax_payments.txt");      
            file1 = fopen(filename,"a");
            fprintf(file1,"\n %d %d %f %f %f %d",DAY,ID,EARNINGS,TAX_RATE_CORPORATE,TAX_PAYMENT,REGION_ID);
            fclose(file1);
            free(filename);
        }  
    //step 2: actual interest_payments and installment_payments
    //Sending installment_message to banks at which the firm has a loan 

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FINMAN)
    {
//		if(ID==ID_DEBUG_PROBE)
//		{
        	printf("\n\n IT %d Firm_execute_financial_payments ID: %d",DAY,ID);
        	printf("\n\t (before) PAYMENT_ACCOUNT: %f TOTAL_DEBT: %f",PAYMENT_ACCOUNT,TOTAL_DEBT);
//		}    
	}
    #endif
    
	//Credit default risk: set probability of default
	double multiplicator = 0.10;
	double bankruptcy_prob = 1-exp(-multiplicator*(TOTAL_DEBT/EQUITY));

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FINMAN)
        //if (DAY>TIME_DEBUG_PROBE)
	{
		printf("\n\n IT %d Firm_execute_financial_payments ID: %d",DAY,ID);
        	printf("\n\t bankruptcy_prob: %f TOTAL_DEBT: %f EQUITY: %f",bankruptcy_prob,TOTAL_DEBT, EQUITY);
 
		if(bankruptcy_prob>1.0 || bankruptcy_prob<0.0 || abs(EQUITY)<1e-6)
		{
		  fprintf(stderr,"\n\n Firm_execute_financial_payments ID: %d",ID);
		  fprintf(stderr, "\n\t bankruptcy_prob: %f TOTAL_DEBT: %f EQUITY: %f",bankruptcy_prob,TOTAL_DEBT, EQUITY);
		}    
	}
    #endif

    TOTAL_DEBT=0.0;
    for (i=LOANS.size-1; i>=0; i--)
    {
    
        //decrease payment_account with the interest_payment
        //the if-condition prevents an interest payment in the first period in which the loan is obtained
        // CONST_INSTALLMENT_PERIODS = 24 months by default

        //If 1<=nr_periods_before_maturity<CONST_INSTALLMENT_PERIODS+1:
        //* decrease nr_periods_before_maturity with 1
        //* add loan value to total_debt
        //* decrease residual_var with var_per_installment
        //* decrease loan_value and payment account with installment amount
        //* send message to bank
  	  if ((LOANS.array[i].nr_periods_before_repayment>=1)&&(LOANS.array[i].nr_periods_before_repayment<CONST_INSTALLMENT_PERIODS+1))
		{

            //pay interest            
            temp_interest=(LOANS.array[i].interest_rate/12.0)*LOANS.array[i].loan_value;
            PAYMENT_ACCOUNT -= temp_interest;
    
            //decrease payment_account with the installment payment
            PAYMENT_ACCOUNT -= LOANS.array[i].installment_amount;
    
            //decrease the value of the loan with the debt_installment_payment:
            LOANS.array[i].loan_value -= LOANS.array[i].installment_amount;

            LOANS.array[i].nr_periods_before_repayment -= 1;

			//21.1.2013: Recompute: credit default risk per loan
            LOANS.array[i].residual_var 		= bankruptcy_prob*LOANS.array[i].loan_value;

            //var_per_installment:
			LOANS.array[i].var_per_installment	= LOANS.array[i].residual_var/LOANS.array[i].nr_periods_before_repayment;
			
            
            //Add loan_value to the current total debt
            TOTAL_DEBT += LOANS.array[i].loan_value;

	    #ifdef _DEBUG_MODE
            if (PRINT_DEBUG_FINMAN)
            {

			printf("\n\n\t Repayment LOAN ID: %d of %d", i, LOANS.size);
			printf("\n\t |%8s|%8s|%8s|%8s|%8s|%8s|%8s|", "N","loan","install","interest","tot_var","var_inst", "bank");
			printf("\n\t |%8d|%+5.2f|%+5.2f|%+5.2f|%+5.2f|%+5.2f|%8d|", LOANS.array[i].nr_periods_before_repayment, LOANS.array[i].loan_value, LOANS.array[i].installment_amount, LOANS.array[i].interest_rate, LOANS.array[i].residual_var, LOANS.array[i].var_per_installment, LOANS.array[i].bank_id);

            }
            #endif
            

            //check that the loan value does not go negative:
            if(LOANS.array[i].loan_value < -1e-3)
            {
                printf("\n ERROR in function Firm_execute_financial_payments, line 421:"
                 "loan value = %2.5f,"
                 "installment_amount = %2.5f."
                 "Corrected negative loan value to zero. \n", LOANS.array[i].loan_value, LOANS.array[i].installment_amount);
    
                LOANS.array[i].loan_value =0.0;
            }
    
            //Sending debt_installment_payment_msg to all banks at which the firm has a loan
            //Note: this message is to be separated from the general bank_account_update_message send at the end of the period
            //to the firm's deposit bank (the banks at which the firm has loans is a different one than the bank at which the firm has deposits).
    
		if (LOANS.array[i].nr_periods_before_repayment>0)
		{
			    //add_installment_message(bank_id, installment_amount, interest_amount, var_per_installment)
			    add_installment_message(LOANS.array[i].bank_id, LOANS.array[i].installment_amount, temp_interest, LOANS.array[i].var_per_installment, LOANS.array[i].residual_var);  
		}
		else //if (LOANS.array[i].nr_periods_before_repayment==0)
		{	
			    add_installment_message(LOANS.array[i].bank_id, LOANS.array[i].installment_amount, temp_interest, 0.0, 0.0);  
		}                    

			TOTAL_INTEREST_PAYMENT_IN_CALENDAR_MONTH += temp_interest;
			TOTAL_DEBT_INSTALLMENT_PAYMENT_IN_CALENDAR_MONTH += LOANS.array[i].installment_amount; 
			FIRM_OUTFLOWS_CALENDAR.total_interest_payment += temp_interest;
			FIRM_OUTFLOWS_CALENDAR.total_debt_installment_payment += LOANS.array[i].installment_amount;    
        }
        //If nr_periods_before_maturity==CONST_INSTALLMENT_PERIODS+1:
        //* decrease with 1
        //* add value to total debt
        if (LOANS.array[i].nr_periods_before_repayment==CONST_INSTALLMENT_PERIODS+1)
        {
            LOANS.array[i].nr_periods_before_repayment -= 1;

  	    //21.1.2013: Recompute: credit default risk per loan
            LOANS.array[i].residual_var 		= bankruptcy_prob*LOANS.array[i].loan_value;

            //var_per_installment:
	    LOANS.array[i].var_per_installment	= LOANS.array[i].residual_var/LOANS.array[i].nr_periods_before_repayment;
            
            //Add loan_value to the current total debt
            TOTAL_DEBT += LOANS.array[i].loan_value;
	    
            //add_installment_message(bank_id, installment_amount, interest_amount, var_per_installment)
	    	// for new loans: no installment and interest payment in first period, mesg is for value_at_risk computation of  bank
            add_installment_message(LOANS.array[i].bank_id, 0.0, 0.0, LOANS.array[i].var_per_installment, LOANS.array[i].residual_var);  

    	    #ifdef _DEBUG_MODE
            if (PRINT_DEBUG_FINMAN)
            {

		            printf("\n\t Fresh LOAN ID: %d of %d",i, LOANS.size);
					printf("\n\t |%8s|%8s|%8s|%8s|%8s|%8s|%8s|", "N","loan","install","interest","tot_var","var_inst", "bank");
					printf("\n\t |%8d|%+5.2f|%+5.2f|%+5.2f|%+5.2f|%+5.2f|%8d|", LOANS.array[i].nr_periods_before_repayment, LOANS.array[i].loan_value, LOANS.array[i].installment_amount, LOANS.array[i].interest_rate, LOANS.array[i].residual_var, LOANS.array[i].var_per_installment, LOANS.array[i].bank_id);
			}
            #endif

        }
        //If nr_periods_before_maturity<0:
        //* this should give an error
        else if (LOANS.array[i].nr_periods_before_repayment<0)
        {
            printf("\n Loan item %d: nr_periods_before_repayment=%d\n", i, LOANS.array[i].nr_periods_before_repayment);
            printf("\n Firm: %d, Bank: %d\n", ID, LOANS.array[i].bank_id);
            printf("\n ERROR in function Firm_execute_financial_payments, line 482: nr_periods_before_repayment<0. \n");
        }

        //If nr_periods_before_maturity == 0
        //* remove the loan item.
        if (LOANS.array[i].nr_periods_before_repayment==0)
        {
            remove_debt_item(&LOANS, i);

    	    #ifdef _DEBUG_MODE
            if (PRINT_DEBUG_FINMAN)
            {
				if(ID==ID_DEBUG_PROBE)
				{
                	printf("\n\t Remove LOAN ID: %d of %d",i, LOANS.size);
				}            
			}
            #endif
		}
	
	    #ifdef _DEBUG_MODE
		if (PRINT_DEBUG_FINMAN)
		{
			if(ID==ID_DEBUG_PROBE)
			{
				printf("\n\t (after) PAYMENT_ACCOUNT: %f TOTAL_DEBT: %f",PAYMENT_ACCOUNT,TOTAL_DEBT);
			}            
		}
		#endif
	}
    
    //step 3: actual dividend payments
    //Actual bank account updates are send to the bank at end of day when the firm sends its bank_update message 
       
	if(CURRENT_SHARES_OUTSTANDING>0) 
	{   
		CURRENT_DIVIDEND_PER_SHARE = TOTAL_DIVIDEND_PAYMENT/CURRENT_SHARES_OUTSTANDING;
	
		//add dividend_per_share_msg(firm_id, current_dividend_per_share)
		//add_dividend_per_share_message(ID, CURRENT_DIVIDEND_PER_SHARE);
	
		TOTAL_DIVIDEND_PAYMENT_IN_CALENDAR_MONTH =TOTAL_DIVIDEND_PAYMENT;
		FIRM_OUTFLOWS_CALENDAR.total_dividend_payment = TOTAL_DIVIDEND_PAYMENT;
		FIRM_STOCKS_CALENDAR.current_shares_outstanding = CURRENT_SHARES_OUTSTANDING;
	}
	else
	{
		TOTAL_DIVIDEND_PAYMENT_IN_CALENDAR_MONTH = 0.0;
	   	TOTAL_DIVIDEND_PAYMENT = 0.0;
	   	FIRM_OUTFLOWS_CALENDAR.total_dividend_payment =0.0;
	   	FIRM_STOCKS_CALENDAR.current_shares_outstanding = 0;
	}


    //decrease payment_account with the total_dividend_payment
    PAYMENT_ACCOUNT -= TOTAL_DIVIDEND_PAYMENT;
    
	//Retained earnings
	RETAINED_EARNINGS = max(0,NET_EARNINGS - TOTAL_DIVIDEND_PAYMENT);

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FINMAN)
    {
		if(ID==ID_DEBUG_PROBE)
		{
		printf("\n\t TOTAL_DIVIDEND_PAYMENT: %f",TOTAL_DIVIDEND_PAYMENT);
		printf("\n\t (after) PAYMENT_ACCOUNT: %f",PAYMENT_ACCOUNT);
		printf("\n\t Firm ID %d adds dividend_info_message.\n", ID);
		}    
	}
    #endif

	add_dividend_info_message(ID, TOTAL_DIVIDEND_PAYMENT);    

    return 0;
}

/*
 * \fn Firm_set_bankruptcy_insolvency()
 * \brief Function to set the type of bankruptcy to insolvency, set the active flag to 0,
 *  start the bankruptcy idle counter, and then go to end_Firm state.
 *  
 */
int Firm_set_bankruptcy_insolvency()
{
    FILE *file1;
    char *filename;
    
    //Set active flag to 0
    ACTIVE=0;
	INACTIVE=1;
	
	//Store data at bankruptcy
	AGE_AT_BANKRUPTCY=AGE;
    AGE = -1;
	DEBT_AT_BANKRUPTCY = TOTAL_DEBT;
	EQUITY_AT_BANKRUPTCY = EQUITY;
	NO_EMPLOYEES_AT_BANKRUPTCY = NO_EMPLOYEES;

    //Start the idle counter
    BANKRUPTCY_IDLE_COUNTER = CONST_BANKRUPTCY_IDLE_PERIOD;
    
    //Set type of bankruptcy
    //Type 2: insolvency
    BANKRUPTCY_INSOLVENCY_STATE  = 1;
    BANKRUPTCY_ILLIQUIDITY_STATE = 0;

    //send msg to malls
    add_bankruptcy_insolvency_message(ID);

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
        printf("\n\n Firm_set_bankruptcy_insolvency: IT %d ID %d", DAY, ID);
        printf("\n\t ACTIVE: %d BANKRUPTCY_IDLE_COUNTER: %d Workers: %d",ACTIVE,BANKRUPTCY_IDLE_COUNTER, EMPLOYEES.size);
        printf("\n\t BANKRUPTCY_INSOLVENCY_STATE: %d BANKRUPTCY_ILLIQUIDITY_STATE: %d\n",BANKRUPTCY_INSOLVENCY_STATE,BANKRUPTCY_ILLIQUIDITY_STATE);
    }
    #endif                    

    if (PRINT_DEBUG_FILE_EXP1)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/firms_bankruptcies.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %d %f %f %f %d %d",DAY,ID,PAYMENT_ACCOUNT,TOTAL_DEBT,EQUITY,-11,REGION_ID);
        fclose(file1);
        free(filename);
    }    

    //Reset immediate variables related to production
    //See: Firm_bankruptcy_reset_immediately();

    return 0;
}

/*
 * \fn Firm_bankruptcy_generic_procedure()
 * \brief Function to process the bankruptcy condition in case of insolvency.
 *  Send a fire_message to all employees
 */
int Firm_bankruptcy_generic_procedure()
{
    int i;
    int count_fire, count_fire_msg;
	
    #ifdef _DEBUG_MODE  
        char * filename;
        FILE * file1;
    #endif
    
	//XML Condition: Do once
	if (BANKRUPTCY_IDLE_COUNTER == CONST_BANKRUPTCY_IDLE_PERIOD - 1)
	{

		//Effect on financial market: none (19.8.2010)
		//Shareholders retain their shares.

		//Effect on investment goods market
		//Left-over capital
		
		//Effect on labour market
		//Firing all employees
		count_fire=0; count_fire_msg=0;
		for (i=0;i<EMPLOYEES.size;i++)
		{
			add_firing_message(ID, EMPLOYEES.array[i].id);
			count_fire_msg++;
		}
		for (i=EMPLOYEES.size;i>0;i--)
		{
			remove_employee(&EMPLOYEES, i-1);
			count_fire++;
		}


		for (i=0;i<R_AND_D_EMPLOYEES.size;i++)
		{
			add_firing_message(ID, R_AND_D_EMPLOYEES.array[i].id);
		}
		for (i=R_AND_D_EMPLOYEES.size;i>0;i--)
		{
			remove_employee(&R_AND_D_EMPLOYEES, i-1);
		}
		
		//For resetting variables see:
		//Firm_bankruptcy_reset_immediately();
		//Firm_bankruptcy_reset_delayed();


		//Effect on consumption goods market
		//Option 1: all local inventory stock is lost --> see Firm_bankruptcy_procedures
		//Option 2: send back local inventory stock to factory
		//Option 3: fire-sales at local outlet malls at discount prices


		#ifdef _DEBUG_MODE
		if(PRINT_DEBUG_BANKRUPTCY)
		{
			printf("\n\n IT %d Firm_bankruptcy_generic_procedure: ID %d", DAY, ID);
			printf("\n\t BANKRUPTCY_IDLE_COUNTER %d", BANKRUPTCY_IDLE_COUNTER);

			printf("\n\t Sent fire msgs: %d Fired workers: %d", count_fire_msg, count_fire);
			printf("\n\t DEBT_RESCALING_FACTOR = %2.2f TARGET_LEVERAGE_RATIO = %2.2f TARGET_LIQUIDITY_RATIO = %2.2f\n", DEBT_RESCALING_FACTOR, TARGET_LEVERAGE_RATIO, TARGET_LIQUIDITY_RATIO);
		}
		#endif
	}

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FILE_EXP1)
    {
        //Start an empty string for the filename
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        
        //Concatenate
        strcpy(filename, "debug_bankruptcy.txt");
        //Open a file pointer: FILE * file 
        file1 = fopen(filename,"a");
        
        fprintf(file1, "\n\n IT %d Firm_bankruptcy_generic_procedure: ID %d", DAY, ID);
		fprintf(file1, "\n\t Sent fire msgs: %d Fired workers: %d", count_fire, count_fire_msg);
        fprintf(file1, "\n\t DEBT_RESCALING_FACTOR = %2.2f TARGET_LEVERAGE_RATIO = %2.2f TARGET_LIQUIDITY_RATIO = %2.2f\n", DEBT_RESCALING_FACTOR, TARGET_LEVERAGE_RATIO, TARGET_LIQUIDITY_RATIO);
        
        //close the file pointer: FILE * file 
        fclose(file1);
        free(filename);
    }
    #endif
    
    return 0;
}

/*
 * \fn Firm_bankruptcy_rescale_loans()
 * \brief Function to process the bankruptcy condition in case of illiquidity.
 * OLD STYLE CODE for illiquidity bankruptcy :
 *  There is no write-off of bad debt on the balance sheet of the banks.
 *  Raise new equity by a issuing new shares on the AFM according to a target liquidity ratio.
 * 19.8.2010 NEW STYLE CODE for illiquidity bankruptcy:
 * Identical to insolvency procedure:
 * - write off debt
 * - do not go to the AFM to raise new liquidity
*/
int Firm_bankruptcy_rescale_loans()
{   
    int i;

	double bad_debt=0.0;
    double credit_refunded=0.0;
    double writeoff_var=0.0;
    double write_off_ratio=0.0;
	double nr_rescalings_left; 
	
    #ifdef _DEBUG_MODE  
        __attribute__ ((unused)) char * filename;
        __attribute__ ((unused)) FILE * file1;
    #endif
    
    //Effect on credit market: write off debt
		#ifdef _DEBUG_MODE
		if(PRINT_DEBUG_BANKRUPTCY)
		{
			if(TOTAL_DEBT<1e-7)
			{
				fprintf(stderr, "\n\t Prevented division by zero in write_off_ratio: TOTAL_DEBT=%f", TOTAL_DEBT);	
			}
		}
		#endif

	//Condition: ONCE AT START
	if ((BANKRUPTCY_IDLE_COUNTER == CONST_BANKRUPTCY_IDLE_PERIOD - 1)&&(TOTAL_DEBT>1e-7))
	{
		//Renegotiating debt: refunding credit, computing bad debt
		 TOTAL_ASSETS = TOTAL_VALUE_CAPITAL_STOCK + PAYMENT_ACCOUNT;

		//Insolvency: Set the target debt
		if(BANKRUPTCY_INSOLVENCY_STATE==1)
			TARGET_DEBT = DEBT_RESCALING_FACTOR*TOTAL_ASSETS;

		//Illiquidity: Set the target debt
		FLAG_ILLIQUIDITY_CORRECTION=0;
		if(BANKRUPTCY_ILLIQUIDITY_STATE==1)
		{
			//Default rule
			//TARGET_DEBT = DEBT_RESCALING_FACTOR*TOTAL_DEBT; 

			/* NEW: Liquidity rescaling based on Total_Assets*/
			
			TARGET_DEBT = DEBT_RESCALING_FACTOR*TOTAL_ASSETS;
			if(TARGET_DEBT > TOTAL_DEBT)
			{
				TARGET_DEBT = DEBT_RESCALING_FACTOR*TOTAL_DEBT; //Default rule
				FLAG_ILLIQUIDITY_CORRECTION=1;

				#ifdef _DEBUG_MODE
				if(PRINT_DEBUG_BANKRUPTCY)
				{
			        printf("\n\n IT %d Firm_bankruptcy_rescale_loans: Monthly for ID %d", DAY, ID);
				printf("\n\n Illiquid Firm ID %d: Debt rescaling correction: using TD instead of TA. Cause: TARGET_DEBT > TOTAL_DEBT (%f) > (%f)", ID, DEBT_RESCALING_FACTOR*TOTAL_ASSETS, TOTAL_DEBT);
				}
				#endif
			}
			
		}
	}

	//Condition: each month
	if ((BANKRUPTCY_IDLE_COUNTER%20==0)&&(TOTAL_DEBT>1e-7))
	{

		//No. of months
		nr_rescalings_left = (double)(BANKRUPTCY_IDLE_COUNTER/20);

		//This month
		if(nr_rescalings_left>0)
		{
			write_off_ratio = (1/nr_rescalings_left)*(TOTAL_DEBT - TARGET_DEBT)/TOTAL_DEBT;

		#ifdef _DEBUG_MODE
		if(PRINT_DEBUG_BANKRUPTCY)
		//if (DAY>TIME_DEBUG_PROBE)
		{
		        printf("\n\n IT %d Firm_bankruptcy_rescale_loans: Monthly for ID %d", DAY, ID);

			if(BANKRUPTCY_INSOLVENCY_STATE==1)
			printf("\n\t INSOLVENCY");

			if(BANKRUPTCY_ILLIQUIDITY_STATE==1)
			printf("\n\t ILLIQUIDITY");

			printf("\n\t BANKRUPTCY_IDLE_COUNTER %d", BANKRUPTCY_IDLE_COUNTER);
			printf("\n\t nr_rescalings_left=%f",nr_rescalings_left);
			printf("\n\t |%8s|%8s|%8s|%8s|%8s|", "rescale","asset","debt","trgt","wo ratio");
			printf("\n\t |%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|", DEBT_RESCALING_FACTOR, TOTAL_ASSETS, TOTAL_DEBT, TARGET_DEBT, write_off_ratio);
		}
		#endif

		}

		for (i=0; i<LOANS.size; i++)
		{

			#ifdef _DEBUG_MODE
			if(PRINT_DEBUG_BANKRUPTCY)
			//if (DAY>TIME_DEBUG_PROBE)
			{
				printf("\n\t Loan %d:",i);
				printf("\n\t |%8s|%8s|%8s|%8s|%8s|", "N","loan","install","tot_var","var");
				printf("\n\t |%d|%8.2f|%8.2f|%8.2f|%8.2f|", LOANS.array[i].nr_periods_before_repayment, LOANS.array[i].loan_value, LOANS.array[i].installment_amount, LOANS.array[i].residual_var, LOANS.array[i].var_per_installment);
			}
			#endif

		    //step 1: refunding credit
		    //the credit_refunded is that part of the loan which can be refunded using the payment_account
		    //credit_refunded = (PAYMENT_ACCOUNT/TOTAL_DEBT)*LOANS.array[i].loan_value;
		    //PAYMENT_ACCOUNT -= credit_refunded;
		    //TOTAL_ASSETS -= credit_refunded;
		    credit_refunded = 0;  // No credit is refunded
		    
		    //step 2: computing bad debt		   
		    bad_debt = write_off_ratio*LOANS.array[i].loan_value;
		    
		    //the credit_remaining is that part of the debt which is not written off
		    //credit_remaining = (1-write_off_ratio)*LOANS.array[i].loan_value

			//Compute value at risk to be written off: writeoff_var is to be subtracted from bank's value at risk (residual value is a wrong name here)
		    writeoff_var = write_off_ratio*LOANS.array[i].var_per_installment * LOANS.array[i].nr_periods_before_repayment;

		    LOANS.array[i].residual_var =  (1-write_off_ratio)*LOANS.array[i].residual_var;        
		    LOANS.array[i].var_per_installment =  (1-write_off_ratio)*LOANS.array[i].var_per_installment;        
		    LOANS.array[i].loan_value =  (1-write_off_ratio)*LOANS.array[i].loan_value;
		    
		    LOANS.array[i].installment_amount = LOANS.array[i].loan_value/LOANS.array[i].nr_periods_before_repayment;

		   //Now recompute the balance sheet after the write-off  
		   TOTAL_DEBT -= bad_debt;
		   EQUITY = TOTAL_ASSETS - TOTAL_DEBT;

			#ifdef _DEBUG_MODE
			if(PRINT_DEBUG_BANKRUPTCY)
			//if (DAY>TIME_DEBUG_PROBE)
			{
				printf("\n\t After rescale:");
				printf("\n\t |%8s|%8s|%8s|%8s|%8s|%8s|%8s|%8s|", "loan","install","tot_var","inst_var", "ratio", "woff","bad", "bank");
				printf("\n\t |%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8.2f|%8d|", LOANS.array[i].loan_value, LOANS.array[i].installment_amount, LOANS.array[i].residual_var, LOANS.array[i].var_per_installment, write_off_ratio, writeoff_var, bad_debt, LOANS.array[i].bank_id);
			}
			#endif

		    //step 3: send the bankruptcy_message to write off part of the debt
		    //add_bankruptcy_message(firm_id, bank_id, bad_debt, credit_refunded, residual_var);
		    
		    add_bankruptcy_message(ID, LOANS.array[i].bank_id, bad_debt, credit_refunded, writeoff_var);        
		            
	   }
	}   

    return 0;
}

/*
 * \fn Firm_bankruptcy_idle_counter()
 * \brief Function to decrease the bankruptcy_idle_counter.
 *  Note that a negative count means the financing condition has not been yet satisfied at the end of the default idle period.
 */
int Firm_bankruptcy_idle_counter()
{   

    //Add conditions for resetting the AT_BANKRUPTCY variables:
    if (BANKRUPTCY_IDLE_COUNTER<CONST_BANKRUPTCY_IDLE_PERIOD && DAY%20==1)
    {
		#ifdef _DEBUG_MODE    
		if (PRINT_DEBUG_BANKRUPTCY)
		{
			printf("\n\n Firm_bankruptcy_idle_counter: IT %d ID %d", DAY, ID	);
		    printf("\n\t Before: BANKRUPTCY_IDLE_COUNTER: %d DEBT_AT_BANKRUPTCY=%f",BANKRUPTCY_IDLE_COUNTER, DEBT_AT_BANKRUPTCY);
		}
		#endif   

		DEBT_AT_BANKRUPTCY = 0;
		EQUITY_AT_BANKRUPTCY = 0;
		NO_EMPLOYEES_AT_BANKRUPTCY = 0;
		AGE_AT_BANKRUPTCY = 0;

		#ifdef _DEBUG_MODE    
		if (PRINT_DEBUG_BANKRUPTCY)
		{
		    printf("\n\t After: BANKRUPTCY_IDLE_COUNTER: %d DEBT_AT_BANKRUPTCY=%f",BANKRUPTCY_IDLE_COUNTER, DEBT_AT_BANKRUPTCY);
		}
		#endif   

	}

	//Decrease counter by 1
    BANKRUPTCY_IDLE_COUNTER -= 1;
        
    return 0;
}

/*
 * \fn Firm_reset_bankruptcy_flags()
 * \brief Function to reset the bankruptcy flags.
 */
int Firm_reset_bankruptcy_flags()
{
    int i,j;

   double production_quantity, production_quantity_per_mall;

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
	printf("\n\n Firm_reset_bankruptcy_flags: IT %d ID %d PAYMENT_ACCOUNT %f", DAY, ID, PAYMENT_ACCOUNT);
        printf("\n\t Before: BANKRUPTCY_IDLE_COUNTER: %d Activation day=%d",BANKRUPTCY_IDLE_COUNTER, DAY_OF_MONTH_TO_ACT);
        
    }
    #endif   

	//Recompute the balance sheet
    TOTAL_ASSETS = PAYMENT_ACCOUNT + TOTAL_VALUE_CAPITAL_STOCK + TOTAL_VALUE_LOCAL_INVENTORY;
    EQUITY = TOTAL_ASSETS - TOTAL_DEBT;

    //Add conditions for resetting the active flag to 1:
    if (BANKRUPTCY_IDLE_COUNTER==0)
    {

        ACTIVE=1;
		INACTIVE=0;
		
		
        BANKRUPTCY_INSOLVENCY_STATE  = 0;
        BANKRUPTCY_ILLIQUIDITY_STATE = 0;
		//DAY_OF_MONTH_TO_ACT = ((DAY+1)%MONTH);
		//LAST_DAY_OF_MONTH_TO_ACT = (20+DAY_OF_MONTH_TO_ACT-1)%20;


		DAY_OF_MONTH_TO_ACT = (DAY+5)%MONTH;
		LAST_DAY_OF_MONTH_TO_ACT = (20+DAY_OF_MONTH_TO_ACT-1)%20;
    	DAY_OF_YEAR_MARKET_RESEARCH = (DAY+1)%240;
    }

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
        printf("\n\t After: BANKRUPTCY_IDLE_COUNTER: %d Activation day=%d",BANKRUPTCY_IDLE_COUNTER, DAY_OF_MONTH_TO_ACT);
        printf("\n\t BANKRUPTCY_INSOLVENCY_STATE: %d BANKRUPTCY_ILLIQUIDITY_STATE: %d",BANKRUPTCY_INSOLVENCY_STATE,BANKRUPTCY_ILLIQUIDITY_STATE);
        
    }
    #endif   


    /*Compute initial production quantity after bankcruptcy. Two options: 
	1. This is the feasible output given the capital stock and the average specific skills in firm's region (reported from Eurostat)
	2. Average production quantity of all firms located in its region*/

    //First Option:
    production_quantity = min(AVERAGE_S_SKILL_FROM_EUROSTAT,TECHNOLOGY)*TOTAL_UNITS_CAPITAL_STOCK;	

    // Second option
    //production_quantity = AVERAGE_OUTPUT_FROM_EUROSTAT;
    
    MEAN_SPECIFIC_SKILLS = AVERAGE_S_SKILL_FROM_EUROSTAT;

    /*Set the production quantity per mall*/
	
    production_quantity_per_mall = production_quantity/	MALLS_SALES_STATISTICS.size;
    
    
    //Add initialization code for Dynamic arrays of ADTs
    
    //LINEAR_REGRESSION_ESTIMATORS				 //ESTIMATORS_LINEAR_REGRESSION_ARRAY
    for (i=0;i<LINEAR_REGRESSION_ESTIMATORS.size;i++)
    {
	    //LINEAR_REGRESSION_ESTIMATORS.array[i].mall_id = 0;
	    LINEAR_REGRESSION_ESTIMATORS.array[i].intercept = 0.0;
	    LINEAR_REGRESSION_ESTIMATORS.array[i].regressor = 0.0;
	    LINEAR_REGRESSION_ESTIMATORS.array[i].variance = 0.0;
    }

    //MALLS_SALES_STATISTICS = 0;				 //SALES_STATISTICS_ARRAY
    for (i=0;i<MALLS_SALES_STATISTICS.size;i++)
    {
		//MALLS_SALES_STATISTICS.array[i].mall_id = 0;
		for (j=0;j<MALLS_SALES_STATISTICS.array[i].sales.size;j++)
		{
		   //MALLS_SALES_STATISTICS.array[i].sales.array[j].period = j+1;
			MALLS_SALES_STATISTICS.array[i].sales.array[j].sales = production_quantity_per_mall;
		}
    }

    //SOLD_QUANTITIES = 0;				 //SOLD_QUANTITIES_PER_MALL_ARRAY
    for (i=0;i<SOLD_QUANTITIES.size;i++)
    {
	    //SOLD_QUANTITIES.array[i].mall_id = 0;
	    SOLD_QUANTITIES.array[i].sold_quantity = 0.0;
	    SOLD_QUANTITIES.array[i].stock_empty = 0;
	    SOLD_QUANTITIES.array[i].estimated_demand = 0.0;
    }

    //DELIVERY_VOLUME = 0;				 //DELIVERY_VOLUME_PER_MALL_ARRAY
    for (i=0;i<DELIVERY_VOLUME.size;i++)
    {
	    //DELIVERY_VOLUME.array[i].mall_id = 0;
	    DELIVERY_VOLUME.array[i].quantity = 0.0;
	    DELIVERY_VOLUME.array[i].price = 0.0;
	    DELIVERY_VOLUME.array[i].quality = 0.0;
    }

    //PLANNED_DELIVERY_VOLUME = 0;				 //DELIVERY_VOLUME_PER_MALL_ARRAY
    for (i=0;i<PLANNED_DELIVERY_VOLUME.size;i++)
    {
	    //PLANNED_DELIVERY_VOLUME.array[i].mall_id = 0;
	    PLANNED_DELIVERY_VOLUME.array[i].quantity = 0.0;
	    PLANNED_DELIVERY_VOLUME.array[i].price = 0.0;
	    PLANNED_DELIVERY_VOLUME.array[i].quality = 0.0;
    }

    //CURRENT_MALL_STOCKS = 0;				 //MALL_INFO_ARRAY
    for (i=0;i<CURRENT_MALL_STOCKS.size;i++)
    {
	    //CURRENT_MALL_STOCKS.array[i].mall_id = 0;
	    CURRENT_MALL_STOCKS.array[i].critical_stock = 0.0;
	    CURRENT_MALL_STOCKS.array[i].current_stock = 0.0;
    }

    //LAST_PLANNED_PRODUCTION_QUANTITIES = 0;				 //DOUBLE_ARRAY
    for (i=0;i<LAST_PLANNED_PRODUCTION_QUANTITIES.size;i++)
    {
	LAST_PLANNED_PRODUCTION_QUANTITIES.array[i]= production_quantity ;
    }

    //CAPITAL_FINANCING = 0;				 //FINANCING_CAPITAL_ARRAY
    for (i=0;i<CAPITAL_FINANCING.size;i++)
    {
	    CAPITAL_FINANCING.array[i].financing_per_month = 0.0;
	    CAPITAL_FINANCING.array[i].nr_periods_before_repayment = 0;
    }

    //SET_OF_LENDERS = 0;				 //POTENTIAL_LENDER_ARRAY: should not be reset, since loans remain


    return 0;
}

/*
 * \fn Firm_bankruptcy_reset_immediately()
 * \brief Function to reset variables immediately.
 */
int Firm_bankruptcy_reset_immediately()
{   
    int i,j;


    //Cancelling local stocks
    TOTAL_VALUE_LOCAL_INVENTORY = 0.0;
    FIRM_STOCKS_CALENDAR.total_value_local_inventory = 0.0;

	//Balance sheet: Flow variables
		FIRM_OUTFLOWS_CALENDAR.labour_costs = 0.0;
		FIRM_OUTFLOWS_CALENDAR.capital_costs = 0.0;
		FIRM_OUTFLOWS_CALENDAR.energy_costs = 0.0;
		FIRM_OUTFLOWS_CALENDAR.tax_payment = 0.0;
		FIRM_OUTFLOWS_CALENDAR.total_debt_installment_payment = 0.0;
		FIRM_OUTFLOWS_CALENDAR.total_interest_payment = 0.0;
		FIRM_OUTFLOWS_CALENDAR.total_dividend_payment = 0.0;
		FIRM_OUTFLOWS_CALENDAR.value_of_repurchased_shares = 0.0;
		FIRM_OUTFLOWS_CALENDAR.total_expenses = 0.0;
		
		//FIRM_INFLOWS_CALENDAR.cum_revenue = 0.0;
		FIRM_INFLOWS_CALENDAR.new_loans = 0.0;
		FIRM_INFLOWS_CALENDAR.value_of_issued_shares = 0.0;
		FIRM_INFLOWS_CALENDAR.subsidy = 0.0;
		FIRM_INFLOWS_CALENDAR.total_income = 0.0;
		FIRM_INFLOWS_CALENDAR.net_inflow = 0.0;

	// LIST OF MEMORY VARIABLES FOR FIRM AGENT.
	//===========================================
	//ID = 0;				 //INT
	//REGION_ID = 0;				 //INT
	//GOV_ID = 0;				 //INT
	//DAY_OF_MONTH_TO_ACT = 0;				 //INT
	//LAST_DAY_OF_MONTH_TO_ACT = 0;				 //INT
	//PAYMENT_ACCOUNT = 0;				 //DOUBLE
	//PAYMENT_ACCOUNT_BALANCE_SHEET = 0;				 //DOUBLE
	//BANK_ID = 0;				 //INT
	//PARTITION_ID = 0;				 //INT
	//CPI = 0;				 //DOUBLE
	MEAN_WAGE = 0;
	MEAN_WAGE_R_AND_D =0;				 //DOUBLE
	NEEDED_CAPITAL_STOCK = 0;				 //DOUBLE
	//ACTUAL_CAP_PRICE = 0;				 //DOUBLE
	MEAN_SPECIFIC_SKILLS = 0;				 //DOUBLE
	PLANNED_PRODUCTION_QUANTITY = 0;				 //DOUBLE
	PRODUCTION_QUANTITY = 0;				 //DOUBLE
	PLANNED_OUTPUT = 0;				 //DOUBLE
	OUTPUT = 0;				 //DOUBLE
	UNIT_COSTS = 0;				 //DOUBLE
	TOTAL_SUPPLY = 0;				 //DOUBLE
	PRODUCTION_COSTS = 0;				 //DOUBLE
	REVENUE_PER_DAY = 0;				 //DOUBLE
	VINTAGE_CHOICE_TAKEN=0;	

	//LINEAR_REGRESSION_ESTIMATORS				 //ESTIMATORS_LINEAR_REGRESSION_ARRAY

	//TECHNOLOGICAL_FRONTIER = 0;				 //DOUBLE
	//CUM_REVENUE = 0;				 //DOUBLE

	//MALLS_SALES_STATISTICS = 0;				 //SALES_STATISTICS_ARRAY

	//QUALITY = 0;				 //DOUBLE
	//PRICE = 0;				 //DOUBLE
	PRICE_LAST_MONTH = 0;				 //DOUBLE
	DEMAND_CAPITAL_STOCK = 0;				 //DOUBLE
	PLANNED_PRODUCTION_COSTS = 0;				 //DOUBLE
	PLANNED_EXPENDITURES_PRODUCTION_INNOVATION =0;	
	//ADAPTION_PRODUCTION_VOLUME_DUE_TO_INSUFFICIENT_FINANCES = 0;				 //DOUBLE
	//FRACTION_RESERVED_FOR_DELAYED_PAYMENTS = 0;				 //DOUBLE

	//SOLD_QUANTITIES = 0;				 //SOLD_QUANTITIES_PER_MALL_ARRAY

	TOTAL_SOLD_QUANTITY = 0;				 //DOUBLE
	//CUM_TOTAL_SOLD_QUANTITY = 0;				 //DOUBLE
	//SOLD_QUANTITY_IN_CALENDAR_MONTH = 0;				 //DOUBLE

	//DELIVERY_VOLUME = 0;				 //DELIVERY_VOLUME_PER_MALL_ARRAY

	//PLANNED_DELIVERY_VOLUME = 0;				 //DELIVERY_VOLUME_PER_MALL_ARRAY

	//CURRENT_MALL_STOCKS = 0;				 //MALL_INFO_ARRAY

	//LAST_PLANNED_PRODUCTION_QUANTITIES = 0;				 //DOUBLE_ARRAY

	TOTAL_EXTERNAL_FINANCING_OBTAINED = 0;				 //DOUBLE
	CAPITAL_COSTS = 0;				 //DOUBLE
	LABOUR_COSTS = 0;				 //DOUBLE

	//CAPITAL_FINANCING = 0;				 //FINANCING_CAPITAL_ARRAY

	FINANCIAL_RESOURCES_FOR_PRODUCTION = 0;				 //DOUBLE
	//PLANNED_VALUE_CAPITAL_STOCK = 0;				 //DOUBLE
	TOTAL_UNITS_LOCAL_INVENTORY = 0;				 //DOUBLE
	CALC_CAPITAL_COSTS = 0;				 //DOUBLE
	CALC_PRODUCTION_COSTS = 0;				 //DOUBLE
	FIRM_PRODUCTIVITY = 0;				 //DOUBLE
	FIRM_PRODUCTIVITY_LAST_YEAR = 0;				 //DOUBLE
	FIRM_PRODUCTIVITY_PROGRESS = 0;				 //DOUBLE

	//SET_OF_LENDERS = 0;				 //POTENTIAL_LENDER_ARRAY

	NUMBER_OF_BANKS_ASKED = 0;				 //INT
	EBIT = 0;				 //DOUBLE
	EARNINGS = 0;				 //DOUBLE
	//TAX_RATE_CORPORATE = 0;				 //DOUBLE
	//TAX_RATE_VAT = 0;				 //DOUBLE
	//TAX_PAYMENT = 0;				 //DOUBLE
	TAX_PAYMENT_IN_CALENDAR_MONTH = 0;				 //DOUBLE
	//NET_EARNINGS = 0;				 //DOUBLE
	PREVIOUS_NET_EARNINGS = 0;				 //DOUBLE
	TOTAL_INTEREST_PAYMENT = 0;				 //DOUBLE
	TOTAL_INTEREST_PAYMENT_IN_CALENDAR_MONTH = 0;				 //DOUBLE
	TOTAL_DEBT_INSTALLMENT_PAYMENT = 0;				 //DOUBLE
	TOTAL_DEBT_INSTALLMENT_PAYMENT_IN_CALENDAR_MONTH = 0;				 //DOUBLE
	TOTAL_DIVIDEND_PAYMENT = 0;				 //DOUBLE
	TOTAL_DIVIDEND_PAYMENT_IN_CALENDAR_MONTH = 0;				 //DOUBLE
	CURRENT_SHARE_PRICE = 0;				 //DOUBLE
	PREVIOUS_DIVIDEND_PER_SHARE = 0;				 //DOUBLE
	CURRENT_DIVIDEND_PER_SHARE = 0;				 //DOUBLE
	PREVIOUS_EARNINGS_PER_SHARE = 0;				 //DOUBLE
	CURRENT_EARNINGS_PER_SHARE = 0;				 //DOUBLE
	PREVIOUS_DIVIDEND_PER_EARNINGS = 0;				 //DOUBLE
	CURRENT_DIVIDEND_PER_EARNINGS = 0;				 //DOUBLE
	DEBT_EARNINGS_RATIO = 0;				 //DOUBLE
	DEBT_EQUITY_RATIO = 0;				 //DOUBLE
	PRICE_EARNINGS_RATIO = 0;				 //DOUBLE
	RETAINED_EARNINGS_RATIO = 0;				 //DOUBLE
	EARNINGS_PER_SHARE_RATIO_GROWTH = 0;				 //DOUBLE
	CRITICAL_PRICE_EARNINGS_RATIO = 0;				 //DOUBLE
	CRITICAL_EARNINGS_PER_SHARE_RATIO = 0;				 //DOUBLE
	//LOANS = 0;				 //DEBT_ITEM_ARRAY
	//TOTAL_DEBT = 0;				 //DOUBLE
	TOTAL_DEBT_BALANCE_SHEET = 0;				 //DOUBLE
	TOTAL_VALUE_LOCAL_INVENTORY = 0;				 //DOUBLE
	TOTAL_VALUE_LOCAL_INVENTORY_BALANCE_SHEET = 0;				 //DOUBLE
	//TOTAL_UNITS_CAPITAL_STOCK = 0;				 //DOUBLE
	//TOTAL_VALUE_CAPITAL_STOCK = 0;				 //DOUBLE
	//TOTAL_VALUE_CAPITAL_STOCK_BALANCE_SHEET = 0;				 //DOUBLE
	TOTAL_CAPITAL_DEPRECIATION_VALUE = 0;				 //DOUBLE
	TOTAL_CAPITAL_DEPRECIATION_UNITS = 0;				 //DOUBLE
	//TOTAL_ASSETS = 0;				 //DOUBLE
	//EQUITY = 0;				 //DOUBLE
	//EQUITY_BALANCE_SHEET = 0;				 //DOUBLE
	PRODUCTION_LIQUIDITY_NEEDS = 0;				 //DOUBLE
	FINANCIAL_LIQUIDITY_NEEDS = 0;				 //DOUBLE
	TOTAL_FINANCIAL_NEEDS = 0;				 //DOUBLE
	EXTERNAL_FINANCIAL_NEEDS = 0;				 //DOUBLE
	EARNINGS_PER_SHARE = 0;				 //DOUBLE
	TOTAL_PAYMENTS = 0;				 //DOUBLE
	//PREVIOUS_SHARES_OUTSTANDING = 0;				 //INT
	TOTAL_INCOME = 0;				 //DOUBLE
	TOTAL_LIABILITIES = 0;				 //DOUBLE
	TOTAL_EXPENSES = 0;				 //DOUBLE
	//CURRENT_SHARES_OUTSTANDING = 0;				 //INT

	//EMPLOYEES = 0;				 //EMPLOYEE_ARRAY

	//WAGE_OFFER = 0;				 //DOUBLE
	//TECHNOLOGY = 0;				 //DOUBLE
	NO_EMPLOYEES = 0;
	NO_EMPLOYEES_PRODUCTION = 0;
	NO_EMPLOYEES_INNOVATION = 0;				 //INT
	NO_EMPLOYEES_SKILL_1 = 0;				 //INT
	NO_EMPLOYEES_SKILL_2 = 0;				 //INT
	NO_EMPLOYEES_SKILL_3 = 0;				 //INT
	NO_EMPLOYEES_SKILL_4 = 0;				 //INT
	NO_EMPLOYEES_SKILL_5 = 0;				 //INT
	VACANCIES = 0;				 //INT
	POSTED_VACANCIES = 0;				 //INT	
	AVERAGE_G_SKILL = 0;				 //DOUBLE
	AVERAGE_S_SKILL_OF_1 = 0;				 //DOUBLE
	AVERAGE_S_SKILL_OF_2 = 0;				 //DOUBLE
	AVERAGE_S_SKILL_OF_3 = 0;				 //DOUBLE
	AVERAGE_S_SKILL_OF_4 = 0;				 //DOUBLE
	AVERAGE_S_SKILL_OF_5 = 0;				 //DOUBLE
	WAGE_OFFER_FOR_SKILL_1 = 0;				 //DOUBLE
	WAGE_OFFER_FOR_SKILL_2 = 0;				 //DOUBLE
	WAGE_OFFER_FOR_SKILL_3 = 0;				 //DOUBLE
	WAGE_OFFER_FOR_SKILL_4 = 0;				 //DOUBLE
	WAGE_OFFER_FOR_SKILL_5 = 0;				 //DOUBLE
	EMPLOYEES_NEEDED = 0;				 //INT
	CUM_PERSON_MONTHS=0;
	EMPLOYEES_NEEDED_PRODUCTION=0;
	
	//FIRM_BALANCE_SHEET_CALENDAR = 0;				 //FIRM_BALANCE_SHEET_ADT
	//FIRM_STOCKS_CALENDAR = 0;				 //FIRM_STOCKS_ADT
	//FIRM_OUTFLOWS_CALENDAR = 0;				 //FIRM_OUTFLOWS_ADT
	//FIRM_INFLOWS_CALENDAR = 0;				 //FIRM_INFLOWS_ADT
	//AGE = 0;				 //INT
	TRANSFER_PAYMENT = 0;				 //DOUBLE
	SUBSIDY_PCT = 0;				 //DOUBLE
	ACTIVE = 0;				 //INT
	//INACTIVE=1;
	//AGE_AT_BANKRUPTCY;
    //AGE;
	//DEBT_AT_BANKRUPTCY;
	//EQUITY_AT_BANKRUPTCY;
	//NO_EMPLOYEES_AT_BANKRUPTCY;
	
	//BANKRUPTCY_IDLE_COUNTER = 0;				 //INT
	//BANKRUPTCY_STATE = 0;				 //INT
	//BANKRUPTCY_INSOLVENCY_STATE = 0;				 //INT
	//BANKRUPTCY_ILLIQUIDITY_STATE = 0;				 //INT
	FINANCIAL_CRISIS_STATE = 0;				 //INT
	SUBSIDY_PAYMENT = 0;				 //DOUBLE


	INNOVATION_FLAG = 0;
	//TOTAL_NO_PERIODS_FOR_PRODUCT_DEVELOPMENT = 0;
	INNOVATION_EMPLOYEES_NEEDED = 0;
	PLANNED_QUALITY = 0.0;
	INTERMEDIATE_QUALITY = QUALITY;
	REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT=TOTAL_NO_PERIODS_FOR_PRODUCT_DEVELOPMENT;
	R_AND_D_INVESTMENTS_PER_MONTH=0.0;
	OPTIMAL_EMPLOYEES_NEEDED_INNOVATION=0;
	EMPLOYEES_NEEDED_INNOVATION=0;
	NO_REDUNDANCIES_R_AND_D_EMPLOYEES=0;
	VACANCIES_R_AND_D_EMPLOYEES =0;

	//LINEAR_REGRESSION_ESTIMATORS				 //ESTIMATORS_LINEAR_REGRESSION_ARRAY
	for (i=0;i<LINEAR_REGRESSION_ESTIMATORS.size;i++)
	{
		//LINEAR_REGRESSION_ESTIMATORS.array[i].mall_id = 0;
		LINEAR_REGRESSION_ESTIMATORS.array[i].intercept = 0.0;
		LINEAR_REGRESSION_ESTIMATORS.array[i].regressor = 0.0;
		LINEAR_REGRESSION_ESTIMATORS.array[i].variance = 0.0;
	}

	//MALLS_SALES_STATISTICS = 0;				 //SALES_STATISTICS_ARRAY
	for (i=0;i<MALLS_SALES_STATISTICS.size;i++)
	{
	    //MALLS_SALES_STATISTICS.array[i].mall_id = 0;
	    for (j=0;j<MALLS_SALES_STATISTICS.array[i].sales.size;j++)
	    {
		//MALLS_SALES_STATISTICS.array[i].sales.array[j].period = 0;
		MALLS_SALES_STATISTICS.array[i].sales.array[j].sales = 0;
	    }
	}

	//SOLD_QUANTITIES = 0;				 //SOLD_QUANTITIES_PER_MALL_ARRAY
	for (i=0;i<SOLD_QUANTITIES.size;i++)
	{
		//SOLD_QUANTITIES.array[i].mall_id = 0;
		SOLD_QUANTITIES.array[i].sold_quantity = 0.0;
		SOLD_QUANTITIES.array[i].stock_empty = 0;
		SOLD_QUANTITIES.array[i].estimated_demand = 0.0;
	}

	//DELIVERY_VOLUME = 0;				 //DELIVERY_VOLUME_PER_MALL_ARRAY
	for (i=0;i<DELIVERY_VOLUME.size;i++)
	{
		//DELIVERY_VOLUME.array[i].mall_id = 0;
		DELIVERY_VOLUME.array[i].quantity = 0.0;
		DELIVERY_VOLUME.array[i].price = 0.0;
		DELIVERY_VOLUME.array[i].quality = 0.0;
	}

	//PLANNED_DELIVERY_VOLUME = 0;				 //DELIVERY_VOLUME_PER_MALL_ARRAY
	for (i=0;i<PLANNED_DELIVERY_VOLUME.size;i++)
	{
		//PLANNED_DELIVERY_VOLUME.array[i].mall_id = 0;
		PLANNED_DELIVERY_VOLUME.array[i].quantity = 0.0;
		PLANNED_DELIVERY_VOLUME.array[i].price = 0.0;
		PLANNED_DELIVERY_VOLUME.array[i].quality = 0.0;
	}

	//CURRENT_MALL_STOCKS = 0;				 //MALL_INFO_ARRAY
	for (i=0;i<CURRENT_MALL_STOCKS.size;i++)
	{
		//CURRENT_MALL_STOCKS.array[i].mall_id = 0;
		//CURRENT_MALL_STOCKS.array[i].critical_stock = 0.0;
		CURRENT_MALL_STOCKS.array[i].current_stock = 0.0;
	}

	//LAST_PLANNED_PRODUCTION_QUANTITIES = 0;				 //DOUBLE_ARRAY
	for (i=0;i<LAST_PLANNED_PRODUCTION_QUANTITIES.size;i++)
	{
	    LAST_PLANNED_PRODUCTION_QUANTITIES.array[i]=0.0;
	}

	//CAPITAL_FINANCING = 0;				 //FINANCING_CAPITAL_ARRAY
	for (i=0;i<CAPITAL_FINANCING.size;i++)
	{
		CAPITAL_FINANCING.array[i].financing_per_month = 0.0;
		CAPITAL_FINANCING.array[i].nr_periods_before_repayment = 0;
	}

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
	printf("\n\n Firm_bankruptcy_reset_immediately: IT %d ID %d Activation day=%d", DAY, ID, DAY_OF_MONTH_TO_ACT);
	printf("\n\t PAYMENT_ACCOUNT = %f NET_EARNINGS = %f EQUITY = %f", PAYMENT_ACCOUNT, NET_EARNINGS, EQUITY);
	printf("\n\t BANKRUPTCY_INSOLVENCY_STATE %d BANKRUPTCY_ILLIQUIDITY_STATE %d", BANKRUPTCY_INSOLVENCY_STATE, BANKRUPTCY_ILLIQUIDITY_STATE);
    }
    #endif

    return 0;
}


/*
 * \fn Firm_bankruptcy_reset_delayed()
 * \brief Function to reset variables with a delay: until it is 1st of month.
 */
int Firm_bankruptcy_reset_delayed()
{   
    FIRM_INFLOWS_CALENDAR.cum_revenue	= 0.0;	
    NET_EARNINGS					= 0.0;
    SOLD_QUANTITY_IN_CALENDAR_MONTH	= 0.0;	

    CUM_TOTAL_SOLD_QUANTITY 		= 0.0;	
    CUM_REVENUE 					= 0.0;	  

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
		printf("\n\n Firm_bankruptcy_reset_delayed: IT %d ID %d Activation day=%d", DAY, ID, DAY_OF_MONTH_TO_ACT);
		printf("\n\t PAYMENT_ACCOUNT = %f NET_EARNINGS = %f", PAYMENT_ACCOUNT, NET_EARNINGS);
    }
    #endif

    return 0;
}

