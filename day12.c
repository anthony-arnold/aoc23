#include <stdio.h>
#include <string.h>
#include <stdint.h>

const char* find(const char* str, int n) {
    const char *p;
    int i = 0;
    int th = 0;
    for(p = str; *p && (i < n); p++) {
        i++;
        switch(*p) {
        case '#':
            th=1;
            break;
        case '.':
            if (th) return NULL;
            i = 0;
            break;
        }
    }

    if (i == n) {
        return p - n;
    }
    return NULL;
}

uint64_t mem[32][128];

uint64_t combo(const char* line, int* groups, int n, int off) {
    int64_t matches = 0;
    int i = *groups;
    const char* ptr;
    if(mem[n][off]!=UINT64_MAX) return mem[n][off];

    ptr = find(line, i);
    while (ptr) {

        if (n == 1 && strchr(ptr+i, '#')) {}
        else if (*(ptr+i) != '#') {
            if (n==1) matches++;
            if (*(ptr+i) == '\0') break;
            if(n>1)
                matches += combo(ptr+i+1, groups+1, n-1,  off+(ptr-line)+i+1);
        }
        if(*ptr=='#') break;

        ptr = find(ptr + 1, i);
    }
    mem[n][off] = matches;
    return matches;
}

int main() {
    char line[128];
    int groups[32];
    int n;
    int k;
    uint64_t sum1 = 0;
    uint64_t sum2 = 0;
    char* append;
    while (!feof(stdin)) {
        scanf("%[?#.]", line);
        k = strlen(line);
        n = 0;
        while(scanf("%d,", &groups[n]) == 1) {
            n++;
        }
        memset(mem, 0xff, sizeof(mem));
        sum1 += combo(line, groups, n, 0);

        append = line + k;
        for (int i = 1; i < 5; i++) {
            *append++ = '?';
            memcpy(append, line, k);
            append += k;
            memcpy(&groups[n*i], &groups, sizeof(int) * n);
        }
        *append = '\0';

        n *= 5;
        sum2 += combo(line, groups, n, 0);
    }
    printf("%lu\n", sum1);
    printf("%lu\n", sum2);
}
