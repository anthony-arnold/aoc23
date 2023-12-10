#include <stdio.h>
#include <string.h>

char grid[256][256];
char raycast[256][256];
int start[2];
int path[65536][2];
char pipes[] = "-|LF7J";

enum {
    UP,
    LEFT,
    RIGHT,
    DOWN
};

int at(int x[2]) {
    return grid[x[0]][x[1]];
}

int next(int prev[2], int loc[2], int out[2]) {
    int c = at(loc);
    int dir;

    switch (c) {
    case '|':
        if (prev[1] > loc[1]) {
            dir = UP;
        }
        else {
            dir = DOWN;
        }
        break;
    case '-':
        if (prev[0] > loc[0]) {
            dir = LEFT;
        }
        else {
            dir = RIGHT;
        }
        break;
    case 'L':

        if (prev[0] > loc[0]) {
            dir = UP;
        }
        else {
            dir = RIGHT;
        }
        break;
    case 'J':

        if (prev[0] < loc[0]) {
            dir = UP;
        }
        else {
            dir = LEFT;
        }
        break;
    case '7':

        if (prev[0] < loc[0]) {
            dir = DOWN;
        }
        else {
            dir = LEFT;
        }
        break;
    case 'F':
        if (prev[0] > loc[0]) {
            dir = DOWN;
        }
        else {
            dir = RIGHT;
        }
        break;
    }

    switch(dir) {
    case UP:
        out[0] = loc[0];
        out[1] = loc[1] - 1;
        if (out[1] < 0) return 0;
        switch(at(out)) {
        case '-':
        case 'J':
        case 'L':
        case '.':
            return 0;
        }
        break;
    case DOWN:
        out[0] = loc[0];
        out[1] = loc[1] + 1;
        switch(at(out)) {
        case '-':
        case 'F':
        case '7':
        case '.':
            return 0;
        }
        break;
    case LEFT:
        out[0] = loc[0] - 1;
        out[1] = loc[1];
        if (out[0] < 0) return 0;
        switch(at(out)) {
        case '|':
        case 'J':
        case '7':
        case '.':
            return 0;
        }
        break;
    case RIGHT:
        out[0] = loc[0] + 1;
        out[1] = loc[1];
        switch(at(out)) {
        case '|':
        case 'L':
        case 'F':
        case '.':
            return 0;
        }
        break;
    }

    return 1;
}

int walk(int prev[2], int loc[2]) {
    int out[2];
    if (next(prev, loc, out)) {
        if (out[0] == start[0] && out[1] == start[1]) {
            path[0][0] = start[0];
            path[0][1] = start[1];
            return 1;
        }

        int i = walk(loc, out);
        if (i) {
            path[i][0] = out[0];
            path[i][1] = out[1];
            return i + 1;
        }
    }
    return 0;
}

int main() {
    int c;
    int x = 0;
    int y = 0;
    int len;
    int xmin = 256, ymin = 256, xmax = 0, ymax = 0;
    int inside = 0;

    memset(raycast, '.', sizeof(raycast));

    while ((c = fgetc(stdin)) != EOF) {
        if (c == 'S') {
            start[0] = x;
            start[1] = y;
        }

        if (c == '\n') {
            grid[x++][y] = '.';
            grid[x][y] = 0;
            y++;
            x = 0;
        }
        else {
            grid[x++][y] = c;
        }
    }

    for (int i = 0; i < 6; i++) {
        grid[start[0]][start[1]] = pipes[i];
        len = walk(start, start);
        if (len) break;
    }

    printf("%d\n", len/2);

    for (int i = 0; i < len; i++) {
        raycast[path[i][0]][path[i][1]] = grid[path[i][0]][path[i][1]];
        if (path[i][0] < xmin) xmin = path[i][0];
        if (path[i][0] > xmax) xmax = path[i][0];
        if (path[i][1] < ymin) ymin = path[i][1];
        if (path[i][1] > ymax) ymax = path[i][1];
    }

    for (int y = ymin; y <= ymax; y++) {
        int crossing = 0;
        int in = 0;
        for (int x = xmin; x <= xmax; x++) {
            int c = raycast[x][y];

            switch (c) {
            case 'F':
            case 'L':
                crossing = c;
                break;
            case 'J':
                if (crossing == 'F') {
                    in = !in;
                }
                crossing = 0;
                break;
            case '7':
                if (crossing == 'L') {
                    in = !in;
                }
                crossing = 0;
                break;
            case '|':
                in = !in;
                break;
            }


            if (c != '.') continue;
            if (in) {
                inside++;
                grid[x][y] = 'I';
            }
            else {
                grid[x][y] = 'O';
            }
        }
    }


    printf("%d\n", inside);
}
