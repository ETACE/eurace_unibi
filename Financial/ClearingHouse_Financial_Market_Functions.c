#include "../header.h"
#include "../ClearingHouse_agent_header.h"
#include "../my_library_header.h"
#include "ClearingHouse_aux_header.h"

/*
 * \fn ClearingHouse_send_index_price()
 * \brief Daily. Send index price message every day, at start of the iteration.
 */
int ClearingHouse_send_index_price()
{  
    //Send stock_index_price
    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_CH) 
    {
		printf("\n ClearingHouse_send_index_price:");
		printf("\n\t Adding the index_price_message with price = %f moving_avg_price = %f\n", STOCK_INDEX.price, STOCK_INDEX.moving_avg_price);
    }
    #endif
    
    add_index_price_message(STOCK_INDEX.price, STOCK_INDEX.moving_avg_price);

    return 0;
}

/*
 * \fn ClearingHouse_send_index_info()
 * \brief First day of month. Compute dividend for the stock_index, and send index info message.
 */
int ClearingHouse_send_index_info()
{  
    int i;

    //Compute dividend per share for the stock_index
    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_CH) 
    {
		printf("\n ClearingHouse_send_stock_index_info:");
		printf("\n\t MONTHLY_COUNTER_TOTAL_DIVIDEND=%f STOCK_INDEX.weight=%f STOCK_INDEX.nr_shares=%d\n", MONTHLY_COUNTER_TOTAL_DIVIDEND, STOCK_INDEX.weight, STOCK_INDEX.nr_shares);
    }
    #endif
    
    
    //All firms have equal weight in the stock index
    if (STOCK_INDEX.nr_shares>0)
		STOCK_INDEX.dividend_per_share = MONTHLY_COUNTER_TOTAL_DIVIDEND /STOCK_INDEX.nr_shares;
    else
		printf("DIVISION BY ZERO: Error in ClearingHouse_send_index_info: STOCK_INDEX.nr_shares = %d", STOCK_INDEX.nr_shares);
	
    //Random dividend process
    //RANDOM_NUMBERS_NORMAL is N(100,1.0) distributed
    i = random_int(0,RANDOM_NUMBERS_NORMAL.size-1);
    
    //Scale total dividend income of a household to 1% of monthly wage:
    //STOCK_INDEX.dividend_per_share = RANDOM_NUMBERS_NORMAL.array[i]; //Test code: random number
    //STOCK_INDEX.dividend_per_share = 0.01*(RANDOM_NUMBERS_NORMAL.array[i]/100)/(STOCK_INDEX.nr_shares/1600);
    
    //Send stock_index dividend per unit
    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_CH) 
    {
	printf("\n\t Adding the index_info_message with dividend_per_share = %f\n", STOCK_INDEX.dividend_per_share);
    }
    #endif
    
    add_index_info_message(STOCK_INDEX.dividend_per_share);
    
    return 0;
}

/*
 * \fn ClearingHouse_receive_dividend_info()
 * \brief Read dividend_info messages. Daily, at end of iteration.
 */
int ClearingHouse_receive_dividend_info()
{   
    
    //Reset counter on 1st day of month
    if (DAY%MONTH==1)
		MONTHLY_COUNTER_TOTAL_DIVIDEND=0.0;
    
    //Read dividend_info messages and add to counter
    START_DIVIDEND_INFO_MESSAGE_LOOP
		MONTHLY_COUNTER_TOTAL_DIVIDEND += dividend_info_message->total_dividend;	
    FINISH_DIVIDEND_INFO_MESSAGE_LOOP

    //Update stock index dividend
    STOCK_INDEX.total_dividend = MONTHLY_COUNTER_TOTAL_DIVIDEND;

    #ifdef _DEBUG_MODE
    if (PRINT_DEBUG_CH) 
    {
		printf("\n\n ClearingHouse_receive_dividend_info:");
		printf("\n\t MONTHLY_COUNTER_TOTAL_DIVIDEND=%f\n\n", MONTHLY_COUNTER_TOTAL_DIVIDEND);
    }
    #endif

    return 0;
}

