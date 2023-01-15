#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
34_긴자리덧셈뺄셈_ver02
8자리 압축
*/
#include <cstdio>
#define rint register int

const int BASE = 100'000'000;
const int LM = 205;
const int NLM = LM / 8 + 2;

inline int max(int a, int b) { return a > b ? a : b; }
inline int strlen(char* s, int i = 0) {
    while (s[i]) ++i;
    return i;
}
struct Bigint {
    int num[NLM];
    int sign, len;
    Bigint() { init(); }
    Bigint(char* s) {
        init();                         // 0으로 초기화 
        if (s[0] == '-') sign = 1, ++s; // 음수라면
        rint slen = strlen(s), i = slen - 1;
        len = (slen + 7) / 8;           // 8자리로 압축된 Bigint의 길이
        int d = 0;
        for (; i >= 0; --i) {
            d = d * 10 + s[slen - 1 - i] - '0'; // Horner's method
            if (i % 8 == 0)             // 8자리 단위로 num에 저장 if(!(i&7))
                num[i / 8] = d, d = 0;  // 가장 높은 자리수부터 저장됨 num[i >> 3]
        }
    }
    void init() {    // 0으로 초기화 
        sign = 0, len = 1;
        for (rint i = 0; i < NLM; ++i) num[i] = 0;
    }

    bool isZero() { return len == 1 && num[0] == 0; }
    int arrCmp(int* ap, int alen, int* bp, int blen) {
        if (alen != blen) return alen - blen;
        rint i = alen - 1; // 맨 뒤가 가장 큰 수이므로 큰수부터 비교하기
        for (; i > 0 && ap[i] == bp[i]; --i);
        return ap[i] - bp[i];
    }

    int plus(int* ap, int* bp, int len) {
        for (rint i = 0; i < len; ++i) {
            ap[i] += bp[i];            // 더하여 저장
            ap[i + 1] += ap[i] / BASE; // 자리올림 처리
            ap[i] %= BASE;             // 나머지만 남기기
        }
        return len + (ap[len] > 0);
    }
    int minus(int* tg, int* ap, int* bp, int len) {
        // ap[]에서 bp[]를 뺀 결과를 tg[]에 저장하기
        for (rint i = 0; i < len; ++i) {
            tg[i] = ap[i] - bp[i];
            if (tg[i] < 0)  // 자리 내림이 필요한 경우
                tg[i] += BASE, ap[i + 1] --;
        }
        for (; len > 0 && tg[len] == 0; --len); // leading zero 제거하기
        return len + 1; // tg[len] 이 0이므로 길이는 len + 1이다.
    }
    void add(Bigint& r) {    // 덧셈 연산은
        if (sign == r.sign) // 부호가 같으면 더하기
            len = plus(num, r.num, max(len, r.len));
        else {              // 부호가 다른면 절댓값이 큰수에서 절댓값이 작은 수를 빼기
            int cmp = arrCmp(num, len, r.num, r.len);
            if (cmp < 0) len = minus(num, r.num, num, r.len), sign = r.sign;
            else if (cmp > 0) len = minus(num, num, r.num, len);
            else init();    // 두수가 같은 경우 빼기 결과는 0이다.
        }
    }
    void subtract(Bigint r) { // (피감수 - 감수) 뺄셈 연산은 
        r.sign ^= 1, add(r);  // 감수의 부호를 바꾼후 add()가 처리하도록 한다.
    }
    void toString(char* s) {   // 결과를 문자열로 저장할 때는 다시 역순으로...
        rint i = 0, j, k = 0, n;
        for (; i < len; ++i) {  // 각 자리별로 분해하여 digit문자로 저장하기
            n = num[i];
            for (j = 0; j < 8; ++j, n /= 10)
                s[k++] = n % 10 + '0';
        }
        s[k] = '0';                                 // 문자열 끝 sentinel value
        for (; k > 0 && s[k] == '0'; --k) s[k] = 0; // leading zero제거

        for (j = 0; j < k; ++j, --k) {              // 역순으로 뒤집기
            char t = s[j]; s[j] = s[k]; s[k] = t;
        }
    }
}sumRet, subRet, operand;

char as[LM], bs[LM];

int main() {
#ifdef _WIN32
    freopen("28.txt", "r", stdin);
#endif // _WIN32
    while (scanf("%s %s", &as, &bs)) {
        sumRet = subRet = Bigint(as);
        operand = Bigint(bs);
        if (sumRet.isZero() && operand.isZero()) break;
        sumRet.add(operand);
        subRet.subtract(operand);

        sumRet.toString(as);
        subRet.toString(bs);
        puts(as);
        puts(bs);
    }
    return 0;
}