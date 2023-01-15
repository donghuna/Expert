/*
16_수열복원_user
*/
const int LM = 100005;

int N;
int stNum[LM];  // stNum[cardIndex] 에는 학생번호를 저장
int trr[LM];

extern int orderCheck(int left, int right);

void mergeSort(int* arr, int s, int e) {
    // 1. base condition
    if (s >= e) return;

    // 2. devide & conquer
    int m = (s + e) / 2, i = s, j = m + 1, k = s;
    mergeSort(arr, s, m);
    mergeSort(arr, m + 1, e);

    // 3. merge
    while (i <= m && j <= e) {
        if (orderCheck(arr[i], arr[j])) trr[k++] = arr[i++];
        else trr[k++] = arr[j++];
    }
    while (i <= m) trr[k++] = arr[i++];
    while (j <= e) trr[k++] = arr[j++];

    // 4. copy
    for (i = s; i <= e; ++i) arr[i] = trr[i];
}

void array_restore(int arrCount, int dat[]) {
    N = arrCount;
    for (int i = 1; i <= N; ++i) stNum[i] = i - 1;  // 학생번호 0 ~ N-1로 초기화
    mergeSort(stNum, 1, N);
    for (int i = 1; i <= N; ++i) dat[stNum[i]] = i;
}
