#include "../header.h"
#include "../Mall_agent_header.h"
#include "../my_library_header.h"
#include "Mall_aux_header.h"



/********************Mall agent functions*****************/

int Mall_idle()
{
    return 0;
}

/** \fn Mall_update_mall_stock()
 * \brief Malls receive the goods deliveries  
 */
int Mall_update_mall_stock()
{
    int i,j;
    
    START_UPDATE_MALL_STOCK_MESSAGE_LOOP
    
    //Filter: 
    if(ID==update_mall_stock_message->mall_id)
    {
        for(j=0; j < CURRENT_STOCK.size; j++)
        {   
            
            if(update_mall_stock_message->firm_id==
            CURRENT_STOCK.array[j].firm_id)
            {
                CURRENT_STOCK.array[j].stock=CURRENT_STOCK.array[j].
                stock + update_mall_stock_message->quantity;
                
                CURRENT_STOCK.array[j].firm_id=
                update_mall_stock_message->firm_id;

                CURRENT_STOCK.array[j].quality=
                update_mall_stock_message->quality;

                CURRENT_STOCK.array[j].price=
                update_mall_stock_message->price;
                
                CURRENT_STOCK.array[j].previous_price=
                                update_mall_stock_message->previous_price;
            }
        }
    }
    FINISH_UPDATE_MALL_STOCK_MESSAGE_LOOP
    
    /*This reads the bankruptcy message of firms in a illiquitity bankruptcy*/
    START_BANKRUPTCY_ILLIQUIDITY_MESSAGE_LOOP
    for(i=0; i< CURRENT_STOCK.size; i++)
    {   
                
                if(bankruptcy_illiquidity_message->firm_id==
                CURRENT_STOCK.array[i].firm_id)
                {
                    CURRENT_STOCK.array[i].stock=0;
                    
                    //CURRENT_STOCK.array[i].firm_id=update_mall_stock_message->firm_id;

                    CURRENT_STOCK.array[i].quality=0;

                    CURRENT_STOCK.array[i].price=0;
                    
                    CURRENT_STOCK.array[i].previous_price=0;
                }
    }
    FINISH_BANKRUPTCY_ILLIQUIDITY_MESSAGE_LOOP 

    return 0;
}

/** \fn Mall_send_quality_price_info_1()
 * \brief Malls send message with quality and price information. 
 */
int Mall_send_quality_price_info_1()
{

    int i;
    int available;

    for(i=0;i<CURRENT_STOCK.size;i++)
    {
        if(CURRENT_STOCK.array[i].stock > 0)
        {
            available= 1;
        }else
        {
            available= 0;
        }   
        
        add_quality_price_info_1_message(ID,REGION_ID,
        CURRENT_STOCK.array[i].firm_id,         
        CURRENT_STOCK.array[i].quality, 
        CURRENT_STOCK.array[i].price,available);

    }
    
    return 0;
}


/** \fn Mall_update_mall_stocks_sales_rationing_1()
 * \brief Mall reads the consumption requests and satisfies the demand if possible (otherwise rationing). 
 */
