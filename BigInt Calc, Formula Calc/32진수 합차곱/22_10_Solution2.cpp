/*
32_32진수 합차곱_user_ver02
ver02_2: 5자리 압축, 한 번에 자리올림. loop unrolling
*/
//
// make the result = (big + small) * |big - small|
// if the result is wrong answer per each TC, the penalty, 10000000 will be added to SCORE.
// total memory(heap + global + static + ...) cannot be over 256 MB
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

int mystrcmp(unsigned char* s, unsigned char* t) { // random 데이터 이므로 초반(s[0] ~ s[7])에 비교가 끝남
    for (rint i = 0; i < LM; ++i)
        if (s[i] != t[i]) return s[i] - t[i]; // 계산 결과는 signed int
    return 0;
}

void calc(unsigned char* a, unsigned char* b, unsigned char* result) {
    LL big[3005] = { 0 }, small[3005] = { 0 }, mul[6005] = { 0 };
    LL sum[3005] = { 0 }, diff[3005] = { 0 };
    rint i, j, k, n = KM;

    int flag = mystrcmp(a, b);
    if (flag == 0) {
        result[0] = '0', result[1] = 0;
        return;
    }

    // reverse & 25bit compress & get sum & difference
    if (flag < 0) {
        for (i = 0, j = 14999; j >= 0; i++, j -= 5) {
            big[i] = (toInt[b[j - 4]] << 20) | (toInt[b[j - 3]] << 15) | (toInt[b[j - 2]] << 10) | (toInt[b[j - 1]] << 5) | toInt[b[j]];
            small[i] = (toInt[a[j - 4]] << 20) | (toInt[a[j - 3]] << 15) | (toInt[a[j - 2]] << 10) | (toInt[a[j - 1]] << 5) | toInt[a[j]];
            sum[i] += big[i] + small[i];
            sum[i + 1] += sum[i] >> 25, sum[i] &= MASK;
            diff[i] += big[i] - small[i] + MOD, diff[i + 1] --;
            diff[i + 1] += diff[i] >> 25, diff[i] &= MASK;
        }
    }
    else {
        for (i = 0, j = 14999; j >= 0; i++, j -= 5) {
            big[i] = (toInt[a[j - 4]] << 20) | (toInt[a[j - 3]] << 15) | (toInt[a[j - 2]] << 10) | (toInt[a[j - 1]] << 5) | toInt[a[j]];
            small[i] = (toInt[b[j - 4]] << 20) | (toInt[b[j - 3]] << 15) | (toInt[b[j - 2]] << 10) | (toInt[b[j - 1]] << 5) | toInt[b[j]];
            sum[i] += big[i] + small[i];
            sum[i + 1] = sum[i] >> 25, sum[i] &= MASK;
            diff[i] += big[i] - small[i] + MOD, diff[i + 1] --;
            diff[i + 1] += diff[i] >> 25, diff[i] &= MASK;
        }
    }

    // get multiplication
    for (i = 0; i <= n; ++i) for (j = 0; j < n; ++j)
        mul[i + j] += sum[i] * diff[j];

    // normalize
    n = n * 2 - 1;
    for (i = 0; i < n; ++i) {
        mul[i + 1] += mul[i] >> 25;
        mul[i] &= MASK;
    }

    // reverse to origin order & toChar
    i = 0, j = n;
    for (k = 20; k >= 0 && (mul[n] >> k) == 0; k -= 5);
    for (; k >= 0; k -= 5) {
        result[i++] = toChar[(mul[n] >> k) & 31];
    }

    for (j = n - 1; j >= 0; --j) {
        result[i++] = toChar[(mul[j] >> 20) & 31];
        result[i++] = toChar[(mul[j] >> 15) & 31];
        result[i++] = toChar[(mul[j] >> 10) & 31];
        result[i++] = toChar[(mul[j] >> 5) & 31];
        result[i++] = toChar[mul[j] & 31];
    }
    result[i] = 0;
}