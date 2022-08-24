#include <stdio.h>

#define rint register int
int N;

int heap[500005];
int hn;

void push_heap(int nd)	// new data
{
	rint idx = ++hn;		// 새로운 값이 들어왔기 때문에, heap number (끝 위치)를 하나 늘려준다.
	// 루트가 아니고(루트면 그냥 넣으면 되니까), 신규 데이터가 기존의 부모들 보다 크면 기존값을 하위로 내린다.(반복적으로..)
	for (; idx > 1 && nd > heap[idx >> 1]; idx = idx >> 1) 
	{
		heap[idx] = heap[idx >> 1];
	}
	heap[idx] = nd;
}

void pop_heap()
{
	// heap에서의 pop은, heap[1]의 제거를 의미한다.
	// heap[1]과 heap[hn] 과 변경 (heap[1]을 삭제하기위해서..)
	// hn-- (마지막 힙 위치는 제거했다는 의미)
	// 완전이진트리 형식을 맞추기위해 루트부터 child와 크기 비교를 한다.
	// child가 양쪽에 다 있는지 확인
	// 양쪽에 다 있고, 양쪽다 부모보다 크며, 오른쪽 child가 더 크다면 => 오른쪽에 넣는다.
	// 양쪽에 다 있고, 양쪽다 부모보다 크며, 왼쪽 child가 더 크다면 => 왼쪽에 넣는다.
	// 양쪽 혹은 한쪽만 있고, 부모보다 크면 => 큰쪽 child에 넣는다.
	// 나머지는 부모가 더 큰 경우니까 끝.
	
	int nd = heap[hn];
	heap[hn--] = heap[1];
	rint idx = 2;
	//for (; idx <= hn && heap[idx] > nd; idx = idx << 1)	// 이렇게 하면, 왼쪽 child랑만 비교하게 되는 코드.
	//for (; idx <= hn && heap[idx+=(idx+1<=hn && heap[idx] < heap[idx+1])] > nd; idx = idx << 1) // child 끼리 비교하는 코드 추가.
	for (; idx <= hn && heap[idx += (idx < hn && heap[idx] < heap[idx + 1])] > nd; idx = idx << 1) // 좀 더 개선
	{
		heap[idx >> 1] = heap[idx];	// 부모 노드로 값을 옮긴다. (child가 더 크니까)
	}
	heap[idx >> 1] = nd; // 현재  idx위치는 child 위치인데, 위의 조건에 맞지 않아서 끝난 상황이기 때문에, 현재 idx보다 상위 노드에 값을 넣어야 된다.
}

void pop_all_heap()
{
	// pop_heap과 동일한데, 전체 다 pop 시키는 함수.
	rint i;
	for (i = 1; i <= N; ++i)
	{
		int nd = heap[hn];
		heap[hn--] = heap[1];
		rint idx = 2;		// idx를 i 위치에 같이 정의하면 느림;;
		for (; idx <= hn && heap[idx += (idx < hn && heap[idx] < heap[idx + 1])] > nd; idx = idx << 1)
		{
			heap[idx >> 1] = heap[idx];
		}
		heap[idx >> 1] = nd;
	}
}

int main() {
	scanf("%d", &N);
	
	rint i, A;
	for (i = 0; i < N; ++i)
	{
		scanf("%d", &A);
		push_heap(A);
	}

	for (i = 1; i <= hn; ++i)
	{
		printf("%d ", heap[i]);
	}

	printf("\n");
	pop_all_heap();
	
	for (i = 1; i <= N; ++i)
	{
		printf("%d ", heap[i]);
	}

	return 0;
}

