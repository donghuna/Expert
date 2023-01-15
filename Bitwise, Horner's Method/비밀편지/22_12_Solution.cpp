#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
09_�������
bitwise
*/
#include <cstdio>

int code[] = { 0, 0x0f, 0b010011, 0b011100,
0b100110, 0b101001, 0b110101, 0b111010 };
char ans[12];

int getChar(int d) {
    // implement here
    for (int i = 0; i < 8; ++i) {
        int bit = d ^ code[i];       // ���� �ٸ� ��Ʈ ���ϱ�
        if ((bit & (bit - 1)) == 0) { // bit�� 2�� �������̰ų� 0�̶��
            return i;
        }
    }

    return -1;   // �� ã�� ���
}

int main() {
#ifdef _WIN32
    freopen("09.txt", "r", stdin);
#endif // _WIN32
    int N, i, j, d, a;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        // 2�� ��Ʈ 6���� 10�� ���� d�����
        d = 0;
        for (int j = 0; j < 6; ++j) {
            scanf("%1d", &a);
            d = d * 2 + a; // Horner's method
        }

        // d�� 1��Ʈ ���� ���̳��� �ڵ� ã��
        int rv = getChar(d); // -1, 0 ~ 7
        if (rv < 0) { // ������ �ڵ尡 ���� ���: rv=-1
            printf("%d\n", i + 1);
            return 0;
        }
        // rv: 0 ~ 7
        ans[i] = rv + 'A'; // ������ �ڵ带 ã�� ���
    }
    puts(ans); // printf("%s\n", ans);
    return 0;
}