#include <stdlib.h>
/*#include <stdio.h>*/
#include "moves.h"

/* Squares are numbered 0 through 63 starting with square a1 
 * incrementing from file a to file h, and then wrapping
 * back to file a on the next highest rank.  h8 is square 63.
 */

/* Returns the rank number given a square number. */
int Rank(int squareNumber)
{
	return squareNumber / 8;
}

/* Returns the file number given a square number. */
int File(int squareNumber)
{
	return squareNumber % 8;
}

/* Returns a square number given rank and file numbers. */
int SquareNumber(int rank, int file)
{
	return rank * 8 + file;
}

/* Assigns a square address in algebraic notation to a
 * given string buffer for a given square number.
 * The buffer must hold two characters. */
void SquareAddress(int squareNumber, char *address)
{
	address[0] = (char)(File(squareNumber) + 97);
	address[1] = (char)(Rank(squareNumber) + 49);
}

/* Initializes black and white pawn moves in two different
 * two-dimensional arrays.  The first dimension of each array
 * must have at least 64 elements, one for each square on the
 * board.  The second dimension is dynamically sized to either
 * 1, 2, or 3 elements depending on which rank the square is. */
void InitializePawnMoves(long **whitePawnMoves, long **blackPawnMoves)
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
		file = File(squareNumber);

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
			whitePawnMoves[squareNumber] = (long *)malloc(2 * sizeof(long));	

			movePointer = whitePawnMoves[squareNumber];
			*movePointer = SquareNumber(rank + 1, file);

			movePointer++;
			*movePointer = -1;
		}

		if (rank < 6)
		{
			blackPawnMoves[squareNumber] = (long *)malloc(2 * sizeof(long));	

			movePointer = blackPawnMoves[squareNumber];
			*movePointer = SquareNumber(rank - 1, file);

			movePointer++;
			*movePointer = -1;
		}
	}


}



void InitializePawnCaptures(long **whitePawnCaptures, long **blackPawnCaptures)
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

