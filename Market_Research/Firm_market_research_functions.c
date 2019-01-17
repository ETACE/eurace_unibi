#include "../header.h"
#include "../Firm_agent_header.h"
#include "../my_library_header.h"



int Firm_check_fiancial_situation_for_product_innovation(int year)
{

int i,j,t, L_max,flag, index_price, Y;
int no_employees_product_innovation_fundable;
//Check Financial situation:

double equity, assets, total_debt;
double estimated_fix_costs, estimated_variable_costs, estimated_r_and_d_expenditures;
double total_value_capital_stock;
double monthly_wage_growth;
double estimated_mean_wage,no_employees,payment_account,earnings, estimated_mean_wage_r_and_d;
double sum_interest_payments, average_productivity ,eff_productivity,used_capital_stock,sum_output,pot_output,capital_stock_depreciation_units,installment_payment;
double interest_payments,investment_nominal,planned_output,labour_demand,realized_output,debt_needed,mean_specific_skills;
double actual_sales_estimation, buffer, combined_variance_demand_function, expected_sales, current_stock, critical_stock;

monthly_wage_growth = 1+VARIABLES_CHANGE.productivity_progress;

no_employees_product_innovation_fundable=0;
	


for(L_max=MAX_NO_EMPLOYEES_PRODUCT_INNOVATION; L_max>=0;L_max--)
{		
	adt_capital_stock_vintages_array capital_stock;
	init_adt_capital_stock_vintages_array(&capital_stock);
	
	financing_capital_array temp_capital_financing;
	init_financing_capital_array(&temp_capital_financing);
	
	debt_item_array temp_loans;
	init_debt_item_array(&temp_loans);
		
	flag=0;
	
	for(i=0;i<CAPITAL_STOCK_VINTAGES.size;i++)	
	{
			add_adt_capital_stock_vintages(&capital_stock, CAPITAL_STOCK_VINTAGES.array[i].
				amount,CAPITAL_STOCK_VINTAGES.array[i].productivity);
	}
	
	for(i=0;i<CAPITAL_FINANCING.size;i++)
	{
			add_financing_capital(&temp_capital_financing,CAPITAL_FINANCING.array[i].financing_per_month,
				CAPITAL_FINANCING.array[i].nr_periods_before_repayment);
	}

	for(i=0;i<LOANS.size;i++)
	{
		add_debt_item(&temp_loans, 0,LOANS.array[i].loan_value,LOANS.array[i].interest_rate,LOANS.array[i].installment_amount
			,0,0,0,LOANS.array[i].nr_periods_before_repayment);
	}
	
	//Temporary variables to store...
	mean_specific_skills = MEAN_SPECIFIC_SKILLS;
	estimated_mean_wage = MEAN_WAGE;
	estimated_mean_wage_r_and_d = MEAN_WAGE_R_AND_D;		
	no_employees= NO_EMPLOYEES_PRODUCTION;
	payment_account = PAYMENT_ACCOUNT;
	earnings= EARNINGS;

	buffer = TOTAL_BUFFER;

		
	for(Y=0; Y <year-1;Y++)
	{

		if(Y==0)
		{
			for(i = 0; i < MARKET_RESEARCH_DATA_PRICING.size;i++)
			{
				if(MARKET_RESEARCH_DATA_PRICING.array[i].price== EXPECTED_PRICE_CHOICES.array[Y])
				{
					index_price = i;
					combined_variance_demand_function = pow(MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array
						[Y].probability,2)*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance + 
						pow(LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept+Y*12*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor,2)*DEMAND_FUNCTION_PRICING.variance/
						(1.0*pow	(ACTUAL_SAMPLE_SIZE,2))+DEMAND_FUNCTION_PRICING.variance/(1.0*pow(ACTUAL_SAMPLE_SIZE,2))	
						*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance;
					break;
				}
			}
		}else
		{
			for(i = 0; i < MARKET_RESEARCH_DATA_PRICING.size;i++)
			{
				if(MARKET_RESEARCH_DATA_PRICING.array[i].price== EXPECTED_PRICE_CHOICES.array[Y])
				{
					
				
					for(j=0;j< DEMAND_FUNCTIONS_PRODUCT_INNOVATION.size;j++)
					{
						if(Y== DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[j].year && DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[j].quality ==QUALITY)
						{
							index_price = i;
		
							combined_variance_demand_function = pow(MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array
								[Y].probability,2)*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance + 
								pow(LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept,2)*DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[j].variance/
								(1.0*pow	(ACTUAL_SAMPLE_SIZE,2))+DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[j].variance/(1.0*pow(ACTUAL_SAMPLE_SIZE,2))*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance;
								break;
						}
					}
				}	
			}	
		}

		current_stock= buffer;

		buffer = QUANTIL_NORMAL_DISTRIBUTION*pow(combined_variance_demand_function ,0.5);


		for(t=0;t<12;t++)
		{
			average_productivity=0.0;
			eff_productivity=0.0;
			used_capital_stock=0.0;
			sum_output=0;
			pot_output=0;
			capital_stock_depreciation_units=0.0;
			installment_payment=0.0;
			interest_payments=0.0;
			investment_nominal=0.0;
			sum_interest_payments=0.0;
	

				//Expected sales are linear combination of market shares at the beginning and the end of the year times market size		
				expected_sales = ((LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept 
					+ (1+LAST_MARKET_SIZES.array[0].market_sizes.size+Y*12+t)*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor)
					)*((t/11.0)*MARKET_RESEARCH_DATA_PRICING.array[index_price].estimated_values.array[Y+1].probability+((11-t)/11.0)*MARKET_RESEARCH_DATA_PRICING.array[index_price].estimated_values.array[Y].probability);
				
				//Set critical stock: Expected sales plus buffer
				critical_stock = expected_sales + buffer;

				//Set output: Difference of critical and current stock 
				planned_output = max(critical_stock - current_stock, 0);





			//Fix costs:
		
			// Capital costs for sunk investments:
	
			estimated_fix_costs=0;
	
			for(j=0; j< temp_capital_financing.size;j++)
			{
				if(temp_capital_financing.array[j].nr_periods_before_repayment==0)
      	     	{
             		remove_financing_capital(&temp_capital_financing,j);
       	       		j--;
              	}else
                {
                	temp_capital_financing.array[j].nr_periods_before_repayment--;
            	    estimated_fix_costs+= temp_capital_financing.array[j].financing_per_month;
            	}
			}


			//Interest payments:
			for(j=0;j<temp_loans.size;j++)
			{
				if(temp_loans.array[j].nr_periods_before_repayment>0)
				{
					interest_payments=temp_loans.array[j].loan_value* temp_loans.array[j].interest_rate/12.0;
					estimated_fix_costs+=interest_payments;
					sum_interest_payments+=interest_payments;
					installment_payment += temp_loans.array[j].installment_amount;
					temp_loans.array[j].loan_value-=temp_loans.array[j].installment_amount;
					temp_loans.array[j].nr_periods_before_repayment--;
				}else
				{
					remove_debt_item(&temp_loans,j);
					j--;
							
				}
			}	
	
			//Compute input factor needs
			for(j=capital_stock.size-1;j>=0;j--)
			{
				capital_stock.array[j].amount= capital_stock.array[j].amount*(1-DEPRECIATION_RATE);
				capital_stock_depreciation_units+=capital_stock.array[j].amount*DEPRECIATION_RATE;
			
				if(sum_output < planned_output)
				{
					pot_output += min(mean_specific_skills,capital_stock.array[j].productivity)*capital_stock.array[j].amount;
	
					if(pot_output>planned_output)
					{
						double sum_cap_selected_vintage=(planned_output - sum_output)
									/min(mean_specific_skills,capital_stock.array[j].productivity);
						sum_output += (planned_output - sum_output);
						used_capital_stock+=sum_cap_selected_vintage;
						average_productivity += capital_stock.array[j].productivity*sum_cap_selected_vintage;
						eff_productivity+= min(capital_stock.array[j].productivity,mean_specific_skills)*sum_cap_selected_vintage;
					}else
					{
						used_capital_stock+=capital_stock.array[j].amount;		
						sum_output += min(mean_specific_skills,capital_stock.array[j].productivity)*capital_stock.array[j].amount;
						average_productivity += capital_stock.array[j].productivity*capital_stock.array[j].amount;
						eff_productivity+= min(capital_stock.array[j].productivity,mean_specific_skills)*capital_stock.array[j].amount;
					}
				}
			}
			if(sum_output < planned_output)
			{
				double inv;
				inv = (planned_output - sum_output)/ min(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity,mean_specific_skills);
		
				inv = min(inv, INV_INERTIA*capital_stock_depreciation_units);
				used_capital_stock+=inv;
				average_productivity += TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity*inv;
				eff_productivity+= min(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity,mean_specific_skills)*inv;
							
				for(j=0; j<capital_stock.size;j++)
				{
					if(abs_double(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity-capital_stock.array[j].productivity)<1e-5)
					{
						capital_stock.array[j].amount+=inv;
						break;
					}else
					{
						if(j==capital_stock.size-1)
						{
							add_adt_capital_stock_vintages(&capital_stock,inv,TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity);
						}
					}
				}
					/* If subsidies for best vintage are switched on: reduce the effective price
					 for best practice technology*/									
				if(POLICY_EXP_BEST_TECHNOLOGY_SUBSIDY==1 && abs_double(TECHNOLOGY_VINTAGES.array[i].productivity - TECHNOLOGICAL_FRONTIER)<1e-5)
				{
					investment_nominal=inv*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price*(1-SUBSIDY_PCT);
				}else
				{	
					investment_nominal=inv*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price;
				}
		
			add_financing_capital(&temp_capital_financing,investment_nominal/CONST_INSTALLMENT_PERIODS, CONST_INSTALLMENT_PERIODS);
							
			}
	
			total_value_capital_stock=0.0;
		
			for(i=0;i<TECHNOLOGY_VINTAGES.size;i++)
			{
				for(j=0;j<capital_stock.size;j++)
				{
					if(abs_double(capital_stock.array[j].productivity-TECHNOLOGY_VINTAGES.array[i].productivity)<1e-5)
					{
						total_value_capital_stock+=TECHNOLOGY_VINTAGES.array[i].price*capital_stock.array[j].amount;
					}
				}
			}
	
	
			labour_demand = used_capital_stock;
			if(used_capital_stock>1e-5)
			{
				average_productivity = average_productivity / used_capital_stock;
				eff_productivity = eff_productivity /used_capital_stock;
			}else
			{
				average_productivity = TECHNOLOGY;
				eff_productivity = TECHNOLOGY;

			}
	
			realized_output= used_capital_stock*eff_productivity;
	
			current_stock += realized_output;
			//Compute mean wage:	
			
			if(labour_demand>no_employees)
			{
				estimated_mean_wage =no_employees/(1.0*labour_demand) * estimated_mean_wage  
					+ (labour_demand - no_employees)/(1.0*labour_demand)*WAGE_OFFER*min(average_productivity,mean_specific_skills );
	
			}
	
			//Compute variable costs
			if(realized_output>1e-5)
			{
				estimated_variable_costs = 	(labour_demand*estimated_mean_wage + investment_nominal/CONST_INSTALLMENT_PERIODS)/realized_output;
			}
			else
			{
				estimated_variable_costs = 0.0;
			}


			estimated_r_and_d_expenditures = estimated_mean_wage_r_and_d * L_max;
		
			//Check financing:
		
			payment_account= payment_account - labour_demand*estimated_mean_wage - investment_nominal -
						sum_interest_payments - installment_payment -max(0,earnings)*TAX_RATE_CORPORATE - max(0,earnings)*(1-TAX_RATE_CORPORATE)
						*CONST_DIVIDEND_EARNINGS_RATIO;
	
			//Check if additional loans are necessary
			debt_needed = (-1)*min(payment_account,0);
				
			if(debt_needed>1e-5)
			{
				add_debt_item(&temp_loans, 0,debt_needed,LAST_INTEREST_RATE_FOR_LOANS,debt_needed/CONST_INSTALLMENT_PERIODS,0,0,0,CONST_INSTALLMENT_PERIODS);
			}
			
			payment_account+=debt_needed;
	
			total_debt = 0.0;
	
			for(i=0;i<temp_loans.size;i++)
			{
				total_debt+= temp_loans.array[i].loan_value;
			}


			actual_sales_estimation = min(current_stock,expected_sales);

			//Update stocks and payment account
			payment_account+= actual_sales_estimation*EXPECTED_PRICE_CHOICES.array[Y];

			current_stock -=actual_sales_estimation;
			
			//Compute balance sheet
			assets= total_value_capital_stock + payment_account;
	
			equity = assets - total_debt;

				//Print debug:
			#ifdef _DEBUG_MODE    
   			if (PRINT_DEBUG_MARKET_RESEARCH)
			{
   			if(ID==ID_DEBUG_PROBE)
			{
   			
				
				//printf("no_employees: %d assets %f total_debt %f equity %f total_value_capital_stock %f payment_account %f \n",L_max, assets, total_debt, equity, total_value_capital_stock, payment_account);
			
		
			}	
		}
		#endif

	
			if(equity <0.0)
			{
				flag=1;
				break;
			}


			//Compute earnings
			earnings= actual_sales_estimation* (EXPECTED_PRICE_CHOICES.array[Y] - estimated_variable_costs)  - estimated_fix_costs;
	
		
	
			//Update mean wage:
		
			estimated_mean_wage = estimated_mean_wage*monthly_wage_growth;
			estimated_mean_wage_r_and_d = estimated_mean_wage_r_and_d *monthly_wage_growth ;
		
			no_employees  = labour_demand;
	
			// Skill update:
	
			if(SKILL_UPDATE_ACC_TO_FORMULA==1)
			{
    	  		/*Update the specific skill: depends on the actual specific skill, 
    	    	the gap between the actual specific skills and the actual productivity of the employer,
    	    	and the general skill which determines the speed of closing the this gap.*/
    	   		mean_specific_skills = max(mean_specific_skills, mean_specific_skills+ max(average_productivity-mean_specific_skills,0)
							*((1-pow(0.5,1/(20+0.25*(AVERAGE_G_SKILL-1)*(4-20))))));
			}else
			{
	 		 /*Update the specific skill: depends on the actual specific skill, 
    	   		the gap between the actual specific skills and the actual productivity of
				the employer. The rate is predetermined.*/

    	  			mean_specific_skills = max(mean_specific_skills, mean_specific_skills+ max(average_productivity-mean_specific_skills,0)		     
					*AVERAGE_ADAPTATION_SPEED_SPECIFIC_SKILLS);
				
							
			}
	
		}
	
	}	
	
	//Free memory
	free_adt_capital_stock_vintages_array(&capital_stock);			
	free_financing_capital_array(&temp_capital_financing);
	free_debt_item_array(&temp_loans);

	if(flag==0)
	{
		no_employees_product_innovation_fundable = L_max;
		break;
	}
}


	return no_employees_product_innovation_fundable;
}





