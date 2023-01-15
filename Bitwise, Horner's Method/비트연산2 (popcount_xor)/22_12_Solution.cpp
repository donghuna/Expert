#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
10_비트연산2
idea + bitwise
*/
#include <cstdio>

using LL = long long;
const int MOD = (int)1e9 + 7;
int N;
LL cnt[35], ans;

int main() {
#ifdef _WIN32
    freopen("10.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    int i, j, a;
    for (i = 0; i < N; ++i) {  // O(32 * N)
        scanf("%d", &a);
        for (int j = 0; j < 32; ++j) {
            cnt[j] += (a >> j) & 1;
        }
    }

    for (i = 0; i < 32; ++i) {
        ans += cnt[i] * (N - cnt[i]);
    }

    printf("%lld", ans * 2 % MOD);

    return 0;
}