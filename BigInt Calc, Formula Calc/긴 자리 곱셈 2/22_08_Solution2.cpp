#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/**
29_Bigint multiplication 2
comkiwer
8자리씩 묶어 처리하기 : class + Duff's device(loop unrolling)
*/
#include <cstdio>
#define rint register int

using LL = long long;
const int LM = 2005;
const int NLM = LM / 8 + 2;
const int MOD = 100000000;

int strlen(const char* s, rint len = 0) {
    while (s[len]) ++len;
    return len;
}
struct Bigint {
    LL num[NLM];
    int sign, len;
    Bigint() { init(); }
    Bigint(const char* s) {
        init();
        if (s[0] == '-') sign = 1, ++s;
        rint slen = strlen(s), i = len = (slen + 7) / 8;
        LL d = 0;
        switch ((slen - 1) % 8) {  // Duff's device : loop unrolling
        case 7: do {
            d = d * 10 + *s++ - '0';
        case 6: d = d * 10 + *s++ - '0';
        case 5: d = d * 10 + *s++ - '0';
        case 4: d = d * 10 + *s++ - '0';
        case 3: d = d * 10 + *s++ - '0';
        case 2: d = d * 10 + *s++ - '0';
        case 1: d = d * 10 + *s++ - '0';
        case 0: d = d * 10 + *s++ - '0', \
            num[--i] = d, d = 0;
        } while (i > 0);
        }
    }
    void init() {
        sign = 0, len = 1;
        for (rint i = 0; i < NLM; ++i) num[i] = 0;
    }

    bool isZero() { return len == 1 && num[0] == 0; }
    void multi(Bigint& r) {
        if (isZero() || r.isZero()) {
            init(); return;
        }
        LL ret[NLM] = { 0 };
        for (rint i = 0; i < len; ++i) {
            for (rint j = 0; j < r.len; ++j) ret[i + j] += num[i] * r.num[j];
        }

        sign ^= r.sign;
        len += r.len - 1;
        for (rint i = 0; i <= len; ++i) {
            num[i] = ret[i] % MOD;
            ret[i + 1] += ret[i] / MOD;
        }
        len += (num[len] > 0);
    }
    void toString(char* s) {
        rint i = len - 1, j = 0;
        if (sign) s[j++] = '-';
        LL d = MOD / 10, n = num[i--];
        for (; d > 1 && n / d == 0; d /= 10);
        for (; d; d /= 10) s[j++] = (char)(n / d + '0'), n %= d;

        for (; i >= 0; --i) {
            n = num[i];
            s[j + 7] = (char)(n % 10 + '0'), n /= 10;
            s[j + 6] = (char)(n % 10 + '0'), n /= 10;
            s[j + 5] = (char)(n % 10 + '0'), n /= 10;
            s[j + 4] = (char)(n % 10 + '0'), n /= 10;
            s[j + 3] = (char)(n % 10 + '0'), n /= 10;
            s[j + 2] = (char)(n % 10 + '0'), n /= 10;
            s[j + 1] = (char)(n % 10 + '0'), n /= 10;
            s[j + 0] = (char)(n % 10 + '0'), n /= 10;
            j += 8;
        }
        s[j] = 0;
    }
}A, B;

char as[LM], bs[LM];
int main() {
#ifdef _WIN32
    freopen("29.txt", "r", stdin);
#endif // _WIN32

    while (scanf("%s %s", as, bs)) {
        if (as[0] == '0' && bs[0] == '0') break;
        A = Bigint(as);
        B = Bigint(bs);
        A.multi(B);
        A.toString(as);
        puts(as);
    }
    return 0;
}