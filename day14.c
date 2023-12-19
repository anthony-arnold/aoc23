#include <stdio.h>
#include <string.h>
#include <limits.h>
#define LOOKBACK 1024

int grid[128][128];
int rows=0;
int nrocks = 0;
int len;
int cycles = 0;
int R0 = 100;
int mem[LOOKBACK];
int cyclen;

void north() {
    for (int k = 0; k < rows; k++) {
        for (int j = 0; j < len; j++) {
            int i = k;
            int t = grid[i][j];
            if(t < R0) continue;

            while(i && grid[i-1][j] == '.') {
                i--;
            }
            grid[k][j] = '.';
            grid[i][j] = t;
        }
    }
}


void east() {
    for (int j = len-1; j >= 0; j--) {
        for (int k = 0; k < rows; k++) {
            int i = j;
            int t = grid[k][j];
            if(t < R0) continue;

            while(i+1<len && grid[k][i+1] == '.') {
                i++;
            }
            grid[k][j] = '.';
            grid[k][i] = t;
        }
    }
}


void west() {
    for (int j = 0; j < len; j++) {
        for (int k = 0; k < rows; k++) {
            int i = j;
            int t = grid[k][j];
            if(t < R0) continue;

            while(i && grid[k][i-1] == '.') {
                i--;
            }
            grid[k][j] = '.';
            grid[k][i] = t;
        }
    }
}


void south() {
    for (int k = rows; k >= 0; k--) {
        for (int j = 0; j < len; j++) {
            int i = k;
            int t = grid[k][j];
            if(t < R0) continue;

            while(i+1<rows && grid[i+1][j] == '.') {
                i++;
            }

            grid[k][j] = '.';
            grid[i][j] = t;
        }
    }
}

int load() {
    int sum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < len; j++) {
            int c = grid[i][j];
            if (c >= R0) {
                sum += rows - i;
            }
        }
    }
    return sum;
}

void print_load() {
    printf("%d\n", load());
}

int docycle() {
    int c = 0;
    north();
    if(cycles==0)
        print_load();
    west();
    south();
    east();
    mem[cycles++] = load();

    for (int i = 3; i < cycles/2; i++) {
        if (memcmp(&mem[cycles - i*2], &mem[cycles - i], i * sizeof(int)) == 0) {
            cyclen = i;
            return 0;
        }
    }

    return 1;
}

void print_mod() {
    int off = cycles - cyclen * 2;
    int c = 1000000000 - off;
    int m = c % cyclen;
    printf("%d\n", mem[off + m - 1]);
}

int main() {
    char line[128];
    memset(mem, 0, sizeof(mem));

    while (fgets(line, 127, stdin)) {
        len = strlen(line);
        for (int i = 0; line[i]; i++) {
            grid[rows][i] = line[i];
            if (grid[rows][i] == 'O') {
                grid[rows][i] = R0 + nrocks++;
            }
        }
        rows++;
    }
    for (int i = 0; i < LOOKBACK; i++) {
        if (!docycle()) break;
    }

    print_mod();
}
