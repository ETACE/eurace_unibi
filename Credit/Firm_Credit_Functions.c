    #include "../header.h"
    #include "../Firm_agent_header.h"
    #include "../my_library_header.h"
    

/*
 * \fn Iirm_receive_account_interest()
 * \brief Read account_interest message from Bank. Daily, at start of iteration.
 */
int Firm_receive_account_interest()
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
    FIRM_INFLOWS_CALENDAR.deposit_interest += interest; 

    return 0;	
}

int Firm_ask_loan()
{
/*
	SET_OF_LENDERS: dynamic array of POTENTIAL_LENDER
	POTENTIAL_LENDER ADT: dynamic array: (bank, contact)
	NUM_BANKS: int
	NUMBER_OF_BANKS_ASKED: int
*/
 
	int num_banks=0;
	int j=0;

    if (EXTERNAL_FINANCIAL_NEEDS>0.0)
    {
         //Delete the old set of lenders
		reset_int_array(&SET_OF_LENDERS);


         //Delete the old set of potential lenders
		reset_int_array(&POTENTIAL_LENDERS);
		
        //Search for active banks' name
         START_BANK_IDENTITY_MESSAGE_LOOP
                 add_int(&POTENTIAL_LENDERS,bank_identity_message->bank_id);
                 num_banks++;
         FINISH_BANK_IDENTITY_MESSAGE_LOOP
    
        #ifdef _DEBUG_MODE
            if (PRINT_DEBUG_CREDIT)
            {
                printf("\n\n Firm_ask_loan ID: %d",ID);
                printf("\n\t Found NUMBER_OF_BANKS: %d, POTENTIAL_LENDERS.size=%d",num_banks, POTENTIAL_LENDERS.size);
				printf("\n\t POTENTIAL_LENDERS: [");
				for(j=0;j<POTENTIAL_LENDERS.size;j++) printf("%d ",POTENTIAL_LENDERS.array[j]);
				printf("]");

            }
        #endif       
         
        
        //Create bank network for this firm
		NUMBER_OF_BANKS_ASKED=0;
		
          while(POTENTIAL_LENDERS.size>0 && NUMBER_OF_BANKS_ASKED<num_banks && NUMBER_OF_BANKS_ASKED<NUMBER_OF_BANKS_TO_APPLY)
          {	
				// choose random bank id
                j= random_int(0,POTENTIAL_LENDERS.size-1) ;
                add_loan_request_message(ID, POTENTIAL_LENDERS.array[j], EQUITY, TOTAL_DEBT, (EXTERNAL_FINANCIAL_NEEDS+1e-04));

				//Add bank to set of lenders asked
				add_int(&SET_OF_LENDERS, POTENTIAL_LENDERS.array[j]);

				//Move bank from potential to set of lenders
				remove_int(&POTENTIAL_LENDERS, j);
				NUMBER_OF_BANKS_ASKED++;
          }
	}


        #ifdef _DEBUG_MODE
            if (PRINT_DEBUG_CREDIT)
            {
                printf("\n\t NUMBER_OF_BANKS_ASKED: %d",NUMBER_OF_BANKS_ASKED);
				printf("\n\t SET_OF_LENDERS: [");
				for(j=0;j<SET_OF_LENDERS.size;j++) printf("%d ",SET_OF_LENDERS.array[j]);
				printf("]");
				printf("\n\t POTENTIAL_LENDERS: [");
				for(j=0;j<POTENTIAL_LENDERS.size;j++) printf("%d ",POTENTIAL_LENDERS.array[j]);
				printf("]");

                printf("\n\t EQUITY: %f TOTAL_DEBT: %f EXTERNAL_FINANCIAL_NEEDS: %f",EQUITY,TOTAL_DEBT,EXTERNAL_FINANCIAL_NEEDS);
                
            }
        #endif       

        return 0;
}
     
    
int Firm_get_loan()
{
        //#ifdef _DEBUG_MODE
        FILE * file1=NULL;
        char * filename="";
        //  #endif
            
        double credit_demand=0.0;
        double credit_offered=0.0;
        double credit_accepted=0.0;
        double total_credit_taken=0.0;
    
        int bank_id=0;
        double loan_value=0.0;
        double interest_rate=0.0;
        double interest_amount=0.0;
        double installment_amount=0.0;
        double var_per_installment=0.0;
        double residual_var=0.0;
        double bad_debt=0.0;
        int nr_periods_before_repayment=0;
        
        #ifdef _DEBUG_MODE
            if (PRINT_DEBUG_CREDIT)
            {
				printf("\n\n\t Firm_get_loan REFACTORED");
            }  
        #endif              

		/*Resetting on day 1 of calandar month: see Firm_Stat_Functions */
		//TOTAL_EXTERNAL_FINANCING_OBTAINED=0.0;
         
         // Set LAST_INTEREST_RATE_FOR_LOANS only if (credit_accepted>1e-4)
         LAST_INTEREST_RATE_FOR_LOANS = -1e-4;
	 
        //Travers the banks according to the order in the rate_order_array,
        //obtain a loan if credit_demand >= credit_offer
        START_LOAN_CONDITIONS_MESSAGE_LOOP

	            credit_offered = loan_conditions_message->amount_offered_credit;
	
	             //Set credit demand
                credit_demand = EXTERNAL_FINANCIAL_NEEDS - total_credit_taken;
				credit_accepted = 0.0;
	
                if (credit_demand < 0.0)
                    printf("\n ERROR in function Firm_get_loan, line 132: credit_demand is NEGATIVE.\n ");
        
                if (credit_demand >= credit_offered)
                {
                   credit_accepted = credit_offered;
                }
                else
                {
                   credit_accepted=credit_demand;
                }
                
				//Set data
                total_credit_taken += credit_accepted;                  
                bank_id = loan_conditions_message->bank_id;
                loan_value = credit_accepted;
                interest_rate = loan_conditions_message->proposed_interest_rate;
                installment_amount = credit_accepted/CONST_INSTALLMENT_PERIODS;
                interest_amount=interest_rate*installment_amount;
                    
                residual_var = loan_conditions_message->value_at_risk * (credit_accepted/credit_offered);
                
                var_per_installment = residual_var/CONST_INSTALLMENT_PERIODS;
                bad_debt = 0.0;
                nr_periods_before_repayment=CONST_INSTALLMENT_PERIODS+1;
                
                //ADD LOAN
                if(loan_value < 0.0)
                    printf("\n ERROR in function Firm_get_loan: loan_value is NEGATIVE.\n ");

             //Take out loans that are sufficiently large
             if (credit_accepted>1e-4)
             {
                add_debt_item(&LOANS, bank_id, loan_value, interest_rate, installment_amount, var_per_installment, residual_var, bad_debt, nr_periods_before_repayment);         
                add_loan_acceptance_message(bank_id, credit_accepted, residual_var, interest_rate);  
				LAST_INTEREST_RATE_FOR_LOANS = interest_rate;   

                //update the payment_account with the amount of credit obtained
                PAYMENT_ACCOUNT += credit_accepted;
                FIRM_INFLOWS_CALENDAR.new_loans += credit_accepted;
				TOTAL_EXTERNAL_FINANCING_OBTAINED += credit_accepted;
             }				

		#ifdef _DEBUG_MODE        
		if (PRINT_DEBUG_CREDIT)
		{
		    printf("\n\n Firm_get_loan ID: %d",ID); 
		    printf("\n\t Bank id: %d credit_accepted: %f interest_rate: %f", bank_id, credit_accepted,interest_rate);
		}                  
		#endif

        FINISH_LOAN_CONDITIONS_MESSAGE_LOOP

        
        if (PRINT_DEBUG_FILE_EXP1)
            {
                filename = malloc(40*sizeof(char));
                filename[0]=0;
                strcpy(filename, "its/credit_rationing.txt");      
                file1 = fopen(filename,"a");
                fprintf(file1,"\n %d %d %f %f %d",DAY,ID,EXTERNAL_FINANCIAL_NEEDS,total_credit_taken,REGION_ID);
                fclose(file1);
                free(filename);
            }    
        
        
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
        if (PRINT_DEBUG_CREDIT)
        {
			printf("\n\n Firm_get_loan ID: %d",ID); 
			printf("\n\t total_credit_taken: %f", total_credit_taken);
			printf("\n\t PAYMENT_ACCOUNT: %f EXTERNAL_FINANCIAL_NEEDS: %f",PAYMENT_ACCOUNT,EXTERNAL_FINANCIAL_NEEDS);
        }                  
        #endif
        
        return 0;
    }
    
    int Firm_idle()
    {
        return 0;
    }
    
