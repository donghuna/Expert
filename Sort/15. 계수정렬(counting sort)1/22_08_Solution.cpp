/*
15_countingSort_user
*/
#define rint register int
const int LM = 1 << 20;  // 1048576
const int ADD = 1 << 15; // 32768
const int CLM = 1 << 16; // 0 ~ 65535
int N, cnt[CLM], sortedArr[LM];

//void countingSort(int arraySize, int *arr) {
//  N = arraySize;
//  rint i, j = 0;
//  for (i = 0; i < N; ++i) cnt[arr[i] + ADD] ++;   // 1. 개수세기
//  for (i = 0; i < CLM; ++i) {
//      while (cnt[i]--) sortedArr[j++] = i - ADD;
//  }
//}

void countingSort(int arraySize, int *arr) {
    N = arraySize;
    for (rint i = 0; i < N; ++i) arr[i] += ADD;          // 0. shift

    for (rint i = 0; i < N; ++i) cnt[arr[i]] ++;         // 2. counting
    for (rint i = 1; i < CLM; ++i) cnt[i] += cnt[i - 1]; // 3. accumulate
    for (rint i = N - 1; i >= 0; --i)                    // 4. stable sort
        sortedArr[--cnt[arr[i]]] = arr[i];
}

int query(int idx) {
    return sortedArr[idx] - ADD;
}
