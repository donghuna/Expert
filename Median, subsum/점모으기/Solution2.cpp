#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
02_점모으기_ver02
merge sort
median
*/
#include <cstdio>

const int LM = 100004;
int N, M, ans;
int row[LM], col[LM], trr[LM];

void mergeSort(int*arr, int s, int e) {
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
    for (int i = s; i <= e; ++i) arr[i] = trr[i];
}

int abs(int a) { return a < 0 ? -a : a; }       // abs

int main() {
#ifdef _WIN32
    freopen("input.txt", "r", stdin);
#endif // _WIN32
    scanf("%d %d", &N, &M);
    for (int i = 1; i <= M; ++i) {               // 1 base
        scanf("%d %d", row + i, col + i);
    }
    mergeSort(row, 1, M);                   // 입력받은 좌표값들을 sorting.
    mergeSort(col, 1, M);

    int mr = row[(M + 1) / 2];              // sorting 하여 배열에서 바로 중앙값을 알아낸다. (속도가 여기서 훨씬 빨라짐)
    int mc = col[(M + 1) / 2];
    for (int i = 1; i <= M; ++i) {
        ans += abs(row[i] - mr);
        ans += abs(col[i] - mc);
    }
    printf("%d\n", ans);
    return 0;
}
