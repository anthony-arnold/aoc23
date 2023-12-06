#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdint.h>

#ifndef PART
#define PART 1
#endif

#if PART == 2
uint64_t read_big() {
    uint64_t b = 0;
    int i;
    while(scanf("%d", &i) == 1) {
        b *= (uint64_t)powf(10, floor(log10((double)i) + 1));
        b += i;
    }
    return b;
}
#endif

int main() {
    uint64_t times[8], distances[8];
    int i = 0;
    int n;
    uint64_t p = 1;


    scanf("Time:");
#if PART == 1
    while(scanf("%lu", &times[i++]) == 1);
#else
    times[0] = read_big();
#endif

    scanf("Distance:");
#if PART == 1
    i = 0;
    while(scanf("%lu", &distances[i++]) == 1);
    n = i - 1;
#else
    distances[0] = read_big();
    n = 1;
#endif

    for (i = 0; i < n; i++) {
        int x = 0;
        for(uint64_t j = 1; j < times[i]; j++) {
            if (j*times[i] - j*j > distances[i]) {
                x = times[i] - 2 * j + 1;
                break;
            }
        }
        assert(x > 0);

        p *= x;
    }

    printf("%lu\n", p);
}
