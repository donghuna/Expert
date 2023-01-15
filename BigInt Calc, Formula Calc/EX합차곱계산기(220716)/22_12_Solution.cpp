/*
34_EX����������_user
*/
#define rint register int

using LL = long long;
const int NLM = 100;
const int BASE = 100'000'000;

inline int max(int a, int b) { return a > b ? a : b; }
int strlen(const char* s, rint len = 0) {
    while (s[len]) ++len;
    return len;
}
struct Bigint {
    LL num[NLM];
    int sign, len;
    Bigint() { init(); }
    Bigint(int d) {     // *****$*****
        init();
        num[0] = d;
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
            a[i + 1] += a[i] / BASE;                  // �ڸ� �ø� ó��
            a[i] %= BASE;
        }
        len = maxlen;
        if (a[len]) len++;
    }
    int minus(LL* tg, LL* a, LL* b, int len, int cmd) {
        for (rint i = 0; i < len; ++i) {
            tg[i] = a[i] - b[i];
            if (tg[i] < 0) tg[i] += BASE, a[i + 1]--;  //�ڸ� ���� ó��
        }
        for (; len > 0 && tg[len] == 0; --len);
        return len + 1;
    }
    void add(Bigint& t) {
        if (sign == t.sign) // ���� ��ȣ���
            plus(num, t.num, len, max(len, t.len));
        else {              // �ٸ� ��ȣ���
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
}numStk[NLM];
char opStk[NLM];
int opTop, numTop;

void calc() {
    char op = opStk[opTop];
    if (op == '+') numStk[numTop - 1].add(numStk[numTop]);         // *****$*****
    else if (op == '-') numStk[numTop - 1].sub(numStk[numTop]);    // *****$*****
    else if (op == '*') numStk[numTop - 1].multi(numStk[numTop]);  // *****$*****
    else return;  // ��Ģ�����ڰ� �ƴ� ��� : ��) '('
    opTop--, numTop--;
}


void test(char exp[10000], char result[10000])
{
    opTop = numTop = 0;
    for (rint i = 0; exp[i]; ++i) {    // *****$***** : ������ �����ڷ� ����ϹǷ� ++i
        if (exp[i] > 47) {  // �����
            LL d = 0;
            for (; exp[i] > 47; ++i)   // �� ����
                d = d * 10 + exp[i] - '0';

            numStk[++numTop] = Bigint(d);// *****$*****
            if (opStk[opTop] == '*')    // *****$*****
                calc();
        }
        else {              // �����ڶ��
            if (exp[i] == '+' || exp[i] == '-') {
                calc();
                opStk[++opTop] = exp[i];
            }
            else if (exp[i] == ')') {
                calc();
                opTop--;  // '(' �����
                if (opStk[opTop] == '*')    // *****$*****
                    calc();
            }
            else {   // '(', '*', '/' �� �ܼ��� ������ ���ÿ� �߰��� �Ѵ�.
                opStk[++opTop] = exp[i];
            }
            i++;
        }
    }
    calc();  // ���� ����� �ִٸ� ����ϱ�
    numStk[1].toString(result);       // *****$*****
}