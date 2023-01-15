#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
32_수식계산기1_ver02
[수, 연산자] 단위로 처리하기
*/
#include <cstdio>

int ret;
char str[110], op = '+';
int main() {
#ifdef _WIN32
    freopen("32.txt", "r", stdin);
#endif // _WIN32
    scanf("%s", str);
    for (int i = 0; op;) {
        // 1. 수 추출
        int d = 0;
        for (; str[i] > 47; ++i)
            d = d * 10 + str[i] - '0';  // Horner's method
        ret += op == '+' ? d : -d;
        // 2. 연산자 추출
        op = str[i++];
    }
    printf("%d\n", ret);
    return 0;
}