#include <stdio.h>
#include <stdint.h>

#ifndef PART
#define PART 1
#endif

#if PART == 1
#define EXPAND 1
#else
#define EXPAND 999999
#endif

char grid[256][256];
uint64_t gal[512][2];
uint64_t expansion[512][2];
int width;
int height;

int main() {
    int x = 0;
    int y = 0;
    int c;
    int n = 0;
    uint64_t sum = 0;

    while ((c = fgetc(stdin)) != EOF) {
        grid[y][x] = c;
        if (c == '\n') {
            grid[y][x+1] = 0;
            y++;
            x=0;
        }
        else {
            if (c == '#') {
                gal[n][0] = x;
                gal[n][1] = y;
                expansion[n][0] = 0;
                expansion[n][1] = 0;
                n++;
            }
            x++;
            width = x;
        }
    }
    height = y;

    for (uint64_t i = 0; i < (uint64_t)height; i++) {
        int j;
        for (j = 0; j < width; j++) {
            if (grid[i][j] == '#') break;
        }

        if (j == width) {
            for (int k = 0; k < n; k++) {
                if (gal[k][1] > i) {
                    expansion[k][1] += EXPAND;
                }
            }
        }
    }

    for (uint64_t j = 0; j < (uint64_t)width; j++) {
        int i;
        for (i = 0; i < height; i++) {
            if (grid[i][j] == '#') break;
        }

        if (i == height) {
            for (int k = 0; k < n; k++) {
                if (gal[k][0] > j) {
                    expansion[k][0] += EXPAND;
                }
            }
        }
    }

    for (int k = 0; k < n; k++) {
        gal[k][0] += expansion[k][0];
        gal[k][1] += expansion[k][1];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            uint64_t x0 = gal[i][0];
            uint64_t y0 = gal[i][1];
            uint64_t x1 = gal[j][0];
            uint64_t y1 = gal[j][1];

            uint64_t dx = x0 > x1 ? (x0 - x1) : (x1 - x0);
            uint64_t dy = y0 > y1 ? (y0 - y1) : (y1 - y0);
            uint64_t cc = dx + dy;

            sum += cc;
        }
    }
    printf("%lu\n", sum);
}
