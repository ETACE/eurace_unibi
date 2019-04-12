#include "../header.h"
#include "../Firm_agent_header.h"
#include "../my_library_header.h"
#include "Mall_aux_header.h"
#include "../Labour/Labour_aux_headers.h"

/* Library functions */

/*
 * Function to calculate the expected wage bill
 */
double firm_calc_expected_wage_bill_production(int no_future_employees)
{
	int delta = no_future_employees - NO_EMPLOYEES_PRODUCTION;
	double expected_wage_bill = 0.0;

	if (delta >= 0)
	{
		expected_wage_bill = no_future_employees*(1.04)*MEAN_WAGE;
	}
	else
	{
		qsort(EMPLOYEES.array, EMPLOYEES.size, sizeof(employee),employee_list_rank_general_skills_function);

		int i;
		for(i = 0; i < no_future_employees; i++)
			expected_wage_bill += EMPLOYEES.array[i].wage;
	}

	return expected_wage_bill;
}

/** \fn Firm_calc_input_demands_2(), auxiliary function
 * \brief Firms recalculate the labor demand and the demand for capital goods
 * such that these can be financed with the external finances obtained.
 * This function is iterated multiple times by the function Firm_calc_production_quantity_2
 * in order to find the maximal possible production_quantity that can be financed.
 */
int Firm_calc_input_demands_2()
{
	int i;
 
    /*----------Determination of input needs:-----------------------*/


	/*1. Compute the feasible output given the capital stock*/
	double feasible_output=0.0;
	int employees_needed_last_month;

	for(i=0;i<CAPITAL_STOCK_VINTAGES.size;i++)
	{
		feasible_output+=CAPITAL_STOCK_VINTAGES.array[i].amount*min(CAPITAL_STOCK_VINTAGES.	
		array[i].productivity,MEAN_SPECIFIC_SKILLS);
	}

	/*2.  Check if additional investments are necessary*/
	if(feasible_output >= PLANNED_PRODUCTION_QUANTITY)
	{
		
		if(NO_EMPLOYEES_PRODUCTION>0)
		{
		employees_needed_last_month  = NO_EMPLOYEES_PRODUCTION;


		EMPLOYEES_NEEDED_PRODUCTION = round_double_to_int(PLANNED_PRODUCTION_QUANTITY/OUTPUT * employees_needed_last_month);
		}else
		{
			EMPLOYEES_NEEDED_PRODUCTION = round_double_to_int(PLANNED_PRODUCTION_QUANTITY/MEAN_SPECIFIC_SKILLS);
		}

		NEEDED_CAPITAL_STOCK = EMPLOYEES_NEEDED_PRODUCTION;
	
	}else
	{	
		/*Imput factor determination*/
			
		DEMAND_CAPITAL_STOCK = (PLANNED_PRODUCTION_QUANTITY-feasible_output)/min(TECHNOLOGY_VINTAGES.
		array[VINTAGE_SELECTED].productivity,MEAN_SPECIFIC_SKILLS);

		EMPLOYEES_NEEDED_PRODUCTION = round_double_to_int(TOTAL_UNITS_CAPITAL_STOCK + DEMAND_CAPITAL_STOCK);


		NEEDED_CAPITAL_STOCK = EMPLOYEES_NEEDED_PRODUCTION;

	}    

	/*Set the capital demand*/

	DEMAND_CAPITAL_STOCK = max(NEEDED_CAPITAL_STOCK-TOTAL_UNITS_CAPITAL_STOCK,0.0);

	double expected_wage_bill = firm_calc_expected_wage_bill_production(EMPLOYEES_NEEDED_PRODUCTION);
        
        /*This computes the financial needings for production*/
        /*Distinction of cases: if subsidies for best practice technol.ogy*/
		if(POLICY_EXP_BEST_TECHNOLOGY_SUBSIDY==1 && abs_double(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity - TECHNOLOGICAL_FRONTIER)<1e-5)
		{
			PLANNED_PRODUCTION_COSTS = expected_wage_bill + DEMAND_CAPITAL_STOCK*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price*(1-SUBSIDY_PCT);
		}else
		{
			PLANNED_PRODUCTION_COSTS = expected_wage_bill + DEMAND_CAPITAL_STOCK*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price;
		}

		PLANNED_INNOVATION_EXPENDITURES = 	EMPLOYEES_NEEDED_INNOVATION*(1.04)*MEAN_WAGE_R_AND_D;
		PLANNED_EXPENDITURES_PRODUCTION_INNOVATION= PLANNED_PRODUCTION_COSTS +PLANNED_INNOVATION_EXPENDITURES ;
		EMPLOYEES_NEEDED = EMPLOYEES_NEEDED_PRODUCTION  + EMPLOYEES_NEEDED_INNOVATION;
    
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_PRODUCTION)
    {
		  if(ID==ID_DEBUG_PROBE)
            {
        printf("\n\n IT %d Firm_calc_input_demands_2 ID: %d PAYMENT_ACCOUNT = %f",DAY, ID, PAYMENT_ACCOUNT);
	printf("\n\t MEAN_WAGE=%f DEMAND_CAPITAL_STOCK=%f ACTUAL_CAP_PRICE=%f", MEAN_WAGE, DEMAND_CAPITAL_STOCK, ACTUAL_CAP_PRICE);
	printf("\n\t PLANNED_PRODUCTION_COSTS=%f PLANNED_PRODUCTION_QUANTITY=%f MEAN_SPECIFIC_SKILLS=%f MEAN_WAGE=%f TECHNOLOGY=%f",PLANNED_PRODUCTION_COSTS, PLANNED_PRODUCTION_QUANTITY,MEAN_SPECIFIC_SKILLS,MEAN_WAGE,TECHNOLOGY);
        printf("\n\t TOTAL_UNITS_CAPITAL_STOCK=%f NEEDED_CAPITAL_STOCK=%f",TOTAL_UNITS_CAPITAL_STOCK,NEEDED_CAPITAL_STOCK);
        printf("\n\t DEMAND_CAPITAL_STOCK=%f EMPLOYEES_NEEDED_PRODUCTION=%d",DEMAND_CAPITAL_STOCK,EMPLOYEES_NEEDED_PRODUCTION);
		}

    }
    #endif
    
    return 0;
}   


/************************************ Firm agent functions ************************************/


int Firm_set_quantities_zero()
{

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_PRODUCTION)
    {		  
		if(ID==ID_DEBUG_PROBE)
        {
        	printf("\n\n Firm_set_quantities_zero ID: %d",ID);
        	printf("\n\t DAY_OF_MONTH_TO_ACT: %d",DAY_OF_MONTH_TO_ACT);
      	}
    }
    #endif
                        
    PLANNED_PRODUCTION_QUANTITY = 0;
    PRODUCTION_QUANTITY = 0;

    TOTAL_INTEREST_PAYMENT=0.0;
    TOTAL_DEBT_INSTALLMENT_PAYMENT=0.0;

    return 0;
}


/********************************Firm Role Consumption Goods marke*******************************/


/** \fn Firm_calc_production_quantity()
 * \brief Firm calculate the intended production volume depending on the current stocks in the malls*/
