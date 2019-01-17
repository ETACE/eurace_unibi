#include "../../header.h"
#include "../../IGFirm_agent_header.h"
#include "../../my_library_header.h"
#include "IGFirm_FM_aux_header.h"

/************IGFirm Role: Financial Management Role ********************************/


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
    //In the future: if we want to include sales_costs
    //SALES_COSTS = 0;

    // compute net earnings
    EARNINGS = CUM_REVENUE - CALC_PRODUCTION_COSTS;

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
        printf("\n\t  EARNINGS: %f",EARNINGS);
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
        fprintf(file1,"\n %d %d %f %f ",DAY,ID,CUM_REVENUE,CALC_PRODUCTION_COSTS);
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
   
   /* 1: complete functionality of the IGFirm -- 0: Exogenous stochastic innovation process  */
 
	//See: IGFirm_FM_aux_functions.c
	IGFirm_compute_dividends_dummy_version();
    
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
    TOTAL_PAYMENTS = TOTAL_DIVIDEND_PAYMENT + TAX_PAYMENT ;

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
        fprintf(file1," TOTAL_DIVIDEND_PAYMENT = %f \n", TOTAL_DIVIDEND_PAYMENT);
        fprintf(file1," TAX_PAYMENT = %f \n",TAX_PAYMENT);   
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

    TOTAL_ASSETS = PAYMENT_ACCOUNT;

    EQUITY = TOTAL_ASSETS;
    
    EQUITY_BALANCE_SHEET = EQUITY;
	TOTAL_DEBT_BALANCE_SHEET = 0;
	PAYMENT_ACCOUNT_BALANCE_SHEET = PAYMENT_ACCOUNT;
    
    IGFIRM_STOCKS_CALENDAR.equity = EQUITY;
    IGFIRM_STOCKS_CALENDAR.total_debt = 0;
    IGFIRM_STOCKS_CALENDAR.total_liabilities = EQUITY;
    IGFIRM_STOCKS_CALENDAR.total_assets = TOTAL_ASSETS;
    IGFIRM_STOCKS_CALENDAR.payment_account = PAYMENT_ACCOUNT;

	DEBT_EQUITY_RATIO = 0.0;
    
   	DEBT_EARNINGS_RATIO = 0.0;
    
    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG)
    { 
        printf("\n\n IGFirm_compute_balance_sheet ID: %d",ID);
        printf("\n\t PAYMENT_ACCOUNT: %f TOTAL_ASSETS:: %f",PAYMENT_ACCOUNT,TOTAL_ASSETS);
        printf("\n\t EQUITY: %f DEBT: %f",EQUITY,0.0);
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
      
        fprintf(file1," TOTAL_ASSETS = %f \n",TOTAL_ASSETS);
        fprintf(file1,"\n");
        fprintf(file1," TOTAL_DEBT = %f \n",0.0);
        fprintf(file1," EQUITY = %f \n",EQUITY);
        fprintf(file1,"\n");
        fprintf(file1," NET_EARNINGS = %f \n",NET_EARNINGS);
        fprintf(file1,"\n");
        fprintf(file1,"\n");
        fclose(file1);
        free(filename);
    }    
            
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
  
    
    //step 3: actual dividend payments
    //Actual bank account updates are send to the bank at end of day when the firm sends its bank_update message 

    //add dividend_per_share_msg(firm_id, current_dividend_per_share) to shareholders (dividend per share)     
	if(CURRENT_SHARES_OUTSTANDING>0) 
	{   
		CURRENT_DIVIDEND_PER_SHARE = TOTAL_DIVIDEND_PAYMENT/CURRENT_SHARES_OUTSTANDING;
		//add_dividend_per_share_message(ID, CURRENT_DIVIDEND_PER_SHARE);
		
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
        fprintf(file1," TOTAL_DIVIDEND_PAYMENT = %f \n",TOTAL_DIVIDEND_PAYMENT);
        fprintf(file1," PAYMENT_ACCOUNT = %f \n", PAYMENT_ACCOUNT);
        fprintf(file1,"\n");
   
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

