#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *strop(char* str) {
    while (*str) {
        switch(*str) {
        case '-':
        case '=':
            return str;
        default:
            str++;
        }
    }
    return 0;
}

int lengths[256][8192];
char labels[256][8192][8];

int hash(const char* s) {
    int c = 0;
    for (const char* p = s; *p; p++) {
        if (*p == '\n') continue;
        c = ((c+*p)*17) % 256;
    }
    return c;
}

void rem(const char* str) {
    int b = hash(str);
    for (int i = 0; labels[b][i][0]; i++) {
        if (strcmp(labels[b][i], str) == 0) {
            int j;
            for (j = i + 1; labels[b][j][0]; j++) {
                strcpy(labels[b][j-1], labels[b][j]);
                lengths[b][j-1] = lengths[b][j];
            }
            labels[b][j-1][0] = 0;
            break;
        }
    }
}

void add(const char* str, int len) {
    int b = hash(str);
    int i;
    for (i = 0; labels[b][i][0]; i++) {
        if (strcmp(labels[b][i], str) == 0) {
            break;
        }
    }
    strcpy(labels[b][i], str);
    lengths[b][i] = len;
}

int main() {
    int sum = 0;
    char* op;
    char str[16];

    memset(labels, 0, sizeof(labels));
    memset(lengths, 0, sizeof(lengths));

    while (!feof(stdin)) {
        if (scanf("%[^,]", str)) {
            scanf(",");
            sum += hash(str);

            op = strop(str);
            if (*op == '-') {
                *op = 0;
                rem(str);
            }
            else {
                int len = atoi(op + 1);
                *op = 0;
                add(str, len);
            }
        }
    }

    printf("%d\n", sum);

    sum = 0;
    for (int i = 0; i < 256; i++) {
        for (int j = 0; labels[i][j][0]; j++) {
            sum += (1+i) * (1+j) * lengths[i][j];
        }
    }
    printf("%d\n", sum);

}