/** \fn Firm_draw_sample
 */
int Firm_set_market_research_data_pricing()
{

	int i,j,no_considered_prices;


	//Compute yearly growth rates of price index and quality index


	//1. Price index
	if(VARIABLES_LAST_YEAR.array[0].price_index>1e-5)
	{
		VARIABLES_CHANGE.price_index = (CURRENT_PRICE_INDEX - VARIABLES_LAST_YEAR.array[0].price_index)/VARIABLES_LAST_YEAR.array[0].price_index;
	}else{
		VARIABLES_CHANGE.price_index=0.0;
	}
	//2. Quality Index
	if(VARIABLES_LAST_YEAR.array[0].quality_index>1e-5)
	{
		VARIABLES_CHANGE.quality_index = (CURRENT_QUALITY_INDEX - VARIABLES_LAST_YEAR.array[0].quality_index)/VARIABLES_LAST_YEAR.array[0].quality_index;
	}else{
		VARIABLES_CHANGE.quality_index=0.0;
	}
	
	//5. Productivity Progress
	VARIABLES_CHANGE.productivity_progress=0;


	for(i =0; i<VARIABLES_LAST_YEAR.size; i++ )
	{
		
		VARIABLES_CHANGE.productivity_progress+=VARIABLES_LAST_YEAR.array[i].productivity_progress;
	
	}
	if(VARIABLES_LAST_YEAR.size>0)
	{
		  VARIABLES_CHANGE.productivity_progress=VARIABLES_CHANGE.productivity_progress/VARIABLES_LAST_YEAR.size;
	}

	

	
	/*Linear Regression model for estimating a trend in market growth*/



	//Print debug:
	#ifdef _DEBUG_MODE    
   	if (PRINT_DEBUG_MARKET_RESEARCH)
	{
   		if(ID==ID_DEBUG_PROBE)
		{
   			printf("\n Firm_set_market_research_data():\n ");
			for(i=0; i<LAST_MARKET_SIZES.array[0].market_sizes.size;i++ )
			{
				printf("%d \t %f \n",LAST_MARKET_SIZES.array[0].market_sizes.array[i].period,LAST_MARKET_SIZES.array[0].market_sizes.array[i].market_size);
			}
		
		}	
	}
	#endif

	
	   
	   	double regressor;
	   	double intercept;
	   	double variance;
		double sum_1, sum_2;

	for(i=0;i<LAST_MARKET_SIZES.size;i++)
	{
	    if(LAST_MARKET_SIZES.array[i].market_sizes.size>5)
		{

			 sum_1=0;
	    	 sum_2=0;
			 variance=0.0;

	    	for (j=0;j<LAST_MARKET_SIZES.array[i].market_sizes.size; j++)
	    	    	{
	    	    	sum_1+= (LAST_MARKET_SIZES.array[i].market_sizes.size + 1 - LAST_MARKET_SIZES.array[i].market_sizes.array[j].period)* LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size;

	    	    	sum_2+=  LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size;


	    	    	}
					
	    
	    	regressor = (LAST_MARKET_SIZES.array[i].market_sizes.size * sum_1 - 0.5*LAST_MARKET_SIZES.array[i].market_sizes.size*(LAST_MARKET_SIZES.array[i].market_sizes.size+1)*sum_2)/
	        		(1/6.0*pow(LAST_MARKET_SIZES.array[i].market_sizes.size,2)*(LAST_MARKET_SIZES.array[i].market_sizes.size+1)*
	        		(2*LAST_MARKET_SIZES.array[i].market_sizes.size+1)-1/4.0*(pow(LAST_MARKET_SIZES.array[i].market_sizes.size,2)*pow((LAST_MARKET_SIZES.array[i].market_sizes.size+1),2)));

	    	intercept =  1/(1.0*LAST_MARKET_SIZES.array[i].market_sizes.size)*sum_2 - 0.5*regressor*(LAST_MARKET_SIZES.array[i].market_sizes.size+1);
	    	
	    	variance = 0;
	    	
	    	for(j=0; j< LAST_MARKET_SIZES.size; j++)
	    	  {
	    		 variance+= pow(LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size-(intercept+ 
	    				 (LAST_MARKET_SIZES.array[i].market_sizes.size + 1 - LAST_MARKET_SIZES.array[i].market_sizes.array[j].period)* regressor),2)
	    				  /(LAST_MARKET_SIZES.array[i].market_sizes.size-1);
	    	  }

	    	LINEAR_REGRESSION_MARKET_SIZE.array[i].mall_id=LAST_MARKET_SIZES.array[i].mall_id;
			LINEAR_REGRESSION_MARKET_SIZE.array[i].region_id=LAST_MARKET_SIZES.array[i].region_id;
	    	LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept=intercept;
	    	LINEAR_REGRESSION_MARKET_SIZE.array[i].regressor=regressor;
	    	LINEAR_REGRESSION_MARKET_SIZE.array[i].variance=variance;
	    	  
		}else
		{
			
			LINEAR_REGRESSION_MARKET_SIZE.array[i].mall_id=LAST_MARKET_SIZES.array[i].region_id;
			if(LAST_MARKET_SIZES.array[i].market_sizes.size==0)
			{
	    		LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept=1800.0;
			}else
			{
				LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept=0.0;
				for(j=0;j<LAST_MARKET_SIZES.array[i].market_sizes.size;j++)
				{
					LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept+= LAST_MARKET_SIZES.array[i].market_sizes.array[j].market_size;
				}
				LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept= LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept/LAST_MARKET_SIZES.array[i].market_sizes.size;
				LINEAR_REGRESSION_MARKET_SIZE.array[i].mall_id=LAST_MARKET_SIZES.array[i].mall_id;
				LINEAR_REGRESSION_MARKET_SIZE.array[i].region_id=LAST_MARKET_SIZES.array[i].region_id;
				
			}
	    	LINEAR_REGRESSION_MARKET_SIZE.array[i].regressor=0.0;
	    	LINEAR_REGRESSION_MARKET_SIZE.array[i].variance=0.0;

		}	
	}
	//Estimation of current market size based the linear regression 
	ESTIMATED_MARKET_SIZE  = LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept + (1+LAST_MARKET_SIZES.array[0].market_sizes.size)*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor;
	
	
	//Print debug:
	#ifdef _DEBUG_MODE    
   	if (PRINT_DEBUG_MARKET_RESEARCH)
	{
   		if(ID==ID_DEBUG_PROBE)
		{
   			printf("\n Firm_set_market_research_data():\n ");

			for(i=0;i<LINEAR_REGRESSION_MARKET_SIZE.size;i++)
			{
			if(i==0)
			{			
				printf("\nTotal economy:");
			}else
			{
				printf("\nRegion %d:",i);
			}
   			printf("\n LINEAR_REGRESSION_MARKET_SIZE.intercept %f LINEAR_REGRESSION_MARKET_SIZE.regressor %f LINEAR_REGRESSION_MARKET_SIZE.variance %f ",
   					LINEAR_REGRESSION_MARKET_SIZE.array[i].intercept,LINEAR_REGRESSION_MARKET_SIZE.array[i].regressor,LINEAR_REGRESSION_MARKET_SIZE.array[i].variance);
					//getchar();
			}
		}	
	}
	#endif
	
	//Save price and price index in memory
	PRICE_INDEX_AT_QUESTIONNAIRE = CURRENT_PRICE_INDEX;
	PRICE_AT_QUESTIONNAIRE = PRICE;

	
	//Reset the sample size counter
	
	ACTUAL_SAMPLE_SIZE = 0;


	//Compute the nummber of considered prices:
	if(NEW_PRODUCT_RELEASED==1)
	{

		PRICE_RANGE_PRICING.start_price =  1.0;	
		PRICE_RANGE_PRICING.end_price = 1.4; 
		PRICE_RANGE_PRICING.increment = 0.01;

		PRICE_RANGE_INNOVATION.start_price =  0.8;	
		PRICE_RANGE_INNOVATION.end_price = 1.6; 
		PRICE_RANGE_INNOVATION.increment = 0.02;

		NEW_PRODUCT_RELEASED=0;
	}else
	{
		PRICE_RANGE_PRICING.start_price =  MR_START_PRICE;	
		PRICE_RANGE_PRICING.end_price = MR_END_PRICE; 
		PRICE_RANGE_PRICING.increment = MR_PRICE_INCREMENT;

		PRICE_RANGE_INNOVATION.start_price =  MR_START_PRICE;	
		PRICE_RANGE_INNOVATION.end_price = MR_END_PRICE+0.4; 
		PRICE_RANGE_INNOVATION.increment = (MR_END_PRICE+0.4 - MR_START_PRICE)/40.0;
	}

	double no_cp=  (PRICE_RANGE_PRICING.end_price - PRICE_RANGE_PRICING.start_price)/ PRICE_RANGE_PRICING.increment;

	no_considered_prices = (int) no_cp;

	
	//Reset the market research data array:
	
	

	//delete the Market research array:
	
	int considered_periods;
	if(INNOVATION_SWITCHED_ON == 0)
	{
		considered_periods =2;
	}else
	{
		considered_periods = REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT+2;
	}

	for(i=MARKET_RESEARCH_DATA_PRICING.size-1;i>=0;i--)
	{

	remove_dt_market_research_price(&MARKET_RESEARCH_DATA_PRICING,i);
		
	}
	
	for(i=0; i<no_considered_prices;i++)
	{
		add_dt_market_research_price(&MARKET_RESEARCH_DATA_PRICING,(PRICE_RANGE_PRICING.start_price + i * PRICE_RANGE_PRICING.increment)-1, PRICE_AT_QUESTIONNAIRE*(PRICE_RANGE_PRICING.start_price + i * PRICE_RANGE_PRICING.increment),0);
		
		for(j=0;j<considered_periods;j++)
		{
		
			add_estimated_values_adt(&(MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values),0,0,0,0,0,0,0,0,0);
		
		}

	}




#ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_MARKET_RESEARCH)
    {
		  if(ID==ID_DEBUG_PROBE)
            {
		        printf("\n\n IT %d Firm_set_market_research_data() ID: %d",DAY, ID);
				printf("\n VARIABLES_CHANGE.price_index %f, VARIABLES_CHANGE.quality_index %f, VARIABLES_CHANGE.productivity_progress %f ",VARIABLES_CHANGE.price_index, 
				VARIABLES_CHANGE.quality_index,VARIABLES_CHANGE.productivity_progress);
				printf("\n INNOVATION_FLAG %d",INNOVATION_FLAG);
	
		}

    }
    #endif
	
	return 0;
}


