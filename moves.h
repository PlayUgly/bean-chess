extern long *whitePawnMoves[64];
extern long *whitePawnCaptures[64];
extern long *blackPawnMoves[64];
extern long *blackPawnCaptures[64];
extern long *knightMoves[64];
extern long **bishopMoves[64];
extern long **rookMoves[64];

int Rank(int squareNumber);
int File(int squareNumber);
int SquareNumber(int rank, int file);
void SquareAddress(int squareNumber, char * address);
void InitializeMoves();
void TerminateMoves();
