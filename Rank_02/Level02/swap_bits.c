#include <stdio.h>

unsigned char swap_bits(unsigned char octet)
{
	unsigned char upper = octet / 16;
	unsigned char lower = octet % 16;

	return (lower * 16 + upper);
}

int main()
{
	unsigned char num = 254;

	num = swap_bits(num);
	printf("%d", num);
	return (0);
}
