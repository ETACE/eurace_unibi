#include "../../header.h"
#include "../../IGFirm_agent_header.h"
#include "../../my_library_header.h"
#include "IGFirm_FM_aux_header.h"

/************IGFirm Role: Financial Management Role ********************************/

/*
 * \fn IGFirm_compute_financial_payments()
 * \brief Function to compute the prior financial commitments of the IGFirm: interests, installments, taxes.
 * 
 * The IGFirm computes the commitments by setting these values:
 *  - total_debt_installment_payment
 *  - total_interest_payments
 */
int IGFirm_compute_financial_payments()
{
	int i;
	//  #ifdef _DEBUG_MODE        
        FILE *file1;
        char *filename;
   // #endif
    
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
			printf("\n\n IGFirm_compute_financial_payments ID: %d Activity day: %d",ID,DAY_OF_MONTH_TO_ACT);
			printf("\n\t interest_rate: %f loan_value: %f",LOANS.array[i].interest_rate,LOANS.array[i].loan_value);
			printf("\n\t TOTAL_INTEREST_PAYMENT: %f TOTAL_DEBT_INSTALLMENT_PAYMENT: %f",TOTAL_INTEREST_PAYMENT,TOTAL_DEBT_INSTALLMENT_PAYMENT);    // }    
		}
		#endif
    }

  if (IGFIRM_FIN_MAN_DEBUG)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/IGFirm_fin_man.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"IGFirm_compute_financial_payments()\n");
        fprintf(file1,"---------------------------------------------------------------------------------\n");
        fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
        fprintf(file1," TOTAL_INTEREST_PAYMENT = %f \n",TOTAL_INTEREST_PAYMENT);
        fprintf(file1," TOTAL_DEBT_INSTALLMENT_PAYMENT = %f \n",TOTAL_DEBT_INSTALLMENT_PAYMENT);
        fprintf(file1,"\n");
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }    
    
    
    
    return 0;
}

/*
 * \fn IGFirm_compute_income_statement()
 * \brief Function to compute the income statement of the IGFirm.
 */
int IGFirm_compute_income_statement() 
{
    //  #ifdef _DEBUG_MODE        
        FILE *file1;
        char *filename;
   // #endif

    // compute net earnings
    EARNINGS = CUM_REVENUE - TOTAL_INTEREST_PAYMENT - CALC_PRODUCTION_COSTS;

    if (EARNINGS>0.0)
        TAX_PAYMENT = TAX_RATE_CORPORATE * EARNINGS;
    else
        TAX_PAYMENT = 0.0;
    
    PREVIOUS_NET_EARNINGS = NET_EARNINGS;
    NET_EARNINGS = EARNINGS - TAX_PAYMENT;

    //continue balance sheet (data pertaining to the period that just ended)
    PREVIOUS_EARNINGS_PER_SHARE = EARNINGS_PER_SHARE;
    
    if (CURRENT_SHARES_OUTSTANDING>0)
        EARNINGS_PER_SHARE = NET_EARNINGS/CURRENT_SHARES_OUTSTANDING;

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG)
    { 
        printf("\n\n IGFirm_compute_income_statement ID: %d",ID);
        printf("\n\t CUM_REVENUE: %f CALC_PRODUCTION_COSTS: %f",CUM_REVENUE,CALC_PRODUCTION_COSTS);
        printf("\n\t TOTAL_INTEREST_PAYMENT: %f EARNINGS: %f",TOTAL_INTEREST_PAYMENT,EARNINGS);
        printf("\n\t TAX_PAYMENT: %f NET_EARNINGS: %f",TAX_PAYMENT,NET_EARNINGS);
        
    }    
    #endif
    
    // #ifdef _DEBUG_MODE    
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
   // #endif
   
   
   if (IGFIRM_FIN_MAN_DEBUG)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/IGFirm_fin_man.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"IGFirm_compute_income_statement() \n");
        fprintf(file1,"---------------------------------------------------------------------------------\n");
        fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
        fprintf(file1," CUM_REVENUE = %f \n",CUM_REVENUE);
        fprintf(file1," TOTAL_INTEREST_PAYMENT = %f \n",TOTAL_INTEREST_PAYMENT);
        fprintf(file1," CALC_PRODUCTION_COSTS = %f \n",CALC_PRODUCTION_COSTS);
        fprintf(file1," EARNINGS = %f \n", EARNINGS);
        fprintf(file1,"\n");
        fprintf(file1," TAX_PAYMENT = %f \n",TAX_PAYMENT);
        fprintf(file1," NET_EARNINGS = %f \n",NET_EARNINGS);
        fprintf(file1,"\n");
        fprintf(file1," CURRENT_SHARES_OUTSTANDING = %d \n",CURRENT_SHARES_OUTSTANDING);
        fprintf(file1," EARNINGS_PER_SHARE = %f \n",EARNINGS_PER_SHARE);
        fprintf(file1,"\n");
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }    
    
    
    return 0;
}

/*
 * \fn IGFirm_compute_dividends()
 * \brief Function to compute the total dividend payout of the IGFirm.
 */
int IGFirm_compute_dividends()
{
    //  #ifdef _DEBUG_MODE        
    FILE *file1;
    char *filename;
   // #endif
   
   /*1: complete functionality of the IGFirm -- 0: Exogenous stochastic innovation process  */

	//See: IGFirm_FM_aux_functions.c
        IGFirm_compute_dividends_real_version();
    
  
    //Pay dividends in IGFirm_execute_financial_payments for both real and dummy versions
    //add_dividend_info_message(ID, TOTAL_DIVIDEND_PAYMENT);

    #ifdef _DEBUG_MODE         
    if (PRINT_DEBUG)
    { 
        printf("\n\n Firm_compute_dividends ID: %d",ID);
        printf("\n\t NET_EARNINGS: %f TOTAL_DIVIDEND_PAYMENT: %f",NET_EARNINGS,TOTAL_DIVIDEND_PAYMENT);
    }
    #endif
    
    if (IGFIRM_FIN_MAN_DEBUG)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/IGFirm_fin_man.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"IGFirm_compute_dividends() \n");
        fprintf(file1,"---------------------------------------------------------------------------------\n");
        fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
        fprintf(file1," EARNINGS_PER_SHARE = %f \n",EARNINGS_PER_SHARE);
        fprintf(file1," PREVIOUS_EARNINGS_PER_SHARE = %f \n",PREVIOUS_EARNINGS_PER_SHARE);
        fprintf(file1," CURRENT_SHARES_OUTSTANDING = %d \n", CURRENT_SHARES_OUTSTANDING);
        fprintf(file1," PREVIOUS_SHARES_OUTSTANDING = %d \n",PREVIOUS_SHARES_OUTSTANDING);
        fprintf(file1," TOTAL_DIVIDEND_PAYMENT = %f \n",TOTAL_DIVIDEND_PAYMENT);
        fprintf(file1,"\n");
        fprintf(file1," CURRENT_DIVIDEND_PER_SHARE = %f \n",CURRENT_DIVIDEND_PER_SHARE);
        fprintf(file1," CURRENT_DIVIDEND_PER_EARNINGS = %f \n",CURRENT_DIVIDEND_PER_EARNINGS);
        fprintf(file1,"\n");
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }    
    
    
    return 0;
}

/*
 * \fn IGFirm_compute_total_financial_payments()
 * \brief Function to compute the total financial payments of the IGFirm: interest, installments, taxes, production costs, dividends.
 * 
 *  - total_interest_payment
 *  - total_debt_installment_payment
 *  - total_dividend_payment
 *  - tax_payment
 *  - production_costs
 */
