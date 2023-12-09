#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_HANDS 1024

#ifndef PART
#define PART 2
#endif

char hands[MAX_HANDS][6];
int types[MAX_HANDS];

enum hand_type {
    HIGH_CARD = 1,
    PAIR,
    TWO_PAIR,
    THREE_KIND,
    FULL_HOUSE,
    FOUR_KIND,
    FIVE_KIND
};

int value(int c) {
    switch(c) {
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'J':
#if PART == 1
            return 11;
#else
            return 1;
#endif
        case 'T':
            return 10;
        default:
            return c - '0';
    }
}

int type(char* s) {
    int t[5] = {0};
    int tn[5] = {0};
    int n = 0;
    for (int i = 0; i < 5; i++) {
        int h = value(s[i]);
        int j;
        for (j = 0; j < n; j++) {
            if (t[j] == h) {
                tn[j]++;
                break;
            }
        }
        if (j == n) {
            t[n] = h;
            tn[n] = 1;
            n++;
        }
    }

    if (n == 1) {
        return FIVE_KIND;
    }
    if (n == 2) {
#if PART == 2
            // use jokers
            if (t[0] == 1 || t[1] == 1) return FIVE_KIND;
#endif
        if (tn[0] == 4 || tn[1] == 4) {
            return FOUR_KIND;
        }
        return FULL_HOUSE;
    }
    if (n == 3) {
        if (tn[0] == 3 || tn[1] == 3 || tn[2] == 3) {
#if PART == 2
            if (t[0] == 1 || t[1] == 1 || t[2] == 1) return FOUR_KIND;
#endif
            return THREE_KIND;
        }

#if PART == 2
        for (int i = 0; i < 3; i++) {
            if (t[i] == 1) {
                if (tn[i] == 2) return FOUR_KIND;
                return FULL_HOUSE;
            }
        }

#endif

        return TWO_PAIR;
    }
    if (n == 4) {
#if PART == 2
        for (int i = 0; i < 4; i++) {
            if (t[i] == 1) return THREE_KIND;
        }
#endif
        return PAIR;
    }
#if PART == 2
    for (int i = 0; i < 5; i++) {
        if (t[i] == 1) return PAIR;
    }
#endif
    return HIGH_CARD;
}

int tie_break(char* s, char* t) {
    for (int i = 0; i < 5; i++) {
        int d = value(s[i]) - value(t[i]);
        if (d != 0) return d;
    }
    return 0;
}

int order_hands(const void* plhs, const void* prhs) {
    int tleft = types[*(const int*)plhs];
    int tright = types[*(const int*)prhs];
    if (tleft == tright) {
        char* left = hands[*(const int*)plhs];
        char* right = hands[*(const int*)prhs];
        return tie_break(left, right);
    }
    return tleft - tright;
}

int main() {
    int64_t winnings = 0;
    int bids[MAX_HANDS];
    int order[MAX_HANDS];
    int n = 0;
    while(!feof(stdin)) {
        if (scanf("%s %d", hands[n], &bids[n]) != 2) break;
        types[n] = type(hands[n]);
        order[n] = n;
        n++;
    }

    qsort(order, n, sizeof(int), &order_hands);

    for (int i = 0; i < n; i++) {
        winnings += bids[order[i]] * (i + 1);
    }

    printf("%lu\n", winnings);
}
