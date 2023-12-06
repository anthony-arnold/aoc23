#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdint.h>

#ifndef PART
#define PART 2
#endif

int map_range(int64_t seeds[][2], int64_t mapped[][2], int* np) {
    int n = *np;
    int64_t dst, src, len;
    if (scanf("%li %li %li", &dst, &src, &len) != 3) {
        return 0;
    }

    for (int i = 0; i < *np; i++) {
        int64_t off = dst - src;
        if (seeds[i][1] <= src || seeds[i][0] >= src+len) {
            continue;
        }

        // split out the left?
        if (seeds[i][0] < src && seeds[i][1] > src) {
            seeds[n][0] = seeds[i][0];
            seeds[n][1] = src;

            seeds[i][0] = src;
            n++;
        }

        // split out the right?
        if (seeds[i][0] < src+len && seeds[i][1] > src+len) {
            seeds[n][0] = src+len;
            seeds[n][1] = seeds[i][1];

            seeds[i][1] = src+len;
            n++;
        }

        if (seeds[i][0] >= src && seeds[i][1] <= src+len) {
            // out-of-range is already split out, so map the whole range
            mapped[i][0] = seeds[i][0] + off;
            mapped[i][1] = seeds[i][1] + off;
        }
    }
    *np = n;
    return 1;
}

void discard() {
    while (!feof(stdin) && fgetc(stdin) != ':');
}

int main() {
    int64_t min = INT64_MAX;
    int64_t seeds[128][2];
    int64_t mapped[128][2];
    int n = 0;
    discard();

#if PART == 1
    while (scanf("%li", &seeds[n][0]) == 1) {
        seeds[n][1] = seeds[n][0]+1;
        n++;
    }
#else
    while (scanf("%li %li", &seeds[n][0], &seeds[n][1]) == 2) {
        seeds[n][1] += seeds[n][0];
        n++;
    }
#endif
    memset(mapped, 0, sizeof(mapped));

    while (!feof(stdin)) {
        discard();
        while(map_range(seeds, mapped, &n));

        for (int i = 0; i < n; i++) {
            if (mapped[i][0] == 0 && mapped[i][1] == 0) {
                mapped[i][0] = seeds[i][0];
                mapped[i][1] = seeds[i][1];
            }
        }
        memcpy(seeds, mapped, sizeof(mapped));
        memset(mapped, 0, sizeof(mapped));
    }

    for (int i = 0; i < n; i++) {
        min = seeds[i][0] < min ? seeds[i][0] : min;
    }
    printf("%li\n", min);
}
