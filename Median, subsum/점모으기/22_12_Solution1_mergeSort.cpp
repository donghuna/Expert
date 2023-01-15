#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
02_점모으기_ver01
median
mergeSort
*/
#include <cstdio>

const int LM = 100005;
int N, M, ans;
int row[LM], col[LM], trr[LM];

inline int abs(int a) { return a < 0 ? -a : a; }
void input() {
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= M; ++i)
        scanf("%d %d", row + i, col + i);
}

void mergeSort(int* arr, int s, int e) {
    // 1. base condition
    if (s >= e) return;

    // 2. divide and conquer
    int m = (s + e) / 2, i = s, j = m + 1, k = s;
    mergeSort(arr, s, m);
    mergeSort(arr, m + 1, e);

    // 3. merge
    while (i <= m && j <= e) {
        if (arr[i] <= arr[j]) trr[k++] = arr[i++];
        else trr[k++] = arr[j++];
    }
    while (i <= m) trr[k++] = arr[i++];
    while (j <= e) trr[k++] = arr[j++];

    // 4. copy
    for (i = s; i <= e; ++i) arr[i] = trr[i];
}

int main() {
#ifdef _WIN32
    freopen("02.txt", "r", stdin);
#endif // _WIN32
    input();
    mergeSort(row, 1, M);
    mergeSort(col, 1, M);

    int mr = row[(1 + M) / 2];
    int mc = col[(1 + M) / 2];

    for (int i = 1; i <= M; ++i) {
        ans += abs(mr - row[i]);
        ans += abs(mc - col[i]);
    }

    printf("%d\n", ans);
    return 0;
}