void InitializeKnightMoves(long **knightMoves)
{
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)	
	{
		int rankEdgeDistance = Rank(squareNumber);
		int fileEdgeDistance;

		int knightMoveCount = 0;

		int currentRank = Rank(squareNumber);
		int currentFile = File(squareNumber);

		/* The number of knight moves depends on how far from the
		 * board edges the knight is.  Find the distance to the
		 * two nearest edges. If the distance is more than 2 
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

void InitializeRookMoves(long ***rookMoves)
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

		
		/* Moves to king's side */

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


		/* Moves to queen side */

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


void InitializeBishopMoves(long ***bishopMoves)
{
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		int currentRank = Rank(squareNumber);
		int currentFile = File(squareNumber);

		long *movePointer;
		long **pointerToMovePointer;

		/* Keep track of the number of directions a bishop can move from a square. This determines
		 * the number of move pointers are necessary for each square.  If the bishop is on only 
		 * one side, then it has two direction to move.  If it's in a corner it has only one
		 * direction to move.  Any place else and it has four directions to move.
		 */

		int directionCount = 4;

		if(currentRank == 0 || currentRank == 7)
		{
			directionCount = 2;
		}

		if(currentFile == 0 || currentFile == 7)
		{
			if(directionCount == 4)
			{
				directionCount = 2;
			}
			else
			{
				directionCount = 1;
			}
		}

		bishopMoves[squareNumber] = (long **)malloc((directionCount + 1) * sizeof(long *));
		pointerToMovePointer = bishopMoves[squareNumber];

		int rankEdgeDistance; 
		int fileEdgeDistance;
		int edgeDistance;

		
		/* Moves to black king-side corner */

		rankEdgeDistance = 7 - currentRank;
		fileEdgeDistance = 7 - currentFile;

		if(rankEdgeDistance < fileEdgeDistance)
		{
			edgeDistance = rankEdgeDistance;
		}
		else
		{
			edgeDistance = fileEdgeDistance;
		}

		if(edgeDistance)
		{
			*pointerToMovePointer = (long *)malloc((edgeDistance + 1) * sizeof(long));
			movePointer = *pointerToMovePointer;

			for(int moveCount = 1; moveCount <= edgeDistance; moveCount++)
			{
				*movePointer = SquareNumber(currentRank + moveCount, currentFile + moveCount);
				movePointer++;	
			}

			*movePointer = -1;

			*pointerToMovePointer++;
		}


		/* Moves to black queen-side corner */

		rankEdgeDistance = 7 - currentRank;
		fileEdgeDistance = currentFile;

		if(rankEdgeDistance < fileEdgeDistance)
		{
			edgeDistance = rankEdgeDistance;
		}
		else
		{
			edgeDistance = fileEdgeDistance;
		}

		if(edgeDistance)
		{
			*pointerToMovePointer = (long *)malloc((edgeDistance + 1) * sizeof(long));
			movePointer = *pointerToMovePointer;

			for(int moveCount = 1; moveCount <= edgeDistance; moveCount++)
			{
				*movePointer = SquareNumber(currentRank + moveCount, currentFile - moveCount);
				movePointer++;	
			}

			*movePointer = -1;

			*pointerToMovePointer++;
		}


		/* Moves to white king-side corner */

		rankEdgeDistance = currentRank;
		fileEdgeDistance = 7 - currentFile;

		if(rankEdgeDistance < fileEdgeDistance)
		{
			edgeDistance = rankEdgeDistance;
		}
		else
		{
			edgeDistance = fileEdgeDistance;
		}

		if(edgeDistance)
		{
			*pointerToMovePointer = (long *)malloc((edgeDistance + 1) * sizeof(long));
			movePointer = *pointerToMovePointer;

			for(int moveCount = 1; moveCount <= edgeDistance; moveCount++)
			{
				*movePointer = SquareNumber(currentRank - moveCount, currentFile + moveCount);
				movePointer++;	
			}

			*movePointer = -1;

			*pointerToMovePointer++;
		}


		/* Moves to white queen-side corner */

		rankEdgeDistance = currentRank;
		fileEdgeDistance = currentFile;

		if(rankEdgeDistance < fileEdgeDistance)
		{
			edgeDistance = rankEdgeDistance;
		}
		else
		{
			edgeDistance = fileEdgeDistance;
		}

		if(edgeDistance)
		{
			*pointerToMovePointer = (long *)malloc((edgeDistance + 1) * sizeof(long));
			movePointer = *pointerToMovePointer;

			for(int moveCount = 1; moveCount <= edgeDistance; moveCount++)
			{
				*movePointer = SquareNumber(currentRank - moveCount, currentFile - moveCount);
				movePointer++;	
			}

			*movePointer = -1;

			*pointerToMovePointer++;
		}

		*pointerToMovePointer = 0;
	}
}


void InitializeMoves(struct Moves *moves_pointer)
{
	InitializePawnMoves(moves_pointer->PawnMoves[2], moves_pointer->PawnMoves[0]);
	InitializePawnCaptures(moves_pointer->PawnCaptures[2], moves_pointer->PawnCaptures[0]);
	InitializeKnightMoves(moves_pointer->KnightMoves);
	InitializeBishopMoves(moves_pointer->BishopMoves);
	InitializeRookMoves(moves_pointer->RookMoves);
}

void TerminateMoves(struct Moves *moves_pointer)
{
	for(int squareNumber = 0; squareNumber < 64; squareNumber++)
	{
		free(moves_pointer->PawnMoves[0][squareNumber]);	
		free(moves_pointer->PawnMoves[2][squareNumber]);	

		free(moves_pointer->PawnCaptures[0][squareNumber]);
		free(moves_pointer->PawnCaptures[2][squareNumber]);


		free(moves_pointer->KnightMoves[squareNumber]);


		long **pointerToMovePointer = moves_pointer->BishopMoves[squareNumber];
		
		while(*pointerToMovePointer)
		{
			free(*pointerToMovePointer);
			*pointerToMovePointer++;
		}

		free(moves_pointer->BishopMoves[squareNumber]);


		pointerToMovePointer = moves_pointer->RookMoves[squareNumber];
		
		while(*pointerToMovePointer)
		{
			free(*pointerToMovePointer);
			*pointerToMovePointer++;
		}

		free(moves_pointer->RookMoves[squareNumber]);
	}
}
