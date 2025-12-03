// Stub

#include <nori.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 128
#define MAX_BATS 2

uint32 index_greatest_from(const char *s, uint32 pos, uint32 len);
uint32 char_to_digit(char c);
uint32 u32pow(uint32 b, uint32 n);

int main(void)
{
    uint32 i;
    FILE *f;
    char *buffer;
    uint32 bats[MAX_BATS]; //little-endian
    uint32 total_joltage = 0;

    f = fopen("input", "r");
    buffer = malloc(BUFSIZE);

    while(!feof(f)) {
        fgets(buffer, BUFSIZE, f);
        
        bats[1] = index_greatest_from(buffer, 0, (uint32) strlen(buffer) - 2);
        bats[0] = index_greatest_from(buffer, bats[1] + 1, (uint32) strlen(buffer) - bats[1]);

        printf("Chose batteries %u and %u for a joltage of %c%c\n", bats[1], bats[0], buffer[bats[1]], buffer[bats[0]]);
        printf("%s", buffer);
        printf("%*s^%*s^\n\n", bats[1], "", bats[0] - bats[1] - 1, "");
        
        for(i = 0; i < MAX_BATS; i++) {
            total_joltage += char_to_digit(buffer[bats[i]]) * u32pow(10, i);
        }
    }
    printf("Total joltage %u\n", total_joltage);

    free(buffer);
    fclose(f);
}

uint32 index_greatest_from(const char *s, uint32 pos, uint32 len)
{
    uint32 i;
    uint32 i_ans = pos;

    for (i = pos; i < pos + len; i++) {
        if (s[i] > s[i_ans]) i_ans = i;
    }
    
    return i_ans;
}

uint32 char_to_digit(char c)
{
    if (c < '0' || '9' < c) return (uint32) -1;
    return (uint32) c - '0';
}

uint32 u32pow(uint32 b, uint32 n)
{
    uint32 ans = b;
    if (n == 0) return 1;
    while (n > 1) {
        ans *= b;
        n--;
    }
    return ans;
}
