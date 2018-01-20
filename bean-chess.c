#include <stdio.h>
#include "bits.h"
#include "moves.h"
#include <limits.h>

int main()
{

	char address[2];
	long *movePointer;

	/*
	printf("%d\n", INT_MAX);
	printf("%ld\n", LONG_MAX);
	printf("%lu\n", ULONG_MAX);
	*/

	InitializeBits();
	printf("Bits Initialized!\n");

	InitializeMoves();
	printf("Pawn Moves Initialized!\n");
	
	/*
	for(int i = 0; i < 64; i++)
	{
		printf("%li\n", bit[i]);
	}

	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
	    SquareAddress(squareNumber, address);

		printf("Square %d: %s\n", squareNumber, address);	
	}

	for(int rank = 0; rank < 8; rank++)
	{
		for(int file = 0; file < 8; file++)
		{
			int squareNumber = SquareNumber(rank, file);

			SquareAddress(squareNumber, address);

			printf("%s: %d\n", address, squareNumber);
		}

	}


	printf("White Pawn Moves\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
			SquareAddress(squareNumber, address);
			printf("\t%s: ", address);

			movePointer = whitePawnMoves[squareNumber];	

			while(*movePointer)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			printf("\n");

	}

	printf("\n\n");
	printf("Black Pawn Moves\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
			SquareAddress(squareNumber, address);
			printf("\t%s: ", address);

			movePointer = blackPawnMoves[squareNumber];	

			while(*movePointer)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			printf("\n");
	}
	*/

	printf("White Pawn Captures\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
			SquareAddress(squareNumber, address);
			printf("\t%s: ", address);

			movePointer = whitePawnCaptures[squareNumber];	

			while(*movePointer)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			printf("\n");

	}

	printf("\n\n");
	printf("Black Pawn Captures\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
			SquareAddress(squareNumber, address);
			printf("\t%s: ", address);

			movePointer = blackPawnCaptures[squareNumber];	

			while(*movePointer)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			printf("\n");
	}


	TerminateMoves();
}

