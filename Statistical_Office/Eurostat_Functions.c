//#include <assert.h>
#include "../header.h"
#include "../Eurostat_agent_header.h"
#include "../my_library_header.h"
#include "Eurostat_aux_header.h"

/** \Eurostat_idle()
  */
int Eurostat_idle()
{
    return 0;   
}

/** \Eurostat_initialization()
  */
int Eurostat_initialization()
{
    if(TOTAL_REGIONS>REGION_FIRM_DATA.size)
    {   

        printf("\nIn Eurostat_initialization:");
        printf("\nTOTAL_REGIONS (%d) > size of REGION_FIRM_DATA array (%d)", TOTAL_REGIONS, REGION_FIRM_DATA.size);
    
        printf("\n      Running Eurostat_reset_data function to reset data structures");
        Eurostat_reset_data();

        if(TOTAL_REGIONS==REGION_FIRM_DATA.size)
            printf("\n      TOTAL_REGIONS (%d) == size of REGION_FIRM_DATA array (%d)\n", TOTAL_REGIONS, REGION_FIRM_DATA.size);
    }
    assert(TOTAL_REGIONS==REGION_FIRM_DATA.size);

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG)
    {
        printf("\n Eurostat_initialization");
        getchar();
    }
    #endif
        
    return 0;   
}

/** \Eurostat_send_data_to_government()
 * \brief Eurostat send data: mean wage  ...
 * OBSOLETE FUNCTION
 */   
int Eurostat_send_data_to_government()
{
    int i, region;
    double gdp;
    
    //printf("AVERAGE_WAGE %f\n",AVERAGE_WAGE);
    //add_mean_wage_for_government_message(1, AVERAGE_WAGE);

    //add message for each region
    for (i=0; i<TOTAL_REGIONS; i++)
    {
        region = i+1;
        
        gdp = REGION_FIRM_DATA.array[i].gdp;
        
        printf("\n Region %d GDP=%2.2f\n", region, gdp);
        add_data_for_government_message(region, gdp, AVERAGE_WAGE);
    }
    
    return 0;
}

/** \Eurostat_send_data()
 * \brief Eurostat send data: specific skills ...
 */
int Eurostat_send_data()
{
    int i, region;
    double gdp;
    
    /*First of every month*/
    /*Send the data*/

	//send message about the total market size
	add_msg_market_sizes_message(0, TOTAL_CONSUMPTION_BUDGET);
    
   
    for(i = 0; i < REGION_HOUSEHOLD_DATA.size; i++)
    {
        add_eurostat_send_specific_skills_message(
        REGION_HOUSEHOLD_DATA.array[i].region_id,  
	REGION_HOUSEHOLD_DATA.array[i].average_s_skill, 
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_1, 
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_2,
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_3, 
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_4, 
        REGION_HOUSEHOLD_DATA.array[i].average_s_skill_5,
        REGION_FIRM_DATA.array[i].productivity_progress,
	REGION_FIRM_DATA.array[i].average_wage,
	HISTORY_MONTHLY[0].region_data.array[i].output/HISTORY_MONTHLY[0].region_data.array[i].no_active_firms,
        CPI,PRICE_INDEX,NO_FIRMS,NO_ACTIVE_FIRMS,FIRM_AVERAGE_QUALITY,FIRM_AVERAGE_PRICE,TOTAL_CAPITAL_STOCK_UNITS);

	#ifdef _DEBUG_MODE    
	if (PRINT_DEBUG_EUROSTAT)
	{
		printf("\n\n Eurostat_send_data: added eurostat_send_specific_skills_message, region %d\n", i);
	}          
	#endif        

	
	//send message about the regional market size
	add_msg_market_sizes_message(REGION_HOUSEHOLD_DATA.array[i].region_id,  REGION_HOUSEHOLD_DATA.array[i].consumption_budget );
	

	/*Here Eurostat sends average general skills, aberage specific skills and the average productivity progress of the total economy to the IG firm
	There it is needed for determining the IG price.*/
	if(DAY>1)
	{
		add_msg_skills_eurostat_to_igfirm_message(FIRM_AVERAGE_G_SKILL,FIRM_AVERAGE_S_SKILL,FIRM_AVERAGE_PRODUCTIVITY_PROGRESS,TOTAL_CAPITAL_STOCK_UNITS);

		#ifdef _DEBUG_MODE    
		if (PRINT_DEBUG_EUROSTAT)
		{
			printf("\n\n Eurostat_send_data: added msg_skills_eurostat_to_igfirm_message, region %d\n", i);
		}          
		#endif        
	}




	if(DAY%20 == 1)
	{
	    #ifdef _DEBUG_MODE    
	    if (PRINT_DEBUG_EUROSTAT)
	    {
		    printf("\n\n IT %d Eurostat send data",DAY);  
		    printf("\n\t REGION_FIRM_DATA.array[i].productivity_progress %f",REGION_FIRM_DATA.array[i].productivity_progress);
		    printf("\n\t REGION_HOUSEHOLD_DATA.size = %d REGION_HOUSEHOLD_DATA.array[i].average_s_skill = %f", REGION_HOUSEHOLD_DATA.size, REGION_HOUSEHOLD_DATA.array[i].average_s_skill);
	    }          
	    #endif        
	}
    }
	
	//Add message for each region
	for (i=0; i<TOTAL_REGIONS; i++)
	{
		region = i+1;
		
		gdp = REGION_FIRM_DATA.array[i].gdp;
		
		printf("\n Region %d GDP=%2.2f\n", region, gdp);
		add_data_for_government_message(region, gdp, AVERAGE_WAGE);
	}
	
	//Add message for general economy-wide macrodata 
	add_eurostat_send_macrodata_message(ANNUAL_GROWTH_RATES_MONTHLY.cpi, GDP, UNEMPLOYMENT_RATE);    
	
	#ifdef _DEBUG_MODE    
	if (PRINT_DEBUG_EUROSTAT)
	{
		printf("\n\n Eurostat_send_data: added eurostat_send_macrodata_message\n");
	}          
	#endif        

    return 0;
}


/** \fn Eurostat_calculate_data
 * \brief Eurostat receive micro data and calculates macro data
 */
int Eurostat_calculate_data()
{
    /* Eurostat auxiliary functions */
     Eurostat_reset_data();
     Eurostat_compute_mean_price();

     Eurostat_read_firm_data();
     Eurostat_compute_region_firm_data();
     Eurostat_compute_global_firm_data();

     Eurostat_read_household_data();
     Eurostat_compute_region_household_data();
     Eurostat_compute_global_household_data();

     Eurostat_calc_macro_data();
     Eurostat_calc_firm_population();
     Eurostat_calc_firm_survival_rates();
     
     Eurostat_measure_export();
     Eurostat_calc_price_index();    
    
    return 0;
}

/******************************* STORING MONTHLY DATA **************************************/
/* Datatype:

      struct history_item
      {
            double cpi;
            double gdp;
            double output;
            double employment;
            double unemployment_rate;
            double average_wage;    
       }

    //Static array of history items:
     history_item history_monthly[13];
     history_item history_quarterly[5];
    
    //Single history_items for storing the growth rates: 
    history_item monthly_growth_rates: month to month growth rate statistics
    history_item quarterly__growth_rates: quarter to quarter growth rate statistics
    history_item annual_growth_rates_monthly: annual growth rates (per month), measured as the percentage change over the same month in the previous year.
    history_item annual_growth_rates_quarterly: annual growth rates (per quarter), measured as the percentage change over the same quarter in the previous year.
*/

/* \fn: int Eurostat_store_history_monthly()
 * \brief: Central_Eurostat agent stores statistics to monthly history structure. 
 */