int Firm_calc_production_quantity()
{

    double production_volume = 0;
    double prod_vol, local_buffer;
    int i,j;
    FILE *file1;
     char *filename;    
    


    //Reset the counters at the start of month
    CUM_TOTAL_SOLD_QUANTITY = 0.0;
    CUM_REVENUE = 0.0;  
	STOCK =0.0;
   
    
    //Delete the LINEAR_REGRESSION_ESTIMATORS array
    
    
    //New forcasting rule added on August, 24th

	/*Comptuing the current market share esitmation as liear combination of the estimation of the beginning and the end of the year*/
	ESTIMATED_MARKET_SHARE = (COUNTER_MONTH_SINCE_LAST_PRICE_SETTING/11.0)*ESTIMATED_MARKET_SHARE_END_OF_YEAR +
		((11-COUNTER_MONTH_SINCE_LAST_PRICE_SETTING)/11.0)*ESTIMATED_MARKET_SHARE_BEGINNING_OF_YEAR;
	
	/*Set the total bufferdepending on the service degree and the variance of the demand estimation*/
	TOTAL_BUFFER = QUANTIL_NORMAL_DISTRIBUTION*pow(COMBINED_VARIANCE_DEMAND_FUNCTION ,0.5);
   

	for(i=0;i<LINEAR_REGRESSION_MARKET_SIZE.size;i++)
	{
		for(j=0;j<CURRENT_MALL_STOCKS.size;j++)
		{
			if(CURRENT_MALL_STOCKS.array[j].mall_id==LINEAR_REGRESSION_MARKET_SIZE.array[i].mall_id)
			{
				/*Distribute the buffer among the malls*/
				local_buffer = TOTAL_BUFFER*   (LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept 
				 + (1+LAST_MARKET_SIZES.array[0].market_sizes.size +COUNTER_MONTH_SINCE_LAST_PRICE_SETTING)*LINEAR_REGRESSION_MARKET_SIZE.array[i].regressor)/
					(LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept 
				 + (1+LAST_MARKET_SIZES.array[0].market_sizes.size +COUNTER_MONTH_SINCE_LAST_PRICE_SETTING)*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor);

					/*Cumpute for each mall the critical stock*/
				 CURRENT_MALL_STOCKS.array[j].critical_stock = ESTIMATED_MARKET_SHARE *(LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept 
				 + (1+LAST_MARKET_SIZES.array[0].market_sizes.size +COUNTER_MONTH_SINCE_LAST_PRICE_SETTING)*LINEAR_REGRESSION_MARKET_SIZE.array[i].regressor)
				 + local_buffer;

				#ifdef _DEBUG_MODE
      			if (PRINT_DEBUG_PRODUCTION)
     		    {
					if(ID==ID_DEBUG_PROBE)
      			    {	
					   printf("\n CURRENT_MALL_STOCKS.array[i].critical_stock %f \t LINEAR_REGRESSION_MARKET_SIZE.array[j].intercept %f \t LINEAR_REGRESSION_MARKET_SIZE.array[j].regressor %f \t COUNTER_MONTH_SINCE_LAST_PRICE_SETTING %d \t LINEAR_REGRESSION_MARKET_SIZE.array[j].variance %f, 	Buffer:  %f    ESTIMATED_MARKET_SHARE %f\n ",CURRENT_MALL_STOCKS.array[j].critical_stock, LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept,LINEAR_REGRESSION_MARKET_SIZE.array[i].regressor,  COUNTER_MONTH_SINCE_LAST_PRICE_SETTING,LINEAR_REGRESSION_MARKET_SIZE.array[i].variance, local_buffer, ESTIMATED_MARKET_SHARE);
		        	}        
				}
 				 #endif		
									
	
			}					
				
		}
    }


	//ESTIMATED_MARKET_SIZE of total market

	ESTIMATED_MARKET_SIZE = (LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept 
				 + (1+LAST_MARKET_SIZES.array[0].market_sizes.size +COUNTER_MONTH_SINCE_LAST_PRICE_SETTING)*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor);

	EXPECTED_SOLD_QUANTITY_PER_MONTH = ESTIMATED_MARKET_SHARE *(LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept 
				 + (1+LAST_MARKET_SIZES.array[0].market_sizes.size +COUNTER_MONTH_SINCE_LAST_PRICE_SETTING)*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor);
      

    /*checking whether or not the current mall stocks are below the critical values         
     * (sS-Rule) If this is the case refill the stock up to the max stock */
     for(i = 0; i < CURRENT_MALL_STOCKS.size; i++)
      {
		STOCK +=CURRENT_MALL_STOCKS.array[i].current_stock;
		CRITICAL_STOCK += CURRENT_MALL_STOCKS.array[i].critical_stock;
            
         if(CURRENT_MALL_STOCKS.array[i].current_stock <= 
         	CURRENT_MALL_STOCKS.array[i].critical_stock)    
         {
                /*If stocks are left at the beginning of a new production cycle 
                 * then firms produce the difference between these stocks and the 
                 * critical stock for this mall*/
              
                    prod_vol = CURRENT_MALL_STOCKS.array[i].critical_stock - CURRENT_MALL_STOCKS.array[i].current_stock;
    
                    PLANNED_DELIVERY_VOLUME.array[i].mall_id = 
                    CURRENT_MALL_STOCKS.array[i].mall_id;

                    PLANNED_DELIVERY_VOLUME.array[i].quantity  = prod_vol;
                                
                production_volume = production_volume + prod_vol;
                
            }
            else/*If  stocks are higher than the critical value no production takes place for this mall*/
            {
                PLANNED_DELIVERY_VOLUME.array[i].mall_id= 
                CURRENT_MALL_STOCKS.array[i].mall_id;

                PLANNED_DELIVERY_VOLUME.array[i].quantity= 0;
            }



        }

        /*Smoothing of production quantity in order to avoid high fluctuations*/
        double mean_production_quantity=0;
        for( i = 0; i < LAST_PLANNED_PRODUCTION_QUANTITIES.size; i++)
        {
            mean_production_quantity += LAST_PLANNED_PRODUCTION_QUANTITIES.array[i];
        }

        mean_production_quantity = mean_production_quantity/
        LAST_PLANNED_PRODUCTION_QUANTITIES.size;
    
        PLANNED_PRODUCTION_QUANTITY = LAMBDA*production_volume + (1-LAMBDA)*mean_production_quantity;
        
        //Set planned production value that is retained in memory during the month:
        PLANNED_OUTPUT = PLANNED_PRODUCTION_QUANTITY; 
        
        #ifdef _DEBUG_MODE
        if (PRINT_DEBUG_PRODUCTION)
        {
			  if(ID==ID_DEBUG_PROBE)
            {	
            	printf("\n\n IT %d Firm_calc_production_quantity ID: %d",DAY, ID);
	    		printf("\n\t mean_production_quantity=%f production_volume=%f PLANNED_PRODUCTION_QUANTITY=%f", mean_production_quantity, production_volume, PLANNED_PRODUCTION_QUANTITY);

				printf("\n Planned delivery volumes to malls:");

				for(i=0;i<PLANNED_DELIVERY_VOLUME.size;i++ )
				{
					printf("\n Planned delivery volume for mall id = %d \t %f",PLANNED_DELIVERY_VOLUME.array[i].mall_id,PLANNED_DELIVERY_VOLUME.array[i].quantity);
				}	
		
			}        
		}
        #endif
        
        if (PRINT_DEBUG_FILE_EXP1)
        {                       
            filename = malloc(40*sizeof(char));
            filename[0]=0;
            strcpy(filename, "its/Firm_calc_production_quantity.txt");      
            file1 = fopen(filename,"a");
            fprintf(file1,"\n %d %d %f %d",DAY,ID,PLANNED_PRODUCTION_QUANTITY,REGION_ID);
            fclose(file1);
            free(filename);
        }  
        
    return 0;

}

    
/** \fn Firm_calc_input_demands()
 * \brief Firms calculate the labor demand and the demand for capital goods*/