int IGFirm_compute_total_financial_payments()
{
	//  #ifdef _DEBUG_MODE        
        FILE *file1;
        char *filename;
   // #endif

    //This variable is not used anywhere: it is the sum of financial_liquidity_needs and production_liquidity_needs
    //but excluding the tax_payments. The tax_payments do not need to be financed since we assume they can always be paid out of earnings. 
    TOTAL_PAYMENTS = TOTAL_INTEREST_PAYMENT + TOTAL_DEBT_INSTALLMENT_PAYMENT
            + TOTAL_DIVIDEND_PAYMENT + TAX_PAYMENT + CALC_PRODUCTION_COSTS;

    #ifdef _DEBUG_MODE         
    if (PRINT_DEBUG)
    { 
        printf("\n\n IGFirm_compute_total_financial_payments ID: %d",ID);
        printf("\n\t TOTAL_PAYMENTS: %f",TOTAL_PAYMENTS);
        
    }    
    #endif
    
    
    if (IGFIRM_FIN_MAN_DEBUG)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/IGFirm_fin_man.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"IGFirm_compute_total_financial_payments() \n");
        fprintf(file1,"---------------------------------------------------------------------------------\n");
        fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
        fprintf(file1," TOTAL_INTEREST_PAYMENT = %f \n",TOTAL_INTEREST_PAYMENT);
        fprintf(file1," TOTAL_DEBT_INSTALLMENT_PAYMENT = %f \n",TOTAL_DEBT_INSTALLMENT_PAYMENT);
        fprintf(file1," TOTAL_DIVIDEND_PAYMENT = %f \n", TOTAL_DIVIDEND_PAYMENT);
        fprintf(file1," TAX_PAYMENT = %f \n",TAX_PAYMENT);
        fprintf(file1," CALC_PRODUCTION_COSTS = %f \n",CALC_PRODUCTION_COSTS);
        fprintf(file1," TOTAL_PAYMENTS = %f \n",TOTAL_PAYMENTS);
        fprintf(file1,"\n");
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }    
    
            
    return 0;
}

/*
 * \fn IGFirm_compute_balance_sheet()
 * \brief Function to compute the balance sheet of the IGFirm.
 * We compute these values:
 *  - total_value_capital_stock
 *  - total_value_inventory_stock
 *  - total_assets
 *  - equity
 */
int IGFirm_compute_balance_sheet()
{

	//  #ifdef _DEBUG_MODE        
        FILE *file1;
        char *filename;
   // #endif
   
    //compute the equity of the firm
    //TOTAL_ASSETS=
    //+ PAYMENT_ACCOUNT: remaining cash holdings of the firm
    //+ TOTAL_VALUE_CAPITAL_STOCK: estimated value of the capital stock (this is determined in the capital goods market role)
    //+ TOTAL_VALUE_LOCAL_INVENTORY: value of all the local inventory stocks held at the malls        

    //TOTAL_VALUE_LOCAL_INVENTORY: estimated value of local inventory stocks at current mall prices
    //We loop over the malls and sum the value of all local inventory stocks

    TOTAL_VALUE_LOCAL_INVENTORY=0.0;
    TOTAL_VALUE_LOCAL_INVENTORY= CAPITAL_GOOD_STORE*CAPITAL_GOOD_PRICE;
    //TOTAL_UNITS_LOCAL_INVENTORY = CAPITAL_GOOD_STORE;
   
    TOTAL_ASSETS = PAYMENT_ACCOUNT + TOTAL_VALUE_CAPITAL_STOCK
					+ TOTAL_VALUE_LOCAL_INVENTORY;

    EQUITY = TOTAL_ASSETS - TOTAL_DEBT;
    
    EQUITY_BALANCE_SHEET = EQUITY;
	TOTAL_DEBT_BALANCE_SHEET = TOTAL_DEBT;
	PAYMENT_ACCOUNT_BALANCE_SHEET = PAYMENT_ACCOUNT;
    TOTAL_VALUE_LOCAL_INVENTORY_BALANCE_SHEET =TOTAL_VALUE_LOCAL_INVENTORY;
    
    IGFIRM_STOCKS_CALENDAR.equity = EQUITY;
    IGFIRM_STOCKS_CALENDAR.total_debt = TOTAL_DEBT;
    IGFIRM_STOCKS_CALENDAR.total_liabilities = TOTAL_DEBT+EQUITY;
    IGFIRM_STOCKS_CALENDAR.total_assets = TOTAL_ASSETS;
    IGFIRM_STOCKS_CALENDAR.payment_account = PAYMENT_ACCOUNT;
    IGFIRM_STOCKS_CALENDAR.total_value_capital_stock = TOTAL_VALUE_CAPITAL_STOCK;
    IGFIRM_STOCKS_CALENDAR.total_value_local_inventory = TOTAL_VALUE_LOCAL_INVENTORY;
    

    if (EQUITY>0.0)
        DEBT_EQUITY_RATIO = TOTAL_DEBT/EQUITY;
    else DEBT_EQUITY_RATIO = 0.0;
    
    if(NET_EARNINGS>0.0)
        DEBT_EARNINGS_RATIO = TOTAL_DEBT/NET_EARNINGS;
    else DEBT_EARNINGS_RATIO = 0.0;
    
    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG)
    { 
        printf("\n\n IGFirm_compute_balance_sheet ID: %d",ID);
        printf("\n\t PAYMENT_ACCOUNT: %f TOTAL_VALUE_CAPITAL_STOCK: %f",PAYMENT_ACCOUNT,TOTAL_VALUE_CAPITAL_STOCK);
        printf("\n\t TOTAL_VALUE_LOCAL_INVENTORY: %f TOTAL_ASSETS: %f",TOTAL_VALUE_LOCAL_INVENTORY,TOTAL_ASSETS);
        printf("\n\t EQUITY: %f DEBT: %f",EQUITY,TOTAL_DEBT);
    }   
    #endif
   
     
    if (IGFIRM_FIN_MAN_DEBUG)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/IGFirm_fin_man.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"IGFirm_compute_balance_sheet() \n");
        fprintf(file1,"---------------------------------------------------------------------------------\n");
        fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
        fprintf(file1," PAYMENT_ACCOUNT = %f \n",PAYMENT_ACCOUNT);
        fprintf(file1," TOTAL_VALUE_CAPITAL_STOCK = %f \n",TOTAL_VALUE_CAPITAL_STOCK);
        fprintf(file1," TOTAL_VALUE_LOCAL_INVENTORY = %f \n", TOTAL_VALUE_LOCAL_INVENTORY);
        fprintf(file1," TOTAL_ASSETS = %f \n",TOTAL_ASSETS);
        fprintf(file1,"\n");
        fprintf(file1," TOTAL_DEBT = %f \n",TOTAL_DEBT);
        fprintf(file1," EQUITY = %f \n",EQUITY);
        fprintf(file1,"\n");
        fprintf(file1," NET_EARNINGS = %f \n",NET_EARNINGS);
        fprintf(file1," DEBT_EARNINGS_RATIO = %f \n",DEBT_EARNINGS_RATIO);
        fprintf(file1,"\n");
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }    
            
    return 0;
}

/*
 * \fn IGFirm_compute_total_liquidity_needs()
 * \brief Function to compute the total liquidity needs for executing payments.
 * The values computed in this function:
 *  - financial_liquidity_needs: to finance prior commitments + dividend payment
 *  - production_liquidity_needs: to finance production costs
 * The payout policy can be subject to revision if it turns out to be insupportable by the obtained financial resources.
 */
