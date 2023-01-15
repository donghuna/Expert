#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
32_���ڸ���������_ver01
1�ڸ������� ó�� : naive function
*/

#include <cstdio>
#define rint register int

const int BASE = 10;
const int LM = 210;
char as[LM], bs[LM];

inline int max(int a, int b) { return a > b ? a : b; }
inline int strlen(const char* s, int len = 0) {
    while (s[len]) ++len;
    return len;
}

struct Bigint
{
    int num[LM];  // numerator
    int sign, len;
}sum, sub, operand;

void init(Bigint& r) {  // 0���� �ʱ�ȭ 
    r.len = 1, r.sign = 0;
    for (rint i = 0; i < LM; ++i) r.num[i] = 0;
}

bool isZero(Bigint& r) { return r.len == 1 && r.num[0] == 0; }
void init(Bigint& r, const char* s) {
    init(r);                         // 0���� �ʱ�ȭ 
    if (s[0] == '-') ++s, r.sign = 1;// �������
    r.len = strlen(s);               // ���� ���ϱ�
    for (rint i = 0; i < r.len; ++i) // ������ ��ȭ�ϰ� �������� ����
        r.num[r.len - i - 1] = s[i] - '0';
}

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
    ap[]���� bp[]�� �� ����� tg[]�� �����ϱ�
        for (rint i = 0; i < len; ++i) {
            tg[i] = ap[i] - bp[i];
            if (tg[i] < 0)  // �ڸ� ������ �ʿ��� ���
                ap[i + 1]--, tg[i] += BASE;
        }
    for (; len > 0 && tg[len] == 0; --len); // leading zero �����ϱ�
    return len + 1;  // tg[len] �� 0�̹Ƿ� ���̴� len + 1�̴�.
}
void add(Bigint& a, Bigint& r) { // ���� ������
    if (a.sign == r.sign)      // ��ȣ�� ������ ���ϱ�
        a.len = plus(a.num, r.num, max(a.len, r.len));
    else {                     // ��ȣ�� �ٸ��� ������ ū������ ������ ���� ���� ����
        int cmp = arrCmp(a.num, a.len, r.num, r.len);
        if (cmp < 0) a.len = minus(a.num, r.num, a.num, r.len), a.sign = r.sign;
        else if (cmp > 0) a.len = minus(a.num, a.num, r.num, a.len);
        else init(a); // �μ��� ���� ��� ���� ����� 0�̴�.
    }
}
void subtract(Bigint& a, Bigint r) { // (�ǰ��� - ����) ���� ������ 
    r.sign ^= 1, add(a, r);         // ������ ��ȣ�� �ٲ��� add()�� ó���ϵ��� �Ѵ�.
}

void toString(Bigint& a, char* s) {   // ����� ���ڿ��� ������ ���� �ٽ� ��������...
    for (int i = 0; i < a.len; ++i)
        s[i] = a.num[a.len - i - 1] + '0';
    s[a.len] = 0;  // ���ڿ� �� : sentinel value
}

int main() {
#ifdef _WIN32
    freopen("28.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif // _WIN32
    while (scanf("%s %s", &as, &bs)) {
        if (as[0] == '0' && bs[0] == '0') break;
        init(sum, as), sub = sum;
        init(operand, bs);
        add(sum, operand);
        subtract(sub, operand);
        toString(sum, as);
        toString(sub, bs);
        puts(as);
        puts(bs);
    }
    return 0;
}