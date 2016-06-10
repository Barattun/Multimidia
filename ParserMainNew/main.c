#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AuxiliarFunction.h"



int main(int argc, char **argv)
{
	if (argc > 1)
	{
		ClassificaEntrada(argc, argv);
	}
	else
	{
		printf("\nEntrada Invalida\nExit!\n");
	}

	printf("\n");
	return 0;
}