int IGFirm_compute_total_liquidity_needs()
{

	//  #ifdef _DEBUG_MODE        
        FILE *file1;
        char *filename;
   // #endif
	
	//step 12B: set production and payout financial_needs
    PRODUCTION_LIQUIDITY_NEEDS = PLANNED_PRODUCTION_COSTS;
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
        //printf("Firm_financial_needs, External financing: case 1.");
        EXTERNAL_FINANCIAL_NEEDS = 0.0;
    }
    else
    {
        //external financing needed
        EXTERNAL_FINANCIAL_NEEDS = TOTAL_FINANCIAL_NEEDS - PAYMENT_ACCOUNT;
    }

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG)
    {
        printf("\n\n IGFirm_compute_total_liquidity_needs ID: %d",ID);
        printf("\n\t PRODUCTION_LIQUIDITY_NEEDS %f",PRODUCTION_LIQUIDITY_NEEDS);
        printf("\n\t TOTAL_DEBT_INSTALLMENT_PAYMENT %f TOTAL_INTEREST_PAYMENT %f",TOTAL_DEBT_INSTALLMENT_PAYMENT, TOTAL_INTEREST_PAYMENT);
        printf("\n\t TAX_PAYMENT %f FINANCIAL_LIQUIDITY_NEEDS %f",TAX_PAYMENT, FINANCIAL_LIQUIDITY_NEEDS);
        printf("\n\t TOTAL_DIVIDEND_PAYMENT %f TOTAL_FINANCIAL_NEEDS %f",TOTAL_DIVIDEND_PAYMENT,TOTAL_FINANCIAL_NEEDS);    
        printf("\n\t PAYMENT_ACCOUNT %f EXTERNAL_FINANCIAL_NEEDS %f",PAYMENT_ACCOUNT,EXTERNAL_FINANCIAL_NEEDS);
        
    }
    #endif    
    
     if (IGFIRM_FIN_MAN_DEBUG)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/IGFirm_fin_man.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"IGFirm_compute_total_liquidity_needs() \n");
        fprintf(file1,"---------------------------------------------------------------------------------\n");
        fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
        fprintf(file1," PLANNED_PRODUCTION_COSTS = %f \n",PLANNED_PRODUCTION_COSTS);
        fprintf(file1," PRODUCTION_LIQUIDITY_NEEDS = %f \n",PRODUCTION_LIQUIDITY_NEEDS);
        fprintf(file1,"\n");
        fprintf(file1," TOTAL_INTEREST_PAYMENT = %f \n", TOTAL_INTEREST_PAYMENT);
        fprintf(file1," TOTAL_DEBT_INSTALLMENT_PAYMENT = %f \n", TOTAL_DEBT_INSTALLMENT_PAYMENT);
        fprintf(file1," TAX_PAYMENT = %f \n",TAX_PAYMENT);
        fprintf(file1," FINANCIAL_LIQUIDITY_NEEDS = %f \n",FINANCIAL_LIQUIDITY_NEEDS);
        fprintf(file1,"\n");
        fprintf(file1," TOTAL_DIVIDEND_PAYMENT = %f \n",TOTAL_DIVIDEND_PAYMENT);
        fprintf(file1," TOTAL_FINANCIAL_NEEDS = %f \n",TOTAL_FINANCIAL_NEEDS);
        fprintf(file1,"\n");
        fprintf(file1," PAYMENT_ACCOUNT = %f \n",PAYMENT_ACCOUNT);
        fprintf(file1," EXTERNAL_FINANCIAL_NEEDS = %f \n",EXTERNAL_FINANCIAL_NEEDS);
        fprintf(file1,"\n");
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }  

	return 0;
}

/*
 * \fn IGFirm_check_financial_and_bankruptcy_state()
 * \brief Function that checks the balance sheet and sets flags for the bankruptcy- or financial crisis state.
 */
int IGFirm_check_financial_and_bankruptcy_state()
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
        }
       
    }

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG)
    {
        printf("\n Firm_check_financial_and_bankruptcy_state ID: %d",ID);
        printf("\n\t BANKRUPTCY_ILLIQUIDITY_STATE: %d FINANCIAL_CRISIS_STATE: %d",BANKRUPTCY_ILLIQUIDITY_STATE,FINANCIAL_CRISIS_STATE);
    }
    #endif
        
    return 0;
}

/*
 * \fn IGFirm_set_bankruptcy_illiquidity()
 * \brief Function to set the type of bankruptcy to illiquidity, set the active flag to 0,
 *  start the bankruptcy idle counter, and then go to end_IGFirm state.
 */
int IGFirm_set_bankruptcy_illiquidity()
{
    FILE *file1;
    char *filename;
    
    //Set active flag to 0
    ACTIVE=0;
	AGE =-1;

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
        printf("\n\n IGFirm_set_bankruptcy_illiquidity: IT %d ID %d", DAY, ID);
        printf("\n\t ACTIVE: %d BANKRUPTCY_IDLE_COUNTER: %d Workers: %d",ACTIVE,BANKRUPTCY_IDLE_COUNTER, EMPLOYEES.size);
        printf("\n\t BANKRUPTCY_INSOLVENCY_STATE: %d BANKRUPTCY_ILLIQUIDITY_STATE: %d\n",BANKRUPTCY_INSOLVENCY_STATE,BANKRUPTCY_ILLIQUIDITY_STATE);
    }
    #endif                    
        
    if (PRINT_DEBUG_FILE_EXP1)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/igfirms_bankruptcies.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %d %f %f %f %d %d",DAY,ID,PAYMENT_ACCOUNT,TOTAL_DEBT,EQUITY,-1,REGION_ID);
        fclose(file1);
        free(filename);
    }    

    //Reset immediate variables related to production
    //See: IGFirm_bankruptcy_reset_immediately();
        
    return 0;
}

/*
 * \fn IGFirm_in_financial_crisis()
 * \brief Function to resolve the financial crisis by lowering dividends.
 */
int IGFirm_in_financial_crisis()
{
    double payment_account_after_compulsory_payments;

    //Try to resolve the crisis

    //Recompute dividend
    //Set TOTAL_DIVIDEND_PAYMENT
    payment_account_after_compulsory_payments = PAYMENT_ACCOUNT
            - (TOTAL_INTEREST_PAYMENT + TOTAL_DEBT_INSTALLMENT_PAYMENT
                    + TAX_PAYMENT);

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG)
    {
        printf("\n\n IGFirm_in_financial_crisis ID: %d",ID);
        printf("\n\t former TOTAL_DIVIDEND_PAYMENT: %f",TOTAL_DIVIDEND_PAYMENT);
    }
    #endif
    
    TOTAL_DIVIDEND_PAYMENT = max(0, payment_account_after_compulsory_payments
            - PLANNED_PRODUCTION_COSTS);

    //Set flag if resolved:
    if (PAYMENT_ACCOUNT >= TOTAL_INTEREST_PAYMENT
            + TOTAL_DEBT_INSTALLMENT_PAYMENT + TAX_PAYMENT
            + TOTAL_DIVIDEND_PAYMENT)
    {
        FINANCIAL_CRISIS_STATE=0;
        BANKRUPTCY_STATE=0;
    }
    else
        //If not resolved: payment account remains below total needs
        //Code should never reach this point
         printf("\nERROR in Firm_in_financial_crisis: financial crisis not resolved. \n");

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG)
    {               
        printf("\n\t new TOTAL_DIVIDEND_PAYMENT: %f",TOTAL_DIVIDEND_PAYMENT);
        printf("\n\t new FINANCIAL_CRISIS_STATE: %d BANKRUPTCY_STATE: %d",FINANCIAL_CRISIS_STATE,BANKRUPTCY_STATE);
        
    }
    #endif
    
     return 0;
}

