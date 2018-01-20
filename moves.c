#include <stdlib.h>

long *whitePawnMoves[64];
long *whitePawnCaptures[64];
long *blackPawnMoves[64];
long *blackPawnCaptures[64];
long *knightMoves[64];
long **bishopMoves[64];
long **rookMoves[64];

int Rank(int squareNumber)
{
	return squareNumber / 8;
}

int File(int squareNumber)
{
	return squareNumber % 8;
}

int SquareNumber(int rank, int file)
{
	return rank * 8 + file;
}

void SquareAddress(int squareNumber, char *address)
{
	address[0] = (char)(File(squareNumber) + 97);
	address[1] = (char)(Rank(squareNumber) + 49);
}

void InitializePawnMoves()
{
	int file;
	int rank;
	long *movePointer;

	/*No legal moves for pawns on the first and eighth rank. */
	for(int squareNumber = 0; squareNumber < 8; squareNumber++)
	{
		whitePawnMoves[squareNumber] = (long *)malloc(sizeof(long));
		whitePawnMoves[squareNumber + 56] = (long *)malloc(sizeof(long));

		blackPawnMoves[squareNumber] = (long *)malloc(sizeof(long));
		blackPawnMoves[squareNumber + 56] = (long *)malloc(sizeof(long));
		
		*whitePawnMoves[squareNumber] = 0;
		*whitePawnMoves[squareNumber + 56] = 0;

		*blackPawnMoves[squareNumber] = 0;
		*blackPawnMoves[squareNumber + 56] = 0;
	}

	/*Two moves for pawns on the second rank. */
	for(int squareNumber = 8; squareNumber < 16; squareNumber++)
	{
		whitePawnMoves[squareNumber] = (long *)malloc(3 * sizeof(long));	
		blackPawnMoves[squareNumber + 40] = (long *)malloc(3 * sizeof(long));	

		movePointer = whitePawnMoves[squareNumber];
		*movePointer = SquareNumber(2, file);
		
		movePointer++;
		*movePointer = SquareNumber(3, file);

		movePointer++;
		*movePointer = 0;

		movePointer = blackPawnMoves[squareNumber + 40];
		*movePointer = SquareNumber(5, file);

		movePointer++;
		*movePointer = SquareNumber(4, file);

		movePointer++;
		*movePointer = 0;
	}

	/*One move for the remaining squares */
	for(int squareNumber = 8; squareNumber < 56; squareNumber++)
	{
		file = File(squareNumber);
		rank = Rank(squareNumber);

		if(rank > 1)
		{
			whitePawnMoves[squareNumber] = (long *)malloc(sizeof(long));	

			movePointer = whitePawnMoves[squareNumber];
			*movePointer = SquareNumber(rank + 1, file);

			movePointer++;
			*movePointer = 0;
		}

		if (rank < 6)
		{
			blackPawnMoves[squareNumber] = (long *)malloc(sizeof(long));	

			movePointer = blackPawnMoves[squareNumber];
			*movePointer = SquareNumber(rank - 1, file);

			movePointer++;
			*movePointer = 0;
		}
	}


}

void InitializePawnCaptures()
{
	int rank;
	int file;

	/*No legal pawn captures from the first and eight ranks */
	for(int squareNumber = 0; squareNumber < 8; squareNumber++)
	{
		whitePawnCaptures[squareNumber] = malloc(sizeof(long));
		blackPawnCaptures[squareNumber] = malloc(sizeof(long));

		*whitePawnCaptures[squareNumber] = 0;
		*blackPawnCaptures[squareNumber] = 0;


		whitePawnCaptures[squareNumber + 56] = malloc(sizeof(long));
		blackPawnCaptures[squareNumber + 56] = malloc(sizeof(long));

		*whitePawnCaptures[squareNumber + 56] = 0;
		*blackPawnCaptures[squareNumber + 56] = 0;
	}

	for(int squareNumber = 8; squareNumber < 56; squareNumber++)	
	{
		if (file == 0 || file == 8)
		{	/*Pawns on the edge have only one capture move */
			whitePawnCaptures[squareNumber] = (long *)malloc(2 * sizeof (long));
			blackPawnCaptures[squareNumber] = (long *)malloc(2 * sizeof (long));
		}
		else
		{	/*All other pawns have two capture moves */
			whitePawnCaptures[squareNumber] = (long *)malloc(3 * sizeof (long));
			blackPawnCaptures[squareNumber] = (long *)malloc(3 * sizeof (long));
		}


		long *whiteCapturePointer = whitePawnCaptures[squareNumber];
		long *blackCapturePointer = blackPawnCaptures[squareNumber];

		rank = Rank(squareNumber);
		file = File(squareNumber);

		if(file == 0)
		{
			*whiteCapturePointer = SquareNumber(rank + 1, file + 1);
			*blackCapturePointer = SquareNumber(rank - 1, file + 1);
		}
		else if (file == 7)
		{
			*whiteCapturePointer = SquareNumber(rank + 1, file - 1);
			*blackCapturePointer = SquareNumber(rank - 1, file - 1);
		}
		else
		{
			*whiteCapturePointer = SquareNumber(rank + 1, file + 1);

			whiteCapturePointer++;
			*whiteCapturePointer = SquareNumber(rank + 1, file - 1);

			*blackCapturePointer = SquareNumber(rank - 1, file + 1);

			blackCapturePointer++;
			*blackCapturePointer = SquareNumber(rank - 1, file - 1);
		}

		whiteCapturePointer++;
		*whiteCapturePointer = 0;

		blackCapturePointer++;
		*blackCapturePointer = 0;
	}
}

void InitializeMoves()
{
	InitializePawnMoves();
	InitializePawnCaptures();
}

void TerminateMoves()
{
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		free(whitePawnMoves[squareNumber]);	
		free(blackPawnMoves[squareNumber]);	

		free(whitePawnCaptures[squareNumber]);
		free(blackPawnCaptures[squareNumber]);
	}

}
