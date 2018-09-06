#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ALLOCSIZE 10
static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;


char *alloc(int n) {
    if (allocp - allocbuf + n > ALLOCSIZE) {
        return NULL;
    }
    allocp += n;
    return allocp - n;
}


void afree(char *p) {
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE){
        allocp = p;
    }
}


int main() {
    char *p = alloc(10);
    p[9] = 3;
    assert(allocp == allocbuf + 10);
    assert(alloc(10) == NULL);
    assert(alloc(1) == NULL);
    afree(p);
    assert(allocp == allocbuf);
}