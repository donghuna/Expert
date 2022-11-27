#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
34_���ڸ���������_ver02
8�ڸ� ����
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
        init();                         // 0���� �ʱ�ȭ 
        if (s[0] == '-') sign = 1, ++s; // �������
        rint slen = strlen(s), i = slen - 1;
        len = (slen + 7) / 8;           // 8�ڸ��� ����� Bigint�� ����
        int d = 0;
        for (; i >= 0; --i) {
            d = d * 10 + s[slen - 1 - i] - '0'; // Horner's method
            if (i % 8 == 0)             // 8�ڸ� ������ num�� ���� if(!(i&7))
                num[i / 8] = d, d = 0;  // ���� ���� �ڸ������� ����� num[i >> 3]
        }
    }
    void init() {    // 0���� �ʱ�ȭ 
        sign = 0, len = 1;
        for (rint i = 0; i < NLM; ++i) num[i] = 0;
    }

    bool isZero() { return len == 1 && num[0] == 0; }
    int arrCmp(int* ap, int alen, int* bp, int blen) {
        if (alen != blen) return alen - blen;
        rint i = alen - 1; // �� �ڰ� ���� ū ���̹Ƿ� ū������ ���ϱ�
        for (; i > 0 && ap[i] == bp[i]; --i);
        return ap[i] - bp[i];
    }

    int plus(int* ap, int* bp, int len) {
        for (rint i = 0; i < len; ++i) {
            ap[i] += bp[i];            // ���Ͽ� ����
            ap[i + 1] += ap[i] / BASE; // �ڸ��ø� ó��
            ap[i] %= BASE;             // �������� �����
        }
        return len + (ap[len] > 0);
    }
    int minus(int* tg, int* ap, int* bp, int len) {
        // ap[]���� bp[]�� �� ����� tg[]�� �����ϱ�
        for (rint i = 0; i < len; ++i) {
            tg[i] = ap[i] - bp[i];
            if (tg[i] < 0)  // �ڸ� ������ �ʿ��� ���
                tg[i] += BASE, ap[i + 1] --;
        }
        for (; len > 0 && tg[len] == 0; --len); // leading zero �����ϱ�
        return len + 1; // tg[len] �� 0�̹Ƿ� ���̴� len + 1�̴�.
    }
    void add(Bigint& r) {    // ���� ������
        if (sign == r.sign) // ��ȣ�� ������ ���ϱ�
            len = plus(num, r.num, max(len, r.len));
        else {              // ��ȣ�� �ٸ��� ������ ū������ ������ ���� ���� ����
            int cmp = arrCmp(num, len, r.num, r.len);
            if (cmp < 0) len = minus(num, r.num, num, r.len), sign = r.sign;
            else if (cmp > 0) len = minus(num, num, r.num, len);
            else init();    // �μ��� ���� ��� ���� ����� 0�̴�.
        }
    }
    void subtract(Bigint r) { // (�ǰ��� - ����) ���� ������ 
        r.sign ^= 1, add(r);  // ������ ��ȣ�� �ٲ��� add()�� ó���ϵ��� �Ѵ�.
    }
    void toString(char* s) {   // ����� ���ڿ��� ������ ���� �ٽ� ��������...
        rint i = 0, j, k = 0, n;
        for (; i < len; ++i) {  // �� �ڸ����� �����Ͽ� digit���ڷ� �����ϱ�
            n = num[i];
            for (j = 0; j < 8; ++j, n /= 10)
                s[k++] = n % 10 + '0';
        }
        s[k] = '0';                                 // ���ڿ� �� sentinel value
        for (; k > 0 && s[k] == '0'; --k) s[k] = 0; // leading zero����

        for (j = 0; j < k; ++j, --k) {              // �������� ������
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