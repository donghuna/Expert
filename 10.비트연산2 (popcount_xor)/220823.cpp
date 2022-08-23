#include <stdio.h>

#define rint register int
using LL = long long;
int N;
int A[100005];
LL sum, B[2];

int main() {
#ifdef _WIN32
	freopen("01.txt", "r", stdin);
#endif // _WIN32
	
	rint i, j;
	scanf("%d", &N);	// N 범위 : 10 <= 100,000
	for (i = 0; i < N; ++i) {
		scanf("%d", A + i);
	}

	for (j = 0; j < 32; ++j) {
		// 처음에 int로 해서 overflow 발생. 아래 sum 값이 마이너스가 되는상황;;
		// B를 처음에는 여기서 변수 선언 했었는데, 그거를 전역으로 바꾸기만해도 98ms -> 41ms 으로 속도 감소됨.
		B[0] = B[1] = 0;			
		for (i = 0; i < N; ++i) {
			B[(A[i] >> j) & 1]++;
		}
		sum += B[0] * B[1] * 2;
	}
	printf("%lld", sum % 1000000007);
	return 0;
}
