/* pi.c - simple pi generator (C89)
 *
 * Syntax: ./pi (Number) | Number is any number greater than 0.
 *
 * NOTE: If you put a really high amount of digits, it can cause the program to lock up or run out of memory on something like ELKS. */
 

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int digits = 50; /* default */

    if (argc > 1) {
        digits = atoi(argv[1]);
        if (digits <= 0) {
            printf("Invalid digit count\n");
            return 1;
        }
    }

    int len = (digits * 10) / 3 + 1;
    int *a = (int *)malloc(len * sizeof(int));
    int i, j, q, x;
    int nines = 0;
    int predigit = 0;

    if (!a) {
        printf("Out of memory\n");
        return 1;
    }

    /* initialize array */
    for (i = 0; i < len; i++)
        a[i] = 2;

    for (j = 0; j < digits; j++) {
        q = 0;

        for (i = len - 1; i >= 0; i--) {
            x = 10 * a[i] + q * (i + 1);
            a[i] = x % (2 * (i + 1) - 1);
            q = x / (2 * (i + 1) - 1);
        }

        a[0] = q % 10;
        q = q / 10;

        /* output handling */
        if (q == 9) {
            nines++;
        } else if (q == 10) {
            printf("%d", predigit + 1);
            for (i = 0; i < nines; i++)
                printf("0");
            predigit = 0;
            nines = 0;
        } else {
            if (j > 0) {
             printf("%d", predigit);
            }
            predigit = q;
            if (nines != 0) {
                for (i = 0; i < nines; i++)
                    printf("9");
                nines = 0;
            }
        }

        /* print decimal point after first digit */
        if (j == 1)
            printf(".");
    }

    printf("%d\n", predigit);

    free(a);
    return 0;
}