/*
 * \fn IGFirm_not_in_bankruptcy()
 * \brief Idle function to transit from state IGFirm_bankruptcy_checked to state IGFirm_checks_financial_crisis.
 */
int IGFirm_not_in_bankruptcy()
{   
     #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG) printf("\n\n IGFirm_not_in_bankruptcy");
    #endif
        
    return 0;
}

/*
 * \fn IGFirm_execute_financial_payments()
 * \brief Function to execute financial payments:
 *  - tax_payment
 *  - total_debt_installment_payment
 *  - total_interest_payments
 *  - total_dividend_payment
 * All payments are subtracted from the payment account.
 * After this, all that is left over on the payment account can be used to pay for factor inputs for production.
 */
int IGFirm_execute_financial_payments()
{

    //No bankruptcy
    /*char * filename="";
    FILE * file1=NULL;*/
    int i;
    double temp_interest=0.0;
    double temp_installment_amount =0.0;
    
    
    
    //  #ifdef _DEBUG_MODE        
        FILE *file1;
        char *filename;
   // #endif
   
   if (IGFIRM_FIN_MAN_DEBUG)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/IGFirm_fin_man.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"IGFirm_execute_financial_payments() \n");
        fprintf(file1,"---------------------------------------------------------------------------------\n");
        fprintf(file1," DAY %d \t ID %d \n",DAY,ID);
        fprintf(file1," PAYMENT_ACCOUNT = %f \n",PAYMENT_ACCOUNT);
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }  
    
    //step 1: actual tax_payment to government
    add_tax_payment_message(GOV_ID, TAX_PAYMENT);
    PAYMENT_ACCOUNT -= TAX_PAYMENT;
    TAX_PAYMENT_IN_CALENDAR_MONTH = TAX_PAYMENT;
    IGFIRM_OUTFLOWS_CALENDAR.tax_payment = TAX_PAYMENT;

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
    if (PRINT_DEBUG)
    {
        printf("\n IGFirm_execute_financial_payments ID: %d",ID);
        printf("\n\t (before) PAYMENT_ACCOUNT: %f TOTAL_DEBT: %f",PAYMENT_ACCOUNT,TOTAL_DEBT);
    }
    #endif
    
    TOTAL_DEBT=0.0;
    for (i=LOANS.size-1; i>-1; i--)
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
            //printf("\n Loan item %d: nr_periods_before_repayment=%d\n", i, LOANS.array[i].nr_periods_before_repayment);

            LOANS.array[i].nr_periods_before_repayment -= 1;

            //decrease the residual_var of the loan with the var_per_installment:
            LOANS.array[i].residual_var -= LOANS.array[i].var_per_installment;
           
            //pay interest            
            temp_interest=(LOANS.array[i].interest_rate/12.0)*LOANS.array[i].loan_value;
            PAYMENT_ACCOUNT -= temp_interest;
    
            //decrease payment_account with the installment payment
            PAYMENT_ACCOUNT -= LOANS.array[i].installment_amount;
    
            //decrease the value of the loan with the debt_installment_payment:
            LOANS.array[i].loan_value -= LOANS.array[i].installment_amount;

            //Add loan_value to the current total debt
            TOTAL_DEBT += LOANS.array[i].loan_value;
            //printf("\n Loan item %d: adding debt value =%2.2f\n", i, LOANS.array[i].loan_value);
            //printf("\n TOTAL_DEBT=%2.2f\n", TOTAL_DEBT);
            
            //printf("Now subtracted debt_installment_payment from loan_value: %f (new value:%f).\n", LOANS.array[i].debt_installment_payment, LOANS.array[i].loan_value);

            #ifdef _DEBUG_MODE
            if (PRINT_DEBUG)
            {
                printf("\n\t Repayment LOAN ID: %d of %d",i, LOANS.size);
                printf("\n\t Installment_amount: %f interest_amount: %f remaining loan_value: %f remaining periods: %d",LOANS.array[i].installment_amount,temp_interest,LOANS.array[i].loan_value, LOANS.array[i].nr_periods_before_repayment);
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
    
            //add_installment_message(bank_id, installment_amount, interest_amount, var_per_installment)
            add_installment_message(LOANS.array[i].bank_id,
                    LOANS.array[i].installment_amount, temp_interest,
                    LOANS.array[i].var_per_installment); 
                    
             TOTAL_INTEREST_PAYMENT_IN_CALENDAR_MONTH += temp_interest;
			TOTAL_DEBT_INSTALLMENT_PAYMENT_IN_CALENDAR_MONTH += LOANS.array[i].installment_amount;
			IGFIRM_OUTFLOWS_CALENDAR.total_interest_payment += temp_interest;
			IGFIRM_OUTFLOWS_CALENDAR.total_debt_installment_payment += LOANS.array[i].installment_amount;       
        }
        //If nr_periods_before_maturity==CONST_INSTALLMENT_PERIODS+1:
        //* decrease with 1
        //* add value to total debt
        else if (LOANS.array[i].nr_periods_before_repayment==CONST_INSTALLMENT_PERIODS+1)
        {
            //printf("\n Loan item %d: nr_periods_before_repayment=%d\n", i, LOANS.array[i].nr_periods_before_repayment);

            LOANS.array[i].nr_periods_before_repayment -= 1;
            
            //Add loan_value to the current total debt
            TOTAL_DEBT += LOANS.array[i].loan_value;
            //printf("\n Loan item %d: adding debt value =%2.2f\n", i, LOANS.array[i].loan_value);
            //printf("\n TOTAL_DEBT=%2.2f\n", TOTAL_DEBT);
	    
    	    #ifdef _DEBUG_MODE
            if (PRINT_DEBUG)
            {
                printf("\n\t Fresh LOAN ID: %d of %d",i, LOANS.size);
                printf("\n\t Installment_amount: %f interest_amount: %f remaining loan_value: %f remaining periods: %d",LOANS.array[i].installment_amount,temp_interest,LOANS.array[i].loan_value, LOANS.array[i].nr_periods_before_repayment);
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
            //printf("\n Loan item %d: nr_periods_before_repayment=%d\n", i, LOANS.array[i].nr_periods_before_repayment);
            remove_debt_item(&LOANS, i);

    	    #ifdef _DEBUG_MODE
            if (PRINT_DEBUG)
            {
                printf("\n\t Remove LOAN ID: %d of %d",i, LOANS.size);
            }
            #endif
	}
	
	    #ifdef _DEBUG_MODE
        if (PRINT_DEBUG)
        {
             printf("\n\t (after) PAYMENT_ACCOUNT: %f TOTAL_DEBT: %f",PAYMENT_ACCOUNT,TOTAL_DEBT);
        }
        #endif

    }
    
    //step 3: actual dividend payments
    //Actual bank account updates are send to the bank at end of day when the firm sends its bank_update message 

    //add dividend_per_share_msg(firm_id, current_dividend_per_share) to shareholders (dividend per share)     
    if(CURRENT_SHARES_OUTSTANDING>0) 
   {   
	CURRENT_DIVIDEND_PER_SHARE = TOTAL_DIVIDEND_PAYMENT/CURRENT_SHARES_OUTSTANDING;
	
	TOTAL_DIVIDEND_PAYMENT_IN_CALENDAR_MONTH =TOTAL_DIVIDEND_PAYMENT;
	IGFIRM_OUTFLOWS_CALENDAR.total_dividend_payment = TOTAL_DIVIDEND_PAYMENT;
	IGFIRM_STOCKS_CALENDAR.current_shares_outstanding = CURRENT_SHARES_OUTSTANDING;
   }
   else
   {
	TOTAL_DIVIDEND_PAYMENT_IN_CALENDAR_MONTH = 0.0;
	TOTAL_DIVIDEND_PAYMENT = 0.0;
	IGFIRM_OUTFLOWS_CALENDAR.total_dividend_payment =0.0;
	IGFIRM_STOCKS_CALENDAR.current_shares_outstanding = 0;
   }

    //decrease payment_account with the total_dividend_payment
    PAYMENT_ACCOUNT -= TOTAL_DIVIDEND_PAYMENT;
    
    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG)
    {
	    printf("\n\t TOTAL_DIVIDEND_PAYMENT: %f",TOTAL_DIVIDEND_PAYMENT);
	    printf("\n\t (after) PAYMENT_ACCOUNT: %f",PAYMENT_ACCOUNT);
	    printf("\n\t IGFirm ID %d adds dividend_info_message.\n", ID);
    }
    #endif
    
    //Execute dividend payment
    add_dividend_info_message(ID, TOTAL_DIVIDEND_PAYMENT);

    if (IGFIRM_FIN_MAN_DEBUG)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/IGFirm_fin_man.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1," TAX_PAYMENT = %f \n",TAX_PAYMENT);
        fprintf(file1," temp_interest = %f \n",temp_interest);
        fprintf(file1," temp_installment_amount = %f \n",  temp_installment_amount);
        fprintf(file1," TOTAL_DIVIDEND_PAYMENT = %f \n",TOTAL_DIVIDEND_PAYMENT);
        fprintf(file1," PAYMENT_ACCOUNT = %f \n", PAYMENT_ACCOUNT);
        fprintf(file1,"\n");
        fprintf(file1," TOTAL_DEBT = %f \n", TOTAL_DEBT);
        fprintf(file1,"\n");
        fprintf(file1," TOTAL_DIVIDEND_PAYMENT = %f \n",TOTAL_DIVIDEND_PAYMENT);
        fprintf(file1," CURRENT_DIVIDEND_PER_SHARE = %f \n",CURRENT_DIVIDEND_PER_SHARE);
        fprintf(file1," CURRENT_SHARES_OUTSTANDING = %d \n",CURRENT_SHARES_OUTSTANDING);
        fprintf(file1,"\n");
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }  

    return 0;
}

