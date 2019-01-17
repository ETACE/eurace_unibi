#include "../header.h"
#include "../Household_agent_header.h"
#include "../my_library_header.h"
#include "Household_aux_header.h"


/*
 * \fn logit_decision_model()
 * \brief Logit decision model to determine the proportion of the asset budget to invest in the risky asset.
 */
int logit_decision_model()
{
    double performance[2];
    double relative_performance[2];
    double proportion[2];
    double sum=0.0;

    //Test code: LOGIT_BETA=0: random, LOGIT_BETA=+inf: select most profitable choice
    BELIEFS.expected_return = RISK_FREE_RATE + random_unif();

    //Expected price: MA(price); determined by Clearinghouse
    BELIEFS.expected_return = ASSETSOWNED.moving_avg_price;

    //Performance:
    performance[0] = RISK_FREE_RATE;
    performance[1] = BELIEFS.expected_return;
  
    //Relative performance:
    sum = performance[0]+performance[1];
    if(sum>0.0)
    {
		relative_performance[0] = performance[0]/sum;
		relative_performance[1] = performance[1]/sum;
    }   
    else printf("\n In logit_decision_model: performance sum is zero.\n");
    
    //Computing the Bolzmann probabilities/fractions: multi-logit
    
    sum = exp(LOGIT_BETA * relative_performance[0])+exp(LOGIT_BETA * relative_performance[1]);
    if(sum>0.0)
    {    
		proportion[0] = exp(LOGIT_BETA * relative_performance[0])/sum;
		proportion[1] = exp(LOGIT_BETA * relative_performance[1])/sum;
    }   
    else printf("\n In logit_decision_model: Proportion sum is zero.\n");

    #ifdef _DEBUG_MODE    
    if (PRINT_DEBUG_AFM)
    {
		printf("\n\n Logit_decision_model: sum = %f\t p1=%f\t p2=%f", sum, proportion[0], proportion[1]);
		printf("\n\t proportion[1]=%f", proportion[1]);
    }
    #endif

    //fraction_to_invest:
    BELIEFS.fraction_to_invest = proportion[1];
    
    return 0;
}
