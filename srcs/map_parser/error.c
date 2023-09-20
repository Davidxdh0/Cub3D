#include "parser.h"

void	errorMessage(char* msg)
{
	printf("Error\n");
	printf("%s\n", msg);
}

void	errorExit(char* msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(0);
}