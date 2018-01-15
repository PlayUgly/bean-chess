long **whitePawnMoves[64];
long **blackPawnMoves[64];
long **knightMoves[64];
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

