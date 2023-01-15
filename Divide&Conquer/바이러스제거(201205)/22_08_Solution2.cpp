/*
24_바이러스제거_user_ver02
binary search : recursive
*/
#define rint register int

static const int LM = 50'000'000;
const int SECTOR = 512;

extern char virus_checkup(int n);
extern void culture(int n, int a, int b);
extern void clear(int n);

int bisearch(int st, int ed) {
    if (st >= ed) return st;
    int m = (st + ed) / 2;
    if (virus_checkup(LM + m))
        return bisearch(st, m);
    return bisearch(m + 1, ed);
}

void test()
{
    for (rint st = 0; st < LM;) {
        rint ed = st + SECTOR;
        if (ed > LM) ed = LM;

        // 테이블 생성
        culture(st + LM, st, st);
        for (rint i = st + 1; i < ed; ++i) {
            culture(i + LM, i + LM - 1, i);
        }

        if (virus_checkup(LM + ed - 1)) {  // 구간에 바이러스가 있다면
            int tg = bisearch(st, ed - 1); // 가장 처음 등장하는 1 위치 찾기
            clear(tg);
            st = tg + 1;                   // 다음 구간의 시작위치
        }
        else st = ed;                      // 구간에 바이러스가 없는 경우
    }
}