int Eurostat_store_history_monthly()
{   
    FILE *file1;
    char *filename;
    int i, region;
    region=0;
    
    //Shift history backwards
    /*
     * history_monthly[4].GDP = history_monthly[3].GDP;     //t-4 gets filled with value from t-3
     * history_monthly[3].GDP = history_monthly[2].GDP;     //t-3 gets filled with value from t-3
     * history_monthly[2].GDP = history_monthly[1].GDP;     //t-2 gets filled with value from t-2
     * history_monthly[1].GDP = history_monthly[0].GDP;     //t-1 gets filled with value from t-1
     * history_monthly[0].GDP = GDP;                        //t gets filled with value from t
     */

    //*********************************** Economy-wide data
    for (i=12; i>0; i--)
    {
      //t-i-1 gets filled with value from t-i
      HISTORY_MONTHLY[i].cpi = HISTORY_MONTHLY[i-1].cpi;
      HISTORY_MONTHLY[i].gdp = HISTORY_MONTHLY[i-1].gdp;
      HISTORY_MONTHLY[i].output = HISTORY_MONTHLY[i-1].output;
      HISTORY_MONTHLY[i].employment = HISTORY_MONTHLY[i-1].employment;
      HISTORY_MONTHLY[i].unemployment_rate = HISTORY_MONTHLY[i-1].unemployment_rate;
      HISTORY_MONTHLY[i].unemployment_rate_skill_1 = HISTORY_MONTHLY[i-1].unemployment_rate_skill_1;
      HISTORY_MONTHLY[i].unemployment_rate_skill_2 = HISTORY_MONTHLY[i-1].unemployment_rate_skill_2;
      HISTORY_MONTHLY[i].unemployment_rate_skill_3 = HISTORY_MONTHLY[i-1].unemployment_rate_skill_3;
      HISTORY_MONTHLY[i].unemployment_rate_skill_4 = HISTORY_MONTHLY[i-1].unemployment_rate_skill_4;
      HISTORY_MONTHLY[i].unemployment_rate_skill_5 = HISTORY_MONTHLY[i-1].unemployment_rate_skill_5;
      HISTORY_MONTHLY[i].average_wage = HISTORY_MONTHLY[i-1].average_wage;
      HISTORY_MONTHLY[i].no_firms = HISTORY_MONTHLY[i-1].no_firms;
      HISTORY_MONTHLY[i].no_active_firms = HISTORY_MONTHLY[i-1].no_active_firms;
      HISTORY_MONTHLY[i].no_firm_births = HISTORY_MONTHLY[i-1].no_firm_births;
      HISTORY_MONTHLY[i].no_firm_deaths = HISTORY_MONTHLY[i-1].no_firm_deaths;
      HISTORY_MONTHLY[i].investment_value = HISTORY_MONTHLY[i-1].investment_value;
    }
    
    //Store current value of history: [0] gets filled with current value
    HISTORY_MONTHLY[0].cpi = CPI;
    HISTORY_MONTHLY[0].gdp = GDP;                   
    HISTORY_MONTHLY[0].output = MONTHLY_OUTPUT;     
    HISTORY_MONTHLY[0].employment = EMPLOYED;       
    HISTORY_MONTHLY[0].unemployment_rate = UNEMPLOYMENT_RATE;
    HISTORY_MONTHLY[0].unemployment_rate_skill_1 = UNEMPLOYMENT_RATE_SKILL_1;
    HISTORY_MONTHLY[0].unemployment_rate_skill_2 = UNEMPLOYMENT_RATE_SKILL_2;
    HISTORY_MONTHLY[0].unemployment_rate_skill_3 = UNEMPLOYMENT_RATE_SKILL_3;
    HISTORY_MONTHLY[0].unemployment_rate_skill_4 = UNEMPLOYMENT_RATE_SKILL_4;
    HISTORY_MONTHLY[0].unemployment_rate_skill_5 = UNEMPLOYMENT_RATE_SKILL_5;
    HISTORY_MONTHLY[0].average_wage = FIRM_AVERAGE_WAGE;        
    HISTORY_MONTHLY[0].no_firms = NO_FIRMS;         
    HISTORY_MONTHLY[0].no_active_firms = NO_ACTIVE_FIRMS;         
    HISTORY_MONTHLY[0].no_firm_births = NO_FIRM_BIRTHS; 
    HISTORY_MONTHLY[0].no_firm_deaths = NO_FIRM_DEATHS; 
    HISTORY_MONTHLY[0].investment_value = MONTHLY_INVESTMENT_VALUE;

    //*********************************** Code to be tested: region data

    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        //Shift history backwards
        for (i=12; i>0; i--)
        {
            HISTORY_MONTHLY[i].region_data.array[region].cpi = HISTORY_MONTHLY[i-1].region_data.array[region].cpi;
            HISTORY_MONTHLY[i].region_data.array[region].gdp = HISTORY_MONTHLY[i-1].region_data.array[region].gdp;
            HISTORY_MONTHLY[i].region_data.array[region].output = HISTORY_MONTHLY[i-1].region_data.array[region].output;
            HISTORY_MONTHLY[i].region_data.array[region].employment = HISTORY_MONTHLY[i-1].region_data.array[region].employment;
            HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate = HISTORY_MONTHLY[i-1].region_data.array[region].unemployment_rate;
            HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_1 = HISTORY_MONTHLY[i-1].region_data.array[region].unemployment_rate_skill_1;
            HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_2 = HISTORY_MONTHLY[i-1].region_data.array[region].unemployment_rate_skill_2;
            HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_3 = HISTORY_MONTHLY[i-1].region_data.array[region].unemployment_rate_skill_3;
            HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_4 = HISTORY_MONTHLY[i-1].region_data.array[region].unemployment_rate_skill_4;
            HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_5 = HISTORY_MONTHLY[i-1].region_data.array[region].unemployment_rate_skill_5;
            HISTORY_MONTHLY[i].region_data.array[region].average_wage = HISTORY_MONTHLY[i-1].region_data.array[region].average_wage;
            HISTORY_MONTHLY[i].region_data.array[region].no_firms = HISTORY_MONTHLY[i-1].region_data.array[region].no_firms;
	    HISTORY_MONTHLY[i].region_data.array[region].no_active_firms = HISTORY_MONTHLY[i-1].region_data.array[region].no_active_firms;
            HISTORY_MONTHLY[i].region_data.array[region].no_firm_births = HISTORY_MONTHLY[i-1].region_data.array[region].no_firm_births;
            HISTORY_MONTHLY[i].region_data.array[region].no_firm_deaths = HISTORY_MONTHLY[i-1].region_data.array[region].no_firm_deaths;
            HISTORY_MONTHLY[i].region_data.array[region].investment_value = HISTORY_MONTHLY[i-1].region_data.array[region].investment_value;
        }
        
        //Store current value of history
        HISTORY_MONTHLY[0].region_data.array[region].cpi = REGION_FIRM_DATA.array[region].cpi;
        HISTORY_MONTHLY[0].region_data.array[region].gdp = REGION_FIRM_DATA.array[region].gdp;                   
        HISTORY_MONTHLY[0].region_data.array[region].output = REGION_FIRM_DATA.array[region].monthly_output;
        HISTORY_MONTHLY[0].region_data.array[region].employment = REGION_FIRM_DATA.array[region].employees;
        HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate = REGION_HOUSEHOLD_DATA.array[region].unemployment_rate;
        HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_1 = REGION_HOUSEHOLD_DATA.array[region].unemployment_rate_skill_1;
        HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_2 = REGION_HOUSEHOLD_DATA.array[region].unemployment_rate_skill_2;
        HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_3 = REGION_HOUSEHOLD_DATA.array[region].unemployment_rate_skill_3;
        HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_4 = REGION_HOUSEHOLD_DATA.array[region].unemployment_rate_skill_4;
        HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_5 = REGION_HOUSEHOLD_DATA.array[region].unemployment_rate_skill_5;
        HISTORY_MONTHLY[0].region_data.array[region].average_wage = REGION_HOUSEHOLD_DATA.array[region].average_wage;
        HISTORY_MONTHLY[0].region_data.array[region].no_firms = REGION_FIRM_DATA.array[region].no_firms;
	HISTORY_MONTHLY[0].region_data.array[region].no_active_firms = REGION_FIRM_DATA.array[region].no_active_firms;
        HISTORY_MONTHLY[0].region_data.array[region].no_firm_births = REGION_FIRM_DATA.array[region].no_firm_births; 
        HISTORY_MONTHLY[0].region_data.array[region].no_firm_deaths = REGION_FIRM_DATA.array[region].no_firm_deaths;   
        HISTORY_MONTHLY[0].region_data.array[region].investment_value = REGION_FIRM_DATA.array[region].monthly_investment_value;   
        
        if (PRINT_DEBUG_FILE_EXP1)
    {                       
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/eurostat_regional.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %f %f %f ",DAY,REGION_FIRM_DATA.array[region].gdp,REGION_FIRM_DATA.array[region].cpi,REGION_FIRM_DATA.array[region].monthly_output);
        fprintf(file1,"%d %f ",REGION_FIRM_DATA.array[region].employees,REGION_HOUSEHOLD_DATA.array[region].unemployment_rate);
        fprintf(file1," %f %d",REGION_HOUSEHOLD_DATA.array[region].average_wage,REGION_FIRM_DATA.array[region].no_firm_deaths);
        fprintf(file1," %d",region);
        fclose(file1);
        free(filename);
    }

    }

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_EUROSTAT)
    {
        printf("Monthly data recorded by Eurostat:\n");
        printf(" - monthly CPI: %f\n", HISTORY_MONTHLY[0].cpi);
        printf(" - monthly GDP: %f\n", HISTORY_MONTHLY[0].gdp);
        printf(" - monthly output: %f\n", HISTORY_MONTHLY[0].output);
        printf(" - monthly average employment: %d\n", HISTORY_MONTHLY[0].employment);
        printf(" - monthly average unemployment rate: %f\n", HISTORY_MONTHLY[0].unemployment_rate);
        printf(" - monthly average unemployment rate_skill_1: %f\n", HISTORY_MONTHLY[0].unemployment_rate_skill_1);
        printf(" - monthly average unemployment rate_skill_2: %f\n", HISTORY_MONTHLY[0].unemployment_rate_skill_2);
        printf(" - monthly average unemployment rate_skill_3: %f\n", HISTORY_MONTHLY[0].unemployment_rate_skill_3);
        printf(" - monthly average unemployment rate_skill_4: %f\n", HISTORY_MONTHLY[0].unemployment_rate_skill_4);
        printf(" - monthly average unemployment rate_skill_5: %f\n", HISTORY_MONTHLY[0].unemployment_rate_skill_5);        
        printf(" - monthly average wage: %f\n", HISTORY_MONTHLY[0].average_wage);
        printf(" - monthly average number of firms: %d\n", HISTORY_MONTHLY[0].no_firms);
	printf(" - monthly average number of active firms: %d\n", HISTORY_MONTHLY[0].no_active_firms); 
        printf(" - monthly total number of firm births: %d\n", HISTORY_MONTHLY[0].no_firm_births);
        printf(" - monthly total number of firm deaths: %d\n", HISTORY_MONTHLY[0].no_firm_deaths);
        printf(" - monthly investment_value: %f\n", HISTORY_MONTHLY[0].investment_value);
    }    
    #endif

   // #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_FILE_EXP1)
    {                       
        filename = malloc(40*sizeof(char));
        filename[0]=0;
        strcpy(filename, "its/eurostat.txt");      
        file1 = fopen(filename,"a");
        fprintf(file1,"\n %d %f %f %f ",DAY,HISTORY_MONTHLY[0].gdp,HISTORY_MONTHLY[0].cpi,HISTORY_MONTHLY[0].output);
        fprintf(file1,"%d %f ",HISTORY_MONTHLY[0].employment,HISTORY_MONTHLY[0].unemployment_rate);
        fprintf(file1," %f %d",HISTORY_MONTHLY[0].average_wage,HISTORY_MONTHLY[0].no_firm_deaths);
        fclose(file1);
        free(filename);
    }
   // #endif
        
    return 0;
}

