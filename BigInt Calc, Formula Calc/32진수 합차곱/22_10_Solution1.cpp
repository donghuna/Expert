/*
32_32진수 합차곱_user_ver01
ver01: 5자리 압축, 한 번에 자리올림.

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

int strcmp(unsigned char* s, unsigned char* t) { // random data이므로 길어야 0~7 안에 판명난다.
    for (rint i = 0; i < LM; ++i)
        if (s[i] != t[i]) return s[i] - t[i];
    return 0;
}

void calc(unsigned char* a, unsigned char* b, unsigned char* result) {
    LL A[3005] = { 0 }; // a, b중에 더 큰 수를 5개씩 묶어 역순으로 저장
    LL B[3005] = { 0 }; // a, b중에 더 작은 수를 5개씩 묶어 역순으로 저장
    LL C[3005] = { 0 }; // A[i] + B[j]
    LL D[3005] = { 0 }; // A[i] - B[j] (A > B 이므로)
    LL M[6005] = { 0 }; // C[i] * D[j]
    LL d, e;

    char tmp[33000] = { 0 };
    rint i, j, k;

    int flag = strcmp(a, b); // a, b대소 판별 : 길이가 같으므로 문자열 비교로 충분.
    if (flag == 0) {         // a, b가 같은 경우
        result[0] = '0', result[1] = 0;
        return;
    }
    if (flag < 0) {  // a[]가 b[]보다 작은 경우
        for (d = e = i = 0, j = LM - 1; i < LM; ++i, --j) {
            d = (d << 5) | toInt[a[i]];  // 작은수
            e = (e << 5) | toInt[b[i]];  // 큰수
            if (j % 5 == 0) {
                A[j / 5] = e & MASK;     // 큰수
                B[j / 5] = d & MASK;     // 작은수
            }
        }
    }
    else {           // a[]가 b[]보다 큰 경우
        for (d = e = i = 0, j = LM - 1; i < LM; ++i, --j) {
            e = (e << 5) | toInt[a[i]];  // 큰수
            d = (d << 5) | toInt[b[i]];  // 작은수
            if (j % 5 == 0) {
                A[j / 5] = e & MASK;     // 큰수
                B[j / 5] = d & MASK;     // 작은수
            }
        }
    }

    int n = KM;
    for (i = 0; i < n; ++i) {
        // 합 구하기
        C[i] += A[i] + B[i];
        C[i + 1] = C[i] >> 25;
        C[i] &= MASK;

        // 차 구하기
        D[i] += A[i] - B[i];
        if (D[i] < 0) {
            D[i] += MOD;
            D[i + 1]--;
        }
    }

    // multifly
    for (i = 0; i <= n; ++i) { // 두 수의 합은 자리올림이 있을 수 있으므로 <=n 까지
        for (j = 0; j < n; ++j)
            M[i + j] += C[i] * D[j];
    }

    // normalize : 자리 올림 처리
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