int Firm_calc_input_demands()
{
	
    int i,j;
	double logit_for_print_debug[TECHNOLOGY_VINTAGES.size];

	double employees_needed_inno = 0.0; 
	
	EFFECTIVE_INVESTMENTS = 0.0;	


	  //Clean the array of vintages
	  for(i=TECHNOLOGY_VINTAGES.size-1; i>=0;i--)
	{
	remove_adt_technology_vintages(&TECHNOLOGY_VINTAGES,i);
	}	
    
   	 /*Getting information about the offered vintages*/
        START_PRODUCTIVITY_MESSAGE_LOOP
            
		add_adt_technology_vintages(&TECHNOLOGY_VINTAGES,productivity_message->cap_productivity, productivity_message->cap_good_price,0.0);	
			
        FINISH_PRODUCTIVITY_MESSAGE_LOOP
	
		
	 TECHNOLOGICAL_FRONTIER = TECHNOLOGY_VINTAGES.array[TECHNOLOGY_VINTAGES.size-1].productivity;
     ACTUAL_CAP_PRICE = TECHNOLOGY_VINTAGES.array[TECHNOLOGY_VINTAGES.size-1].price;

	//Setting up the logit print debug array. This array is used for printing out the logits for debugging
	for(i=0;i<TECHNOLOGY_VINTAGES.size;i++)
	{
		logit_for_print_debug[i]=0.0;
	}
	
	/*Depreciation of the capital stock*/

	double depreciation;	

	TOTAL_CAPITAL_DEPRECIATION_UNITS=0;
	TOTAL_VALUE_CAPITAL_STOCK=0;
	TOTAL_UNITS_CAPITAL_STOCK=0;
	EFFECTIVE_CAPITAL_STOCK = 0.0;

	for(i=0;i<CAPITAL_STOCK_VINTAGES.size;i++)
	{
	depreciation = CAPITAL_STOCK_VINTAGES.array[i].amount*DEPRECIATION_RATE;
	
	TOTAL_CAPITAL_DEPRECIATION_UNITS += depreciation;
	CAPITAL_STOCK_VINTAGES.array[i].amount-=depreciation;
	TOTAL_UNITS_CAPITAL_STOCK+=CAPITAL_STOCK_VINTAGES.array[i].amount;

	EFFECTIVE_CAPITAL_STOCK += CAPITAL_STOCK_VINTAGES.array[i].amount* CAPITAL_STOCK_VINTAGES.array[i].productivity;

		for(j=0;j<TECHNOLOGY_VINTAGES.size;j++)
		{
		if(CAPITAL_STOCK_VINTAGES.array[i].productivity==TECHNOLOGY_VINTAGES.array[j].productivity)
			{
			TOTAL_CAPITAL_DEPRECIATION_VALUE += TECHNOLOGY_VINTAGES.array[j].price*depreciation;

			TOTAL_VALUE_CAPITAL_STOCK+=TECHNOLOGY_VINTAGES.array[j].price*CAPITAL_STOCK_VINTAGES.array[i].amount;

			

			
			}
		}

	}

	if(TOTAL_UNITS_CAPITAL_STOCK>0.0)
	TOTAL_PRODUCTIVITY_CAPITAL_STOCK = EFFECTIVE_CAPITAL_STOCK / TOTAL_UNITS_CAPITAL_STOCK;

	/*----------Determination of input needs:-----------------------*/


	/*1. Compute the feasible output given the capital stock*/
	double feasible_output=0.0;
	int employees_needed_last_month;

	for(i=0;i<CAPITAL_STOCK_VINTAGES.size;i++)
	{
		feasible_output+=CAPITAL_STOCK_VINTAGES.array[i].amount*min(CAPITAL_STOCK_VINTAGES.array[i].productivity,MEAN_SPECIFIC_SKILLS);
	}

	/*2.  Check if additional investments are necessary*/
	if(feasible_output >= PLANNED_PRODUCTION_QUANTITY)
	{
	DEMAND_CAPITAL_STOCK=0.0;
	VINTAGE_CHOICE_TAKEN = 0;
		
		if(NO_EMPLOYEES_PRODUCTION>0)
		{
		employees_needed_last_month  = NO_EMPLOYEES_PRODUCTION;
		EMPLOYEES_NEEDED_PRODUCTION =round_double_to_int(PLANNED_PRODUCTION_QUANTITY/OUTPUT * employees_needed_last_month);
		
		}else
		{
			EMPLOYEES_NEEDED_PRODUCTION =round_double_to_int(PLANNED_PRODUCTION_QUANTITY/MEAN_SPECIFIC_SKILLS);
		}

		NEEDED_CAPITAL_STOCK = EMPLOYEES_NEEDED_PRODUCTION;

		VINTAGE_CHOICE_ALREADY_TAKEN=0;
	}else
	{	
		
			//This is to check if the firm has already chosen a vintage during the price setting process
		if(VINTAGE_CHOICE_ALREADY_TAKEN==0)
		{
			/*Technology choice*/
		
			/*For each vintage compute...*/
			
			VINTAGE_CHOICE_TAKEN = 1;	
		
			double sum_eff_productivites[TECHNOLOGY_VINTAGES.size];
			double productivity_price_ratio[TECHNOLOGY_VINTAGES.size];
				
			double specific_skills;

			for(i=0;i<TECHNOLOGY_VINTAGES.size;i++)
			{
				/* ...the sum of discounted effective productivities. This means the min of the productivity of the capital good and the mean specific skills where the later converges to the A_i,t */

				specific_skills = MEAN_SPECIFIC_SKILLS;
				sum_eff_productivites[i] = 0;		
			
				for(j=0;j<24;j++)
				{
					if(SKILL_UPDATE_ACC_TO_FORMULA==1)
					{
      					/*Update the specific skill: depends on the actual specific skill, 
        				the gap between the actual specific skills and the actual productivity of the employer,
        				and the general skill which determines the speed of closing the this gap.*/
       					specific_skills = max(specific_skills, specific_skills+ 
						(TECHNOLOGY_VINTAGES.array[i].productivity-specific_skills)
						*((1-pow(0.5,1/(20+0.25*(AVERAGE_G_SKILL-1)*(4-20))))));
					}else
					{
	 				 /*Update the specific skill: depends on the actual specific skill, 
       					 the gap between the actual specific skills and the actual productivity of
					 the employer.*/

		
      						specific_skills = max(specific_skills, specific_skills
							+ (TECHNOLOGY_VINTAGES.array[i].productivity-specific_skills)		     
							*AVERAGE_ADAPTATION_SPEED_SPECIFIC_SKILLS);

			
					
					}
				
					sum_eff_productivites[i]+= pow(1/(1+DISCONT_RATE),j)*
					min(TECHNOLOGY_VINTAGES.array[i].productivity,specific_skills); 
				}


				/* If subsidies for best vintage are switched on: reduce the effective price
				 for best practice technology*/				
				if(POLICY_EXP_BEST_TECHNOLOGY_SUBSIDY==1 && abs_double(TECHNOLOGY_VINTAGES.array[i].productivity - TECHNOLOGICAL_FRONTIER)<1e-5)
				{
					productivity_price_ratio[i]= sum_eff_productivites[i]/ (TECHNOLOGY_VINTAGES.array[i].price*(1-SUBSIDY_PCT));
					TECHNOLOGY_VINTAGES.array[i].sum_effective_productivities = sum_eff_productivites[i];
	
				}else
				{
					productivity_price_ratio[i]= sum_eff_productivites[i]/ (TECHNOLOGY_VINTAGES.array[i].price);
					TECHNOLOGY_VINTAGES.array[i].sum_effective_productivities = sum_eff_productivites[i];
				}
			}

			/*A Logit model used for vintage choice*/
			
			double sum=0;
			double logit[TECHNOLOGY_VINTAGES.size];
				
			if(DAY>=0)
			{
				/*Summing for logit denominator*/
				for(i=0; i<TECHNOLOGY_VINTAGES.size;i++)
				{
					sum += exp(GAMMA_LOGIT_VINTAGE_CHOICE*log(productivity_price_ratio[i]));
				}

				/*Computing the logits*/
				for(i=0; i<TECHNOLOGY_VINTAGES.size;i++)
				{
					logit[i]= exp(GAMMA_LOGIT_VINTAGE_CHOICE*log(productivity_price_ratio[i]))/sum;

					logit_for_print_debug[i]=logit[i];
				}
			

				/*random generator and selection of logit*/

				double rnd_number = (double)random_int(0,100)/100.0;

				for(i=0; i<TECHNOLOGY_VINTAGES.size;i++)
				{	
					if(rnd_number<logit[i])
					{
						VINTAGE_SELECTED = i;
						break;
					}else
					{
						if(i<TECHNOLOGY_VINTAGES.size-1)
							logit[i+1]+=logit[i];
					}
	
				}
			
			}else
			{
				/*Ensure that in the transition phase the firm does only buy the already bought vintage */
				if(CAPITAL_STOCK_VINTAGES.size==1)
				{
					for(i=0; i <TECHNOLOGY_VINTAGES.size;i++)
					{
						if(abs_double(TECHNOLOGY_VINTAGES.array[i].productivity-CAPITAL_STOCK_VINTAGES.array[0].productivity)<1e-5)
						{
							VINTAGE_SELECTED = i;
							break;
						}

					}
				}
			}
			

		}else
		{

			//VINTAGE_CHOICE_ALREADY_TAKEN=0;

		}

			/*Imput factor determination*/
		
			DEMAND_CAPITAL_STOCK = (PLANNED_PRODUCTION_QUANTITY-feasible_output)/min(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity,MEAN_SPECIFIC_SKILLS);


			//Investion inertia

			if(DEMAND_CAPITAL_STOCK > INV_INERTIA*TOTAL_CAPITAL_DEPRECIATION_UNITS)
			{
		
				DEMAND_CAPITAL_STOCK = INV_INERTIA*TOTAL_CAPITAL_DEPRECIATION_UNITS;
				PLANNED_PRODUCTION_QUANTITY = DEMAND_CAPITAL_STOCK*min(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity,MEAN_SPECIFIC_SKILLS) + feasible_output;
			}
	
			EMPLOYEES_NEEDED_PRODUCTION = round_double_to_int(TOTAL_UNITS_CAPITAL_STOCK + DEMAND_CAPITAL_STOCK);

			NEEDED_CAPITAL_STOCK = EMPLOYEES_NEEDED_PRODUCTION;

			
	}

	DEMAND_CAPITAL_STOCK = max(0.0, NEEDED_CAPITAL_STOCK - TOTAL_UNITS_CAPITAL_STOCK);
	
	EMPLOYEES_NEEDED_INNOVATION = OPTIMAL_EMPLOYEES_NEEDED_INNOVATION;

	double expected_wage_bill = firm_calc_expected_wage_bill_production(EMPLOYEES_NEEDED_PRODUCTION);

	/*Financial planning:*/	

	/*Distinction of cases: if subsidies for best practice technology*/
	if(POLICY_EXP_BEST_TECHNOLOGY_SUBSIDY==1 && abs_double(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity - TECHNOLOGICAL_FRONTIER)<1e-5)
	{
	
		PLANNED_PRODUCTION_COSTS = expected_wage_bill + DEMAND_CAPITAL_STOCK*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price*(1-SUBSIDY_PCT);
	
	}else
	{
		
		PLANNED_PRODUCTION_COSTS = expected_wage_bill + DEMAND_CAPITAL_STOCK*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price;

	}

	PLANNED_INNOVATION_EXPENDITURES = 	EMPLOYEES_NEEDED_INNOVATION*(1.04)*MEAN_WAGE_R_AND_D;

	PLANNED_EXPENDITURES_PRODUCTION_INNOVATION= PLANNED_PRODUCTION_COSTS +PLANNED_INNOVATION_EXPENDITURES ;

	EMPLOYEES_NEEDED = EMPLOYEES_NEEDED_PRODUCTION  + EMPLOYEES_NEEDED_INNOVATION;
		
    
        #ifdef _DEBUG_MODE
        if (PRINT_DEBUG_PRODUCTION)
        { 
		  if(ID==ID_DEBUG_PROBE)
          {
			printf("\n\n Firm_calc_input_demands ID: %d",ID);
			printf("\nPLANNED_PRODUCTION_COSTS %f \tEMPLOYEES_NEEDED_PRODUCTION: %d \tMEAN_WAGE: %f",PLANNED_PRODUCTION_COSTS,EMPLOYEES_NEEDED_PRODUCTION,MEAN_WAGE);
			printf("\t DEMAND_CAPITAL_STOCK  %f \n", DEMAND_CAPITAL_STOCK);
			printf("\t EMPLOYEES_NEEDED_INNOVATION: %d employees_needed_inno %f  PLANNED_INNOVATION_EXPENDITURES%f \n", EMPLOYEES_NEEDED_INNOVATION,employees_needed_inno, PLANNED_INNOVATION_EXPENDITURES);
			printf("\t PLANNED_EXPENDITURES_PRODUCTION_INNOVATION%f \n", PLANNED_EXPENDITURES_PRODUCTION_INNOVATION);
		
			printf("Vintage choice:\n");	

			for(i=0; i<TECHNOLOGY_VINTAGES.size;i++)
			{
				printf("Vintage: %d\t Price: %f \t Productivity: %f \t logit: %f \n",i, TECHNOLOGY_VINTAGES.array[i].price, TECHNOLOGY_VINTAGES.array[i].productivity,logit_for_print_debug[i] );
			}
			printf("VINTAGE_SELECTED %d \n", VINTAGE_SELECTED);
		
	    }
        }
        #endif
    
    return 0;
}


