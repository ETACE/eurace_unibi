#include "../header.h"     
#include "../CentralBank_agent_header.h"
#include "../my_library_header.h"

    
    
    /************Central_Bank Role: manage accounts for Governments and commercial banks********************************/
    
int Central_Bank_reset_variables()
{

	ECB_STOCKS_CALENDAR.equity_day_1 = ECB_STOCKS_CALENDAR.equity;
	
	ECB_OUTFLOWS_CALENDAR.gov_bond_purchase = 0.0;
	ECB_OUTFLOWS_CALENDAR.bank_fiat_money = 0.0;
	ECB_OUTFLOWS_CALENDAR.bank_deposits = 0.0;
	ECB_OUTFLOWS_CALENDAR.gov_deposits = 0.0;
	ECB_OUTFLOWS_CALENDAR.dividend_payment = 0.0;
	ECB_OUTFLOWS_CALENDAR.total_expenses = 0.0;
	
	ECB_INFLOWS_CALENDAR.bank_interest = 0.0;
	ECB_INFLOWS_CALENDAR.bank_debt_installment = 0.0;
	ECB_INFLOWS_CALENDAR.gov_interest = 0.0;
	ECB_INFLOWS_CALENDAR.bank_deposits = 0.0;
	ECB_INFLOWS_CALENDAR.gov_deposits = 0.0;
	ECB_INFLOWS_CALENDAR.total_income = 0.0;
	ECB_INFLOWS_CALENDAR.net_inflow = 0.0;

	return 0;
}    
    
    
/** \fn Central_Bank_read_account_update()
 * \brief 
 */

int Central_Bank_monetary_policy()
{
	
    double inflation=0.0;
    double gdp=0.0;
    double unemployment_rate=0.0;
 
    START_EUROSTAT_SEND_MACRODATA_MESSAGE_LOOP
        inflation = eurostat_send_macrodata_message->inflation;
        gdp = eurostat_send_macrodata_message->gdp;
        unemployment_rate = eurostat_send_macrodata_message->unemployment_rate;
    FINISH_EUROSTAT_SEND_MACRODATA_MESSAGE_LOOP 
    
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG)
    {
        printf("\n Central_Bank_monetary_policy ID: %d",ID); 
        printf("\n\t inflation: %f gdp: %f unemployment_rate: %f",inflation,gdp,unemployment_rate);
        printf("\n\t ECB_INTEREST_RATE: %f",ECB_INTEREST_RATE);   
        getchar(); 
    }              
    #endif   

    return 0;
}

int Central_Bank_read_fiat_money_requests()
{

    //Monetization of debt
    //Read the fiat money request from governments, assume ECB is 100% accommodating
    START_REQUEST_FIAT_MONEY_MESSAGE_LOOP
       FIAT_MONEY_GOVS += request_fiat_money_message->nominal_value;
       FIAT_MONEY      += request_fiat_money_message->nominal_value;
    FINISH_REQUEST_FIAT_MONEY_MESSAGE_LOOP
    
    return 0;
}

/** \fn Central_Bank_read_account_update()
 * \brief 
 */
