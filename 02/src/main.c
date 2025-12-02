#include <nori.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 128
#define RANGE_SEP ','
#define ID_SEP '-'

uint64 ulog10(uint64 n);
uint64 upow(uint64 b, uint64 n);
uint64 count_invalid(uint64 lo, uint64 hi);

int main(void)
{
    FILE *f;
    char *buf;
    char c;
    uint32 i;
    uint64 id_lo = 0, id_hi = 0;
    uint64 ans = 0;

    buf = malloc(BUFFER_SIZE);
    f = fopen("input", "r");
    while (!feof(f)) {
        for (i = 0; i < BUFFER_SIZE; i++) {
            c = (char) fgetc(f);
            if (feof(f)) break;
            if (c == RANGE_SEP) break;
            buf[i] = c;
        }
        buf[i < BUFFER_SIZE - 1 ? i : BUFFER_SIZE - 1] = '\0';

        printf("%s\n", buf);
        sscanf(buf, "%lu-%lu", &id_lo, &id_hi);

        printf("\tlo: %lu\n\thi: %lu\n",
                id_lo, id_hi);

        ans += count_invalid(id_lo, id_hi);
        printf("====================\n");
    }

    printf("ans: %lu\n", ans);
}

uint64 count_invalid(uint64 lo, uint64 hi)
{
    uint64 ans = 0;
    uint64 magnitude;
    uint64 l_half, r_half;

    while(lo <= hi) {
        magnitude = ulog10(lo);
        if (magnitude % 2 != 0) {
            lo++;
            continue;
        }
        l_half = lo / upow(10, magnitude / 2);
        r_half = lo % upow(10, magnitude / 2);
        if (l_half == r_half) {
            ans += lo;
            printf("found: %lu\n", lo);
        }
        lo++;
    }

    return ans;
}

uint64 ulog10(uint64 n)
{
    uint64 ans = 0;
    if (n == 0) return 0;
    while (n > 0) {
        n /= 10;
        ans++;
    }
    return ans;
}

uint64 upow(uint64 b, uint64 n)
{
    uint64 ans = b;
    if (n == 0) return 1;
    while (n > 1) {
        ans = ans * b;
        n--;
    }
    return ans;

}
