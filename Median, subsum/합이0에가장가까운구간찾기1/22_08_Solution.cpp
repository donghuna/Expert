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

LL abs(LL a) { return a < 0 ? -a : a; }     // abs
int main() {
#ifdef _WIN32
    freopen("03.txt", "r", stdin);
#endif // _WIN32
    scanf("%d", &N);
    for (int i = 1; i <= N; ++i) {
        scanf("%d", A + i);         // == &A[i]
        sum += A[i];
    }
    ans = sum, ansSt = 1, ansEd = N;    // 전체 배열을 다 더하고, S와 E 위치도 끝과 끝으로 지정하여 초기값을 완성한다.

    int s = 1, e = N;   // two pointer
    while (s <= e) {
        if (abs(sum) < abs(ans)) {
            ans = sum;
            ansSt = s, ansEd = e;
        }
        if (sum == 0) break;            // 0이면 종료
        if (sum < 0)                    // 현재 범위에서 가장 작은 값 제외시키기 // 마이너스 : 스타팅 포인트를 +1 시켜서 sum 값을 늘려본다. (end point를 암만 바꿔봤자 값은 더 작아질 뿐이다.)
            sum -= A[s++];
        else 
            sum -= A[e--];              // 현재 범위에서 가장 큰 값 제외시키기 // 플러스 : end point를 -1 시켜서 sum 값을 줄여본다.
    }

    printf("%lld\n", ans);
    printf("%d %d\n", ansSt, ansEd);
    return 0;
}
