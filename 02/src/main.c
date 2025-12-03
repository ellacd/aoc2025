#include <nori.h>

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LITTLE_BUFFER_SIZE 32
#define BUFFER_SIZE 128
#define RANGE_SEP ','
#define ID_SEP '-'

uint64 ulog10(uint64 n);
uint64 upow(uint64 b, uint64 n);
uint64 count_invalid(uint64 lo, uint64 hi);
boolean has_pattern(const char *s, const char *pattern);

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

    free(buf);
    fclose(f);
}

uint64 count_invalid(uint64 lo, uint64 hi)
{
    uint32 i;
    uint64 len;
    uint64 ans = 0;
    char s[LITTLE_BUFFER_SIZE];
    char pattern[LITTLE_BUFFER_SIZE];

    while(lo <= hi) {
        len = ulog10(lo);
        snprintf(s, LITTLE_BUFFER_SIZE, "%lu", lo);
        for (i = 1; i <= len / 2; i++) {
            if (len % i != 0) continue;
            strcpy(pattern, s);
            pattern[i] = '\0';
            if (has_pattern(s, pattern)) {
                ans += lo;
                break;
            }
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

boolean has_pattern(const char *s, const char *pattern)
{
    uint32 i;
    uint32 repeats;
    uint32 len_s = (uint32) strlen(s);
    uint32 len_pattern = (uint32) strlen(pattern);
    char substr[LITTLE_BUFFER_SIZE];
    if (len_s % len_pattern != 0) return FALSE;

    repeats = len_s / len_pattern;
    for (i = 0; i < repeats; i++) {
        strcpy(substr, s + i * len_pattern);
        substr[len_pattern] = '\0';
        if(strstr(substr, pattern) == NULL) return FALSE;
    }
    printf("s: %s\n\thas pattern: %s\n", s, pattern);
    return TRUE;
}
