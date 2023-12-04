/* Type your code here, or load an example. */
int square(int num) {
    return num * num;
}
#include <stdio.h>

int num_intersect(int* x, int nx, int* y, int ny) {
    int n = 0;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            if (x[i] == y[j]) {
                n++;
            }
        }
    }
    return n;
}

int cards_won(int win[250][128], int* nwin, int have[250][128], int* nhave, int ncards, int i) {
    int x = num_intersect(win[i], nwin[i], have[i], nhave[i]);
    int w = x;
    for (int y = i + 1; y < x; y++) {
        x += cards_won(win, nwin, have, nhave, ncards, y);
    }
    return x;
}

int main() {
    int c;
    int win[250][128];
    int have[250][128];
    int nwin[250];
    int nhave[250];
    char temp[128];
    int card = 0;
    while (!feof(stdin)) {
        // discard game
        int _;
        scanf("Card %d:", &_);

        int n = 0;
        while (scanf("%d", &win[card][n++]) == 1) continue;
        n--;
        nwin[card] = n;

        // discard pipe
        scanf("|");
        n = 0;
        while (scanf("%d", &have[card][n++]) == 1) continue;
        n--;
        nhave[card] = n;

        card++;
    }

    int mul[250];
    int sum = 0;
    int answer2 = 0;
    for (int i = 0; i < card; i++) {
        mul[i] = 1;
    }
    for (int i = 0; i < card; i++) {
        int n = num_intersect(win[i], nwin[i], have[i], nhave[i]);
        if (n) {
            sum += 1 << (n-1);
        }
        answer2 += mul[i];

        for (int j = 0; j < n; j++) {
            mul[i + j + 1] += mul[i];
        }
    }
    printf("%d\n", sum);
    printf("%d\n", answer2);

}
