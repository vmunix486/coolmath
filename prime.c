/* prime.c - endless prime number generator */

#include <stdio.h>

#define MAX_PRIMES 1024  /* adjust for memory vs speed. For more clarification, this is for how many prime numbers to store in RAM. */

static unsigned int primes[MAX_PRIMES];

void delay()
{
    volatile unsigned long i;
    for (i = 0; i < 30000UL; i++); /* tune for speed */
}

int is_prime(unsigned int n, int count)
{
    int i;
    unsigned int p;

    for (i = 0; i < count; i++) {
        p = primes[i];

        if (p * p > n)
            break;

        if (n % p == 0)
            return 0;
    }
    return 1;
}

int main()
{
    unsigned int n = 2;
    int count = 0;

    while (1) {
        if (is_prime(n, count)) {

            /* store prime if we still have room */
            if (count < MAX_PRIMES)
                primes[count++] = n;

            printf("%u\n", n);
            fflush(stdout);
            delay();
        }

        /* skip even numbers after 2 */
        if (n == 2)
            n = 3;
        else
            n += 2;
    }

    return 0;
}
