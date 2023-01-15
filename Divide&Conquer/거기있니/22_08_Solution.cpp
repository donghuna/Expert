/*
22_�ű��ִ�_user
bitwise �̿�
*/
extern int countSameNumber(int guess[]);
#define rint register int

const int LM = 100000;
int used[LM + 5], guess[LM + 5];

void consistOf(int N, int K) {
    rint i, j, x, p, bin = 1;
    while ((1 << (bin + 1)) < K) bin++;
    // bin�� �ִ밪 16
    // 100000 / 16 = 6250
    for (i = 1; i <= N; i += bin) {  // �ִ� 6250�� �ݺ�����
        p = 0;
        for (j = 0; j < bin; ++j) {  // �ִ� 16���� ó��
            int len = 1 << j;        // 1, 2, 4, 8, 16, ... 32768
            for (x = 0; x < len && i + j <= LM; ++x) { // len �� (i+j)�� ����
                guess[p++] = i + j;
            }
            for (; x < len; ++x) guess[p++] = 0;       // �������� 0���� ä���
        }
        int res = countSameNumber(guess);
        for (j = 0; j < bin && i + j <= N; ++j) {
            used[i + j] = (res >> j) & 1;
        }
    }
}

int isEntryNumber(int num) {  // O(1)
    return used[num];
}