/******************************* STORING QUARTERLY DATA **************************************/
/* \fn: int Eurostat_store_history_quarterly()
 * \brief: Central_Eurostat agent stores statistics to quarterly history structure. 
 */
int Eurostat_store_history_quarterly()
{
    int i, region;
    region=0;
    
    //*********************************** Economy-wide data
    //Shift history backwards
    for (i=4; i>0; i--)
    {
      //t-i-1 gets filled with value from t-i
      HISTORY_QUARTERLY[i].cpi = HISTORY_QUARTERLY[i-1].cpi;
      HISTORY_QUARTERLY[i].gdp = HISTORY_QUARTERLY[i-1].gdp;
      HISTORY_QUARTERLY[i].output = HISTORY_QUARTERLY[i-1].output;
      HISTORY_QUARTERLY[i].employment = HISTORY_QUARTERLY[i-1].employment;      
      HISTORY_QUARTERLY[i].unemployment_rate = HISTORY_QUARTERLY[i-1].unemployment_rate;
      HISTORY_QUARTERLY[i].unemployment_rate_skill_1 = HISTORY_QUARTERLY[i-1].unemployment_rate_skill_1;
      HISTORY_QUARTERLY[i].unemployment_rate_skill_2 = HISTORY_QUARTERLY[i-1].unemployment_rate_skill_2;
      HISTORY_QUARTERLY[i].unemployment_rate_skill_3 = HISTORY_QUARTERLY[i-1].unemployment_rate_skill_3;
      HISTORY_QUARTERLY[i].unemployment_rate_skill_4 = HISTORY_QUARTERLY[i-1].unemployment_rate_skill_4;
      HISTORY_QUARTERLY[i].unemployment_rate_skill_5 = HISTORY_QUARTERLY[i-1].unemployment_rate_skill_5;
      HISTORY_QUARTERLY[i].average_wage = HISTORY_QUARTERLY[i-1].average_wage;
      HISTORY_QUARTERLY[i].no_firms = HISTORY_QUARTERLY[i-1].no_firms;
      HISTORY_QUARTERLY[i].no_active_firms = HISTORY_QUARTERLY[i-1].no_active_firms;
      HISTORY_QUARTERLY[i].no_firm_births = HISTORY_QUARTERLY[i-1].no_firm_births;
      HISTORY_QUARTERLY[i].no_firm_deaths = HISTORY_QUARTERLY[i-1].no_firm_deaths;
      HISTORY_QUARTERLY[i].investment_value = HISTORY_QUARTERLY[i-1].investment_value;
    }
        
    //Reset first elements for sum
    HISTORY_QUARTERLY[0].cpi=1.0;
    HISTORY_QUARTERLY[0].gdp=0.0;
    HISTORY_QUARTERLY[0].output=0.0;
    HISTORY_QUARTERLY[0].employment=0.0;
    HISTORY_QUARTERLY[0].unemployment_rate=0.0;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_1=0.0;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_2=0.0;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_3=0.0;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_4=0.0;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_5=0.0;    
    HISTORY_QUARTERLY[0].average_wage=0.0;
    HISTORY_QUARTERLY[0].no_firms=0;
    HISTORY_QUARTERLY[0].no_active_firms=0;
    HISTORY_QUARTERLY[0].no_firm_births=0;
    HISTORY_QUARTERLY[0].no_firm_deaths=0;
    HISTORY_QUARTERLY[0].investment_value=0.0;

    //Store first value: construct quarterly sums from monthly history
    for (i=0; i<3; i++)
    {
        HISTORY_QUARTERLY[0].cpi                *= HISTORY_MONTHLY[i].cpi;
        HISTORY_QUARTERLY[0].gdp                += HISTORY_MONTHLY[i].gdp;
        HISTORY_QUARTERLY[0].output             += HISTORY_MONTHLY[i].output;
        HISTORY_QUARTERLY[0].employment         += HISTORY_MONTHLY[i].employment;        
        HISTORY_QUARTERLY[0].unemployment_rate  += HISTORY_MONTHLY[i].unemployment_rate;
        HISTORY_QUARTERLY[0].unemployment_rate_skill_1  += HISTORY_MONTHLY[i].unemployment_rate_skill_1;
        HISTORY_QUARTERLY[0].unemployment_rate_skill_2  += HISTORY_MONTHLY[i].unemployment_rate_skill_2;
        HISTORY_QUARTERLY[0].unemployment_rate_skill_3  += HISTORY_MONTHLY[i].unemployment_rate_skill_3;
        HISTORY_QUARTERLY[0].unemployment_rate_skill_4  += HISTORY_MONTHLY[i].unemployment_rate_skill_4;
        HISTORY_QUARTERLY[0].unemployment_rate_skill_5  += HISTORY_MONTHLY[i].unemployment_rate_skill_5;
        HISTORY_QUARTERLY[0].average_wage       += HISTORY_MONTHLY[i].average_wage;
        HISTORY_QUARTERLY[0].no_firms           += HISTORY_MONTHLY[i].no_firms;
	HISTORY_QUARTERLY[0].no_active_firms    += HISTORY_MONTHLY[i].no_active_firms;
        HISTORY_QUARTERLY[0].no_firm_births     += HISTORY_MONTHLY[i].no_firm_births;
        HISTORY_QUARTERLY[0].no_firm_deaths     += HISTORY_MONTHLY[i].no_firm_deaths;
        HISTORY_QUARTERLY[0].investment_value   += HISTORY_MONTHLY[i].investment_value;
    }
    //The following quarterly statistics are averages of monthly statistics
    //HISTORY_QUARTERLY[0].cpi                    = HISTORY_QUARTERLY[0].cpi/3;
    HISTORY_QUARTERLY[0].gdp                    = HISTORY_QUARTERLY[0].gdp;
    HISTORY_QUARTERLY[0].output                 = HISTORY_QUARTERLY[0].output;
    HISTORY_QUARTERLY[0].employment             = HISTORY_QUARTERLY[0].employment/3;
    HISTORY_QUARTERLY[0].unemployment_rate      = HISTORY_QUARTERLY[0].unemployment_rate/3;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_1 = HISTORY_QUARTERLY[0].unemployment_rate_skill_1/3;    
    HISTORY_QUARTERLY[0].unemployment_rate_skill_2 = HISTORY_QUARTERLY[0].unemployment_rate_skill_2/3;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_3 = HISTORY_QUARTERLY[0].unemployment_rate_skill_3/3;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_4 = HISTORY_QUARTERLY[0].unemployment_rate_skill_4/3;
    HISTORY_QUARTERLY[0].unemployment_rate_skill_5 = HISTORY_QUARTERLY[0].unemployment_rate_skill_5/3;
    HISTORY_QUARTERLY[0].average_wage           = HISTORY_QUARTERLY[0].average_wage/3;
    HISTORY_QUARTERLY[0].no_firms               = HISTORY_QUARTERLY[0].no_firms/3;
    HISTORY_QUARTERLY[0].no_active_firms        = HISTORY_QUARTERLY[0].no_active_firms/3;
    HISTORY_QUARTERLY[0].no_firm_births         = HISTORY_QUARTERLY[0].no_firm_births;
    HISTORY_QUARTERLY[0].no_firm_deaths         = HISTORY_QUARTERLY[0].no_firm_deaths;
    HISTORY_QUARTERLY[0].investment_value       = HISTORY_QUARTERLY[0].investment_value;
    
    //*********************************** Code to be tested: region data

    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        //Shift history backwards
        for (i=4; i>0; i--)
        {
            HISTORY_QUARTERLY[i].region_data.array[region].cpi = HISTORY_QUARTERLY[i-1].region_data.array[region].cpi;
            HISTORY_QUARTERLY[i].region_data.array[region].gdp = HISTORY_QUARTERLY[i-1].region_data.array[region].gdp;
            HISTORY_QUARTERLY[i].region_data.array[region].output = HISTORY_QUARTERLY[i-1].region_data.array[region].output;
            HISTORY_QUARTERLY[i].region_data.array[region].employment = HISTORY_QUARTERLY[i-1].region_data.array[region].employment;      
            HISTORY_QUARTERLY[i].region_data.array[region].unemployment_rate = HISTORY_QUARTERLY[i-1].region_data.array[region].unemployment_rate;
            HISTORY_QUARTERLY[i].region_data.array[region].unemployment_rate_skill_1 = HISTORY_QUARTERLY[i-1].region_data.array[region].unemployment_rate_skill_1;
            HISTORY_QUARTERLY[i].region_data.array[region].unemployment_rate_skill_2 = HISTORY_QUARTERLY[i-1].region_data.array[region].unemployment_rate_skill_2;
            HISTORY_QUARTERLY[i].region_data.array[region].unemployment_rate_skill_3 = HISTORY_QUARTERLY[i-1].region_data.array[region].unemployment_rate_skill_3;
            HISTORY_QUARTERLY[i].region_data.array[region].unemployment_rate_skill_4 = HISTORY_QUARTERLY[i-1].region_data.array[region].unemployment_rate_skill_4;
            HISTORY_QUARTERLY[i].region_data.array[region].unemployment_rate_skill_5 = HISTORY_QUARTERLY[i-1].region_data.array[region].unemployment_rate_skill_5;
            HISTORY_QUARTERLY[i].region_data.array[region].average_wage = HISTORY_QUARTERLY[i-1].region_data.array[region].average_wage;
            HISTORY_QUARTERLY[i].region_data.array[region].no_firms = HISTORY_QUARTERLY[i-1].region_data.array[region].no_firms;
	    HISTORY_QUARTERLY[i].region_data.array[region].no_active_firms = HISTORY_QUARTERLY[i-1].region_data.array[region].no_active_firms;
            HISTORY_QUARTERLY[i].region_data.array[region].no_firm_births = HISTORY_QUARTERLY[i-1].region_data.array[region].no_firm_births;
            HISTORY_QUARTERLY[i].region_data.array[region].no_firm_deaths = HISTORY_QUARTERLY[i-1].region_data.array[region].no_firm_deaths;
            HISTORY_QUARTERLY[i].region_data.array[region].investment_value = HISTORY_QUARTERLY[i-1].region_data.array[region].investment_value;
        }

        //Reset first elements for sum
        HISTORY_QUARTERLY[0].region_data.array[region].cpi=1.0;
        HISTORY_QUARTERLY[0].region_data.array[region].gdp=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].output=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].employment=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_1=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_2=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_3=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_4=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_5=0.0;    
        HISTORY_QUARTERLY[0].region_data.array[region].average_wage=0.0;
        HISTORY_QUARTERLY[0].region_data.array[region].no_firms=0;
	HISTORY_QUARTERLY[0].region_data.array[region].no_active_firms=0;
        HISTORY_QUARTERLY[0].region_data.array[region].no_firm_births=0;
        HISTORY_QUARTERLY[0].region_data.array[region].no_firm_deaths=0;
        HISTORY_QUARTERLY[0].region_data.array[region].investment_value=0.0;

        //Store first value: construct quarterly sums from monthly history
        for (i=0; i<3; i++)
        {
            HISTORY_QUARTERLY[0].region_data.array[region].cpi                *= HISTORY_MONTHLY[i].region_data.array[region].cpi;
            HISTORY_QUARTERLY[0].region_data.array[region].gdp                += HISTORY_MONTHLY[i].region_data.array[region].gdp;
            HISTORY_QUARTERLY[0].region_data.array[region].output             += HISTORY_MONTHLY[i].region_data.array[region].output;
            HISTORY_QUARTERLY[0].region_data.array[region].employment         += HISTORY_MONTHLY[i].region_data.array[region].employment;        
            HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate  += HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate;
            HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_1  += HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_1;
            HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_2  += HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_2;
            HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_3  += HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_3;
            HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_4  += HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_4;
            HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_5  += HISTORY_MONTHLY[i].region_data.array[region].unemployment_rate_skill_5;
            HISTORY_QUARTERLY[0].region_data.array[region].average_wage       += HISTORY_MONTHLY[i].region_data.array[region].average_wage;
            HISTORY_QUARTERLY[0].region_data.array[region].no_firms           += HISTORY_MONTHLY[i].region_data.array[region].no_firms;
	    HISTORY_QUARTERLY[0].region_data.array[region].no_active_firms    += HISTORY_MONTHLY[i].region_data.array[region].no_active_firms;
            HISTORY_QUARTERLY[0].region_data.array[region].no_firm_births     += HISTORY_MONTHLY[i].region_data.array[region].no_firm_births;
            HISTORY_QUARTERLY[0].region_data.array[region].no_firm_deaths     += HISTORY_MONTHLY[i].region_data.array[region].no_firm_deaths;           
            HISTORY_QUARTERLY[0].region_data.array[region].investment_value   += HISTORY_MONTHLY[i].region_data.array[region].investment_value;           
        }
        
        //The following quarterly statistics are averages of monthly statistics
        //HISTORY_QUARTERLY[0].region_data.array[region].cpi                    = HISTORY_QUARTERLY[0].region_data.array[region].cpi/3;
        HISTORY_QUARTERLY[0].region_data.array[region].gdp                    = HISTORY_QUARTERLY[0].region_data.array[region].gdp;
        HISTORY_QUARTERLY[0].region_data.array[region].output                 = HISTORY_QUARTERLY[0].region_data.array[region].output;        
        HISTORY_QUARTERLY[0].region_data.array[region].employment             = HISTORY_QUARTERLY[0].region_data.array[region].employment/3;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate      = HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate/3;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_1 = HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_1/3;    
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_2 = HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_2/3;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_3 = HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_3/3;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_4 = HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_4/3;
        HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_5 = HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_5/3;
        HISTORY_QUARTERLY[0].region_data.array[region].average_wage           = HISTORY_QUARTERLY[0].region_data.array[region].average_wage/3;
        HISTORY_QUARTERLY[0].region_data.array[region].no_firms               = HISTORY_QUARTERLY[0].region_data.array[region].no_firms/3;
	HISTORY_QUARTERLY[0].region_data.array[region].no_active_firms        = HISTORY_QUARTERLY[0].region_data.array[region].no_active_firms/3;
        HISTORY_QUARTERLY[0].region_data.array[region].no_firm_births         = HISTORY_QUARTERLY[0].region_data.array[region].no_firm_births;
        HISTORY_QUARTERLY[0].region_data.array[region].no_firm_deaths         = HISTORY_QUARTERLY[0].region_data.array[region].no_firm_deaths;    
        HISTORY_QUARTERLY[0].region_data.array[region].investment_value       = HISTORY_QUARTERLY[0].region_data.array[region].investment_value;    
    }

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_EUROSTAT)
    {
        printf("Quarterly data recorded by Eurostat:\n");
        printf(" - quarterly CPI: %f\n", HISTORY_QUARTERLY[0].cpi);
        printf(" - quarterly GDP: %f\n", HISTORY_QUARTERLY[0].gdp);
        printf(" - quarterly output: %f\n", HISTORY_QUARTERLY[0].output);
        printf(" - quarterly average employment: %d\n", HISTORY_QUARTERLY[0].employment);
        printf(" - quarterly average unemployment rate: %f\n", HISTORY_QUARTERLY[0].unemployment_rate);
        printf(" - quarterly average wage: %f\n", HISTORY_QUARTERLY[0].average_wage);
        printf(" - quarterly average number of firms: %d\n", HISTORY_QUARTERLY[0].no_firms);
	printf(" - quarterly average number of active firms: %d\n", HISTORY_QUARTERLY[0].no_active_firms);
        printf(" - quarterly total number of firm births: %d\n", HISTORY_QUARTERLY[0].no_firm_births);
        printf(" - quarterly total number of firm deaths: %d\n", HISTORY_QUARTERLY[0].no_firm_deaths);
        printf(" - quarterly total investment value: %f\n", HISTORY_QUARTERLY[0].investment_value);
    }
    #endif
        
    return 0;
}


