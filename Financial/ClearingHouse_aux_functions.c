#include "../header.h"
#include "../ClearingHouse_agent_header.h"
#include "../my_library_header.h"
#include "ClearingHouse_aux_header.h"

/*
 * \fn ClearingHouse_correct_rationing_positive(int total_rationing)
 * \brief Non-uniform random rationing mechanism for positive orders.
 * Traverse the PROCESSED_ORDERS:
    + take first long order
    + set random number of units to ration x=random_int(1,total_rationing)
    + if order units > x: ration by x and set y=x, else ration to 0 and set y=old PROCESSED_ORDERS.array[i].quantity
    + decrease total_rationing by y
    + continue to next long order until total_rationing=0
    + if end of PROCESSED_ORDERS is reached while total_rationing>0, declare failure.
 */
void ClearingHouse_correct_rationing_positive(int total_rationing)
{  
    int i;
    int x, rationed_units;
    
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM_CH)
    { 
		printf("Starting correction: correct_rationing_positive(%d)\n", total_rationing);
    }
    #endif

    i=0;
    while ((total_rationing>0)&&(i<PROCESSED_ORDERS.size))
    {
		//Only consider positive orders:
		if(PROCESSED_ORDERS.array[i].quantity>0)
		{	    
			//Ration this order by random x units, if the order has at least x units
			x=random_int(1,total_rationing);
			if (PRINT_DEBUG_AFM_CH) printf("Upper limit on random number = %d\n", total_rationing);
			if (PRINT_DEBUG_AFM_CH) printf("Order: quantity = %d\t rnd ration = %d\t",PROCESSED_ORDERS.array[i].quantity, x);		    
			
			if (x<=PROCESSED_ORDERS.array[i].quantity)
			{
				//Ŕation this order by random x
				PROCESSED_ORDERS.array[i].quantity -= x;
				rationed_units = x;
				if (PRINT_DEBUG_AFM_CH) printf("case 1\t");
			}
			else
			{		    
				//Fully ration this order to 0:
				rationed_units = PROCESSED_ORDERS.array[i].quantity;
				PROCESSED_ORDERS.array[i].quantity =0;
				if (PRINT_DEBUG_AFM_CH) printf("case 2\t");
			}
				if (PRINT_DEBUG_AFM_CH) printf("actual ration = %d\t new quantity = %d\n", rationed_units, PROCESSED_ORDERS.array[i].quantity);
			total_rationing -= rationed_units;
		}//order-loop
		i++;

		// start over
		if (i==PROCESSED_ORDERS.size)
			i=0;
    }//while-loop
    
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM_CH)
    {
		if (i<PROCESSED_ORDERS.size)
			printf("ClearingHouse: Additional random rationing successful: i = %d, total_rationing left= %d\n", i, total_rationing);
    }    
    #endif

    //This is an error
    if (i>=PROCESSED_ORDERS.size)
    {
		printf("Error in ClearingHouse_correct_rationing_positive:\n");
			printf("Additional random rationing failed: reached end of PROCESSED_ORDERS: i = %d, total_rationing left = %d\n", i, total_rationing);	
    }
}

/*
 * \fn ClearingHouse_correct_rationing_negative(int total_rationing)
 * \brief Non-uniform random rationing mechanism for negative orders.
 * Input: total_rationing<0
 * Traverse the PROCESSED_ORDERS:
    + take first long order
    + set random number of units to ration x=random_int(1,-total_rationing)
    + if order units > x: ration by x and set y=x, else ration to 0 and set y=old PROCESSED_ORDERS.array[i].quantity
    + increase total_rationing by y
    + continue to next long order until total_rationing=0
    + if end of PROCESSED_ORDERS is reached while total_rationing<0, declare failure.
 */
