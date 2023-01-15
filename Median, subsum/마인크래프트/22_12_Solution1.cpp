#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
01_����ũ����Ʈ_ver01
O(N*M*257) => O(64250000)
*/
#include <cstdio>

const int LM = 250005;
int N, M, NM; // N(����), M(����), NM = N * M
int B;        // �κ� ����
int A[LM];    // �� ���� ���� ����
int ansTime = 1 << 30, ansHeight;

int check(int tgH) {
    int timeCost = 0, inven = B;
    for (int i = 0; i < NM; ++i) {
        if (A[i] < tgH) {  // ��ǥ�� �ϴ� ���̺��� ���� ���� ���
            int diff = tgH - A[i];
            inven -= diff;
            timeCost += diff;
        }
        else {             // ��ǥ�� �ϴ� ���̺��� ���� ���� ���
            int diff = A[i] - tgH;
            inven += diff;
            timeCost += diff * 2;
        }
    }
    if (inven < 0)  // ���� ����� �������
        return 1;

    if (timeCost <= ansTime) {
        ansTime = timeCost;
        ansHeight = tgH;
    }
    return 0;
}

int main() {
#ifdef _WIN32
    freopen("01.txt", "r", stdin);
#endif // _WIN32
    scanf("%d %d %d", &N, &M, &B);
    NM = N * M;
    for (int i = 0; i < NM; ++i)
        scanf("%d", A + i);  // &A[i]

    for (int h = 0; h < 257; ++h) {
        if (check(h))
            break;
    }

    printf("%d %d\n", ansTime, ansHeight);
    return 0;
}