/*
 * \fn ClearingHouse_receive_orders()
 * \brief Read order messages, and add these to the pending_orders array.
 */
int ClearingHouse_receive_orders()
{  
    int i;
    int quantity;
    
    //Reset the pending_orders array
    reset_order_array(&PENDING_ORDERS);
    
    //Add all incoming orders to the pending_orders array
    //ADT: add_order(&PENDING_ORDERS, trader_id, value, quantity)
    //quantity is the bid/ask quantity given current price
    START_ORDER_MESSAGE_LOOP
		quantity = (int)((order_message->value)/STOCK_INDEX.price);
		add_order(&PENDING_ORDERS, order_message->trader_id, order_message->value, quantity);
    FINISH_ORDER_MESSAGE_LOOP
    
    
    
    //Diagnosis
    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM)
    { 
		printf("\n\n ClearingHouse_receive_orders:");

		printf("\n==== Step 1: Pending Orders:\n");
		if (PENDING_ORDERS.size==0)
			printf("\n No orders\n\n");
		for (i=0; i<PENDING_ORDERS.size; i++)
		{
			printf("(ID, Value, Quantity) = (%d %+f %+d)\n", PENDING_ORDERS.array[i].trader_id, PENDING_ORDERS.array[i].value, PENDING_ORDERS.array[i].quantity);
		}
		printf("===== +++++++++++++++ ====\n");
    }    
    #endif
    
    return 0;
}

/*
 * \fn ClearingHouse_compute_transactions()
 * \brief Function to process the pending orders, and compute transactions.
 */
