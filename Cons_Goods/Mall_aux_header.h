/*********************************
 * Mall_aux_header.h
 * Header file for Mall auxiliary functions.
 * *********************************
 * History:
 * 29/10/08 Sander 
 *********************************/

/* Mall auxiliary functions */
void sort_mall_sales_list(sales_statistics_array * sales_mall_list);
int sales_statistics_list_rank_sales_function(const void *x, const void *y);
void Mall_add_export_data(int firm_region, int household_region, double export_volume, double export_value, double export_previous_value);