/*
 * \fn IGFirm_set_bankruptcy_insolvency()
 * \brief Function to set the type of bankruptcy to insolvency, set the active flag to 0,
 *  start the bankruptcy idle counter, and then go to end_IGFirm state.
 *  
 */
int IGFirm_set_bankruptcy_insolvency()
{
    FILE *file1;
    char *filename;
    
    //Set active flag to 0
    ACTIVE=0;
	AGE = -1;

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
        printf("\n\n IGFirm_set_bankruptcy_insolvency: IT %d ID %d", DAY, ID);
        printf("\n\t ACTIVE: %d BANKRUPTCY_IDLE_COUNTER: %d Workers: %d",ACTIVE,BANKRUPTCY_IDLE_COUNTER, EMPLOYEES.size);
        printf("\n\t BANKRUPTCY_INSOLVENCY_STATE: %d BANKRUPTCY_ILLIQUIDITY_STATE: %d\n",BANKRUPTCY_INSOLVENCY_STATE,BANKRUPTCY_ILLIQUIDITY_STATE);
    }
    #endif                    

    if (PRINT_DEBUG_FILE_EXP1)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/igfirms_bankruptcies.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %d %f %f %f %d %d",DAY,ID,PAYMENT_ACCOUNT,TOTAL_DEBT,EQUITY,-11,REGION_ID);
        fclose(file1);
        free(filename);
    }    

    //Reset immediate variables related to production
    //See: IGFirm_bankruptcy_reset_immediately();
        
    return 0;
}

/*
 * \fn IGFirm_bankruptcy_insolvency_procedure()
 * \brief Function to process the bankruptcy condition in case of insolvency.
 *  Send a bankruptcy_message to all banks at which the IGFirm has a loan.
 *  Write-off bad debt on the balance sheet of the bank.
 * 19.8.2010 NEW STYLE CODE:
 * - Do not raise new equity by issuing new shares on the AFM, following a target leverage ratio (target debt/target equity).
 */
