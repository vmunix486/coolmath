/* pibench.c - Benchmarking program with pi 
 *
 * Has two modes: an incremental benchmark and a 1-digit-at-a-time mode
 *
 * Written in C89, and does not have floating point, long long, or dynamic allocation 
 */

#include <stdio.h>
#include <time.h>

/* Adjust number depending on memory allocation */
#define MAX_DIGITS 2000

/* Spigot state */
struct spigot {
  int a[(MAX_DIGITS * 10) / 3 + 1];
  int len;
  int nines;
  int predigit;
};

/* Start the spigot */
void spigot_init(struct spigot *s, int digits)
{
  int i;
  s->len = (digits * 10) / 3;
  for (i = 0; i < s->len; i++)
    s->a[i] = 2;
  s->nines = 0;
  s->predigit = 0;
}

/* Generate the next digit of pi */
int spigot_next(struct spigot *s)
{
  int i;
  int carry = 0;
  for (i = s->len - 1; i >= 0; i--) {
      int x = s->a[i] * 10 + carry;
      s->a[i] = x % (2 * i + 1);
      carry = (x / (2 * i + 1)) * i;
  }

  /* Extract the digit */
  int q = carry / 10;

  /* Handle carry and logic for those nasty nines */
  if (q == 9) {
    s->nines++;
  } else if (q == 10) {
    int out = s->predigit + 1;

    /* print predigits plus one */
    putchar('0' + out);

    /* print all the sad, lonely, buffered zeros */
    for (; s->nines > 0; s->nines--)
      putchar('0');

    s->predigit = 0;
  } else {
  /* print the previous digit */
  putchar('0' + s->predigit);

  /* print all the poor, little, buffered nines */
  for (; s->nines > 0; s->nines--)
    putchar('9');

  s->predigit = q;
  }
return 0;
}

/* Flush the final digit */
void spigot_flush(struct spigot *s)
{
  putchar('0' + s->predigit);
}

/* -------------------------------------- */
/* Mode 1: Incremental benchmark */
/* -------------------------------------- */

void run_incremental(void)
{
  int steps[] = {10, 50, 100, 500, 1000};
  int num_steps = sizeof(steps) / sizeof(steps[0]);
  int i, j;

  printf("Incremental benchmark:\n\n");

  for (i = 0; i < num_steps, i++) {
    int digits = steps[i];
    struct spigot s;

    clock_t start, end;

    printf("Computing %d digits...\n", digits);

    spigot_init(&s, digits);

    start = clock();

    for (j = 0; j < digits; j++)
      spigot_next(&s);

    spigot_flush(&s);

    end = clock();

    printf("\nTime: %ld ticks", (long)(end - start));

#ifndef CLOCKS_PER_SEC
  printf(" (%.2f sec)", (double)(end - start) / CLOCKS_PER_SEC);
#endif

  printf("\n\n");
  }
}

/* -------------------------------------- */
/* Mode 2: Streaming mode */
/* -------------------------------------- */

void delay(void)
{
  /* crude portable delay */
  volatile long i;
  for (i = 0; i < 20000; i++);
}

void run_streaming(void)
{
  struct spigot s;
  int i;

  printf("Streaming digits of pi:\n\n");

  spigot_init(&s, MAX_DIGITS);

  for (i = 0; i < MAX_DIGITS; i++) {
    spigot_next(&s);
    delay(); /* So it doesn't instantly do 1 quadtrodecillion digits in 1 second */
  }

  spigot_flush(&s);

  printf("\n\nDone.\n");
}

/* -------------------------------------- */
/* Main */
/* -------------------------------------- */

int main(int argc, char *argv[])
{
  if (argc > 1 && argv[1][0] == 's') {
    run_streaming();
  } else {
    run_incremental();
  }

  return 0;
}
