#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAX_NODES 17576

int left[MAX_NODES];
int right[MAX_NODES];
char steps[1024];
int nsteps;

int node_addr(const char* node) {
    return (node[0] - 'A')*26*26 + (node[1] - 'A')*26 + (node[2] - 'A');
}

int walk(int node, uint64_t *pstep) {
    int step = *pstep;
    char s = steps[step++ % nsteps];
    switch(s) {
        case 'L':
            node = left[node];
            break;
        case 'R':
            node = right[node];
            break;
    }
    *pstep = step;
    return node;
}

int main() {
    int node;
    int zzz = node_addr("ZZZ");
    int ghosts[26*26];
    int nghosts = 0;
    uint64_t lcm;
    uint64_t step = 0;

    scanf("%s", steps);
    nsteps = strlen(steps);

    while(!feof(stdin)) {
        char anode[4], aleft[4], aright[4];
        if (scanf(" %[A-Z] = (%[A-Z], %[A-Z])", anode, aleft, aright) != 3) {
            break;
        }
        int ni = node_addr(anode);
        int li = node_addr(aleft);
        int ri = node_addr(aright);

        left[ni] = li;
        right[ni] = ri;

        if (ni % 26 == 0) {
            ghosts[nghosts++] = ni;
        }
    }

    // PART 1
    node = 0;
    while (node != zzz) {
        node = walk(node, &step);
    }
    printf("%lu\n", step);

    // PART 2
    // To make sense of this:
    //  - the number of steps in the directions is prime
    //  - the number of steps required is the LCM of the number of steps required by each ghost
    //  ... BUT ...
    //  - all ghosts reach a destination in a multiple of the number of steps
    //  - each multiple is a prime number
    //  ... SO ...
    //  - the LCM is just the product of all the multiples times the number of steps in the
    //    directions
    lcm = 1;
    for (int i = 0; i < nghosts; i++) {
        step = 0;
        node = ghosts[i];
        
        while(node % 26 != 25) {
            node = walk(node, &step);
        }
        lcm *= step / nsteps;
    }

    printf("%lu\n", lcm * nsteps);

}
