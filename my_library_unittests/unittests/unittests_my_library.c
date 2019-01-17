#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

#include "../../header.h"
#include "../../my_library_header.h"


void unittest_random_int()
{   
	int i,a;
	for(i=0;i<100;i++)
	{
		a= random_int(0,100);
		printf("%d ",a);
	}

}

void unittest_random_unif()
{   
	int i;
	for(i=0;i<100;i++)
	{
		printf("%f ",random_unif());
	}

}

