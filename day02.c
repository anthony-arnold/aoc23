#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define max(c,d) ((d)>(c)?(d):(c))

enum {
    RED,
    GREEN,
    BLUE
};

const int MAX_COLOUR[] = {
    12, 13, 14
};

int main() {
    int sum = 0;
    uint64_t sumprod = 0;
    int game = 1;
    int d;
    char colour[6] = {0};

    while (!feof(stdin)) {
        int minimum[3] = {0};

        // discard game
        while (fgetc(stdin) != ':');

        int possible = 1;
        while (scanf("%d %[a-z]", &d, colour) == 2) {
            fgetc(stdin); // discard separator
            int c;
            if (strcmp(colour, "red") == 0) c = RED;
            else if (strcmp(colour, "green") == 0) c = GREEN;
            else if (strcmp(colour, "blue") == 0) c = BLUE;
            else abort();

            possible &= d <= MAX_COLOUR[c];
            minimum[c] = max(minimum[c], d);
        }
        if (possible) {
            sum += game;
        }
        sumprod += minimum[0] * minimum[1] * minimum[2];

        game++;
    }

    printf("%d\n", sum);
    printf("%d\n", sumprod);
}