int ClearingHouse_compute_transactions()
{  
    int i;
    int trader_id;
    int quantity=0;
    double value=0.0;
    
    int demand=0;
    int supply=0;

    int sum_units_sold=0;
    int sum_units_bought=0;
    int sum_quantity=0;
    double sum_value=0.0;
    
/*
    //Pending order array:
	PENDING_ORDERS.array[i].trader_id
	PENDING_ORDERS.array[i].value
	PENDING_ORDERS.array[i].quantity

    //Processed order array:
	PROCESSED_ORDERS.array[i].trader_id
	PROCESSED_ORDERS.array[i].value
	PROCESSED_ORDERS.array[i].quantity
	
    //Reset the processed order array	
	reset_order_array(&PROCESSED_ORDERS);
	
    //Adding an order to processed orders:
	add_order(&PROCESSED_ORDERS, trader_id, value, quantity)
*/

    //Process the pending_orders array, produce processed_orders
    reset_order_array(&PROCESSED_ORDERS);
    
    //Step 2: aggregates
    demand = 0;
    supply = 0;
    
    #ifdef _DEBUG_MODE
	if (PRINT_DEBUG_AFM_CH) 
	{
	    printf("\n\n ClearingHouse_compute_transactions:");
	    printf("\n==== Step 2: aggregates\nPENDING_ORDERS.size = %d\n", PENDING_ORDERS.size);
	}

	if (PRINT_DEBUG_AFM) 
	    printf("Here is what is stored in PENDING_ORDERS:\n\n");
    #endif
    
    for (i=0; i<PENDING_ORDERS.size; i++)
    {

    	value = PENDING_ORDERS.array[i].value;

	//Transform requested value to units: set PENDING_ORDERS.array[i].quantity 
	if (value>0.0)
	{
	    demand += (int)(value/STOCK_INDEX.price);
	    PENDING_ORDERS.array[i].quantity = (int)(value/STOCK_INDEX.price);
	    
	    #ifdef _DEBUG_MODE    
	    if (PRINT_DEBUG_AFM)
	    { 
		printf("Order %d\n value = %f\t demand + %d\t PENDING_ORDERS.quantity = %d\n", i, value, (int)(value/STOCK_INDEX.price), (int)(value/STOCK_INDEX.price));
	    }    
	    #endif
	}
	else
	{
	    supply += -1*(int)(value/STOCK_INDEX.price);
	    PENDING_ORDERS.array[i].quantity = (int)(value/STOCK_INDEX.price);

	    #ifdef _DEBUG_MODE    
	    if (PRINT_DEBUG_AFM)
	    { 
		printf("Order %d\n value = %f\t supply + %d\t PENDING_ORDERS.quantity = %d\n", i, value, -1*(int)(value/STOCK_INDEX.price), (int)(value/STOCK_INDEX.price));
	    }    
	    #endif
	}
    }

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM_CH)
	printf("\n==== Step 3: Check for zeros and break\n");
    #endif

    //Step 3: Check for zeros and break
    if (demand ==0)
    {
	#ifdef _DEBUG_MODE    
	if (PRINT_DEBUG_AFM_CH)
	    printf("In ClearingHouse_compute_transactions: Zero demand side.\n");
	#endif	
    }
    if (supply ==0)
    {
	#ifdef _DEBUG_MODE 
	if (PRINT_DEBUG_AFM_CH)
	    printf("In ClearingHouse_compute_transactions: Zero supply side.\n");
	#endif	
    }
    
    if (demand==0 || supply ==0)
    {
	#ifdef _DEBUG_MODE 
	if (PRINT_DEBUG_AFM_CH)
	    printf(" ==> Adding zero processed orders for all.\n");
	#endif	
	
	DSRATIO = 1;
	
	//Add zero orders for all
	for (i=0; i<PENDING_ORDERS.size; i++)
	{
	    trader_id = PENDING_ORDERS.array[i].trader_id;
	    add_order(&PROCESSED_ORDERS, trader_id, 0.0, 0);
	}
    }
    else if (demand>0 && supply>0)
    {
	#ifdef _DEBUG_MODE    
	if (PRINT_DEBUG_AFM_CH)
	    printf("No zeros: continue with rationing\n");
	#endif
	
	//Demand/Supply ratio
	DSRATIO = (double)demand/(double)supply;
	
	//Step 4: rationing of long side
	#ifdef _DEBUG_MODE    
	if (PRINT_DEBUG_AFM_CH)
	    printf("\n==== Step 4: rationing of long side\n");
	#endif

	//Demand rationing
	if (DSRATIO>1.0)
	for (i=0; i<PENDING_ORDERS.size; i++)
	{
	    //Trader is buyer
	    if (PENDING_ORDERS.array[i].quantity>0)
	    {
			quantity = (int)((1/DSRATIO)*PENDING_ORDERS.array[i].quantity);
			sum_units_bought += quantity;
	    }

	    //Trader is seller
	    if (PENDING_ORDERS.array[i].quantity<=0)
	    {
			quantity = PENDING_ORDERS.array[i].quantity;
			sum_units_sold += -quantity;
	    }

	    //Add new processed order
	    value = quantity*STOCK_INDEX.price;
	    sum_value += value;
	    sum_quantity += quantity;
	    add_order(&PROCESSED_ORDERS, PENDING_ORDERS.array[i].trader_id, value, quantity);
	}
	else
	//Supply rationing
	for (i=0; i<PENDING_ORDERS.size; i++)
	{
	    //Trader is buyer
	    if (PENDING_ORDERS.array[i].quantity>0) 
	    {
			quantity = PENDING_ORDERS.array[i].quantity;
			sum_units_bought += quantity;
	    }
	    //Trader is seller
	    if (PENDING_ORDERS.array[i].quantity<=0)
	    {		
			quantity = (int)(DSRATIO*PENDING_ORDERS.array[i].quantity);
			sum_units_sold += -quantity;
	    }
		
	    //Add new processed order
	    value = quantity*STOCK_INDEX.price;
	    sum_value += value;
	    sum_quantity += quantity;
	    add_order(&PROCESSED_ORDERS, PENDING_ORDERS.array[i].trader_id, value, quantity);
	}

    }
    
    //Diagnosis
	#ifdef _DEBUG_MODE    
	if (PRINT_DEBUG_AFM_CH)
	{ 
	    printf("===== Rationing results ======\n");
	    printf("Total orders: PENDING_ORDERS\n demand (units)=%d\t supply (units)=%d\n", demand, supply);	    
	    ClearingHouse_diagnosis();
	}    
	#endif

	if (sum_value > 1e-1 || sum_value < -1e-1 || sum_quantity!=0)
	{
	    #ifdef _DEBUG_MODE    
	    if (PRINT_DEBUG_AFM_CH)
	    { 
		printf("Error in ClearingHouse_compute_transactions: unit consistency check failed.\n");
		printf("sum_value=%f\t sum_quantity = %d.\n", sum_value, sum_quantity);
	    }    
	    #endif

	    if (sum_quantity>0)
			ClearingHouse_correct_rationing_positive(sum_quantity);
	    if (sum_quantity<0)
			ClearingHouse_correct_rationing_negative(sum_quantity);
	    //Check consistency:
	    ClearingHouse_diagnosis();
	}

    return 0;
}


