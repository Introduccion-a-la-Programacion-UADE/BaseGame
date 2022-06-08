#include "Utils.h"


void initializeRandom()
{
	//srand(time(NULL));
}


int getRandom(int maxValue)
{
	int random = (rand() % maxValue);

	return random;
}