int Firm_set_market_research_data_innovation()
{

	int i,j, no_considered_prices_innovation;
	double lowest_quality, highest_quality,no_cp;

	lowest_quality= INTERMEDIATE_QUALITY - REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT*QUALITY_CHANGE;
	highest_quality=INTERMEDIATE_QUALITY + REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT*QUALITY_CHANGE;
	no_cp=  (PRICE_RANGE_INNOVATION.end_price -PRICE_RANGE_INNOVATION.start_price)/PRICE_RANGE_INNOVATION.increment;
	
	no_considered_prices_innovation = (int) no_cp;

	printf("no_considered_prices_innovation % d \n",no_considered_prices_innovation);


	//Compting the number of possible quality realisations
	NO_CONSIDERED_QUALITIES = REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT + 1;


	//Delete old array
	for(i=MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.size-1;i>=0;i--)
	{

	remove_dt_market_research_qualities(&MARKET_RESEARCH_DATA_PRODUCT_INNOVATION,i);
		
	}

	//Set new array

	for(i=0; i<NO_CONSIDERED_QUALITIES; i++)
	{
		add_dt_market_research_qualities(&MARKET_RESEARCH_DATA_PRODUCT_INNOVATION,lowest_quality +i*2*QUALITY_CHANGE,0);
		
		for(j=0; j<no_considered_prices_innovation;j++)
		{
		add_dt_market_research_price(&MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price,(PRICE_RANGE_INNOVATION.start_price + j * PRICE_RANGE_INNOVATION.increment)-1, PRICE_AT_QUESTIONNAIRE*(PRICE_RANGE_INNOVATION.start_price+ j * PRICE_RANGE_INNOVATION.increment),0);
		
		// 2 times if the market share should be a linear combination
		add_estimated_values_adt(&MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values,0,0,0,0,0,0,0,0,0);

		add_estimated_values_adt(&MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values,0,0,0,0,0,0,0,0,0);
		}
		
	}
	

		#ifdef _DEBUG_MODE    
 	 			if (PRINT_DEBUG_MARKET_RESEARCH)
   		 		{
			  		if(ID==ID_DEBUG_PROBE)
            		{

						printf( "\n QREMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT %d   lowest_quality %f  highest_quality %f INTERMEDIATE_QUALITY%f\n",REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT, lowest_quality,highest_quality,INTERMEDIATE_QUALITY);
					}

   				 }
   				 #endif


	//Set up the market research data for different quality levels for the period of product completion 


return 0;
}




int Firm_bypass_setting_if_delayed()
{

	MARKET_RESEARCH_DELAYED =0;

return 0;
}


/** \fn Firm_release_new_product
 */
int Firm_release_new_product()
{

	
	//Set new quality	
	LAST_QUALITY = QUALITY;

	if(INTERMEDIATE_QUALITY>QUALITY)
	{
		QUALITY = INTERMEDIATE_QUALITY;
		NEW_PRODUCT_RELEASED = 1;

	}else
	{
		INTERMEDIATE_QUALITY= QUALITY;
	
	}

	REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT =  TOTAL_NO_PERIODS_FOR_PRODUCT_DEVELOPMENT;

	return 0;
	
	
	
} 
/** \fn Firm_draw_sample
 */
int Firm_draw_sample()
{

	add_interview_request_message(ID);
	
	return 0;
	
	
	
} 

/** \fn Firm_send_questionnaire
 */
int Firm_send_questionnaire()
{

	int i,no_considered_prices_pricing, no_considered_prices_innovation;
	no_considered_prices_pricing=(int)((PRICE_RANGE_PRICING.end_price - PRICE_RANGE_PRICING.start_price)/ PRICE_RANGE_PRICING.increment);

	no_considered_prices_innovation=(int)((PRICE_RANGE_INNOVATION.end_price - PRICE_RANGE_INNOVATION.start_price)/ PRICE_RANGE_INNOVATION.increment);

	//Read response:
	
	START_INTERVIEW_POSITIVE_RESPONSE_MESSAGE_LOOP
	
		
		ACTUAL_SAMPLE_SIZE++;
		
		
	FINISH_INTERVIEW_POSITIVE_RESPONSE_MESSAGE_LOOP	
	
	
	

	
	//Send message for pricing:
	add_questionnaire_pricing_message(ID,PRICE_RANGE_PRICING.start_price*PRICE,no_considered_prices_pricing,PRICE_RANGE_PRICING.increment*PRICE,QUALITY,VARIABLES_CHANGE.price_index);	


	//Send message for current quality for the next periods
	
	for(i=1;i<MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.size;i++)
	{
		add_questionnaire_innovation_message(ID,PRICE_RANGE_PRICING.start_price*PRICE,no_considered_prices_pricing,PRICE_RANGE_PRICING.increment*PRICE,QUALITY, VARIABLES_CHANGE.price_index, VARIABLES_CHANGE.quality_index,i);
	}

	
	//Send message for all qualities under consideration

	for(i=0;i<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.size;i++)
	{
		if(abs_double(MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality-QUALITY)>1e-5)
		{
			add_questionnaire_innovation_message(ID,PRICE*PRICE_RANGE_INNOVATION.start_price,no_considered_prices_innovation,PRICE_RANGE_INNOVATION.increment*PRICE,MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality,
		   		VARIABLES_CHANGE.price_index, VARIABLES_CHANGE.quality_index,REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT);

			add_questionnaire_innovation_message(ID,PRICE*PRICE_RANGE_INNOVATION.start_price,no_considered_prices_innovation,PRICE_RANGE_INNOVATION.increment*PRICE,MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality,
		   		VARIABLES_CHANGE.price_index, VARIABLES_CHANGE.quality_index,REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT+1);


			//printf("PRICE_RANGE_INNOVATION.start_price %f no_considered_prices_innovation %d PRICE_RANGE_INNOVATION.increment*PRICE %f",PRICE_RANGE_INNOVATION.start_price,no_considered_prices_innovation,PRICE_RANGE_INNOVATION.increment*PRICE);
		}
	
	}


	if(ACTUAL_SAMPLE_SIZE<MARKET_RESEARCH_SAMPLE_SIZE)
	{
		DAY_OF_YEAR_MARKET_RESEARCH = (DAY_OF_YEAR_MARKET_RESEARCH +1)%240; 
		MARKET_RESEARCH_DELAYED = 1;
	}else
	{
		MARKET_RESEARCH_ACTIVE=1;
	}
	

	#ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_MARKET_RESEARCH)
    {
		  if(ID==ID_DEBUG_PROBE)
            {
		        printf("\n\n IT %d Firm_send_questionnaire() ID: %d",DAY, ID);
				printf("\n MARKET_RESEARCH_SAMPLE_SIZE %d	ACTUAL_SAMPLE_SIZE %d",MARKET_RESEARCH_SAMPLE_SIZE,ACTUAL_SAMPLE_SIZE);

	
		}

    }
    #endif
	
	return 0;
}



int Firm_count_questionnaire()
{

	int i,j,considered_time_horizon;

	considered_time_horizon=MARKET_RESEARCH_DATA_PRICING.array[0].estimated_values.size;

	START_FILLED_OUT_QUESTIONNAIRE_PRICING_MESSAGE_LOOP

	
	for(i=0;i<MARKET_RESEARCH_DATA_PRICING.size;i++)
	{		
		MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[0].no_positive_response +=  filled_out_questionnaire_pricing_message->questionnaire[i];
	}
	FINISH_FILLED_OUT_QUESTIONNAIRE_PRICING_MESSAGE_LOOP


	START_FILLED_OUT_QUESTIONNAIRE_PRODUCT_INNOVATION_MESSAGE_LOOP

	
	if(abs_double(QUALITY-filled_out_questionnaire_product_innovation_message->quality)<1e-5)
	{
		for(i=0;i<MARKET_RESEARCH_DATA_PRICING.size;i++)
		{
			MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[filled_out_questionnaire_product_innovation_message->year].no_positive_response +=  filled_out_questionnaire_product_innovation_message->questionnaire[i];
		}
	}

	FINISH_FILLED_OUT_QUESTIONNAIRE_PRODUCT_INNOVATION_MESSAGE_LOOP	
	
	START_FILLED_OUT_QUESTIONNAIRE_PRODUCT_INNOVATION_MESSAGE_LOOP
	
	for(i=0;i<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.size;i++)
	{
		
		//Check incoming messages for price and quality...	
		if(abs_double(MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality-filled_out_questionnaire_product_innovation_message->quality)<1e-5)
		{

			if(filled_out_questionnaire_product_innovation_message->year == REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT)
			{

				for(j=0;j<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.size;j++)
				{
	
					MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].no_positive_response+=  filled_out_questionnaire_product_innovation_message->questionnaire[j];

				}
			}else if(filled_out_questionnaire_product_innovation_message->year == REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT + 1)
			{
				for(j=0;j<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.size;j++)
				{
	
					MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[1].no_positive_response+=  filled_out_questionnaire_product_innovation_message->questionnaire[j];

				}

			}			
		}
		
	}
	FINISH_FILLED_OUT_QUESTIONNAIRE_PRODUCT_INNOVATION_MESSAGE_LOOP

	return 0;
}


