#include <stdio.h>
#include <ctype.h>
#include <string.h>

const char* NUMBERS[] = {
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine"
};

int main() {
    int c;
    char buf[128] = {0};
    char* d = buf;
    int m = 0;

    while((c = fgetc(stdin)) != EOF) {
        if (c == '\n') {
            // a and b will hold ptrs to the first and last numbers
            char *a = 0, *b = 0;
            // p and q will be the values of these numbers
            int p, q;

            // search for the first and last digit
            for (int i = 1; i < 10; i++) {
                char* x = strchr(buf, '0' + i); // first instance of digit i
                char* y = strrchr(buf, '0' + i); // last instance of digit i

                // record min and max
                if (x && (!a || x < a)) {
                    a = x;
                    p = i;
                }
                if (y && (!b || y > b)) {
                    b = y;
                    q = i;
                }
            }

            // search for first and last occurence of each word
            for (int i = 0; i < 9; i++) {
                // first occurence of word i
                char* w = strstr(buf, NUMBERS[i]);
                if (w && (!a || w < a)) {
                    a = w;
                    p = i + 1;
                }

                // last occurence
                while (w) {
                    if (!b || w > b) {
                        b = w;
                        q = i + 1;
                    }
                    w = strstr(w + 1, NUMBERS[i]);
                }
            }

            // done
            memset(buf, 0, sizeof(buf));
            d = buf;
            m += p * 10 + q;
        }
        else {
            // Fill buffer
            *d++ = c;
        }
    }
    printf("%d\n", m);
}
