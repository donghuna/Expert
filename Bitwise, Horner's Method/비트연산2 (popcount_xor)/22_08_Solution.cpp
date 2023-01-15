#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
10_비트연산2
*/
#include <cstdio>

using LL = long long;          // typedef long long LL;
//const int MOD = 1e9 + 7;     // 1e9 = 1 * 10의9제곱
const int MOD = 1'000'000'007; //1000000007

LL cnt[33], ans;

int main() {
#ifdef _WIN32
    freopen("input.txt", "r", stdin);
#endif // _WIN32

    int N, i, j, c;
    unsigned int a;
    scanf("%d", &N);
    for (i = 0; i < N; ++i) {
        scanf("%u", &a);
        // j번 자리가 1인 비트수를 cnt[j]에 세기
        for (j = 0; j < 32; ++j) {
            if ((a >> j) & 1) cnt[j] ++;
        }
    }
    for (i = 0; i < 32; ++i) {
        ans += cnt[i] * (N - cnt[i]); // *****
    }
    printf("%lld", ans * 2 % MOD);     // *****
    return 0;
}
