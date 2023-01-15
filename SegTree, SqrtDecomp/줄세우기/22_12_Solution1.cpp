#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
21_줄세우기_ver01
sqrt decomposition
*/
#include <cstdio>

const int LM = 100005;
const int MOD = 256;

int N, H[LM], T[LM]; // N: 전체 사람수, H[] : 키, T[]: 임시배열
int B[LM];           // B[] : block(구역)별 빈 자리수의 합
int qrr[LM];         // qrr[i] : i번째 사람이 왼쪽을 바라볼 때, 자신보다 작거나 같은 사람들의 수
int ans[LM];         // ans[i] : i번째 사람의 키

void mergeSort(int* arr, int s, int e) {
    if (s >= e) return;
    int m = (s + e) / 2, i = s, j = m + 1, k = s;
    mergeSort(arr, s, m);
    mergeSort(arr, m + 1, e);

    while (i <= m && j <= e) {
        if (arr[i] <= arr[j]) T[k++] = arr[i++];
        else T[k++] = arr[j++];
    }
    while (i <= m) T[k++] = arr[i++];
    while (j <= e) T[k++] = arr[j++];
    for (i = s; i <= e; ++i) arr[i] = T[i];
}

int query(int cnt) {  // cnt번째 자리 찾기
    int i = 0;
    for (; B[i / MOD] < cnt; i += MOD) cnt -= B[i / MOD];

    // 자투리 남은 자리 계산하기
    for (; cnt > 0; ++i) {
        if (H[i] > 0) cnt--;
        if (cnt == 0) return i;
    }
    return -1; // impossible
}

int main() {
#ifdef _WIN32
    freopen("21.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%d", H + i);
        B[i / MOD] ++;
    }
    for (int i = 0; i < N; ++i) scanf("%d", qrr + i);

    mergeSort(H, 0, N - 1);

    for (int i = N - 1; i >= 0; --i) {
        int ret = query(qrr[i] + 1);
        ans[i] = H[ret];  // get answer

        // update
        H[ret] = 0;
        B[ret / MOD] --;
    }
    for (int i = 0; i < N; ++i) printf("%d\n", ans[i]);
    return 0;
}