/************ Computation ********************************/
/* \fn: int Eurostat_compute_growth_rates_monthly()
 * \brief: Computes rates of change from the current history at the end of every month.
 */
int Eurostat_compute_growth_rates_monthly()
{
    int i,region;
    region=0;

    //*********************************** Economy-wide data
    MONTHLY_GROWTH_RATES.cpi                       = 1.0;
    MONTHLY_GROWTH_RATES.gdp                       = 0.0; 
    MONTHLY_GROWTH_RATES.output                    = 0.0;
    MONTHLY_GROWTH_RATES.employment                = 0.0;
    MONTHLY_GROWTH_RATES.unemployment_rate         = 0.0;
    MONTHLY_GROWTH_RATES.unemployment_rate_skill_1         = 0.0;
    MONTHLY_GROWTH_RATES.unemployment_rate_skill_2         = 0.0;
    MONTHLY_GROWTH_RATES.unemployment_rate_skill_3         = 0.0;
    MONTHLY_GROWTH_RATES.unemployment_rate_skill_4         = 0.0;
    MONTHLY_GROWTH_RATES.unemployment_rate_skill_5         = 0.0;
    MONTHLY_GROWTH_RATES.average_wage                      = 0.0;
    MONTHLY_GROWTH_RATES.no_firms                  = 0.0;
    MONTHLY_GROWTH_RATES.no_firm_births            = 0.0;
    MONTHLY_GROWTH_RATES.no_firm_deaths            = 0.0;
    MONTHLY_GROWTH_RATES.investment_value          = 0.0;
    
    ANNUAL_GROWTH_RATES_MONTHLY.cpi                = 1.0;           //CPI: compounded inflation rate in pct over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.gdp                = 0.0;           //GDP: percentage change in GDP over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.output             = 0.0;           //percentage change in output over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.employment         = 0.0;           //percentage change in total employment over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate  = 0.0;           //percentage change in unemployment_rate over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_1  = 0.0;
    ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_2  = 0.0;
    ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_3  = 0.0;
    ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_4  = 0.0;
    ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_5  = 0.0;
    ANNUAL_GROWTH_RATES_MONTHLY.average_wage               = 0.0;   //percentage change in average_wage over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.no_firms           = 0.0;           //percentage change in no_firms over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.no_firm_births     = 0.0;           //percentage change in no_firm_births over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.no_firm_deaths     = 0.0;           //percentage change in no_firm_deaths over last 12 months
    ANNUAL_GROWTH_RATES_MONTHLY.investment_value   = 0.0;
    
    //compute monthly rates of change: change over the previous month
    if(HISTORY_MONTHLY[1].cpi>0.0)              {MONTHLY_GROWTH_RATES.cpi                       = (HISTORY_MONTHLY[0].cpi-1)*100;}
    if(HISTORY_MONTHLY[1].gdp>0.0)              {MONTHLY_GROWTH_RATES.gdp                       = (HISTORY_MONTHLY[0].gdp / HISTORY_MONTHLY[1].gdp -1)*100;}
    if(HISTORY_MONTHLY[1].output>0.0)           {MONTHLY_GROWTH_RATES.output                    = (HISTORY_MONTHLY[0].output / HISTORY_MONTHLY[1].output  -1)*100;}
    if(HISTORY_MONTHLY[1].employment>0)         {MONTHLY_GROWTH_RATES.employment                = (HISTORY_MONTHLY[0].employment / HISTORY_MONTHLY[1].employment  -1)*100;}
    if(HISTORY_MONTHLY[1].unemployment_rate>0.0){MONTHLY_GROWTH_RATES.unemployment_rate         = (HISTORY_MONTHLY[0].unemployment_rate / HISTORY_MONTHLY[1].unemployment_rate  -1)*100;}
    if(HISTORY_MONTHLY[1].unemployment_rate_skill_1>0.0){MONTHLY_GROWTH_RATES.unemployment_rate_skill_1         = (HISTORY_MONTHLY[0].unemployment_rate_skill_1 / HISTORY_MONTHLY[1].unemployment_rate_skill_1  -1)*100;}
    if(HISTORY_MONTHLY[1].unemployment_rate_skill_2>0.0){MONTHLY_GROWTH_RATES.unemployment_rate_skill_2         = (HISTORY_MONTHLY[0].unemployment_rate_skill_2 / HISTORY_MONTHLY[1].unemployment_rate_skill_2  -1)*100;}
    if(HISTORY_MONTHLY[1].unemployment_rate_skill_3>0.0){MONTHLY_GROWTH_RATES.unemployment_rate_skill_3         = (HISTORY_MONTHLY[0].unemployment_rate_skill_3 / HISTORY_MONTHLY[1].unemployment_rate_skill_3  -1)*100;}
    if(HISTORY_MONTHLY[1].unemployment_rate_skill_4>0.0){MONTHLY_GROWTH_RATES.unemployment_rate_skill_4         = (HISTORY_MONTHLY[0].unemployment_rate_skill_4 / HISTORY_MONTHLY[1].unemployment_rate_skill_4  -1)*100;}
    if(HISTORY_MONTHLY[1].unemployment_rate_skill_5>0.0){MONTHLY_GROWTH_RATES.unemployment_rate_skill_5         = (HISTORY_MONTHLY[0].unemployment_rate_skill_5 / HISTORY_MONTHLY[1].unemployment_rate_skill_5  -1)*100;}
    if(HISTORY_MONTHLY[1].average_wage>0.0)     {MONTHLY_GROWTH_RATES.average_wage              = (HISTORY_MONTHLY[0].average_wage / HISTORY_MONTHLY[1].average_wage  -1)*100;}
    if(HISTORY_MONTHLY[1].no_firms>0)           {MONTHLY_GROWTH_RATES.no_firms                  = (HISTORY_MONTHLY[0].no_firms / HISTORY_MONTHLY[1].no_firms  -1)*100;}
    if(HISTORY_MONTHLY[1].no_firm_births>0)     {MONTHLY_GROWTH_RATES.no_firm_births            = (HISTORY_MONTHLY[0].no_firm_births / HISTORY_MONTHLY[1].no_firm_births  -1)*100;}
    if(HISTORY_MONTHLY[1].no_firm_deaths>0)     {MONTHLY_GROWTH_RATES.no_firm_deaths            = (HISTORY_MONTHLY[0].no_firm_deaths / HISTORY_MONTHLY[1].no_firm_deaths  -1)*100;}   
    if(HISTORY_MONTHLY[1].investment_value>0)     {MONTHLY_GROWTH_RATES.investment_value        = (HISTORY_MONTHLY[0].investment_value / HISTORY_MONTHLY[1].investment_value  -1)*100;}   

    //compute annual rate of change of CPI: compounded inflation rate over the previous 12 months
    for (i=0; i<12; i++)
    {
        ANNUAL_GROWTH_RATES_MONTHLY.cpi *= HISTORY_MONTHLY[i].cpi;
    }
    ANNUAL_GROWTH_RATES_MONTHLY.cpi = (ANNUAL_GROWTH_RATES_MONTHLY.cpi-1)*100;
    
    //compute annual rates of change over the previous 12 months: respective to same month in previous year
    if(HISTORY_MONTHLY[12].gdp>0.0)             {ANNUAL_GROWTH_RATES_MONTHLY.gdp                = (HISTORY_MONTHLY[0].gdp / HISTORY_MONTHLY[12].gdp  -1)*100;}
    if(HISTORY_MONTHLY[12].output>0.0)          {ANNUAL_GROWTH_RATES_MONTHLY.output             = (HISTORY_MONTHLY[0].output / HISTORY_MONTHLY[12].output  -1)*100;}
    if(HISTORY_MONTHLY[12].employment>0)        {ANNUAL_GROWTH_RATES_MONTHLY.employment         = (HISTORY_MONTHLY[0].employment / HISTORY_MONTHLY[12].employment  -1)*100;}
    if(HISTORY_MONTHLY[12].unemployment_rate>0) {ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate  = (HISTORY_MONTHLY[0].unemployment_rate / HISTORY_MONTHLY[12].unemployment_rate  -1)*100;}
    if(HISTORY_MONTHLY[12].unemployment_rate_skill_1>0) {ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_1  = (HISTORY_MONTHLY[0].unemployment_rate_skill_1 / HISTORY_MONTHLY[12].unemployment_rate_skill_1  -1)*100;}
    if(HISTORY_MONTHLY[12].unemployment_rate_skill_2>0) {ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_2  = (HISTORY_MONTHLY[0].unemployment_rate_skill_2 / HISTORY_MONTHLY[12].unemployment_rate_skill_2  -1)*100;}
    if(HISTORY_MONTHLY[12].unemployment_rate_skill_3>0) {ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_3  = (HISTORY_MONTHLY[0].unemployment_rate_skill_3 / HISTORY_MONTHLY[12].unemployment_rate_skill_3  -1)*100;}
    if(HISTORY_MONTHLY[12].unemployment_rate_skill_4>0) {ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_4  = (HISTORY_MONTHLY[0].unemployment_rate_skill_4 / HISTORY_MONTHLY[12].unemployment_rate_skill_4  -1)*100;}
    if(HISTORY_MONTHLY[12].unemployment_rate_skill_5>0) {ANNUAL_GROWTH_RATES_MONTHLY.unemployment_rate_skill_5  = (HISTORY_MONTHLY[0].unemployment_rate_skill_5 / HISTORY_MONTHLY[12].unemployment_rate_skill_5  -1)*100;}
    if(HISTORY_MONTHLY[12].average_wage>0)      {ANNUAL_GROWTH_RATES_MONTHLY.average_wage       = (HISTORY_MONTHLY[0].average_wage / HISTORY_MONTHLY[12].average_wage  -1)*100;}
    if(HISTORY_MONTHLY[12].no_firms>0)          {ANNUAL_GROWTH_RATES_MONTHLY.no_firms           = (HISTORY_MONTHLY[0].no_firms / HISTORY_MONTHLY[12].no_firms  -1)*100;}
    if(HISTORY_MONTHLY[12].no_firm_births>0)    {ANNUAL_GROWTH_RATES_MONTHLY.no_firm_births     = (HISTORY_MONTHLY[0].no_firm_births / HISTORY_MONTHLY[12].no_firm_births  -1)*100;}
    if(HISTORY_MONTHLY[12].no_firm_deaths>0)    {ANNUAL_GROWTH_RATES_MONTHLY.no_firm_deaths     = (HISTORY_MONTHLY[0].no_firm_deaths / HISTORY_MONTHLY[12].no_firm_deaths  -1)*100;}
    if(HISTORY_MONTHLY[12].investment_value>0)    {ANNUAL_GROWTH_RATES_MONTHLY.investment_value     = (HISTORY_MONTHLY[0].investment_value / HISTORY_MONTHLY[12].investment_value  -1)*100;}

    
    //*********************************** Code to be tested: region data
    
    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        MONTHLY_GROWTH_RATES.region_data.array[region].cpi                       = 1.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].gdp                       = 0.0; 
        MONTHLY_GROWTH_RATES.region_data.array[region].output                    = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].employment                = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate         = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_1 = 0.0;        
        MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_2 = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_3 = 0.0;        
        MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_4 = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_5 = 0.0;        
        MONTHLY_GROWTH_RATES.region_data.array[region].average_wage              = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].no_firms                  = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].no_firm_births            = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].no_firm_deaths            = 0.0;
        MONTHLY_GROWTH_RATES.region_data.array[region].investment_value          = 0.0;
        
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].cpi                = 1.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].gdp                = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].output             = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].employment         = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate  = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_1  = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_2  = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_3  = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_4  = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_5  = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].average_wage       = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].no_firms           = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].no_firm_births     = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].no_firm_deaths     = 0.0;
        ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].investment_value   = 0.0;
        
        //compute monthly rates of change: change over the previous month
        if(HISTORY_MONTHLY[1].region_data.array[region].cpi>0.0)              {MONTHLY_GROWTH_RATES.region_data.array[region].cpi                       = (HISTORY_MONTHLY[0].region_data.array[region].cpi-1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].gdp>0.0)              {MONTHLY_GROWTH_RATES.region_data.array[region].gdp                       = (HISTORY_MONTHLY[0].region_data.array[region].gdp / HISTORY_MONTHLY[1].region_data.array[region].gdp -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].output>0.0)           {MONTHLY_GROWTH_RATES.region_data.array[region].output                    = (HISTORY_MONTHLY[0].region_data.array[region].output / HISTORY_MONTHLY[1].region_data.array[region].output  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].employment>0)         {MONTHLY_GROWTH_RATES.region_data.array[region].employment                = (HISTORY_MONTHLY[0].region_data.array[region].employment / HISTORY_MONTHLY[1].region_data.array[region].employment  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate>0.0){MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate         = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate / HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_1>0.0){MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_1 = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_1 / HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_1  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_2>0.0){MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_2 = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_2 / HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_2  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_3>0.0){MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_3 = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_3 / HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_3  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_4>0.0){MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_4 = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_4 / HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_4  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_5>0.0){MONTHLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_5 = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_5 / HISTORY_MONTHLY[1].region_data.array[region].unemployment_rate_skill_5  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].average_wage>0.0)     {MONTHLY_GROWTH_RATES.region_data.array[region].average_wage              = (HISTORY_MONTHLY[0].region_data.array[region].average_wage / HISTORY_MONTHLY[1].region_data.array[region].average_wage  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].no_firms>0)           {MONTHLY_GROWTH_RATES.region_data.array[region].no_firms                  = (HISTORY_MONTHLY[0].region_data.array[region].no_firms / HISTORY_MONTHLY[1].region_data.array[region].no_firms  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].no_firm_births>0)     {MONTHLY_GROWTH_RATES.region_data.array[region].no_firm_births            = (HISTORY_MONTHLY[0].region_data.array[region].no_firm_births / HISTORY_MONTHLY[1].region_data.array[region].no_firm_births  -1)*100;}
        if(HISTORY_MONTHLY[1].region_data.array[region].no_firm_deaths>0)     {MONTHLY_GROWTH_RATES.region_data.array[region].no_firm_deaths            = (HISTORY_MONTHLY[0].region_data.array[region].no_firm_deaths / HISTORY_MONTHLY[1].region_data.array[region].no_firm_deaths  -1)*100;}   
        if(HISTORY_MONTHLY[1].region_data.array[region].investment_value>0)     {MONTHLY_GROWTH_RATES.region_data.array[region].investment_value        = (HISTORY_MONTHLY[0].region_data.array[region].investment_value / HISTORY_MONTHLY[1].region_data.array[region].investment_value  -1)*100;}   
        
        //compute annual rate of change of CPI: compounded inflation rate over the previous 12 months
         for (i=0; i<12; i++)
         {
            ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].cpi *= HISTORY_MONTHLY[i].region_data.array[region].cpi;
         }
         ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].cpi = (ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].cpi-1)*100;

        //compute annual rates of change over the previous 12 months: respective to same month in previous year
        if(HISTORY_MONTHLY[12].region_data.array[region].gdp>0.0)             {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].gdp                = (HISTORY_MONTHLY[0].region_data.array[region].gdp / HISTORY_MONTHLY[12].region_data.array[region].gdp  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].output>0.0)          {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].output             = (HISTORY_MONTHLY[0].region_data.array[region].output / HISTORY_MONTHLY[12].region_data.array[region].output  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].employment>0)        {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].employment         = (HISTORY_MONTHLY[0].region_data.array[region].employment / HISTORY_MONTHLY[12].region_data.array[region].employment  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate>0) {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate  = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate / HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_1>0) {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_1  = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_1 / HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_1  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_2>0) {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_2  = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_2 / HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_2  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_3>0) {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_3  = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_3 / HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_3  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_4>0) {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_4  = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_4 / HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_4  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_5>0) {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].unemployment_rate_skill_5  = (HISTORY_MONTHLY[0].region_data.array[region].unemployment_rate_skill_5 / HISTORY_MONTHLY[12].region_data.array[region].unemployment_rate_skill_5  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].average_wage>0)      {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].average_wage       = (HISTORY_MONTHLY[0].region_data.array[region].average_wage / HISTORY_MONTHLY[12].region_data.array[region].average_wage  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].no_firms>0)          {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].no_firms           = (HISTORY_MONTHLY[0].region_data.array[region].no_firms / HISTORY_MONTHLY[12].region_data.array[region].no_firms  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].no_firm_births>0)    {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].no_firm_births     = (HISTORY_MONTHLY[0].region_data.array[region].no_firm_births / HISTORY_MONTHLY[12].region_data.array[region].no_firm_births  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].no_firm_deaths>0)    {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].no_firm_deaths     = (HISTORY_MONTHLY[0].region_data.array[region].no_firm_deaths / HISTORY_MONTHLY[12].region_data.array[region].no_firm_deaths  -1)*100;}
        if(HISTORY_MONTHLY[12].region_data.array[region].investment_value>0)    {ANNUAL_GROWTH_RATES_MONTHLY.region_data.array[region].investment_value = (HISTORY_MONTHLY[0].region_data.array[region].investment_value / HISTORY_MONTHLY[12].region_data.array[region].investment_value  -1)*100;}
    }

    
    return 0;
}

