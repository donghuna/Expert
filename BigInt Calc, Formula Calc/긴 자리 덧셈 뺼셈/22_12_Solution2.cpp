#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
30_���ڸ���������_ver02
BigInt class : 1digit
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
    // default�� ����� ���ڸ� 0
    void init() {
        for (int i = 0; i < LM; ++i) num[i] = 0;
        len = 1;
        sign = 0;  // 0:��� Ȥ�� 0, 1:����
    }
    BigInt() { init(); }
    BigInt(const char* s) {
        init();
        if (s[0] == '-')
            ++s, sign = 1;
        len = strlen(s);
        for (int i = 0; i < len; ++i)
            num[len - i - 1] = s[i] - '0';
    }
    bool isZero() { return len == 1 && num[0] == 0; }
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

    void add(BigInt& b) {  // ��� ����� a�� ����ȴ�.
        if (sign == b.sign) len = plus(num, num, b.num, max(len, b.len));
        else {
            int cmp = arrcmp(num, len, b.num, b.len);
            if (cmp < 0) len = minus(num, b.num, num, b.len);
            else if (cmp > 0) len = minus(num, num, b.num, len);
            else init();   // �μ��� ���� ����̹Ƿ� ������ ����� 0�̴�.
        }
    }

    void subtract(BigInt b) {
        b.sign ^= 1, add(b);
    }

    void toString(char* ret) {
        for (int i = 0; i < len; ++i)
            ret[i] = num[len - i - 1] + '0';
        ret[len] = 0;  // ���ڿ��� �� : sentinel value
    }
}sum, diff, operand;
// ��: sum += operand
// ��: diff = abs(diff - operand)

int main() {
#ifdef _WIN32
    freopen("30.txt", "r", stdin);
#endif // _WIN32
    while (scanf("%s %s", as, bs)) {
        sum = diff = BigInt(as);
        operand = BigInt(bs);
        if (sum.isZero() && operand.isZero()) break;
        sum.add(operand);
        diff.subtract(operand);
        sum.toString(as);
        diff.toString(bs);
        puts(as);
        puts(bs);
    }

    return 0;
}