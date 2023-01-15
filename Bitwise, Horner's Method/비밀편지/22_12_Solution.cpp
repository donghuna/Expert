#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
09_비밀편지
bitwise
*/
#include <cstdio>

int code[] = { 0, 0x0f, 0b010011, 0b011100,
0b100110, 0b101001, 0b110101, 0b111010 };
char ans[12];

int getChar(int d) {
    // implement here
    for (int i = 0; i < 8; ++i) {
        int bit = d ^ code[i];       // 서로 다른 비트 구하기
        if ((bit & (bit - 1)) == 0) { // bit가 2의 제곱수이거나 0이라면
            return i;
        }
    }

    return -1;   // 못 찾은 경우
}

int main() {
#ifdef _WIN32
    freopen("09.txt", "r", stdin);
#endif // _WIN32
    int N, i, j, d, a;
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        // 2진 비트 6개로 10진 정수 d만들기
        d = 0;
        for (int j = 0; j < 6; ++j) {
            scanf("%1d", &a);
            d = d * 2 + a; // Horner's method
        }

        // d와 1비트 이하 차이나는 코드 찾기
        int rv = getChar(d); // -1, 0 ~ 7
        if (rv < 0) { // 적절한 코드가 없는 경우: rv=-1
            printf("%d\n", i + 1);
            return 0;
        }
        // rv: 0 ~ 7
        ans[i] = rv + 'A'; // 적절한 코드를 찾은 경우
    }
    puts(ans); // printf("%s\n", ans);
    return 0;
}