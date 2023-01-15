/*
32_32���� ������_user_ver01
ver01: 5�ڸ� ����, �� ���� �ڸ��ø�.

[Problem]
 make the result = (A + B) * |A - B|
 if the result is wrong answer per each TC, the penalty, 10000000 will be added to SCORE.
 total memory(heap + global + static + ...) cannot be over 256 MB
*/
typedef long long LL;
#define rint  register int
const int MOD = 1 << 25;
const int MASK = MOD - 1;
const int LM = 15000;
const int KM = LM / 5;

int toInt[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                0, 0, 0, 0, 0, 0, 0,
                10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };
char toChar[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

int strcmp(unsigned char* s, unsigned char* t) { // random data�̹Ƿ� ���� 0~7 �ȿ� �Ǹ���.
    for (rint i = 0; i < LM; ++i)
        if (s[i] != t[i]) return s[i] - t[i];
    return 0;
}

void calc(unsigned char* a, unsigned char* b, unsigned char* result) {
    LL A[3005] = { 0 }; // a, b�߿� �� ū ���� 5���� ���� �������� ����
    LL B[3005] = { 0 }; // a, b�߿� �� ���� ���� 5���� ���� �������� ����
    LL C[3005] = { 0 }; // A[i] + B[j]
    LL D[3005] = { 0 }; // A[i] - B[j] (A > B �̹Ƿ�)
    LL M[6005] = { 0 }; // C[i] * D[j]
    LL d, e;

    char tmp[33000] = { 0 };
    rint i, j, k;

    int flag = strcmp(a, b); // a, b��� �Ǻ� : ���̰� �����Ƿ� ���ڿ� �񱳷� ���.
    if (flag == 0) {         // a, b�� ���� ���
        result[0] = '0', result[1] = 0;
        return;
    }
    if (flag < 0) {  // a[]�� b[]���� ���� ���
        for (d = e = i = 0, j = LM - 1; i < LM; ++i, --j) {
            d = (d << 5) | toInt[a[i]];  // ������
            e = (e << 5) | toInt[b[i]];  // ū��
            if (j % 5 == 0) {
                A[j / 5] = e & MASK;     // ū��
                B[j / 5] = d & MASK;     // ������
            }
        }
    }
    else {           // a[]�� b[]���� ū ���
        for (d = e = i = 0, j = LM - 1; i < LM; ++i, --j) {
            e = (e << 5) | toInt[a[i]];  // ū��
            d = (d << 5) | toInt[b[i]];  // ������
            if (j % 5 == 0) {
                A[j / 5] = e & MASK;     // ū��
                B[j / 5] = d & MASK;     // ������
            }
        }
    }

    int n = KM;
    for (i = 0; i < n; ++i) {
        // �� ���ϱ�
        C[i] += A[i] + B[i];
        C[i + 1] = C[i] >> 25;
        C[i] &= MASK;

        // �� ���ϱ�
        D[i] += A[i] - B[i];
        if (D[i] < 0) {
            D[i] += MOD;
            D[i + 1]--;
        }
    }

    // multifly
    for (i = 0; i <= n; ++i) { // �� ���� ���� �ڸ��ø��� ���� �� �����Ƿ� <=n ����
        for (j = 0; j < n; ++j)
            M[i + j] += C[i] * D[j];
    }

    // normalize : �ڸ� �ø� ó��
    n *= 2;
    for (i = 0; i <= n; ++i) {
        M[i + 1] += M[i] >> 25;
        M[i] &= MASK;
    }

    // to string
    for (i = k = 0; i <= n; ++i) {
        d = M[i];
        for (j = 0; j < 5; ++j)
            tmp[k++] = toChar[d & 31], d >>= 5;
    }

    for (k--; tmp[k] == 48; --k); // eliminate leading zero
    for (i = 0; k >= 0; ++i, --k) // reverse order saving
        result[i] = tmp[k];
    result[i] = 0;                // sentinel value
}