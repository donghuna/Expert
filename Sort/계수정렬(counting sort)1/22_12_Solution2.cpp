/*
17_계수정렬_user_ver02
stable counting sort
*/
const int LM = 1 << 20;    // 1048576
const int BIAS = 1 << 15;  // 32768
const int CLM = 1 << 16;   // 65536

int N, cnt[CLM], sortedArr[LM];

void countingSort(int arraySize, int* arr) {
    N = arraySize;
    int i, j;
    // 0. init cnt array
    for (i = 0; i < CLM; ++i)
        cnt[i] = 0;
    // 1. counting
    for (i = 0; i < N; ++i)
        cnt[arr[i] += BIAS] ++;
    // 2. accumulate
    for (i = 1; i < CLM; ++i) cnt[i] += cnt[i - 1];

    // 3. sort
    for (i = N - 1; i >= 0; --i) {
        sortedArr[--cnt[arr[i]]] = arr[i] - BIAS;
    }
}

int query(int idx) {
    return sortedArr[idx];
}