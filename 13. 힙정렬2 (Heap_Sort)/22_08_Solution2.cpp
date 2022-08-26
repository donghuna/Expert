#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
13_힙정렬2
ver02 : naive function
*/
#include <cstdio>
#define rint register int

const int LM = 1 << 19; // 524288
int N;

struct Priority_queue {
    int heap[LM], hn;

    void push(int nd) {
        rint c = ++hn;
        for (; c > 1 && nd > heap[c >> 1]; c >>= 1)
            heap[c] = heap[c >> 1];
        heap[c] = nd;
    }

    void pop() {
        rint c = 2;
        int nd = heap[hn];
        heap[hn--] = heap[1];

        for (; c <= hn && heap[c += (c < hn && heap[c + 1] > heap[c])] > nd; c <<= 1)
            heap[c >> 1] = heap[c];
        heap[c >> 1] = nd;
    }

    void output() {
        for (rint i = 1; i <= N; ++i) printf("%d ", heap[i]);
        puts("");
    }
}pq;

int main() {
#ifdef _WIN32
    freopen("input.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    int val;
    // 1. build maxpq
    for (rint i = 0; i < N; ++i) {
        scanf("%d", &val);
        pq.push(val);
    }
    pq.output();

    // 2. sort 
    for (rint i = 0; i < N; ++i) pq.pop();
    pq.output();

    return 0;
}
