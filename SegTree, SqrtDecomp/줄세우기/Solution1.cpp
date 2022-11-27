#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
34_줄세우기_ver01
sqrt decomposition
*/
#include <cstdio>

const int LM = 100005;
const int BASE = 8;
const int MOD = 1 << BASE;
const int MASK = MOD - 1;

int N, A[LM], T[LM], Q[LM];
int B[LM];
int ans[LM];

void update(int idx) {
    A[idx] = 0, B[idx >> BASE]--;
}

int query(int cnt) {
    int st = 0;
    for (; B[st] < cnt; ++st)      // 구역단위 계산
        cnt -= B[st];

    st *= MOD;
    for (; cnt; ++st) if (A[st]) { // 남은 자투리는 순차탐색
        cnt--;
        if (cnt == 0) return st;
    }
    return 0;
}

void mergeSort(int s, int e) {
    if (s + 1 >= e) return;
    int m = (s + e) >> 1, i = s, j = m, k = s;
    mergeSort(s, m), mergeSort(m, e);
    while (i < m && j < e) {
        if (A[i] <= A[j]) T[k++] = A[i++];
        else T[k++] = A[j++];
    }
    while (i < m) T[k++] = A[i++];
    while (j < e) T[k++] = A[j++];

    for (i = s; i < e; ++i) A[i] = T[i];
}

int main() {
#ifdef _WIN32
    freopen("34.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    // 입력
    for (int i = 0; i < N; ++i) {
        B[i >> BASE] ++;               // 구역수 증가
        scanf("%d", A + i);
    }
    // 정보 입력
    for (int i = 0; i < N; ++i) scanf("%d", Q + i);

    mergeSort(0, N);

    for (int i = N - 1; i >= 0; --i) {
        int idx = query(Q[i] + 1);     // i번 학생의 키 구하기
        ans[i] = A[idx];
        update(idx);                   // i번 학생 정보 제거
    }

    for (int i = 0; i < N; ++i)
        printf("%d\n", ans[i]);
    return 0;
}