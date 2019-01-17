/*********************************
 * Mall_aux_functions.c 
 * Mall auxiliary functions.
 * *********************************
 * History:
 * 29/10/08 Sander 
 *********************************/
#include "../header.h"
#include "../Mall_agent_header.h"
#include "Mall_aux_header.h"


/* \fn: int sales_statistics_list_rank_sales_function(const void *x, const void *y)
 * \brief: 
 */
int sales_statistics_list_rank_sales_function(const void *x, const void *y)
{
    if( ((temporary_sales_statistics *)x)->sales < ((temporary_sales_statistics *)y)->sales) return -1;
    else if( ((temporary_sales_statistics *)x)->sales > ((temporary_sales_statistics *)y)->sales) return 1;
    else return 0;
}


/* \fn: void Mall_add_export_data()
 * \brief: Function to add data to the export matrix (during every transaction).
 * export_volume: Q_t
 * export_value: P_t*Q_t
 * export_previous_value: P_t-1*Q_t
 */
void Mall_add_export_data(int firm_region, int household_region, double export_volume, double export_value, double export_previous_value)
{
	int index;
	
	//add value to export matrix
	index=(firm_region-1)*TOTAL_REGIONS+(household_region-1);
	EXPORT_VOLUME_MATRIX[index] += export_volume;
	EXPORT_VALUE_MATRIX[index] += export_value;
	EXPORT_PREVIOUS_VALUE_MATRIX[index] += export_previous_value;
}


