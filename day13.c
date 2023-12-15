#include <stdio.h>
#include <string.h>

#define MIR_MAX 32
char grid[MIR_MAX][MIR_MAX];

int strcmpv(int i, int j, int rows) {
    for(int k = 0; k < rows; k++) {
        int c = grid[k][i] - grid[k][j];
        if(c != 0) return c;
    }
    return 0;
}

int vert(int rows, int skip) {
    int k = strlen(grid[0]);
    for (int i = 0, j = 1; j < k; i++, j++) {
        if(i==skip) continue;
        if (strcmpv(i, j, rows) == 0) {
            int m;
            int n;
            for(m = i - 1, n = j + 1; m >= 0 && n < k; m--, n++) {
                if (strcmpv(m, n, rows) != 0) break;
            }

            if (m<0 || n == k) {
                return i+1;
            }
        }
    }
    return 0;
}

int horiz(int rows, int skip) {
    for (int i = 0, j = 1; j < rows; i++, j++) {
        if(i==skip)continue;
        if (strcmp(grid[i], grid[j]) == 0) {
            int m;
            int n;
            for(m = i - 1, n = j + 1; m >= 0 && n < rows; m--, n++) {
                if (strcmp(grid[m], grid[n]) != 0) break;
            }

            if (m<0 || n == rows) {
                return i+1;
            }
        }
    }
    return 0;
}

int mirror(int rows, int skipR, int skipC) {
    int m = 100 * horiz(rows, skipR);
    if (m)
        return m;
    return vert(rows, skipC);
}

int mirror2(int rows) {
    int u = mirror(rows,-1,-1);
    int skipR = -1;
    int skipC = -1;
    int v;
    int k = strlen(grid[0]);
    if(u >= 100)
        skipR=u/100-1;
    else
        skipC=u-1;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < k; j++) {
            int c = grid[i][j];
            int d = c == '#' ? '.' : '#';
            grid[i][j] = d;
            v = mirror(rows,skipR,skipC);
            if (v && v!=u) {
                return v;
            }
            grid[i][j] = c;
        }
    }
    return u;
}

int main() {
    int sum = 0, sum2 = 0;
    int rows=0;
    while(!feof(stdin)) {
        for (;;) {
            fgets(grid[rows], MIR_MAX, stdin);
            if(feof(stdin) || grid[rows][0] == '\n' || grid[rows][0] == 0) {
                break;
            }
            int k = strlen(grid[rows]);
            if (grid[rows][k-1] =='\n') {
                grid[rows][k-1] = '\0';
            }
            rows++;
        }

        sum += mirror(rows,-1,-1);
        sum2 += mirror2(rows);
        rows = 0;
    }

    printf("%d\n", sum);
    printf("%d\n", sum2);
}