int Firm_analyze_questionnaire()
{

	int i,j,k,t;

	double mean_log_counts ;
	double mean_of_price_range ;
	double coefficient_numerator;
	double coefficient_denominator;
	double coefficient,intercept,exp_intercept, variance;



	//Delete old demand functions
	for(i=DEMAND_FUNCTIONS_PRODUCT_INNOVATION.size;i>=0;i--)
	{
		remove_dt_demand_function(&DEMAND_FUNCTIONS_PRODUCT_INNOVATION,i);
	}

	for(t=0;t<MARKET_RESEARCH_DATA_PRICING.array[0].estimated_values.size;t++)
	{
		/*Define a temporary array*/
		dt_price_quantity_touple_array price_quantity_log_quantity;
		init_dt_price_quantity_touple_array(&price_quantity_log_quantity);
			
		for(i=0;i<MARKET_RESEARCH_DATA_PRICING.size;i++)
		{
			//Add logarithm of counts and (no log) prices to the temporrary array

			//if(no_positive_respones = 0, set this value to 0.1 in order to avoid NANs)					
			if(MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[t].no_positive_response>0)
			{
				add_dt_price_quantity_touple(&price_quantity_log_quantity,
				MARKET_RESEARCH_DATA_PRICING.array[i].price , log(MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[t].no_positive_response));
								
			}else
			{
					add_dt_price_quantity_touple(&price_quantity_log_quantity,
					MARKET_RESEARCH_DATA_PRICING.array[i].price , log(0.1));
			}
		}	
			

		/*Linear Regression*/

		mean_log_counts = 0.0;
		mean_of_price_range = 0.0;
			
		//Compute means
		for(i=0;i<price_quantity_log_quantity.size;i++)
		{	
			mean_of_price_range += price_quantity_log_quantity.array[i].price;
			mean_log_counts+= price_quantity_log_quantity.array[i].quantity;
		}
		if(price_quantity_log_quantity.size>0)
		{
			mean_log_counts = mean_log_counts/price_quantity_log_quantity.size;
			mean_of_price_range = mean_of_price_range/price_quantity_log_quantity.size;
		}
			
		//Compute the coefficients
		coefficient_numerator = 0.0;
		coefficient_denominator = 0.0;
		coefficient=0.0;
		variance =0.0;

		for(i=0;i<price_quantity_log_quantity.size;i++)
		{	
			coefficient_numerator += (price_quantity_log_quantity.array[i].quantity - mean_log_counts )*(price_quantity_log_quantity.array[i].price-mean_of_price_range);
			coefficient_denominator += pow(price_quantity_log_quantity.array[i].price-mean_of_price_range,2) ;
		}
		if(coefficient_denominator>1e-5)
		{			
			coefficient = coefficient_numerator/  coefficient_denominator;
		}
	
		/*Transform the linearized function in exponential form and store the in array*/

		intercept = mean_log_counts - coefficient*mean_of_price_range;

		exp_intercept=exp(intercept);

		for(i=0; i<price_quantity_log_quantity.size;i++)
		{
			variance += pow((exp(price_quantity_log_quantity.array[i].quantity) - exp_intercept*exp(coefficient*price_quantity_log_quantity.array[i].price) ),2);
 		}			
		if(price_quantity_log_quantity.size>1)
		{			
			variance =variance/ (price_quantity_log_quantity.size -1);
		}else
		{
			variance = 0.0;
		}
		if(t==0)
		{	
			DEMAND_FUNCTION_PRICING.quality=QUALITY;
			DEMAND_FUNCTION_PRICING.year=0;
			DEMAND_FUNCTION_PRICING.factor=exp(intercept);
			DEMAND_FUNCTION_PRICING.exponent=coefficient;
			DEMAND_FUNCTION_PRICING.variance=variance;
		}else
		{
			add_dt_demand_function(&DEMAND_FUNCTIONS_PRODUCT_INNOVATION,QUALITY,t,exp(intercept),coefficient,variance);

		}	
		//Free memory
		free_dt_price_quantity_touple_array(&price_quantity_log_quantity);
	
	//Compute the estimated probabilities:

	}	

	for(i=0; i<MARKET_RESEARCH_DATA_PRICING.size;i++)
	{
		for(t=0;t<MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.size;t++)
		{
			if(t==0)
			{
				MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[t].probability = 
					(DEMAND_FUNCTION_PRICING.factor*exp(DEMAND_FUNCTION_PRICING.exponent*MARKET_RESEARCH_DATA_PRICING.array[i].price))/(double) ACTUAL_SAMPLE_SIZE;		
					#ifdef _DEBUG_MODE    
  					if (PRINT_DEBUG_MARKET_RESEARCH)
   					{
						if(ID==ID_DEBUG_PROBE)
      				    {
		        			printf(" \nPrice	%f Estimated market share %f",MARKET_RESEARCH_DATA_PRICING.array[i].price, MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[t].probability);
						}

    				}
    				#endif


			}else
			{
				for(k=0;k<DEMAND_FUNCTIONS_PRODUCT_INNOVATION.size;k++)
				{
					if(t==DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].year)
					{					
					MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[t].probability = 
					(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].factor*exp(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].exponent*MARKET_RESEARCH_DATA_PRICING.array[i].price))/(double) ACTUAL_SAMPLE_SIZE;	
					}
				}
			}	
		}
	}
	
	//Second: For last year of considered time horizon

		
	for(i=0;i<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.size;i++)
	{
		for(t = 0; t < 2; t++)
		{

			/*Define a temporary array*/
			dt_price_quantity_touple_array price_quantity_log_quantity;
			init_dt_price_quantity_touple_array(&price_quantity_log_quantity);

	
			for(j=0;j<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.size;j++)
			{
				//Add logarithm of counts and (no log) prices to the temporrary array
	
	
				//if(no_positive_respones = 0, set this value to 0.1 in order to avoid NANs)					
				if(MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[t].no_positive_response>0)
				{
					add_dt_price_quantity_touple(&price_quantity_log_quantity,
					MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price , 
						log(MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[t].no_positive_response));
								
				}else
				{
					add_dt_price_quantity_touple(&price_quantity_log_quantity,
					MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price , log(0.1));
				}
			}
	
			

			/*Linear Regression*/
	
			mean_log_counts = 0.0;
			mean_of_price_range = 0.0;
				
			//Compute means
			for(j=0;j<price_quantity_log_quantity.size;j++)
			{	
				mean_of_price_range += price_quantity_log_quantity.array[j].price;
				mean_log_counts+= price_quantity_log_quantity.array[j].quantity;
			}
			if(price_quantity_log_quantity.size>0)
			{
				mean_log_counts = mean_log_counts/price_quantity_log_quantity.size;
				mean_of_price_range = mean_of_price_range/price_quantity_log_quantity.size;
			}

			
			//Compute the coefficients
			coefficient_numerator = 0.0;
			coefficient_denominator = 0.0;
			coefficient=0.0;
			variance =0.0;
	
			for(j=0;j<price_quantity_log_quantity.size;j++)
			{	
				coefficient_numerator += (price_quantity_log_quantity.array[j].quantity - mean_log_counts )*(price_quantity_log_quantity.array[j].price-mean_of_price_range);
				coefficient_denominator += pow(price_quantity_log_quantity.array[j].price-mean_of_price_range,2) ;
			}
			if(coefficient_denominator>1e-5)
			{			
				coefficient = coefficient_numerator/  coefficient_denominator;
			}

			/*Transform the linearized function in exponential form and store the in array*/
	
			intercept = mean_log_counts - coefficient*mean_of_price_range;

			exp_intercept=exp(intercept);
	
			for(j=0; j<price_quantity_log_quantity.size;j++)
			{
				variance += pow((exp(price_quantity_log_quantity.array[j].quantity) - exp_intercept*exp(coefficient*price_quantity_log_quantity.array[j].price) ),2);
 			}			
			if(price_quantity_log_quantity.size>1)
			{			
			variance =variance/ (price_quantity_log_quantity.size -1);
			}else
			{
				variance = 0.0;
			}
				
			if(abs_double(MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality-QUALITY)>1e-5)
			{
				add_dt_demand_function(&DEMAND_FUNCTIONS_PRODUCT_INNOVATION,MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality,REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT+t,exp(intercept),coefficient,variance);
			}	
			//Free memory
			free_dt_price_quantity_touple_array(&price_quantity_log_quantity);
		
			//Compute the estimated probabilities:
	

		}	
	}

	for(i=0;i<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.size;i++)
	{
		for(k=0;k<DEMAND_FUNCTIONS_PRODUCT_INNOVATION.size;k++)
		{	
			if(abs_double(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].quality-MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality)<1e-5)
			{
				if(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].year==REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT)
				{
	
					for(j=0;j<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.size;j++)
					{
					MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].probability = 
						(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].factor*
						exp(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].exponent*MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price))/(double) ACTUAL_SAMPLE_SIZE;
					}
				}else if(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].year==REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT +1)		
				{
					for(j=0;j<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.size;j++)
					{
						MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[1].probability = 
							(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].factor*
							exp(DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].exponent*MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price))/(double) ACTUAL_SAMPLE_SIZE;
					}
				}			
			}
		}
	}
return 0;

}


