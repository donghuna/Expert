#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
34_줄세우기_ver02
segment tree
*/
#include <stdio.h>

const int LM = (int)1e5 + 5;
const int TLM = 1 << 18;
int N, A[LM], R[LM], ans[LM], trr[LM];
int tree[TLM];

void mergeSort(int* arr, int s, int e) {
    // 0. base condition
    if (s >= e) return;
    // 1. divide
    int m = (s + e) / 2, i = s, j = m + 1, k;
    // 2. conquer
    mergeSort(arr, s, m);
    mergeSort(arr, m + 1, e);
    for (k = s; k <= e; ++k) {
        if (i > m) trr[k] = arr[j++];
        else if (j > e) trr[k] = arr[i++];
        else if (arr[i] < arr[j]) trr[k] = arr[i++];
        else trr[k] = arr[j++];
    }
    //3. copy
    for (i = s; i <= e; ++i) arr[i] = trr[i];
}

void buildTree(int now, int s, int e) {
    if (s == e) {
        tree[now] = 1;
        return;
    }
    int lch = now * 2, rch = lch + 1, m = (s + e) / 2;
    buildTree(lch, s, m);
    buildTree(rch, m + 1, e);
    tree[now] = tree[lch] + tree[rch];
}

void update(int now, int s, int e, int lowCnt, int tg) {
    tree[now]--;
    if (s >= e) {
        ans[tg] = A[s];
        return;
    }
    int lch = now * 2, rch = lch + 1, m = (s + e) / 2;
    if (tree[lch] > lowCnt) {
        update(lch, s, m, lowCnt, tg);
    }
    else {
        update(rch, m + 1, e, lowCnt - tree[lch], tg);
    }
}

int main() {
    //freopen("input.txt", "r", stdin);
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", A + i);
    for (int i = 1; i <= N; ++i) scanf("%d", R + i);

    mergeSort(A, 1, N);

    buildTree(1, 1, N);
    for (int i = N; i > 0; --i) {
        update(1, 1, N, R[i], i);
    }
    for (int i = 1; i <= N; ++i)
        printf("%d\n", ans[i]);

    return 0;
}