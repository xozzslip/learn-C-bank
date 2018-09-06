#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

typedef struct BufHdr {
    size_t len;
    size_t cap;
    void *buf;
}BufHdr;

#define buf__hdr(b) ((BufHdr *)((void * )(b) - offsetof(BufHdr, buf)))
#define buf__fit(b) (buf__fits(b) ? 0 : ((b) = buf__grow(b, sizeof(*(b)))))
#define buf__fits(b) (buf_cap(b) > buf_len(b))
#define buf_push(b, x) (buf__fit(b), (b)[buf__hdr(b)->len] = x, buf__hdr(b)->len++)
#define buf_len(b) ((b) ? buf__hdr(b)->len : 0)
#define buf_cap(b) ((b) ? buf__hdr(b)->cap : 0)

void *buf__grow(void *b, size_t elem_size) {
    size_t new_cap = (2 * buf_cap(b) + 1);
    size_t new_size = offsetof(BufHdr, buf) + new_cap * elem_size;
    BufHdr *new_hdr;
    if (b) {
        new_hdr = realloc(new_hdr, new_size);
    }
    else {
        new_hdr = malloc(new_size);
        new_hdr->len = 0;
    }
    new_hdr->cap = new_cap;
    return new_hdr->buf;
}

void test_buf() {
    long *buf = NULL;
    int *buf2 = NULL;
    int i = 0;
    printf("%lu", buf_len(buf));
    buf_push(buf, 1);

    // for (i = 0; i < 1024; i++) {
    //     buf_push(buf, i);
    //     buf_push(buf2, i);
    // }

    // for (i = 0; i < 1024; i++) {
    //     assert(buf[i] == i);
    //     assert(buf2[i] == i);
    // }
}



int main() {
    test_buf();
}