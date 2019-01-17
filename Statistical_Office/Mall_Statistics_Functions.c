#include "../header.h"
#include "../Mall_agent_header.h"
#include "../my_library_header.h"


int Mall_send_id_to_firms()
{
    
    add_msg_mall_id_to_firms_message(ID,REGION_ID);
    return 0;
}


int Mall_initialize_firm_arrays()
{
    
if(XML_CLONED==1)
{
    int i,j;

	//Clean up the revenue array
    for(i=0;i<FIRM_REVENUES.size;i++)
	{
		remove_sales_in_mall(&FIRM_REVENUES,i);
		i--;
	 }

	//Clean up the cuurent stock array
	for(j=0;j<CURRENT_STOCK.size;j++)
	{
		remove_mall_stock(&CURRENT_STOCK,j);
		j--;
	 }


	//read the messages sent by firms

	START_MSG_FIRM_ID_TO_MALLS_MESSAGE_LOOP
	
	add_mall_stock(&CURRENT_STOCK,msg_firm_id_to_malls_message->firm_id,  msg_firm_id_to_malls_message->region_id , 0.0,1.0,0.0,0.0) ;


	//Add on FIRM_REVENUES array
	add_sales_in_mall(&FIRM_REVENUES,msg_firm_id_to_malls_message->firm_id,0.0);

	FINISH_MSG_FIRM_ID_TO_MALLS_MESSAGE_LOOP



}	

    return 0;
}