/* \fn: int Eurostat_compute_growth_rates_quarterly()
 * \brief: Computes rates of change from the current history at the end of every quarterly.
 */
int Eurostat_compute_growth_rates_quarterly()
{
    int i,region;
    region=0;
    
    //*********************************** Economy-wide data
    QUARTERLY_GROWTH_RATES.cpi                         = 1.0;
    QUARTERLY_GROWTH_RATES.gdp                         = 0.0;
    QUARTERLY_GROWTH_RATES.output                      = 0.0;
    QUARTERLY_GROWTH_RATES.employment                  = 0.0;
    QUARTERLY_GROWTH_RATES.unemployment_rate           = 0.0;
    QUARTERLY_GROWTH_RATES.unemployment_rate_skill_1   = 0.0;    
    QUARTERLY_GROWTH_RATES.unemployment_rate_skill_2   = 0.0;
    QUARTERLY_GROWTH_RATES.unemployment_rate_skill_3   = 0.0;    
    QUARTERLY_GROWTH_RATES.unemployment_rate_skill_4   = 0.0;
    QUARTERLY_GROWTH_RATES.unemployment_rate_skill_5   = 0.0;    
    QUARTERLY_GROWTH_RATES.average_wage                = 0.0;
    QUARTERLY_GROWTH_RATES.no_firms                    = 0.0;
    QUARTERLY_GROWTH_RATES.no_firm_births              = 0.0;
    QUARTERLY_GROWTH_RATES.no_firm_deaths              = 0.0;
    QUARTERLY_GROWTH_RATES.investment_value            = 0.0;
    
    ANNUAL_GROWTH_RATES_QUARTERLY.cpi                  = 1.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.gdp                  = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.output               = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.employment           = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate    = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_1    = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_2    = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_3    = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_4    = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_5    = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.average_wage         = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.no_firms             = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.no_firm_births       = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.no_firm_deaths       = 0.0;
    ANNUAL_GROWTH_RATES_QUARTERLY.investment_value     = 0.0;

    //compute quarterly rate of change of CPI: compounded inflation rate over the previous 3 months
    for (i=0; i<3; i++)
    {
        QUARTERLY_GROWTH_RATES.cpi *= HISTORY_MONTHLY[0].cpi;           
    }
    QUARTERLY_GROWTH_RATES.cpi = (QUARTERLY_GROWTH_RATES.cpi-1)*100;
    
    //compute quarterly rates of change: change over the previous 3 months
    if(HISTORY_QUARTERLY[1].gdp>0.0)                {QUARTERLY_GROWTH_RATES.gdp                         = (HISTORY_QUARTERLY[0].gdp / HISTORY_QUARTERLY[1].gdp  -1)*100;}
    if(HISTORY_QUARTERLY[1].output>0.0)             {QUARTERLY_GROWTH_RATES.output                      = (HISTORY_QUARTERLY[0].output / HISTORY_QUARTERLY[1].output  -1)*100;}
    if(HISTORY_QUARTERLY[1].employment>0)           {QUARTERLY_GROWTH_RATES.employment                  = (HISTORY_QUARTERLY[0].employment / HISTORY_QUARTERLY[1].employment  -1)*100;}
    if(HISTORY_QUARTERLY[1].unemployment_rate>0.0)  {QUARTERLY_GROWTH_RATES.unemployment_rate           = (HISTORY_QUARTERLY[0].unemployment_rate / HISTORY_QUARTERLY[1].unemployment_rate  -1)*100;}
    if(HISTORY_QUARTERLY[1].unemployment_rate_skill_1>0.0)  {QUARTERLY_GROWTH_RATES.unemployment_rate_skill_1   = (HISTORY_QUARTERLY[0].unemployment_rate_skill_1 / HISTORY_QUARTERLY[1].unemployment_rate_skill_1  -1)*100;}
    if(HISTORY_QUARTERLY[1].unemployment_rate_skill_2>0.0)  {QUARTERLY_GROWTH_RATES.unemployment_rate_skill_2   = (HISTORY_QUARTERLY[0].unemployment_rate_skill_2 / HISTORY_QUARTERLY[1].unemployment_rate_skill_2  -1)*100;}
    if(HISTORY_QUARTERLY[1].unemployment_rate_skill_3>0.0)  {QUARTERLY_GROWTH_RATES.unemployment_rate_skill_3   = (HISTORY_QUARTERLY[0].unemployment_rate_skill_3 / HISTORY_QUARTERLY[1].unemployment_rate_skill_3  -1)*100;}
    if(HISTORY_QUARTERLY[1].unemployment_rate_skill_4>0.0)  {QUARTERLY_GROWTH_RATES.unemployment_rate_skill_4   = (HISTORY_QUARTERLY[0].unemployment_rate_skill_4 / HISTORY_QUARTERLY[1].unemployment_rate_skill_4  -1)*100;}
    if(HISTORY_QUARTERLY[1].unemployment_rate_skill_5>0.0)  {QUARTERLY_GROWTH_RATES.unemployment_rate_skill_5   = (HISTORY_QUARTERLY[0].unemployment_rate_skill_5 / HISTORY_QUARTERLY[1].unemployment_rate_skill_5  -1)*100;}
    if(HISTORY_QUARTERLY[1].average_wage>0.0)       {QUARTERLY_GROWTH_RATES.average_wage                = (HISTORY_QUARTERLY[0].average_wage / HISTORY_QUARTERLY[1].average_wage  -1)*100;}
    if(HISTORY_QUARTERLY[1].no_firms>0)             {QUARTERLY_GROWTH_RATES.no_firms                    = (HISTORY_QUARTERLY[0].no_firms / HISTORY_QUARTERLY[1].no_firms  -1)*100;}
    if(HISTORY_QUARTERLY[1].no_firm_births>0)       {QUARTERLY_GROWTH_RATES.no_firm_births              = (HISTORY_QUARTERLY[0].no_firm_births / HISTORY_QUARTERLY[1].no_firm_births  -1)*100;}
    if(HISTORY_QUARTERLY[1].no_firm_deaths>0)       {QUARTERLY_GROWTH_RATES.no_firm_deaths              = (HISTORY_QUARTERLY[0].no_firm_deaths / HISTORY_QUARTERLY[1].no_firm_deaths  -1)*100;}
    if(HISTORY_QUARTERLY[1].investment_value>0)       {QUARTERLY_GROWTH_RATES.investment_value          = (HISTORY_QUARTERLY[0].investment_value / HISTORY_QUARTERLY[1].investment_value  -1)*100;}
    
    //compute annual rate of change of CPI: compounded inflation rate over the last 4 quarters (should equal the inflation rate measured over last 12 months)
     for (i=0; i<4; i++)
     {
        ANNUAL_GROWTH_RATES_QUARTERLY.cpi *= HISTORY_QUARTERLY[i].cpi;
     }
     ANNUAL_GROWTH_RATES_QUARTERLY.cpi = (ANNUAL_GROWTH_RATES_QUARTERLY.cpi-1)*100;

    //compute annual rates of change over the previous 4 quarters: respective to same quarter in previous year    
    if(HISTORY_QUARTERLY[4].gdp>0.0)                {ANNUAL_GROWTH_RATES_QUARTERLY.gdp                  = (HISTORY_QUARTERLY[0].gdp / HISTORY_QUARTERLY[4].gdp  -1)*100;}
    if(HISTORY_QUARTERLY[4].output>0.0)             {ANNUAL_GROWTH_RATES_QUARTERLY.output               = (HISTORY_QUARTERLY[0].output / HISTORY_QUARTERLY[4].output  -1)*100;}
    if(HISTORY_QUARTERLY[4].employment>0)           {ANNUAL_GROWTH_RATES_QUARTERLY.employment           = (HISTORY_QUARTERLY[0].employment / HISTORY_QUARTERLY[4].employment  -1)*100;}
    if(HISTORY_QUARTERLY[4].unemployment_rate>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate    = (HISTORY_QUARTERLY[0].unemployment_rate / HISTORY_QUARTERLY[4].unemployment_rate  -1)*100;}
    if(HISTORY_QUARTERLY[4].unemployment_rate_skill_1>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_1    = (HISTORY_QUARTERLY[0].unemployment_rate_skill_1 / HISTORY_QUARTERLY[4].unemployment_rate_skill_1  -1)*100;}
    if(HISTORY_QUARTERLY[4].unemployment_rate_skill_2>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_2    = (HISTORY_QUARTERLY[0].unemployment_rate_skill_2 / HISTORY_QUARTERLY[4].unemployment_rate_skill_2  -1)*100;}
    if(HISTORY_QUARTERLY[4].unemployment_rate_skill_3>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_3    = (HISTORY_QUARTERLY[0].unemployment_rate_skill_3 / HISTORY_QUARTERLY[4].unemployment_rate_skill_3  -1)*100;}
    if(HISTORY_QUARTERLY[4].unemployment_rate_skill_4>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_4    = (HISTORY_QUARTERLY[0].unemployment_rate_skill_4 / HISTORY_QUARTERLY[4].unemployment_rate_skill_4  -1)*100;}
    if(HISTORY_QUARTERLY[4].unemployment_rate_skill_5>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.unemployment_rate_skill_5    = (HISTORY_QUARTERLY[0].unemployment_rate_skill_5 / HISTORY_QUARTERLY[4].unemployment_rate_skill_5  -1)*100;}
    if(HISTORY_QUARTERLY[4].average_wage>0.0)       {ANNUAL_GROWTH_RATES_QUARTERLY.average_wage         = (HISTORY_QUARTERLY[0].average_wage / HISTORY_QUARTERLY[4].average_wage  -1)*100;}
    if(HISTORY_QUARTERLY[4].no_firms>0)             {ANNUAL_GROWTH_RATES_QUARTERLY.no_firms             = (HISTORY_QUARTERLY[0].no_firms / HISTORY_QUARTERLY[4].no_firms  -1)*100;}
    if(HISTORY_QUARTERLY[4].no_firm_births>0)       {ANNUAL_GROWTH_RATES_QUARTERLY.no_firm_births       = (HISTORY_QUARTERLY[0].no_firm_births / HISTORY_QUARTERLY[4].no_firm_births  -1)*100;}
    if(HISTORY_QUARTERLY[4].no_firm_deaths>0)       {ANNUAL_GROWTH_RATES_QUARTERLY.no_firm_deaths       = (HISTORY_QUARTERLY[0].no_firm_deaths / HISTORY_QUARTERLY[4].no_firm_deaths  -1)*100;}
    if(HISTORY_QUARTERLY[4].investment_value>0)     {ANNUAL_GROWTH_RATES_QUARTERLY.investment_value     = (HISTORY_QUARTERLY[0].investment_value / HISTORY_QUARTERLY[4].investment_value  -1)*100;}
    
    //*********************************** Code to be tested: region data
    
    for ( region=0; region<REGION_FIRM_DATA.size; region++)
    {
        QUARTERLY_GROWTH_RATES.region_data.array[region].cpi                         = 1.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].gdp                         = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].output                      = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].employment                  = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate           = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_1   = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_2   = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_3   = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_4   = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_5   = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].average_wage                = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].no_firms                    = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].no_firm_births              = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].no_firm_deaths              = 0.0;
        QUARTERLY_GROWTH_RATES.region_data.array[region].investment_value            = 0.0;

        
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].cpi                  = 1.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].gdp                  = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].output               = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].employment           = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate    = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_1    = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_2    = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_3    = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_4    = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_5    = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].average_wage         = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].no_firms             = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].no_firm_births       = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].no_firm_deaths       = 0.0;
        ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].investment_value     = 0.0;
    
        //compute quarterly rates of change of CPI: compounded inflation rate over the previous 3 months
        for (i=0; i<3; i++)
        {
            QUARTERLY_GROWTH_RATES.region_data.array[region].cpi *= HISTORY_MONTHLY[0].region_data.array[region].cpi;           
        }
        QUARTERLY_GROWTH_RATES.region_data.array[region].cpi = (QUARTERLY_GROWTH_RATES.region_data.array[region].cpi-1)*100;
        
        //compute quarterly rates of change:
        if(HISTORY_QUARTERLY[1].region_data.array[region].gdp>0.0)                {QUARTERLY_GROWTH_RATES.region_data.array[region].gdp                         = (HISTORY_QUARTERLY[0].region_data.array[region].gdp / HISTORY_QUARTERLY[1].region_data.array[region].gdp  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].output>0.0)             {QUARTERLY_GROWTH_RATES.region_data.array[region].output                      = (HISTORY_QUARTERLY[0].region_data.array[region].output / HISTORY_QUARTERLY[1].region_data.array[region].output  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].employment>0)           {QUARTERLY_GROWTH_RATES.region_data.array[region].employment                  = (HISTORY_QUARTERLY[0].region_data.array[region].employment / HISTORY_QUARTERLY[1].region_data.array[region].employment  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate>0.0)  {QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate           = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate / HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_1>0.0)  {QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_1   = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_1 / HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_1  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_2>0.0)  {QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_2   = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_2 / HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_2  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_3>0.0)  {QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_3   = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_3 / HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_3  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_4>0.0)  {QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_4   = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_4 / HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_4  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_5>0.0)  {QUARTERLY_GROWTH_RATES.region_data.array[region].unemployment_rate_skill_5   = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_5 / HISTORY_QUARTERLY[1].region_data.array[region].unemployment_rate_skill_5  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].average_wage>0.0)       {QUARTERLY_GROWTH_RATES.region_data.array[region].average_wage                = (HISTORY_QUARTERLY[0].region_data.array[region].average_wage / HISTORY_QUARTERLY[1].region_data.array[region].average_wage  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].no_firms>0)             {QUARTERLY_GROWTH_RATES.region_data.array[region].no_firms                    = (HISTORY_QUARTERLY[0].region_data.array[region].no_firms / HISTORY_QUARTERLY[1].region_data.array[region].no_firms  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].no_firm_births>0)       {QUARTERLY_GROWTH_RATES.region_data.array[region].no_firm_births              = (HISTORY_QUARTERLY[0].region_data.array[region].no_firm_births / HISTORY_QUARTERLY[1].region_data.array[region].no_firm_births  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].no_firm_deaths>0)       {QUARTERLY_GROWTH_RATES.region_data.array[region].no_firm_deaths              = (HISTORY_QUARTERLY[0].region_data.array[region].no_firm_deaths / HISTORY_QUARTERLY[1].region_data.array[region].no_firm_deaths  -1)*100;}
        if(HISTORY_QUARTERLY[1].region_data.array[region].investment_value>0)       {QUARTERLY_GROWTH_RATES.region_data.array[region].investment_value              = (HISTORY_QUARTERLY[0].region_data.array[region].investment_value / HISTORY_QUARTERLY[1].region_data.array[region].investment_value  -1)*100;}
        
        //compute annual rate of change of CPI: compounded inflation rate over the last 4 quarters (should equal the inflation rate measured over last 12 months)
         for (i=0; i<4; i++)
         {
            ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].cpi *= HISTORY_QUARTERLY[i].region_data.array[region].cpi;
         }
         ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].cpi = (ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].cpi-1)*100;

        //compute annual rates of change over the previous 4 quarters: respective to same quarter in previous year
        if(HISTORY_QUARTERLY[4].region_data.array[region].gdp>0.0)                {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].gdp                  = (HISTORY_QUARTERLY[0].region_data.array[region].gdp / HISTORY_QUARTERLY[4].region_data.array[region].gdp  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].output>0.0)             {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].output               = (HISTORY_QUARTERLY[0].region_data.array[region].output / HISTORY_QUARTERLY[4].region_data.array[region].output  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].employment>0)           {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].employment           = (HISTORY_QUARTERLY[0].region_data.array[region].employment / HISTORY_QUARTERLY[4].region_data.array[region].employment  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate    = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate / HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_1>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_1    = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_1 / HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_1  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_2>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_2    = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_2 / HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_2  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_3>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_3    = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_3 / HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_3  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_4>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_4    = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_4 / HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_4  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_5>0.0)  {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].unemployment_rate_skill_5    = (HISTORY_QUARTERLY[0].region_data.array[region].unemployment_rate_skill_5 / HISTORY_QUARTERLY[4].region_data.array[region].unemployment_rate_skill_5  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].average_wage>0.0)       {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].average_wage  = (HISTORY_QUARTERLY[0].region_data.array[region].average_wage / HISTORY_QUARTERLY[4].region_data.array[region].average_wage  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].no_firms>0)             {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].no_firms             = (HISTORY_QUARTERLY[0].region_data.array[region].no_firms / HISTORY_QUARTERLY[4].region_data.array[region].no_firms  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].no_firm_births>0)       {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].no_firm_births       = (HISTORY_QUARTERLY[0].region_data.array[region].no_firm_births / HISTORY_QUARTERLY[4].region_data.array[region].no_firm_births  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].no_firm_deaths>0)       {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].no_firm_deaths       = (HISTORY_QUARTERLY[0].region_data.array[region].no_firm_deaths / HISTORY_QUARTERLY[4].region_data.array[region].no_firm_deaths  -1)*100;}
        if(HISTORY_QUARTERLY[4].region_data.array[region].investment_value>0)       {ANNUAL_GROWTH_RATES_QUARTERLY.region_data.array[region].investment_value     = (HISTORY_QUARTERLY[0].region_data.array[region].investment_value / HISTORY_QUARTERLY[4].region_data.array[region].investment_value  -1)*100;}
    }
    
    return 0;
}


/* \fn: int Eurostat_measure_recession(void)
 * \brief: Function to measure the start, duration and end of a recession.
 */
int Eurostat_measure_recession()
{
    //Signal start of recesson: 2 quarters of succesive negative growth of GDP
    if (RECESSION_STARTED==0)
    {
        if ( (HISTORY_QUARTERLY[0].gdp < HISTORY_QUARTERLY[1].gdp) && (HISTORY_QUARTERLY[1].gdp < HISTORY_QUARTERLY[2].gdp))
        {
            RECESSION_STARTED=1;
            RECESSION_DURATION = 0;
        }   
    }   
    //Signal end of recesson: 1 quarter of positive growth of GDP after start of recession
    if (RECESSION_STARTED==1)
    {
        RECESSION_DURATION++;

        if (HISTORY_QUARTERLY[0].gdp >= HISTORY_QUARTERLY[1].gdp)
        {
            RECESSION_STARTED=0;
        }
    }

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_EUROSTAT)
    {
        printf(" - recession started: %d\n", RECESSION_STARTED);
        printf(" - duration of recession: %d\n", RECESSION_DURATION);
    }
    #endif
        
    return 0;
}