int Mall_update_mall_stocks_sales_rationing_1()
{
    int i,j,k,l;
    double aggregated_demand;
    double rationing_rate;
    double sold_quantity_to_consumer;

    consumption_request_array consumption_request_list;
    init_consumption_request_array(&consumption_request_list);
    /*Read the consumption request message*/
    START_CONSUMPTION_REQUEST_1_MESSAGE_LOOP
    //Filter: (a.id==m.mall_id)
    if(ID==consumption_request_1_message->mall_id)
    {
            add_consumption_request(&consumption_request_list,consumption_request_1_message->worker_id,
            consumption_request_1_message->region_id, 
            consumption_request_1_message->firm_id, 
            consumption_request_1_message->quantity );
    }
    FINISH_CONSUMPTION_REQUEST_1_MESSAGE_LOOP


    /*Aggregation of demand per firm*/
    for(i = 0; i < CURRENT_STOCK.size;i++)
    {
        aggregated_demand=0.0;
        for(j = 0; j < consumption_request_list.size; j++)  
        {
            if(CURRENT_STOCK.array[i].firm_id == 
            consumption_request_list.array[j].firm_id)
            {
                aggregated_demand+= consumption_request_list.array[j].quantity;
            }
        }
        /*If aggregated demand > current stock . Rationing*/
        if(aggregated_demand> CURRENT_STOCK.array[i].stock)
        {
    
            rationing_rate= CURRENT_STOCK.array[i].stock/ aggregated_demand;
            
            
            for(k=0; k<consumption_request_list.size;k++)
            {
                if(CURRENT_STOCK.array[i].firm_id == 
                consumption_request_list.array[k].firm_id)      
                {
                    sold_quantity_to_consumer  = consumption_request_list.array[k].quantity*
                    rationing_rate;
                    
                    /*Send accepted consumption volume*/
                    add_accepted_consumption_1_message(ID,
                    consumption_request_list.array[k].worker_id, 
                    sold_quantity_to_consumer, 1);
                    
                    /*Add on Export matrix*/
                    Mall_add_export_data(CURRENT_STOCK.array[i].region_id, consumption_request_list.array[k].consumer_region_id,
                            sold_quantity_to_consumer, sold_quantity_to_consumer*CURRENT_STOCK.array[i].price, sold_quantity_to_consumer*CURRENT_STOCK.array[i].previous_price);
                }
            }
            /*Calc and store revenues per firm*/
            for(k=0; k< CURRENT_STOCK.size;k++)
            {
                    
                if(CURRENT_STOCK.array[i].firm_id==
                FIRM_REVENUES.array[k].firm_id)
                {
                    FIRM_REVENUES.array[k].sales = CURRENT_STOCK.array[i]
                    .stock*CURRENT_STOCK.array[i].price;
                
                    /*mall stock completely sold out*/
                    CURRENT_STOCK.array[i].stock=0.0;
                }
            }
        }
        else /*Otherwise no rationing*/
        {
            
            for(k=0; k<consumption_request_list.size;k++)
            {
                if(CURRENT_STOCK.array[i].firm_id == 
                consumption_request_list.array[k].firm_id)
                {   /*Send accepted consumption volume*/
                    
                    sold_quantity_to_consumer  = consumption_request_list.array[k].quantity;
                    
                    add_accepted_consumption_1_message(ID,
                    consumption_request_list.array[k].worker_id,
                    consumption_request_list.array[k].quantity, 0);

                    /*Add on Export matrix*/
                    Mall_add_export_data(CURRENT_STOCK.array[i].region_id, consumption_request_list.array[k].consumer_region_id,
                            sold_quantity_to_consumer, sold_quantity_to_consumer*CURRENT_STOCK.array[i].price, sold_quantity_to_consumer*CURRENT_STOCK.array[i].previous_price);
                }   
            }
    
            for(l=0; l< CURRENT_STOCK.size;l++)
            {
                /*Calc and store revenues per firm*/
                if(CURRENT_STOCK.array[i].firm_id==
                FIRM_REVENUES.array[l].firm_id)
                {
                    FIRM_REVENUES.array[l].sales = 
                    aggregated_demand *CURRENT_STOCK.array[i].price ;
                    /*remaining mall stock*/
                    CURRENT_STOCK.array[i].stock-=aggregated_demand;
        
                }
            }
        }
    }

    free_consumption_request_array(&consumption_request_list);

    /*Send second price info*/

    int available;
    for(i=0;i<CURRENT_STOCK.size;i++)
    {

        if(CURRENT_STOCK.array[i].stock > 0)
        {
            available= 1;
        }else
        {
            available= 0;
        }
    
        add_quality_price_info_2_message(ID,REGION_ID,
        CURRENT_STOCK.array[i].firm_id,         
        CURRENT_STOCK.array[i].quality, 
        CURRENT_STOCK.array[i].price,available);

    }




    return 0;
}


/** \fn Mall_update_mall_stocks_sales_rationing_2()
 * \brief After the second request round the mall satisfies the demand if possible, otherwise rationing.
 */
