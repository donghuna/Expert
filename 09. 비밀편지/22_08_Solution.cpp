#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
09_비밀편지
1. Horner's method
2. Use bit operator
3. scanf
*/
#include <cstdio>

int code[8] = { 0B000000, 0b001111, 0b010011, 0b011100, 0b100110,  0b101001, 0b110101, 0b111010 };
int N;
char ans[10];

int check(int d) {
    for (int i = 0; i < 8; ++i) {
        // implementation here
        int x = code[i] ^ d;
        if ((x & (x - 1)) == 0) return i;
    }
    return -1;
}

int main() {
#ifdef _WIN32
    freopen("09.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    int d, a, i, j;
    for (i = 0; i < N; ++i) {
        d = 0;
        for (j = 0; j < 6; ++j) {
            scanf("%1d", &a);
            d = d * 2 + a;  // Horner's method
        }

        int ret = check(d);  // 0 ~ 7 : -1
        if (ret < 0) {
            printf("%d\n", i + 1);
            return 0;
        }
        ans[i] = ret + 'A';
    }
    puts(ans);
    return 0;
}
