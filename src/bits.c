long bit[64];

void InitializeBits()
{
	bit[0] = 1;

	for(int i = 1; i < 64; i++)
	{
		bit[i] = bit[i - 1] * 2;
	}
}

