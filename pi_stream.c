/*
 * pi_stream.c - Streaming pi digits in C89
 */

#include <stdio.h>

#define MAX_DIGITS 2000

struct spigot {
    int a[(MAX_DIGITS * 10) / 3 + 1];
    int len;
    int nines;
    int predigit;
};

void spigot_init(struct spigot *s)
{
    int i;

    s->len = (MAX_DIGITS * 10) / 3;

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

/* crude portable delay */
void delay(void)
{
    volatile long i;
    for (i = 0; i < 20000; i++);
}

int main(void)
{
    struct spigot s;
    int i;

    printf("Streaming pi digits:\n\n");

    spigot_init(&s);

    for (i = 0; i < MAX_DIGITS; i++) {
        spigot_next(&s);
        delay(); /* handicap; remove for full speed */
    }

    spigot_flush(&s);

    printf("\n\nDone.\n");

    return 0;
}
