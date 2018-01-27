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

	InitializeMoves();
	printf("Moves Initialized!\n");
	
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

			while(*movePointer > 0)
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

			while(*movePointer > 0)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			printf("\n");
	}

	printf("White Pawn Captures\n");
		
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
			SquareAddress(squareNumber, address);
			printf("\t%s: ", address);

			movePointer = whitePawnCaptures[squareNumber];	

			while(*movePointer > 0)
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

			while(*movePointer > 0)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			printf("\n");
	}

	printf("\n\n");
	printf("Knight Moves\n");

	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
			SquareAddress(squareNumber, address);
			printf("\t%s: ", address);

			movePointer = knightMoves[squareNumber];	

			while(*movePointer > -1)
			{
				SquareAddress(*movePointer, address);
				printf("%s ", address);

				movePointer++;
			}

			printf("\n");
	}

	*/

	/*
	printf("\n\n");
	printf("Rook Moves\n");

	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
			long **pointerToMovePointer = rookMoves[squareNumber];

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
*/

	printf("\n\n");
	printf("Bishop Moves\n");

	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
			long **pointerToMovePointer = bishopMoves[squareNumber];

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

	TerminateMoves();
}
