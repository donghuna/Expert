#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
30_���ڸ���������_ver01
naive function
*/
#include <cstdio>

const int LM = 205;
const int BASE = 10;

char as[LM], bs[LM];
int strlen(const char* s, int len = 0) {
    for (; s[len]; ++len);
    return len;
}

struct BigInt {
    int num[LM];
    int len, sign;
}sum, diff, operand;
// ��: sum += operand
// ��: diff = abs(diff - operand)

// default�� ����� ���ڸ� 0
void init(BigInt& t) {
    for (int i = 0; i < LM; ++i) t.num[i] = 0;
    t.len = 1;
    t.sign = 0;  // 0:��� Ȥ�� 0, 1:����
}

void init(BigInt& t, const char* s) {
    init(t);
    if (s[0] == '-')
        ++s, t.sign = 1;
    t.len = strlen(s);
    for (int i = 0; i < t.len; ++i)
        t.num[t.len - i - 1] = s[i] - '0';
}

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }
int arrcmp(int* ap, int alen, int* bp, int blen) {
    if (alen != blen) return alen - blen;  // 1����: ���̰� ����� ū ���̴�.
    int i = alen - 1;                      // 2����: ���̰� ���ٸ� ���� �ڸ����� ���Ѵ�.
    for (; i > 0 && ap[i] == bp[i]; --i);  //        ���� �ڸ��� �μ��� ���� �ٸ� ��� �Ǵ� ������ �ڸ���� ����
    return ap[i] - bp[i];                  // ����(ap<bp), 0(ap==bp), ���(ap>bp)
}

int plus(int* tg, int* ap, int* bp, int len) {
    for (int i = 0; i < len; ++i) {
        tg[i] = ap[i] + bp[i];
        tg[i + 1] += tg[i] / BASE;  // �ڸ��ø� ó��
        tg[i] %= BASE;
    }
    return len + (tg[len] > 0);
}

int minus(int* tg, int* ap, int* bp, int len) {
    for (int i = 0; i < len; ++i) {
        tg[i] = ap[i] - bp[i];
        if (tg[i] < 0)
            ap[i + 1]--, tg[i] += BASE;
    }
    int i = len - 1;
    for (; i > 0 && tg[i] == 0; --i);  // delete leading zero
    return i + 1;
}

void add(BigInt& a, BigInt& b) {  // ��� ����� a�� ����ȴ�.
    if (a.sign == b.sign) a.len = plus(a.num, a.num, b.num, max(a.len, b.len));
    else {
        int cmp = arrcmp(a.num, a.len, b.num, b.len);
        if (cmp < 0) a.len = minus(a.num, b.num, a.num, b.len);
        else if (cmp > 0) a.len = minus(a.num, a.num, b.num, a.len);
        else init(a);   // �μ��� ���� ����̹Ƿ� ������ ����� 0�̴�.
    }
}

void subtract(BigInt& a, BigInt b) {
    b.sign ^= 1, add(a, b);
}

void output(BigInt& t) {
    for (int i = t.len - 1; i >= 0; --i)
        printf("%d", t.num[i]);
    puts("");
}

int main() {
#ifdef _WIN32
    freopen("30.txt", "r", stdin);
#endif // _WIN32
    while (scanf("%s %s", as, bs)) {
        if (as[0] == '0' && bs[0] == '0') break;
        init(sum, as), diff = sum;
        init(operand, bs);
        add(sum, operand);
        subtract(diff, operand);
        output(sum);
        output(diff);
    }

    return 0;
}