// even.c - Lists off even numbers

#include <stdio.h>

int main(void)
{
	unsigned int n = 0;
	while (1) {
		printf("%u\n", n);
		n += 2;
	}
	return 0;
}
