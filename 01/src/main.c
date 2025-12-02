#include <nori.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DIAL_INITIAL 50
#define DIAL_NOTCHES 100
#define BUFSIZE 64

int32 dial_turn(int32 *pos, char dir, int32 dist);

int main(void)
{
    FILE *f = fopen("input", "r");
    char *buf;
    char dir;
    int32 amt;
    int32 prev_ans = 0;
    int32 ans = 0;
    int32 pos = DIAL_INITIAL;

    buf = malloc(BUFSIZE);

    while (fgets(buf, BUFSIZE, f)) {
        printf("pos: %d\t", pos);

        // logic
        sscanf(buf, "%c%d", &dir, &amt);
        ans += dial_turn(&pos, dir, amt);
        assert(0 <= pos && pos < 100);

        // fancy printing
        printf("dir: %c\tamt: %d\tnow: %d",
               dir, amt, pos);        
        if (ans - prev_ans > 0)
            printf("\t+%d!", ans - prev_ans);
        printf("\n");
        prev_ans = ans;
    }

    printf("ans: %d\n", ans);

    free(buf);
    fclose(f);
}

int32 dial_turn(int32 *pos, char dir, int32 dist)
{
    int32 ans = 0;
    int32 new_pos = *pos;
    assert(dir == 'L' || dir == 'R');
    if (dist > DIAL_NOTCHES) {
        ans += dist / DIAL_NOTCHES;
        dist = dist % DIAL_NOTCHES;
    }
    if (dir == 'L') dist = -dist;

    new_pos += dist;
    if (new_pos < 0) {
        new_pos += DIAL_NOTCHES;
        if (*pos != 0) ans++;
    } else if (new_pos == 0 && *pos != 0) {
        // that is, if pos is newly 0
        ans++;
    } else if (new_pos > DIAL_NOTCHES - 1) {
        new_pos += -DIAL_NOTCHES;
        ans++;
    }

    *pos = new_pos;
    return ans;
}