/* GENUA NOTE: This needs to be updated with the new style of checking FINANCIAL_NEEDS
 * See file: Firm_Financial_Management
 */

/** \fn Firm_calc_production_quantity_2()
 * \brief Firms iterate over the planned production quantity decreasing it incrementally,
 * such that the corresponding labor demand and capital demand can be financed by the actually obtained financial resources.
 * If PLANNED_PRODUCTION_COSTS <= PAYMENT_ACCOUNT this function does nothing.
 */
int Firm_calc_production_quantity_2()
{
    double decrement;
    double diff;
    diff = PLANNED_PRODUCTION_QUANTITY;
    FILE *file1;
     char *filename;    

    //Here we set a fraction of the planned production quantity
    decrement = ADAPTION_PRODUCTION_VOLUME_DUE_TO_INSUFFICIENT_FINANCES*PLANNED_PRODUCTION_QUANTITY;
    
        if( PAYMENT_ACCOUNT>1e-6)
        {
            
			if(PLANNED_EXPENDITURES_PRODUCTION_INNOVATION >PAYMENT_ACCOUNT)
			{
				if(PLANNED_PRODUCTION_COSTS < PAYMENT_ACCOUNT)
				{
					while (PLANNED_EXPENDITURES_PRODUCTION_INNOVATION > PAYMENT_ACCOUNT)
					{
						EMPLOYEES_NEEDED_INNOVATION--;
	
						PLANNED_INNOVATION_EXPENDITURES = 	EMPLOYEES_NEEDED_INNOVATION*(1.04)*MEAN_WAGE_R_AND_D;
						PLANNED_EXPENDITURES_PRODUCTION_INNOVATION= PLANNED_PRODUCTION_COSTS +PLANNED_INNOVATION_EXPENDITURES ;
					
					}

					EMPLOYEES_NEEDED = EMPLOYEES_NEEDED_PRODUCTION + EMPLOYEES_NEEDED_INNOVATION; 
				}else
				{
          	  		while (PLANNED_PRODUCTION_COSTS > PAYMENT_ACCOUNT)
            		{



							#ifdef _DEBUG_MODE
        if (PRINT_DEBUG_PRODUCTION)
        { 
			if(ID==ID_DEBUG_PROBE)
          	{
            
         
            	printf("\n\t PLANNED_PRODUCTION_QUANTITY: %.2f (-%.2f) PLANNED_OUTPUT: %.2f",PLANNED_PRODUCTION_QUANTITY, diff, PLANNED_OUTPUT);
			}
		}
        #endif




						EMPLOYEES_NEEDED_INNOVATION=0;
						PLANNED_PRODUCTION_QUANTITY -= decrement;
						if( PLANNED_PRODUCTION_QUANTITY>1e-5)
						{
            	    		Firm_calc_input_demands_2();
						}else
						{
							 PLANNED_PRODUCTION_QUANTITY=0.0;
           					Firm_calc_input_demands_2();
							break;
						}
           			 }
				}
			}
        }else
        {
            PLANNED_PRODUCTION_QUANTITY=0.0;
			EMPLOYEES_NEEDED_INNOVATION=0;
            Firm_calc_input_demands_2();
        }
        
        //Compute the diff
        diff -= PLANNED_PRODUCTION_QUANTITY;
        
        //Set planned production value that is retained in memory during the month:
        PLANNED_OUTPUT = PLANNED_PRODUCTION_QUANTITY;

        double expected_wage_bill = firm_calc_expected_wage_bill_production(EMPLOYEES_NEEDED_PRODUCTION);

		REMAINING_BUDGET_FOR_HIRING = expected_wage_bill;
		
		int i=0;
		for(i=0; i<EMPLOYEES.size;i++)
			REMAINING_BUDGET_FOR_HIRING -= EMPLOYEES.array[i].wage;

		// if remianing budget < 0, employees will be fired later
		if(REMAINING_BUDGET_FOR_HIRING < 0)
			REMAINING_BUDGET_FOR_HIRING = 0;

	#ifdef _DEBUG_MODE
        if (PRINT_DEBUG_PRODUCTION)
        { 
			if(ID==ID_DEBUG_PROBE)
          	{
            	printf("\n\n Firm_calc_production_quantity_2 ID: %d",ID);
            	printf("\n\t EMPLOYEES_NEEDED_PRODUCTION: %d \t NEEDED_CAPITAL_STOCK: %f",EMPLOYEES_NEEDED_PRODUCTION,NEEDED_CAPITAL_STOCK);
            	printf("\n\t PLANNED_PRODUCTION_COSTS: %f",PLANNED_PRODUCTION_COSTS);
            	printf("\n\t PLANNED_PRODUCTION_QUANTITY: %.2f (-%.2f) PLANNED_OUTPUT: %.2f",PLANNED_PRODUCTION_QUANTITY, diff, PLANNED_OUTPUT);
				printf("\t EMPLOYEES_NEEDED_INNOVATION: %d  PLANNED_INNOVATION_EXPENDITURES%f \n", EMPLOYEES_NEEDED_INNOVATION, PLANNED_INNOVATION_EXPENDITURES);
				printf("\t PLANNED_EXPENDITURES_PRODUCTION_INNOVATION%f \n", PLANNED_EXPENDITURES_PRODUCTION_INNOVATION);
			}	
		}
        #endif

        if (PRINT_DEBUG_FILE_EXP1)
        {                       
            filename = malloc(40*sizeof(char));
            filename[0]=0;
            strcpy(filename, "its/Firm_calc_production_quantity_2.txt");      
            file1 = fopen(filename,"a");
            fprintf(file1,"\n %d %d %f %d",DAY,ID,PLANNED_PRODUCTION_QUANTITY,REGION_ID);
            fclose(file1);
            free(filename);
        }  
        
    return 0;
}

/** \fn Firm_send_capital_demand()
 * \brief Firm sends demand for capital to the capital goods market. */
int Firm_send_capital_demand()
{
    //Check how many units of the consumption good can be produced with the current labor force. 

	//Recalc capital demand if rationed at the labor market	
	DEMAND_CAPITAL_STOCK = max(0,NO_EMPLOYEES_PRODUCTION-TOTAL_UNITS_CAPITAL_STOCK);


    if ( NEEDED_CAPITAL_STOCK > 0.0)
        {                   
            
             add_capital_good_request_message(ID,DEMAND_CAPITAL_STOCK,VINTAGE_SELECTED);          
        }

	#ifdef _DEBUG_MODE
        if (PRINT_DEBUG_PRODUCTION)
        { 
			if(ID==ID_DEBUG_PROBE)	
            {
          	  printf("\n\n Firm_send_capital_demand ID: %d",ID);
          	  printf("\n\t DEMAND_CAPITAL_STOCK: %f",DEMAND_CAPITAL_STOCK);
			}		
		}
        #endif

    return 0;
}


