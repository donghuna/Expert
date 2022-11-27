#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
32_긴자리덧셈뺄셈_ver01
1자리단위로 처리 : naive function
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

void init(Bigint& r) {  // 0으로 초기화 
    r.len = 1, r.sign = 0;
    for (rint i = 0; i < LM; ++i) r.num[i] = 0;
}

bool isZero(Bigint& r) { return r.len == 1 && r.num[0] == 0; }
void init(Bigint& r, const char* s) {
    init(r);                         // 0으로 초기화 
    if (s[0] == '-') ++s, r.sign = 1;// 음수라면
    r.len = strlen(s);               // 길이 구하기
    for (rint i = 0; i < r.len; ++i) // 정수로 변화하고 역순으로 저장
        r.num[r.len - i - 1] = s[i] - '0';
}

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
    ap[]에서 bp[]를 뺀 결과를 tg[]에 저장하기
        for (rint i = 0; i < len; ++i) {
            tg[i] = ap[i] - bp[i];
            if (tg[i] < 0)  // 자리 내림이 필요한 경우
                ap[i + 1]--, tg[i] += BASE;
        }
    for (; len > 0 && tg[len] == 0; --len); // leading zero 제거하기
    return len + 1;  // tg[len] 이 0이므로 길이는 len + 1이다.
}
void add(Bigint& a, Bigint& r) { // 덧셈 연산은
    if (a.sign == r.sign)      // 부호가 같으면 더하기
        a.len = plus(a.num, r.num, max(a.len, r.len));
    else {                     // 부호가 다른면 절댓값이 큰수에서 절댓값이 작은 수를 빼기
        int cmp = arrCmp(a.num, a.len, r.num, r.len);
        if (cmp < 0) a.len = minus(a.num, r.num, a.num, r.len), a.sign = r.sign;
        else if (cmp > 0) a.len = minus(a.num, a.num, r.num, a.len);
        else init(a); // 두수가 같은 경우 빼기 결과는 0이다.
    }
}
void subtract(Bigint& a, Bigint r) { // (피감수 - 감수) 뺄셈 연산은 
    r.sign ^= 1, add(a, r);         // 감수의 부호를 바꾼후 add()가 처리하도록 한다.
}

void toString(Bigint& a, char* s) {   // 결과를 문자열로 저장할 때는 다시 역순으로...
    for (int i = 0; i < a.len; ++i)
        s[i] = a.num[a.len - i - 1] + '0';
    s[a.len] = 0;  // 문자열 끝 : sentinel value
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