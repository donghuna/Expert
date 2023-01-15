#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
15_������1_ver01
custom heap : naive function
*/
#include <cstdio>

const int LM = 1 << 19; // 524288
int heap[LM], hn, N;

void push(int nd) {
    int c = ++hn;
    for (; c > 1 && nd > heap[c / 2]; c /= 2)
        heap[c] = heap[c / 2];      // �θ��� child�� ���� ������
    heap[c] = nd;
}

void pop() {
    int nd = heap[hn], c = 2;
    heap[hn--] = heap[1];
    for (; c <= hn; c *= 2) {
        // ��ǥ child ����
        //c += (c < hn && heap[c + 1] > heap[c]); // if������� �ʱ�
        if (c < hn && heap[c + 1] > heap[c]) c++; // if����ϱ�

        if (heap[c] > nd)
            heap[c / 2] = heap[c]; // child���� �θ�� ���� �ø���
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