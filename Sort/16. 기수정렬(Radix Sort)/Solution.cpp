/// ***** user.cpp *****
#define rint register int

const int LM = (int)25e6 + 5;
const int MSB = 1 << 31;
const int SHIFT = 8;         // 2^SHIFT 진법
// base를 나누는 이유는, 안나누면 모든 숫자에 대해서 counting을 해줘야하는데.. 2^32 크기의 배열 할당이 안됨.
const int BASE = 1 << SHIFT; // 구간크기
const int MASK = BASE - 1;
int sortedArr[LM], cnt[BASE];

/// 배열 A와 원소의 개수 N을 전달받아 초기화한다.
void initUser(int N, int *arr) {
	rint i, j;
	int*ap = sortedArr, *bp = arr, *tp;
	// preprocessing : sign비트 반전 시키기
	for (i = 0; i < N; ++i) ap[i] = bp[i] ^ MSB;

	// counting sort
	for (i = 0; i < 25; i += SHIFT) {
		for (j = 0; j < BASE; ++j) cnt[j] = 0;		// counting array 초기화
		for (j = 0; j < N; ++j) cnt[(ap[j] >> i) & MASK] ++;	// AP가 32 bit인데, 8개씩 쪼개서 4번을 확인할 거임. 그래서 8비트를 가져오는것. 가져온 다음 카운팅 함.
		for (j = 1; j < BASE; ++j) cnt[j] += cnt[j - 1];	// 이건 카운팅한거 누적하는 것.
		for (j = N - 1; j >= 0; --j)
			bp[--cnt[(ap[j] >> i) & MASK]] = ap[j];	// AP를 역으로 순회하면서, 누적값(=인덱스 위치) 확인하면서 BP배열에 정렬시켜 넣는다. 인덱스 위치했으면 -1 해줘야됨.

		tp = ap, ap = bp, bp = tp;	// swap을 해주는 이유는, 1번째 8bit는 정렬 되었는데 swap 안해주면 2번째 8bit로 다시 정렬됨..
	}
}


/// " A 배열을 오름차순 정렬했을때 idx번째 값은 얼마인가? "
/// 라는 질의에 실시간으로 답하는 함수이다.
int query(int idx) {
	return sortedArr[idx - 1] ^ MSB;
}