int Central_Bank_read_account_update()
{
	int i,j;
	double a,b;
	double temp_deposit = 0;
	double interest = 0.0;

    #ifdef _DEBUG_MODE
       int bank_mesg_count=0; //debug
       int gov_mesg_count=0; //debug
    #endif
        FILE * file1=NULL;
        char * filename="";
  
    
    ECB_DEPOSITS=0.0;

    //Recomputing fiat_money_banks, adding it later to fiat_money
    FIAT_MONEY -= FIAT_MONEY_BANKS;
    FIAT_MONEY_BANKS = 0.0;

    //record previous value
    a = ECB_STOCKS_CALENDAR.fiat_money_banks;
    ECB_STOCKS_CALENDAR.fiat_money_banks =0.0;

    START_BANK_TO_CENTRAL_BANK_ACCOUNT_UPDATE_MESSAGE_LOOP
        ECB_DEPOSITS += bank_to_central_bank_account_update_message->payment_account;
        
		ECB_STOCKS_CALENDAR.fiat_money_banks +=  bank_to_central_bank_account_update_message->ecb_debt;

        //Search the correct account and update the value    
        for (i=0;i<ACCOUNTS_BANKS.size;i++)
        {       
            if(ACCOUNTS_BANKS.array[i].id == bank_to_central_bank_account_update_message->id)
            {
            	temp_deposit = ACCOUNTS_BANKS.array[i].payment_account;
            
                ACCOUNTS_BANKS.array[i].payment_account = 
                bank_to_central_bank_account_update_message->payment_account;
                
                
                if(temp_deposit >= ACCOUNTS_BANKS.array[i].payment_account)
                {
                 	ECB_OUTFLOWS_CALENDAR.bank_deposits +=
                 	(temp_deposit - ACCOUNTS_BANKS.array[i].payment_account);
                 }
                 else
                 {
                 	ECB_INFLOWS_CALENDAR.bank_deposits +=
                 	(ACCOUNTS_BANKS.array[i].payment_account - temp_deposit);
                 
                 }
            }
        }
        
        #ifdef _DEBUG_MODE
        if(PRINT_DEBUG_CREDIT)
            bank_mesg_count++;        
        #endif

    FINISH_BANK_TO_CENTRAL_BANK_ACCOUNT_UPDATE_MESSAGE_LOOP

    //Check difference between new and old ECB debt to banks: either a net outflow (new loans) or inflow (debt installment)
	b = ECB_STOCKS_CALENDAR.fiat_money_banks - a;
	if(b>0.0)
	{
	    ECB_OUTFLOWS_CALENDAR.bank_fiat_money = b;
	    ECB_INFLOWS_CALENDAR.bank_debt_installment = 0.0;
	    //Add new ECB debt
	    FIAT_MONEY 		+= b;
	    FIAT_MONEY_BANKS 	+= b;
	}
	else
	{
	    ECB_OUTFLOWS_CALENDAR.bank_fiat_money = 0.0;
	    ECB_INFLOWS_CALENDAR.bank_debt_installment = b;
	    //Subtract new ECB debt (b<0.0)
	    FIAT_MONEY 		+= b;
	    FIAT_MONEY_BANKS 	+= b;
	}

    //Interest from bank to ECB: net between interest on ECB debt and interest on Bank cash reserves held at ECB
    //bank_interest_amount = int_to_ecb - int_from_ecb
    interest = 0.0;

    START_BANK_INTEREST_PAYMENT_MESSAGE_LOOP
        interest += bank_interest_payment_message->bank_interest_amount;
    FINISH_BANK_INTEREST_PAYMENT_MESSAGE_LOOP

	CASH += interest;
	ECB_INFLOWS_CALENDAR.bank_interest += interest;

    #ifdef _DEBUG_MODE
        if(PRINT_DEBUG_CREDIT)
        {                        
            if(bank_mesg_count!=ACCOUNTS_BANKS.size)
            {    
                printf("\nERROR in Central_Bank_Functions.c, line 180: nr of mesg not equal to size of bank account array.\n");
                printf("\n Nr of Bank_mesg=%d, size of bank account array=%d\n", bank_mesg_count, ACCOUNTS_BANKS.size);
            }    
            else
                printf("\n Nr of mesg equal to size of bank account array.\n");
        }
    #endif
    
    START_GOV_TO_CENTRAL_BANK_ACCOUNT_UPDATE_MESSAGE_LOOP
        for (i=0;i<ACCOUNTS_GOVS.size;i++)
        {       
            //Search the correct account and update the value
            if(ACCOUNTS_GOVS.array[i].id == gov_to_central_bank_account_update_message->id)
            {
            	temp_deposit = ACCOUNTS_GOVS.array[i].payment_account;
                               
                ACCOUNTS_GOVS.array[i].payment_account = 
                gov_to_central_bank_account_update_message->payment_account;
                                
                if(temp_deposit >= ACCOUNTS_GOVS.array[i].payment_account)
                {
                 	ECB_OUTFLOWS_CALENDAR.gov_deposits +=
                 	(temp_deposit - ACCOUNTS_GOVS.array[i].payment_account);
                 }
                 else
				{
                 	ECB_INFLOWS_CALENDAR.gov_deposits +=
                 	(ACCOUNTS_GOVS.array[i].payment_account - temp_deposit);
                }
                
            }
    
            //Total deposits at ECB
            ECB_DEPOSITS += gov_to_central_bank_account_update_message->payment_account;
        }
        
        #ifdef _DEBUG_MODE        
        if(PRINT_DEBUG_CREDIT)
            gov_mesg_count++;    
        #endif
        
    FINISH_GOV_TO_CENTRAL_BANK_ACCOUNT_UPDATE_MESSAGE_LOOP

    #ifdef _DEBUG_MODE
        if(PRINT_DEBUG_CREDIT)
        {                        
            if(gov_mesg_count!=ACCOUNTS_GOVS.size)
            {
                printf("\nERROR in Central_Bank_Functions.c, line 107: nr of mesg not equal to size of gov account array.\n");
                printf("\n Nr of Gov_mesg=%d, size of gov account array=%d\n", gov_mesg_count, ACCOUNTS_GOVS.size);
            }
            else
                printf("\n Nr of mesg equal to size of gov account array.\n");
        }
    #endif        
    #ifdef _DEBUG_MODE        
        if (PRINT_DEBUG_FILE_EXP1)
        {                       
            filename = malloc(40*sizeof(char));
            filename[0]=0;
            strcpy(filename, "its/CentralBank_daily_balance_sheet.txt");      
            file1 = fopen(filename,"a");
            fprintf(file1,"\n %d %f %f %f",DAY,FIAT_MONEY_GOVS,FIAT_MONEY_BANKS, FIAT_MONEY);
            fprintf(file1," %f %f",CASH,ECB_DEPOSITS);
            fclose(file1);
            free(filename);
        }                
    #endif
   
   //End of month: stock-flow accounting
    if(DAY%MONTH == 0)
    {
		ECB_OUTFLOWS_CALENDAR.total_expenses = 
		ECB_OUTFLOWS_CALENDAR.gov_bond_purchase +
		
		ECB_OUTFLOWS_CALENDAR.bank_fiat_money +
		ECB_OUTFLOWS_CALENDAR.bank_deposits +
		ECB_OUTFLOWS_CALENDAR.gov_deposits +
		ECB_OUTFLOWS_CALENDAR.dividend_payment;
		
		ECB_INFLOWS_CALENDAR.total_income = 
		ECB_INFLOWS_CALENDAR.bank_interest +
		ECB_INFLOWS_CALENDAR.bank_debt_installment +
		ECB_INFLOWS_CALENDAR.gov_interest +
		ECB_INFLOWS_CALENDAR.bank_deposits +
		ECB_INFLOWS_CALENDAR.gov_deposits;
		
		
		ECB_INFLOWS_CALENDAR.net_inflow =
		ECB_INFLOWS_CALENDAR.total_income -
		ECB_OUTFLOWS_CALENDAR.total_expenses; 

		//CASH
		ECB_STOCKS_CALENDAR.cash = CASH;

		//Loans to banks	/govs	
		ECB_STOCKS_CALENDAR.fiat_money_banks = FIAT_MONEY_BANKS;
		ECB_STOCKS_CALENDAR.fiat_money_govs = FIAT_MONEY_GOVS;
		
		ECB_STOCKS_CALENDAR.nr_gov_bonds = 0;
		ECB_STOCKS_CALENDAR.gov_bond_holdings = 0.0;
		
		ECB_STOCKS_CALENDAR.total_assets =
		ECB_STOCKS_CALENDAR.fiat_money_banks +
		ECB_STOCKS_CALENDAR.gov_bond_holdings +
		ECB_STOCKS_CALENDAR.cash;

		//accounts
		ECB_STOCKS_CALENDAR.payment_account_banks=0.0;
		ECB_STOCKS_CALENDAR.payment_account_govs=0.0;

		for (j=0;j<ACCOUNTS_BANKS.size;j++)
		{       
			ECB_STOCKS_CALENDAR.payment_account_banks += 
			ACCOUNTS_BANKS.array[j].payment_account;
		}
	
		for (j=0;j<ACCOUNTS_GOVS.size;j++)
		{       
			ECB_STOCKS_CALENDAR.payment_account_govs += 
			ACCOUNTS_GOVS.array[j].payment_account;
		}

		//fiat
		ECB_STOCKS_CALENDAR.fiat_money = FIAT_MONEY;

		ECB_STOCKS_CALENDAR.equity = 
		ECB_STOCKS_CALENDAR.total_assets -
		ECB_STOCKS_CALENDAR.payment_account_govs -
		ECB_STOCKS_CALENDAR.payment_account_banks -
		ECB_STOCKS_CALENDAR.fiat_money;

		ECB_STOCKS_CALENDAR.total_liabilities = 
		ECB_STOCKS_CALENDAR.payment_account_govs +
		ECB_STOCKS_CALENDAR.payment_account_banks +
		ECB_STOCKS_CALENDAR.fiat_money +
		ECB_STOCKS_CALENDAR.equity;

		/*
		* Ecb pays dividend:
		* In case of positive ECB equity, the ECB makes a profit, and 
		* should distribute this evenly among governments
		*/
		double dividend_per_gov=0.0;
		int no_govs;
		if(CASH>0.0)
		{
			no_govs = TOTAL_REGIONS/NO_REGIONS_PER_GOV;

			//Step1 : ECB pays out all CASH as dividends
			dividend_per_gov = CASH/no_govs;

			//Step 2 : ECB adds dividends to Governments' payment accounts
			for (j=0; j<ACCOUNTS_GOVS.size; j++)	
				ACCOUNTS_GOVS.array[j].payment_account += dividend_per_gov;

			//Step 3 : ECB sends ecb_dividend_payment_msg, Governments adjust payment accounts
			add_ecb_dividend_message(dividend_per_gov);
		
			//Recompute stocks
			ECB_OUTFLOWS_CALENDAR.dividend_payment = CASH;
			ECB_STOCKS_CALENDAR.cash=0;		
			ECB_STOCKS_CALENDAR.payment_account_govs += CASH;
			ECB_STOCKS_CALENDAR.equity -= 2*CASH;
			CASH =0.0;
		}
	}//end of month loop
    return 0;
}

   
/** \fn Central_Bank_send_dividend()
 * \brief 
 */
int Central_Bank_send_dividend()
{
    return 0;
}

