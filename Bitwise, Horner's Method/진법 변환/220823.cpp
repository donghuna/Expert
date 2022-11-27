/*
7. 진법변환
*/

/*
ascii lookup table 만드는 코드
	for (int i = 0; i < 256; i++)
	{
		if (i >= '0' && i <= '9')
			printf("%d, ", i - '0');
		else if (i >= 'A' && i <= 'Z')
			printf("%d, ", i - 'A' + 10);
		else
			printf("0, ");
		if (i % 10 == 9)
			printf("\n");
	}
*/

#include <cstdio>
#define rint register int
using LL = long long;
int A, B;
char S[101];

int ascii[256] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	2, 3, 4, 5, 6, 7, 8, 9, 0, 0,
	0, 0, 0, 0, 0, 10, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
	25, 26, 27, 28, 29, 30, 31, 32, 33, 34,
	35, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

char data[128] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void dtoB(LL d)
{
	if(d < B)
		printf("%c", data[d%B]);
	else {
		dtoB(d / B);
		printf("%c", data[d%B]);
	}
}

int main() {
#ifdef _WIN32
	freopen("01.txt", "r", stdin);
#endif // _WIN32
	rint i;		// rint로 변경한것뿐인데 36ms -> 6ms 로 단축

	while (scanf("%d %s %d", &A, S, &B) && A)
	{
		LL d = 0;
		// A to dec
		for (i = 0; S[i]; ++i)		// S[i] == NULL == 즉 len 만큼만 돌게 됨.
		{
			/*
			if (S[i] < 'A') {
				d = d * A + S[i] - '0';
			}
			else
			{
				d = d * A + S[i] - 'A' + 10;
			}
			*/
			d = d * A + ascii[S[i]];		// Lookup table 사용
		}
		dtoB(d);
		puts("");
	}
	return 0;
}