int Firm_receive_capital_goods()
{
    
	int i,j;

        FILE *file1;
        char *filename;
        double capital_good_price = 0.0;
        double capital_good_delivery_volume = 0.0;

	int flag = 0;
        
        CAPITAL_COSTS = 0.0;
		SUBSIDY_PAYMENT=0.0;

	// EFFECTIVE_INVESTMENTS is set to 0 in Firm_calc_input_demands
	
    
        START_CAPITAL_GOOD_DELIVERY_MESSAGE_LOOP
        
        /*Determine the weighted average productivity of the total capital stock*/
    
        /*Update of productivity*/
		
        /*Update of current value of capital stock*/
 
 		for(i=0;i<CAPITAL_STOCK_VINTAGES.size;i++)
		{
			if(capital_good_delivery_message->productivity==CAPITAL_STOCK_VINTAGES.array[i].productivity)
			{
				CAPITAL_STOCK_VINTAGES.array[i].amount +=capital_good_delivery_message->capital_good_delivery_volume;
				
				TOTAL_UNITS_CAPITAL_STOCK+=capital_good_delivery_message->capital_good_delivery_volume;

				EFFECTIVE_INVESTMENTS = capital_good_delivery_message->capital_good_delivery_volume * CAPITAL_STOCK_VINTAGES.array[i].productivity; 

				TOTAL_VALUE_CAPITAL_STOCK+= capital_good_delivery_message->capital_good_price*
					capital_good_delivery_message->capital_good_delivery_volume;


				EFFECTIVE_CAPITAL_STOCK += capital_good_delivery_message->capital_good_delivery_volume * CAPITAL_STOCK_VINTAGES.array[i].productivity;
				flag=1;
				
				break;
			
				
			}
					
			
		}		
 		/*If new capital vintage is purchased add new vintage to array*/

					
 		if(flag==0)
		{
			add_adt_capital_stock_vintages(&CAPITAL_STOCK_VINTAGES,capital_good_delivery_message->capital_good_delivery_volume,TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity);

		TOTAL_UNITS_CAPITAL_STOCK+=capital_good_delivery_message->capital_good_delivery_volume;
		EFFECTIVE_CAPITAL_STOCK += capital_good_delivery_message->capital_good_delivery_volume*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity;
		/*Sorting the array from low to high*/
			for(i=0;i<CAPITAL_STOCK_VINTAGES.size;i++)
				{
	 			for(j=0;j<i;j++)
					{	
					if(CAPITAL_STOCK_VINTAGES.array[i].productivity<CAPITAL_STOCK_VINTAGES.array[j].productivity)
						{
						double x =CAPITAL_STOCK_VINTAGES.array[i].productivity;
						double y =CAPITAL_STOCK_VINTAGES.array[i].amount;
						CAPITAL_STOCK_VINTAGES.array[i].productivity= CAPITAL_STOCK_VINTAGES.array[j].productivity;
						CAPITAL_STOCK_VINTAGES.array[i].amount= CAPITAL_STOCK_VINTAGES.array[j].amount;
						CAPITAL_STOCK_VINTAGES.array[j].productivity=x;
						CAPITAL_STOCK_VINTAGES.array[j].amount=y;
						}
					}
				}
		}	

		/*Comute the total productivity regardless if employed or idle*/
		if(TOTAL_UNITS_CAPITAL_STOCK>0.0)
			TOTAL_PRODUCTIVITY_CAPITAL_STOCK = EFFECTIVE_CAPITAL_STOCK / TOTAL_UNITS_CAPITAL_STOCK;

	         

        /*Computing the capital bill*/

		/*Distinction of cases: if subsidies for best practice technology are switched on and the purchased vintage is the best vintage available:*/

		if(POLICY_EXP_BEST_TECHNOLOGY_SUBSIDY==1 && abs_double(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity - TECHNOLOGICAL_FRONTIER)<1e-5)
		{
        CAPITAL_COSTS += capital_good_delivery_message
        ->capital_good_delivery_volume* TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price;
        capital_good_price = capital_good_delivery_message->capital_good_price*(1-SUBSIDY_PCT);
        capital_good_delivery_volume = capital_good_delivery_message->capital_good_delivery_volume;
		SUBSIDY_PAYMENT += capital_good_delivery_volume* TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price*SUBSIDY_PCT;
	
        }else
		{
   			CAPITAL_COSTS += capital_good_delivery_message
        		->capital_good_delivery_volume* TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price;

	       	capital_good_price = capital_good_delivery_message->capital_good_price;
	        capital_good_delivery_volume = capital_good_delivery_message->capital_good_delivery_volume;

			

		}
    FINISH_CAPITAL_GOOD_DELIVERY_MESSAGE_LOOP

        if(CAPITAL_COSTS>0.0)
        {
        add_financing_capital(&CAPITAL_FINANCING,(CAPITAL_COSTS - SUBSIDY_PAYMENT)/CONST_INSTALLMENT_PERIODS,CONST_INSTALLMENT_PERIODS);
        }

          if (PRINT_DEBUG_FILE_EXP1)
        {
            filename = malloc(40*sizeof(char));
            filename[0]=0;
            strcpy(filename, "its/firms_capital_goods.txt"); 
            file1 = fopen(filename,"a");
            fprintf(file1,"\n %d %d %f %f %f",DAY,ID,TOTAL_UNITS_CAPITAL_STOCK,capital_good_delivery_volume,capital_good_price);
            fclose(file1);
            free(filename);
        }
	#ifdef _DEBUG_MODE
        if (PRINT_DEBUG_PRODUCTION)
        { 
		  if(ID==ID_DEBUG_PROBE)
	        {
	            printf("\n\n Firm_receive_capital_goods ID: %d",ID);
    	        printf("\n\t TOTAL_UNITS_CAPITAL_STOCK: %f Delivery of new capital: %f price %f", TOTAL_UNITS_CAPITAL_STOCK,capital_good_delivery_volume,capital_good_price);
   		        printf("\n\t CAPITAL_COSTS: %f Installment periods: %d", CAPITAL_COSTS, CONST_INSTALLMENT_PERIODS);
			}
		}
        #endif

    return 0;
}





