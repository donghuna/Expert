/*
23_어디있니_user_ver01
binary bit + Divide & Conquer
*/
extern int countScore(int guess[]);
#define rint register int
const int LM = 256;
int* ret;
int entry[LM];
int remainIdx[LM];

void getEntry() {
    rint i, j = 0, k, p, cnt = 0;
    int guess[LM] = { 0 };
    for (i = 1; i < 256 && cnt < 200; i += 7) {
        p = 0;
        for (j = 0; j < 7; ++j) {
            int len = 1 << j;
            for (k = 0; k < len; ++k) {
                guess[p++] = i + j;
            }
        }
        rint res = countScore(guess) % 256;   /// 존재 유무만 판단한다.
        for (j = 0; j < 7; ++j) if ((res >> j) & 1) {
            entry[cnt++] = i + j;
        }
    }
}

void DAC(int s, int e, int totalCnt) {
    // base condition
    if (totalCnt == 0) return;     // 범위를 벗어낫거나 자기 자리 찾은 경우가 없다면 종료
    if (totalCnt == e - s + 1) {   // s에서 e사이에 남아 있는 수들이 자기 자리를 찾은 경우
        for (rint i = s; i <= e; ++i) {
            ret[remainIdx[i]] = entry[remainIdx[i]];
            entry[remainIdx[i]] = 0;
        }
        return;
    }

    // normal condition : 분할하여 탐색
    int m = (s + e) / 2, left[LM] = { 0 };
    for (rint i = s; i <= m; ++i)
        left[remainIdx[i]] = entry[remainIdx[i]];
    int leftCnt = countScore(left) / 256; // 왼쪽 절반의 범위에서 자기 자리 찾은 수의 개수 구하기
    int rightCnt = totalCnt - leftCnt;    // 오른쪽 절반의 범위에서 자기 자리 찾은 수의 개수
    DAC(s, m, leftCnt);
    DAC(m + 1, e, rightCnt);
}

void consistOf(int userRet[])
{
    ret = userRet;
    rint i, tmp, remainCnt = 200;
    for (i = 0; i < 200; ++i) remainIdx[i] = i;
    // 1. get entry[]
    getEntry();

    // 2. find position
    while (true) {
        int cnt = countScore(entry) / 256;     /// 자기 자리 찾은 수의 개수
        DAC(0, remainCnt - 1, cnt);

        remainCnt = 0;                         /// 남아있는 수의 개수
        for (i = 0; i < 200; ++i) {
            if (entry[i])
                remainIdx[remainCnt++] = i;    /// 남아있는 수의 인덱스 담기
        }
        if (remainCnt == 0) break;             /// 남아있는 수가 없다면 종료

        /// 남은 수들을 한 자리씩 이동시키기
        tmp = entry[remainIdx[0]];
        for (i = 0; i < remainCnt - 1; ++i)
            entry[remainIdx[i]] = entry[remainIdx[i + 1]];
        entry[remainIdx[i]] = tmp;
    }
}