int IGFirm_bankruptcy_insolvency_procedure()
{
    int i;
    int count_fire, count_fire_msg;

    double target_debt=0.0;
    double bad_debt=0.0;
    double credit_refunded=0.0;
    double writeoff_var=0.0;
    double write_off_ratio=0.0;
  
    #ifdef _DEBUG_MODE  
        char * filename;
        FILE * file1;
    #endif

    //Effect on credit market: write off debt

	//XML Condition:
	if ((BANKRUPTCY_IDLE_COUNTER == CONST_BANKRUPTCY_IDLE_PERIOD - 1)&&(TOTAL_DEBT>1e-7))
	{
		//Renegotiating debt: refunding credit, computing bad debt
		 TOTAL_ASSETS = TOTAL_VALUE_CAPITAL_STOCK + PAYMENT_ACCOUNT;
		//Set the target debt
		target_debt = DEBT_RESCALING_FACTOR*TOTAL_ASSETS;
		write_off_ratio = (TOTAL_DEBT - target_debt)/TOTAL_DEBT;

		for (i=0; i<LOANS.size; i++)
		{
		    //step 1: refunding credit
		    //the credit_refunded is that part of the loan which can be refunded using the payment_account
		    //credit_refunded = (PAYMENT_ACCOUNT/TOTAL_DEBT)*LOANS.array[i].loan_value;
		    //PAYMENT_ACCOUNT -= credit_refunded;
		    //TOTAL_ASSETS -= credit_refunded;
		    credit_refunded = 0;  // credit_refunded is not more used 
		    
		    //step 2: computing bad debt		   
		    bad_debt = write_off_ratio*LOANS.array[i].loan_value;
		    
		    //the credit_remaining is that part of the debt which is not written off
		    //credit_remaining = (1-write_off_ratio)*LOANS.array[i].loan_value

			//Compute value at risk to be written off: writeoff_var is to be subtracted from bank's value at risk (residual value is a wrong name here)
		    writeoff_var = write_off_ratio*LOANS.array[i].var_per_installment * LOANS.array[i].nr_periods_before_repayment;

		    LOANS.array[i].var_per_installment =  (1-write_off_ratio)*LOANS.array[i].var_per_installment;        
		    LOANS.array[i].loan_value =  (1-write_off_ratio)*LOANS.array[i].loan_value;
		    
		    LOANS.array[i].installment_amount = LOANS.array[i].loan_value/LOANS.array[i].nr_periods_before_repayment;

		    //step 3: send the bankruptcy_message to write off part of the debt
		    //add_bankruptcy_message(firm_id, bank_id, bad_debt, credit_refunded, residual_var);
		    
		    add_bankruptcy_message(ID, LOANS.array[i].bank_id, bad_debt, credit_refunded, writeoff_var);        
	   }
	   //Now recompute the balance sheet after the write-off  
	   TOTAL_DEBT = target_debt;
	   EQUITY = TOTAL_ASSETS - TOTAL_DEBT;
	}   

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
    
    for (i=0;i<RESEARCH_EMPLOYEES.size;i++)
    {
            add_firing_message(ID, RESEARCH_EMPLOYEES.array[i].id);
	    count_fire++;
    }
	
    for (i=RESEARCH_EMPLOYEES.size;i>0;i--)
    {
		remove_employee(&RESEARCH_EMPLOYEES, i-1);
		count_fire_msg++;
    }

    //For resetting variables see:
    //IGFirm_bankruptcy_reset_immediately();
	//IGFirm_bankruptcy_reset_delayed();
        
    //Effect on consumption goods market
    //Option 1: all local inventory stock is lost
    //Option 2: send back local inventory stock to factory
    //Option 3: fire-sales at local outlet malls at discount prices
    
    #ifdef _DEBUG_MODE
    if(PRINT_DEBUG_BANKRUPTCY)
    {
        printf("\n\n IT %d IGFirm_bankruptcy_insolvency_procedure: ID %d", DAY, ID);
	printf("\n\t Sent fire msgs: %d Fired workers: %d", count_fire_msg, count_fire);
        printf("\n\t DEBT_RESCALING_FACTOR = %2.2f TARGET_LEVERAGE_RATIO = %2.2f TARGET_LIQUIDITY_RATIO = %2.2f\n", DEBT_RESCALING_FACTOR, TARGET_LEVERAGE_RATIO, TARGET_LIQUIDITY_RATIO);
    }
    #endif

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
        
        fprintf(file1, "\n\n IT %d IGFirm_bankruptcy_insolvency_procedure: ID %d", DAY, ID);
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
 * \fn IGFirm_bankruptcy_illiquidity_procedure()
 * \brief Function to process the bankruptcy condition in case of illiquidity.
 * OLD STYLE CODE:
 *  There is no write-off of bad debt on the balance sheet of the banks.
 *  Raise new equity by a issuing new shares on the AFM according to a target liquidity ratio.
 * 19.8.2010 NEW STYLE CODE:
 * Identical to insolvency procedure:
 * - also write off debt
 * - do not go the AFM to raise new liquidity
 */
int IGFirm_bankruptcy_illiquidity_procedure()
{   
    int i;
    int count_fire, count_fire_msg;

    double target_debt=0.0;
    double bad_debt=0.0;
    double credit_refunded=0.0;
    double writeoff_var=0.0;
    double write_off_ratio=0.0;
  
    #ifdef _DEBUG_MODE  
        char * filename;
        FILE * file1;
    #endif

    //Effect on credit market: write off debt
		#ifdef _DEBUG_MODE
		if(PRINT_DEBUG_BANKRUPTCY)
		{
			if(TOTAL_DEBT<1e-7)
			{
				fprintf(stderr, "\n\n IT %d IGFirm_bankruptcy_insolvency_procedure: ID %d", DAY, ID);
				fprintf(stderr, "\n\t Prevented division by zero in write_off_ratio: TOTAL_DEBT=%f", TOTAL_DEBT);	
			}
		}
		#endif

	//XML Condition:
	if ((BANKRUPTCY_IDLE_COUNTER == CONST_BANKRUPTCY_IDLE_PERIOD - 1)&&(TOTAL_DEBT>1e-7))
	{
		//Renegotiating debt: refunding credit, computing bad debt
		 TOTAL_ASSETS = TOTAL_VALUE_CAPITAL_STOCK + PAYMENT_ACCOUNT;
		//Set the target debt
		target_debt = DEBT_RESCALING_FACTOR*TOTAL_ASSETS;
		write_off_ratio = (TOTAL_DEBT - target_debt)/TOTAL_DEBT;

		for (i=0; i<LOANS.size; i++)
		{
		    //step 1: refunding credit
		    //the credit_refunded is that part of the loan which can be refunded using the payment_account
		    //credit_refunded = (PAYMENT_ACCOUNT/TOTAL_DEBT)*LOANS.array[i].loan_value;
		    //PAYMENT_ACCOUNT -= credit_refunded;
		    //TOTAL_ASSETS -= credit_refunded;
		    credit_refunded = 0;  // credit_refunded is not more used 
		    
		    //step 2: computing bad debt
		   
		    bad_debt = write_off_ratio*LOANS.array[i].loan_value;
		    
		    //the credit_remaining is that part of the debt which is not written off
		    //credit_remaining = (1-write_off_ratio)*LOANS.array[i].loan_value

			//Compute value at risk to be written off: writeoff_var is to be subtracted from bank's value at risk (residual value is a wrong name here)
		    writeoff_var = write_off_ratio*LOANS.array[i].var_per_installment * LOANS.array[i].nr_periods_before_repayment;
		            
		    LOANS.array[i].var_per_installment =  (1-write_off_ratio)*LOANS.array[i].var_per_installment;        
		    LOANS.array[i].loan_value =  (1-write_off_ratio)*LOANS.array[i].loan_value;
		    LOANS.array[i].installment_amount = LOANS.array[i].loan_value/LOANS.array[i].nr_periods_before_repayment;

		    //step 3: send the bankruptcy_message to write off part of the debt
		    //add_bankruptcy_message(firm_id, bank_id, bad_debt, credit_refunded, residual_var);
		    
		    add_bankruptcy_message(ID, LOANS.array[i].bank_id, bad_debt, credit_refunded, writeoff_var);        
		            
	   }

	   //Now recompute the balance sheet after the write-off  
	   TOTAL_DEBT = target_debt;
	   EQUITY = TOTAL_ASSETS - TOTAL_DEBT;
	}   

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
    
    for (i=0;i<RESEARCH_EMPLOYEES.size;i++)
    {
		add_firing_message(ID, RESEARCH_EMPLOYEES.array[i].id);
		count_fire++;
    }

	for (i=RESEARCH_EMPLOYEES.size;i>0;i--)
    {
		remove_employee(&RESEARCH_EMPLOYEES, i-1);
		count_fire_msg++;
    }

    //For resetting variables see:
    //IGFirm_bankruptcy_reset_immediately();
	//IGFirm_bankruptcy_reset_delayed();
        
    //Effect on consumption goods market
    //Option 1: all local inventory stock is lost
    //Option 2: send back local inventory stock to factory
    //Option 3: fire-sales at local outlet malls at discount prices
    
    #ifdef _DEBUG_MODE
    if(PRINT_DEBUG_BANKRUPTCY)
    {
        printf("\n\n IT %d IGFirm_bankruptcy_illiquidity_procedure: ID %d", DAY, ID);
	printf("\n\t Sent fire msgs: %d Fired workers: %d", count_fire, count_fire_msg);
        printf("\n\t DEBT_RESCALING_FACTOR = %2.2f TARGET_LEVERAGE_RATIO = %2.2f TARGET_LIQUIDITY_RATIO = %2.2f\n", DEBT_RESCALING_FACTOR, TARGET_LEVERAGE_RATIO, TARGET_LIQUIDITY_RATIO);
    }
    #endif

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
        
        fprintf(file1, "\n\n IT %d IGFirm_bankruptcy_illiquidity_procedure: ID %d", DAY, ID);
	fprintf(file1, "\n\t Sent fire msgs: %d Fired workers: %d", count_fire_msg, count_fire);
        fprintf(file1, "\n\t DEBT_RESCALING_FACTOR = %2.2f TARGET_LEVERAGE_RATIO = %2.2f TARGET_LIQUIDITY_RATIO = %2.2f\n", DEBT_RESCALING_FACTOR, TARGET_LEVERAGE_RATIO, TARGET_LIQUIDITY_RATIO);
        
        //close the file pointer: FILE * file 
        fclose(file1);
        free(filename);
    }
    #endif

    return 0;
}

/*
 * \fn IGFirm_bankruptcy_idle_counter()
 * \brief Function to decrease the bankruptcy_idle_counter.
 *  Note that a negative count means the financing condition has not been yet satisfied at the end of the default idle period.
 */
int IGFirm_bankruptcy_idle_counter()
{   
	BANKRUPTCY_IDLE_COUNTER -= 1;
          
    return 0;
}

/*
 * \fn IGFirm_reset_bankruptcy_flags()
 * \brief Function to reset the bankruptcy flags.
 */
