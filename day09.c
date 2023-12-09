#include <stdio.h>

#ifndef PART
#define PART 1
#endif

#if PART == 1
#define EXTR_DIR -1
#else
#define EXTR_DIR 0
#endif

#define EXTR_LOC(n) ((PART == 1) ? (n-1) : 0)
#define EXTRA_DIR ((PART == 1) ? -1 : 0)
#define EXTRA_OFF ((PART == 1) ? 0 : 1)

int extr(int r[], int n) {
    int d[n];

    int zero = 1;
    for (int i = 1; i < n; i++) {
        d[i+EXTR_DIR] = r[i] - r[i-1];
        zero &= d[i+EXTR_DIR] == 0;
    }

    if (zero) {
        d[EXTR_LOC(n)] = 0;
    }
    else {
        d[EXTR_LOC(n)] = extr(d+EXTRA_OFF, n-1);
    }

#if PART == 1
    return r[n-1] + d[n-1];
#else
    return r[0] - d[0];
#endif
}

int main() {
    int r[128];
    int n;
    char c;
    int a = 0;
    while(!feof(stdin)) {
        n = 0;
        while(scanf("%d%c", &r[n], &c) == 2) {
            n++;
            if (c == '\n') break;
        }
        if (n == 0) break;

        a += extr(r, n);
    }

    printf("%d\n", a);
}