int Mall_update_mall_stocks_sales_rationing_2()
{
    int i,j,k,l;
    double aggregated_demand;
    double rationing_rate;
    double sold_quantity_to_consumer;

    consumption_request_array consumption_request_list;
    init_consumption_request_array(&consumption_request_list);

        /*Read the request*/
    START_CONSUMPTION_REQUEST_2_MESSAGE_LOOP
    //Filter: (a.id==m.mall_id)
    if(ID==consumption_request_2_message->mall_id)
    {
            add_consumption_request(&consumption_request_list,
            consumption_request_2_message->worker_id, 
            consumption_request_2_message->region_id, 
            consumption_request_2_message->firm_id, 
            consumption_request_2_message->quantity );
    }
    FINISH_CONSUMPTION_REQUEST_2_MESSAGE_LOOP

        /*Aggregation of demand*/
    for(i = 0; i < CURRENT_STOCK.size;i++)
    {
        aggregated_demand=0;
        for(j = 0; j < consumption_request_list.size; j++)
        {
            if(CURRENT_STOCK.array[i].firm_id == 
            consumption_request_list.array[j].firm_id)
            {
                aggregated_demand+= consumption_request_list.array[j].quantity;
            }
        }
        /*If agg demand > mall stocks . Rationing*/
        if(aggregated_demand > CURRENT_STOCK.array[i].stock)
        {
        

            rationing_rate= CURRENT_STOCK.array[i].stock/ aggregated_demand;
    
            for(k=0; k<consumption_request_list.size;k++)
            {
                if(CURRENT_STOCK.array[i].firm_id == 
                consumption_request_list.array[k].firm_id)
                {
                    
                    sold_quantity_to_consumer  = consumption_request_list.array[k].quantity*
                                        rationing_rate;
                                        
                    add_accepted_consumption_2_message(ID,
                    consumption_request_list.array[k].worker_id,
                    sold_quantity_to_consumer, 1);
                    
                    /*Add on Export matrix*/
                    Mall_add_export_data(CURRENT_STOCK.array[i].region_id, consumption_request_list.array[k].consumer_region_id,
                            sold_quantity_to_consumer, sold_quantity_to_consumer*CURRENT_STOCK.array[i].price, sold_quantity_to_consumer*CURRENT_STOCK.array[i].previous_price);
                }
            }
            /*Revenues and final mall stock*/
            for(k=0; k< CURRENT_STOCK.size;k++)
            {
                if(CURRENT_STOCK.array[i].firm_id==
                FIRM_REVENUES.array[k].firm_id)
                {
                    FIRM_REVENUES.array[k].sales += CURRENT_STOCK.array[i]
                    .stock*CURRENT_STOCK.array[i].price;

                    CURRENT_STOCK.array[i].stock=0; 
                }
            }
        }
        else /*Otherwise no rationg*/
        {

            for(k=0; k<consumption_request_list.size;k++)
            {
                if(CURRENT_STOCK.array[i].firm_id == 
                consumption_request_list.array[k].firm_id)
                {
                    sold_quantity_to_consumer  = consumption_request_list.array[k].quantity;
                    
                    add_accepted_consumption_2_message(ID,
                    consumption_request_list.array[k].worker_id, 
                    consumption_request_list.array[k].quantity, 0);
                    
                    /*Add on Export matrix*/
                    Mall_add_export_data(CURRENT_STOCK.array[i].region_id, consumption_request_list.array[k].consumer_region_id,
                            sold_quantity_to_consumer, sold_quantity_to_consumer*CURRENT_STOCK.array[i].price, sold_quantity_to_consumer*CURRENT_STOCK.array[i].previous_price);
                }   
            }
            /*revenues and final stocks*/
            for(l=0; l< CURRENT_STOCK.size;l++)
            {
        
                if(CURRENT_STOCK.array[i].firm_id==
                FIRM_REVENUES.array[l].firm_id)
                {
    
                    FIRM_REVENUES.array[l].sales += aggregated_demand *
                    CURRENT_STOCK.array[i].price;
                    
                    CURRENT_STOCK.array[i].stock-=aggregated_demand;
                }
            }
        }
    }
    free_consumption_request_array(&consumption_request_list);

    return 0;
}

