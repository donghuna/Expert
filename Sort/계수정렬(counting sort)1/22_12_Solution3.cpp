/*
17_계수정렬_user_ver01
unstable self counting sort
*/
const int LM = 1 << 20;
const int CLM = 1 << 16;
const int BIAS = 1 << 15;  // 32768
int N, cnt[CLM], * A;

void countingSort(int arraySize, int* arr) {
    A = arr;
    N = arraySize;
    for (int i = 0; i < N; ++i)
        arr[i] += BIAS;

    /// counting sort
    for (int i = 0; i < N; ++i)   // counting
        cnt[arr[i]] ++;

    for (int i = 1; i < CLM; ++i)  // accumulate
        cnt[i] += cnt[i - 1];

    int i, j;
    // self counting sort
    for (i = N - 1; i >= 0; --i) {
        if (arr[i] < 0) arr[i] = -arr[i];  // 이전단계에서 자리를 찾은 경우
        else {
            for (j = --cnt[arr[i]]; i != j; j = --cnt[arr[i]]) {
                int tmp = arr[j];
                arr[j] = -arr[i]; // 자리를 찾은 경우를 음수로 표시
                arr[i] = tmp;
            }
        }
    }
}

int query(int idx) {
    return A[idx] - BIAS;
}