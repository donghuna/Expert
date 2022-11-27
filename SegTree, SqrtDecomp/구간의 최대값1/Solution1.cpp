#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
33_������ �ִ밪1_ver01
sqrt decomposition
*/
#include <cstdio>

const int INF = 1 << 30;
const int LM = 50005;
const int MOD = 256;
const int MASK = MOD - 1;

int N, Q, A[LM], B[MOD];

inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

void update(int idx, int newVal) {
    int bn = idx / MOD;                            // ���� ��ȣ ���ϱ�
    int st = bn * MOD, ed = min(N - 1, st + MASK); // bn������ ����ϴ� A[]�� ���۹�ȣ�� �� ��ȣ
    A[idx] = B[bn] = newVal;                       // �� ������Ʈ
    while (st <= ed)                               // bn������ �ִ밪 ���ϱ�
        B[bn] = max(B[bn], A[st++]);
}

int query(int st, int ed) {
    int ret = -INF;
    while (st <= ed && (st & MASK))                  // ���� ���������� �ִ밪 ���ϱ�
        ret = max(ret, A[st++]);

    while (st <= ed && ((ed + 1) & MASK))          // ���� ���������� �����Ͽ� �ִ밪 ���ϱ�
        ret = max(ret, A[ed--]);

    for (; st <= ed; st += MOD)                    // ���������� �ִ밪 ���ϱ�
        ret = max(ret, B[st / MOD]);
    return ret;
}

int main() {
#ifdef _WIN32
    freopen("33.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
#endif // _WIN32
    scanf("%d %d", &N, &Q);
    int i, val, st, ed;
    for (i = 0; i < N; ++i) {                     // �ʱⰪ �Է�
        scanf("%d", &val);
        update(i, val);
    }

    for (i = 0; i < Q; ++i) {                      // ���� ó��
        scanf("%d %d", &st, &ed);
        printf("%d\n", query(st - 1, ed - 1));     // 0_base�� ������Ʈ �Ǿ����Ƿ�...
    }
    return 0;
}