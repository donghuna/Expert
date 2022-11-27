#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/**
30_수식계산기1
*/
#include <cstdio>

char str[300], sign = '+';
int ret, d;

int main() {
    scanf("%s", str);
    for (int i = 0; sign;) {
        d = 0;
        while (str[i] >= '0' && str[i] <= '9')
            d = d * 10 + str[i++] - '0'; // Horner's method

        ret += (sign == '-') ? -d : d;
        sign = str[i++];
    }
    printf("%d", ret);
    return 0;
}