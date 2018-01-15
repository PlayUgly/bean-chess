#include <stdio.h>
#include "moves.h"
#include "bits.h"
#include <limits.h>

int main()
{

	printf("%d\n", INT_MAX);
	printf("%ld\n", LONG_MAX);
	printf("%lu\n", ULONG_MAX);

	InitializeBits();
	
	printf("Bits Initialized!\n");

	for(int i = 0; i < 64; i++)
	{
		printf("%li\n", bit[i]);
	}

	/*
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		char address[2];

	    SquareAddress(squareNumber, address);

		printf("Square %d: %s\n", squareNumber, address);	
	}

	for(int rank = 0; rank < 8; rank++)
	{
		for(int file = 0; file < 8; file++)
		{
			int squareNumber = SquareNumber(rank, file);
			char address[2];

			SquareAddress(squareNumber, address);

			printf("%s: %d\n", address, squareNumber);
		}

	}
	*/
}

