/*********************************
 * Eurostat_aux_header.h
 * Header file for Eurostat auxiliary functions.
 * *********************************
 * History:
 * 02/02/09 Sander, added new auxiliary functions
 * 15/09/08 Sander 
 *********************************/

/* Eurostat auxiliary functions */
void Eurostat_reset_data(void);
void Eurostat_compute_mean_price(void);

void Eurostat_read_firm_data(void);
void Eurostat_compute_region_firm_data(void);
void Eurostat_compute_global_firm_data(void);

void Eurostat_read_household_data(void);
void Eurostat_compute_region_household_data(void);
void Eurostat_compute_global_household_data(void);

void Eurostat_calc_macro_data(void);
void Eurostat_calc_price_index(void);
void Eurostat_calc_firm_population(void);
void Eurostat_calc_firm_survival_rates(void);
void Eurostat_measure_export(void);
