/*
32_EX합차곱계산기_user
긴자리수 연산 + 수식계산기
*/
#define rint register int

using LL = long long;
const int LM = 100;
const int MOD = 100000000;

inline int max(int a, int b) { return a > b ? a : b; }
struct Bigint {
    LL num[LM];
    int sign, len;
    void push(int nd) {
        init();
        num[0] = nd;
    }
    void init() {
        sign = 0, len = 1;
        for (rint i = 0; i < LM; ++i) num[i] = 0;
    }
    LL arrCmp(LL* a, int alen, LL* b, int blen) {
        if (alen != blen) return alen - blen;
        rint i = alen - 1;
        while (i > 0 && a[i] == b[i]) --i;
        return a[i] - b[i];
    }
    int isZero(Bigint& r) {
        return r.len == 1 && r.num[0] == 0;
    }
    void plus(LL* a, LL* b, int& len, int maxlen) {
        for (rint i = 0; i < maxlen; ++i) {
            a[i] += b[i];
            a[i + 1] += a[i] / MOD;
            a[i] %= MOD;
        }
        len = maxlen;
        if (a[len]) len++;
    }
    int minus(LL* tg, LL* a, LL* b, int len, int cmd) {
        for (rint i = 0; i < len; ++i) {
            tg[i] = a[i] - b[i];
            if (tg[i] < 0) tg[i] += MOD, a[i + 1]--;
        }
        for (; len > 0 && tg[len] == 0; --len);
        return len + 1;
    }
    void add(Bigint& r) {
        if (sign == r.sign) plus(num, r.num, len, max(len, r.len));
        else {
            LL cmp = arrCmp(num, len, r.num, r.len);
            if (cmp < 0) len = minus(num, r.num, num, r.len, 1), sign = r.sign;
            else if (cmp > 0) len = minus(num, num, r.num, len, 0);
            else init();
        }
    }
    void sub(Bigint& r) {
        r.sign ^= 1, add(r);
    }
    void multi(Bigint& r) {
        if (isZero(*this) || isZero(r)) { init(); return; }
        LL ret[LM] = { 0 };
        for (rint i = 0; i < len; ++i) {
            for (rint j = 0; j < r.len; ++j) {
                ret[i + j] += num[i] * r.num[j];
            }
        }

        sign ^= r.sign;
        len = len + r.len - 1;
        for (rint i = 0; i <= len; ++i) {
            ret[i + 1] += ret[i] / MOD;
            num[i] = ret[i] % MOD;
        }
        if (num[len]) len++;
    }
    void toChar(char* s) {
        rint i = len - 1, j = 0, k;
        LL d = 10000000, v = num[i];
        if (sign) s[j++] = '-';
        for (; v / d == 0; d /= 10);
        for (; d; d /= 10) s[j++] = (char)(v / d + '0'), v %= d;
        for (i--; i >= 0; --i) {
            d = num[i];
            for (k = 7; k >= 0; --k) s[j + k] = d % 10 + '0', d /= 10;
            j += 8;
        }
        s[j] = 0;
    }
}numStk[LM];

char form[10000], opStk[LM];
int numCnt, opCnt;

void calc() {
    char sign = opStk[opCnt];
    if (sign == '+') numStk[numCnt - 1].add(numStk[numCnt]);
    else if (sign == '-') numStk[numCnt - 1].sub(numStk[numCnt]);
    else if (sign == '*') numStk[numCnt - 1].multi(numStk[numCnt]);
    else return;   // '('
    opCnt--, numCnt--;
}

void test(char form[10000], char result[10000])
{
    numCnt = opCnt = 0;
    rint i, d;
    for (i = 0; form[i]; ++i) {
        if (form[i] >= '0' && form[i] <= '9') {
            d = 0;
            while (form[i] >= '0' && form[i] <= '9') {
                d = d * 10 + form[i] - '0';
                i++;
            }
            numStk[++numCnt].push(d);
            if (opStk[opCnt] == '*' || opStk[opCnt] == '/')
                calc();
        }
        else {
            if (form[i] == '+' || form[i] == '-') {
                if (numCnt > 1) calc();
                opStk[++opCnt] = form[i];
            }
            else if (form[i] == ')') {
                calc();
                opCnt--;
                if (opStk[opCnt] == '*' ||
                    opStk[opCnt] == '/') calc();
            }
            else opStk[++opCnt] = form[i];  // '(*/'
            i++;
        }
    }
    if (numCnt > 1) calc();
    numStk[1].toChar(result);
}