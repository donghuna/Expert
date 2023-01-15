/*
22_거기있니_user
bitwise 이용
*/
extern int countSameNumber(int guess[]);
#define rint register int

const int LM = 100000;
int used[LM + 5], guess[LM + 5];

void consistOf(int N, int K) {
    rint i, j, x, p, bin = 1;
    while ((1 << (bin + 1)) < K) bin++;
    // bin의 최대값 16
    // 100000 / 16 = 6250
    for (i = 1; i <= N; i += bin) {  // 최대 6250번 반복가능
        p = 0;
        for (j = 0; j < bin; ++j) {  // 최대 16개씩 처리
            int len = 1 << j;        // 1, 2, 4, 8, 16, ... 32768
            for (x = 0; x < len && i + j <= LM; ++x) { // len 은 (i+j)의 개수
                guess[p++] = i + j;
            }
            for (; x < len; ++x) guess[p++] = 0;       // 나머지는 0으로 채우기
        }
        int res = countSameNumber(guess);
        for (j = 0; j < bin && i + j <= N; ++j) {
            used[i + j] = (res >> j) & 1;
        }
    }
}

int isEntryNumber(int num) {  // O(1)
    return used[num];
}