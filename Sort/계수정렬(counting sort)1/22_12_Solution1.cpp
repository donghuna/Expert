/*
17_계수정렬_user_ver01
simple unstable counting sort
*/
const int LM = 1 << 20;    // 1048576
const int BIAS = 1 << 15;  // 32768
const int CLM = 1 << 16;   // 65536

int N, cnt[CLM], sortedArr[LM];

void countingSort(int arraySize, int* arr) {
    N = arraySize;
    int i, j;
    for (i = 0; i < N; ++i)
        cnt[arr[i] + BIAS] ++;

    for (i = j = 0; i < CLM; ++i) {
        while (cnt[i]--)
            sortedArr[j++] = i - BIAS;
    }
}

int query(int idx) {
    return sortedArr[idx];
}