int Firm_execute_production()
{
	int i,e;

    
   
	if(PLANNED_PRODUCTION_QUANTITY != 0)
    {     
        double sum_already_used_vintages=0.0;
		double technology =0.0;
        PRODUCTION_QUANTITY=0.0;
		
		double temp_capital_amount = 0.0;
		int w = 0;
		double employee_usage = 0.0;

		//Workers learn individually.
		if(INDIVIDUAL_LEARNING == 1)
		{
			qsort(EMPLOYEES.array, EMPLOYEES.size, sizeof(employee),employee_list_rank_general_skills_function);
			qsort(EMPLOYEES.array, EMPLOYEES.size, sizeof(employee),employee_list_rank_specific_skills_function);
			// Store the specific skill before the learning process for wage setting in "performance pay" or to analyze the learning.
			for(e = 0; e < EMPLOYEES.size; e++)
			{
				EMPLOYEES.array[e].specific_skill_before_learning = EMPLOYEES.array[e].specific_skill;
			
			}
		}



for(i=CAPITAL_STOCK_VINTAGES.size-1;i>=0;i--)
		{    
			if(INDIVIDUAL_LEARNING == 0)
			{
				/*Here the production quantity is computed*/	
				PRODUCTION_QUANTITY+= min(CAPITAL_STOCK_VINTAGES.array[i].amount,max(0,NO_EMPLOYEES_PRODUCTION-sum_already_used_vintages))*min(CAPITAL_STOCK_VINTAGES.array[i].productivity,MEAN_SPECIFIC_SKILLS);

				/*Here we compute the productivity of the used capital stock. This is sent to workers thus the specific skills converges to this 		value*/
		
				technology += min(CAPITAL_STOCK_VINTAGES.array[i].amount,max(0,NO_EMPLOYEES_PRODUCTION-sum_already_used_vintages))*CAPITAL_STOCK_VINTAGES.array[i].productivity;

				/*Sum up the used vintages:*/
				sum_already_used_vintages+=min(CAPITAL_STOCK_VINTAGES.array[i].amount,max(0,NO_EMPLOYEES_PRODUCTION-sum_already_used_vintages));
			}
			else
			{
				// Amount of vintage type: CAPITAL_STOCK_VINTAGES.array[i]
				temp_capital_amount = CAPITAL_STOCK_VINTAGES.array[i].amount;

				// As long as capital of this type and employees are left. Start: w = 0	-> no employee worked yet.			
				while((temp_capital_amount > 1e-05) && (w < EMPLOYEES.size))
				{

					// Capital amount of vintage type is larger than 1. Need more than 1 worker to use this type of capital.
					if(temp_capital_amount >= (1 + 1e-05))
					{
						// Employee_usage is 0: Employee did not work yet.
						if(employee_usage < 1e-05)
						{			

							// One unit of capital and one unit of labor are used.
							PRODUCTION_QUANTITY+= min(CAPITAL_STOCK_VINTAGES.array[i].productivity,EMPLOYEES.array[w].specific_skill);
		
							technology += 1*CAPITAL_STOCK_VINTAGES.array[i].productivity;
							sum_already_used_vintages += 1;


							//Employee learns by using the type of capital if the productivity is higher than its specific skills.
							if(EMPLOYEES.array[w].specific_skill < CAPITAL_STOCK_VINTAGES.array[i].productivity)
							{
								EMPLOYEES.array[w].specific_skill = EMPLOYEES.array[w].specific_skill + 
								(CAPITAL_STOCK_VINTAGES.array[i].productivity - EMPLOYEES.array[w].specific_skill)*((1-pow(0.5,1/(20+0.25*(EMPLOYEES.array[w].general_skill-1)*(4-20)))));
							}
							
							//One unit of CAPITAL_STOCK_VINTAGES.array[i] was used. 
							temp_capital_amount -= 1;

							//The employees spent his whole working time on this machine. He cannot work more. 
							employee_usage = 1.0;

						}
						else// Employee_usage is bigger than 0 but smaller than 1: Employee worked on a different machine but the amount of this machine was smaller than zero.
						{

							// (1-employee_usage) units of capital and (1-employee_usage) units of labor are used.
							PRODUCTION_QUANTITY+= (1-employee_usage)*min(CAPITAL_STOCK_VINTAGES.array[i].productivity,EMPLOYEES.array[w].specific_skill);

							technology += (1-employee_usage)*CAPITAL_STOCK_VINTAGES.array[i].productivity;
							sum_already_used_vintages += (1-employee_usage);

							//Employee learns by using the type of capital if the productivity is higher than its specific skills.
							//But only the fraction (1-employee_usage) of his working time.
							if(EMPLOYEES.array[w].specific_skill < CAPITAL_STOCK_VINTAGES.array[i].productivity)
							{
								EMPLOYEES.array[w].specific_skill = EMPLOYEES.array[w].specific_skill + 
								(1-employee_usage)*(CAPITAL_STOCK_VINTAGES.array[i].productivity - EMPLOYEES.array[w].specific_skill)*((1-pow(0.5,1/(20+0.25*(EMPLOYEES.array[w].general_skill-1)*(4-20)))));
							}

							//(1-employee_usage) units of CAPITAL_STOCK_VINTAGES.array[i] was used. 
							temp_capital_amount -= (1-employee_usage);

							//The employees spent the fraction (1-employee_usage) of his working time on this machine. 
							//Now his working time is complete. He cannot work more. 
							employee_usage = 1.0;
						}
						
						// Employee_usage is 1: Employee worked and cannot work any longer.
						if(employee_usage > 1 - 1e-05)
						{
							// Next employee.
							w++;

							//Reset to zero for next worker.
							employee_usage = 0.0;
						}
					}
					else // Capital amount of vintage type is smaller 1.
					{
	
						// Employee_usage is 0: Employee did not work yet.
						if(employee_usage < 1e-05)
						{

							// temp_capital_amount units of capital and temp_capital_amount units of labor are used.
							PRODUCTION_QUANTITY+= temp_capital_amount*min(CAPITAL_STOCK_VINTAGES.array[i].productivity,EMPLOYEES.array[w].specific_skill);

							technology += temp_capital_amount*CAPITAL_STOCK_VINTAGES.array[i].productivity;
							sum_already_used_vintages += temp_capital_amount;

							//Employee learns by using the type of capital if the productivity is higher than its specific skills.
							//But only the fraction (temp_capital_amount < 1) of his working time.
							if(EMPLOYEES.array[w].specific_skill < CAPITAL_STOCK_VINTAGES.array[i].productivity)
							{
								EMPLOYEES.array[w].specific_skill = EMPLOYEES.array[w].specific_skill + 
								temp_capital_amount*(CAPITAL_STOCK_VINTAGES.array[i].productivity - EMPLOYEES.array[w].specific_skill)*((1-pow(0.5,1/(20+0.25*(EMPLOYEES.array[w].general_skill-1)*(4-20)))));
							}

							//The employees spent the fraction (temp_capital_amount < 1) of his working time on this machine. 
							//He has to work on a different machine in order to reach his full working time.
							employee_usage += temp_capital_amount;

							// Amount of vintage type is zero: CAPITAL_STOCK_VINTAGES.array[i]. Use next vintage
							temp_capital_amount = 0.0;							
						}
						else// Employee_usage is bigger than 0 but smaller than 1: Employee worked on a different machine but the amount of this machine was smaller than zero.
						{
							//Only a fraction temp_capital_amount < of CAPITAL_STOCK_VINTAGES.array[i] is left. 
							//But the fraction of working time of the actual worker is smaller
							if(temp_capital_amount >= (1-employee_usage))
							{
								// (1-employee_usage) units of capital and (1-employee_usage) units of labor are used.
								PRODUCTION_QUANTITY+= (1-employee_usage)*min(CAPITAL_STOCK_VINTAGES.array[i].productivity,EMPLOYEES.array[w].specific_skill);

								technology += (1-employee_usage)*CAPITAL_STOCK_VINTAGES.array[i].productivity;
								sum_already_used_vintages += (1-employee_usage);

								//Employee learns by using the type of capital if the productivity is higher than its specific skills.
								//But only the fraction (1-employee_usage) of his working time.
								if(EMPLOYEES.array[w].specific_skill < CAPITAL_STOCK_VINTAGES.array[i].productivity)
								{
									EMPLOYEES.array[w].specific_skill = EMPLOYEES.array[w].specific_skill + 
									(1-employee_usage)*(CAPITAL_STOCK_VINTAGES.array[i].productivity - EMPLOYEES.array[w].specific_skill)*((1-pow(0.5,1/(20+0.25*(EMPLOYEES.array[w].general_skill-1)*(4-20)))));
								}

								//(1-employee_usage) units of CAPITAL_STOCK_VINTAGES.array[i] was used.
								temp_capital_amount -= (1-employee_usage);

								//The employees spent the fraction (1-employee_usage) of his working time on this machine. 
								//Now his working time is complete. He cannot work more. 
								employee_usage = 1.0;

							}
							else//if(temp_capital_amount <= (1-employee_usage))
							{

								// temp_capital_amount units of capital and temp_capital_amount units of labor are used.
								PRODUCTION_QUANTITY+= temp_capital_amount*min(CAPITAL_STOCK_VINTAGES.array[i].productivity,EMPLOYEES.array[w].specific_skill);

								technology += temp_capital_amount*CAPITAL_STOCK_VINTAGES.array[i].productivity;
								sum_already_used_vintages += temp_capital_amount;

								//Employee learns by using the type of capital if the productivity is higher than its specific skills.
								//But only the fraction (temp_capital_amount < 1) of his working time.
								if(EMPLOYEES.array[w].specific_skill < CAPITAL_STOCK_VINTAGES.array[i].productivity)
								{
									EMPLOYEES.array[w].specific_skill = EMPLOYEES.array[w].specific_skill + 
									temp_capital_amount*(CAPITAL_STOCK_VINTAGES.array[i].productivity - EMPLOYEES.array[w].specific_skill)*((1-pow(0.5,1/(20+0.25*(EMPLOYEES.array[w].general_skill-1)*(4-20)))));
								}

								//The employees spent the fraction (temp_capital_amount < 1) of his working time on this machine. 
								//He has to work on a different machine in order to reach his full working time.
								employee_usage += temp_capital_amount;

								// Amount of vintage type is zero: CAPITAL_STOCK_VINTAGES.array[i]. Use next vintage
								temp_capital_amount = 0.0;

							}
						}

						// Employee_usage is 1: Employee worked.
						if(employee_usage > 1 - 1e-05)
						{

							// Next employee.
							w++;
							//Reset to zero for next employee.
							employee_usage = 0.0;
						}
					}
				}//end while
			}//end individual learning == 1
		}
	if(sum_already_used_vintages>0)
	{
	technology = technology/sum_already_used_vintages;
	TECHNOLOGY = technology;

	}
 	if(TOTAL_UNITS_CAPITAL_STOCK)
	{
		UTILIZATION_CAPACITY = sum_already_used_vintages/TOTAL_UNITS_CAPITAL_STOCK;
	}else
	{
		UTILIZATION_CAPACITY=0.0;
	}
    
    }
    else
    {
        PRODUCTION_QUANTITY=0.0;
		UTILIZATION_CAPACITY=0.0;
    }

	
	// For testing the goodness of the profit estimation:

	EXPECTED_OUTPUT_IN_CURRENT_MONTH = EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].output;
	EXPECTED_PROFIT_IN_CURRENT_MONTH = EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].earnings;
	EXPECTED_LABOR_COSTS_IN_CURRENT_MONTH = EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].labor_costs;
	EXPECTED_CAPITAL_COSTS_IN_CURRENT_MONTH = EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].capital_costs;
	EXPECTED_INTERESTS_IN_CURRENT_MONTH = EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].interest_payments;
	EXPECTED_WAGE_IN_CURRENT_MONTH =EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].wage;
	EXPECTED_MEAN_SPECIFIC_SKILLS_IN_CURRENT_MONTH =EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].mean_specific_skills;
	EXPECTED_AVERAGE_PRODUCTIVITY_IN_CURRENT_MONTH =EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].average_productivity;
	EXPECTED_INVESTMENT_NOMINAL_IN_CURRENT_MONTH =EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].investment_nominal;
	EXPECTED_ACTUAL_SOLD_QUANTITY_IN_CURRENT_MONTH = EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[COUNTER_MONTH_SINCE_LAST_PRICE_SETTING].sold_quantity;
    
    //Set actual production value that is retained  in memory during the month:
    OUTPUT = PRODUCTION_QUANTITY;
	// Increment the counter
	COUNTER_MONTH_SINCE_LAST_PRICE_SETTING++;

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_PRODUCTION)
    {
	  if(ID==ID_DEBUG_PROBE)
        {
        	printf("\n\n ID %d Firm_execute_production ID: %d Activity day: %d",DAY, ID,DAY_OF_MONTH_TO_ACT);
        	printf("\n\t PLANNED_PRODUCTION_QUANTITY: %f OUTPUT: %f",PLANNED_PRODUCTION_QUANTITY,OUTPUT);
		printf("\n\tUTILIZATION_CAPACITY: %f \t NO_EMPLOYEES_PRODUCTION: %d",UTILIZATION_CAPACITY,NO_EMPLOYEES_PRODUCTION);
		printf("\n\tNO_EMPLOYEES_INNOVATION %d \t NO_EMPLOYEES: %d",NO_EMPLOYEES_INNOVATION, NO_EMPLOYEES);
		}    
	}
    #endif
        
    TOTAL_SUPPLY = TOTAL_UNITS_LOCAL_INVENTORY + OUTPUT;
    
	/*Execute Product Innovation*/

	
	if(INNOVATION_FLAG==1)
	{
		
		
		INNOVATION_MONTH_COUNTER++;
		int random_no;
		double random_number;
		CUM_PERSON_MONTHS += NO_EMPLOYEES_INNOVATION;



		 #ifdef _DEBUG_MODE    
    if(PRINT_DEBUG_MARKET_RESEARCH)
    {
	  if(ID==ID_DEBUG_PROBE)
        {
        	printf("\n\n ID %d Firm_execute_production ID: ",ID);
        		printf(" REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT %d    INNOVATION_MONTH_COUNTER %d    CUM_PERSON_MONTHS %d\n",REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT,INNOVATION_MONTH_COUNTER,CUM_PERSON_MONTHS);
		}    
	}
    #endif


	if(INNOVATION_SWITCHED_ON==1)
	{
		double max_person_months;
		
		max_person_months = 12*MAX_NO_EMPLOYEES_PRODUCT_INNOVATION; 
		

	
		if(INNOVATION_MONTH_COUNTER==12)
		{

			REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT--;

				
		
			ACTUAL_R_AND_D_SUCCESS_PROBABILITY =( CUM_PERSON_MONTHS)/(1.0*max_person_months+12.0);


												
					
					random_no = random_int(0,100);
					random_number = random_no/100.0;
					if(random_number<ACTUAL_R_AND_D_SUCCESS_PROBABILITY)
					{
						INTERMEDIATE_QUALITY+=QUALITY_CHANGE; 
					}else
					{
						INTERMEDIATE_QUALITY-=QUALITY_CHANGE;
					}



			#ifdef _DEBUG_MODE    
 			if (PRINT_DEBUG_MARKET_RESEARCH)
  			{
			    if(ID==ID_DEBUG_PROBE )
                {
		    
					printf(" ACTUAL_R_AND_D_SUCCESS_PROBABILITY %f \n",ACTUAL_R_AND_D_SUCCESS_PROBABILITY );
				}

    		}
    		#endif

		}



			#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE )
            {
		    
			printf( "R_AND_D_INVESTMENTS_PER_MONTH %f   INTERMEDIATE_QUALITY %f \n",R_AND_D_INVESTMENTS_PER_MONTH,INTERMEDIATE_QUALITY );
		}

    }
    #endif


	}
	}