/*
 * \fn ClearingHouse_update_price()
 * \brief Function to update the stock index price.
 */
int ClearingHouse_update_price()
{  
    int i;
    double coeff;
    double sum;
    
    //Step 3: Update the price of the stock market index using the latest supply/demand data.
    coeff = pow(DSRATIO, INDEX_PRICE_ADJ);
    
    if (coeff > INDEX_PRICE_ADJ_MAX) 
		coeff = INDEX_PRICE_ADJ_MAX;
    else if (coeff < INDEX_PRICE_ADJ_MIN)
		coeff = INDEX_PRICE_ADJ_MIN;
        
    STOCK_INDEX.price = coeff*STOCK_INDEX.price;
	STOCK_INDEX_PRICE = STOCK_INDEX.price;
    if (PRINT_DEBUG_AFM_CH) printf("\n In ClearingHouse_compute_transactions: STOCK_INDEX.price = %f\n", STOCK_INDEX.price);


    //Step 4: Shift the price history and determine the moving average:
    
    //remove the oldest price at the front of the list, reduce array size by 1
    remove_double(&STOCK_INDEX.price_history, 0);
    
    //add new price at the end of the list, increase array size by 1
    add_double(&STOCK_INDEX.price_history, STOCK_INDEX.price);
    
    sum=0.0;
    for (i=0;i<STOCK_INDEX.price_history.size;i++)
	sum += STOCK_INDEX.price_history.array[i];
	
    if(STOCK_INDEX.price_history.size>0)
		STOCK_INDEX.moving_avg_price = sum/STOCK_INDEX.price_history.size;
    else printf("Error in ClearingHouse_update_price(): STOCK_INDEX.price_history.size=%d\n", STOCK_INDEX.price_history.size);
    
    return 0;
}

/*
 * \fn ClearingHouse_send_transaction_info()
 * \brief Function to send the processed orders.
 */
int ClearingHouse_send_transaction_info()
{  
    int i;
    
    //Only send  order_status if print_debug_afm is off:
    if (~PRINT_DEBUG_AFM)
    { 

		//Send processed_orders array
		for (i=0; i<PROCESSED_ORDERS.size; i++)
		{
			add_order_status_message(PROCESSED_ORDERS.array[i].trader_id, PROCESSED_ORDERS.array[i].value, PROCESSED_ORDERS.array[i].quantity);
		}
	}

	//Send empty order_status if print_debug_afm is off:
	if (PRINT_DEBUG_AFM)
	{ 
		//Send processed_orders array
		for (i=0; i<PROCESSED_ORDERS.size; i++)
		{
			add_order_status_message(PROCESSED_ORDERS.array[i].trader_id, 0.0,0);
		}
    }

    return 0;
}

