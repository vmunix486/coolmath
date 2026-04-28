/*
 * pibench.c - Incremental benchmark for pi digits in C89
 */

#include <stdio.h>
#include <time.h>

#define MAX_DIGITS 2000

struct spigot {
    int a[(MAX_DIGITS * 10) / 3 + 1];
    int len;
    int nines;
    int predigit;
};

void spigot_init(struct spigot *s, int digits)
{
    int i;
    s->len = (digits * 10) / 3;

    for (i = 0; i < s->len; i++)
        s->a[i] = 2;

    s->nines = 0;
    s->predigit = 0;
}

void spigot_next(struct spigot *s)
{
    int i, carry = 0;

    for (i = s->len - 1; i >= 0; i--) {
        int x = s->a[i] * 10 + carry;
        s->a[i] = x % (2 * i + 1);
        carry = (x / (2 * i + 1)) * i;
    }

    {
        int q = carry / 10;

        if (q == 9) {
            s->nines++;
        } else if (q == 10) {
            putchar('0' + (s->predigit + 1));
            for (; s->nines > 0; s->nines--)
                putchar('0');
            s->predigit = 0;
        } else {
            putchar('0' + s->predigit);
            for (; s->nines > 0; s->nines--)
                putchar('9');
            s->predigit = q;
        }
    }
}

void spigot_flush(struct spigot *s)
{
    putchar('0' + s->predigit);
}

void run_test(int digits)
{
    struct spigot s;
    int i;

    clock_t start, end;

    printf("Computing %d digits...\n", digits);

    spigot_init(&s, digits);

    start = clock();

    for (i = 0; i < digits; i++)
        spigot_next(&s);

    spigot_flush(&s);

    end = clock();

    printf("\nTime: %ld ticks", (long)(end - start));

#ifdef CLOCKS_PER_SEC
    printf(" (%.2f sec)", (double)(end - start) / CLOCKS_PER_SEC);
#endif

    printf("\n\n");
}

int main(void)
{
    int tests[] = {10, 50, 100, 500, 1000};
    int i;

    printf("Pi benchmark (C89 spigot)\n\n");

    for (i = 0; i < sizeof(tests)/sizeof(tests[0]); i++)
        run_test(tests[i]);

    return 0;
}
