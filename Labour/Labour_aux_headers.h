/*********************************
 * Labour_aux_header.h
 * Header file for Labour auxiliary functions.
 * *********************************
 * History:
 * 28/01/09 Sander 
 *********************************/

/* Labour  auxiliary functions */

void sort_vacancy_list(vacancy_array * vacancy_list);
void sort_job_offer_list(job_offer_array * job_offer_list);
void sort_job_application_list(job_application_array * job_application_list);

int vacancy_list_rank_wage_offer_function(const void *x, const void *y);
int job_offer_list_rank_wage_offer_function(const void *x, const void *y);
int employee_list_rank_specific_skills_function(const void *x, const void *y);
int employee_list_rank_general_skills_function(const void *x, const void *y);
int job_application_list_rank_general_skill_function(const void *x, const void *y);
