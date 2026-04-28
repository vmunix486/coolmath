/*
 * pi_stream.c - Growing pi output
 */

#include <stdio.h>

#define MAX_DIGITS 1000

struct spigot {
    int a[(MAX_DIGITS * 10) / 3 + 1];
    int len;
    int nines;
    int predigit;
};

/* Output buffer */
char outbuf[MAX_DIGITS + 10];
int outpos = 0;

/* Instead of printing, we store characters */
void emit_char(char c)
{
    if (outpos < MAX_DIGITS + 9) {
        outbuf[outpos++] = c;
        outbuf[outpos] = '\0';
    }
}

/* Replace putchar with emit_char */
#define putchar emit_char

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

/* crude delay */
void delay(void)
{
    volatile long i;
    for (i = 0; i < 20000; i++);
}

int main(void)
{
    struct spigot s;
    int i;

    printf("Growing pi output:\n\n");

    spigot_init(&s, MAX_DIGITS);

    /* First digit manually */
    outbuf[0] = '3';
    outbuf[1] = '\0';
    outpos = 1;

    printf("%s\n", outbuf);

    /* Add decimal point */
    emit_char('.');
    printf("%s\n", outbuf);

    /* Skip first internal step */
    spigot_next(&s);

    for (i = 0; i < MAX_DIGITS; i++) {
        spigot_next(&s);

        printf("%s\n", outbuf);
        delay();
    }

    spigot_flush(&s);

    return 0;
}
