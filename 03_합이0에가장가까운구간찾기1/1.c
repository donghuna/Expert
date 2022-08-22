#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
/*
03_합이0에 가까운 1
tow pointer
*/
#include <cstdio>

using LL = long long; // typedef long long LL;
const int LM = 100005;
int N, A[LM];
LL ans, sum;
int ansSt, ansEd;

LL abs(LL a) { return a < 0 ? -a : a; }
int main() {
#ifdef _WIN32
    freopen("03.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", A + i);
        sum += A[i];
    }
    ans = sum, ansSt = 1, ansEd = N;

    int s = 1, e = N;
    while (s <= e) {
        if (abs(sum) < abs(ans)) {
            ans = sum;
            ansSt = s, ansEd = e;
        }
        if (sum == 0) break;
        if (sum < 0) 
            sum -= A[s++];
        else 
            sum -= A[e--];
    }

    printf("%lld\n", ans);
    printf("%d %d\n", ansSt, ansEd);
    return 0;
}
