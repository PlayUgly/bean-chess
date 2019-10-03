#include <stdio.h>
#include <limits.h>
#include "bits.h"
#include "moves.h"

int main()
{

	char address[2];
	long *movePointer;

	struct Moves moves;

	/*
	printf("%d\n", INT_MAX);
	printf("%ld\n", LONG_MAX);
	printf("%lu\n", ULONG_MAX);
	*/

	InitializeBits();
	printf("Bits Initialized!\n");

	InitializeMoves(&moves);
	printf("Moves Initialized!\n");
	
	/*
	for(int i = 0; i < 64; i++)
	{
		printf("%li\n", bit[i]);
	}

	printf("\n\n\n");


	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
	    SquareAddress(squareNumber, address);

		printf("Square %d: %s\n", squareNumber, address);	
	}

	printf("\n\n\n");


	for(int rank = 0; rank < 8; rank++)
	{
		for(int file = 0; file < 8; file++)
		{
			int squareNumber = SquareNumber(rank, file);

			SquareAddress(squareNumber, address);

			printf("%s: %d\n", address, squareNumber);
		}

	}

	printf("\n\n\n");
*/

	printf("White Pawn Moves\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		SquareAddress(squareNumber, address);
		printf("\t%s: ", address);

		movePointer = moves.PawnMoves[2][squareNumber];	

		while(*movePointer > 0)
		{
			SquareAddress(*movePointer, address);
			printf("%s ", address);

			movePointer++;
		}

		printf("\n");
	}

	printf("\n\n\n");


	printf("Black Pawn Moves\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		SquareAddress(squareNumber, address);
		printf("\t%s: ", address);

		movePointer = moves.PawnMoves[0][squareNumber];	

		while(*movePointer > 0)
		{
			SquareAddress(*movePointer, address);
			printf("%s ", address);

			movePointer++;
		}

		printf("\n");
	}

	printf("\n\n\n");


	printf("White Pawn Captures\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		SquareAddress(squareNumber, address);
		printf("\t%s: ", address);

		movePointer = moves.PawnCaptures[2][squareNumber];	

		while(*movePointer > 0)
		{
			SquareAddress(*movePointer, address);
			printf("%s ", address);

			movePointer++;
		}

		printf("\n");
	}

	printf("\n\n\n");


	printf("Black Pawn Captures\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		SquareAddress(squareNumber, address);
		printf("\t%s: ", address);

		movePointer = moves.PawnCaptures[0][squareNumber];	

		while(*movePointer > 0)
		{
			SquareAddress(*movePointer, address);
			printf("%s ", address);

			movePointer++;
		}

		printf("\n");
	}

	printf("\n\n\n");


	printf("Knight Moves\n");

	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		SquareAddress(squareNumber, address);
		printf("\t%s: ", address);

		movePointer = moves.KnightMoves[squareNumber];	

		while(*movePointer > -1)
		{
			SquareAddress(*movePointer, address);
			printf("%s ", address);

			movePointer++;
		}

		printf("\n");
	}

	printf("\n\n\n");


	printf("Bishop Moves\n");

	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		long **pointerToMovePointer = moves.BishopMoves[squareNumber];

		SquareAddress(squareNumber, address);
		printf("\t%s: ", address);

		while(*pointerToMovePointer)
		{
			movePointer = *pointerToMovePointer;

			while(*movePointer > -1)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			*pointerToMovePointer++;
		}


		printf("\n");
	}

	printf("\n\n\n");


	printf("Rook Moves\n");

	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		long **pointerToMovePointer = moves.RookMoves[squareNumber];

		SquareAddress(squareNumber, address);
		printf("\t%s: ", address);

		while(*pointerToMovePointer)
		{
			movePointer = *pointerToMovePointer;

			while(*movePointer > -1)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			*pointerToMovePointer++;
		}


		printf("\n");
	}

	TerminateMoves(&moves);
}
