struct Moves
{
	long *PawnMoves[3][64];
	long *PawnCaptures[3][64];
	long *KnightMoves[64];
	long **BishopMoves[64];
	long **RookMoves[64];	
};

int Rank(int squareNumber);
int File(int squareNumber);
int SquareNumber(int rank, int file);
void SquareAddress(int squareNumber, char * address);
void InitializeMoves(struct Moves *move_pointer);
void TerminateMoves(struct Moves *move_pointer);