void ClearingHouse_correct_rationing_negative(int total_rationing)
{  
    int i;
    int x, rationed_units;
    
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM_CH)
    {
		printf("Starting correction: correct_rationing_negative(%d)\n", total_rationing);
    }
    #endif

    i=0;
    while ((total_rationing<0)&&(i<PROCESSED_ORDERS.size))
    {
		//Only consider negative orders:
		if(PROCESSED_ORDERS.array[i].quantity<0)
		{	    
			//Ration this order by random x units, if the order has at least x units
			x=random_int(1,-total_rationing);
			if (PRINT_DEBUG_AFM_CH) printf("Upper limit on random number = %d\n", total_rationing);
			if (PRINT_DEBUG_AFM_CH) printf("Order: quantity = %d\t rnd ration = %d\t",PROCESSED_ORDERS.array[i].quantity, x);		    
			
			if (x<= -PROCESSED_ORDERS.array[i].quantity)
			{
				//Ŕation this order by random x: a negative order is increased
				PROCESSED_ORDERS.array[i].quantity += x;
				rationed_units = x;
				if (PRINT_DEBUG_AFM_CH) printf("case 3\t");
			}
			else
			{
				//Fully ration this order to 0:
				rationed_units = -PROCESSED_ORDERS.array[i].quantity;
				PROCESSED_ORDERS.array[i].quantity =0;
				if (PRINT_DEBUG_AFM_CH) printf("case 4\t");
			}
			if (PRINT_DEBUG_AFM_CH) printf("actual ration = %d\t new quantity = %d\n", rationed_units, PROCESSED_ORDERS.array[i].quantity);

			//increase to-ration units towards 0:
			total_rationing += rationed_units;
		}//order-loop
		i++;

		// start over
		if (i==PROCESSED_ORDERS.size)
			i=0;
    }//while-loop
    
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM_CH)
    {
	if (i<PROCESSED_ORDERS.size)
	    printf("ClearingHouse: Additional random rationing successful: i = %d, total_rationing left= %d\n", i, total_rationing);
    }    
    #endif

    //This is an error
    if (i>=PROCESSED_ORDERS.size)
    {
		printf("Error in ClearingHouse_correct_rationing_negative:\n");
    	printf("ClearingHouse: Additional random rationing failed: reached end of PROCESSED_ORDERS: i = %d, total_rationing left = %d\n", i, total_rationing);	
    }
}

/*
 * \fn ClearingHouse_diagnosis()
 * \brief Print out post-rationing diagnosis. Test consistency of the processed orders.
 */
void ClearingHouse_diagnosis()
{  
    int i;
    int quantity=0;
    int sum_units_bought=0;
    int sum_units_sold=0;
    double sum_value_bought=0.0;
    double sum_value_sold=0.0;
    double sum_value=0.0;
    int sum_quantity=0;
    
   	for (i=0; i<PROCESSED_ORDERS.size; i++)
	{
	    //Trader is buyer
	    if (PROCESSED_ORDERS.array[i].quantity>0)
	    {
			quantity = PROCESSED_ORDERS.array[i].quantity;
			sum_value_bought += quantity*STOCK_INDEX.price;
			sum_units_bought += quantity;
	    }

	    //Trader is seller
	    if (PROCESSED_ORDERS.array[i].quantity<=0)
	    {
			quantity = PROCESSED_ORDERS.array[i].quantity;
			sum_value_sold += quantity*STOCK_INDEX.price;
			sum_units_sold += -quantity;
	    }
	}
    sum_value 	 = sum_value_bought + sum_value_sold;
    sum_quantity = sum_units_bought - sum_units_sold;

	#ifdef _DEBUG_MODE    
	if (PRINT_DEBUG_AFM_CH)
	{ 
	    printf("===== ClearingHouse_diagnosis() reports =====\n");
	    printf("Total transactions: PROCESSED_ORDERS\n bought (units)=%d\t sold (units)=%d\n", sum_units_bought, sum_units_sold);
	    printf("Consistency checks should evaluate to 0\n sum_value = %f\t sum_quantity = %d\n", sum_value, sum_quantity);
	    printf("===== ++++++++++++++++++ ======\n");
	}    
	#endif
}
