#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
07_진법변환
Horner's method
*/
#include <cstdio>

using LL = long long;
int A, B;
char S[70];

char toChar(int d) {
    if (d < 10) return d + '0';
    return d + 'A' - 10;
}
void dToB(LL d) {
    if (d < B) printf("%c", toChar(d));
    else {
        dToB(d / B);
        printf("%c", toChar(d % B));
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
            if (S[i] < 'A') d = d * A + S[i] - '0';
            else d = d * A + S[i] - 'A' + 10;
        }
        // decimal -> B
        dToB(d);
        puts(""); // printf("\n");
    }
    return 0;
}
