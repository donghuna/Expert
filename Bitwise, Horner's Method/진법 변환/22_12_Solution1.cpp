#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
07_진법변환_ver01
Horner's method
2진법수
1101 = (((0*2 + 1) * 2 + 1) * 2 + 0) * 2 + 1
*/
#include <cstdio>

using LL = long long;
int A, B;
char S[100];

char toChar(int d) {
    if (d < 10) return d + '0';
    return d + 'A' - 10;
}

void dToB(LL d) {
    // base condition
    if (d < B) {
        printf("%c", toChar(d));
        return;
    }
    // normal condition
    dToB(d / B);
    printf("%c", toChar(d % B));
}

int main() {
#ifdef _WIN32
    freopen("07.txt", "r", stdin);
#endif // _WIN32
    while (scanf("%d %s %d", &A, S, &B) && A) {
        // 1. to decimal from A_system : Horner's method
        LL d = 0;
        for (int i = 0; S[i]; ++i) {
            if (S[i] < 'A') d = d * A + (S[i] - '0'); // (S[i]-48)
            else d = d * A + (S[i] - 'A' + 10); // (S[i]-55)
        }

        // 2. to B_system from decimal : Horner's method
        dToB(d);
        puts("");
    }
    return 0;
}