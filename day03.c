#include <stdio.h>
#include <ctype.h>
#include <string.h>

int num_len(int n) {
    int len = 1;
    while (n > 9) {
        n /= 10;
        len++;
    }
    return len;
}

typedef struct num {
    int x0;
    int x1;
    int y;
    int n;
} num;

#define MAX_N 1500
#define WIDTH 150
#define BUFLN (WIDTH*WIDTH)

int main() {
    int sum = 0;
    int c;
    int n = 0;
    int x = 0;
    int y = 0;

    num numbers[MAX_N];
    int numn = 0;

    char buffer[BUFLN];
    memset(buffer, '.', sizeof(buffer));

    int cogs[BUFLN][2];
    memset(cogs, 0, sizeof(cogs));

    while ((c = fgetc(stdin)) != EOF) {
        if (isdigit(c)) {
            n = n * 10 + c - '0';
            buffer[y*WIDTH+x] = '.';
            x++;
        }
        else {
            buffer[y*WIDTH+x] = c;
            if (n) {
                numbers[numn].x0 = x - num_len(n);
                numbers[numn].x1 = x;
                numbers[numn].y = y;
                numbers[numn].n = n;
                numn++;
            }
            if (c == '\n') {
                buffer[y*WIDTH+x] = '.';
                x = 0;
                y++;
            }
            else {
                x++;
            }
            n = 0;
        }
    }

    for (int i = 0; i < numn; i++) {
        num* N = &numbers[i];
        int a = 0;
        for (int Y = N->y-1; Y <= N->y+1; Y++) {
            if (Y < 0) continue;

            for (int X = N->x0 - 1; X <= N->x1; X++) {
                if (X < 0) continue;

                if (buffer[Y*WIDTH+X] == '*') {
                    // potential cog
                    if (cogs[Y*WIDTH+X][0] == 0) {
                        cogs[Y*WIDTH+X][0] = N->n;
                    }
                    else {
                        cogs[Y*WIDTH+X][1] = N->n;
                    }
                }

                if (buffer[Y*WIDTH+X] != '.') {
                    a = 1;
                    break;
                }

            }
            if (a) break;
        }
        if (a) {
            sum += N->n;
        }
    }
    printf("%d\n", sum);

    sum = 0;
    for (int i = 0; i < BUFLN; i++) {
        sum += cogs[i][0] * cogs[i][1];
    }
    printf("%d\n", sum);

}
