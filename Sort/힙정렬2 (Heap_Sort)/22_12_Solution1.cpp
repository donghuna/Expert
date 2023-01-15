#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
15_힙정렬1_ver01
custom heap : naive function
*/
#include <cstdio>

const int LM = 1 << 19; // 524288
int heap[LM], hn, N;

void push(int nd) {
    int c = ++hn;
    for (; c > 1 && nd > heap[c / 2]; c /= 2)
        heap[c] = heap[c / 2];      // 부모값을 child로 끌어 내리기
    heap[c] = nd;
}

void pop() {
    int nd = heap[hn], c = 2;
    heap[hn--] = heap[1];
    for (; c <= hn; c *= 2) {
        // 대표 child 고르기
        //c += (c < hn && heap[c + 1] > heap[c]); // if사용하지 않기
        if (c < hn && heap[c + 1] > heap[c]) c++; // if사용하기

        if (heap[c] > nd)
            heap[c / 2] = heap[c]; // child값을 부모로 끌어 올리기
        else break;
    }
    heap[c / 2] = nd;
}

void output() {
    for (int i = 1; i <= N; ++i) printf("%d ", heap[i]);
    puts("");
}

int main() {
#ifdef _WIN32
    freopen("13.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    int i, val;
    // 1. build heap
    for (i = 0; i < N; ++i) {
        scanf("%d", &val);
        push(val);
    }
    output();

    // 2. sort heap
    for (int i = 0; i < N - 1; ++i)
        pop();
    output();
    return 0;
}