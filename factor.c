// factor - Factors of the given number

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	unsigned int n;
	unsigned int i;
	if (argc != 2) {
		printf("Usage: %s <number>\n", argv[0]);
		return 1;
	}

	n = (unsigned int)atoi(argv[1]);

	if (n == 0) {
		printf("kaboom.\n");
		return 1;
	}

	for (i = 1; i <= n / i; i++) {
		if (n % i == 0) {
			printf("%u\t%u\n", i, n / i);
			}
	}
	return 0;
}
