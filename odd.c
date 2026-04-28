// odd.c - Lists off odd numbers

#include <stdio.h>

int main(void)
{
	unsigned int n = 1;
	while (1) {
		printf("%u\n", n);
		n += 2;
	}
	return 0;
}