int Firm_prepone_vintage_choice()
{

		int i,j;
		
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
					 the employer. The rate is predetermined.*/

					
      				specific_skills = max(specific_skills, specific_skills+ (TECHNOLOGY_VINTAGES.array[i].productivity-specific_skills)		     
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
			double logit_vintage[TECHNOLOGY_VINTAGES.size];
				
			if(DAY>=TRANSITION_PHASE)
			{
				/*Summing for logit denominator*/
				for(i=0; i<TECHNOLOGY_VINTAGES.size;i++)
				{
					sum += exp(GAMMA_LOGIT_VINTAGE_CHOICE*log(productivity_price_ratio[i]));
				}

				/*Computing the logits*/
				for(i=0; i<TECHNOLOGY_VINTAGES.size;i++)
				{
					logit_vintage[i]= exp(GAMMA_LOGIT_VINTAGE_CHOICE*log(productivity_price_ratio[i]))/sum;
				}
			

				/*random generator and selection of logit*/

				double rnd_number = (double)random_int(0,100)/100.0;

				for(i=0; i<TECHNOLOGY_VINTAGES.size;i++)
				{	
					if(rnd_number<logit_vintage[i])
					{
						VINTAGE_SELECTED = i;
						break;
					}else
					{
						if(i<TECHNOLOGY_VINTAGES.size-1)
							logit_vintage[i+1]+=logit_vintage[i];
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

		VINTAGE_CHOICE_ALREADY_TAKEN = 1;
		VINTAGE_CHOICE_TAKEN = 1;


		#ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_MARKET_RESEARCH)
    {
		if(ID==ID_DEBUG_PROBE)
        {
		        printf("\n Firm_prepone_vintage_choice(): \n VINTAGE_SELECTED %d", VINTAGE_SELECTED);
		}

    }
    #endif

	
	return 0;
}


int	Firm_set_price()
{
	
	int i,j,t,Y;	

	int no_employees, no_employees_at_end_of_year, labour_demand;
	double average_productivity;
	double eff_productivity;
	double used_capital_stock;
	double planned_output;	
	double sum_output;
	double pot_output;
	double sum_earnings;
	double sum_earnings_discounted;
	double mean_specific_skills;
	double estimated_mean_wage;
	double realized_output;
	double capital_stock_depreciation_units;
	double payment_account;
	double installment_payment;
	double interest_payments;
	double earnings;
	double debt_needed;
	double investment_nominal;
	double temp_highest_earnings;
	double mean_specific_skills_at_end_of_year;
	double estimated_mean_wage_at_end_of_year ;
	double payment_account_at_end_of_year;
	double earnings_at_end_of_year;
	double 	buffer_at_end_of_year ;
	double labor_costs, capital_costs, calc_cap_costs;
	double sum_interest_payments;
	double combined_variance_demand_function;
	double buffer;
	double critical_stock;
	double expected_sales;
	double actual_sales_estimation;
	double current_stocks;

	double monthly_wage_growth = 1+VARIABLES_CHANGE.productivity_progress;

			#ifdef _DEBUG_MODE    
 		   if (PRINT_DEBUG_MARKET_RESEARCH)
   			 {
				  if(ID==ID_DEBUG_PROBE)
     	       {
					printf( "\nOld PRICE %f \n",PRICE);
							
				}
  		  }
  		 #endif


	//delete array PROSPECTIVE_VARIABLES

	for(i=PROSPECTIVE_VARIABLES.size-1;i>=0;i--)
	{
		remove_dt_prospective_variables(&PROSPECTIVE_VARIABLES,i);
	}

	// optimal price choices for the next years until the completation of the R & D project	
	for(i=EXPECTED_PRICE_CHOICES.size-1;i>=0;i--)
	{
		remove_double(&EXPECTED_PRICE_CHOICES,i);
	}

	//Define temporary arrays for some variables which change from year to year. Starting with the actual values...
	adt_capital_stock_vintages_array capital_stock_at_end_of_year;
	init_adt_capital_stock_vintages_array(&capital_stock_at_end_of_year);

	financing_capital_array temp_capital_financing_at_end_of_year;
	init_financing_capital_array(&temp_capital_financing_at_end_of_year);

	debt_item_array temp_loans_at_end_of_year;
	init_debt_item_array(&temp_loans_at_end_of_year);

	for(i=0;i<CAPITAL_STOCK_VINTAGES.size;i++)
	{
		add_adt_capital_stock_vintages(&capital_stock_at_end_of_year, CAPITAL_STOCK_VINTAGES.array[i].
		amount,CAPITAL_STOCK_VINTAGES.array[i].productivity);
	}

	for(i=0;i<CAPITAL_FINANCING.size;i++)
	{
		add_financing_capital(&temp_capital_financing_at_end_of_year,CAPITAL_FINANCING.array[i].financing_per_month,
		CAPITAL_FINANCING.array[i].nr_periods_before_repayment);
	}

	for(i=0;i<LOANS.size;i++)
	{
		add_debt_item(&temp_loans_at_end_of_year, 0,LOANS.array[i].loan_value,LOANS.array[i].interest_rate,LOANS.array[i].installment_amount
			,0,0,0,LOANS.array[i].nr_periods_before_repayment);
	}

	//Temporary variables to store...
	mean_specific_skills_at_end_of_year = MEAN_SPECIFIC_SKILLS;
	estimated_mean_wage_at_end_of_year = MEAN_WAGE;
	no_employees_at_end_of_year = NO_EMPLOYEES_PRODUCTION;
	payment_account_at_end_of_year = PAYMENT_ACCOUNT;
	earnings_at_end_of_year= EARNINGS;
	buffer_at_end_of_year = TOTAL_BUFFER;


	for(Y=0;Y<MARKET_RESEARCH_DATA_PRICING.array[0].estimated_values.size-1;Y++)
	{
		temp_highest_earnings =0;

		for(i=0;i<MARKET_RESEARCH_DATA_PRICING.size;i++)
		{

			//Reset the earnings 
			adt_capital_stock_vintages_array capital_stock;
			init_adt_capital_stock_vintages_array(&capital_stock);

			for(j=0;j<capital_stock_at_end_of_year.size;j++)
			{
				add_adt_capital_stock_vintages(&capital_stock, capital_stock_at_end_of_year.array[j].amount,capital_stock_at_end_of_year.array[j].productivity);
			}

			financing_capital_array temp_capital_financing;
			init_financing_capital_array(&temp_capital_financing);

			for(j=0;j<temp_capital_financing_at_end_of_year.size;j++)
			{
				add_financing_capital(&temp_capital_financing, temp_capital_financing_at_end_of_year.array[j].financing_per_month,
				temp_capital_financing_at_end_of_year.array[j].nr_periods_before_repayment);
			}

			debt_item_array temp_loans;
			init_debt_item_array(&temp_loans);

			for(j=0;j<temp_loans_at_end_of_year.size;j++)
			{
				add_debt_item(&temp_loans, 0,temp_loans_at_end_of_year.array[j].loan_value,temp_loans_at_end_of_year.array[j].interest_rate,temp_loans_at_end_of_year.array[j].installment_amount
					,0,0,0,temp_loans_at_end_of_year.array[j].nr_periods_before_repayment);
			}

				
			dt_monthly_estimations_array temp_variables_over_year;
			init_dt_monthly_estimations_array(&temp_variables_over_year);

	
			sum_earnings=0.0;
			sum_earnings_discounted=0.0;			

			mean_specific_skills = mean_specific_skills_at_end_of_year;
			estimated_mean_wage =estimated_mean_wage_at_end_of_year;
			no_employees = no_employees_at_end_of_year;
			payment_account = payment_account_at_end_of_year;
			earnings=earnings_at_end_of_year;
			buffer = buffer_at_end_of_year;
			
			MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_earnings =0.0;

			current_stocks = buffer;
			
			//Optimal price and quantity choice:

			if(Y==0)
			{
			combined_variance_demand_function = pow(MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array
					[0].probability,2)*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance + 
					pow(LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept,2)*DEMAND_FUNCTION_PRICING.variance/
					(1.0*pow	(ACTUAL_SAMPLE_SIZE,2))+DEMAND_FUNCTION_PRICING.variance/(1.0*pow(ACTUAL_SAMPLE_SIZE,2))	
					*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance;
			}else
			{
				for(j=0;j< DEMAND_FUNCTIONS_PRODUCT_INNOVATION.size;j++)
				{
					if(Y== DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[j].year && DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[j].quality ==QUALITY)
					{
						combined_variance_demand_function = pow(MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array
						[Y].probability,2)*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance + 
						pow(LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept + Y*12*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor,2)*DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[j].variance/
						(1.0*pow	(ACTUAL_SAMPLE_SIZE,2))+DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[j].variance/(1.0*pow(ACTUAL_SAMPLE_SIZE,2))	
						*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance;

					}

				}


			}


			buffer = QUANTIL_NORMAL_DISTRIBUTION*pow(combined_variance_demand_function ,0.5);

			current_stocks=TOTAL_BUFFER;

			for(t=0;t<12;t++)
			{
				average_productivity=0.0;
				eff_productivity = 0.0;
				used_capital_stock=0.0;
				sum_output=0;
				pot_output=0;
				capital_stock_depreciation_units=0.0;
				installment_payment=0.0;
				interest_payments=0.0;
				investment_nominal=0.0;
				labor_costs=0.0;
				capital_costs=0.0;
				calc_cap_costs=0.0;
				sum_interest_payments=0.0; 

				//Expected sales are linear combination of market shares at the beginning and the end of the year times market size		
				expected_sales = ((LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept 
					+ (1+LAST_MARKET_SIZES.array[0].market_sizes.size+Y*12+t)*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor)
					)*((t/11.0)*MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y+1].probability+((11-t)/11.0)*MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].probability);
				
				//Set critical stock: Expected sales plus buffer
				critical_stock = expected_sales + buffer;

				//Set output: Difference of critical and current stock 
				planned_output = max(critical_stock - current_stocks, 0);

				//Fix costs:
				// Capital costs for sunk investments:

				MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_fix_costs=0;
			
				for(j=0; j< temp_capital_financing.size;j++)
				{
					if(temp_capital_financing.array[j].nr_periods_before_repayment==0)
      	        	{
             	       remove_financing_capital(&temp_capital_financing,j);
       	       	    	j--;
                	}else
               		{
                		temp_capital_financing.array[j].nr_periods_before_repayment--;
                		MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_fix_costs
							+= temp_capital_financing.array[j].financing_per_month;
						calc_cap_costs+=temp_capital_financing.array[j].financing_per_month;
                	}
				}

				//Interest payments:
				for(j=temp_loans.size-1;j>=0;j--)
				{
					
					interest_payments=temp_loans.array[j].loan_value* temp_loans.array[j].interest_rate/12.0;
					MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_fix_costs
						+=interest_payments;
					installment_payment += temp_loans.array[j].installment_amount;
					sum_interest_payments+=interest_payments;
					temp_loans.array[j].loan_value-=temp_loans.array[j].installment_amount;					
					temp_loans.array[j].nr_periods_before_repayment--;

					if(temp_loans.array[j].nr_periods_before_repayment<1)
					{
						remove_debt_item(&temp_loans,j);

					}

				}	

			


					#ifdef _DEBUG_MODE    
 		   if (PRINT_DEBUG_MARKET_RESEARCH)
   			 {
				  if(ID==ID_DEBUG_PROBE && Y==0)
     	       {
		    
				//printf( "fixed costs %f   Interest costs:  %f      Calc Capital costs  %f\n",MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_fix_costs,sum_interest_payments,calc_cap_costs);
					for(j=0;j<temp_loans.size;j++)
					{

						//printf( "Y: %d t: %d temp_loans.array[j].nr_periods_before_repayment %d  temp_loans.array[j].loan_value %f \n",Y,t,temp_loans.array[j].nr_periods_before_repayment,temp_loans.array[j].loan_value);
					}
				}

  		  }
  		 #endif	

				//Compute input factor needs
				for(j=capital_stock.size-1;j>=0;j--)
				{
					capital_stock.array[j].amount= capital_stock.array[j].amount*(1-DEPRECIATION_RATE);
					capital_stock_depreciation_units+=capital_stock.array[j].amount*DEPRECIATION_RATE;
		
					if(sum_output < planned_output)
					{
						pot_output += min(mean_specific_skills,capital_stock.array[j].productivity)*capital_stock.array[j].amount;

						if(pot_output>planned_output)
						{
							double sum_cap_selected_vintage=(planned_output - sum_output)
								/min(mean_specific_skills,capital_stock.array[j].productivity);
							sum_output += (planned_output - sum_output);
							used_capital_stock+=sum_cap_selected_vintage;
							average_productivity += capital_stock.array[j].productivity*sum_cap_selected_vintage;
							eff_productivity += min(capital_stock.array[j].productivity,mean_specific_skills)
								*sum_cap_selected_vintage;
							
						}else
						{
							used_capital_stock+=capital_stock.array[j].amount;		
							sum_output += min(mean_specific_skills,capital_stock.array[j].productivity)*capital_stock.array[j].amount;
							average_productivity += capital_stock.array[j].productivity*capital_stock.array[j].amount;
							eff_productivity += min(capital_stock.array[j].productivity,
								mean_specific_skills)*capital_stock.array[j].amount;
						}
					}
				}
				if(sum_output < planned_output)
				{
					double inv;
					inv = (planned_output - sum_output)/ min(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity,mean_specific_skills);
	
					inv = min(inv, INV_INERTIA*capital_stock_depreciation_units);
					used_capital_stock+=inv;

					inv += (round_double_to_int(used_capital_stock) - used_capital_stock);
					average_productivity += TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity*inv;
					eff_productivity += min(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity,
								mean_specific_skills)*inv;
						
					for(j=0; j<capital_stock.size;j++)
					{
						if(abs_double(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity-capital_stock.array[j].productivity)<1e-5)
						{
							capital_stock.array[j].amount+=inv;
							break;
						}else
						{
							if(j==capital_stock.size-1)
							{
								add_adt_capital_stock_vintages(&capital_stock,inv,TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity);
							}
						}
					}

					/* If subsidies for best vintage are switched on: reduce the effective price
					 for best practice technology*/				
					if(POLICY_EXP_BEST_TECHNOLOGY_SUBSIDY==1 && abs_double(TECHNOLOGY_VINTAGES.array[i].productivity - TECHNOLOGICAL_FRONTIER)<1e-5)
					{
						investment_nominal=inv*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price*(1-SUBSIDY_PCT);
					}else
					{	
						investment_nominal=inv*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price;
					}
					add_financing_capital(&temp_capital_financing,investment_nominal/CONST_INSTALLMENT_PERIODS, CONST_INSTALLMENT_PERIODS);
						
				
				}

				labour_demand = round_double_to_int(used_capital_stock);
				used_capital_stock = round_double_to_int(used_capital_stock);
				if(used_capital_stock>1e-5)
				{
					average_productivity = average_productivity / used_capital_stock;
					eff_productivity = eff_productivity / used_capital_stock;
				}else
				{
					average_productivity = TECHNOLOGY;
					used_capital_stock  = TECHNOLOGY;

				}
				/*Capital costs*/
				capital_costs=calc_cap_costs + investment_nominal
					/CONST_INSTALLMENT_PERIODS;

				/*Determine tealized output*/
				realized_output= labour_demand*eff_productivity;

				current_stocks += realized_output;
			
				//Compute mean wage:	
				if(labour_demand>no_employees)
				{
					estimated_mean_wage =no_employees/(1.0*labour_demand) * estimated_mean_wage  
						+ (labour_demand - no_employees)/(1.0*labour_demand)*WAGE_OFFER*min(average_productivity,mean_specific_skills);

				}

				//Compute variable costs
				if(realized_output>1e-5)
				{
					MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_variable_costs = 	
						(labour_demand*estimated_mean_wage + investment_nominal/CONST_INSTALLMENT_PERIODS)/realized_output;
				}
				else
				{
					MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_variable_costs = 0.0;
				}
	
				labor_costs = labour_demand*estimated_mean_wage;
				//Check financing:
	
				payment_account= payment_account - 
					labour_demand*estimated_mean_wage - investment_nominal -
					sum_interest_payments - installment_payment -max(0,earnings)*TAX_RATE_CORPORATE - max(0,earnings)*(1-TAX_RATE_CORPORATE)
					*CONST_DIVIDEND_EARNINGS_RATIO;

				//Check if additional loans are necessary
				debt_needed = (-1)*min(payment_account,0);



						
				if(debt_needed>1e-5)
				{
					add_debt_item(&temp_loans, 0,debt_needed,LAST_INTEREST_RATE_FOR_LOANS,debt_needed/CONST_INSTALLMENT_PERIODS,0,0,0,CONST_INSTALLMENT_PERIODS);
				}
				payment_account+=debt_needed;



				// Compute actual sales:

				actual_sales_estimation = min(current_stocks,expected_sales);



				//Compute earnings
				earnings= actual_sales_estimation* (MARKET_RESEARCH_DATA_PRICING.array[i].price - 
					MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_variable_costs)  - 
					MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_fix_costs;


				add_dt_monthly_estimations(&temp_variables_over_year,realized_output,earnings,actual_sales_estimation,
					labor_costs,capital_costs,sum_interest_payments,estimated_mean_wage,mean_specific_skills,average_productivity,investment_nominal);


				#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		//	if(Y==0)
		  // printf( "payment_account %f   debt_needed %f \n",payment_account ,  debt_needed );
			//printf( "earnings %f   realized_output %f  variable costs %f  fixed costs %f   investment_nominal %f \n ", earnings,  realized_output,MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_variable_costs,MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_fix_costs, investment_nominal);

			
			
		}

    }
    #endif







				sum_earnings_discounted += pow(1/(1+DISCONT_RATE),t)*earnings;
				sum_earnings += earnings;			

				MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_earnings += pow(1/(1+DISCONT_RATE),Y*12+t)*earnings;
	
				//Add expected earnings on payment account
				payment_account+= actual_sales_estimation*MARKET_RESEARCH_DATA_PRICING.array[i].price;

				current_stocks -=actual_sales_estimation;
	
				//Update mean wage:
	
				estimated_mean_wage = estimated_mean_wage*monthly_wage_growth;
	
				no_employees  = labour_demand;

				// Skill update:

				if(SKILL_UPDATE_ACC_TO_FORMULA==1)
				{
      				/*Update the specific skill: depends on the actual specific skill, 
        			the gap between the actual specific skills and the actual productivity of the employer,
        			and the general skill which determines the speed of closing the this gap.*/
       				mean_specific_skills = max(mean_specific_skills, mean_specific_skills+ 
						max(average_productivity-mean_specific_skills,0)
						*((1-pow(0.5,1/(20+0.25*(AVERAGE_G_SKILL-1)*(4-20))))));
				}else
				{
	 				 /*Update the specific skill: depends on the actual specific skill, 
       				 the gap between the actual specific skills and the actual productivity of
					 the employer. The rate is predetermined.*/
				
      					mean_specific_skills = max(mean_specific_skills, mean_specific_skills+ max(average_productivity-mean_specific_skills,0)		     
							*AVERAGE_ADAPTATION_SPEED_SPECIFIC_SKILLS);
						
				}
			}		


	
			#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE && Y==MARKET_RESEARCH_DATA_PRICING.array[0].estimated_values.size-2)
            {
			
		 printf( "Price: %f   sum_earnings_discounted  %f    sum_earnings %f \n",MARKET_RESEARCH_DATA_PRICING.array[i].price, sum_earnings_discounted ,sum_earnings);

			//printf( "earnings %f  %f \n ", earnings,  realized_output,MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_variable_costs,MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_fix_costs, investment_nominal);
		}

    }
    #endif
		

			//Search for the highest expected earnings. Therefore we start with the first price and overwrite the values if the expected earnings are higher
			if(i==0 || temp_highest_earnings < MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_earnings)
			{

	
				if(Y!=MARKET_RESEARCH_DATA_PRICING.array[0].estimated_values.size-1)
				{
					if(i!=0)
					{
						remove_dt_prospective_variables(&PROSPECTIVE_VARIABLES,Y);
					}

					add_dt_prospective_variables(&PROSPECTIVE_VARIABLES,mean_specific_skills,estimated_mean_wage, no_employees, earnings, payment_account, buffer,0,0,0);
	
	
					for(j=0;j<capital_stock.size;j++)
					{
						add_adt_capital_stock_vintages(&PROSPECTIVE_VARIABLES.array[Y].capital_stock_vintages, capital_stock.array[j].
							amount,capital_stock.array[j].productivity);
					}

					for(j=0;j<temp_capital_financing.size;j++)
					{
						add_financing_capital(&PROSPECTIVE_VARIABLES.array[Y].capital_financing, temp_capital_financing.array[j].financing_per_month,
							temp_capital_financing.array[j].nr_periods_before_repayment);
					}
				


					for(j=0;j<temp_loans.size;j++)
					{
						add_debt_item(&PROSPECTIVE_VARIABLES.array[Y].loans, 0,temp_loans.array[j].loan_value
						,temp_loans.array[j].interest_rate,temp_loans.array[j].installment_amount
							,0,0,0,temp_loans.array[j].nr_periods_before_repayment);
					}
				
				}
				temp_highest_earnings = MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_earnings;

				if(EXPECTED_PRICE_CHOICES.size != Y + 1)
				{
					add_double(&EXPECTED_PRICE_CHOICES,MARKET_RESEARCH_DATA_PRICING.array[i].price);
				}else
				{
					EXPECTED_PRICE_CHOICES.array[Y]=MARKET_RESEARCH_DATA_PRICING.array[i].price;
				}

				//Set new price:
				if(Y==0)
				{
					for(t=0;t<12;t++)
					{
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].output= 			
							temp_variables_over_year.array[t].output;
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].earnings= 			
							temp_variables_over_year.array[t].earnings;
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].labor_costs= 
							temp_variables_over_year.array[t].labor_costs;
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].capital_costs= 
							temp_variables_over_year.array[t].capital_costs;
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].interest_payments= 
							temp_variables_over_year.array[t].interest_payments;
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].wage= 
							temp_variables_over_year.array[t].wage;
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].mean_specific_skills= 
							temp_variables_over_year.array[t].mean_specific_skills;
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].average_productivity= 
							temp_variables_over_year.array[t].average_productivity;
						EXPECTED_EARNINGS_AND_COSTS_OVER_YEAR[t].investment_nominal=
							temp_variables_over_year.array[t].investment_nominal;
					
					}

				

					PRICE_LAST_MONTH = PRICE;
					PRICE = MARKET_RESEARCH_DATA_PRICING.array[i].price;
					EXPECTED_SOLD_QUANTITY_PER_MONTH = ESTIMATED_MARKET_SIZE*
					MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[0].probability;
					ESTIMATED_MARKET_SHARE_BEGINNING_OF_YEAR = MARKET_RESEARCH_DATA_PRICING.array[i]
						.estimated_values.array[0].probability ;
					ESTIMATED_MARKET_SHARE_END_OF_YEAR = MARKET_RESEARCH_DATA_PRICING.array[i]
						.estimated_values.array[1].probability ;
				
					EARNINGS_WHILE_LAST_PRICING_PERIOD = SUM_EARNINGS_SINCE_PRICE_CHANGE;
					SUM_EARNINGS_SINCE_PRICE_CHANGE=0.0;	

	

					COMBINED_VARIANCE_DEMAND_FUNCTION = pow(MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[0].probability,2)
						*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance + pow(LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept,2)
						*DEMAND_FUNCTION_PRICING.variance/(1.0*pow	(ACTUAL_SAMPLE_SIZE,2))+DEMAND_FUNCTION_PRICING.variance/(1.0*pow(ACTUAL_SAMPLE_SIZE,2))	
						*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance;



				
				}else if(Y==REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT)
				{
		
					BEST_PRICING_ABANDON_STRATEGY.quality=QUALITY;
					BEST_PRICING_ABANDON_STRATEGY.price= MARKET_RESEARCH_DATA_PRICING.array[i].price;
					BEST_PRICING_ABANDON_STRATEGY.expected_earnings	=MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_earnings;
					BEST_PRICING_ABANDON_STRATEGY.sum_earnings=sum_earnings;
					BEST_PRICING_ABANDON_STRATEGY.sum_expected_earnings_discounted=sum_earnings_discounted;


	
				}

			}
				
	
			
			//Free memory
			free_adt_capital_stock_vintages_array(&capital_stock);
			free_financing_capital_array(&temp_capital_financing);
			free_debt_item_array(&temp_loans);
			free_dt_monthly_estimations_array(&temp_variables_over_year);
	
	
		}
				
		//Pass these variables of the optimal price startegy to the next considered year 
		if(Y<MARKET_RESEARCH_DATA_PRICING.array[0].estimated_values.size-1)
		{
			for(i=0;i<capital_stock_at_end_of_year.size;i++)
			{
				remove_adt_capital_stock_vintages(&capital_stock_at_end_of_year,i);
				i--;
			}
	
			for(i=0;i<PROSPECTIVE_VARIABLES.array[Y].capital_stock_vintages.size;i++)
			{
				add_adt_capital_stock_vintages(&capital_stock_at_end_of_year, PROSPECTIVE_VARIABLES.array[Y].capital_stock_vintages.array[i].
				amount,PROSPECTIVE_VARIABLES.array[Y].capital_stock_vintages.array[i].productivity);
			}
		
		
			for(i=0;i<temp_capital_financing_at_end_of_year.size;i++)
			{
				remove_financing_capital(&temp_capital_financing_at_end_of_year,i);
			i--;
			}
		
			for(i=0;i<PROSPECTIVE_VARIABLES.array[Y].capital_financing.size;i++)
			{
				add_financing_capital(&temp_capital_financing_at_end_of_year, PROSPECTIVE_VARIABLES.array[Y].capital_financing.array[i].financing_per_month,
				PROSPECTIVE_VARIABLES.array[Y].capital_financing.array[i].nr_periods_before_repayment);
			}
		
			for(i=0;i<temp_loans_at_end_of_year.size;i++)
			{
				remove_debt_item(&temp_loans_at_end_of_year,i);
				i--;
			}
		
			for(i=0;i<PROSPECTIVE_VARIABLES.array[Y].loans.size;i++)
			{
				add_debt_item(&temp_loans_at_end_of_year, 0,PROSPECTIVE_VARIABLES.array[Y].loans.array[i].loan_value
					,PROSPECTIVE_VARIABLES.array[Y].loans.array[i].interest_rate,PROSPECTIVE_VARIABLES.array[Y].loans.array[i].installment_amount
					,0,0,0,PROSPECTIVE_VARIABLES.array[Y].loans.array[i].nr_periods_before_repayment);
				
					#ifdef _DEBUG_MODE    
 		   if (PRINT_DEBUG_MARKET_RESEARCH)
   			 {
				  if(ID==ID_DEBUG_PROBE)
     	       {
		    
					//printf( "fixed costs %f\n",MARKET_RESEARCH_DATA_PRICING.array[i].estimated_values.array[Y].estimated_fix_costs);
					

					//	printf( "PROSPECTIVE_VARIABLES.array[%d].loans.array[%d].loan_value %f installmet %f periods remaining %d\n",Y,i,PROSPECTIVE_VARIABLES.array[Y].loans.array[i].loan_value, PROSPECTIVE_VARIABLES.array[Y].loans.array[i].installment_amount,PROSPECTIVE_VARIABLES.array[Y].loans.array[i].nr_periods_before_repayment );
	
				}

  		  }
  		 #endif



			}
		
			mean_specific_skills_at_end_of_year = PROSPECTIVE_VARIABLES.array[Y].mean_specific_skills;
			estimated_mean_wage_at_end_of_year = PROSPECTIVE_VARIABLES.array[Y].estimated_mean_wage;
			no_employees_at_end_of_year = PROSPECTIVE_VARIABLES.array[Y].no_employees;
			payment_account_at_end_of_year =PROSPECTIVE_VARIABLES.array[Y].payment_account ;
			earnings_at_end_of_year= PROSPECTIVE_VARIABLES.array[Y].earnings;
			buffer_at_end_of_year = PROSPECTIVE_VARIABLES.array[Y].buffer;
		}	

	}		
	
	

	free_adt_capital_stock_vintages_array(&capital_stock_at_end_of_year);
	free_financing_capital_array(&temp_capital_financing_at_end_of_year);
	free_debt_item_array(&temp_loans_at_end_of_year);
	

	//Set price just set flag
	PRICE_JUST_SET_FLAG = 1;

	MARKET_RESEARCH_ACTIVE =0;

	COUNTER_MONTH_SINCE_LAST_PRICE_SETTING=0;
   
			#ifdef _DEBUG_MODE    
 		   if (PRINT_DEBUG_MARKET_RESEARCH)
   			 {
				  if(ID==ID_DEBUG_PROBE)
     	       {
					printf( "\nNew PRICE %f\n",PRICE);

					printf( "COMBINED_VARIANCE_DEMAND_FUNCTION %f\n",COMBINED_VARIANCE_DEMAND_FUNCTION );
			
				}
  		  }
  		 #endif

	return 0;
}