/** \fn Mall_pay_firm()
 * \brief Mall transfers the revenues to the firm
 */
int Mall_pay_firm()
{
    int i,j;
    
    TOTAL_SUPPLY=0;
    int stock_empty;

    for(i=0; i<CURRENT_STOCK.size;i++)
    {
        TOTAL_SUPPLY += CURRENT_STOCK.array[i].stock;
    }

    
    for(i=0; i< FIRM_REVENUES.size;i++)
    {
        
        
        for(j=0; j<CURRENT_STOCK.size;j++)
        {
        
            if(FIRM_REVENUES.array[i].firm_id == CURRENT_STOCK.array[j].firm_id)
            {

                if(CURRENT_STOCK.array[j].stock ==0)
                {
                    stock_empty =1;
                }else
                {
                    stock_empty =0;
                }
            
                add_sales_message(ID, FIRM_REVENUES.array[i].firm_id,
                        FIRM_REVENUES.array[i].sales,stock_empty,CURRENT_STOCK.array[j].stock);
            }
        }
    }


    return 0;
}

/* \fn: int Mall_reset_export_data()
 * \brief: Function to reset the export matrix (at start of month).
 */
int Mall_reset_export_data()
{
    int i,j;
    
    //reset export matrix
    for (i=0; i<TOTAL_REGIONS; i++)
    {
        for (j=0; j<TOTAL_REGIONS; j++)
        {
            EXPORT_VOLUME_MATRIX[i*TOTAL_REGIONS+j]=0.0;
            EXPORT_VALUE_MATRIX[i*TOTAL_REGIONS+j]=0.0;
            EXPORT_PREVIOUS_VALUE_MATRIX[i*TOTAL_REGIONS+j]=0.0;
        }
    }
    return 0;
}

/* \fn: int Mall_send_export_data()
 * \brief: Function to send the export matrix to Eurostat.
 */
int Mall_send_export_data()
{
    int firm_region, household_region;
    double export_volume, export_value, export_previous_value;

    //mall sends a bunch of messages with export data (only the non-zero elements)
    for (firm_region=1; firm_region<=TOTAL_REGIONS; firm_region++)
    {
        for (household_region=1; household_region<=TOTAL_REGIONS; household_region++)
        {
            export_volume = EXPORT_VOLUME_MATRIX[(firm_region-1)*TOTAL_REGIONS+(household_region-1)];
            export_value = EXPORT_VALUE_MATRIX[(firm_region-1)*TOTAL_REGIONS+(household_region-1)];
            export_previous_value = EXPORT_PREVIOUS_VALUE_MATRIX[(firm_region-1)*TOTAL_REGIONS+(household_region-1)];
            if (export_volume > 0.0)
            {
                add_mall_data_message(ID, firm_region, household_region, export_volume, export_value, export_previous_value);
            }           
        }
    }
    
    return 0;
}

/* \fn: int Mall_read_insolvency_bankruptcy()
 * \brief: Function to read insolvency_bankruptcy messages from firms in insolvency. The mall has to set the current mall stocks equal 0.
 */
int Mall_read_insolvency_bankruptcy()
{
	int i;
	
	START_BANKRUPTCY_INSOLVENCY_MESSAGE_LOOP
    for(i=0; i< CURRENT_STOCK.size; i++)
            {   
                
                if(bankruptcy_insolvency_message->firm_id==
                CURRENT_STOCK.array[i].firm_id)
                {
                    CURRENT_STOCK.array[i].stock=0;
                    
                    //CURRENT_STOCK.array[i].firm_id=update_mall_stock_message->firm_id;

                    CURRENT_STOCK.array[i].quality=0;

                    CURRENT_STOCK.array[i].price=0;
                    
                    CURRENT_STOCK.array[i].previous_price=0;
                }
            }
    
    FINISH_BANKRUPTCY_INSOLVENCY_MESSAGE_LOOP 
    
    return 0;
}