return 0;
}



/** \fn Firm_calc_pay_costs()
 * \brief In this function the firm receives the purchased investment goods and pays the goods and  the wage bill. Additionally, the new mean wage and tthe new average specific skill level is     computed. */
int Firm_calc_pay_costs()
{
     FILE *file1;
     char *filename;    
    int i;
    
        /*Pay capital costs*/

        add_pay_capital_goods_message(ID,CAPITAL_COSTS);
        FIRM_OUTFLOWS_CALENDAR.capital_costs = CAPITAL_COSTS;
        

        LABOUR_COSTS=0.0;
		LABOUR_COSTS_PRODUCTION = 0.0;

		// Pay labour production costs
        for(i=0; i<EMPLOYEES.size;i++)
        {
            LABOUR_COSTS_PRODUCTION += EMPLOYEES.array[i].wage;

            add_wage_payment_message(ID,
            EMPLOYEES.array[i].id,EMPLOYEES.array[i].wage,
            TECHNOLOGY,MEAN_SPECIFIC_SKILLS,0,EMPLOYEES.array[i].specific_skill);
              
        }

		//Pay R and D costs
		
		R_AND_D_INVESTMENTS_PER_MONTH = 0.0;
	
		for(i=0; i<R_AND_D_EMPLOYEES.size;i++)
        {
            R_AND_D_INVESTMENTS_PER_MONTH += R_AND_D_EMPLOYEES.array[i].wage;

            add_wage_payment_message(ID,
            EMPLOYEES.array[i].id,R_AND_D_EMPLOYEES.array[i].wage,
            TECHNOLOGY,MEAN_SPECIFIC_SKILLS,0,0.0);
              
        }

		LABOUR_COSTS_INNOVATION = R_AND_D_INVESTMENTS_PER_MONTH;

        LABOUR_COSTS = LABOUR_COSTS_PRODUCTION + LABOUR_COSTS_INNOVATION; 
        FIRM_OUTFLOWS_CALENDAR.labour_costs = LABOUR_COSTS;
        
   		/*Calculate the unit costs and total costs*/
        if(PRODUCTION_QUANTITY!=0 )
        {
            
            CALC_CAPITAL_COSTS = 0;
        for(i = 0; i<CAPITAL_FINANCING.size;i++) 
            {
                if(CAPITAL_FINANCING.array[i].nr_periods_before_repayment==0)
                {
                    remove_financing_capital(&CAPITAL_FINANCING,i);
                    i--;
                }else
                {
                CAPITAL_FINANCING.array[i].nr_periods_before_repayment--;
                CALC_CAPITAL_COSTS+= CAPITAL_FINANCING.array[i].financing_per_month;
                }
                

            } 
            
			CUM_R_D_INVESTMENTS +=LABOUR_COSTS_INNOVATION;
        
            UNIT_COSTS=(LABOUR_COSTS_PRODUCTION + LABOUR_COSTS_INNOVATION  +CALC_CAPITAL_COSTS + TOTAL_INTEREST_PAYMENT) / PRODUCTION_QUANTITY;
    
            if(PRICE_LAST_MONTH<1e-5 )
		    {	
            PRICE_LAST_MONTH = PRICE;
            PRICE = LABOUR_COSTS_PRODUCTION/(PRODUCTION_QUANTITY)*(1 + MARK_UP);
            }

		ACTUAL_MARK_UP = (PRICE - UNIT_COSTS)/UNIT_COSTS;

            if (PRINT_DEBUG_FILE_EXP1)
             {
             filename = malloc(40*sizeof(char));
             filename[0]=0;
             strcpy(filename, "its/firms_pricing.txt");      
             file1 = fopen(filename,"a");
             fprintf(file1,"\n %d %d %f %f %f",DAY,ID,LABOUR_COSTS,CALC_CAPITAL_COSTS,TOTAL_INTEREST_PAYMENT);
             fprintf(file1," %f %f %f",PRODUCTION_QUANTITY,UNIT_COSTS,PRICE);
             fclose(file1);
             free(filename);

              }    

            
            
        }


        PRODUCTION_COSTS = CAPITAL_COSTS - SUBSIDY_PAYMENT + LABOUR_COSTS;
        CALC_PRODUCTION_COSTS= LABOUR_COSTS_PRODUCTION+ CALC_CAPITAL_COSTS;

        PAYMENT_ACCOUNT -= PRODUCTION_COSTS;
		
    remove_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,0);
    add_double(&LAST_PLANNED_PRODUCTION_QUANTITIES,PLANNED_PRODUCTION_QUANTITY); 

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_PRODUCTION)
    {
		if(ID==ID_DEBUG_PROBE)
        {
        	printf("\n\n IT %d Firm_calc_pay_costs ID: %d",DAY,ID);
        	printf("\n\t CAPITAL_COSTS: %f LABOUR_COSTS: %f LABOUR_COSTS_PROUCTION %f",CAPITAL_COSTS,LABOUR_COSTS,LABOUR_COSTS_PRODUCTION);
        	printf("\n\t UNIT_COSTS: %f PRICE_LAST_MONTH: %f PRICE: %f  ACTUAL_MARK_UP: %f",UNIT_COSTS,PRICE_LAST_MONTH,PRICE, ACTUAL_MARK_UP);
		printf("\n\t PRODUCTION_COSTS: %f \t PLANNED_PRODUCTION_COSTS: %f",PRODUCTION_COSTS,PLANNED_PRODUCTION_COSTS);

			printf("\n\t Mean Wage: %f \t Wage offer %f",MEAN_WAGE,WAGE_OFFER);
        }
    }   
    #endif
        
    return 0;
}


/** \fn Firm_send_goods_to_mall()
 * \brief Here the firms send the produced goods to the malls. If the realized output is less than  the intended one, then the malls are only delivered with a proportional share of their      plannded delivery volumes. */