int Firm_decide_product_innovation()
{
	int i,j,k,t,Y,L;

	double mean_specific_skills;
	double estimated_mean_wage;
	double estimated_mean_wage_r_and_d;
	double no_employees;
	double payment_account ;
	double earnings;
	double average_productivity;
	double eff_productivity;
	double used_capital_stock;
	double sum_output;
	double pot_output;
	double capital_stock_depreciation_units;
	double installment_payment;
	double investment_nominal;
	double planned_output;	
	double labour_demand;
	double interest_payments;
	double debt_needed;
	double realized_output;
	double sum_earnings;
	double sum_earnings_discounted;
	double monthly_wage_growth;
	double yearly_discont_factor;
	double monthly_discont_factor;
	double value;
	double probability;
	double actual_sales_estimation;
	double buffer, current_stocks, critical_stock,combined_variance_demand_function, expected_sales ;
	


	monthly_wage_growth = 1+VARIABLES_CHANGE.productivity_progress;

	
	//Deleting some variables

	for(i=0;i<BEST_PRICING_STRATEGIES.size;i++)
	{
		remove_dt_best_price_strategies(&BEST_PRICING_STRATEGIES,i);
		i--;
	}

	// 1. For each quality search for the best pricing strategy for the following year
	for(i=0; i<MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.size; i++)
	{

		//	adt_capital_stock_vintages_array capital_stock_at_end_of_year;
		//	init_adt_capital_stock_vintages_array(&capital_stock_at_end_of_year);

		//	financing_capital_array temp_capital_financing_at_end_of_year;
			//init_financing_capital_array(&temp_capital_financing_at_end_of_year);


		//	debt_item_array temp_loans_at_end_of_year;
		//	init_debt_item_array(&temp_loans_at_end_of_year);


		

			for(j=0; j <MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.size;j++)
			{

				
		
				adt_capital_stock_vintages_array capital_stock;
				init_adt_capital_stock_vintages_array(&capital_stock);

				financing_capital_array temp_capital_financing;
				init_financing_capital_array(&temp_capital_financing);

				debt_item_array temp_loans;
				init_debt_item_array(&temp_loans);
	
					for(k=0;k<PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].capital_stock_vintages.size;k++)
					{
						add_adt_capital_stock_vintages(&capital_stock,PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].capital_stock_vintages.array[k].
							amount,PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].capital_stock_vintages.array[k].productivity);
					}

					for(k=0;k<PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].capital_financing.size;k++)
					{
						add_financing_capital(&temp_capital_financing, PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].capital_financing.array[k].financing_per_month,
							PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].capital_financing.array[k].nr_periods_before_repayment);
					}

					for(k=0;k<PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].loans.size;k++)
					{
						add_debt_item(&temp_loans, 0,PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].loans.array[k].loan_value,PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].loans.array[k].interest_rate,
							PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].loans.array[k].installment_amount
							,0,0,0,	PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].loans.array[k].nr_periods_before_repayment);
					}

					mean_specific_skills = PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].mean_specific_skills;
					estimated_mean_wage = PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].estimated_mean_wage;
					no_employees = PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].no_employees;
					payment_account = PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].payment_account;
					earnings= PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].earnings;
					buffer =  PROSPECTIVE_VARIABLES.array[PROSPECTIVE_VARIABLES.size-1].buffer;



				
				current_stocks = buffer;


				//Reset the earnings 

				MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_earnings =0.0;

				//Fixed Costs
				MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_fix_costs = CALC_CAPITAL_COSTS + TOTAL_INTEREST_PAYMENT +  LABOUR_COSTS_INNOVATION;

				sum_earnings=0.0;
				sum_earnings_discounted=0.0;
			
				for(k=0;k< DEMAND_FUNCTIONS_PRODUCT_INNOVATION.size;k++)
				{
					if(REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT== DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].year && DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].quality ==MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality)
					{
						combined_variance_demand_function = pow(MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].probability,2)*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance + 
						pow(LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept+
						 REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT*12*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor,2)
							*DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].variance/
						(1.0*pow	(ACTUAL_SAMPLE_SIZE,2))+DEMAND_FUNCTIONS_PRODUCT_INNOVATION.array[k].variance/(1.0*pow(ACTUAL_SAMPLE_SIZE,2))	
						*LINEAR_REGRESSION_MARKET_SIZE.array[0].variance;
					}

				}


			



				buffer = QUANTIL_NORMAL_DISTRIBUTION*pow(combined_variance_demand_function ,0.5);

				for(t=0;t<12;t++)
				{

					average_productivity=0.0;
					eff_productivity=0.0;
					used_capital_stock=0.0;
					sum_output=0;
					pot_output=0;
					capital_stock_depreciation_units=0.0;
					installment_payment=0.0;
					interest_payments=0.0;
					investment_nominal=0.0;


					//Expected sales are linear combination of market shares at the beginning and the end of the year times market size		
					expected_sales =  ((LINEAR_REGRESSION_MARKET_SIZE.array[0].intercept 
						+ (1+LAST_MARKET_SIZES.array[0].market_sizes.size+12*REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT+t)*LINEAR_REGRESSION_MARKET_SIZE.array[0].regressor + 
						QUANTIL_NORMAL_DISTRIBUTION*pow(LINEAR_REGRESSION_MARKET_SIZE.array[0].variance,0.5))
						)*((t/11.0)*MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[1].probability+((11-t)/11.0)*
						MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].probability);
				
					//Set critical stock: Expected sales plus buffer
					critical_stock = expected_sales + buffer;

					//Set output: Difference of critical and current stock 
					planned_output = max(critical_stock - current_stocks, 0);
	
	

					//Fix costs:

					// Capital costs for sunk investments:

					MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_fix_costs=0;


					for(k=0; k< temp_capital_financing.size;k++)
					{
						if(temp_capital_financing.array[k].nr_periods_before_repayment==0)
                		{
                   		 remove_financing_capital(&temp_capital_financing,k);
                  		  k--;
               			}else
                		{
                			temp_capital_financing.array[k].nr_periods_before_repayment--;
                			MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_fix_costs
								+= temp_capital_financing.array[k].financing_per_month;
                		}
					}	

					//Interest payments:
					for(k=0;k<temp_loans.size;k++)
					{
						if(temp_loans.array[k].nr_periods_before_repayment>0)
						{
							interest_payments=temp_loans.array[k].loan_value* temp_loans.array[k].interest_rate/12.0;
							MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_fix_costs
								+=interest_payments;
								installment_payment += temp_loans.array[k].installment_amount;
								temp_loans.array[k].loan_value-=temp_loans.array[k].installment_amount;
								temp_loans.array[k].nr_periods_before_repayment--;

							
						}else
						{
							remove_debt_item(&temp_loans,k);
							k--;
						}
					}		

					//Compute input factor needs
					for(k=capital_stock.size-1;k>=0;k--)
					{
	
						capital_stock.array[k].amount= capital_stock.array[k].amount*(1-DEPRECIATION_RATE);
						capital_stock_depreciation_units+=capital_stock.array[k].amount*DEPRECIATION_RATE;
				
						if(sum_output < planned_output)
						{
							pot_output += min(mean_specific_skills,capital_stock.array[k].productivity)*capital_stock.array[k].amount;

							if(pot_output>planned_output)
							{
								double sum_cap_selected_vintage=(planned_output - sum_output)
									/min(mean_specific_skills,capital_stock.array[k].productivity);
								sum_output += (planned_output - sum_output);
								used_capital_stock+=sum_cap_selected_vintage;
								average_productivity += capital_stock.array[k].productivity*sum_cap_selected_vintage;
								eff_productivity+=min(capital_stock.array[k].productivity,mean_specific_skills)*sum_cap_selected_vintage;

							}else
							{
								used_capital_stock+=capital_stock.array[k].amount;		
								sum_output += min(mean_specific_skills,capital_stock.array[k].productivity)*capital_stock.array[k].amount;
								average_productivity += capital_stock.array[k].productivity*capital_stock.array[k].amount;
								eff_productivity+=min(capital_stock.array[k].productivity,mean_specific_skills)*capital_stock.array[k].amount;
							}

								
						}
					}
	
				
					if(sum_output < planned_output)
					{
						double inv;

						inv = (planned_output - sum_output)/ min(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity,mean_specific_skills);

						inv = min(inv, INV_INERTIA*capital_stock_depreciation_units);
						used_capital_stock+=inv;
						average_productivity += TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity*inv;
						eff_productivity+=min(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity,mean_specific_skills)*inv;
						
						for(k=0; k<capital_stock.size;k++)
						{
							if(abs_double(TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity-capital_stock.array[k].productivity)<1e-5)
							{
								
								capital_stock.array[k].amount+=inv;
									
								
							}else
							{
								if(k==capital_stock.size-1)
								{
									add_adt_capital_stock_vintages(&capital_stock,inv,TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].productivity);
								}
							}
						}
						/* If subsidies for best vintage are switched on: reduce the effective price
						 for best practice technology*/				
						if(POLICY_EXP_BEST_TECHNOLOGY_SUBSIDY==1 && abs_double(TECHNOLOGY_VINTAGES.array[i].productivity - TECHNOLOGICAL_FRONTIER)<1e-5)
						{
							investment_nominal=inv*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price*(1-SUBSIDY_PCT);
						}else
						{	
							investment_nominal=inv*TECHNOLOGY_VINTAGES.array[VINTAGE_SELECTED].price;
						}

						add_financing_capital(&temp_capital_financing,
						    investment_nominal/CONST_INSTALLMENT_PERIODS,CONST_INSTALLMENT_PERIODS);
						
				
					}


				

			
					labour_demand = used_capital_stock;
					if(used_capital_stock>1e-5)
					{
						average_productivity = average_productivity / used_capital_stock;
						eff_productivity=eff_productivity/used_capital_stock;
					}else
					{
						average_productivity = TECHNOLOGY;
						eff_productivity=TECHNOLOGY;

					}
					realized_output= used_capital_stock*eff_productivity;

					current_stocks +=realized_output;
			
					//Compute mean wage:	
		
					if(labour_demand>no_employees)
					{
						estimated_mean_wage =no_employees/(1.0*labour_demand) * estimated_mean_wage  
						+ (labour_demand - no_employees)/(1.0*labour_demand)*WAGE_OFFER*min(average_productivity,mean_specific_skills );

					}

					//Compute variable costs
					if(realized_output>1e-5)
					{
						MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_variable_costs = 	
						(labour_demand*estimated_mean_wage + 
						investment_nominal/CONST_INSTALLMENT_PERIODS)/realized_output;
					}
					else
					{
						MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_variable_costs = 0.0;
					}

					//Check financing:

					payment_account= payment_account - labour_demand*estimated_mean_wage - 
						investment_nominal  -
						 interest_payments - installment_payment -max(0,earnings)*TAX_RATE_CORPORATE - max(0,earnings)*(1-TAX_RATE_CORPORATE)
						*CONST_DIVIDEND_EARNINGS_RATIO;


					//Check if additional loans are necessary
					debt_needed = (-1)*min(payment_account,0);
					
					if(debt_needed>1e-5)
					{
					add_debt_item(&temp_loans, 0,debt_needed,LAST_INTEREST_RATE_FOR_LOANS,debt_needed/CONST_INSTALLMENT_PERIODS,
						0,0,0,CONST_INSTALLMENT_PERIODS);
					}
					payment_account+= debt_needed;


					actual_sales_estimation = min(current_stocks,expected_sales);


					//Compute earnings
					earnings= actual_sales_estimation* (MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price - 
						MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_variable_costs)  - 
						MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_fix_costs;




							#ifdef _DEBUG_MODE    
 	 			if (PRINT_DEBUG_MARKET_RESEARCH)
   		 		{
			  		if(ID==ID_DEBUG_PROBE)
            		{

						printf( "Quality:  %f  Price: %f  earnings %f  actual_sales_estimation %f   expected_sales %f buffer%f\n",MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality, 
							MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price,
							earnings,actual_sales_estimation,expected_sales, buffer);
					}

   				 }
   				 #endif




	

					sum_earnings += earnings;
					sum_earnings_discounted+=pow(1/(1+DISCONT_RATE),t)*earnings;
			
					MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_earnings += 
						pow(1/(1+DISCONT_RATE),REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT*12+t)*earnings;

						//Add expected earnings on payment account
					payment_account+= actual_sales_estimation*MARKET_RESEARCH_DATA_PRICING.array[i].price;

					current_stocks -=actual_sales_estimation;

					//Update mean wage:

					estimated_mean_wage = estimated_mean_wage*monthly_wage_growth;

					no_employees  = labour_demand;


					// Skill update:

					if(SKILL_UPDATE_ACC_TO_FORMULA==1)
					{
      						/*Update the specific skill: depends on the actual specific skill, 
        					the gap between the actual specific skills and the actual productivity of the employer,
        					and the general skill which determines the speed of closing the this gap.*/
       						mean_specific_skills = max(mean_specific_skills, mean_specific_skills+ 
							max(average_productivity-mean_specific_skills,0)
							*((1-pow(0.5,1/(20+0.25*(AVERAGE_G_SKILL-1)*(4-20))))));
					}else
					{
	 					 /*Update the specific skill: depends on the actual specific skill, 
       						 the gap between the actual specific skills and the actual productivity of
						 the employer. The rate is predetermined.*/

						mean_specific_skills = max(mean_specific_skills, mean_specific_skills+ max(average_productivity-mean_specific_skills,0)		     
								*AVERAGE_ADAPTATION_SPEED_SPECIFIC_SKILLS);

					
					}



				}

				#ifdef _DEBUG_MODE    
 	 			if (PRINT_DEBUG_MARKET_RESEARCH)
   		 		{
			  		if(ID==ID_DEBUG_PROBE)
            		{

						printf( "Quality:  %f  Price: %f  estimated_earnings %f  probability  %f no positive respones %d \n",MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality, 
							MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price,
							MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_earnings,
							MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].probability,MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array			
							[i].market_research_price.array[j].estimated_values.array[0].no_positive_response);
					}

   				 }
   				 #endif
		


				if(j==0)
				{
					add_dt_best_price_strategies(&BEST_PRICING_STRATEGIES,MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].quality,	
						MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price,
						MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_earnings,sum_earnings,sum_earnings_discounted);

					
					
				
				}else
				{
					if(MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_earnings>
						BEST_PRICING_STRATEGIES.array[i].expected_earnings)
					{
						BEST_PRICING_STRATEGIES.array[i].expected_earnings=
							MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].estimated_values.array[0].estimated_earnings;
						BEST_PRICING_STRATEGIES.array[i].price=
							MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.array[i].market_research_price.array[j].price;

						BEST_PRICING_STRATEGIES.array[i].sum_earnings = sum_earnings;
						BEST_PRICING_STRATEGIES.array[i].sum_expected_earnings_discounted=sum_earnings_discounted;

					}
		
				}
				
				free_adt_capital_stock_vintages_array(&capital_stock);
				free_financing_capital_array(&temp_capital_financing);
				free_debt_item_array(&temp_loans);

			}
		
		
	}
	

	yearly_discont_factor= 1/pow(1+DISCONT_RATE,12); 

	monthly_discont_factor=1/(1+DISCONT_RATE);	



		#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "yearly_discont_factor %f   monthly_discont_factor  %f  DISCONT_RATE %f \n",yearly_discont_factor,monthly_discont_factor,DISCONT_RATE);



			printf("BEST_PRICING_ABANDON_STRATEGY.sum_expected_earnings_discounted  %f ,BEST_PRICING_ABANDON_STRATEGY.sum_earnings %f\n",
BEST_PRICING_ABANDON_STRATEGY.sum_expected_earnings_discounted ,BEST_PRICING_ABANDON_STRATEGY.sum_earnings);
		}

    }
    #endif

	estimated_mean_wage_r_and_d = MEAN_WAGE_R_AND_D;

	
	//Create the lattice
	for(i=VALUE_LATTICE.size-1;i>=0;i--)
	{
		remove_dt_value_lattice_years(&VALUE_LATTICE,i);
	}


	add_dt_value_lattice_years(&VALUE_LATTICE,0,0);
	add_dt_value_lattice(&VALUE_LATTICE.array[0].values,INTERMEDIATE_QUALITY,0.0,0);
	
	for(Y=1;Y<REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT;Y++)
	{
		add_dt_value_lattice_years(&VALUE_LATTICE,Y,0);
		for(i=0;i<VALUE_LATTICE.array[Y-1].values.size;i++)
		{	
			add_dt_value_lattice(&VALUE_LATTICE.array[Y].values,VALUE_LATTICE.array[Y-1].values.array[i].intermediate_quality-QUALITY_CHANGE,0.0,0);
		
		}
		add_dt_value_lattice(&VALUE_LATTICE.array[Y].values,VALUE_LATTICE.array[Y].values.array[VALUE_LATTICE.array[Y-1].values.size-1].intermediate_quality+2*QUALITY_CHANGE,0.0,0);
		
	}


	//For first month: check fianancing and number of fundable R&D employees
	NO_EMPLOYEES_PRODUCT_INNOVATION_FUNDABLE = Firm_check_fiancial_situation_for_product_innovation(REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT); 

	#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "NO_EMPLOYEES_PRODUCT_INNOVATION_FUNDABLE %d \n",NO_EMPLOYEES_PRODUCT_INNOVATION_FUNDABLE);
		}

    }
    #endif
		

	//DETERMINING the value of the R&D project: backward reduction

	//Starting with last point of decicision
			
		for(i=0;i<VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.size;i++)
		{
			double lowest_quality, medium_quality;	
			double expected_cash_flow_lowest_quality, expected_cash_flow_medium_quality;
			double value_abandon;	
	
			//two possible outcome:

			lowest_quality = VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].intermediate_quality - QUALITY_CHANGE;	
			medium_quality = VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].intermediate_quality + QUALITY_CHANGE;
		

			//Computing the corresponding expected cash flows
			for(j=0;j<BEST_PRICING_STRATEGIES.size;j++)
			{
				if(abs_double(BEST_PRICING_STRATEGIES.array[j].quality-lowest_quality)<1e-5)
				{
					expected_cash_flow_lowest_quality= BEST_PRICING_STRATEGIES.array[j].sum_expected_earnings_discounted + BEST_PRICING_STRATEGIES.array[j].sum_earnings 
						* (pow(yearly_discont_factor,2))/(1-yearly_discont_factor);
	
	
					#ifdef _DEBUG_MODE    
 	   		if (PRINT_DEBUG_MARKET_RESEARCH)
   			 {
				  if(ID==ID_DEBUG_PROBE)
        	    {
		    
				printf( "quality    %f:   sum_exp_earnings   %f   BEST_PRICING_STRATEGIES.array[j].sum_earnings  %f \n",lowest_quality, BEST_PRICING_STRATEGIES.array[j].sum_expected_earnings_discounted ,BEST_PRICING_STRATEGIES.array[j].sum_earnings);
			}

    		}
    		#endif



				}else if(abs_double(BEST_PRICING_STRATEGIES.array[j].quality-medium_quality)<1e-5)
				{
					expected_cash_flow_medium_quality=BEST_PRICING_STRATEGIES.array[j].sum_expected_earnings_discounted + BEST_PRICING_STRATEGIES.array[j].sum_earnings 
						* (pow(yearly_discont_factor,2))/(1-yearly_discont_factor);

						#ifdef _DEBUG_MODE    
 	   					if (PRINT_DEBUG_MARKET_RESEARCH)
   		 				{
				  		if(ID==ID_DEBUG_PROBE){
		    				printf( "quality    %f:   sum_exp_earnings   %f   BEST_PRICING_STRATEGIES.array[j].sum_earnings  %f \n",medium_quality, 
							BEST_PRICING_STRATEGIES.array[j].sum_expected_earnings_discounted ,BEST_PRICING_STRATEGIES.array[j].sum_earnings);}}
    					#endif

				}
			}

			#ifdef _DEBUG_MODE    
 	      if (PRINT_DEBUG_MARKET_RESEARCH)
   		  {
	   	  if(ID==ID_DEBUG_PROBE)
            {    
				printf( "expected_cash_flow_lowest_quality for qu %f: %f   expected_cash_flow_medium_quality for qu %f:  %f \n",lowest_quality, expected_cash_flow_lowest_quality,medium_quality, expected_cash_flow_medium_quality );
				}
    		}
    		#endif

		

		for(L=1;L<NO_EMPLOYEES_PRODUCT_INNOVATION_FUNDABLE+1;L++)
		{

			value = 0.0;

			//Expenditures for 12 month:
			for(t=0;t<12;t++)
			{
				value -= L * 1/pow(1+DISCONT_RATE,t)* estimated_mean_wage_r_and_d*pow(monthly_wage_growth,12*(VALUE_LATTICE.size-1) + t);
	
			}

			probability = (L)/(1.0*MAX_NO_EMPLOYEES_PRODUCT_INNOVATION+1);; 

			value+=  (probability*expected_cash_flow_medium_quality + (1-probability)*expected_cash_flow_lowest_quality)*(yearly_discont_factor);
			




		#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "L %d   probability %f  value %f \n",L, probability, value);
		}

    }
    #endif



			if(L==1)
			{
				VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].value=value;
				VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].strategy=L;
			}else
			{
				if(value>VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].value)
				{
					VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].value=value;
					VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].strategy=L;
				}

			}
		
			
		}


		value_abandon = yearly_discont_factor*(BEST_PRICING_ABANDON_STRATEGY.sum_expected_earnings_discounted +  max(RATIO_PROJECT_VALUE_ESTABLISHED_PRODUCT,1)*BEST_PRICING_ABANDON_STRATEGY.sum_earnings 
						* (pow(yearly_discont_factor,2))/(1-yearly_discont_factor));



			#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].value %f value_abandon %f VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].strategy %d  \n",VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].value, value_abandon, VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].strategy);
		}

    }
    #endif



		if(VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].value< value_abandon)
		{
			VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].value=value_abandon;
			VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].strategy=-1;

		}



		#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "Choosen strategy:  VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].strategy %d  \n", VALUE_LATTICE.array[VALUE_LATTICE.size-1].values.array[i].strategy);
		}

    }
    #endif
		

	
	}


	///The next periods:
	for(Y=VALUE_LATTICE.size-2;Y>=0;Y--)
	{

		for(i=0;i<VALUE_LATTICE.array[Y].values.size;i++)
		{
			double lowest_quality, medium_quality;	
			double value_lowest_quality, value_medium_quality;
			double value_abandon;	
	
			//Two possible outcome:

			lowest_quality = VALUE_LATTICE.array[Y].values.array[i].intermediate_quality - QUALITY_CHANGE;	
			medium_quality = VALUE_LATTICE.array[Y].values.array[i].intermediate_quality + QUALITY_CHANGE;
			

			//Computing the corresponding expected cash flows
			for(j=0;j<VALUE_LATTICE.array[Y+1].values.size;j++)
			{
				if(abs_double(VALUE_LATTICE.array[Y+1].values.array[j].intermediate_quality-lowest_quality)<1e-5)
				{
					value_lowest_quality= VALUE_LATTICE.array[Y+1].values.array[j].value;

				}else if(abs_double(VALUE_LATTICE.array[Y+1].values.array[j].intermediate_quality-medium_quality)<1e-5)	
				{
					value_medium_quality=VALUE_LATTICE.array[Y+1].values.array[j].value;
	
				}
			}

			

						#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "value_lowest_quality for qu %f: %f   value_medium_quality for qu %f:  :  %f \n",lowest_quality, value_lowest_quality,medium_quality,value_medium_quality);
		}

    }
    #endif


			

			for(L=1;L<NO_EMPLOYEES_PRODUCT_INNOVATION_FUNDABLE+1;L++)
			{

				value = 0.0;

				//Expenditures for 12 month:
				for(t=0;t<12;t++)
				{
					value -= L * 1/pow(1+DISCONT_RATE,t)* estimated_mean_wage_r_and_d*pow(monthly_wage_growth,Y*12+t);
	
				}

				probability = (L)/(1.0*MAX_NO_EMPLOYEES_PRODUCT_INNOVATION+1); 

				value+=  (probability*value_medium_quality + (1-probability)*value_lowest_quality)*(yearly_discont_factor);
				



						#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "L %d   probability %f  value %f \n",L, probability, value);
		}

    }
    #endif

	
				if(L==1)
				{
					VALUE_LATTICE.array[Y].values.array[i].value=value;
					VALUE_LATTICE.array[Y].values.array[i].strategy=L;
				}else
				{
					if(value>VALUE_LATTICE.array[Y].values.array[i].value)
					{
						VALUE_LATTICE.array[Y].values.array[i].value=value;
						VALUE_LATTICE.array[Y].values.array[i].strategy=L;
					}
	
				}
		
			
			}

	
			// Strategy Abandon 0 R&D Employees
	

			value_abandon = pow(yearly_discont_factor,REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT-Y)*
				(BEST_PRICING_ABANDON_STRATEGY.sum_expected_earnings_discounted + max(RATIO_PROJECT_VALUE_ESTABLISHED_PRODUCT,1)*BEST_PRICING_ABANDON_STRATEGY.sum_earnings 
						* (pow(yearly_discont_factor,2))/(1-yearly_discont_factor))   ;


			if(VALUE_LATTICE.array[Y].values.array[i].value<value_abandon)
			{
				VALUE_LATTICE.array[Y].values.array[i].value=value_abandon;
				VALUE_LATTICE.array[Y].values.array[i].strategy=-1;

			}



		


					#ifdef _DEBUG_MODE    
 	   if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "VALUE_LATTICE.array[%d].values.array[%d].value %f value_abandon %f VALUE_LATTICE.array[%d].values.array[%d].strategy %d  \n",Y,i,VALUE_LATTICE.array[Y].values.array[i].value, value_abandon,  Y, i,VALUE_LATTICE.array[Y].values.array[i].strategy);

			printf( "Choosen strategy:  VALUE_LATTICE.array[Y].values.array[i].strategy %d  \n", VALUE_LATTICE.array[Y].values.array[i].strategy);
		}

    }
    #endif



		}

	}

	/*If the firm has to decide to start a project, it determines the ratio of the project compared to the the value of keeping
	 the current product at the market. 
	This is used for determining the outside option when deciding whether or not to continue the r and d project*/
	if(REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT ==  TOTAL_NO_PERIODS_FOR_PRODUCT_DEVELOPMENT)
	{	
		
		double value_keep_product_at_market= pow(yearly_discont_factor,REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT)*
			(BEST_PRICING_ABANDON_STRATEGY.sum_expected_earnings_discounted + BEST_PRICING_ABANDON_STRATEGY.sum_earnings 
			* (pow(yearly_discont_factor,2))/(1-yearly_discont_factor));

		RATIO_PROJECT_VALUE_ESTABLISHED_PRODUCT = VALUE_LATTICE.array[0].values.array[0].value /value_keep_product_at_market;
		
	}


		#ifdef _DEBUG_MODE    
 	 	  if (PRINT_DEBUG_MARKET_RESEARCH)
   		 {
			  if(ID==ID_DEBUG_PROBE)
            {
		    
			printf( "RATIO_PROJECT_VALUE_ESTABLISHED_PRODUCT %f   \n",RATIO_PROJECT_VALUE_ESTABLISHED_PRODUCT);
			}
		 }
   		 #endif



	//Set R&D strategy:

	if(VALUE_LATTICE.array[0].values.array[0].strategy==-1)
	{	
		OPTIMAL_EMPLOYEES_NEEDED_INNOVATION=0;
		TOTAL_PERSON_MONTHS=0;
		INNOVATION_FLAG=0;
		//ACTUAL_R_AND_D_SUCCESS_PROBABILITY=0.0;
		CUM_PERSON_MONTHS=0;
		INTERMEDIATE_QUALITY = QUALITY;
		REMAINING_PERIODS_TO_COMPLETE_PRODUCT_DEVELOPMENT =  TOTAL_NO_PERIODS_FOR_PRODUCT_DEVELOPMENT;
		
	}else
	{
		OPTIMAL_EMPLOYEES_NEEDED_INNOVATION=VALUE_LATTICE.array[0].values.array[0].strategy;
		TOTAL_PERSON_MONTHS=OPTIMAL_EMPLOYEES_NEEDED_INNOVATION*12;
		INNOVATION_FLAG=1;
		//ACTUAL_R_AND_D_SUCCESS_PROBABILITY=0.0;
		CUM_PERSON_MONTHS=0;

	}




	INNOVATION_MONTH_COUNTER=0;

	

	return 0;
}



int Firm_clean_up_arrays()
{

int i;

	#ifndef _DEBUG_MODE 
	//Delete MARKET_RESEARCH_DATA_PRICING
	for(i=MARKET_RESEARCH_DATA_PRICING.size-1;i>=0;i--)
	{
		remove_dt_market_research_price(&MARKET_RESEARCH_DATA_PRICING,i);
	}
	//Delete MARKET_RESEARCH_DATA_PRODUCT_INNOVATION
	for(i=MARKET_RESEARCH_DATA_PRODUCT_INNOVATION.size-1;i>=0;i--)
	{
	remove_dt_market_research_qualities(&MARKET_RESEARCH_DATA_PRODUCT_INNOVATION,i);	
	}
	//delete array PROSPECTIVE_VARIABLES

	for(i=PROSPECTIVE_VARIABLES.size-1;i>=0;i--)
	{
		remove_dt_prospective_variables(&PROSPECTIVE_VARIABLES,i);
	}
	
	 #endif
return 0;
}

