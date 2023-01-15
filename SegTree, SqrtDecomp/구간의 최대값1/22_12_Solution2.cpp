#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
20_������ �ִ밪1_ver02
sqrt decomposition : [s, e) , update()�Լ� �̿�
*/
#include <cstdio>

const int LM = 50005;
const int MOD = 256;   // sqrt(50000) = 223.606
int N, Q;
int A[LM];             // input data
int B[MOD + 1];        // max value per block

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }
void update(int idx, int newVal) {
    int bn = idx / MOD;                       // idx�� ���Ե� ���� ��ȣ
    int sn = bn * MOD, en = min(sn + MOD, N); // idx�� ���Ե� ���� ����
    A[idx] = B[bn] = newVal;
    for (int i = sn; i < en; ++i)             // ������ �ִ밪 ������Ʈ
        B[bn] = max(B[bn], A[i]);
}

int query(int s, int e) {   // ���� [s, e)
    int maxValue = A[s];
    // 1. ���� ���������� �ִ밪 ���ϱ�
    while (s < e && s % MOD)
        maxValue = max(maxValue, A[s++]);

    // 2. ���� ���������� �ִ밪 ���ϱ�
    while (s < e && e % MOD)
        maxValue = max(maxValue, A[--e]);

    // 3. �� ������ �ִ밪 ���ϱ�
    for (s /= MOD, e /= MOD; s < e; s++)
        maxValue = max(maxValue, B[s]);

    return maxValue;
}

int main() {
#ifdef _WIN32
    freopen("20.txt", "r", stdin);
#endif // _WIN32
    int val, s, e;
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N; ++i) {
        scanf("%d", A + i);
        update(i, A[i]);
    }

    for (int i = 0; i < Q; ++i) {
        scanf("%d %d", &s, &e);
        printf("%d\n", query(s - 1, e));
    }

    return 0;
}