int Firm_send_goods_to_mall()
{   
    
		int i,j;        
		double delivery_volume=0;

        for(i=0; i<PLANNED_DELIVERY_VOLUME.size; i++)
        {
            delivery_volume+=PLANNED_DELIVERY_VOLUME.array[i].quantity;

        }


        for(i = 0; i < PLANNED_DELIVERY_VOLUME.size; i++)
        {

            for(j = 0; j < DELIVERY_VOLUME.size; j++)
            {
                if(DELIVERY_VOLUME.array[j].mall_id == 
                PLANNED_DELIVERY_VOLUME.array[i].mall_id)
                {
                    /*If planned prod vol > realized prod vol -> curtain the delivery vol*/
                    if(delivery_volume>PRODUCTION_QUANTITY)
                    {
                        DELIVERY_VOLUME.array[j].quantity =
                        PRODUCTION_QUANTITY / delivery_volume * PLANNED_DELIVERY_VOLUME.array[i].quantity;
                    
                    }else /*otherwise planned = realized del vol*/
                    
                    if(PRODUCTION_QUANTITY > delivery_volume &&
                    delivery_volume !=0)
                    {
                        DELIVERY_VOLUME.array[j].quantity = PRODUCTION_QUANTITY / delivery_volume*PLANNED_DELIVERY_VOLUME.array[i].quantity;

                    }else 
                    if(PRODUCTION_QUANTITY > delivery_volume &&
                    delivery_volume ==0)
                    {   

                        DELIVERY_VOLUME.array[j].quantity = 
                        PRODUCTION_QUANTITY/(DELIVERY_VOLUME.size);
                    }
                    else
                    {
                        DELIVERY_VOLUME.array[j].quantity = 
                        PLANNED_DELIVERY_VOLUME.array[i].quantity;
                    }
        
                    DELIVERY_VOLUME.array[j].quality=
                    PLANNED_DELIVERY_VOLUME.array[j].quality;

                    DELIVERY_VOLUME.array[j].price=
                    PLANNED_DELIVERY_VOLUME.array[j].price;
            
            
                    add_update_mall_stock_message(
                    DELIVERY_VOLUME.array[j].mall_id,ID,
                    DELIVERY_VOLUME.array[j].quantity,QUALITY,PRICE,PRICE_LAST_MONTH);
            
                }
            }
        }


	
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_PRODUCTION)
    {
		if(ID==ID_DEBUG_PROBE)
        {
        	printf("\n\n IT %d Firm_send_goods_to_mall ID: %d",DAY,ID);
			for(i=0;i<DELIVERY_VOLUME.size;i++)
			{
        		printf("\n\t Delivery volume to mall id %d \t %f,\t pĺanned delivery volume: %f",DELIVERY_VOLUME.array[i].mall_id, DELIVERY_VOLUME.array[i].quantity,PLANNED_DELIVERY_VOLUME.array[i].quantity);
			}        
		}
    }   
    #endif
    
    
    return 0;
}

/** \fn Firm_calc_revenue()
 * \brief Here the firms calc the revenues and profits and then distribute the dividends to households 
 */
int Firm_calc_revenue()
{
    FILE *file1;
     char *filename;
    REVENUE_PER_DAY=0.0;
    TOTAL_SOLD_QUANTITY=0.0;
    int i;

    /*calc the daily revenue and sum up the monthly revenue*/
    START_SALES_MESSAGE_LOOP
    
        for(i=0; i< SOLD_QUANTITIES.size; i++)
        {
            if(sales_message->mall_id ==  SOLD_QUANTITIES.array[i].mall_id)
            {
                
                
                SOLD_QUANTITIES.array[i].stock_empty = 
                               sales_message->stock_empty;
                
          		
				if(PRICE>1e-6)
				{
                SOLD_QUANTITIES.array[i].sold_quantity += 
                sales_message->revenue/PRICE;
				}else{
					SOLD_QUANTITIES.array[i].sold_quantity +=0.0;
				}
            
                REVENUE_PER_DAY += sales_message->revenue;
        
                CUM_REVENUE += sales_message->revenue;
    
				if(PRICE>1e-6)
				{
                	TOTAL_SOLD_QUANTITY+=sales_message->revenue/PRICE;
				}else{
					TOTAL_SOLD_QUANTITY=0.0;
				}
            }   
        }
        

        //Update mall stocks
        for(i=0; i< CURRENT_MALL_STOCKS.size; i++)
        {
            if(sales_message->mall_id ==  CURRENT_MALL_STOCKS.array[i].mall_id)
            {
                CURRENT_MALL_STOCKS.array[i].current_stock= sales_message->current_stock;
            }
        }
    
    FINISH_SALES_MESSAGE_LOOP
    
        if (PRINT_DEBUG_FILE_EXP1)
    {
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/firms_goods_market.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %d %f %f",DAY,ID,TOTAL_SOLD_QUANTITY,PRICE);
        fclose(file1);
        free(filename);
    }    
    /*GENUA*/
    /*add_bank_account_update_message(BANK_ID, PAYMENT_ACCOUNT);*/
    //Not needed here: there is a function after this called Firm_send_payments_to_bank
    
    PAYMENT_ACCOUNT += REVENUE_PER_DAY;
    FIRM_INFLOWS_CALENDAR.cum_revenue += REVENUE_PER_DAY;
    
    
	//Resetting the calendar month counter
	if(DAY%MONTH == 1)
	{
		
		SOLD_QUANTITY_IN_LAST_CALENDAR_MONTH =  SOLD_QUANTITY_IN_CALENDAR_MONTH ;
		  remove_double(&LAST_SOLD_QUANTITIES,0);
				    add_double(&LAST_SOLD_QUANTITIES,SOLD_QUANTITY_IN_CALENDAR_MONTH); 
		SOLD_QUANTITY_IN_CALENDAR_MONTH = 0;
		 
	}
	/*The monthly sales statistics*/
    CUM_TOTAL_SOLD_QUANTITY += TOTAL_SOLD_QUANTITY; 
    SOLD_QUANTITY_IN_CALENDAR_MONTH+= TOTAL_SOLD_QUANTITY;
        
    /*On a monthly base the earnings are computed and dividends distributed*/
    //See the functions for financial management
    return 0;       
    
}
int Firm_compute_sales_statistics()
{

	int i, j, k;

	if(PRICE_JUST_SET_FLAG ==0 )
	{
    	/*The sales per mall must be stored for the inventory rule*/
            
        int remove_index;
   
        for(j=0; j < MALLS_SALES_STATISTICS.size;j++)
        {
			
            for(k = 0; k < MALLS_SALES_STATISTICS.array[j].sales.size; k++)
            {
					
                if(MALLS_SALES_STATISTICS.array[j].sales.array[k].period== FIRM_PLANNING_HORIZON)
                {       
                remove_index = k;
                remove_data_type_sales(&(MALLS_SALES_STATISTICS.array[j].sales), remove_index);
                k--;
                }else
                {
                    MALLS_SALES_STATISTICS.array[j].sales.array[k].period++;
                    
                }
            }
        }

		// The the last 12 monthly revenues 
		if(LAST_REVENUES.size==12)
		{
			remove_double(&LAST_REVENUES,0);
		}
		
		add_double(&LAST_REVENUES,CUM_REVENUE);
                                         
                
        for(i=0; i< SOLD_QUANTITIES.size;i++)
               {
                   for(j=0; j<MALLS_SALES_STATISTICS.size; j++)
                   {
                       if(MALLS_SALES_STATISTICS.array[j].mall_id == SOLD_QUANTITIES.array[i].mall_id)
                       {
                    
                       	if(SOLD_QUANTITIES.array[i].stock_empty==0)
                        {
           	               add_data_type_sales(&(MALLS_SALES_STATISTICS.array[j].sales), 1 , 
                           SOLD_QUANTITIES.array[i].sold_quantity);           	            
           	         }
           	         else
           	         {
							//test:  for test market no additional production in case of sold out malls
						 add_data_type_sales(&(MALLS_SALES_STATISTICS.array[j].sales), 1 , 
                          SOLD_QUANTITIES.array[i].sold_quantity);
						
           	         }
            	         SOLD_QUANTITIES.array[i].sold_quantity=0;
                       SOLD_QUANTITIES.array[i].stock_empty=0;
                       }
                   }
               }
           
    }else
	{ 
         for(i=0; i< SOLD_QUANTITIES.size;i++)
         {
	        SOLD_QUANTITIES.array[i].sold_quantity=0;
            SOLD_QUANTITIES.array[i].stock_empty=0;
		
			//reset price setting flag
			PRICE_JUST_SET_FLAG = 0;
		}
	}     
    
    return 0;
}


/** \fn Firm_update_specific_skills_of_workers()()
 * \brief   Because the specific skills of workers have changed the firms update the specific skill levels of the workers.
 */
int Firm_update_specific_skills_of_workers()
{

	int flag =0;
	int i;

    START_SPECIFIC_SKILL_UPDATE_MESSAGE_LOOP
		
		flag=0;        

        for(i=0; i<EMPLOYEES.size;i++)
        {
            if(specific_skill_update_message->id==EMPLOYEES.array[i].id)
            {
                EMPLOYEES.array[i].specific_skill=
                specific_skill_update_message->specific_skills;
				EMPLOYEES.array[i].general_skill= 
					 specific_skill_update_message->general_skills;

				flag=1;
				break;
                
            }
        }
		
		if(flag==0)
		{
  			for(i=0; i<R_AND_D_EMPLOYEES.size;i++)
        	{
        	    if(specific_skill_update_message->id==R_AND_D_EMPLOYEES.array[i].id)
         	    {
              	 	R_AND_D_EMPLOYEES.array[i].specific_skill=
                	specific_skill_update_message->specific_skills;
				
					R_AND_D_EMPLOYEES.array[i].general_skill= 
					 specific_skill_update_message->general_skills;
					break;
             	}
        	}
		}
        
    FINISH_SPECIFIC_SKILL_UPDATE_MESSAGE_LOOP
    
    return 0;
}


