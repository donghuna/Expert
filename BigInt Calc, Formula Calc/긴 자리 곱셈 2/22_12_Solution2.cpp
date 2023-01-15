#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
31_긴자리곱셈_ver02
8자리 압축 : loop unrolling
*/

#include <cstdio>
#define rint register int

using LL = long long;
const int LM = 2005;
const int NLM = LM / 8 + 2;
const int BASE = 100000000;

inline int max(int a, int b) { return a > b ? a : b; }
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

    LL arrCmp(LL* a, int alen, LL* b, int blen) {
        if (alen != blen) return alen - blen;
        rint i = alen - 1;
        while (i > 0 && a[i] == b[i]) --i;
        return a[i] - b[i];
    }
    int isZero() {
        return len == 1 && num[0] == 0;
    }
    void plus(LL* a, LL* b, int& len, int maxlen) {
        for (rint i = 0; i < maxlen; ++i) {
            a[i] += b[i];
            a[i + 1] += a[i] / BASE;                  // 자리 올림 처리
            a[i] %= BASE;
        }
        len = maxlen;
        if (a[len]) len++;
    }
    int minus(LL* tg, LL* a, LL* b, int len, int cmd) {
        for (rint i = 0; i < len; ++i) {
            tg[i] = a[i] - b[i];
            if (tg[i] < 0) tg[i] += BASE, a[i + 1]--;  //자리 내림 처리
        }
        for (; len > 0 && tg[len] == 0; --len);
        return len + 1;
    }
    void add(Bigint& t) {
        if (sign == t.sign) // 같은 부호라면
            plus(num, t.num, len, max(len, t.len));
        else {              // 다른 부호라면
            LL cmp = arrCmp(num, len, t.num, t.len);
            if (cmp < 0) len = minus(num, t.num, num, t.len, 1), sign = t.sign;
            else if (cmp > 0) len = minus(num, num, t.num, len, 0);
            else init();
        }
    }
    void sub(Bigint& t) {
        t.sign ^= 1, add(t);
    }

    void multi(Bigint& t) {
        if (isZero() || t.isZero()) {
            init(); return;
        }
        LL ret[NLM] = { 0 };
        for (rint i = 0; i < len; ++i) {
            for (rint j = 0; j < t.len; ++j) ret[i + j] += num[i] * t.num[j];
        }

        sign ^= t.sign;
        len += t.len - 1;
        for (rint i = 0; i <= len; ++i) {
            ret[i + 1] += ret[i] / BASE;
            num[i] = ret[i] % BASE;
        }
        len += (num[len] > 0);
    }

    void toString(char* s) {
        rint i = len - 1, j = 0;
        if (sign) s[j++] = '-';
        LL d = 10'000'000, n = num[i--];
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
    freopen("31.txt", "r", stdin);
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