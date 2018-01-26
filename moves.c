#include <stdlib.h>
/* #include <stdio.h> */

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
		*movePointer = -1;

		movePointer = blackPawnMoves[squareNumber + 40];
		*movePointer = SquareNumber(5, file);

		movePointer++;
		*movePointer = SquareNumber(4, file);

		movePointer++;
		*movePointer = -1;
	}

	/* One move for the remaining squares */
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
			*movePointer = -1;
		}

		if (rank < 6)
		{
			blackPawnMoves[squareNumber] = (long *)malloc(sizeof(long));	

			movePointer = blackPawnMoves[squareNumber];
			*movePointer = SquareNumber(rank - 1, file);

			movePointer++;
			*movePointer = -1;
		}
	}


}

void InitializePawnCaptures()
{
	int rank;
	int file;

	/* No legal pawn captures from the first and eight ranks */
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
		{	/* Pawns on the edge have only one capture move */
			whitePawnCaptures[squareNumber] = (long *)malloc(2 * sizeof (long));
			blackPawnCaptures[squareNumber] = (long *)malloc(2 * sizeof (long));
		}
		else
		{	/* All other pawns have two capture moves */
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

void InitializeKnightMoves()
{
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)	
	{
		int rankEdgeDistance = Rank(squareNumber);
		int fileEdgeDistance;

		int knightMoveCount = 0;

		int currentRank = Rank(squareNumber);
		int currentFile = File(squareNumber);

		/* The number of knight moves depends on how far from the
		 * board edges the knight is.  Find the minimum distance 
		 * from both edges.  If the distance is more than 2 
		 * squares from an edge, then use 2.  Add the distances
		 * from the two edges.  The number of knight moves is
		 * then found from this table:
		 *
		 * 	Sum of two distances		Knight move count
		 * 			0							2
		 * 			1							3
		 * 			2							4
		 * 			3							6
		 * 			4							8
		 *
		 * 	I figured this our for myself.  Confirm it for 
		 * 	yourself if you don't believe it.
		 */

		if(currentRank == 0 || currentRank == 7)
		{
			rankEdgeDistance = 0;
		}
		else if (currentRank == 1 || currentRank == 6)
		{
			rankEdgeDistance = 1;
		}
		else
		{
			rankEdgeDistance = 2;
		}

		if(currentFile == 0 || currentFile == 7)
		{
			fileEdgeDistance = 0;
		}
		else if (currentFile == 1 || currentFile == 6)
		{
			fileEdgeDistance = 1;
		}
		else
		{
			fileEdgeDistance = 2;
		}

		int total = rankEdgeDistance + fileEdgeDistance;

		switch(total)
		{
			case 0:
				knightMoveCount = 2;
				break;

			case 1:
				knightMoveCount = 3;
				break;	

			case 2:
				knightMoveCount = 4;
				break;

			case 3:
				knightMoveCount = 6;
				break;

			case 4:
				knightMoveCount = 8;
				break;
		}

		knightMoves[squareNumber] = (long *)malloc((knightMoveCount + 1) * sizeof(long));
		
		long *movePointer = knightMoves[squareNumber];

		for(int rankChange = -2; rankChange < 3; rankChange++)
		{
			int nextRank = currentRank + rankChange;

			if(nextRank > - 1 && nextRank < 8 && rankChange != 0)
			{
				int fileChange;

				if(rankChange == 1 || rankChange == -1)
				{
					fileChange = 2;
				}
				else
				{
					fileChange = 1;
				}

				int multiplier = -1;

				while(multiplier < 2)
				{
					int nextFile;

					nextFile = currentFile + multiplier * fileChange;
				
					if (nextFile > -1 && nextFile < 8)
					{
						*movePointer = SquareNumber(nextRank, nextFile);
						*movePointer++;
					}

					multiplier += 2;
				}
			}
		}

		*movePointer = -1;

	}
}

void InitializeRookMoves()
{
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		int currentRank = Rank(squareNumber);
		int currentFile = File(squareNumber);

		long *movePointer;
		long **pointerToMovePointer;

		/* Keep track of the number of directions a rook can move from a square. This determines
		 * the number of move pointers are necessary for each square.  Start with 4 and
		 * subtract the number of edges the square is on.
		 */
		int directionCount = 4;

		if(currentRank == 0 || currentRank == 7)
		{
			directionCount--;
		}

		if(currentFile == 0 || currentFile == 7)
		{
			directionCount--;
		}

		rookMoves[squareNumber] = (long **)malloc((directionCount + 1) * sizeof(long *));
		pointerToMovePointer = rookMoves[squareNumber];

		int edgeDistance;

		
		/* Moves to white's right */

		if(currentFile < 7)
		{
			edgeDistance = 7 - currentFile;

			*pointerToMovePointer = (long *)malloc((edgeDistance + 1) * sizeof(long));
			movePointer = *pointerToMovePointer;

			for(int nextFile = currentFile + 1; nextFile < 8; nextFile++)
			{
				*movePointer = SquareNumber(currentRank, nextFile);
				movePointer++;	
			}

			*movePointer = -1;

			*pointerToMovePointer++;

		}


		/* Moves to white's left */

		if(currentFile > 0)
		{
			edgeDistance = currentFile;

			*pointerToMovePointer = (long *)malloc((edgeDistance + 1) * sizeof(long));
			movePointer = *pointerToMovePointer;

			for(int nextFile = currentFile - 1; nextFile > -1; nextFile--)
			{
				*movePointer = SquareNumber(currentRank, nextFile);
				movePointer++;	
			}

			*movePointer = -1;

			*pointerToMovePointer++;

		}


		/* Moves to black's side of the board */

		if(currentRank < 7)
		{
			edgeDistance = 7 - currentRank;

			*pointerToMovePointer = (long *)malloc((edgeDistance + 1) * sizeof(long));
			movePointer = *pointerToMovePointer;

			for(int nextRank = currentRank + 1; nextRank < 8; nextRank++)
			{
				*movePointer = SquareNumber(nextRank, currentFile);
				movePointer++;	
			}

			*movePointer = -1;

			*pointerToMovePointer++;

		}

		/* Moves to white's side of the board */

		if(currentRank > 0)
		{
			edgeDistance = currentRank;

			*pointerToMovePointer = (long *)malloc((edgeDistance + 1) * sizeof(long));
			movePointer = *pointerToMovePointer;

			for(int nextRank = currentRank - 1; nextRank > -1; nextRank--)
			{
				*movePointer = SquareNumber(nextRank, currentFile);
				movePointer++;	
			}

			*movePointer = -1;

			*pointerToMovePointer++;

		}
		*pointerToMovePointer = 0;
	}
}


void InitializeMoves()
{
/*	InitializePawnMoves();
	InitializePawnCaptures();
	InitializeKnightMoves();
*/
	InitializeRookMoves();
}

void TerminateMoves()
{
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
/*		free(whitePawnMoves[squareNumber]);	
		free(blackPawnMoves[squareNumber]);	

		free(whitePawnCaptures[squareNumber]);
		free(blackPawnCaptures[squareNumber]);
		free(knightMoves[squareNumber]);
*/		
		long **pointerToMovePointer = rookMoves[squareNumber];
		
		while(*pointerToMovePointer)
		{
			free(*pointerToMovePointer);
			*pointerToMovePointer++;
		}

		free(rookMoves[squareNumber]);
	}
}
