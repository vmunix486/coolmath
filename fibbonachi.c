// fibbonachi - Fibbonachi Sequence

#include <stdio.h>

int main (void)
{
	unsigned int a = 0;
	unsigned int b = 1;
	unsigned int next;

	while (1) {
		printf("%u\n", a);
		next = a + b;
		a = b;
		b = next;
	}
	return 0;
}
