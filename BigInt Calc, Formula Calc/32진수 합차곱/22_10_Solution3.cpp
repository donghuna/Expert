/*
32_32진수 합차곱_user_ver03
ver03: 6자리 압축, 15번씩 나누어 자리올림.
*/
//
// make the result = (A + B) * |A - B|
// if the result is wrong answer per each TC, the penalty, 10000000 will be added to SCORE.
// total memory(heap + global + static + ...) cannot be over 256 MB

using ULL = unsigned long long;
#define rint  register int
const int MOD = 1 << 30;
const int MASK = MOD - 1;
const int LM = 15000;
const int KM = LM / 6;

int toInt[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
                0, 0, 0, 0, 0, 0, 0,
                10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35 };
char toChar[] = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

int mystrcmp(unsigned char* s, unsigned char* t) {
    for (rint i = 0; i < LM; ++i)
        if (s[i] != t[i]) return s[i] - t[i];
    return 0;
}

void calc(unsigned char* a, unsigned char* b, unsigned char* result) {
    ULL A[3005] = { 0 }, B[3005] = { 0 };
    ULL C[3005] = { 0 }, D[3005] = { 0 };
    ULL M[6005] = { 0 }, d, e;

    char tmp[33000] = { 0 };
    rint i, j, k;
    int flag = mystrcmp(a, b);
    if (flag == 0) {
        result[0] = '0', result[1] = 0;
        return;
    }
    if (flag < 0) {
        for (d = e = i = 0, j = LM - 1; i < LM; ++i, --j) {
            d = (d << 5) | toInt[a[i]];
            e = (e << 5) | toInt[b[i]];
            if (j % 6 == 0) A[j / 6] = e & MASK, B[j / 6] = d & MASK;
        }
    }
    else {
        for (d = e = i = 0, j = LM - 1; i < LM; ++i, --j) {
            d = (d << 5) | toInt[a[i]];
            e = (e << 5) | toInt[b[i]];
            if (j % 6 == 0) A[j / 6] = d & MASK, B[j / 6] = e & MASK;
        }
    }

    ULL carry = 0;
    int n = KM;
    for (i = 0; i < n; ++i) {
        // 합 구하기
        C[i] += A[i] + B[i];
        C[i + 1] = C[i] >> 30, C[i] &= MASK;

        // 차 구하기
        if (A[i] < B[i] + carry) // ULL이므로 음수가 없다.
            D[i] = MOD + A[i] - B[i] - carry, carry = 1;
        else D[i] = A[i] - B[i] - carry, carry = 0;
    }
    for (i = 0; i <= n; ++i) {
        for (j = 0; j < n; ++j) M[i + j] += C[i] * D[j];
        if (i % 16 == 15) {
            for (j = 0; j < n; ++j) {
                M[i + j + 1] += M[i + j] >> 30;
                M[i + j] &= MASK;
            }
        }
    }

    n *= 2;
    for (i = 0; i <= n; ++i) {
        M[i + 1] += M[i] >> 30;
        M[i] &= MASK;
    }

    for (i = k = 0; i <= n; ++i) {
        d = M[i];
        for (j = 0; j < 6; ++j)
            tmp[k++] = toChar[d & 31], d >>= 5;
    }

    for (k--; tmp[k] == 48; --k);
    for (i = 0; k >= 0; ++i, --k) result[i] = tmp[k];
    result[i] = 0;
}