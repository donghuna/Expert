#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
36_�ù�
DP
D[ed] : A[ed]�������� Ʈ���� ��⸦ �̿��Ҷ� �ּ� ���
�⺻�� D[ed] = D[ed-1] + A[ed] * truckCost;
��ȭ�� D[ed] = min(D[ed], D[st-1] + getCost(st, ed) + helicost)
               (1 <= st <= ed)
getCost(st, ed) : ����(st, ed)�� Ʈ������ �й��Ҷ� �ּ� ���
*/
#include <cstdio>

const int LM = 3005;
int N, truckCost, heliCost;
int A[LM], D[LM], T[LM], prefixSum[LM];

void mergeSort(int* arr, int s, int e) {
    // 1. base condition
    if (s >= e) return;
    // 2. Devide & Conquer
    int m = (s + e) / 2, i = s, j = m + 1, k = s;
    mergeSort(arr, s, m), mergeSort(arr, m + 1, e);
    // 3. merge
    while (i <= m && j <= e) {
        if (arr[i] <= arr[j]) T[k++] = arr[i++];
        else T[k++] = arr[j++];
    }
    while (i <= m) T[k++] = arr[i++];
    while (j <= e) T[k++] = arr[j++];
    // 4. copy
    for (i = s; i <= e; ++i) arr[i] = T[i];
}

inline int min(int a, int b) { return a < b ? a : b; }

int getCost(int s, int e) {
    int m = (s + e) / 2;
    int scost = (A[m] * (m - s + 1) - (prefixSum[m] - prefixSum[s] + A[s])) * truckCost;
    int ecost = ((prefixSum[e] - prefixSum[m]) - A[m] * (e - m)) * truckCost;
    return scost + ecost;
}

int main() {
#ifdef _WIN32
    freopen("36.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) scanf("%d", A + i);
    scanf("%d %d", &truckCost, &heliCost);
    mergeSort(A, 1, N);
    // get prefix sum
    for (int i = 1; i <= N; ++i) prefixSum[i] = prefixSum[i - 1] + A[i];

    // Dynamic Programming
    for (int ed = 1; ed <= N; ++ed) {
        D[ed] = D[ed - 1] + A[ed] * truckCost;
        for (int st = 1; st <= ed; ++st) {
            D[ed] = min(D[ed], D[st - 1] + getCost(st, ed) + heliCost);
        }
    }
    printf("%d\n", D[N]);
    return 0;
}