int IGFirm_reset_bankruptcy_flags()
{
    int i;

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
	printf("\n\n Firm_reset_bankruptcy_flags: IT %d ID %d ", DAY, ID);
        printf("\n\t Before: BANKRUPTCY_IDLE_COUNTER: %d Activation day=%d",BANKRUPTCY_IDLE_COUNTER, DAY_OF_MONTH_TO_ACT);
        
    }
    #endif   

    //Recompute the balance sheet
    TOTAL_ASSETS = PAYMENT_ACCOUNT + TOTAL_VALUE_LOCAL_INVENTORY;
    EQUITY = TOTAL_ASSETS - TOTAL_DEBT;
    
    //Add conditions for resetting the active flag to 1:
	if (BANKRUPTCY_IDLE_COUNTER==0)
    {
        ACTIVE=1;
        BANKRUPTCY_INSOLVENCY_STATE  = 0;
        BANKRUPTCY_ILLIQUIDITY_STATE = 0;
		DAY_OF_MONTH_TO_ACT = ((DAY+1)%MONTH);
    }

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
        printf("\n\t After: BANKRUPTCY_IDLE_COUNTER: %d Activation day=%d",BANKRUPTCY_IDLE_COUNTER, DAY_OF_MONTH_TO_ACT);
        printf("\n\t BANKRUPTCY_INSOLVENCY_STATE: %d BANKRUPTCY_ILLIQUIDITY_STATE: %d",BANKRUPTCY_INSOLVENCY_STATE,BANKRUPTCY_ILLIQUIDITY_STATE);
    }
    #endif   
    
    //Add initialization code for Dynamic arrays of ADTs

    //LAST_NET_PROFITS = 0;				 //DOUBLE_ARRAY
    for (i=0;i<LAST_NET_PROFITS.size;i++)
    {
		LAST_NET_PROFITS.array[i] = 0.0;
    }


    //LAST_CAPITAL_GOOD_DEMAND = 0;				 //DOUBLE_ARRAY
    for (i=0;i<LAST_CAPITAL_GOOD_DEMAND.size;i++)
    {
		LAST_CAPITAL_GOOD_DEMAND.array[i] = 0.0;
    }

    //LAST_CAPITAL_GOOD_SALES = 0;				 //DOUBLE_ARRAY
    for (i=0;i<LAST_CAPITAL_GOOD_SALES.size;i++)
    {
		LAST_CAPITAL_GOOD_SALES.array[i] = 0.0;
    }

    //LAST_PRODUCTION_QUANTITIES = 0;				 //DOUBLE_ARRAY
    for (i=0;i<LAST_PRODUCTION_QUANTITIES.size;i++)
    {
		LAST_PRODUCTION_QUANTITIES.array[i] = 0.0;
    }

    //SET_OF_LENDERS = 0;				 //POTENTIAL_LENDER_ARRAY
    for (i=0;i<SET_OF_LENDERS.size;i++)
    {
		SET_OF_LENDERS.array[i].bank_name = 0;
		SET_OF_LENDERS.array[i].contacted = 0;
    }
    
    return 0;
}

/*
 * \fn IGFirm_bankruptcy_reset_immediately()
 * \brief Function to reset variables immediately.
 */
