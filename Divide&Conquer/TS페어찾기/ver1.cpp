/*
21_TS페어찾기_ver01
binary search : 0번 수와 차이로 그룹을 지어 확인하기, 차가 d인 수들의 최대갯수는 4이다.
*/
extern bool checkCards(int indexA, int indexB, int diff);

const int LM = 50005;
int M, A[LM][4], len[LM];

void playGame(int N) {
    register int i, j, s, m, e, d;
    for (i = 0; len[i]; ++i) len[i] = 0;
    M = N + N;
    A[0][len[0]++] = 0;
    for (i = 1; i < M; ++i) {
        d = s = 0, e = N - 1;
        while (s <= e) {
            m = (s + e) >> 1;
            if (checkCards(0, i, m))
                d = m, e = m - 1;
            else s = m + 1;
        }
        A[d][len[d]++] = i;
    }

    for (i = 1; len[i] == 4; ++i) {
        int* p = A[i];
        if (checkCards(p[0], p[1], 0)) checkCards(p[2], p[3], 0);
        else if (checkCards(p[0], p[2], 0)) checkCards(p[1], p[3], 0);
        else checkCards(p[0], p[3], 0), checkCards(p[1], p[2], 0);
    }
    for (; len[i]; ++i) checkCards(A[i][0], A[i][1], 0);
}