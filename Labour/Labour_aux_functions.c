/*********************************
 * Labour_aux_functions.c 
 * Labour auxiliary functions.
 * *********************************
 * History:
 * 28/01/09 Sander 
 *********************************/
#include "../header.h"
#include "Labour_aux_headers.h"

int vacancy_list_rank_wage_offer_function(const void *x, const void *y)
{
    if( ((vacancy *)x)->wage_offer > ((vacancy *)y)->wage_offer) return -1;
    else if( ((vacancy *)x)->wage_offer < ((vacancy *)y)->wage_offer) return 1;
    else return 0;
}

int job_offer_list_rank_wage_offer_function(const void *x, const void *y)
{
    if( ((job_offer *)x)->wage_offer > ((job_offer *)y)->wage_offer) return -1;
    else if( ((job_offer *)x)->wage_offer < ((job_offer *)y)->wage_offer) return 1;
    else
    {
        /* If equal randomly sort */
        if(rand()/((double)RAND_MAX + 1) <= 0.5) return -1;
        else return 1;
    }
}

int employee_list_rank_specific_skills_function(const void *x, const void *y)
{
    if( ((employee *)x)->specific_skill > ((employee *)y)->specific_skill) return -1;
    else if( ((employee *)x)->specific_skill < ((employee *)y)->specific_skill) return 1;
    else return 0;
}

int employee_list_rank_general_skills_function(const void *x, const void *y)
{
    if( ((employee *)x)->general_skill > ((employee *)y)->general_skill) return -1;
    else if( ((employee *)x)->general_skill < ((employee *)y)->general_skill) return 1;
    else return 0;
}

/** \fn int job_application_list_rank_general_skill_function(const void *x, const void *y)
 * \brief Returns an integer result of the comparision between the two elements
 * \param x The first element to compare.
 * \param y The second element to compare.
 * \return The compare result.
 */
int job_application_list_rank_general_skill_function(const void *x, const void *y)
{
    if( ((job_application *)x)->general_skill > ((job_application *)y)->general_skill) 
        return -1;
    else if( ((job_application *)x)->general_skill < ((job_application *)y)->general_skill)         return 1;
    else
    {
        if( ((job_application *)x)->specific_skill > ((job_application *)y)
        ->specific_skill) return -1;

        else if( ((job_application *)x)->specific_skill < ((job_application *)y)
        ->specific_skill) return 1;

        else
        {
            /* If equal randomly sort */
            if(rand()/((double)RAND_MAX + 1) <= 0.5) return -1;
            else return 1;
        }
    }
}
