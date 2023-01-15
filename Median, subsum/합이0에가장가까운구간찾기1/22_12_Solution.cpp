#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
03_합이0에 가장 가까운 구간찾기1
two pointer
*/
#include <cstdio>

using LL = long long;  // typedef long long LL;
const int LM = 100005;
int N, arr[LM];
LL sum, ans;
int ansS, ansE;

LL abs(LL a) { return a < 0 ? -a : a; }
int main() {
#ifdef _WIN32
    freopen("03.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", arr + i);
        sum += arr[i];
    }

    ans = sum;
    ansS = 1, ansE = N;

    int s = 1, e = N;
    while (s <= e) {
        if (abs(sum) < abs(ans)) {
            ans = sum;
            ansS = s, ansE = e;
        }
        if (sum == 0) break;
        if (sum < 0) sum -= arr[s++];
        else sum -= arr[e--];
    }

    printf("%lld\n", ans);
    printf("%d %d\n", ansS, ansE);

    return 0;
}