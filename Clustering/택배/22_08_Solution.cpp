#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
26_�ù�
Dynamic Programming
DT[ed] = A[ed]�� �������� Ʈ���� ��⸦ ����� �� �ּ� ����� ��
*/
#include <cstdio>

const int LM = 3005;
int N, truckCost, heliCost;
int A[LM], T[LM];
int PS[LM];  // prefix sum
int DT[LM];

void mergeSort(int s, int e) {
    if (s >= e) return;
    int m = (s + e) / 2, i = s, j = m + 1, k = s;
    mergeSort(s, m);
    mergeSort(m + 1, e);

    while (i <= m && j <= e) {
        if (A[i] <= A[j]) T[k++] = A[i++];
        else T[k++] = A[j++];
    }
    while (i <= m) T[k++] = A[i++];
    while (j <= e) T[k++] = A[j++];

    for (i = s; i <= e; ++i) A[i] = T[i];
}

int getCost(int s, int e) {
    int m = (s + e) / 2;
    int sCost = (A[m] * (m - s + 1) - (PS[m] - PS[s] + A[s])) * truckCost;
    int eCost = ((PS[e] - PS[m]) - (e - m) * A[m]) * truckCost;
    return sCost + eCost;
}

int min(int a, int b) { return a < b ? a : b; }
int main() {
#ifdef _WIN32
    freopen("input.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", A + i);
    }
    scanf("%d %d", &truckCost, &heliCost);

    mergeSort(1, N);

    // get prefix sum
    for (int i = 1; i <= N; ++i) PS[i] = PS[i - 1] + A[i];

    // DP process
    // DT[e] = A[e]�� �������� Ʈ���� ��⸦ ����� �� �ּҺ���� ��
    for (int e = 1; e <= N; ++e) {
        // �ʱⰪ : A[e]���� Ʈ���� �̿��ϴ� ������ ����
        DT[e] = DT[e - 1] + A[e] * truckCost;
        // 1. DT[s-1] : A[s-1] �������� �����ذ� �̹� ������
        // 2. m((s+e)/2) �������� ���(heliCost)�� �̿��ϰ� ������ ������ ����������
        //    Ʈ���� �̿��ϴ�() ����� �ּҺ��
        for (int s = e; s >= 1; --s) {
            int cost = getCost(s, e) + heliCost;
            DT[e] = min(DT[e], DT[s - 1] + cost);
        }
    }
    printf("%d\n", DT[N]);
    return 0;
}