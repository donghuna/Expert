#include <stdio.h>

#define rint register int

const int LM = 105;	// limit 105
int arr[LM][LM][LM];
int M, N, H;	// 가로 세로 높이, 2≤M≤100, 2≤N≤100, 1≤H≤100
int count;
int dh[] = { -1, 1, 0, 0, 0, 0 };
int dr[] = { 0, 0, -1, 1, 0, 0 };
int dc[] = { 0, 0, 0, 0, -1, 1 };

struct Data {
	int h, r, c, date;
}queue[LM * LM * LM];
int qf, qr;

void push(int h, int r, int c, int date)
{
	if (arr[h][r][c] == 0)	return;
	queue[qr++] = { h, r, c, date };
	arr[h][r][c] = 0;	// 익었으니, 배열에서는 뺀다.
	--count;
}

void BFS()
{
	if (count == 0)
	{
		// 모든 토마토가 익어있던 상황
		printf("0");
		return;
	}

	// queue에 있는거 돌리면서 push 한다.
	while (qf < qr)
	{
		Data &tD = queue[qf++];
		for (int i = 0; i < 6; i++)
		{
			push(tD.h + dh[i], tD.r + dr[i], tD.c + dc[i], tD.date + 1);	// 인접한 사과들 큐에 넣기
		}
	}

	if (count > 0)
	{
		// 사과가 모두 익지 못하는 상황
		printf("-1");
		return;
	}

	printf("%d", queue[qr - 1].date);
}

int main() {
#ifdef _WIN32
	freopen("number.txt", "r", stdin);
#endif // _WIN32

	scanf("%d %d %d", &M, &N, &H);
	rint i, j, k;

	// 원래 인풋은 정수 1은 익은 토마토, 정수 0은 익지 않은 토마토, 정수 -1은 토마토가 들어있지 않은 칸을 나타낸다. 
	// 그런데 여기서 visited array를 사용하지 않는 대신에, 원래 입력받은 arr를 사용할 것이기 때문에,
	// 익은 토마토는 2, 익지 않은 토마토(계속 탐색되어야될 위치)를 1, 없는공간은 0으로 만들어서,
	// 처음 입력받은 익은 토마토는 queue에 넣고 0으로 만들고,
	// 익지 않은 토마토만 array에 넣어서, 
	// 결국에 array에는 익지 않은 토마토만 남기고, 익은 토마토들은 queue에 다 들어가게 만드는 방법을 사용할 것이다.

	int value;
	for (k = 1; k <= H; ++k)
	{
		for (i = 1; i <= N; ++i)
		{
			for (j = 1; j <= M; ++j)
			{
				scanf("%d", &value);
				value++;
				//if (value == 0) // 빈공간이니까, nothing.
				if (value == 1) ++count, arr[k][i][j] = 1; // 익지 않은 토마토는 카운팅하고 배열에 넣기.
				if (value == 2) queue[qr++] = { k, i, j, 0 }; //push();	// 익은 토마토는 queue에 넣는다.
			}
		}
	}

	BFS();
	return 0;
}
