#include "../header.h"
#include "../IGFirm_agent_header.h"
#include "../my_library_header.h"

/*
 * \fn IGFirm_remains_in_bankruptcy()
 * \brief In bankruptcy branch: if a.external_financial_needs > 0.0, send an error message
 */
int IGFirm_remains_in_bankruptcy(void)
{
	//printf("Error in Bankruptcy: IGFirm %d remains in bankruptcy. External financial needs: %f\n", ID, EXTERNAL_FINANCIAL_NEEDS);
	printf("Error in Bankruptcy: IGFirm %d remains in bankruptcy.\n", ID);
	return 0;
}

/*
 * \fn IGFirm_receive_stock_info_dummy()
 * \brief Dummy for stategraph interface.
 */
int IGFirm_receive_stock_info_dummy(void)
{
	return 0;
}


