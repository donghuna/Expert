#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
07_진법변환
Horner's method + Look up table
*/
#include <cstdio>

using LL = long long;
int A, B;
char S[70], str[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int ascii[128] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, \
    2, 3, 4, 5, 6, 7, 8, 9, 0, 0, \
    0, 0, 0, 0, 0, 10, 11, 12, 13, 14, \
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, \
    25, 26, 27, 28, 29, 30, 31, 32, 33, 34, \
    35
};
void dToB(LL d) {
    if (d < B) printf("%c", str[d]);
    else {
        dToB(d / B);
        printf("%c", str[d % B]);
    }
}
int main() {
#ifdef _WIN32
    freopen("07.txt", "r", stdin);
#endif // _WIN32
    while (scanf("%d %s %d", &A, S, &B) && A) {
        // A -> decimal
        LL d = 0;
        for (int i = 0; S[i]; ++i) {
            d = d * A + ascii[S[i]];
        }
        // decimal -> B
        dToB(d);
        puts("");
    }
    return 0;
}
