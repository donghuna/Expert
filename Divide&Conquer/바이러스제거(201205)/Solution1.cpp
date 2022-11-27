/*
24_바이러스제거_user_ver01
binary search : Loop
*/
#define rint register int

static const int LM = 50'000'000;
const int SECTOR = 512;

extern char virus_checkup(int n);
extern void culture(int n, int a, int b);
extern void clear(int n);
int biSearchLoop(rint low, rint high) {
    rint mid, ret = -1;
    while (low <= high) {
        mid = (low + high) >> 1;
        if (low == high && ret < 0) // 위치가 미결정인데 남은 구간은 1개
            return low;             // low(high)가 바이러스가 있는 위치
        if (virus_checkup(LM + mid)) {
            ret = mid;
            high = mid - 1;
        }
        else low = mid + 1;
    }
    return ret;
}

void test()
{
    for (int st = 0; st < LM;) {
        int ed = st + SECTOR;
        if (ed > LM) ed = LM;

        // 테이블 생성
        culture(st + LM, st, st);
        for (rint i = st + 1; i < ed; ++i) {
            culture(i + LM, i + LM - 1, i);
        }

        if (virus_checkup(LM + ed - 1)) {      // 구간에 바이러스가 있다면
            int tg = biSearchLoop(st, ed - 1); // 구간에서 가장 처음 등장하는 1 위치 찾기
            clear(tg);
            st = tg + 1;                       // 다음 구간의 시작위치
        }
        else st = ed;                          // 구간에 바이러스가 없는 경우
    }
}