int IGFirm_bankruptcy_reset_immediately()
{   
    int i; 
    
    //Cancelling local stocks
    TOTAL_VALUE_LOCAL_INVENTORY = 0.0;
    IGFIRM_STOCKS_CALENDAR.total_value_local_inventory = 0.0;
    
	//Balance sheet: Flow variables
		IGFIRM_OUTFLOWS_CALENDAR.labour_costs = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.capital_costs = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.energy_costs = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.tax_payment = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.total_debt_installment_payment = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.total_interest_payment = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.total_dividend_payment = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.value_of_repurchased_shares = 0.0;
		IGFIRM_OUTFLOWS_CALENDAR.total_expenses = 0.0;
		
		IGFIRM_INFLOWS_CALENDAR.cum_revenue = 0.0;
		IGFIRM_INFLOWS_CALENDAR.new_loans = 0.0;
		IGFIRM_INFLOWS_CALENDAR.value_of_issued_shares = 0.0;
		IGFIRM_INFLOWS_CALENDAR.subsidy = 0.0;
		IGFIRM_INFLOWS_CALENDAR.total_income = 0.0;
		IGFIRM_INFLOWS_CALENDAR.net_inflow = 0.0;

	// LIST OF MEMORY VARIABLES FOR IGFIRM AGENT.
	//===========================================
	//ID = 0;				 //INT
	//REGION_ID = 0;				 //INT
	//GOV_ID = 0;				 //INT
	//BANK_ID = 0;				 //INT
	//DAY_OF_MONTH_TO_ACT = 0;				 //INT
	//LAST_DAY_OF_MONTH_TO_ACT = 0;				 //INT
	//PAYMENT_ACCOUNT = 0;				 //DOUBLE
	//PAYMENT_ACCOUNT_BALANCE_SHEET = 0;				 //DOUBLE
	//PARTITION_ID = 0;				 //INT

	//SET_OF_LENDERS = 0;				 //POTENTIAL_LENDER_ARRAY

	NUMBER_OF_BANKS_ASKED = 0;				 //INT
	EBIT = 0;				 //DOUBLE
	//EARNINGS = 0;				 //DOUBLE
	//TAX_RATE_CORPORATE = 0;				 //DOUBLE
	//TAX_RATE_VAT = 0;				 //DOUBLE
	//TAX_PAYMENT = 0;				 //DOUBLE
	//TAX_PAYMENT_IN_CALENDAR_MONTH = 0;				 //DOUBLE
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
	//TOTAL_DEBT_BALANCE_SHEET = 0;				 //DOUBLE
	TOTAL_VALUE_LOCAL_INVENTORY = 0;				 //DOUBLE
	TOTAL_VALUE_LOCAL_INVENTORY_BALANCE_SHEET = 0;				 //DOUBLE
	//TOTAL_UNITS_CAPITAL_STOCK = 0;				 //DOUBLE
	//TOTAL_VALUE_CAPITAL_STOCK = 0;				 //DOUBLE
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
	PRODUCTIVITY = 0;				 //DOUBLE
	CAPITAL_GOOD_PRICE = 0;				 //DOUBLE
	REVENUE_PER_DAY = 0;				 //DOUBLE
	NET_PROFIT = 0;				 //DOUBLE
	CURRENT_SHARES_OUTSTANDING = 0;				 //INT
	ENERGY_PRICE_MARKUP = 0;				 //DOUBLE
	ENERGY_COSTS_PER_DAY = 0;				 //DOUBLE
	EARNINGS_PER_DAY = 0;				 //DOUBLE
	CUM_ENERGY_COSTS = 0;				 //DOUBLE

	//LAST_NET_PROFITS = 0;				 //DOUBLE_ARRAY

	DIVIDEND_PAYMENT = 0;				 //DOUBLE
	DURATION_UNTIL_NEXT_INNOVATION = 0;				 //INT
	INNOVATION_SUCCESS = 0;				 //INT
	ADDITIONAL_PRODUCTIVITY = 0;				 //DOUBLE
	REVENUE_FOR_INNOVATION = 0;				 //DOUBLE
	CAPITAL_GOOD_DEMAND_AFTER_LAST_INNOVATION = 0;				 //DOUBLE
	CAPITAL_GOOD_DEMAND = 0;				 //DOUBLE
	CAPITAL_GOOD_DEMAND_LAST_MONTH = 0;				 //DOUBLE

	//LAST_CAPITAL_GOOD_DEMAND = 0;				 //DOUBLE_ARRAY

	//LAST_CAPITAL_GOOD_SALES = 0;				 //DOUBLE_ARRAY

	NO_ZERO_DEMAND = 0;				 //INT
	CRITICAL_STOCK = 0;				 //DOUBLE
	OUTPUT = 0;				 //DOUBLE
	PLANNED_OUTPUT = 0;				 //DOUBLE
	CAPITAL_GOOD_STORE = 0;				 //DOUBLE
	CAPITAL_GOOD_STORE_AFTER_PRODUCTION = 0;				 //DOUBLE
	CAPITAL_GOOD_STORE_BEFORE_PRODUCTION = 0;				 //DOUBLE
	PLANNED_PRODUCTION_QUANTITY = 0;				 //DOUBLE
	PLANNED_PRODUCTION_COSTS = 0;				 //DOUBLE
	PRODUCTION_COSTS = 0;				 //DOUBLE
	CALC_PRODUCTION_COSTS = 0;				 //DOUBLE
	PRODUCTION_COSTS_LAST_MONTH = 0;				 //DOUBLE
	PRODUCTION_QUANTITY = 0;				 //DOUBLE

	//LAST_PRODUCTION_QUANTITIES = 0;				 //DOUBLE_ARRAY

	LABOUR_COSTS = 0;				 //DOUBLE
	UNIT_COSTS = 0;				 //DOUBLE
	SALES = 0;				 //DOUBLE
	SALES_LAST_MONTH = 0;				 //DOUBLE
	NEW_PRODUCTIVITY = 0;				 //DOUBLE
	NEW_CAPITAL_GOOD_PRICE = 0;				 //DOUBLE
	CUM_REVENUE = 0;				 //DOUBLE
	CUM_REVENUE_LAST_MONTH = 0;				 //DOUBLE
	CUM_NET_PROFITS = 0;				 //DOUBLE
	FINANCIAL_RESOURCES_FOR_PRODUCTION = 0;				 //DOUBLE
	//INNOVATION_SHEME_LOW_PROGRESS = 0;				 //INT_ARRAY
	//INNOVATION_SHEME_MEDIUM_PROGRESS = 0;				 //INT_ARRAY
	//INNOVATION_SHEME_HIGH_PROGRESS = 0;				 //INT_ARRAY
	PERCENT_REVENUE_FOR_INNOVATION = 0;				 //DOUBLE

	//EMPLOYEES = 0;				 //EMPLOYEE_ARRAY
	//RESEARCH_EMPLOYEES = 0;				 //EMPLOYEE_ARRAY

	TECHNOLOGY = 0;				 //DOUBLE
	WAGE_OFFER = 0;				 //DOUBLE
	WAGE_OFFER_FOR_RD = 0;				 //DOUBLE
	BASE_WAGE_OFFER_FOR_RD = 0;				 //DOUBLE
	NO_EMPLOYEES = 0;				 //INT
	NO_RESEARCH_EMPLOYEES = 0;				 //INT
	NO_EMPLOYEES_SKILL_1 = 0;				 //INT
	NO_EMPLOYEES_SKILL_2 = 0;				 //INT
	NO_EMPLOYEES_SKILL_3 = 0;				 //INT
	NO_EMPLOYEES_SKILL_4 = 0;				 //INT
	NO_EMPLOYEES_SKILL_5 = 0;				 //INT
	VACANCIES = 0;				 //INT
	POSTED_VACANCIES = 0;				 //INT
	PRODUCTION_VACANCIES_POSTED = 0;				 //INT
	RESEARCH_VACANCIES = 0;				 //INT
	RESEARCH_VACANCIES_POSTED = 0;				 //INT
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
	RESEARCH_EMPLOYEES_NEEDED = 0;				 //INT
	MEAN_WAGE = 0;				 //DOUBLE
	MEAN_RESEARCH_WAGE = 0;				 //DOUBLE
	MEAN_SPECIFIC_SKILLS = 0;				 //DOUBLE
	MEAN_RESEARCH_SPECIFIC_SKILLS = 0;				 //DOUBLE
	//IGFIRM_BALANCE_SHEET_CALENDAR = 0;				 //IGFIRM_BALANCE_SHEET_ADT
	//IGFIRM_STOCKS_CALENDAR = 0;				 //IGFIRM_STOCKS_ADT
	//IGFIRM_OUTFLOWS_CALENDAR = 0;				 //IGFIRM_OUTFLOWS_ADT
	//IGFIRM_INFLOWS_CALENDAR = 0;				 //IGFIRM_INFLOWS_ADT
	//AGE = 0;				 //INT
	TRANSFER_PAYMENT = 0;				 //DOUBLE
	SUBSIDY_PCT = 0;				 //DOUBLE
	ACTIVE = 0;				 //INT
	//BANKRUPTCY_IDLE_COUNTER = 0;				 //INT
	//BANKRUPTCY_STATE = 0;				 //INT
	//BANKRUPTCY_INSOLVENCY_STATE = 0;				 //INT
	//BANKRUPTCY_ILLIQUIDITY_STATE = 0;				 //INT
	FINANCIAL_CRISIS_STATE = 0;				 //INT
	SUBSIDY_PAYMENT = 0;				 //DOUBLE


	//LAST_NET_PROFITS = 0;				 //DOUBLE_ARRAY
	for (i=0;i<LAST_NET_PROFITS.size;i++)
	{
	    LAST_NET_PROFITS.array[i] = 0.0;
	}

	//LAST_CAPITAL_GOOD_DEMAND = 0;				 //DOUBLE_ARRAY
	for (i=0;i<LAST_CAPITAL_GOOD_DEMAND.size;i++)
	{
	    LAST_CAPITAL_GOOD_DEMAND.array[i] = 0.0;
	}

	//LAST_CAPITAL_GOOD_SALES = 0;				 //DOUBLE_ARRAY
	for (i=0;i<LAST_CAPITAL_GOOD_SALES.size;i++)
	{
	    LAST_CAPITAL_GOOD_SALES.array[i] = 0.0;
	}

	//LAST_PRODUCTION_QUANTITIES = 0;				 //DOUBLE_ARRAY
	for (i=0;i<LAST_PRODUCTION_QUANTITIES.size;i++)
	{
	    LAST_PRODUCTION_QUANTITIES.array[i] = 0.0;
	}

	//SET_OF_LENDERS = 0;				 //POTENTIAL_LENDER_ARRAY
	for (i=0;i<SET_OF_LENDERS.size;i++)
	{
	    SET_OF_LENDERS.array[i].bank_name = 0;
	    SET_OF_LENDERS.array[i].contacted = 0;
	}

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
		printf("\n\n IGFirm_bankruptcy_reset_immediately: IT %d ID %d Activation day=%d", DAY, ID, DAY_OF_MONTH_TO_ACT);
		printf("\n\t PAYMENT_ACCOUNT = %f NET_EARNINGS = %f EQUITY = %f", PAYMENT_ACCOUNT, NET_EARNINGS, EQUITY);
    }
    #endif

    return 0;
}

/*
 * \fn IGFirm_bankruptcy_reset_delayed()
 * \brief Function to reset variables with a delay: until it is 1st of month.
 */
int IGFirm_bankruptcy_reset_delayed()
{   
	NET_EARNINGS					= 0.0;			

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_BANKRUPTCY)
    {
	printf("\n\n IGFirm_bankruptcy_reset_delayed: IT %d ID %d Activation day=%d", DAY, ID, DAY_OF_MONTH_TO_ACT);
	printf("\n\t PAYMENT_ACCOUNT = %f NET_EARNINGS = %f", PAYMENT_ACCOUNT, NET_EARNINGS);
    }
    #endif

    return 0;
}
